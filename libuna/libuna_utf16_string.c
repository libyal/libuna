/*
 * UTF-16 string functions
 *
 * Copyright (C) 2008-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#include "libuna_definitions.h"
#include "libuna_libcerror.h"
#include "libuna_scsu.h"
#include "libuna_types.h"
#include "libuna_unicode_character.h"
#include "libuna_utf16_string.h"

/* Determines the size of an UTF-16 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_byte_stream(
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int codepage,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_byte_stream";
	size_t byte_stream_index                     = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	if( byte_stream_size == 0 )
	{
		return( 1 );
	}
	while( byte_stream_index < byte_stream_size )
	{
		/* Convert the byte stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_byte_stream(
		     &unicode_character,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_index,
		     codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from byte stream.",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character byte words are required
		 */
		if( libuna_unicode_character_size_to_utf16(
		     unicode_character,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		*utf16_string_size += 1;
	}
	return( 1 );
}

/* Copies an UTF-16 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_copy_from_byte_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int codepage,
     libcerror_error_t **error )
{
	static char *function     = "libuna_utf16_string_copy_from_byte_stream";
	size_t utf16_string_index = 0;

	if( libuna_utf16_string_with_index_copy_from_byte_stream(
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     byte_stream,
	     byte_stream_size,
	     codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy byte stream to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-16 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_with_index_copy_from_byte_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int codepage,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_with_index_copy_from_byte_stream";
	size_t byte_stream_index                     = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( byte_stream_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing byte stream value.",
		 function );

		return( -1 );
	}
	while( byte_stream_index < byte_stream_size )
	{
		/* Convert the byte stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_byte_stream(
		     &unicode_character,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_index,
		     codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from byte stream.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 character byte words
		 */
		if( libuna_unicode_character_copy_to_utf16(
		     unicode_character,
		     utf16_string,
		     utf16_string_size,
		     utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ *utf16_string_index ] = 0;

		*utf16_string_index += 1;
	}
	return( 1 );
}

/* Compares an UTF-16 string with a byte stream
 * Returns LIBUNA_COMPARE_LESS, LIBUNA_COMPARE_EQUAL, LIBUNA_COMPARE_GREATER if successful or -1 on error
 */
int libuna_utf16_string_compare_with_byte_stream(
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int codepage,
     libcerror_error_t **error )
{
	static char *function                                    = "libuna_utf16_string_compare_with_byte_stream";
	size_t byte_stream_index                                 = 0;
	size_t utf16_string_index                                = 0;
	libuna_unicode_character_t utf16_unicode_character       = 0;
	libuna_unicode_character_t byte_stream_unicode_character = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( byte_stream_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing byte stream value.",
		 function );

		return( -1 );
	}
	if( ( utf16_string_size >= 1 )
	 && ( utf16_string[ utf16_string_size - 1 ] == 0 ) )
	{
		utf16_string_size -= 1;
	}
	/* Check if the byte stream is terminated with zero bytes
	 */
	if( ( byte_stream_size >= 1 )
	 && ( byte_stream[ byte_stream_size - 1 ] == 0 ) )
	{
		byte_stream_size -= 1;
	}
	while( ( utf16_string_index < utf16_string_size )
	    && ( byte_stream_index < byte_stream_size ) )
	{
		/* Convert the UTF-16 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &utf16_unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16.",
			 function );

			return( -1 );
		}
		/* Convert the byte stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_byte_stream(
		     &byte_stream_unicode_character,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_index,
		     codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from byte stream.",
			 function );

			return( -1 );
		}
		if( utf16_unicode_character < byte_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_LESS );
		}
		else if( utf16_unicode_character > byte_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_GREATER );
		}
	}
	/* Check if both strings were entirely processed
	 */
	if( utf16_string_index < utf16_string_size )
	{
		return( LIBUNA_COMPARE_GREATER );
	}
	else if( byte_stream_index < byte_stream_size )
	{
		return( LIBUNA_COMPARE_LESS );
	}
	return( LIBUNA_COMPARE_EQUAL );
}

/* Determines the size of an UTF-16 string from an UTF-7 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf7_stream(
     const uint8_t *utf7_stream,
     size_t utf7_stream_size,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf7_stream";
	size_t utf7_stream_index                     = 0;
	libuna_unicode_character_t unicode_character = 0;
	uint32_t utf7_stream_base64_data             = 0;

	if( utf7_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream.",
		 function );

		return( -1 );
	}
	if( utf7_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-7 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	if( utf7_stream_size == 0 )
	{
		return( 1 );
	}
	while( utf7_stream_index < utf7_stream_size )
	{
		/* Convert the UTF-7 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf7_stream(
		     &unicode_character,
		     utf7_stream,
		     utf7_stream_size,
		     &utf7_stream_index,
		     &utf7_stream_base64_data,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-7 stream.",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character bytes are required
		 */
		if( libuna_unicode_character_size_to_utf16(
		     unicode_character,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		*utf16_string_size += 1;
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-7 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_copy_from_utf7_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *utf7_stream,
     size_t utf7_stream_size,
     libcerror_error_t **error )
{
	static char *function     = "libuna_utf16_string_copy_from_utf7_stream";
	size_t utf16_string_index = 0;

	if( libuna_utf16_string_with_index_copy_from_utf7_stream(
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     utf7_stream,
	     utf7_stream_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to UTF-7 stream to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-7 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_with_index_copy_from_utf7_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const uint8_t *utf7_stream,
     size_t utf7_stream_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_with_index_copy_from_utf7_stream";
	size_t utf7_stream_index                     = 0;
	libuna_unicode_character_t unicode_character = 0;
	uint32_t utf7_stream_base64_data             = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( utf7_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream.",
		 function );

		return( -1 );
	}
	if( utf7_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-7 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf7_stream_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing UTF-7 stream value.",
		 function );

		return( -1 );
	}
	while( utf7_stream_index < utf7_stream_size )
	{
		/* Convert the UTF-7 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf7_stream(
		     &unicode_character,
		     utf7_stream,
		     utf7_stream_size,
		     &utf7_stream_index,
		     &utf7_stream_base64_data,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-7 stream.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 character bytes
		 */
		if( libuna_unicode_character_copy_to_utf16(
		     unicode_character,
		     utf16_string,
		     utf16_string_size,
		     utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ *utf16_string_index ] = 0;

		*utf16_string_index += 1;
	}
	return( 1 );
}

/* Compares an UTF-16 string with an UTF-7 stream
 * Returns LIBUNA_COMPARE_LESS, LIBUNA_COMPARE_EQUAL, LIBUNA_COMPARE_GREATER if successful or -1 on error
 */
int libuna_utf16_string_compare_with_utf7_stream(
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *utf7_stream,
     size_t utf7_stream_size,
     libcerror_error_t **error )
{
	static char *function                                    = "libuna_utf16_string_compare_with_utf7_stream";
	size_t utf16_string_index                                = 0;
	size_t utf7_stream_index                                 = 0;
	libuna_unicode_character_t utf16_unicode_character       = 0;
	libuna_unicode_character_t utf7_stream_unicode_character = 0;
	uint32_t utf7_stream_base64_data                         = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf7_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream.",
		 function );

		return( -1 );
	}
	if( utf7_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-7 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf7_stream_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing UTF-7 stream value.",
		 function );

		return( -1 );
	}
	if( ( utf16_string_size >= 1 )
	 && ( utf16_string[ utf16_string_size - 1 ] == 0 ) )
	{
		utf16_string_size -= 1;
	}
	/* Check if the UTF-7 stream is terminated with zero bytes
	 */
	if( ( utf7_stream_size >= 1 )
	 && ( utf7_stream[ utf7_stream_size - 1 ] == 0 ) )
	{
		utf7_stream_size -= 1;
	}
	while( ( utf16_string_index < utf16_string_size )
	    && ( utf7_stream_index < utf7_stream_size ) )
	{
		/* Convert the UTF-16 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &utf16_unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16.",
			 function );

			return( -1 );
		}
		/* Convert the UTF-7 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf7_stream(
		     &utf7_stream_unicode_character,
		     utf7_stream,
		     utf7_stream_size,
		     &utf7_stream_index,
		     &utf7_stream_base64_data,
                     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-7 stream.",
			 function );

			return( -1 );
		}
		if( utf16_unicode_character < utf7_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_LESS );
		}
		else if( utf16_unicode_character > utf7_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_GREATER );
		}
	}
	/* Check if both strings were entirely processed
	 */
	if( utf16_string_index < utf16_string_size )
	{
		return( LIBUNA_COMPARE_GREATER );
	}
	else if( utf7_stream_index < utf7_stream_size )
	{
		return( LIBUNA_COMPARE_LESS );
	}
	return( LIBUNA_COMPARE_EQUAL );
}

/* Determines the size of an UTF-16 string from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf8(
     const libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf8";
	size_t utf8_string_index                     = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	if( utf8_string_size == 0 )
	{
		return( 1 );
	}
	while( utf8_string_index < utf8_string_size )
	{
		/* Convert the UTF-8 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-8.",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character bytes are required
		 */
		if( libuna_unicode_character_size_to_utf16(
		    unicode_character,
		    utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		*utf16_string_size += 1;
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_copy_from_utf8(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function     = "libuna_utf16_string_copy_from_utf8";
	size_t utf16_string_index = 0;

	if( libuna_utf16_string_with_index_copy_from_utf8(
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy UTF-8 string to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_with_index_copy_from_utf8(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_with_index_copy_from_utf8";
	size_t utf8_string_index                     = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing UTF-8 string value.",
		 function );

		return( -1 );
	}
	while( utf8_string_index < utf8_string_size )
	{
		/* Convert the UTF-8 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-8.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 character bytes
		 */
		if( libuna_unicode_character_copy_to_utf16(
		     unicode_character,
		     utf16_string,
		     utf16_string_size,
		     utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ *utf16_string_index ] = 0;

		*utf16_string_index += 1;
	}
	return( 1 );
}

/* Determines the size of an UTF-16 string from an UTF-8 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf8_stream(
     const uint8_t *utf8_stream,
     size_t utf8_stream_size,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf8_stream";
	size_t utf8_stream_index                     = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf8_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 stream.",
		 function );

		return( -1 );
	}
	if( utf8_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	if( utf8_stream_size == 0 )
	{
		return( 1 );
	}
	/* Check if UTF-8 stream starts with a byte order mark (BOM)
	 */
	if( utf8_stream_size >= 3 )
	{
		if( ( utf8_stream[ 0 ] == 0x0ef )
		 && ( utf8_stream[ 1 ] == 0x0bb )
		 && ( utf8_stream[ 2 ] == 0x0bf ) )
		{
			utf8_stream_index += 3;
		}
	}
	while( utf8_stream_index < utf8_stream_size )
	{
		/* Convert the UTF-8 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_stream,
		     utf8_stream_size,
		     &utf8_stream_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-8 stream.",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character bytes are required
		 */
		if( libuna_unicode_character_size_to_utf16(
		     unicode_character,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		*utf16_string_size += 1;
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-8 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_copy_from_utf8_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *utf8_stream,
     size_t utf8_stream_size,
     libcerror_error_t **error )
{
	static char *function     = "libuna_utf16_string_copy_from_utf8_stream";
	size_t utf16_string_index = 0;

	if( libuna_utf16_string_with_index_copy_from_utf8_stream(
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     utf8_stream,
	     utf8_stream_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to UTF-8 stream to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-8 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_with_index_copy_from_utf8_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const uint8_t *utf8_stream,
     size_t utf8_stream_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_with_index_copy_from_utf8_stream";
	size_t utf8_stream_index                     = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( utf8_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 stream.",
		 function );

		return( -1 );
	}
	if( utf8_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_stream_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing UTF-8 stream value.",
		 function );

		return( -1 );
	}
	/* Check if UTF-8 stream starts with a byte order mark (BOM)
	 */
	if( utf8_stream_size >= 3 )
	{
		if( ( utf8_stream[ 0 ] == 0x0ef )
		 && ( utf8_stream[ 1 ] == 0x0bb )
		 && ( utf8_stream[ 2 ] == 0x0bf ) )
		{
			utf8_stream_index += 3;
		}
	}
	while( utf8_stream_index < utf8_stream_size )
	{
		/* Convert the UTF-8 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_stream,
		     utf8_stream_size,
		     &utf8_stream_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-8 stream.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 character bytes
		 */
		if( libuna_unicode_character_copy_to_utf16(
		     unicode_character,
		     utf16_string,
		     utf16_string_size,
		     utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ *utf16_string_index ] = 0;

		*utf16_string_index += 1;
	}
	return( 1 );
}

/* Compares an UTF-16 string with an UTF-8 stream
 * Returns LIBUNA_COMPARE_LESS, LIBUNA_COMPARE_EQUAL, LIBUNA_COMPARE_GREATER if successful or -1 on error
 */
int libuna_utf16_string_compare_with_utf8_stream(
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *utf8_stream,
     size_t utf8_stream_size,
     libcerror_error_t **error )
{
	static char *function                                    = "libuna_utf16_string_compare_with_utf8_stream";
	size_t utf16_string_index                                = 0;
	size_t utf8_stream_index                                 = 0;
	libuna_unicode_character_t utf16_unicode_character       = 0;
	libuna_unicode_character_t utf8_stream_unicode_character = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 stream.",
		 function );

		return( -1 );
	}
	if( utf8_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_stream_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing UTF-8 stream value.",
		 function );

		return( -1 );
	}
	/* Check if UTF-8 stream starts with a byte order mark (BOM)
	 */
	if( utf8_stream_size >= 3 )
	{
		if( ( utf8_stream[ 0 ] == 0x0ef )
		 && ( utf8_stream[ 1 ] == 0x0bb )
		 && ( utf8_stream[ 2 ] == 0x0bf ) )
		{
			utf8_stream_index += 3;
		}
	}
	if( ( utf16_string_size >= 1 )
	 && ( utf16_string[ utf16_string_size - 1 ] == 0 ) )
	{
		utf16_string_size -= 1;
	}
	/* Check if the UTF-8 stream is terminated with zero bytes
	 */
	if( ( utf8_stream_size >= 1 )
	 && ( utf8_stream[ utf8_stream_size - 1 ] == 0 ) )
	{
		utf8_stream_size -= 1;
	}
	while( ( utf16_string_index < utf16_string_size )
	    && ( utf8_stream_index < utf8_stream_size ) )
	{
		/* Convert the UTF-16 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &utf16_unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16.",
			 function );

			return( -1 );
		}
		/* Convert the UTF-8 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &utf8_stream_unicode_character,
		     utf8_stream,
		     utf8_stream_size,
		     &utf8_stream_index,
                     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-8 stream.",
			 function );

			return( -1 );
		}
		if( utf16_unicode_character < utf8_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_LESS );
		}
		else if( utf16_unicode_character > utf8_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_GREATER );
		}
	}
	/* Check if both strings were entirely processed
	 */
	if( utf16_string_index < utf16_string_size )
	{
		return( LIBUNA_COMPARE_GREATER );
	}
	else if( utf8_stream_index < utf8_stream_size )
	{
		return( LIBUNA_COMPARE_LESS );
	}
	return( LIBUNA_COMPARE_EQUAL );
}

/* Determines the size of an UTF-16 string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf16_stream(
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf16_stream";
	libuna_unicode_character_t unicode_character = 0;
	size_t utf16_stream_index                    = 0;
	int read_byte_order                          = 0;
	int result                                   = 0;

	if( utf16_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size % 2 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream value.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	if( utf16_stream_size == 0 )
	{
		return( 1 );
	}
	/* Check if UTF-16 stream is in big or little endian
	 */
	if( utf16_stream_size >= 2 )
	{
		if( ( utf16_stream[ 0 ] == 0x0ff )
		 && ( utf16_stream[ 1 ] == 0x0fe ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf16_stream_index = 2;
		}
		else if( ( utf16_stream[ 0 ] == 0x0fe )
		      && ( utf16_stream[ 1 ] == 0x0ff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf16_stream_index = 2;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	while( ( utf16_stream_index + 1 ) < utf16_stream_size )
	{
		/* Convert the UTF-16 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16_stream(
		     &unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 stream.",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character bytes are required
		 */
		if( ( byte_order & LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE ) == 0 )
		{
			result = libuna_unicode_character_size_to_utf16(
			          unicode_character,
			          utf16_string_size,
			          error );
		}
		else
		{
			result = libuna_unicode_character_size_to_ucs2(
			          unicode_character,
			          utf16_string_size,
			          error );
		}
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		*utf16_string_size += 1;
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_copy_from_utf16_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function     = "libuna_utf16_string_copy_from_utf16_stream";
	size_t utf16_string_index = 0;

	if( libuna_utf16_string_with_index_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     utf16_stream,
	     utf16_stream_size,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy UTF-16 stream to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_with_index_copy_from_utf16_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_with_index_copy_from_utf16_stream";
	libuna_unicode_character_t unicode_character = 0;
	size_t utf16_stream_index                    = 0;
	int read_byte_order                          = 0;
	int result                                   = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( utf16_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size == 0 )
	 || ( ( utf16_stream_size % 2 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream value.",
		 function );

		return( -1 );
	}
	/* Check if UTF-16 stream is in big or little endian
	 */
	if( utf16_stream_size >= 2 )
	{
		if( ( utf16_stream[ 0 ] == 0x0ff )
		 && ( utf16_stream[ 1 ] == 0x0fe ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf16_stream_index = 2;
		}
		else if( ( utf16_stream[ 0 ] == 0x0fe )
		      && ( utf16_stream[ 1 ] == 0x0ff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf16_stream_index = 2;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	while( ( utf16_stream_index + 1 ) < utf16_stream_size )
	{
		/* Convert the UTF-16 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16_stream(
		     &unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 stream.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 character bytes
		 */
		if( ( byte_order & LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE ) == 0 )
		{
			result = libuna_unicode_character_copy_to_utf16(
			          unicode_character,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
		}
		else
		{
			result = libuna_unicode_character_copy_to_ucs2(
			          unicode_character,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
		}
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ *utf16_string_index ] = 0;

		*utf16_string_index += 1;
	}
	return( 1 );
}

/* Compares an UTF-16 string with an UTF-16 stream
 * Returns LIBUNA_COMPARE_LESS, LIBUNA_COMPARE_EQUAL, LIBUNA_COMPARE_GREATER if successful or -1 on error
 */
int libuna_utf16_string_compare_with_utf16_stream(
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function                                     = "libuna_utf16_string_compare_with_utf16_stream";
	libuna_unicode_character_t utf16_stream_unicode_character = 0;
	libuna_unicode_character_t utf16_unicode_character        = 0;
	size_t utf16_stream_index                                 = 0;
	size_t utf16_string_index                                 = 0;
	int read_byte_order                                       = 0;
	int result                                                = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size == 0 )
	 || ( ( utf16_stream_size % 2 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream value.",
		 function );

		return( -1 );
	}
	/* Check if UTF-16 stream is in big or little endian
	 */
	if( utf16_stream_size >= 2 )
	{
		if( ( utf16_stream[ 0 ] == 0xfe )
		 && ( utf16_stream[ 1 ] == 0xff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf16_stream_index = 2;
		}
		else if( ( utf16_stream[ 0 ] == 0xff )
		      && ( utf16_stream[ 1 ] == 0xfe ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf16_stream_index = 2;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	if( ( utf16_string_size >= 1 )
	 && ( utf16_string[ utf16_string_size - 1 ] == 0 ) )
	{
		utf16_string_size -= 1;
	}
	/* Check if the UTF-16 stream is terminated with zero bytes
	 */
	if( ( utf16_stream_size >= 2 )
	 && ( utf16_stream[ utf16_stream_size - 2 ] == 0 )
	 && ( utf16_stream[ utf16_stream_size - 1 ] == 0 ) )
	{
		utf16_stream_size -= 2;
	}
	while( ( utf16_string_index < utf16_string_size )
	    && ( utf16_stream_index < utf16_stream_size ) )
	{
		/* Convert the UTF-16 character bytes into an Unicode character
		 */
		if( ( byte_order & LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE ) == 0 )
		{
			result = libuna_unicode_character_copy_from_utf16(
			          &utf16_unicode_character,
			          utf16_string,
			          utf16_string_size,
			          &utf16_string_index,
			          error );
		}
		else
		{
			result = libuna_unicode_character_copy_from_ucs2(
			          &utf16_unicode_character,
			          utf16_string,
			          utf16_string_size,
			          &utf16_string_index,
			          error );
		}
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16.",
			 function );

			return( -1 );
		}
		/* Convert the UTF-16 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16_stream(
		     &utf16_stream_unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
                     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 stream.",
			 function );

			return( -1 );
		}
		if( utf16_unicode_character < utf16_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_LESS );
		}
		else if( utf16_unicode_character > utf16_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_GREATER );
		}
	}
	/* Check if both strings were entirely processed
	 */
	if( utf16_string_index < utf16_string_size )
	{
		return( LIBUNA_COMPARE_GREATER );
	}
	else if( utf16_stream_index < utf16_stream_size )
	{
		return( LIBUNA_COMPARE_LESS );
	}
	return( LIBUNA_COMPARE_EQUAL );
}

/* Determines the size of an UTF-16 string from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf32(
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf32";
	size_t utf32_string_index                    = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf32_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	if( utf32_string_size == 0 )
	{
		return( 1 );
	}
	while( utf32_string_index < utf32_string_size )
	{
		/* Convert the UTF-32 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-32.",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character bytes are required
		 */
		if( libuna_unicode_character_size_to_utf16(
		     unicode_character,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		*utf16_string_size += 1;
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_copy_from_utf32(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     libcerror_error_t **error )
{
	static char *function     = "libuna_utf16_string_copy_from_utf32";
	size_t utf16_string_index = 0;

	if( libuna_utf16_string_with_index_copy_from_utf32(
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     utf32_string,
	     utf32_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy UTF-32 string to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_with_index_copy_from_utf32(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_with_index_copy_from_utf32";
	size_t utf32_string_index                    = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing UTF-32 string value.",
		 function );

		return( -1 );
	}
	while( utf32_string_index < utf32_string_size )
	{
		/* Convert the UTF-32 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-32.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 character bytes
		 */
		if( libuna_unicode_character_copy_to_utf16(
		     unicode_character,
		     utf16_string,
		     utf16_string_size,
		     utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ *utf16_string_index ] = 0;

		*utf16_string_index += 1;
	}
	return( 1 );
}

/* Compares an UTF-16 string with an UTF-32 string
 * Returns LIBUNA_COMPARE_LESS, LIBUNA_COMPARE_EQUAL, LIBUNA_COMPARE_GREATER if successful or -1 on error
 */
int libuna_utf16_string_compare_with_utf32(
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     libcerror_error_t **error )
{
	static char *function                              = "libuna_utf16_string_compare_with_utf32";
	size_t utf16_string_index                          = 0;
	size_t utf32_string_index                          = 0;
	libuna_unicode_character_t utf16_unicode_character = 0;
	libuna_unicode_character_t utf32_unicode_character = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing UTF-32 string value.",
		 function );

		return( -1 );
	}
	if( ( utf16_string_size >= 1 )
	 && ( utf16_string[ utf16_string_size - 1 ] == 0 ) )
	{
		utf16_string_size -= 1;
	}
	if( ( utf32_string_size >= 1 )
	 && ( utf32_string[ utf32_string_size - 1 ] == 0 ) )
	{
		utf32_string_size -= 1;
	}
	while( ( utf16_string_index < utf16_string_size )
	    && ( utf32_string_index < utf32_string_size ) )
	{
		/* Convert the UTF-16 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &utf16_unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16.",
			 function );

			return( -1 );
		}
		/* Convert the UTF-32 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &utf32_unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_index,
                     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-32.",
			 function );

			return( -1 );
		}
		if( utf16_unicode_character < utf32_unicode_character )
		{
			return( LIBUNA_COMPARE_LESS );
		}
		else if( utf16_unicode_character > utf32_unicode_character )
		{
			return( LIBUNA_COMPARE_GREATER );
		}
	}
	/* Check if both strings were entirely processed
	 */
	if( utf16_string_index < utf16_string_size )
	{
		return( LIBUNA_COMPARE_GREATER );
	}
	else if( utf32_string_index < utf32_string_size )
	{
		return( LIBUNA_COMPARE_LESS );
	}
	return( LIBUNA_COMPARE_EQUAL );
}

/* Determines the size of an UTF-16 string from an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf32_stream(
     const uint8_t *utf32_stream,
     size_t utf32_stream_size,
     int byte_order,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf32_stream";
	size_t utf32_stream_index                    = 0;
	libuna_unicode_character_t unicode_character = 0;
	int read_byte_order                          = 0;

	if( utf32_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream.",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf32_stream_size % 4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-32 stream value.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	if( utf32_stream_size == 0 )
	{
		return( 1 );
	}
	/* Check if UTF-32 stream is in big or little endian
	 */
	if( utf32_stream_size >= 4 )
	{
		if( ( utf32_stream[ 0 ] == 0x00 )
		 && ( utf32_stream[ 1 ] == 0x00 )
		 && ( utf32_stream[ 2 ] == 0xfe )
		 && ( utf32_stream[ 3 ] == 0xff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf32_stream_index = 4;
		}
		else if( ( utf32_stream[ 0 ] == 0xff )
		      && ( utf32_stream[ 1 ] == 0xfe )
		      && ( utf32_stream[ 2 ] == 0x00 )
		      && ( utf32_stream[ 3 ] == 0x00 ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf32_stream_index = 4;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	while( ( utf32_stream_index + 3 ) < utf32_stream_size )
	{
		/* Convert the UTF-32 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32_stream(
		     &unicode_character,
		     utf32_stream,
		     utf32_stream_size,
		     &utf32_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-32 stream.",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character bytes are required
		 */
		if( libuna_unicode_character_size_to_utf16(
		     unicode_character,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		*utf16_string_size += 1;
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_copy_from_utf32_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *utf32_stream,
     size_t utf32_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function     = "libuna_utf16_string_copy_from_utf32_stream";
	size_t utf16_string_index = 0;

	if( libuna_utf16_string_with_index_copy_from_utf32_stream(
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     utf32_stream,
	     utf32_stream_size,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy UTF-32 stream to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-16 string from an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_with_index_copy_from_utf32_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const uint8_t *utf32_stream,
     size_t utf32_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_with_index_copy_from_utf32_stream";
	size_t utf32_stream_index                    = 0;
	libuna_unicode_character_t unicode_character = 0;
	int read_byte_order                          = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( utf32_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream.",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf32_stream_size == 0 )
	 || ( ( utf32_stream_size % 4 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-32 stream value.",
		 function );

		return( -1 );
	}
	/* Check if UTF-32 stream is in big or little endian
	 */
	if( utf32_stream_size >=4 )
	{
		if( ( utf32_stream[ 0 ] == 0x00 )
		 && ( utf32_stream[ 1 ] == 0x00 )
		 && ( utf32_stream[ 2 ] == 0xfe )
		 && ( utf32_stream[ 3 ] == 0xff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf32_stream_index = 4;
		}
		else if( ( utf32_stream[ 0 ] == 0xff )
		      && ( utf32_stream[ 1 ] == 0xfe )
		      && ( utf32_stream[ 2 ] == 0x00 )
		      && ( utf32_stream[ 3 ] == 0x00 ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf32_stream_index = 4;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	while( ( utf32_stream_index + 3 ) < utf32_stream_size )
	{
		/* Convert the UTF-32 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32_stream(
		     &unicode_character,
		     utf32_stream,
		     utf32_stream_size,
		     &utf32_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-32 stream.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 character bytes
		 */
		if( libuna_unicode_character_copy_to_utf16(
		     unicode_character,
		     utf16_string,
		     utf16_string_size,
		     utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ *utf16_string_index ] = 0;

		*utf16_string_index += 1;
	}
	return( 1 );
}

/* Compares an UTF-16 string with an UTF-32 stream
 * Returns LIBUNA_COMPARE_LESS, LIBUNA_COMPARE_EQUAL, LIBUNA_COMPARE_GREATER if successful or -1 on error
 */
int libuna_utf16_string_compare_with_utf32_stream(
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *utf32_stream,
     size_t utf32_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function                                     = "libuna_utf16_string_compare_with_utf32_stream";
	size_t utf16_string_index                                 = 0;
	size_t utf32_stream_index                                 = 0;
	libuna_unicode_character_t utf16_unicode_character        = 0;
	libuna_unicode_character_t utf32_stream_unicode_character = 0;
	int read_byte_order                                       = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream.",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf32_stream_size == 0 )
	 || ( ( utf32_stream_size % 4 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-32 stream value.",
		 function );

		return( -1 );
	}
	/* Check if UTF-32 stream is in big or little endian
	 */
	if( utf32_stream_size >= 4 )
	{
		if( ( utf32_stream[ 0 ] == 0x00 )
		 && ( utf32_stream[ 1 ] == 0x00 )
		 && ( utf32_stream[ 2 ] == 0xfe )
		 && ( utf32_stream[ 3 ] == 0xff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf32_stream_index = 4;
		}
		else if( ( utf32_stream[ 0 ] == 0xff )
		      && ( utf32_stream[ 1 ] == 0xfe )
		      && ( utf32_stream[ 2 ] == 0x00 )
		      && ( utf32_stream[ 3 ] == 0x00 ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf32_stream_index = 4;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	if( ( utf16_string_size >= 1 )
	 && ( utf16_string[ utf16_string_size - 1 ] == 0 ) )
	{
		utf16_string_size -= 1;
	}
	/* Check if the UTF-32 stream is terminated with zero bytes
	 */
	if( ( utf32_stream_size >= 4 )
	 && ( utf32_stream[ utf32_stream_size - 4 ] == 0 )
	 && ( utf32_stream[ utf32_stream_size - 3 ] == 0 )
	 && ( utf32_stream[ utf32_stream_size - 2 ] == 0 )
	 && ( utf32_stream[ utf32_stream_size - 1 ] == 0 ) )
	{
		utf32_stream_size -= 1;
	}
	while( ( utf16_string_index < utf16_string_size )
	    && ( utf32_stream_index < utf32_stream_size ) )
	{
		/* Convert the UTF-16 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &utf16_unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16.",
			 function );

			return( -1 );
		}
		/* Convert the UTF-32 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32_stream(
		     &utf32_stream_unicode_character,
		     utf32_stream,
		     utf32_stream_size,
		     &utf32_stream_index,
		     byte_order,
                     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-32 stream.",
			 function );

			return( -1 );
		}
		if( utf16_unicode_character < utf32_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_LESS );
		}
		else if( utf16_unicode_character > utf32_stream_unicode_character )
		{
			return( LIBUNA_COMPARE_GREATER );
		}
	}
	/* Check if both strings were entirely processed
	 */
	if( utf16_string_index < utf16_string_size )
	{
		return( LIBUNA_COMPARE_GREATER );
	}
	else if( utf32_stream_index < utf32_stream_size )
	{
		return( LIBUNA_COMPARE_LESS );
	}
	return( LIBUNA_COMPARE_EQUAL );
}

/* Determines the size of an UTF-16 string from a Standard Compression Scheme for Unicode (SCSU) stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_scsu_stream(
     const uint8_t *scsu_stream,
     size_t scsu_stream_size,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	uint32_t scsu_dynamic_window_positions[ 8 ] = {
		0x0080, 0x00c0, 0x0400, 0x0600, 0x0900, 0x3040, 0x30a0, 0xff00 };

	static char *function                        = "libuna_utf8_string_size_from_scsu_stream";
	libuna_unicode_character_t unicode_character = 0;
	size_t scsu_stream_index                     = 0;
	uint32_t scsu_window_position                = 0;
	uint8_t byte_value1                          = 0;
	uint8_t byte_value2                          = 0;
	uint8_t byte_value3                          = 0;
	uint8_t dynamic_window_position_index        = 0;
	uint8_t in_unicode_mode                      = 0;
	uint8_t unicode_character_set                = 0;

	if( scsu_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid SCSU stream.",
		 function );

		return( -1 );
	}
	if( scsu_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid SCSU stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	if( scsu_stream_size == 0 )
	{
		return( 1 );
	}
	while( scsu_stream_index < scsu_stream_size )
	{
		unicode_character_set = 0;

		if( scsu_stream_index >= scsu_stream_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: SCSU stream too small.",
			 function );

			return( -1 );
		}
		byte_value1 = scsu_stream[ scsu_stream_index++ ];

		if( in_unicode_mode != 0 )
		{
			if( ( byte_value1 <= 0xdf )
			 || ( byte_value1 >= 0xf3 ) )
			{
				if( scsu_stream_index >= scsu_stream_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];

				unicode_character   = byte_value1;
				unicode_character <<= 8;
				unicode_character  |= byte_value2;

				unicode_character_set = 1;
			}
			/* UCn tags
			 */
			else if( ( byte_value1 >= 0xe0 )
			      && ( byte_value1 <= 0xe7 ) )
			{
				dynamic_window_position_index = byte_value1 - 0xe0;

				in_unicode_mode = 0;
			}
			/* UDn tags
			 */
			else if( ( byte_value1 >= 0xe8 )
			      && ( byte_value1 <= 0xef ) )
			{
				if( scsu_stream_index >= scsu_stream_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];

				dynamic_window_position_index = byte_value1 - 0xe8;
				scsu_window_position          = libuna_scsu_window_offset_table[ byte_value2 ];

				scsu_dynamic_window_positions[ dynamic_window_position_index ] = scsu_window_position;

				in_unicode_mode = 0;
			}
			/* UQU tag
			 */
			else if( byte_value1 == 0xf0 )
			{
				if( ( scsu_stream_size < 2 )
				 || ( scsu_stream_index > ( scsu_stream_size - 2 ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];
				byte_value3 = scsu_stream[ scsu_stream_index++ ];

				unicode_character   = byte_value2;
				unicode_character <<= 8;
				unicode_character  |= byte_value3;

				unicode_character_set = 1;
			}
			/* UDX tag
			 */
			else if( byte_value1 == 0xf1 )
			{
				if( ( scsu_stream_size < 2 )
				 || ( scsu_stream_index > ( scsu_stream_size - 2 ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];
				byte_value3 = scsu_stream[ scsu_stream_index++ ];

				dynamic_window_position_index = byte_value2 >> 5;
				scsu_window_position          = byte_value2 & 0x1f;
				scsu_window_position        <<= 8;
				scsu_window_position         |= byte_value3;
				scsu_window_position        <<= 7;
				scsu_window_position         += 0x00010000UL;

				scsu_dynamic_window_positions[ dynamic_window_position_index ] = scsu_window_position;

				in_unicode_mode = 0;
			}
		}
		else
		{
			if( ( byte_value1 == 0x00 )
			 || ( byte_value1 == 0x09 )
			 || ( byte_value1 == 0x0a )
			 || ( byte_value1 == 0x0c )
			 || ( byte_value1 == 0x0d )
			 || ( ( byte_value1 >= 0x20 )
			  &&  ( byte_value1 <= 0x7f ) ) )
			{
				unicode_character = byte_value1;

				unicode_character_set = 1;
			}
			/* SQn tags
			 */
			else if( ( byte_value1 >= 0x01 )
			      && ( byte_value1 <= 0x08 ) )
			{
				if( scsu_stream_index >= scsu_stream_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];

				unicode_character = byte_value2;

				if( byte_value2 < 0x80 )
				{
					unicode_character += libuna_scsu_static_window_positions[ byte_value1 - 0x01 ];
				}
				else
				{
					unicode_character -= 0x80;
					unicode_character += scsu_dynamic_window_positions[ byte_value1 - 0x01 ];
				}
				unicode_character_set = 1;
			}
			/* SDX tag
			 */
			else if( byte_value1 == 0x0b )
			{
				if( ( scsu_stream_size < 2 )
				 || ( scsu_stream_index > ( scsu_stream_size - 2 ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];
				byte_value3 = scsu_stream[ scsu_stream_index++ ];

				dynamic_window_position_index = byte_value2 >> 5;
				scsu_window_position          = byte_value2 & 0x1f;
				scsu_window_position        <<= 8;
				scsu_window_position         |= byte_value3;
				scsu_window_position        <<= 7;
				scsu_window_position         += 0x00010000UL;

				scsu_dynamic_window_positions[ dynamic_window_position_index ] = scsu_window_position;
			}
			/* SQU tag
			 */
			else if( byte_value1 == 0x0e )
			{
				if( ( scsu_stream_size < 2 )
				 || ( scsu_stream_index > ( scsu_stream_size - 2 ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];
				byte_value3 = scsu_stream[ scsu_stream_index++ ];

				unicode_character   = byte_value2;
				unicode_character <<= 8;
				unicode_character  |= byte_value3;

				unicode_character_set = 1;
			}
			/* SCU tag
			 */
			else if( byte_value1 == 0x0f )
			{
				in_unicode_mode = 1;
			}
			/* SCn tags
			 */
			else if( ( byte_value1 >= 0x10 )
			      && ( byte_value1 <= 0x17 ) )
			{
				dynamic_window_position_index = byte_value1 - 0x10;
			}
			/* SDn tags
			 */
			else if( ( byte_value1 >= 0x18 )
			      && ( byte_value1 <= 0x1f ) )
			{
				if( scsu_stream_index >= scsu_stream_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];

				dynamic_window_position_index = byte_value1 - 0x18;
				scsu_window_position          = libuna_scsu_window_offset_table[ byte_value2 ];

				scsu_dynamic_window_positions[ dynamic_window_position_index ] = scsu_window_position;
			}
			else if( byte_value1 >= 0x80 )
			{
				unicode_character  = byte_value1 - 0x80;
				unicode_character += scsu_dynamic_window_positions[ dynamic_window_position_index ];

				unicode_character_set = 1;
			}
		}
		if( unicode_character_set != 0 )
		{
			/* Determine how many UTF-16 character bytes are required
			 */
			if( libuna_unicode_character_size_to_utf16(
			     unicode_character,
			     utf16_string_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_CONVERSION,
				 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
				 "%s: unable to unable to determine size of Unicode character in UTF-16.",
				 function );

				return( -1 );
			}
			if( unicode_character == 0 )
			{
				break;
			}
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		*utf16_string_size += 1;
	}
	return( 1 );
}

/* Copies an UTF-16 string from a Standard Compression Scheme for Unicode (SCSU) stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_copy_from_scsu_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     const uint8_t *scsu_stream,
     size_t scsu_stream_size,
     libcerror_error_t **error )
{
	static char *function     = "libuna_utf16_string_copy_from_scsu_stream";
	size_t utf16_string_index = 0;

	if( libuna_utf16_string_with_index_copy_from_scsu_stream(
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     scsu_stream,
	     scsu_stream_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to SCSU stream to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-16 string from a Standard Compression Scheme for Unicode (SCSU) stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_with_index_copy_from_scsu_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const uint8_t *scsu_stream,
     size_t scsu_stream_size,
     libcerror_error_t **error )
{
	uint32_t scsu_dynamic_window_positions[ 8 ] = {
		0x0080, 0x00c0, 0x0400, 0x0600, 0x0900, 0x3040, 0x30a0, 0xff00 };

	static char *function                        = "libuna_utf16_string_with_index_copy_from_scsu_stream";
	libuna_unicode_character_t unicode_character = 0;
	size_t scsu_stream_index                     = 0;
	uint32_t scsu_window_position                = 0;
	uint8_t byte_value1                          = 0;
	uint8_t byte_value2                          = 0;
	uint8_t byte_value3                          = 0;
	uint8_t dynamic_window_position_index        = 0;
	uint8_t in_unicode_mode                      = 0;
	uint8_t unicode_character_set                = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( scsu_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid SCSU stream.",
		 function );

		return( -1 );
	}
	if( scsu_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid SCSU stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( scsu_stream_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: missing SCSU stream value.",
		 function );

		return( -1 );
	}
	while( scsu_stream_index < scsu_stream_size )
	{
		unicode_character_set = 0;

		if( scsu_stream_index >= scsu_stream_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: SCSU stream too small.",
			 function );

			return( -1 );
		}
		byte_value1 = scsu_stream[ scsu_stream_index++ ];

		if( in_unicode_mode != 0 )
		{
			if( ( byte_value1 <= 0xdf )
			 || ( byte_value1 >= 0xf3 ) )
			{
				if( scsu_stream_index >= scsu_stream_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];

				unicode_character   = byte_value1;
				unicode_character <<= 8;
				unicode_character  |= byte_value2;

				unicode_character_set = 1;
			}
			/* UCn tags
			 */
			else if( ( byte_value1 >= 0xe0 )
			      && ( byte_value1 <= 0xe7 ) )
			{
				dynamic_window_position_index = byte_value1 - 0xe0;

				in_unicode_mode = 0;
			}
			/* UDn tags
			 */
			else if( ( byte_value1 >= 0xe8 )
			      && ( byte_value1 <= 0xef ) )
			{
				if( scsu_stream_index >= scsu_stream_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];

				dynamic_window_position_index = byte_value1 - 0xe8;
				scsu_window_position          = libuna_scsu_window_offset_table[ byte_value2 ];

				scsu_dynamic_window_positions[ dynamic_window_position_index ] = scsu_window_position;

				in_unicode_mode = 0;
			}
			/* UQU tag
			 */
			else if( byte_value1 == 0xf0 )
			{
				if( ( scsu_stream_size < 2 )
				 || ( scsu_stream_index > ( scsu_stream_size - 2 ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];
				byte_value3 = scsu_stream[ scsu_stream_index++ ];

				unicode_character   = byte_value2;
				unicode_character <<= 8;
				unicode_character  |= byte_value3;

				unicode_character_set = 1;
			}
			/* UDX tag
			 */
			else if( byte_value1 == 0xf1 )
			{
				if( ( scsu_stream_size < 2 )
				 || ( scsu_stream_index > ( scsu_stream_size - 2 ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];
				byte_value3 = scsu_stream[ scsu_stream_index++ ];

				dynamic_window_position_index = byte_value2 >> 5;
				scsu_window_position          = byte_value2 & 0x1f;
				scsu_window_position        <<= 8;
				scsu_window_position         |= byte_value3;
				scsu_window_position        <<= 7;
				scsu_window_position         += 0x00010000UL;

				scsu_dynamic_window_positions[ dynamic_window_position_index ] = scsu_window_position;

				in_unicode_mode = 0;
			}
		}
		else
		{
			if( ( byte_value1 == 0x00 )
			 || ( byte_value1 == 0x09 )
			 || ( byte_value1 == 0x0a )
			 || ( byte_value1 == 0x0c )
			 || ( byte_value1 == 0x0d )
			 || ( ( byte_value1 >= 0x20 )
			  &&  ( byte_value1 <= 0x7f ) ) )
			{
				unicode_character = byte_value1;

				unicode_character_set = 1;
			}
			/* SQn tags
			 */
			else if( ( byte_value1 >= 0x01 )
			      && ( byte_value1 <= 0x08 ) )
			{
				if( scsu_stream_index >= scsu_stream_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];

				unicode_character = byte_value2;

				if( byte_value2 < 0x80 )
				{
					unicode_character += libuna_scsu_static_window_positions[ byte_value1 - 0x01 ];
				}
				else
				{
					unicode_character -= 0x80;
					unicode_character += scsu_dynamic_window_positions[ byte_value1 - 0x01 ];
				}
				unicode_character_set = 1;
			}
			/* SDX tag
			 */
			else if( byte_value1 == 0x0b )
			{
				if( ( scsu_stream_size < 2 )
				 || ( scsu_stream_index > ( scsu_stream_size - 2 ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];
				byte_value3 = scsu_stream[ scsu_stream_index++ ];

				dynamic_window_position_index = byte_value2 >> 5;
				scsu_window_position          = byte_value2 & 0x1f;
				scsu_window_position        <<= 8;
				scsu_window_position         |= byte_value3;
				scsu_window_position        <<= 7;
				scsu_window_position         += 0x00010000UL;

				scsu_dynamic_window_positions[ dynamic_window_position_index ] = scsu_window_position;
			}
			/* SQU tag
			 */
			else if( byte_value1 == 0x0e )
			{
				if( ( scsu_stream_size < 2 )
				 || ( scsu_stream_index > ( scsu_stream_size - 2 ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];
				byte_value3 = scsu_stream[ scsu_stream_index++ ];

				unicode_character   = byte_value2;
				unicode_character <<= 8;
				unicode_character  |= byte_value3;

				unicode_character_set = 1;
			}
			/* SCU tag
			 */
			else if( byte_value1 == 0x0f )
			{
				in_unicode_mode = 1;
			}
			/* SCn tags
			 */
			else if( ( byte_value1 >= 0x10 )
			      && ( byte_value1 <= 0x17 ) )
			{
				dynamic_window_position_index = byte_value1 - 0x10;
			}
			/* SDn tags
			 */
			else if( ( byte_value1 >= 0x18 )
			      && ( byte_value1 <= 0x1f ) )
			{
				if( scsu_stream_index >= scsu_stream_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: SCSU stream too small.",
					 function );

					return( -1 );
				}
				byte_value2 = scsu_stream[ scsu_stream_index++ ];

				dynamic_window_position_index = byte_value1 - 0x18;
				scsu_window_position          = libuna_scsu_window_offset_table[ byte_value2 ];

				scsu_dynamic_window_positions[ dynamic_window_position_index ] = scsu_window_position;
			}
			else if( byte_value1 >= 0x80 )
			{
				unicode_character  = byte_value1 - 0x80;
				unicode_character += scsu_dynamic_window_positions[ dynamic_window_position_index ];

				unicode_character_set = 1;
			}
		}
		if( unicode_character_set != 0 )
		{
			/* Convert the Unicode character into UTF-16 character bytes
			 */
			if( libuna_unicode_character_copy_to_utf16(
			     unicode_character,
			     utf16_string,
			     utf16_string_size,
			     utf16_string_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_CONVERSION,
				 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
				 "%s: unable to copy Unicode character to UTF-16.",
				 function );

				return( -1 );
			}
			if( unicode_character == 0 )
			{
				break;
			}
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ *utf16_string_index ] = 0;

		*utf16_string_index += 1;
	}
	return( 1 );
}

