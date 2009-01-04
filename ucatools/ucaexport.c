/*
 * Exports Unicode and ASCII (byte stream) text
 *
 * Copyright (c) 2008, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <character_string.h>
#include <file_io.h>
#include <memory.h>
#include <narrow_string.h>
#include <notify.h>
#include <system_string.h>
#include <types.h>

#include <errno.h>

#include <stdio.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

/* If libtool DLL support is enabled set LIBUCA_DLL_IMPORT
 * before including libuca.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBUCA_DLL_IMPORT
#endif

#include <libuca.h>

#include "ucacommon.h"
#include "ucainput.h"
#include "ucaoutput.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Usage: ucaexport [ -c codepage ] [ -i input_format ] [ -n newline_converion ] [ -o output_format ] [ -BhlsvV ] source destination\n\n" );

	fprintf( stream, "\tsource:      the source file\n\n" );
	fprintf( stream, "\tdestination: the destination file\n\n" );

	fprintf( stream, "\t-B:          do not export a byte order mark\n" );
	fprintf( stream, "\t-c:          codepage of byte stream, options: ascii (default), windows-1250, windows-1251, windows-1252,\n" );
	fprintf( stream, "\t             windows-1253, windows-1254, windows-1255, windows-1256, windows-1257 or windows-1258\n" );
	fprintf( stream, "\t-h:          shows this help\n" );
	fprintf( stream, "\t-i:          input format, options: auto-detect (default), byte-stream, utf8, utf16le, utf16be\n" );
	fprintf( stream, "\t-l:          list information about the codepages\n" );
	fprintf( stream, "\t-n:          convert newline characters, options: none (default), cr, crlf, lf\n" );
	fprintf( stream, "\t-o:          output format, options: byte-stream, utf8 (default), utf16le, utf16be\n" );
	fprintf( stream, "\t-s:          enable strict conversion mode\n" );
	fprintf( stream, "\t-v:          verbose output to stderr\n" );
	fprintf( stream, "\t-V:          print version\n" );
}

/* Prints the codepages information
 */
void codepages_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "\tCodepage:     Description:\n" );
	fprintf( stream, "\tascii:        Support 7-bit ASCII character set\n" );
	fprintf( stream, "\twindows-1250: Supports the Windows 1250 (Central European) character set\n" );
	fprintf( stream, "\twindows-1251: Supports the Windows 1251 (Cyrillic) character set\n" );
	fprintf( stream, "\twindows-1252: Supports the Windows 1250 (Western European/Latin 1) character set\n" );
	fprintf( stream, "\twindows-1253: Supports the Windows 1253 (Greek) character set\n" );
	fprintf( stream, "\twindows-1254: Supports the Windows 1254 (Turkish) character set\n" );
	fprintf( stream, "\twindows-1255: Supports the Windows 1255 (Hebrew) character set\n" );
	fprintf( stream, "\twindows-1256: Supports the Windows 1256 (Arabic) character set\n" );
	fprintf( stream, "\twindows-1257: Supports the Windows 1257 (Baltic) character set\n" );
	fprintf( stream, "\twindows-1258: Supports the Windows 1258 (Vietnamese) character set\n" );
}

/* The main program
 */
#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libuca_unicode_character_t unicode_character[ 2 ];

	character_t *program                      = _CHARACTER_T_STRING( "ucaexport" );
	system_character_t *destination           = NULL;
	system_character_t *source                = NULL;
	uint8_t *destination_string_buffer        = NULL;
	uint8_t *source_string_buffer             = NULL;
	size_t destination_string_buffer_iterator = 0;
	size_t destination_string_buffer_size     = 1024;
	size_t source_string_buffer_iterator      = 0;
	size_t realignment_iterator               = 0;
	size_t source_string_buffer_size          = 1024;
	ssize_t read_count                        = 0;
	ssize_t write_count                       = 0;
	system_integer_t option                   = 0;
	int analyze_first_character               = 1;
	int destination_file_descriptor           = 0;
	int source_file_descriptor                = 0;
	int byte_stream_codepage                  = LIBUCA_CODEPAGE_ASCII;
	int export_byte_order_mark                = 1;
	int input_format                          = UCACOMMON_FORMAT_AUTO_DETECT;
	int newline_conversion                    = UCACOMMON_NEWLINE_CONVERSION_NONE;
	int output_format                         = UCACOMMON_FORMAT_UTF8;
	int verbose                               = 0;
	int result                                = 1;
	uint8_t amount_of_unicode_characters      = 0;
	uint8_t unicode_character_iterator        = 0;
	uint8_t strict_mode                       = 0;

	ucaoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_CHARACTER_T_STRING( "Bc:hi:ln:o:svV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf( stderr, "Invalid argument: %s\n",
				 argv[ optind ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'B':
				export_byte_order_mark = 0;

				break;

			case (system_integer_t) 'c':
				if( ucainput_determine_byte_stream_codepage(
				     optarg,
				     &byte_stream_codepage ) != 1 )
				{
					fprintf( stderr, "Unsupported byte stream codepage defaulting to: ascii.\n" );

					byte_stream_codepage = LIBUCA_CODEPAGE_ASCII;
				}
				break;

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'i':
				if( system_string_compare(
				 optarg,
				 _SYSTEM_CHARACTER_T_STRING( "auto-detect" ),
				 11 ) == 0 )
				{
					input_format = UCACOMMON_FORMAT_AUTO_DETECT;
				}
				else if( ucainput_determine_format(
				          optarg,
				          &input_format ) != 1 )
				{
					fprintf( stderr, "Unsupported input format defaulting to: auto-detect.\n" );

					input_format = UCACOMMON_FORMAT_AUTO_DETECT;
				}
				break;

			case (system_integer_t) 'l':
				codepages_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'n':
				if( ucainput_determine_newline_conversion(
				     optarg,
				     &newline_conversion ) != 1 )
				{
					fprintf( stderr, "Unsupported newline conversion defaulting to: none.\n" );

					newline_conversion = UCACOMMON_NEWLINE_CONVERSION_NONE;
				}
				break;

			case (system_integer_t) 'o':
				if( ucainput_determine_format(
				     optarg,
				     &output_format ) != 1 )
				{
					fprintf( stderr, "Unsupported output format defaulting to: utf8.\n" );

					output_format = UCACOMMON_FORMAT_UTF8;
				}
				break;

			case (system_integer_t) 's':
				strict_mode = 1;

				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				ucaoutput_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf( stderr, "Missing source.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind++ ];

	if( optind == argc )
	{
		fprintf( stderr, "Missing destination.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	destination = argv[ optind++ ];

	libuca_set_notify_values(
	 stderr,
	 verbose );

	source_file_descriptor = file_io_open(
	                          source,
	                          FILE_IO_O_RDONLY );

	if( source_file_descriptor == -1 )
	{
		fprintf( stderr, "Unable to open source: %" PRIs_SYSTEM ".\n",
		 source );

		return( EXIT_FAILURE );
	}
	destination_file_descriptor = file_io_open(
	                               destination,
	                               ( FILE_IO_O_WRONLY | FILE_IO_O_CREAT | FILE_IO_O_TRUNC ) );

	if( destination_file_descriptor == -1 )
	{
		fprintf( stderr, "Unable to open destination: %" PRIs_SYSTEM ".\n",
		 destination );

		file_io_close(
		 source_file_descriptor );

		return( EXIT_FAILURE );
	}
	source_string_buffer = (uint8_t *) memory_allocate(
	                                    sizeof( uint8_t ) * source_string_buffer_size );

	if( source_string_buffer == NULL )
	{
		fprintf( stderr, "Unable to create source string buffer.\n" );

		file_io_close(
		 source_file_descriptor );
		file_io_close(
		 destination_file_descriptor );

		return( EXIT_FAILURE );
	}
	destination_string_buffer = (uint8_t *) memory_allocate(
	                                         sizeof( uint8_t ) * destination_string_buffer_size );

	if( destination_string_buffer == NULL )
	{
		fprintf( stderr, "Unable to create destination string buffer.\n" );

		file_io_close(
		 source_file_descriptor );
		file_io_close(
		 destination_file_descriptor );

		memory_free(
		 source_string_buffer );

		return( EXIT_FAILURE );
	}
	if( export_byte_order_mark != 0 )
	{
		switch( output_format )
		{
			case UCACOMMON_FORMAT_UTF8:
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xef;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xbb;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xbf;
				break;

			case UCACOMMON_FORMAT_UTF16BE:
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xfe;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xff;
				break;

			case UCACOMMON_FORMAT_UTF16LE:
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xff;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xfe;
				break;

			case UCACOMMON_FORMAT_UTF32BE:
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0x00;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0x00;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xfe;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xff;
				break;

			case UCACOMMON_FORMAT_UTF32LE:
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xff;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0xfe;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0x00;
				destination_string_buffer[ destination_string_buffer_iterator++ ] = 0x00;
				break;

			default:
				break;
		}
	}
	while( 1 )
	{
		read_count = file_io_read(
		              source_file_descriptor,
		              &source_string_buffer[ source_string_buffer_iterator ],
		              source_string_buffer_size - source_string_buffer_iterator );

		if( read_count < 0 )
		{
			fprintf( stderr, "Unable to read from source file.\n" );

			result = -1;

			break;
		}
		read_count                    += source_string_buffer_iterator;
		source_string_buffer_iterator  = 0;

		if( read_count == 0 )
		{
			break;
		}
		if( analyze_first_character != 0 )
		{
			if( ( source_string_buffer[ 0 ] == 0xef )
			 && ( source_string_buffer[ 1 ] == 0xbb )
			 && ( source_string_buffer[ 2 ] == 0xbf ) )
			{
				if( input_format == UCACOMMON_FORMAT_AUTO_DETECT )
				{
					input_format = UCACOMMON_FORMAT_UTF8;
				}
				if( input_format == UCACOMMON_FORMAT_UTF8 )
				{
					source_string_buffer_iterator += 3;
				}
			}
			else if( ( source_string_buffer[ 0 ] == 0xfe )
			      && ( source_string_buffer[ 1 ] == 0xff ) )
			{
				if( input_format == UCACOMMON_FORMAT_AUTO_DETECT )
				{
					input_format = UCACOMMON_FORMAT_UTF16BE;
				}
				if( input_format == UCACOMMON_FORMAT_UTF16BE )
				{
					source_string_buffer_iterator += 2;
				}
			}
			else if( ( source_string_buffer[ 0 ] == 0xff )
			      && ( source_string_buffer[ 1 ] == 0xfe ) )
			{
				if( ( source_string_buffer[ 2 ] == 0x00 )
			         && ( source_string_buffer[ 3 ] == 0x00 ) )
				{
					if( input_format == UCACOMMON_FORMAT_AUTO_DETECT )
					{
						input_format = UCACOMMON_FORMAT_UTF32LE;
					}
					if( input_format == UCACOMMON_FORMAT_UTF32LE )
					{
						source_string_buffer_iterator += 4;
					}
				}
				else
				{
					if( input_format == UCACOMMON_FORMAT_AUTO_DETECT )
					{
						input_format = UCACOMMON_FORMAT_UTF16LE;
					}
					if( input_format == UCACOMMON_FORMAT_UTF16LE )
					{
						source_string_buffer_iterator += 2;
					}
				}
			}
			else if( ( source_string_buffer[ 0 ] == 0x00 )
			      && ( source_string_buffer[ 1 ] == 0x00 )
			      && ( source_string_buffer[ 1 ] == 0xfe )
			      && ( source_string_buffer[ 1 ] == 0xff ) )
			{
				if( input_format == UCACOMMON_FORMAT_AUTO_DETECT )
				{
					input_format = UCACOMMON_FORMAT_UTF32BE;
				}
				if( input_format == UCACOMMON_FORMAT_UTF32BE )
				{
					source_string_buffer_iterator += 4;
				}
			}
			else if( input_format == UCACOMMON_FORMAT_AUTO_DETECT )
			{
				input_format = UCACOMMON_FORMAT_BYTE_STREAM;
			}
			read_count -= source_string_buffer_iterator;

			analyze_first_character = 0;

			fprintf( stdout, "Exporting:\n" );
			fprintf( stdout, "\tSource:\t\t: %s\n",
			 source );
			fprintf( stdout, "\tof format:\t: " );

			if( input_format == UCACOMMON_FORMAT_BYTE_STREAM )
			{
				fprintf( stdout, "byte stream" );
			}
			else if( input_format == UCACOMMON_FORMAT_UTF8 )
			{
				fprintf( stdout, "UTF-8" );
			}
			else if( input_format == UCACOMMON_FORMAT_UTF16BE )
			{
				fprintf( stdout, "UTF-16 big endian" );
			}
			else if( input_format == UCACOMMON_FORMAT_UTF16LE )
			{
				fprintf( stdout, "UTF-16 little endian" );
			}
			else if( input_format == UCACOMMON_FORMAT_UTF32BE )
			{
				fprintf( stdout, "UTF-32 big endian" );
			}
			else if( input_format == UCACOMMON_FORMAT_UTF32LE )
			{
				fprintf( stdout, "UTF-32 little endian" );
			}
			fprintf( stdout, "\n" );

			fprintf( stdout, "\tDestination:\t: %s\n",
			 destination );
			fprintf( stdout, "\tof format:\t: " );

			if( output_format == UCACOMMON_FORMAT_BYTE_STREAM )
			{
				fprintf( stdout, "byte stream" );
			}
			else if( output_format == UCACOMMON_FORMAT_UTF8 )
			{
				fprintf( stdout, "UTF-8" );
			}
			else if( output_format == UCACOMMON_FORMAT_UTF16BE )
			{
				fprintf( stdout, "UTF-16 big endian" );
			}
			else if( output_format == UCACOMMON_FORMAT_UTF16LE )
			{
				fprintf( stdout, "UTF-16 little endian" );
			}
			else if( output_format == UCACOMMON_FORMAT_UTF32BE )
			{
				fprintf( stdout, "UTF-32 big endian" );
			}
			else if( output_format == UCACOMMON_FORMAT_UTF32LE )
			{
				fprintf( stdout, "UTF-32 little endian" );
			}
			fprintf( stdout, "\n" );
			fprintf( stdout, "\n" );

			/* TODO print codepage
			 */
		}
		for( ; read_count > 0; read_count-- )
		{
			/* Sanity check
			 */
			if( source_string_buffer_iterator >= source_string_buffer_size )
			{
				break;
			}
			/* Make sure to have at least room for a 6 byte character in the destination string buffer
			 */
		 	if( destination_string_buffer_iterator >= ( destination_string_buffer_size - 5 ) )
			{
				break;
			}
			switch( input_format )
			{
				case UCACOMMON_FORMAT_BYTE_STREAM:
					result = libuca_unicode_character_copy_from_byte_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  byte_stream_codepage,
						  strict_mode );
					break;

				case UCACOMMON_FORMAT_UTF8:
					result = libuca_unicode_character_copy_from_utf8(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  strict_mode );
					break;

				case UCACOMMON_FORMAT_UTF16BE:
					result = libuca_unicode_character_copy_from_utf16_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUCA_ENDIAN_BIG,
						  strict_mode );
					break;

				case UCACOMMON_FORMAT_UTF16LE:
					result = libuca_unicode_character_copy_from_utf16_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUCA_ENDIAN_LITTLE,
						  strict_mode );
					break;

				case UCACOMMON_FORMAT_UTF32BE:
					result = libuca_unicode_character_copy_from_utf32_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUCA_ENDIAN_BIG,
						  strict_mode );
					break;

				case UCACOMMON_FORMAT_UTF32LE:
					result = libuca_unicode_character_copy_from_utf32_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUCA_ENDIAN_LITTLE,
						  strict_mode );
					break;

				default:
					fprintf( stderr, "Unsupported input format.\n" );

					result = -1;

					break;
			}
			if( result != 1 )
			{
				fprintf( stderr, "Unable to convert input character.\n" );

				break;
			}
			amount_of_unicode_characters++;

			if( newline_conversion != UCACOMMON_NEWLINE_CONVERSION_NONE )
			{
				/* Determine if character is a line feed (LF)
				 */
				if( unicode_character[ unicode_character_iterator ] == 0x000a )
				{
					if( newline_conversion == UCACOMMON_NEWLINE_CONVERSION_CRLF )
					{
						if( unicode_character_iterator == 0 )
						{
							unicode_character[ unicode_character_iterator     ] = 0x000d;
							unicode_character[ unicode_character_iterator + 1 ] = 0x000a;
			
							amount_of_unicode_characters++;
						}
					}
					else if( newline_conversion == UCACOMMON_NEWLINE_CONVERSION_CR )
					{
						if( unicode_character_iterator == 0 )
						{
							unicode_character[ unicode_character_iterator ] = 0x000d;
						}
						else if( unicode_character_iterator == 1 )
						{
							unicode_character[ unicode_character_iterator - 1 ] = 0x000d;

							amount_of_unicode_characters--;
						}
					}
					else if( newline_conversion == UCACOMMON_NEWLINE_CONVERSION_LF )
					{
						if( unicode_character_iterator == 1 )
						{
							unicode_character[ unicode_character_iterator - 1 ] = 0x000a;

							amount_of_unicode_characters--;
						}
					}
				}
				/* Determine if character is a carriage return (CR)
				 */
				else if( unicode_character[ unicode_character_iterator ] == 0x000d )
				{
					unicode_character_iterator++;

					continue;
				}
			}
			/* Write all unicode characters
			 */
			for( unicode_character_iterator = 0; unicode_character_iterator < amount_of_unicode_characters; unicode_character_iterator++ )
			{
				switch( output_format )
				{
					case UCACOMMON_FORMAT_BYTE_STREAM:
						result = libuca_unicode_character_copy_to_byte_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  byte_stream_codepage,
							  strict_mode );
						break;

					case UCACOMMON_FORMAT_UTF8:
						result = libuca_unicode_character_copy_to_utf8(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  strict_mode );
						break;

					case UCACOMMON_FORMAT_UTF16BE:
						result = libuca_unicode_character_copy_to_utf16_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUCA_ENDIAN_BIG,
							  strict_mode );
						break;

					case UCACOMMON_FORMAT_UTF16LE:
						result = libuca_unicode_character_copy_to_utf16_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUCA_ENDIAN_LITTLE,
							  strict_mode );
						break;

					case UCACOMMON_FORMAT_UTF32BE:
						result = libuca_unicode_character_copy_to_utf32_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUCA_ENDIAN_BIG,
							  strict_mode );
						break;

					case UCACOMMON_FORMAT_UTF32LE:
						result = libuca_unicode_character_copy_to_utf32_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUCA_ENDIAN_LITTLE,
							  strict_mode );
						break;

					default:
						fprintf( stderr, "Unsupported output format.\n" );

						result = -1;

						break;
				}
				if( result != 1 )
				{
					fprintf( stderr, "Unable to convert output character.\n" );

					break;
				}
			}
			amount_of_unicode_characters = 0;
			unicode_character_iterator   = 0;
		}
		if( destination_string_buffer_iterator > 0 )
		{
			write_count = file_io_write(
			               destination_file_descriptor,
			               destination_string_buffer,
		        	       destination_string_buffer_iterator );

			if( write_count < 0 )
			{
				fprintf( stderr, "Unable to write to destination file.\n" );

				result = -1;

				break;
			}
			destination_string_buffer_iterator = 0;
		}
		/* Realign the remaining bytes to the start of the source string buffer
		 */
		realignment_iterator          = source_string_buffer_iterator;
		source_string_buffer_iterator = 0;

		for( ; read_count > 0; read_count-- )
		{
			source_string_buffer[ source_string_buffer_iterator++ ] = source_string_buffer[ realignment_iterator++ ];
		}
	}
	memory_free(
	 source_string_buffer );
	memory_free(
	 destination_string_buffer );

	if( file_io_close(
	     source_file_descriptor ) != 0 )
	{
		fprintf( stderr, "Unable to close source: %" PRIs_SYSTEM ".\n",
		 source );
	}
	if( file_io_close(
	     destination_file_descriptor ) != 0 )
	{
		fprintf( stderr, "Unable to close destination: %" PRIs_SYSTEM ".\n",
		 destination );
	}
	if( result != 1 )
	{
		return( EXIT_FAILURE );
	}
	fprintf( stdout, "Export completed.\n" );

	return( EXIT_SUCCESS );
}

