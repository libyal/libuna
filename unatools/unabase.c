/*
 * De/Encodes data from/to different base encodings
 *
 * Copyright (c) 2008-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#include <stdio.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <libsystem.h>

#include "unacommon.h"
#include "unainput.h"
#include "unatools_libuna.h"
#include "unaoutput.h"

#define UNABASE_BUFFER_SIZE	8 * 1024 * 1024

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use unabase to de/encode data form/to different base\n"
	                 "encodings\n\n" );

	fprintf( stream, "Usage: unabase [ -m mode ] [ -hvV ] source destination\n\n" );

	fprintf( stream, "\tsource:      the source file\n" );
	fprintf( stream, "\tdestination: the destination file\n\n" );

	fprintf( stream, "\t-m:          export mode, options: decode (default),\n"
	                 "\t             or encode\n" );
	fprintf( stream, "\t-h:          shows this help\n" );
	fprintf( stream, "\t-v:          verbose output to stderr\n" );
	fprintf( stream, "\t-V:          print version\n" );
}

/* Prints the export information
 */
void export_fprint(
      FILE *stream,
      const libcstring_system_character_t *source_filename,
      const libcstring_system_character_t *destination_filename )
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
	 "\n" );

	fprintf(
	 stream,
	 "\tdestination:\t\t%s\n",
	 destination_filename );
	fprintf(
	 stream,
	 "\n" );

	fprintf(
	 stream,
	 "\n" );
}

/* Exports the source file to the destination file
 * Returns the number of bytes of the source processed or -1 on error
 */
ssize64_t unabase(
           const libcstring_system_character_t *source_filename,
           const libcstring_system_character_t *destination_filename,
           liberror_error_t **error )
{
	libuna_unicode_character_t unicode_character[ 2 ];

	uint8_t *destination_string_buffer              = NULL;
	uint8_t *source_string_buffer                   = NULL;
	static char *function                           = "unabase";
	libsystem_file_handle_t destination_file_handle = LIBSYSTEM_FILE_HANDLE_EMPTY;
	libsystem_file_handle_t source_file_handle      = LIBSYSTEM_FILE_HANDLE_EMPTY;
	ssize64_t export_count                          = 0;
	size_t destination_string_buffer_iterator       = 0;
	size_t destination_string_buffer_size           = UNABASE_BUFFER_SIZE;
	size_t source_string_buffer_iterator            = 0;
	size_t realignment_iterator                     = 0;
	size_t source_string_buffer_size                = UNABASE_BUFFER_SIZE;
	ssize_t read_count                              = 0;
	ssize_t write_count                             = 0;
	uint8_t number_of_unicode_characters            = 0;
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
		 "%s: unable to open source: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 source_filename );

		goto on_error;
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
		 "%s: unable to open destination: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 destination_filename );

		goto on_error;
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

		goto on_error;
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

		goto on_error;
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
			/* Write all unicode characters
			 */
			for( unicode_character_iterator = 0;
			     unicode_character_iterator < number_of_unicode_characters;
			     unicode_character_iterator++ )
			{
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
			number_of_unicode_characters = 0;
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

		for( ;
		     read_count > 0;
		     read_count-- )
		{
			source_string_buffer[ source_string_buffer_iterator++ ] = source_string_buffer[ realignment_iterator++ ];
		}
	}
	memory_free(
	 source_string_buffer );

	source_string_buffer = NULL;

	memory_free(
	 destination_string_buffer );

	destination_string_buffer = NULL;

	if( libsystem_file_close(
	     &source_file_handle,
	     error ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close source: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 source_filename );

		goto on_error;
	}
	if( libsystem_file_close(
	     &destination_file_handle,
	     error ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close destination: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 destination_filename );

		goto on_error;
	}
	return( export_count );

on_error:
	if( destination_string_buffer != NULL )
	{
		memory_free(
		 destination_string_buffer );
	}
	if( source_string_buffer != NULL )
	{
		memory_free(
		 source_string_buffer );
	}
	if( destination_file_handle != LIBSYSTEM_FILE_HANDLE_EMPTY )
	{
		libsystem_file_close(
		 &destination_file_handle,
		 NULL );
	}
	if( source_file_handle != LIBSYSTEM_FILE_HANDLE_EMPTY )
	{
		libsystem_file_close(
		 &source_file_handle,
		 NULL );
	}
	return( -1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	liberror_error_t *error                             = NULL;
	libcstring_system_character_t *destination_filename = NULL;
	libcstring_system_character_t *option_mode          = NULL;
	libcstring_system_character_t *source_filename      = NULL;
	char *program                                       = "unabase";
	ssize64_t export_count                              = 0;
	libcstring_system_integer_t option                  = 0;
	int verbose                                         = 0;

	libsystem_notify_set_stream(
	 stderr,
	 NULL );
	libsystem_notify_set_verbose(
	 1 );

	if( libsystem_initialize(
	     "unatools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize system values.\n" );

		goto on_error;
	}
	unaoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = libsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "hm:vV" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				goto on_error;

			case (libcstring_system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (libcstring_system_integer_t) 'm':
				option_mode = optarg;

				break;

			case (libcstring_system_integer_t) 'v':
				verbose = 1;

				break;

			case (libcstring_system_integer_t) 'V':
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
	 destination_filename );

	export_count = unabase(
	                source_filename,
	                destination_filename,
	                &error );

	if( export_count <= -1 )
	{
		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

