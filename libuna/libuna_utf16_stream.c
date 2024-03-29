/*
 * UTF-16 stream functions
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
#include "libuna_types.h"
#include "libuna_unicode_character.h"
#include "libuna_utf16_stream.h"

/* Copies an UTF-16 stream byte order mark (BOM)
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_copy_byte_order_mark(
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     size_t *utf16_stream_index,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function = "libuna_utf16_stream_copy_byte_order_mark";

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
	if( utf16_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream index.",
		 function );

		return( -1 );
	}
	if( ( *utf16_stream_index + 2 ) > utf16_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 stream too small.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		utf16_stream[ *utf16_stream_index     ] = 0xfe;
		utf16_stream[ *utf16_stream_index + 1 ] = 0xff;
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		utf16_stream[ *utf16_stream_index     ] = 0xff;
		utf16_stream[ *utf16_stream_index + 1 ] = 0xfe;
	}
	*utf16_stream_index += 2;

	return( 1 );
}

/* Determines the size of an UTF-16 stream from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_size_from_utf8(
     const libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf16_stream_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_size_from_utf8";
	libuna_unicode_character_t unicode_character = 0;
	size_t safe_utf16_stream_size                = 0;
	size_t utf8_string_index                     = 0;

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
	if( utf16_stream_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream size.",
		 function );

		return( -1 );
	}
	/* Add the byte order mark
	 */
	safe_utf16_stream_size = 1;

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
		     &safe_utf16_stream_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Convert the number of characters into bytes
	 */
	*utf16_stream_size = safe_utf16_stream_size * 2;

	return( 1 );
}

/* Copies an UTF-16 stream from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_copy_from_utf8(
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     const libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_copy_from_utf8";
	libuna_unicode_character_t unicode_character = 0;
	size_t utf16_stream_index                    = 0;
	size_t utf8_string_index                     = 0;

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
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
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
	if( libuna_utf16_stream_copy_byte_order_mark(
	     utf16_stream,
	     utf16_stream_size,
	     &utf16_stream_index,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
		 "%s: unable to copy UTF-16 byte order mark.",
		 function );

		return( -1 );
	}
	while( utf8_string_index < utf8_string_size )
	{
		/* Convert the UTF-8 string bytes into an Unicode character
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
			 "%s: unable to copy Unicode character from UTF-8 string.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 stream bytes
		 */
		if( libuna_unicode_character_copy_to_utf16_stream(
		     unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16 stream.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	return( 1 );
}

/* Determines the size of an UTF-16 stream from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_size_from_utf16(
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_stream_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_size_from_utf16";
	libuna_unicode_character_t unicode_character = 0;
	size_t safe_utf16_stream_size                = 0;
	size_t utf16_string_index                    = 0;

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
	if( utf16_stream_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream size.",
		 function );

		return( -1 );
	}
	/* Add the byte order mark
	 */
	safe_utf16_stream_size = 1;

	while( utf16_string_index < utf16_string_size )
	{
		/* Convert the UTF-16 character bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16.",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character bytes are required
		 */
		if( libuna_unicode_character_size_to_utf16(
		     unicode_character,
		     &safe_utf16_stream_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Convert the number of characters into bytes
	 */
	*utf16_stream_size = safe_utf16_stream_size * 2;

	return( 1 );
}

/* Copies an UTF-16 stream from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_copy_from_utf16(
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_copy_from_utf16";
	libuna_unicode_character_t unicode_character = 0;
	size_t utf16_stream_index                    = 0;
	size_t utf16_string_index                    = 0;

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
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
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
	if( libuna_utf16_stream_copy_byte_order_mark(
	     utf16_stream,
	     utf16_stream_size,
	     &utf16_stream_index,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
		 "%s: unable to copy UTF-16 byte order mark.",
		 function );

		return( -1 );
	}
	while( utf16_string_index < utf16_string_size )
	{
		/* Convert the UTF-16 string bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 string.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 stream bytes
		 */
		if( libuna_unicode_character_copy_to_utf16_stream(
		     unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16 stream.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	return( 1 );
}

/* Determines the size of an UTF-16 stream from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_size_from_utf32(
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf16_stream_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_size_from_utf32";
	libuna_unicode_character_t unicode_character = 0;
	size_t safe_utf16_stream_size                = 0;
	size_t utf32_string_index                    = 0;

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
	if( utf16_stream_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream size.",
		 function );

		return( -1 );
	}
	/* Add the byte order mark
	 */
	safe_utf16_stream_size += 1;

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
		     &safe_utf16_stream_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Convert the number of characters into bytes
	 */
	*utf16_stream_size = safe_utf16_stream_size * 2;

	return( 1 );
}

/* Copies an UTF-16 stream from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_copy_from_utf32(
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_copy_from_utf32";
	libuna_unicode_character_t unicode_character = 0;
	size_t utf16_stream_index                    = 0;
	size_t utf32_string_index                    = 0;

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
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
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
	if( libuna_utf16_stream_copy_byte_order_mark(
	     utf16_stream,
	     utf16_stream_size,
	     &utf16_stream_index,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
		 "%s: unable to copy UTF-16 byte order mark.",
		 function );

		return( -1 );
	}
	while( utf32_string_index < utf32_string_size )
	{
		/* Convert the UTF-32 string bytes into an Unicode character
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
			 "%s: unable to copy Unicode character from UTF-32 string.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 stream bytes
		 */
		if( libuna_unicode_character_copy_to_utf16_stream(
		     unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16 stream.",
			 function );

			return( -1 );
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	return( 1 );
}

