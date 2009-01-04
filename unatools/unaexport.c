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
#include <file_io.h>
#include <memory.h>
#include <narrow_string.h>
#include <notify.h>
#include <types.h>

#include <errno.h>

#include <stdio.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

/* If libtool DLL support is enabled set LIBUNA_DLL_IMPORT
 * before including libuna.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBUNA_DLL_IMPORT
#endif

#include <libuna.h>

#include "character_string.h"
#include "glob.h"
#include "process_status.h"
#include "safe_types.h"
#include "system_string.h"

#include "unacommon.h"
#include "unagetopt.h"
#include "unainput.h"
#include "unaoutput.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Usage: unaexport [ -c codepage ] [ -i input_format ] [ -n newline_converion ]\n" );
	fprintf( stream, "       [ -o output_format ] [ -BhlqvV ] source destination\n\n" );

	fprintf( stream, "\tsource:      the source file\n" );
	fprintf( stream, "\tdestination: the destination file\n\n" );

	fprintf( stream, "\t-B:          do not export a byte order mark\n" );
	fprintf( stream, "\t-c:          codepage of byte stream, options: ascii (default),\n" );
	fprintf( stream, "\t             windows-1250, windows-1251, windows-1252, windows-1253,\n" );
	fprintf( stream, "\t             windows-1254, windows-1255, windows-1256, windows-1257\n" );
	fprintf( stream, "\t             or windows-1258\n" );
	fprintf( stream, "\t-h:          shows this help\n" );
	fprintf( stream, "\t-i:          input format, options: auto-detect (default), byte-stream,\n" );
	fprintf( stream, "\t             utf8, utf16be, utf16le, utf32be or utf32le\n" );
	fprintf( stream, "\t-l:          list information about the codepages\n" );
	fprintf( stream, "\t-n:          convert newline characters, options: none (default), cr,\n" );
	fprintf( stream, "\t             crlf or lf\n" );
	fprintf( stream, "\t-o:          output format, options: byte-stream, utf8 (default),\n" );
	fprintf( stream, "\t             utf16be, utf16le, utf32be or utf32le\n" );
	fprintf( stream, "\t-q:          quiet shows no status information\n" );
	fprintf( stream, "\t-v:          verbose output to stderr\n" );
	fprintf( stream, "\t-V:          print version\n" );
}

/* Prints the export information
 */
void export_fprint(
      FILE *stream,
      const system_character_t *source_filename,
      int input_format,
      const system_character_t *destination_filename,
      int output_format,
      int byte_stream_codepage,
      int export_byte_order_mark,
      int newline_conversion )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Exporting:\n" );
	fprintf( stream, "\tsource:\t\t\t%s\n",
	 source_filename );
	fprintf( stream, "\tof format:\t\t" );

	if( input_format == UNACOMMON_FORMAT_BYTE_STREAM )
	{
		fprintf( stream, "auto detect" );
	}
	else if( input_format == UNACOMMON_FORMAT_BYTE_STREAM )
	{
		fprintf( stream, "byte stream" );
	}
	else if( input_format == UNACOMMON_FORMAT_UTF8 )
	{
		fprintf( stream, "UTF-8" );
	}
	else if( input_format == UNACOMMON_FORMAT_UTF16BE )
	{
		fprintf( stream, "UTF-16 big endian" );
	}
	else if( input_format == UNACOMMON_FORMAT_UTF16LE )
	{
		fprintf( stream, "UTF-16 little endian" );
	}
	else if( input_format == UNACOMMON_FORMAT_UTF32BE )
	{
		fprintf( stream, "UTF-32 big endian" );
	}
	else if( input_format == UNACOMMON_FORMAT_UTF32LE )
	{
		fprintf( stream, "UTF-32 little endian" );
	}
	else
	{
		fprintf( stream, "unsupported" );
	}
	fprintf( stream, "\n" );

	fprintf( stream, "\tdestination:\t\t%s\n",
	 destination_filename );
	fprintf( stream, "\tof format:\t\t" );

	if( output_format == UNACOMMON_FORMAT_BYTE_STREAM )
	{
		fprintf( stream, "byte stream" );
	}
	else if( output_format == UNACOMMON_FORMAT_UTF8 )
	{
		fprintf( stream, "UTF-8" );
	}
	else if( output_format == UNACOMMON_FORMAT_UTF16BE )
	{
		fprintf( stream, "UTF-16 big endian" );
	}
	else if( output_format == UNACOMMON_FORMAT_UTF16LE )
	{
		fprintf( stream, "UTF-16 little endian" );
	}
	else if( output_format == UNACOMMON_FORMAT_UTF32BE )
	{
		fprintf( stream, "UTF-32 big endian" );
	}
	else if( output_format == UNACOMMON_FORMAT_UTF32LE )
	{
		fprintf( stream, "UTF-32 little endian" );
	}
	else
	{
		fprintf( stream, "unsupported" );
	}
	fprintf( stream, "\n" );

	/* TODO print codepage
	 */

	fprintf( stream, "\texport byte order mark:\t" );

	if( export_byte_order_mark == 0 )
	{
		fprintf( stream, "no" );
	}
	else
	{
		fprintf( stream, "yes" );
	}
	fprintf( stream, "\n" );

	fprintf( stream, "\tnewline conversion:\t" );
	
	if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_NONE )
	{
		fprintf( stream, "none" );
	}
	else if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CRLF )
	{
		fprintf( stream, "carriage return and line feed (crlf)" );
	}
	else if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CR )
	{
		fprintf( stream, "carriage return (cr)" );
	}
	else if( newline_conversion == UNACOMMON_NEWLINE_CONVERSION_LF )
	{
		fprintf( stream, "line feed (lf)" );
	}
	else
	{
		fprintf( stream, "unsupported" );
	}
	fprintf( stream, "\n" );

	fprintf( stream, "\n" );
}

/* Exports the source file to the destination file
 * Returns the amount of bytes of the source processed or -1 on error
 */
ssize64_t unaexport(
           const system_character_t *source_filename,
           int input_format,
           const system_character_t *destination_filename,
           int output_format,
           int byte_stream_codepage,
           int export_byte_order_mark,
           int newline_conversion,
           void (*callback)( process_status_t *process_status, size64_t bytes_read, size64_t bytes_total ) )
{
	libuna_unicode_character_t unicode_character[ 2 ];

	libuna_error_t *error                     = NULL;
	uint8_t *destination_string_buffer        = NULL;
	uint8_t *source_string_buffer             = NULL;
	static char *function                     = "unaexport";
	ssize64_t export_count                    = 0;
	size_t destination_string_buffer_iterator = 0;
	size_t destination_string_buffer_size     = 8 * 1024 * 1024;
	size_t source_string_buffer_iterator      = 0;
	size_t realignment_iterator               = 0;
	size_t source_string_buffer_size          = 8 * 1024 * 1024;
	ssize_t read_count                        = 0;
	ssize_t write_count                       = 0;
	int destination_file_descriptor           = 0;
	int result                                = 1;
	int source_file_descriptor                = 0;
	uint8_t amount_of_unicode_characters      = 0;
	uint8_t analyze_first_character           = 1;
	uint8_t unicode_character_iterator        = 0;

	if( source_filename == NULL )
	{
		notify_warning_printf( "%s: invalid source filename.\n",
		 function );

		return( -1 );
	}
	if( destination_filename == NULL )
	{
		notify_warning_printf( "%s: invalid destination filename.\n",
		 function );

		return( -1 );
	}
	if( ( input_format != UNACOMMON_FORMAT_AUTO_DETECT )
	 && ( input_format != UNACOMMON_FORMAT_BYTE_STREAM )
	 && ( input_format != UNACOMMON_FORMAT_UTF8 )
	 && ( input_format != UNACOMMON_FORMAT_UTF16BE )
	 && ( input_format != UNACOMMON_FORMAT_UTF16LE )
	 && ( input_format != UNACOMMON_FORMAT_UTF32BE )
	 && ( input_format != UNACOMMON_FORMAT_UTF32LE ) )
	{
		notify_warning_printf( "%s: unsupported input format.\n",
		 function );

		return( -1 );
	}
	if( ( output_format != UNACOMMON_FORMAT_BYTE_STREAM )
	 && ( output_format != UNACOMMON_FORMAT_UTF8 )
	 && ( output_format != UNACOMMON_FORMAT_UTF16BE )
	 && ( output_format != UNACOMMON_FORMAT_UTF16LE )
	 && ( output_format != UNACOMMON_FORMAT_UTF32BE )
	 && ( output_format != UNACOMMON_FORMAT_UTF32LE ) )
	{
		notify_warning_printf( "%s: unsupported output format.\n",
		 function );

		return( -1 );
	}
	if( ( newline_conversion != UNACOMMON_NEWLINE_CONVERSION_NONE )
	 && ( newline_conversion != UNACOMMON_NEWLINE_CONVERSION_CRLF )
	 && ( newline_conversion != UNACOMMON_NEWLINE_CONVERSION_CR )
	 && ( newline_conversion != UNACOMMON_NEWLINE_CONVERSION_LF ) )
	{
		notify_warning_printf( "%s: unsupported newline conversion.\n",
		 function );

		return( -1 );
	}
	source_file_descriptor = unacommon_open(
	                          source_filename,
	                          FILE_IO_O_RDONLY );

	if( source_file_descriptor == -1 )
	{
		notify_warning_printf( "%s: unable to open source: %" PRIs_SYSTEM ".\n",
		 function, source_filename );

		return( -1 );
	}
	destination_file_descriptor = unacommon_open(
	                               destination_filename,
	                               ( FILE_IO_O_WRONLY | FILE_IO_O_CREAT | FILE_IO_O_TRUNC ) );

	if( destination_file_descriptor == -1 )
	{
		notify_warning_printf( "%s: unable to open destination: %" PRIs_SYSTEM ".\n",
		 function, destination_filename );

		file_io_close(
		 source_file_descriptor );

		return( -1 );
	}
	source_string_buffer = (uint8_t *) memory_allocate(
	                                    sizeof( uint8_t ) * source_string_buffer_size );

	if( source_string_buffer == NULL )
	{
		notify_warning_printf( "%s: unable to create source string buffer.\n",
		 function );

		file_io_close(
		 source_file_descriptor );
		file_io_close(
		 destination_file_descriptor );

		return( -1 );
	}
	destination_string_buffer = (uint8_t *) memory_allocate(
	                                         sizeof( uint8_t ) * destination_string_buffer_size );

	if( destination_string_buffer == NULL )
	{
		notify_warning_printf( "%s: unable to create destination string buffer.\n",
		 function );

		file_io_close(
		 source_file_descriptor );
		file_io_close(
		 destination_file_descriptor );

		memory_free(
		 source_string_buffer );

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
				          &error );
				break;

			case UNACOMMON_FORMAT_UTF16BE:
				result = libuna_utf16_stream_copy_byte_order_mark(
				          destination_string_buffer,
				          destination_string_buffer_size,
				          &destination_string_buffer_iterator,
				          LIBUNA_ENDIAN_BIG,
				          &error );
				break;

			case UNACOMMON_FORMAT_UTF16LE:
				result = libuna_utf16_stream_copy_byte_order_mark(
				          destination_string_buffer,
				          destination_string_buffer_size,
				          &destination_string_buffer_iterator,
				          LIBUNA_ENDIAN_LITTLE,
				          &error );
				break;

			case UNACOMMON_FORMAT_UTF32BE:
				result = libuna_utf32_stream_copy_byte_order_mark(
				          destination_string_buffer,
				          destination_string_buffer_size,
				          &destination_string_buffer_iterator,
				          LIBUNA_ENDIAN_BIG,
				          &error );
				break;

			case UNACOMMON_FORMAT_UTF32LE:
				result = libuna_utf32_stream_copy_byte_order_mark(
				          destination_string_buffer,
				          destination_string_buffer_size,
				          &destination_string_buffer_iterator,
				          LIBUNA_ENDIAN_LITTLE,
				          &error );
				break;

			default:
				result = 1;
				break;
		}
		if( result != 1 )
		{
			notify_warning_printf( "%s: unable to set byte order mark.\n",
			 function );

			libuna_error_backtrace_fprint(
			 error,
			 stderr );
			libuna_error_free(
			 &error );

			file_io_close(
			 source_file_descriptor );
			file_io_close(
			 destination_file_descriptor );

			memory_free(
			 source_string_buffer );
			memory_free(
			 destination_string_buffer );

			return( -1 );
		}
		if( error != NULL )
		{
			notify_warning_printf( "%s: error was set but return code was: %d.\n",
			 function, result );

			libuna_error_backtrace_fprint(
			 error,
			 stderr );
			libuna_error_free(
			 &error );
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
			notify_warning_printf( "%s: unable to read from source.\n",
			 function );

			export_count = -1;

			break;
		}
		export_count                  += read_count;
		read_count                    += (ssize_t) source_string_buffer_iterator;
		source_string_buffer_iterator  = 0;

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
				case UNACOMMON_FORMAT_BYTE_STREAM:
					result = libuna_unicode_character_copy_from_byte_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  byte_stream_codepage,
					          &error );
					break;

				case UNACOMMON_FORMAT_UTF8:
					result = libuna_unicode_character_copy_from_utf8(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
					          &error );
					break;

				case UNACOMMON_FORMAT_UTF16BE:
					result = libuna_unicode_character_copy_from_utf16_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUNA_ENDIAN_BIG,
					          &error );
					break;

				case UNACOMMON_FORMAT_UTF16LE:
					result = libuna_unicode_character_copy_from_utf16_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUNA_ENDIAN_LITTLE,
					          &error );
					break;

				case UNACOMMON_FORMAT_UTF32BE:
					result = libuna_unicode_character_copy_from_utf32_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUNA_ENDIAN_BIG,
					          &error );
					break;

				case UNACOMMON_FORMAT_UTF32LE:
					result = libuna_unicode_character_copy_from_utf32_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  LIBUNA_ENDIAN_LITTLE,
					          &error );
					break;

				default:
					result = -1;
					break;
			}
			if( result != 1 )
			{
				notify_warning_printf( "%s: unable to convert input character.\n",
				 function );

				libuna_error_backtrace_fprint(
				 error,
				 stderr );
				libuna_error_free(
				 &error );

				export_count = -1;

				break;
			}
			if( error != NULL )
			{
				notify_warning_printf( "%s: error was set but return code was: %d.\n",
				 function, result );

				libuna_error_backtrace_fprint(
				 error,
				 stderr );
				libuna_error_free(
				 &error );
			}
			amount_of_unicode_characters++;

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
			for( unicode_character_iterator = 0; unicode_character_iterator < amount_of_unicode_characters; unicode_character_iterator++ )
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
						          &error );
						break;

					case UNACOMMON_FORMAT_UTF8:
						result = libuna_unicode_character_copy_to_utf8(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
						          &error );
						break;

					case UNACOMMON_FORMAT_UTF16BE:
						result = libuna_unicode_character_copy_to_utf16_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUNA_ENDIAN_BIG,
						          &error );
						break;

					case UNACOMMON_FORMAT_UTF16LE:
						result = libuna_unicode_character_copy_to_utf16_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUNA_ENDIAN_LITTLE,
						          &error );
						break;

					case UNACOMMON_FORMAT_UTF32BE:
						result = libuna_unicode_character_copy_to_utf32_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUNA_ENDIAN_BIG,
						          &error );
						break;

					case UNACOMMON_FORMAT_UTF32LE:
						result = libuna_unicode_character_copy_to_utf32_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  LIBUNA_ENDIAN_LITTLE,
						          &error );
						break;

					default:
						result = -1;
						break;
				}
				if( result != 1 )
				{
					notify_warning_printf( "%s: unable to convert output character.\n",
					 function );

					libuna_error_backtrace_fprint(
					 error,
					 stderr );
					libuna_error_free(
					 &error );

					export_count = -1;

					break;
				}
			}
			if( error != NULL )
			{
				notify_warning_printf( "%s: error was set but return code was: %d.\n",
				 function, result );

				libuna_error_backtrace_fprint(
				 error,
				 stderr );
				libuna_error_free(
				 &error );
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
			write_count = file_io_write(
			               destination_file_descriptor,
			               destination_string_buffer,
		        	       destination_string_buffer_iterator );

			if( write_count < 0 )
			{
				notify_warning_printf( "%s: unable to write to destination.\n",
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
		/* Provide for a process status update
		 */
		if( callback != NULL )
		{
			callback(
			 process_status,
			 (size64_t) export_count,
			 0 );
		}
	}
	memory_free(
	 source_string_buffer );
	memory_free(
	 destination_string_buffer );

	if( file_io_close(
	     source_file_descriptor ) != 0 )
	{
		notify_warning_printf( "%s: unable to close source: %" PRIs_SYSTEM ".\n",
		 function, source_filename );

		file_io_close(
		 destination_file_descriptor );

		return( -1 );
	}
	if( file_io_close(
	     destination_file_descriptor ) != 0 )
	{
		notify_warning_printf( "%s: unable to close destination: %" PRIs_SYSTEM ".\n",
		 function, destination_filename );

		return( -1 );
	}
	return( export_count );
}

/* The main program
 */
#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	character_t *program                     = _CHARACTER_T_STRING( "unaexport" );
	system_character_t *destination_filename = NULL;
	system_character_t *source_filename      = NULL;
	void *callback                           = &process_status_update_unknown_total;
	ssize64_t export_count                   = 0;
	system_integer_t option                  = 0;
	int byte_stream_codepage                 = LIBUNA_CODEPAGE_ASCII;
	int export_byte_order_mark               = 1;
	int input_format                         = UNACOMMON_FORMAT_AUTO_DETECT;
	int newline_conversion                   = UNACOMMON_NEWLINE_CONVERSION_NONE;
	int output_format                        = UNACOMMON_FORMAT_UTF8;
	int verbose                              = 0;
	int status                               = 0;

	unaoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = unagetopt(
	                   argc,
	                   argv,
	                   _SYSTEM_CHARACTER_T_STRING( "Bc:hi:ln:o:qvV" ) ) ) != (system_integer_t) -1 )
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
				if( unainput_determine_byte_stream_codepage(
				     optarg,
				     &byte_stream_codepage ) != 1 )
				{
					fprintf( stderr, "Unsupported byte stream codepage defaulting to: ascii.\n" );

					byte_stream_codepage = LIBUNA_CODEPAGE_ASCII;
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
					input_format = UNACOMMON_FORMAT_AUTO_DETECT;
				}
				else if( unainput_determine_format(
				          optarg,
				          &input_format ) != 1 )
				{
					fprintf( stderr, "Unsupported input format defaulting to: auto-detect.\n" );

					input_format = UNACOMMON_FORMAT_AUTO_DETECT;
				}
				break;

			case (system_integer_t) 'l':
				unaoutput_codepages_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'n':
				if( unainput_determine_newline_conversion(
				     optarg,
				     &newline_conversion ) != 1 )
				{
					fprintf( stderr, "Unsupported newline conversion defaulting to: none.\n" );

					newline_conversion = UNACOMMON_NEWLINE_CONVERSION_NONE;
				}
				break;

			case (system_integer_t) 'o':
				if( unainput_determine_format(
				     optarg,
				     &output_format ) != 1 )
				{
					fprintf( stderr, "Unsupported output format defaulting to: utf8.\n" );

					output_format = UNACOMMON_FORMAT_UTF8;
				}
				break;

			case (system_integer_t) 'q':
				callback = NULL;

				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				unaoutput_copyright_fprint(
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
	source_filename = argv[ optind++ ];

	if( optind == argc )
	{
		fprintf( stderr, "Missing destination.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	destination_filename = argv[ optind++ ];

	notify_set_values(
	 stderr,
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
	     _CHARACTER_T_STRING( "Export" ),
	     _CHARACTER_T_STRING( "exported" ),
	     _CHARACTER_T_STRING( "Exported" ),
	     stdout ) != 1 )
	{
		fprintf( stderr, "Unable to create process status.\n" );

		return( EXIT_FAILURE );
	}
	if( process_status_start(
	     process_status ) != 1 )
	{
		fprintf( stderr, "Unable to start process status.\n" );

		process_status_free(
		 &process_status );

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
	                callback );

	if( export_count <= -1 )
	{
		status = PROCESS_STATUS_FAILED;
	}
	else
	{
		status = PROCESS_STATUS_COMPLETED;
	}
	if( process_status_stop(
	     process_status,
	     (size64_t) export_count,
	     status ) != 1 )
	{
		fprintf( stderr, "Unable to stop process status.\n" );

		process_status_free(
		 &process_status );

		return( EXIT_FAILURE );
	}
	if( process_status_free(
	     &process_status ) != 1 )
	{
		fprintf( stderr, "Unable to free process status.\n" );

		return( EXIT_FAILURE );
	}
	if( status != PROCESS_STATUS_COMPLETED )
	{
		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}

