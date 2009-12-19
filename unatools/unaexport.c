/*
 * Exports Unicode and ASCII (byte stream) text
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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
#include <memory.h>
#include <narrow_string.h>
#include <types.h>

#include <liberror.h>

#include <errno.h>

#include <stdio.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

/* If libtool DLL support is enabled set LIBUNA_DLL_IMPORT
 * before including libuna.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBUNA_DLL_IMPORT
#endif

#include <libuna.h>

#include <libsystem.h>

#include "byte_size_string.h"
#include "process_status.h"
#include "unacommon.h"
#include "unainput.h"
#include "unaoutput.h"

#define UNAEXPORT_BUFFER_SIZE	8 * 1024 * 1024

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use unaexport to export text in one encoding to another.\n\n" );

	fprintf( stream, "Usage: unaexport [ -c codepage ] [ -i input_format ] [ -n newline_conversion ]\n" );
	fprintf( stream, "       [ -o output_format ] [ -BhlqvV ] source destination\n\n" );

	fprintf( stream, "\tsource:      the source file\n" );
	fprintf( stream, "\tdestination: the destination file\n\n" );

	fprintf( stream, "\t-B:          do not export a byte order mark (BOM)\n" );
	fprintf( stream, "\t-c:          codepage of byte-stream, options: ascii (default), iso-8559-1,\n" );
	fprintf( stream, "\t             iso-8559-2, iso-8559-3, iso-8559-4, iso-8559-5, iso-8559-6,\n" );
	fprintf( stream, "\t             iso-8559-7, iso-8559-8, iso-8559-9, iso-8559-10, iso-8559-11,\n" );
	fprintf( stream, "\t             iso-8559-13, iso-8559-14, iso-8559-15, iso-8559-16,\n" );
	fprintf( stream, "\t             windows-874, windows-1250, windows-1251, windows-1252,\n" );
	fprintf( stream, "\t             windows-1253, windows-1254, windows-1255, windows-1256\n" );
	fprintf( stream, "\t             windows-1257 or windows-1258\n" );
	fprintf( stream, "\t-h:          shows this help\n" );
	fprintf( stream, "\t-i:          input format, options: auto-detect (default), utf7,\n" );
	fprintf( stream, "\t             utf8, utf16be, utf16le, utf32be or utf32le\n" );
	fprintf( stream, "\t-l:          list information about the codepages\n" );
	fprintf( stream, "\t-n:          convert newline characters, options: none (default), cr,\n" );
	fprintf( stream, "\t             crlf or lf\n" );
	fprintf( stream, "\t-o:          output format, options: byte-stream, utf7, utf8 (default),\n" );
	fprintf( stream, "\t             utf16be, utf16le, utf32be or utf32le\n" );
	fprintf( stream, "\t-q:          quiet shows no status information\n" );
	fprintf( stream, "\t-v:          verbose output to stderr\n" );
	fprintf( stream, "\t-V:          print version\n" );
}

/* Prints the export information
 */
void export_fprint(
      FILE *stream,
      const libsystem_character_t *source_filename,
      int input_format,
      const libsystem_character_t *destination_filename,
      int output_format,
      int byte_stream_codepage,
      int export_byte_order_mark,
      int newline_conversion )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf(
	 stream,
	 "Exporting:\n" );
	fprintf(
	 stream,
	 "\tsource:\t\t\t%s\n",
	 source_filename );
	fprintf(
	 stream,
	 "\tof format:\t\t" );
	unaoutput_format_fprint(
	 stream,
	 input_format );
	fprintf(
	 stream,
	 "\n" );

	fprintf(
	 stream,
	 "\tdestination:\t\t%s\n",
	 destination_filename );
	fprintf(
	 stream,
	 "\tof format:\t\t" );
	unaoutput_format_fprint(
	 stream,
	 output_format );
	fprintf(
	 stream,
	 "\n" );

	fprintf(
	 stream,
	 "\tbyte-stream codepage:\t" );
	unaoutput_codepage_fprint(
	 stream,
	 byte_stream_codepage );
	fprintf(
	 stream,
	 "\n" );

	fprintf(
	 stream,
	 "\texport byte order mark:\t" );

	if( export_byte_order_mark == 0 )
	{
		fprintf(
		 stream,
		 "no" );
	}
	else
	{
		fprintf(
		 stream,
		 "yes" );
	}
	fprintf(
	 stream,
	 "\n" );

	fprintf(
	 stream,
	 "\tnewline conversion:\t" );
	
	if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_NONE )
	{
		fprintf(
		 stream,
		 "none" );
	}
	else if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CRLF )
	{
		fprintf(
		 stream,
		 "carriage return and line feed (crlf)" );
	}
	else if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CR )
	{
		fprintf(
		 stream,
		 "carriage return (cr)" );
	}
	else if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_LF )
	{
		fprintf(
		 stream,
		 "line feed (lf)" );
	}
	else
	{
		fprintf(
		 stream,
		 "unsupported" );
	}
	fprintf(
	 stream,
	 "\n" );

	fprintf(
	 stream,
	 "\n" );
}

/* Exports the source file to the destination file
 * Returns the amount of bytes of the source processed or -1 on error
 */
ssize64_t unaexport(
           const libsystem_character_t *source_filename,
           int input_format,
           const libsystem_character_t *destination_filename,
           int output_format,
           int byte_stream_codepage,
           int export_byte_order_mark,
           int newline_conversion,
           process_status_t *process_status,
           liberror_error_t **error )
{
	libuna_unicode_character_t unicode_character[ 2 ];

	uint8_t *destination_string_buffer              = NULL;
	uint8_t *source_string_buffer                   = NULL;
	static char *function                           = "unaexport";
	libsystem_file_handle_t destination_file_handle = LIBSYSTEM_FILE_HANDLE_EMPTY;
	libsystem_file_handle_t source_file_handle      = LIBSYSTEM_FILE_HANDLE_EMPTY;
	ssize64_t export_count                          = 0;
	size_t destination_string_buffer_iterator       = 0;
	size_t destination_string_buffer_size           = UNAEXPORT_BUFFER_SIZE;
	size_t last_source_string_buffer_iterator       = 0;
	size_t source_string_buffer_iterator            = 0;
	size_t realignment_iterator                     = 0;
	size_t source_string_buffer_size                = UNAEXPORT_BUFFER_SIZE;
	ssize_t read_count                              = 0;
	ssize_t write_count                             = 0;
	uint32_t destination_utf7_stream_base64_data    = 0;
	uint32_t source_utf7_stream_base64_data         = 0;
	uint8_t amount_of_unicode_characters            = 0;
	uint8_t analyze_first_character                 = 1;
	uint8_t unicode_character_iterator              = 0;
	int result                                      = 1;

	if( source_filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source filename.",
		 function );

		return( -1 );
	}
	if( destination_filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination filename.",
		 function );

		return( -1 );
	}
	if( ( input_format != UNACOMMON_FORMAT_AUTO_DETECT )
	 && ( input_format != UNACOMMON_FORMAT_BYTE_STREAM )
	 && ( input_format != UNACOMMON_FORMAT_UTF7 )
	 && ( input_format != UNACOMMON_FORMAT_UTF8 )
	 && ( input_format != UNACOMMON_FORMAT_UTF16BE )
	 && ( input_format != UNACOMMON_FORMAT_UTF16LE )
	 && ( input_format != UNACOMMON_FORMAT_UTF32BE )
	 && ( input_format != UNACOMMON_FORMAT_UTF32LE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported input format.",
		 function );

		return( -1 );
	}
	if( ( output_format != UNACOMMON_FORMAT_BYTE_STREAM )
	 && ( output_format != UNACOMMON_FORMAT_UTF7 )
	 && ( output_format != UNACOMMON_FORMAT_UTF8 )
	 && ( output_format != UNACOMMON_FORMAT_UTF16BE )
	 && ( output_format != UNACOMMON_FORMAT_UTF16LE )
	 && ( output_format != UNACOMMON_FORMAT_UTF32BE )
	 && ( output_format != UNACOMMON_FORMAT_UTF32LE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported output format.",
		 function );

		return( -1 );
	}
	if( ( newline_conversion != UNACOMMON_NEWLINE_CONVERSION_NONE )
	 && ( newline_conversion != UNACOMMON_NEWLINE_CONVERSION_CRLF )
	 && ( newline_conversion != UNACOMMON_NEWLINE_CONVERSION_CR )
	 && ( newline_conversion != UNACOMMON_NEWLINE_CONVERSION_LF ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported newline conversion.",
		 function );

		return( -1 );
	}
	if( libsystem_file_open(
	     &source_file_handle,
	     source_filename,
	     LIBSYSTEM_FILE_OPEN_READ,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open source: %" PRIs_LIBSYSTEM ".",
		 function,
		 source_filename );

		return( -1 );
	}
	if( libsystem_file_open(
	     &destination_file_handle,
	     destination_filename,
	     LIBSYSTEM_FILE_OPEN_WRITE_TRUNCATE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open destination: %" PRIs_LIBSYSTEM ".",
		 function,
		 destination_filename );

		libsystem_file_close(
		 &source_file_handle,
		 NULL );

		return( -1 );
	}
	source_string_buffer = (uint8_t *) memory_allocate(
	                                    sizeof( uint8_t ) * source_string_buffer_size );

	if( source_string_buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create source string buffer.",
		 function );

		libsystem_file_close(
		 &destination_file_handle,
		 NULL );
		libsystem_file_close(
		 &source_file_handle,
		 NULL );

		return( -1 );
	}
	destination_string_buffer = (uint8_t *) memory_allocate(
	                                         sizeof( uint8_t ) * destination_string_buffer_size );

	if( destination_string_buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination string buffer.",
		 function );

		memory_free(
		 source_string_buffer );

		libsystem_file_close(
		 &destination_file_handle,
		 NULL );
		libsystem_file_close(
		 &source_file_handle,
		 NULL );

		return( -1 );
	}
	if( export_byte_order_mark != 0 )
	{
		switch( output_format )
		{
			case UNACOMMON_FORMAT_UTF8:
				result = libuna_utf8_stream_copy_byte_order_mark(
				          destination_string_buffer,
				          destination_string_buffer_size,
				          &destination_string_buffer_iterator,
				          error );
				break;

			case UNACOMMON_FORMAT_UTF16BE:
				result = libuna_utf16_stream_copy_byte_order_mark(
				          destination_string_buffer,
				          destination_string_buffer_size,
				          &destination_string_buffer_iterator,
				          LIBUNA_ENDIAN_BIG,
				          error );
				break;

			case UNACOMMON_FORMAT_UTF16LE:
				result = libuna_utf16_stream_copy_byte_order_mark(
				          destination_string_buffer,
				          destination_string_buffer_size,
				          &destination_string_buffer_iterator,
				          LIBUNA_ENDIAN_LITTLE,
				          error );
				break;

			case UNACOMMON_FORMAT_UTF32BE:
				result = libuna_utf32_stream_copy_byte_order_mark(
				          destination_string_buffer,
				          destination_string_buffer_size,
				          &destination_string_buffer_iterator,
				          LIBUNA_ENDIAN_BIG,
				          error );
				break;

			case UNACOMMON_FORMAT_UTF32LE:
				result = libuna_utf32_stream_copy_byte_order_mark(
				          destination_string_buffer,
				          destination_string_buffer_size,
				          &destination_string_buffer_iterator,
				          LIBUNA_ENDIAN_LITTLE,
				          error );
				break;

			default:
				result = 1;
				break;
		}
		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set byte order mark.",
			 function );

			memory_free(
			 destination_string_buffer );
			memory_free(
			 source_string_buffer );

			libsystem_file_close(
			 &destination_file_handle,
			 NULL );
			libsystem_file_close(
			 &source_file_handle,
			 NULL );

			return( -1 );
		}
	}
	while( 1 )
	{
		read_count = libsystem_file_read(
		              source_file_handle,
		              &( source_string_buffer[ source_string_buffer_iterator ] ),
		              source_string_buffer_size - source_string_buffer_iterator,
		              error );

		if( read_count < 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read from source.",
			 function );

			export_count = -1;

			break;
		}
		export_count                 += read_count;
		read_count                   += (ssize_t) source_string_buffer_iterator;
		source_string_buffer_iterator = 0;

		if( read_count == 0 )
		{
			break;
		}
		if( analyze_first_character != 0 )
		{
			if( ( read_count >= 3 )
			 && ( source_string_buffer[ 0 ] == 0xef )
			 && ( source_string_buffer[ 1 ] == 0xbb )
			 && ( source_string_buffer[ 2 ] == 0xbf ) )
			{
				if( input_format == UNACOMMON_FORMAT_AUTO_DETECT )
				{
					input_format = UNACOMMON_FORMAT_UTF8;
				}
				if( input_format == UNACOMMON_FORMAT_UTF8 )
				{
					source_string_buffer_iterator += 3;
				}
			}
			else if( ( read_count >= 2 )
			      && ( source_string_buffer[ 0 ] == 0xfe )
			      && ( source_string_buffer[ 1 ] == 0xff ) )
			{
				if( input_format == UNACOMMON_FORMAT_AUTO_DETECT )
				{
					input_format = UNACOMMON_FORMAT_UTF16BE;
				}
				if( input_format == UNACOMMON_FORMAT_UTF16BE )
				{
					source_string_buffer_iterator += 2;
				}
			}
			else if( ( read_count >= 2 )
			      && ( source_string_buffer[ 0 ] == 0xff )
			      && ( source_string_buffer[ 1 ] == 0xfe ) )
			{
				if( ( read_count >= 4 )
				 && ( source_string_buffer[ 2 ] == 0x00 )
			         && ( source_string_buffer[ 3 ] == 0x00 ) )
				{
					if( input_format == UNACOMMON_FORMAT_AUTO_DETECT )
					{
						input_format = UNACOMMON_FORMAT_UTF32LE;
					}
					if( input_format == UNACOMMON_FORMAT_UTF32LE )
					{
						source_string_buffer_iterator += 4;
					}
				}
				else
				{
					if( input_format == UNACOMMON_FORMAT_AUTO_DETECT )
					{
						input_format = UNACOMMON_FORMAT_UTF16LE;
					}
					if( input_format == UNACOMMON_FORMAT_UTF16LE )
					{
						source_string_buffer_iterator += 2;
					}
				}
			}
			else if( ( read_count >= 4 )
			      && ( source_string_buffer[ 0 ] == 0x00 )
			      && ( source_string_buffer[ 1 ] == 0x00 )
			      && ( source_string_buffer[ 1 ] == 0xfe )
			      && ( source_string_buffer[ 1 ] == 0xff ) )
			{
				if( input_format == UNACOMMON_FORMAT_AUTO_DETECT )
				{
					input_format = UNACOMMON_FORMAT_UTF32BE;
				}
				if( input_format == UNACOMMON_FORMAT_UTF32BE )
				{
					source_string_buffer_iterator += 4;
				}
			}
			else if( input_format == UNACOMMON_FORMAT_AUTO_DETECT )
			{
				input_format = UNACOMMON_FORMAT_BYTE_STREAM;
			}
			read_count -= (ssize_t) source_string_buffer_iterator;

			analyze_first_character = 0;
		}
		last_source_string_buffer_iterator = source_string_buffer_iterator;

		while( read_count > 0 )
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
				case UNACOMMON_FORMAT_BYTE_STREAM:
					result = libuna_unicode_character_copy_from_byte_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  byte_stream_codepage,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF7:
					result = libuna_unicode_character_copy_from_utf7_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  &source_utf7_stream_base64_data,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF8:
					result = libuna_unicode_character_copy_from_utf8(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF16BE:
					result = libuna_unicode_character_copy_from_utf16_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUNA_ENDIAN_BIG,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF16LE:
					result = libuna_unicode_character_copy_from_utf16_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUNA_ENDIAN_LITTLE,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF32BE:
					result = libuna_unicode_character_copy_from_utf32_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUNA_ENDIAN_BIG,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF32LE:
					result = libuna_unicode_character_copy_from_utf32_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUNA_ENDIAN_LITTLE,
					          error );
					break;

				default:
					result = -1;
					break;
			}
			if( result != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_CONVERSION,
				 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
				 "%s: unable to convert input character.",
				 function );

				export_count = -1;

				break;
			}
			amount_of_unicode_characters++;

			read_count -= source_string_buffer_iterator - last_source_string_buffer_iterator;

			last_source_string_buffer_iterator = source_string_buffer_iterator;

			if( newline_conversion != UNACOMMON_NEWLINE_CONVERSION_NONE )
			{
				/* Determine if character is a line feed (LF)
				 */
				if( unicode_character[ unicode_character_iterator ] == 0x000a )
				{
					if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CRLF )
					{
						if( unicode_character_iterator == 0 )
						{
							unicode_character[ unicode_character_iterator     ] = 0x000d;
							unicode_character[ unicode_character_iterator + 1 ] = 0x000a;
			
							amount_of_unicode_characters++;
						}
					}
					else if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CR )
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
					else if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_LF )
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
			for( unicode_character_iterator = 0;
			     unicode_character_iterator < amount_of_unicode_characters;
			     unicode_character_iterator++ )
			{
				switch( output_format )
				{
					case UNACOMMON_FORMAT_BYTE_STREAM:
						result = libuna_unicode_character_copy_to_byte_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  byte_stream_codepage,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF7:
						result = libuna_unicode_character_copy_to_utf7_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  &destination_utf7_stream_base64_data,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF8:
						result = libuna_unicode_character_copy_to_utf8(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF16BE:
						result = libuna_unicode_character_copy_to_utf16_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUNA_ENDIAN_BIG,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF16LE:
						result = libuna_unicode_character_copy_to_utf16_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUNA_ENDIAN_LITTLE,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF32BE:
						result = libuna_unicode_character_copy_to_utf32_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUNA_ENDIAN_BIG,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF32LE:
						result = libuna_unicode_character_copy_to_utf32_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUNA_ENDIAN_LITTLE,
						          error );
						break;

					default:
						result = -1;
						break;
				}
				if( result != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_CONVERSION,
					 LIBERROR_CONVERSION_ERROR_OUTPUT_FAILED,
					 "%s: unable to convert output character.",
					 function );

					export_count = -1;

					break;
				}
			}
			if( export_count <= -1 )
			{
				break;
			}
			amount_of_unicode_characters = 0;
			unicode_character_iterator   = 0;
		}
		if( export_count <= -1 )
		{
			break;
		}
		if( destination_string_buffer_iterator > 0 )
		{
			write_count = libsystem_file_write(
			               destination_file_handle,
			               destination_string_buffer,
		        	       destination_string_buffer_iterator,
			               error );

			if( write_count < 0 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_WRITE_FAILED,
				 "%s: unable to write to destination.",
				 function );

				export_count = -1;

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
		 if( process_status_update_unknown_total(
		      process_status,
		      (size64_t) export_count,
		      error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to update process status.",
			 function );

			memory_free(
			 destination_string_buffer );
			memory_free(
			 source_string_buffer );

			libsystem_file_close(
			 &destination_file_handle,
			 NULL );
			libsystem_file_close(
			 &source_file_handle,
			 NULL );

			return( -1 );
		}
	}
	memory_free(
	 source_string_buffer );
	memory_free(
	 destination_string_buffer );

	if( libsystem_file_close(
	     &source_file_handle,
	     error ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close source: %" PRIs_LIBSYSTEM ".",
		 function,
		 source_filename );

		libsystem_file_close(
		 &destination_file_handle,
		 NULL );

		return( -1 );
	}
	if( libsystem_file_close(
	     &destination_file_handle,
	     error ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close destination: %" PRIs_LIBSYSTEM ".",
		 function,
		 destination_filename );

		return( -1 );
	}
	return( export_count );
}

/* The main program
 */
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	liberror_error_t *error                     = NULL;
	process_status_t *process_status            = NULL;
	libsystem_character_t *destination_filename = NULL;
	libsystem_character_t *program              = _LIBSYSTEM_CHARACTER_T_STRING( "unaexport" );
	libsystem_character_t *source_filename      = NULL;
	ssize64_t export_count                      = 0;
	libsystem_integer_t option                  = 0;
	uint8_t print_status_information            = 1;
	int byte_stream_codepage                    = LIBUNA_CODEPAGE_ASCII;
	int export_byte_order_mark                  = 1;
	int input_format                            = UNACOMMON_FORMAT_AUTO_DETECT;
	int newline_conversion                      = UNACOMMON_NEWLINE_CONVERSION_NONE;
	int output_format                           = UNACOMMON_FORMAT_UTF8;
	int verbose                                 = 0;
	int status                                  = 0;

	libsystem_notify_set_stream(
	 stderr,
	 NULL );
	libsystem_notify_set_verbose(
	 1 );

	if( libsystem_initialize(
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize system values.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	unaoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = libsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBSYSTEM_CHARACTER_T_STRING( "Bc:hi:ln:o:qvV" ) ) ) != (libsystem_integer_t) -1 )
	{
		switch( option )
		{
			case (libsystem_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %s\n",
				 argv[ optind ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (libsystem_integer_t) 'B':
				export_byte_order_mark = 0;

				break;

			case (libsystem_integer_t) 'c':
				if( unainput_determine_byte_stream_codepage(
				     optarg,
				     &byte_stream_codepage,
				     &error ) != 1 )
				{
					libsystem_notify_print_error_backtrace(
					 error );
					liberror_error_free(
					 &error );

					byte_stream_codepage = LIBUNA_CODEPAGE_ASCII;

					fprintf(
					 stderr,
					 "Unsupported byte stream codepage defaulting to: ascii.\n" );
				}
				break;

			case (libsystem_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (libsystem_integer_t) 'i':
				if( libsystem_string_compare(
				 optarg,
				 _LIBSYSTEM_CHARACTER_T_STRING( "auto-detect" ),
				 11 ) == 0 )
				{
					input_format = UNACOMMON_FORMAT_AUTO_DETECT;
				}
				else if( unainput_determine_format(
				          optarg,
				          &input_format,
				          &error ) != 1 )
				{
					libsystem_notify_print_error_backtrace(
					 error );
					liberror_error_free(
					 &error );

					input_format = UNACOMMON_FORMAT_AUTO_DETECT;

					fprintf(
					 stderr,
					 "Unsupported input format defaulting to: auto-detect.\n" );
				}
				break;

			case (libsystem_integer_t) 'l':
				unaoutput_codepages_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (libsystem_integer_t) 'n':
				if( unainput_determine_newline_conversion(
				     optarg,
				     &newline_conversion,
				     &error ) != 1 )
				{
					libsystem_notify_print_error_backtrace(
					 error );
					liberror_error_free(
					 &error );

					newline_conversion = UNACOMMON_NEWLINE_CONVERSION_NONE;

					fprintf(
					 stderr,
					 "Unsupported newline conversion defaulting to: none.\n" );
				}
				break;

			case (libsystem_integer_t) 'o':
				if( unainput_determine_format(
				     optarg,
				     &output_format,
				     &error ) != 1 )
				{
					libsystem_notify_print_error_backtrace(
					 error );
					liberror_error_free(
					 &error );

					output_format = UNACOMMON_FORMAT_UTF8;

					fprintf(
					 stderr,
					 "Unsupported output format defaulting to: utf8.\n" );
				}
				break;

			case (libsystem_integer_t) 'q':
				print_status_information = 0;

				break;

			case (libsystem_integer_t) 'v':
				verbose = 1;

				break;

			case (libsystem_integer_t) 'V':
				unaoutput_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source_filename = argv[ optind++ ];

	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing destination.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	destination_filename = argv[ optind++ ];

	libsystem_notify_set_verbose(
	 verbose );

	export_fprint(
	 stdout,
	 source_filename,
	 input_format,
	 destination_filename,
	 output_format,
	 byte_stream_codepage,
	 export_byte_order_mark,
	 newline_conversion );

	if( process_status_initialize(
	     &process_status,
	     _LIBSYSTEM_CHARACTER_T_STRING( "Export" ),
	     _LIBSYSTEM_CHARACTER_T_STRING( "exported" ),
	     _LIBSYSTEM_CHARACTER_T_STRING( "Exported" ),
	     stdout,
	     print_status_information,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create process status.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	if( process_status_start(
	     process_status,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to start process status.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		process_status_free(
		 &process_status,
		 NULL );

		return( EXIT_FAILURE );
	}
	export_count = unaexport(
	                source_filename,
	                input_format,
	                destination_filename,
	                output_format,
	                byte_stream_codepage,
	                export_byte_order_mark,
	                newline_conversion,
	                process_status,
	                &error );

	if( export_count <= -1 )
	{
		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		status = PROCESS_STATUS_FAILED;
	}
	else
	{
		status = PROCESS_STATUS_COMPLETED;
	}
	if( process_status_stop(
	     process_status,
	     (size64_t) export_count,
	     status,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to stop process status.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		process_status_free(
		 &process_status,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( process_status_free(
	     &process_status,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free process status.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	if( status != PROCESS_STATUS_COMPLETED )
	{
		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}

