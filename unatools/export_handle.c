/* 
 * Export handle
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

#include <libsystem.h>

#include "export_handle.h"
#include "process_status.h"
#include "unacommon.h"
#include "unainput.h"
#include "unaoutput.h"
#include "unatools_libuna.h"

#define EXPORT_HANDLE_BUFFER_SIZE		8 * 1024 * 1024
#define EXPORT_HANDLE_STRING_SIZE		1024
#define EXPORT_HANDLE_NOTIFY_STREAM		stderr

/* Initializes the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_initialize(
     export_handle_t **export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_initialize";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid export handle value already set.",
		 function );

		return( -1 );
	}
	*export_handle = memory_allocate_structure(
	                  export_handle_t );

	if( *export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create export handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *export_handle,
	     0,
	     sizeof( export_handle_t ) ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear export handle.",
		 function );

		memory_free(
		 *export_handle );

		*export_handle = NULL;

		return( -1 );
	}
	( *export_handle )->source_file_handle      = LIBSYSTEM_FILE_HANDLE_EMPTY;
	( *export_handle )->destination_file_handle = LIBSYSTEM_FILE_HANDLE_EMPTY;
	( *export_handle )->input_format            = UNACOMMON_FORMAT_AUTO_DETECT;
	( *export_handle )->output_format           = UNACOMMON_FORMAT_UTF8;
	( *export_handle )->newline_conversion      = UNACOMMON_NEWLINE_CONVERSION_NONE;
	( *export_handle )->export_byte_order_mark  = 1;
	( *export_handle )->byte_stream_codepage    = LIBUNA_CODEPAGE_ASCII;
	( *export_handle )->notify_stream           = EXPORT_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *export_handle != NULL )
	{
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( -1 );
}

/* Frees the export handle and its elements
 * Returns 1 if successful or -1 on error
 */
int export_handle_free(
     export_handle_t **export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_free";
	int result            = 1;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( result );
}

/* Signals the export handle to abort
 * Returns 1 if successful or -1 on error
 */
int export_handle_signal_abort(
     export_handle_t *export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_signal_abort";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	export_handle->abort = 1;

	return( 1 );
}

/* Opens the input of the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_open_input(
     export_handle_t *export_handle,
     const libcstring_system_character_t *filename,
     liberror_error_t **error )
{
	static char *function = "export_handle_open_input";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( libsystem_file_open(
	     &( export_handle->source_file_handle ),
	     filename,
	     LIBSYSTEM_FILE_OPEN_READ,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open source file: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 filename );

		return( -1 );
	}
	return( 1 );
}

/* Opens the output of the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_open_output(
     export_handle_t *export_handle,
     const libcstring_system_character_t *filename,
     liberror_error_t **error )
{
	static char *function = "export_handle_open_output";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( libsystem_file_open(
	     &( export_handle->destination_file_handle ),
	     filename,
	     LIBSYSTEM_FILE_OPEN_WRITE_TRUNCATE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open destination file: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 filename );

		return( -1 );
	}
	return( 1 );
}

/* Closes the export handle
 * Returns the 0 if succesful or -1 on error
 */
int export_handle_close(
     export_handle_t *export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_close";
	int result            = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( libsystem_file_close(
	     &( export_handle->source_file_handle ),
	     error ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close source file handle.",
		 function );

		result = -1;
	}
	if( libsystem_file_close(
	     &( export_handle->destination_file_handle ),
	     error ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close destination file handle.",
		 function );

		result = -1;
	}
	return( result );
}

/* Sets a string
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_string(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     libcstring_system_character_t **internal_string,
     size_t *internal_string_size,
     liberror_error_t **error )
{
	static char *function = "export_handle_set_string";
	size_t string_length  = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( internal_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal string.",
		 function );

		return( -1 );
	}
	if( internal_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal string size.",
		 function );

		return( -1 );
	}
	if( *internal_string != NULL )
	{
		memory_free(
		 *internal_string );

		*internal_string      = NULL;
		*internal_string_size = 0;
	}
	string_length = libcstring_system_string_length(
	                 string );

	if( string_length > 0 )
	{
		*internal_string = libcstring_system_string_allocate(
		                    string_length + 1 );

		if( *internal_string == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create internal string.",
			 function );

			goto on_error;
		}
		if( libcstring_system_string_copy(
		     *internal_string,
		     string,
		     string_length ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy string.",
			 function );

			goto on_error;
		}
		( *internal_string )[ string_length ] = 0;

		*internal_string_size = string_length + 1;
	}
	return( 1 );

on_error:
	if( *internal_string != NULL )
	{
		memory_free(
		 *internal_string );

		*internal_string = NULL;
	}
	*internal_string_size = 0;

	return( -1 );
}

/* Sets the input format
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int export_handle_set_input_format(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error )
{
	static char *function = "export_handle_set_input_format";
	size_t string_length  = 0;
	int result            = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	string_length = libcstring_system_string_length(
	                 string );

	if( string_length == 11 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "auto-detect" ),
		     11 ) == 0 )
		{
			export_handle->input_format = UNACOMMON_FORMAT_AUTO_DETECT;
			result                      = 1;
		}
	}
	if( result == 0 )
	{
		result = unainput_determine_format(
		          string,
		          &( export_handle->input_format ),
		          error );

		if( result == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine input format.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Sets the output format
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int export_handle_set_output_format(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error )
{
	static char *function = "export_handle_set_output_format";
	int result            = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	result = unainput_determine_format(
		  string,
		  &( export_handle->output_format ),
		  error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine output format.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Sets the newline conversion
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int export_handle_set_newline_conversion(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error )
{
	static char *function = "export_handle_set_output_format";
	int result            = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	result = unainput_determine_newline_conversion(
		  string,
		  &( export_handle->newline_conversion ),
		  error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine newline conversion.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Sets the byte stream codepage
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_byte_stream_codepage(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error )
{
	static char *function = "export_handle_set_byte_stream_codepage";
	int result            = 0;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	result = unainput_determine_byte_stream_codepage(
	          string,
	          &export_handle->byte_stream_codepage,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine byte stream codepage.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Exports the source file to the destination file
 * Returns the number of bytes of the source processed or -1 on error
 */
int export_handle_export_input(
     export_handle_t *export_handle,
     uint8_t print_status_information,
     liberror_error_t **error )
{
	libuna_unicode_character_t unicode_character[ 2 ];

	process_status_t *process_status                = NULL;
	uint8_t *destination_string_buffer              = NULL;
	uint8_t *source_string_buffer                   = NULL;
	static char *function                           = "unaexport";
	ssize64_t export_count                          = 0;
	size_t destination_string_buffer_iterator       = 0;
	size_t destination_string_buffer_size           = EXPORT_HANDLE_BUFFER_SIZE;
	size_t last_source_string_buffer_iterator       = 0;
	size_t source_string_buffer_iterator            = 0;
	size_t realignment_iterator                     = 0;
	size_t source_string_buffer_size                = EXPORT_HANDLE_BUFFER_SIZE;
	ssize_t read_count                              = 0;
	ssize_t write_count                             = 0;
	uint32_t destination_utf7_stream_base64_data    = 0;
	uint32_t source_utf7_stream_base64_data         = 0;
	uint8_t analyze_first_character                 = 1;
	uint8_t number_of_unicode_characters            = 0;
	uint8_t unicode_character_iterator              = 0;
	int result                                      = 1;

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_handle->source_file_handle == LIBSYSTEM_FILE_HANDLE_EMPTY )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid export handle - missing source file handle.",
		 function );

		return( -1 );
	}
	if( export_handle->destination_file_handle == LIBSYSTEM_FILE_HANDLE_EMPTY )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid export handle - missing destination file handle.",
		 function );

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
	if( process_status_initialize(
	     &process_status,
	     _LIBCSTRING_SYSTEM_STRING( "Export" ),
	     _LIBCSTRING_SYSTEM_STRING( "exported" ),
	     _LIBCSTRING_SYSTEM_STRING( "Exported" ),
	     stdout,
	     print_status_information,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create process status.",
		 function );

		goto on_error;
	}
	if( process_status_start(
	     process_status,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to start process status.",
		 function );

		goto on_error;
	}
	if( export_handle->export_byte_order_mark != 0 )
	{
		switch( export_handle->output_format )
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

			goto on_error;
		}
	}
	while( 1 )
	{
		read_count = libsystem_file_read(
		              export_handle->source_file_handle,
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
				if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
				{
					export_handle->input_format = UNACOMMON_FORMAT_UTF8;
				}
				if( export_handle->input_format == UNACOMMON_FORMAT_UTF8 )
				{
					source_string_buffer_iterator += 3;
				}
			}
			else if( ( read_count >= 2 )
			      && ( source_string_buffer[ 0 ] == 0xfe )
			      && ( source_string_buffer[ 1 ] == 0xff ) )
			{
				if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
				{
					export_handle->input_format = UNACOMMON_FORMAT_UTF16BE;
				}
				if( export_handle->input_format == UNACOMMON_FORMAT_UTF16BE )
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
					if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
					{
						export_handle->input_format = UNACOMMON_FORMAT_UTF32LE;
					}
					if( export_handle->input_format == UNACOMMON_FORMAT_UTF32LE )
					{
						source_string_buffer_iterator += 4;
					}
				}
				else
				{
					if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
					{
						export_handle->input_format = UNACOMMON_FORMAT_UTF16LE;
					}
					if( export_handle->input_format == UNACOMMON_FORMAT_UTF16LE )
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
				if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
				{
					export_handle->input_format = UNACOMMON_FORMAT_UTF32BE;
				}
				if( export_handle->input_format == UNACOMMON_FORMAT_UTF32BE )
				{
					source_string_buffer_iterator += 4;
				}
			}
			else if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
			{
				export_handle->input_format = UNACOMMON_FORMAT_BYTE_STREAM;
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
			switch( export_handle->input_format )
			{
				case UNACOMMON_FORMAT_BYTE_STREAM:
					result = libuna_unicode_character_copy_from_byte_stream(
						  &unicode_character[ unicode_character_iterator ],
						  source_string_buffer,
						  source_string_buffer_size,
						  &source_string_buffer_iterator,
						  export_handle->byte_stream_codepage,
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
			number_of_unicode_characters++;

			read_count -= source_string_buffer_iterator - last_source_string_buffer_iterator;

			last_source_string_buffer_iterator = source_string_buffer_iterator;

			if( export_handle->newline_conversion != UNACOMMON_NEWLINE_CONVERSION_NONE )
			{
				/* Determine if character is a line feed (LF)
				 */
				if( unicode_character[ unicode_character_iterator ] == 0x000a )
				{
					if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CRLF )
					{
						if( unicode_character_iterator == 0 )
						{
							unicode_character[ unicode_character_iterator     ] = 0x000d;
							unicode_character[ unicode_character_iterator + 1 ] = 0x000a;
			
							number_of_unicode_characters++;
						}
					}
					else if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CR )
					{
						if( unicode_character_iterator == 0 )
						{
							unicode_character[ unicode_character_iterator ] = 0x000d;
						}
						else if( unicode_character_iterator == 1 )
						{
							unicode_character[ unicode_character_iterator - 1 ] = 0x000d;

							number_of_unicode_characters--;
						}
					}
					else if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_LF )
					{
						if( unicode_character_iterator == 1 )
						{
							unicode_character[ unicode_character_iterator - 1 ] = 0x000a;

							number_of_unicode_characters--;
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
			     unicode_character_iterator < number_of_unicode_characters;
			     unicode_character_iterator++ )
			{
				switch( export_handle->output_format )
				{
					case UNACOMMON_FORMAT_BYTE_STREAM:
						result = libuna_unicode_character_copy_to_byte_stream(
							  unicode_character[ unicode_character_iterator ],
							  destination_string_buffer,
							  destination_string_buffer_size,
							  &destination_string_buffer_iterator,
							  export_handle->byte_stream_codepage,
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
			               export_handle->destination_file_handle,
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

			goto on_error;
		}
	}
	if( process_status_stop(
	     process_status,
	     (size64_t) export_count,
	     PROCESS_STATUS_COMPLETED,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to stop process status.",
		 function );

		goto on_error;
	}
	if( process_status_free(
	     &process_status,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free process status.",
		 function );

		goto on_error;
	}
	memory_free(
	 source_string_buffer );

	source_string_buffer = NULL;

	memory_free(
	 destination_string_buffer );

	destination_string_buffer = NULL;

	return( export_count );

on_error:
	if( process_status != NULL )
	{
		process_status_stop(
		 process_status,
		 (size64_t) export_count,
		 PROCESS_STATUS_FAILED,
		 NULL );
		process_status_free(
		 &process_status,
		 NULL );
	}
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
	return( -1 );
}

/* Prints an overview of the parameters
 * Returns 1 if successful or -1 on error
 */
int export_handle_print_parameters(
     export_handle_t *export_handle,
     liberror_error_t **error )
{
	static char *function = "export_handle_print_parameters";

	if( export_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_handle->notify_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid export handle - missing notify stream.",
		 function );

		return( -1 );
	}
	if( export_handle->source_filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid export handle - missing source filename.",
		 function );

		return( -1 );
	}
	if( export_handle->destination_filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid export handle - missing destination filename.",
		 function );

		return( -1 );
	}
	fprintf(
	 export_handle->notify_stream,
	 "Exporting:\n" );

	fprintf(
	 export_handle->notify_stream,
	 "\tsource:\t\t\t%" PRIs_LIBCSTRING_SYSTEM "\n",
	 export_handle->source_filename );

	fprintf(
	 export_handle->notify_stream,
	 "\tof format:\t\t" );

	unaoutput_format_fprint(
	 export_handle->notify_stream,
	 export_handle->input_format );

	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	fprintf(
	 export_handle->notify_stream,
	 "\tdestination:\t\t%" PRIs_LIBCSTRING_SYSTEM "\n",
	 export_handle->destination_filename );

	fprintf(
	 export_handle->notify_stream,
	 "\tof format:\t\t" );

	unaoutput_format_fprint(
	 export_handle->notify_stream,
	 export_handle->output_format );

	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	fprintf(
	 export_handle->notify_stream,
	 "\tbyte-stream codepage:\t" );

	unaoutput_codepage_fprint(
	 export_handle->notify_stream,
	 export_handle->byte_stream_codepage );

	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	fprintf(
	 export_handle->notify_stream,
	 "\texport byte order mark:\t" );

	if( export_handle->export_byte_order_mark == 0 )
	{
		fprintf(
		 export_handle->notify_stream,
		 "no" );
	}
	else
	{
		fprintf(
		 export_handle->notify_stream,
		 "yes" );
	}
	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	fprintf(
	 export_handle->notify_stream,
	 "\tnewline conversion:\t" );
	
	if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_NONE )
	{
		fprintf(
		 export_handle->notify_stream,
		 "none" );
	}
	else if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CRLF )
	{
		fprintf(
		 export_handle->notify_stream,
		 "carriage return and line feed (crlf)" );
	}
	else if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CR )
	{
		fprintf(
		 export_handle->notify_stream,
		 "carriage return (cr)" );
	}
	else if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_LF )
	{
		fprintf(
		 export_handle->notify_stream,
		 "line feed (lf)" );
	}
	else
	{
		fprintf(
		 export_handle->notify_stream,
		 "unsupported" );
	}
	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	return( 1 );
}

