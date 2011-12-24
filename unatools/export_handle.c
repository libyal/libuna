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
     uint8_t mode,
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
	if( ( mode != EXPORT_HANDLE_MODE_BASE_ENCODING )
	 && ( mode != EXPORT_HANDLE_MODE_TEXT_ENCODING ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported mode.",
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
	( *export_handle )->mode                    = mode;
	( *export_handle )->source_file_handle      = LIBSYSTEM_FILE_HANDLE_EMPTY;
	( *export_handle )->destination_file_handle = LIBSYSTEM_FILE_HANDLE_EMPTY;

	if( mode == EXPORT_HANDLE_MODE_BASE_ENCODING )
	{
		( *export_handle )->encoding      = UNACOMMON_ENCODING_BASE64;
		( *export_handle )->encoding_mode = UNACOMMON_ENCODING_MODE_ENCODE;
	}
	else if( mode == EXPORT_HANDLE_MODE_TEXT_ENCODING )
	{
		( *export_handle )->input_format           = UNACOMMON_FORMAT_AUTO_DETECT;
		( *export_handle )->output_format          = UNACOMMON_FORMAT_UTF8;
		( *export_handle )->newline_conversion     = UNACOMMON_NEWLINE_CONVERSION_NONE;
		( *export_handle )->export_byte_order_mark = 1;
		( *export_handle )->byte_stream_codepage   = LIBUNA_CODEPAGE_ASCII;
	}
	( *export_handle )->notify_stream = EXPORT_HANDLE_NOTIFY_STREAM;

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
		if( ( *export_handle )->source_filename != NULL )
		{
			memory_free(
			 ( *export_handle )->source_filename );
		}
		if( ( *export_handle )->destination_filename != NULL )
		{
			memory_free(
			 ( *export_handle )->destination_filename );
		}
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
	if( libsystem_file_open(
	     &( export_handle->source_file_handle ),
	     export_handle->source_filename,
	     LIBSYSTEM_FILE_OPEN_READ,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open source file: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 export_handle->source_filename );

		return( -1 );
	}
	return( 1 );
}

/* Opens the output of the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_open_output(
     export_handle_t *export_handle,
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
	if( libsystem_file_open(
	     &( export_handle->destination_file_handle ),
	     export_handle->destination_filename,
	     LIBSYSTEM_FILE_OPEN_WRITE_TRUNCATE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open destination file: %" PRIs_LIBCSTRING_SYSTEM ".",
		 function,
		 export_handle->destination_filename );

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

/* Sets the encoding
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int export_handle_set_encoding(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error )
{
	static char *function = "export_handle_set_encoding";
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
	if( export_handle->mode != EXPORT_HANDLE_MODE_BASE_ENCODING )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported mode.",
		 function );

		return( -1 );
	}
	result = unainput_determine_encoding(
		  string,
		  &( export_handle->encoding ),
		  error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine encoding.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Sets the encoding mode
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int export_handle_set_encoding_mode(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error )
{
	static char *function = "export_handle_set_encoding_mode";
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
	if( export_handle->mode != EXPORT_HANDLE_MODE_BASE_ENCODING )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported mode.",
		 function );

		return( -1 );
	}
	result = unainput_determine_encoding_mode(
		  string,
		  &( export_handle->encoding_mode ),
		  error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine encoding mode.",
		 function );

		return( -1 );
	}
	return( result );
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
	if( export_handle->mode != EXPORT_HANDLE_MODE_TEXT_ENCODING )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported mode.",
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
	if( export_handle->mode != EXPORT_HANDLE_MODE_TEXT_ENCODING )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported mode.",
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
	if( export_handle->mode != EXPORT_HANDLE_MODE_TEXT_ENCODING )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported mode.",
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
	if( export_handle->mode != EXPORT_HANDLE_MODE_TEXT_ENCODING )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported mode.",
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
	process_status_t *process_status = NULL;
	static char *function            = "export_handle_export_text_input";

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
	if( export_handle->mode == EXPORT_HANDLE_MODE_BASE_ENCODING )
	{
		if( export_handle_export_base_encoded_input(
		     export_handle,
		     process_status,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to export base encoded input.",
			 function );

			goto on_error;
		}
	}
	else if( export_handle->mode == EXPORT_HANDLE_MODE_TEXT_ENCODING )
	{
		if( export_handle_export_text_encoded_input(
		     export_handle,
		     process_status,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to export text encoded input.",
			 function );

			goto on_error;
		}
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
	return( 1 );

on_error:
	if( process_status != NULL )
	{
		process_status_free(
		 &process_status,
		 NULL );
	}
	return( -1 );
}

/* Exports the base-encoded source file to the destination file
 * Returns the number of bytes of the source processed or -1 on error
 */
int export_handle_export_base_encoded_input(
     export_handle_t *export_handle,
     process_status_t *process_status,
     liberror_error_t **error )
{
	uint8_t *destination_buffer      = NULL;
	uint8_t *source_buffer           = NULL;
	const char *encoding_string      = NULL;
	const char *encoding_mode_string = NULL;
	static char *function            = "export_handle_export_base_encoded_input";
	size64_t export_count            = 0;
	size_t destination_buffer_size   = 0;
	size_t source_buffer_size        = 0;
	size_t write_size                = 0;
	ssize_t read_count               = 0;
	ssize_t write_count              = 0;
	int result                       = 0;

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
	if( export_handle->mode != EXPORT_HANDLE_MODE_BASE_ENCODING )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported mode.",
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
	if( ( export_handle->encoding != UNACOMMON_ENCODING_BASE16 )
	 && ( export_handle->encoding != UNACOMMON_ENCODING_BASE32 )
	 && ( export_handle->encoding != UNACOMMON_ENCODING_BASE32HEX )
	 && ( export_handle->encoding != UNACOMMON_ENCODING_BASE64 )
	 && ( export_handle->encoding != UNACOMMON_ENCODING_BASE64URL ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported encoding.",
		 function );

		return( -1 );
	}
	if( ( export_handle->encoding_mode != UNACOMMON_ENCODING_MODE_DECODE )
	 && ( export_handle->encoding_mode != UNACOMMON_ENCODING_MODE_ENCODE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported encoding mode.",
		 function );

		return( -1 );
	}
	if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
	{
		encoding_mode_string = "decode";
	}
	else
	{
		encoding_mode_string = "encode";
	}
	switch( export_handle->encoding )
	{
		case UNACOMMON_ENCODING_BASE16:
			if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
			{
				source_buffer_size      = ( EXPORT_HANDLE_BUFFER_SIZE / 2 ) * 2;
				destination_buffer_size = EXPORT_HANDLE_BUFFER_SIZE / 2;
			}
			else
			{
				source_buffer_size       = EXPORT_HANDLE_BUFFER_SIZE;
				destination_buffer_size  = EXPORT_HANDLE_BUFFER_SIZE * 2;
				destination_buffer_size += ( destination_buffer_size / 76 ) + 1;
			}
			encoding_string = "base16";

			break;

		case UNACOMMON_ENCODING_BASE32:
			if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
			{
				source_buffer_size      = ( EXPORT_HANDLE_BUFFER_SIZE / 5 ) * 5;
				destination_buffer_size = ( EXPORT_HANDLE_BUFFER_SIZE * 5 ) / 8;
			}
			else
			{
				source_buffer_size       = ( EXPORT_HANDLE_BUFFER_SIZE / 8 ) * 8;
				destination_buffer_size  = ( ( EXPORT_HANDLE_BUFFER_SIZE / 5 ) + 1 ) * 8;
				destination_buffer_size += ( destination_buffer_size / 76 ) + 1;
			}
			encoding_string = "base32";

			break;

		case UNACOMMON_ENCODING_BASE32HEX:
			if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
			{
				source_buffer_size      = ( EXPORT_HANDLE_BUFFER_SIZE / 5 ) * 5;
				destination_buffer_size = ( EXPORT_HANDLE_BUFFER_SIZE * 5 ) / 8;
			}
			else
			{
				source_buffer_size       = ( EXPORT_HANDLE_BUFFER_SIZE / 8 ) * 8;
				destination_buffer_size  = ( ( EXPORT_HANDLE_BUFFER_SIZE / 5 ) + 1 ) * 8;
				destination_buffer_size += ( destination_buffer_size / 76 ) + 1;
			}
			encoding_string = "base32hex";

			break;

		case UNACOMMON_ENCODING_BASE64:
			if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
			{
				source_buffer_size      = ( EXPORT_HANDLE_BUFFER_SIZE / 3 ) * 3;
				destination_buffer_size = ( EXPORT_HANDLE_BUFFER_SIZE * 3 ) / 4;
			}
			else
			{
				source_buffer_size       = ( EXPORT_HANDLE_BUFFER_SIZE / 4 ) * 4;
				destination_buffer_size  = ( ( EXPORT_HANDLE_BUFFER_SIZE / 3 ) + 1 ) * 4;
				destination_buffer_size += ( destination_buffer_size / 76 ) + 1;
			}
			encoding_string = "base64";

			break;

		case UNACOMMON_ENCODING_BASE64URL:
			if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
			{
				source_buffer_size      = ( EXPORT_HANDLE_BUFFER_SIZE / 3 ) * 3;
				destination_buffer_size = ( EXPORT_HANDLE_BUFFER_SIZE * 3 ) / 4;
			}
			else
			{
				source_buffer_size       = ( EXPORT_HANDLE_BUFFER_SIZE / 4 ) * 4;
				destination_buffer_size  = ( ( EXPORT_HANDLE_BUFFER_SIZE / 3 ) + 1 ) * 4;
				destination_buffer_size += ( destination_buffer_size / 76 ) + 1;
			}
			encoding_string = "base64url";

			break;
	}
	source_buffer = (uint8_t *) memory_allocate(
	                             sizeof( uint8_t ) * source_buffer_size );

	if( source_buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create source buffer.",
		 function );

		goto on_error;
	}
	destination_buffer = (uint8_t *) memory_allocate(
	                                  sizeof( uint8_t ) * destination_buffer_size );

	if( destination_buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination buffer.",
		 function );

		goto on_error;
	}
	while( 1 )
	{
		read_count = libsystem_file_read(
		              export_handle->source_file_handle,
		              source_buffer,
		              source_buffer_size,
		              error );

		if( read_count < 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read from source.",
			 function );

			goto on_error;
		}
		export_count += read_count;

		if( read_count == 0 )
		{
			break;
		}
		switch( export_handle->encoding )
		{
			case UNACOMMON_ENCODING_BASE16:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base16_stream_size_to_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE16_VARIANT_CASE_MIXED \
					           | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
					          LIBUNA_BASE16_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base16_stream_size_from_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE16_VARIANT_CASE_UPPER \
					           | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_76,
					          error );
				}
				break;

			case UNACOMMON_ENCODING_BASE32:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base32_stream_size_to_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL \
					           | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE \
					           | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
					          LIBUNA_BASE32_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base32_stream_size_from_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL \
					           | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64 \
					           | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
					          error );
				}
				break;

			case UNACOMMON_ENCODING_BASE32HEX:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base32_stream_size_to_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE32_VARIANT_ALPHABET_HEX \
					           | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE \
					           | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
					          LIBUNA_BASE32_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base32_stream_size_from_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE32_VARIANT_ALPHABET_HEX \
					           | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64 \
					           | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
					          error );
				}
				break;

			case UNACOMMON_ENCODING_BASE64:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base64_stream_size_to_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL \
					           | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE \
					           | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
					          LIBUNA_BASE64_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base64_stream_size_from_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE64_VARIANT_MIME,
					          error );
				}
				break;

			case UNACOMMON_ENCODING_BASE64URL:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base64_stream_size_to_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE64_VARIANT_URL,
					          LIBUNA_BASE64_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base64_stream_size_from_byte_stream(
					          source_buffer,
					          read_count,
					          &write_size,
					          LIBUNA_BASE64_VARIANT_URL,
					          error );
				}
				break;
		}
		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to determine %s size of %s source data.",
			 function,
			 encoding_string,
			 encoding_mode_string );

			goto on_error;
		}
		switch( export_handle->encoding )
		{
			case UNACOMMON_ENCODING_BASE16:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base16_stream_copy_to_byte_stream(
					          source_buffer,
					          read_count,
					          destination_buffer,
					          destination_buffer_size,
					          LIBUNA_BASE16_VARIANT_CASE_MIXED \
					           | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
					          LIBUNA_BASE16_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base16_stream_copy_from_byte_stream(
					          destination_buffer,
					          destination_buffer_size,
					          source_buffer,
					          read_count,
					          LIBUNA_BASE16_VARIANT_CASE_UPPER \
					           | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_76,
					          error );
				}
				break;

			case UNACOMMON_ENCODING_BASE32:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base32_stream_copy_to_byte_stream(
					          source_buffer,
					          read_count,
					          destination_buffer,
					          destination_buffer_size,
					          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL \
					           | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE \
					           | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
					          LIBUNA_BASE32_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base32_stream_copy_from_byte_stream(
					          destination_buffer,
					          destination_buffer_size,
					          source_buffer,
					          read_count,
					          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL \
					           | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64 \
					           | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
					          error );
				}
				break;

			case UNACOMMON_ENCODING_BASE32HEX:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base32_stream_copy_to_byte_stream(
					          source_buffer,
					          read_count,
					          destination_buffer,
					          destination_buffer_size,
					          LIBUNA_BASE32_VARIANT_ALPHABET_HEX \
					           | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE \
					           | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
					          LIBUNA_BASE32_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base32_stream_copy_from_byte_stream(
					          destination_buffer,
					          destination_buffer_size,
					          source_buffer,
					          read_count,
					          LIBUNA_BASE32_VARIANT_ALPHABET_HEX \
					           | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64 \
					           | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
					          error );
				}
				break;

			case UNACOMMON_ENCODING_BASE64:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base64_stream_copy_to_byte_stream(
					          source_buffer,
					          read_count,
					          destination_buffer,
					          destination_buffer_size,
					          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL \
					           | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE \
					           | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
					          LIBUNA_BASE64_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base64_stream_copy_from_byte_stream(
					          destination_buffer,
					          destination_buffer_size,
					          source_buffer,
					          read_count,
					          LIBUNA_BASE64_VARIANT_MIME,
					          error );
				}
				break;

			case UNACOMMON_ENCODING_BASE64URL:
				if( export_handle->encoding_mode == UNACOMMON_ENCODING_MODE_DECODE )
				{
					result = libuna_base64_stream_copy_to_byte_stream(
					          source_buffer,
					          read_count,
					          destination_buffer,
					          destination_buffer_size,
					          LIBUNA_BASE64_VARIANT_URL,
					          LIBUNA_BASE64_FLAG_STRIP_WHITESPACE,
					          error );
				}
				else
				{
					result = libuna_base64_stream_copy_from_byte_stream(
					          destination_buffer,
					          destination_buffer_size,
					          source_buffer,
					          read_count,
					          LIBUNA_BASE64_VARIANT_URL,
					          error );
				}
				break;
		}
		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to %s %s source data.",
			 function,
			 encoding_string,
			 encoding_mode_string );

			goto on_error;
		}
		write_count = libsystem_file_write(
			       export_handle->destination_file_handle,
			       destination_buffer,
			       write_size,
			       error );

		if( write_count < 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_WRITE_FAILED,
			 "%s: unable to write to destination.",
			 function );

			goto on_error;
		}
		if( process_status_update_unknown_total(
		     process_status,
		     export_count,
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
	memory_free(
	 source_buffer );

	source_buffer = NULL;

	memory_free(
	 destination_buffer );

	destination_buffer = NULL;

	return( 1 );

on_error:
	if( process_status != NULL )
	{
		process_status_stop(
		 process_status,
		 (size64_t) export_count,
		 PROCESS_STATUS_FAILED,
		 NULL );
	}
	if( destination_buffer != NULL )
	{
		memory_free(
		 destination_buffer );
	}
	if( source_buffer != NULL )
	{
		memory_free(
		 source_buffer );
	}
	return( -1 );
}

/* Exports the text-encoded source file to the destination file
 * Returns the number of bytes of the source processed or -1 on error
 */
int export_handle_export_text_encoded_input(
     export_handle_t *export_handle,
     process_status_t *process_status,
     liberror_error_t **error )
{
	libuna_unicode_character_t unicode_character[ 2 ];

	uint8_t *destination_buffer                  = NULL;
	uint8_t *source_buffer                       = NULL;
	static char *function                        = "export_handle_export_text_encoded_input";
	size64_t export_count                        = 0;
	size_t destination_buffer_index              = 0;
	size_t destination_buffer_size               = EXPORT_HANDLE_BUFFER_SIZE;
	size_t last_source_buffer_index              = 0;
	size_t realignment_iterator                  = 0;
	size_t source_buffer_index                   = 0;
	size_t source_buffer_size                    = EXPORT_HANDLE_BUFFER_SIZE;
	ssize_t read_count                           = 0;
	ssize_t write_count                          = 0;
	uint32_t destination_utf7_stream_base64_data = 0;
	uint32_t source_utf7_stream_base64_data      = 0;
	uint8_t analyze_first_character              = 1;
	uint8_t number_of_unicode_characters         = 0;
	uint8_t unicode_character_index              = 0;
	int result                                   = 1;

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
	if( export_handle->mode != EXPORT_HANDLE_MODE_TEXT_ENCODING )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported mode.",
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
	if( ( export_handle->input_format != UNACOMMON_FORMAT_AUTO_DETECT )
	 && ( export_handle->input_format != UNACOMMON_FORMAT_BYTE_STREAM )
	 && ( export_handle->input_format != UNACOMMON_FORMAT_UTF7 )
	 && ( export_handle->input_format != UNACOMMON_FORMAT_UTF8 )
	 && ( export_handle->input_format != UNACOMMON_FORMAT_UTF16LE )
	 && ( export_handle->input_format != UNACOMMON_FORMAT_UTF16LE )
	 && ( export_handle->input_format != UNACOMMON_FORMAT_UTF32LE )
	 && ( export_handle->input_format != UNACOMMON_FORMAT_UTF32LE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported input format.",
		 function );

		return( -1 );
	}
	if( ( export_handle->output_format != UNACOMMON_FORMAT_BYTE_STREAM )
	 && ( export_handle->output_format != UNACOMMON_FORMAT_UTF7 )
	 && ( export_handle->output_format != UNACOMMON_FORMAT_UTF8 )
	 && ( export_handle->output_format != UNACOMMON_FORMAT_UTF16LE )
	 && ( export_handle->output_format != UNACOMMON_FORMAT_UTF16LE )
	 && ( export_handle->output_format != UNACOMMON_FORMAT_UTF32LE )
	 && ( export_handle->output_format != UNACOMMON_FORMAT_UTF32LE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported output format.",
		 function );

		return( -1 );
	}
	if( ( export_handle->newline_conversion != UNACOMMON_NEWLINE_CONVERSION_NONE )
	 && ( export_handle->newline_conversion != UNACOMMON_NEWLINE_CONVERSION_CRLF )
	 && ( export_handle->newline_conversion != UNACOMMON_NEWLINE_CONVERSION_CR )
	 && ( export_handle->newline_conversion != UNACOMMON_NEWLINE_CONVERSION_LF ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported newline conversion.",
		 function );

		return( -1 );
	}
	source_buffer = (uint8_t *) memory_allocate(
	                             sizeof( uint8_t ) * source_buffer_size );

	if( source_buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create source buffer.",
		 function );

		goto on_error;
	}
	destination_buffer = (uint8_t *) memory_allocate(
	                                  sizeof( uint8_t ) * destination_buffer_size );

	if( destination_buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination buffer.",
		 function );

		goto on_error;
	}
	if( export_handle->export_byte_order_mark != 0 )
	{
		switch( export_handle->output_format )
		{
			case UNACOMMON_FORMAT_UTF8:
				result = libuna_utf8_stream_copy_byte_order_mark(
				          destination_buffer,
				          destination_buffer_size,
				          &destination_buffer_index,
				          error );
				break;

			case UNACOMMON_FORMAT_UTF16BE:
				result = libuna_utf16_stream_copy_byte_order_mark(
				          destination_buffer,
				          destination_buffer_size,
				          &destination_buffer_index,
				          LIBUNA_ENDIAN_BIG,
				          error );
				break;

			case UNACOMMON_FORMAT_UTF16LE:
				result = libuna_utf16_stream_copy_byte_order_mark(
				          destination_buffer,
				          destination_buffer_size,
				          &destination_buffer_index,
				          LIBUNA_ENDIAN_LITTLE,
				          error );
				break;

			case UNACOMMON_FORMAT_UTF32BE:
				result = libuna_utf32_stream_copy_byte_order_mark(
				          destination_buffer,
				          destination_buffer_size,
				          &destination_buffer_index,
				          LIBUNA_ENDIAN_BIG,
				          error );
				break;

			case UNACOMMON_FORMAT_UTF32LE:
				result = libuna_utf32_stream_copy_byte_order_mark(
				          destination_buffer,
				          destination_buffer_size,
				          &destination_buffer_index,
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
		              &( source_buffer[ source_buffer_index ] ),
		              source_buffer_size - source_buffer_index,
		              error );

		if( read_count < 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read from source.",
			 function );

			goto on_error;
		}
		export_count       += read_count;
		read_count         += (ssize_t) source_buffer_index;
		source_buffer_index = 0;

		if( read_count == 0 )
		{
			break;
		}
		if( analyze_first_character != 0 )
		{
			if( ( read_count >= 3 )
			 && ( source_buffer[ 0 ] == 0xef )
			 && ( source_buffer[ 1 ] == 0xbb )
			 && ( source_buffer[ 2 ] == 0xbf ) )
			{
				if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
				{
					export_handle->input_format = UNACOMMON_FORMAT_UTF8;
				}
				if( export_handle->input_format == UNACOMMON_FORMAT_UTF8 )
				{
					source_buffer_index += 3;
				}
			}
			else if( ( read_count >= 2 )
			      && ( source_buffer[ 0 ] == 0xfe )
			      && ( source_buffer[ 1 ] == 0xff ) )
			{
				if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
				{
					export_handle->input_format = UNACOMMON_FORMAT_UTF16BE;
				}
				if( export_handle->input_format == UNACOMMON_FORMAT_UTF16BE )
				{
					source_buffer_index += 2;
				}
			}
			else if( ( read_count >= 2 )
			      && ( source_buffer[ 0 ] == 0xff )
			      && ( source_buffer[ 1 ] == 0xfe ) )
			{
				if( ( read_count >= 4 )
				 && ( source_buffer[ 2 ] == 0x00 )
			         && ( source_buffer[ 3 ] == 0x00 ) )
				{
					if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
					{
						export_handle->input_format = UNACOMMON_FORMAT_UTF32LE;
					}
					if( export_handle->input_format == UNACOMMON_FORMAT_UTF32LE )
					{
						source_buffer_index += 4;
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
						source_buffer_index += 2;
					}
				}
			}
			else if( ( read_count >= 4 )
			      && ( source_buffer[ 0 ] == 0x00 )
			      && ( source_buffer[ 1 ] == 0x00 )
			      && ( source_buffer[ 1 ] == 0xfe )
			      && ( source_buffer[ 1 ] == 0xff ) )
			{
				if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
				{
					export_handle->input_format = UNACOMMON_FORMAT_UTF32BE;
				}
				if( export_handle->input_format == UNACOMMON_FORMAT_UTF32BE )
				{
					source_buffer_index += 4;
				}
			}
			else if( export_handle->input_format == UNACOMMON_FORMAT_AUTO_DETECT )
			{
				export_handle->input_format = UNACOMMON_FORMAT_BYTE_STREAM;
			}
			read_count -= (ssize_t) source_buffer_index;

			analyze_first_character = 0;
		}
		last_source_buffer_index = source_buffer_index;

		while( read_count > 0 )
		{
			/* Sanity check
			 */
			if( source_buffer_index >= source_buffer_size )
			{
				break;
			}
			/* Make sure to have at least room for a 6 byte character in the destination buffer
			 */
		 	if( destination_buffer_index >= ( destination_buffer_size - 5 ) )
			{
				break;
			}
			switch( export_handle->input_format )
			{
				case UNACOMMON_FORMAT_BYTE_STREAM:
					result = libuna_unicode_character_copy_from_byte_stream(
						  &unicode_character[ unicode_character_index ],
						  source_buffer,
						  source_buffer_size,
						  &source_buffer_index,
						  export_handle->byte_stream_codepage,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF7:
					result = libuna_unicode_character_copy_from_utf7_stream(
						  &unicode_character[ unicode_character_index ],
						  source_buffer,
						  source_buffer_size,
						  &source_buffer_index,
						  &source_utf7_stream_base64_data,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF8:
					result = libuna_unicode_character_copy_from_utf8(
						  &unicode_character[ unicode_character_index ],
						  source_buffer,
						  source_buffer_size,
						  &source_buffer_index,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF16BE:
					result = libuna_unicode_character_copy_from_utf16_stream(
						  &unicode_character[ unicode_character_index ],
						  source_buffer,
						  source_buffer_size,
						  &source_buffer_index,
						  LIBUNA_ENDIAN_BIG,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF16LE:
					result = libuna_unicode_character_copy_from_utf16_stream(
						  &unicode_character[ unicode_character_index ],
						  source_buffer,
						  source_buffer_size,
						  &source_buffer_index,
						  LIBUNA_ENDIAN_LITTLE,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF32BE:
					result = libuna_unicode_character_copy_from_utf32_stream(
						  &unicode_character[ unicode_character_index ],
						  source_buffer,
						  source_buffer_size,
						  &source_buffer_index,
						  LIBUNA_ENDIAN_BIG,
					          error );
					break;

				case UNACOMMON_FORMAT_UTF32LE:
					result = libuna_unicode_character_copy_from_utf32_stream(
						  &unicode_character[ unicode_character_index ],
						  source_buffer,
						  source_buffer_size,
						  &source_buffer_index,
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

				goto on_error;
			}
			number_of_unicode_characters++;

			read_count -= source_buffer_index - last_source_buffer_index;

			last_source_buffer_index = source_buffer_index;

			if( export_handle->newline_conversion != UNACOMMON_NEWLINE_CONVERSION_NONE )
			{
				/* Determine if character is a line feed (LF)
				 */
				if( unicode_character[ unicode_character_index ] == 0x000a )
				{
					if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CRLF )
					{
						if( unicode_character_index == 0 )
						{
							unicode_character[ unicode_character_index     ] = 0x000d;
							unicode_character[ unicode_character_index + 1 ] = 0x000a;
			
							number_of_unicode_characters++;
						}
					}
					else if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_CR )
					{
						if( unicode_character_index == 0 )
						{
							unicode_character[ unicode_character_index ] = 0x000d;
						}
						else if( unicode_character_index == 1 )
						{
							unicode_character[ unicode_character_index - 1 ] = 0x000d;

							number_of_unicode_characters--;
						}
					}
					else if( export_handle->newline_conversion == UNACOMMON_NEWLINE_CONVERSION_LF )
					{
						if( unicode_character_index == 1 )
						{
							unicode_character[ unicode_character_index - 1 ] = 0x000a;

							number_of_unicode_characters--;
						}
					}
				}
				/* Determine if character is a carriage return (CR)
				 */
				else if( unicode_character[ unicode_character_index ] == 0x000d )
				{
					unicode_character_index++;

					continue;
				}
			}
			/* Write all unicode characters
			 */
			for( unicode_character_index = 0;
			     unicode_character_index < number_of_unicode_characters;
			     unicode_character_index++ )
			{
				switch( export_handle->output_format )
				{
					case UNACOMMON_FORMAT_BYTE_STREAM:
						result = libuna_unicode_character_copy_to_byte_stream(
							  unicode_character[ unicode_character_index ],
							  destination_buffer,
							  destination_buffer_size,
							  &destination_buffer_index,
							  export_handle->byte_stream_codepage,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF7:
						result = libuna_unicode_character_copy_to_utf7_stream(
							  unicode_character[ unicode_character_index ],
							  destination_buffer,
							  destination_buffer_size,
							  &destination_buffer_index,
							  &destination_utf7_stream_base64_data,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF8:
						result = libuna_unicode_character_copy_to_utf8(
							  unicode_character[ unicode_character_index ],
							  destination_buffer,
							  destination_buffer_size,
							  &destination_buffer_index,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF16BE:
						result = libuna_unicode_character_copy_to_utf16_stream(
							  unicode_character[ unicode_character_index ],
							  destination_buffer,
							  destination_buffer_size,
							  &destination_buffer_index,
							  LIBUNA_ENDIAN_BIG,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF16LE:
						result = libuna_unicode_character_copy_to_utf16_stream(
							  unicode_character[ unicode_character_index ],
							  destination_buffer,
							  destination_buffer_size,
							  &destination_buffer_index,
							  LIBUNA_ENDIAN_LITTLE,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF32BE:
						result = libuna_unicode_character_copy_to_utf32_stream(
							  unicode_character[ unicode_character_index ],
							  destination_buffer,
							  destination_buffer_size,
							  &destination_buffer_index,
							  LIBUNA_ENDIAN_BIG,
						          error );
						break;

					case UNACOMMON_FORMAT_UTF32LE:
						result = libuna_unicode_character_copy_to_utf32_stream(
							  unicode_character[ unicode_character_index ],
							  destination_buffer,
							  destination_buffer_size,
							  &destination_buffer_index,
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

					goto on_error;
				}
			}
			number_of_unicode_characters = 0;
			unicode_character_index      = 0;
		}
		if( destination_buffer_index > 0 )
		{
			write_count = libsystem_file_write(
			               export_handle->destination_file_handle,
			               destination_buffer,
		        	       destination_buffer_index,
			               error );

			if( write_count < 0 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_WRITE_FAILED,
				 "%s: unable to write to destination.",
				 function );

				goto on_error;
			}
			destination_buffer_index = 0;
		}
		/* Realign the remaining bytes to the start of the source buffer
		 */
		realignment_iterator = source_buffer_index;
		source_buffer_index  = 0;

		for( ;
		     read_count > 0;
		     read_count-- )
		{
			source_buffer[ source_buffer_index++ ] = source_buffer[ realignment_iterator++ ];
		}
		if( process_status_update_unknown_total(
		     process_status,
		     export_count,
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
	memory_free(
	 source_buffer );

	source_buffer = NULL;

	memory_free(
	 destination_buffer );

	destination_buffer = NULL;

	return( 1 );

on_error:
	if( process_status != NULL )
	{
		process_status_stop(
		 process_status,
		 (size64_t) export_count,
		 PROCESS_STATUS_FAILED,
		 NULL );
	}
	if( destination_buffer != NULL )
	{
		memory_free(
		 destination_buffer );
	}
	if( source_buffer != NULL )
	{
		memory_free(
		 source_buffer );
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
	if( ( export_handle->mode != EXPORT_HANDLE_MODE_BASE_ENCODING )
	 && ( export_handle->mode != EXPORT_HANDLE_MODE_TEXT_ENCODING ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid export handle - unsupported mode.",
		 function );

		return( -1 );
	}
	fprintf(
	 export_handle->notify_stream,
	 "Exporting:\n" );

	if( export_handle->mode == EXPORT_HANDLE_MODE_BASE_ENCODING )
	{
	}
	else if( export_handle->mode == EXPORT_HANDLE_MODE_TEXT_ENCODING )
	{
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
	}
	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	return( 1 );
}

