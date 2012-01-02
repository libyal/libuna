/* 
 * Export handle
 *
 * Copyright (c) 2008-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _EXPORT_HANDLE_H )
#define _EXPORT_HANDLE_H

#include <common.h>
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#include <libsystem.h>

#include "process_status.h"
#include "unatools_libuna.h"

#if defined( __cplusplus )
extern "C" {
#endif

enum EXPORT_HANDLE_MODE
{
	EXPORT_HANDLE_MODE_BASE_ENCODING	= (uint8_t) 'b',
	EXPORT_HANDLE_MODE_TEXT_ENCODING	= (uint8_t) 't'
};

typedef struct export_handle export_handle_t;

struct export_handle
{
	/* The mode
	 */
	uint8_t mode;

	/* The source filename
	 */
	libcstring_system_character_t *source_filename;

	/* The source filename size
	 */
	size_t source_filename_size;

	/* The destination filename
	 */
	libcstring_system_character_t *destination_filename;

	/* The destination filename size
	 */
	size_t destination_filename_size;

	/* The source file handle
	 */
	libsystem_file_handle_t source_file_handle;

	/* The destination file handle
	 */
	libsystem_file_handle_t destination_file_handle;

	union
	{
		/* Values for base encoding export
		 */
		struct
		{
			/* The enconding
			 */
			uint8_t encoding;

			/* The encoding mode
			 */
			uint8_t encoding_mode;
		};

		/* Values for text encoding export
		 */
		struct
		{
			/* The input format
			 */
			uint8_t input_format;

			/* The output format
			 */
			uint8_t output_format;

			/* The newline conversion
			 */
			uint8_t newline_conversion;

			/* Value to indicate if the byte-order mark should be exported
			 */
			uint8_t export_byte_order_mark;
		};
	};

	/* The byte stream codepage
	 */
	int byte_stream_codepage;

	/* The nofication output stream
	 */
	FILE *notify_stream;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int export_handle_initialize(
     export_handle_t **export_handle,
     uint8_t mode,
     liberror_error_t **error );

int export_handle_free(
     export_handle_t **export_handle,
     liberror_error_t **error );

int export_handle_signal_abort(
     export_handle_t *export_handle,
     liberror_error_t **error );

int export_handle_open_input(
     export_handle_t *export_handle,
     liberror_error_t **error );

int export_handle_open_output(
     export_handle_t *export_handle,
     liberror_error_t **error );

int export_handle_close(
     export_handle_t *export_handle,
     liberror_error_t **error );

int export_handle_set_string(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     libcstring_system_character_t **internal_string,
     size_t *internal_string_size,
     liberror_error_t **error );

int export_handle_set_encoding(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error );

int export_handle_set_encoding_mode(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error );

int export_handle_set_input_format(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error );

int export_handle_set_output_format(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error );

int export_handle_set_newline_conversion(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error );

int export_handle_set_byte_stream_codepage(
     export_handle_t *export_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error );

int export_handle_export_input(
     export_handle_t *export_handle,
     uint8_t print_status_information,
     liberror_error_t **error );

int export_handle_export_base_encoded_input(
     export_handle_t *export_handle,
     process_status_t *process_status,
     liberror_error_t **error );

int export_handle_export_text_encoded_input(
     export_handle_t *export_handle,
     process_status_t *process_status,
     liberror_error_t **error );

int export_handle_print_parameters(
     export_handle_t *export_handle,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

