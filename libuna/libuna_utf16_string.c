/*
 * UTF-16 string functions
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
#include <types.h>

#include <liberror.h>

#include "libuna_definitions.h"
#include "libuna_types.h"
#include "libuna_unicode_character.h"
#include "libuna_utf16_string.h"

/* Determines the size of a UTF-16 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_byte_stream(
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int codepage,
     size_t *utf16_string_size,
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_byte_stream";
	size_t byte_stream_iterator                  = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( byte_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	/* Check if the byte stream is terminated with a zero byte
	 */
	if( byte_stream[ byte_stream_size - 1 ] != 0 )
	{
		*utf16_string_size += 1;
	}
	while( byte_stream_iterator < byte_stream_size )
	{
		/* Convert the byte stream bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_byte_stream(
		     &unicode_character,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_iterator,
		     codepage,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
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
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_copy_from_byte_stream";
	size_t utf16_string_iterator                 = 0;
	size_t byte_stream_iterator                  = 0;
	libuna_unicode_character_t unicode_character = 0;
	uint8_t zero_byte                            = 0;

	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	/* Check if the byte stream is terminated with zero bytes
	 */
	if( byte_stream[ byte_stream_size - 1 ] != 0 )
	{
		zero_byte = 1;
	}
	while( byte_stream_iterator < byte_stream_size )
	{
		/* Convert the byte stream bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_byte_stream(
		     &unicode_character,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_iterator,
		     codepage,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
		     &utf16_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
	}
	if( zero_byte != 0 )
	{
		if( utf16_string_iterator >= utf16_string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ utf16_string_iterator++ ] = 0;
	}
	return( 1 );
}

/* Determines the size of a UTF-16 string from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf8(
     const libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf16_string_size,
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf8";
	size_t utf8_string_iterator                  = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf8_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	while( utf8_string_iterator < utf8_string_size )
	{
		/* Convert the UTF-8 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
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
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_copy_from_utf8";
	size_t utf8_string_iterator                  = 0;
	size_t utf16_string_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	while( utf8_string_iterator < utf8_string_size )
	{
		/* Convert the UTF-8 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
		     &utf16_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the size of a UTF-16 string from a UTF-8 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf8_stream(
     const uint8_t *utf8_stream,
     size_t utf8_stream_size,
     size_t *utf16_string_size,
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf8_stream";
	size_t utf8_stream_iterator                  = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf8_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 stream.",
		 function );

		return( -1 );
	}
	if( utf8_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_stream_size < 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-8 stream bytes.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	/* Check if UTF-8 stream starts with a byte order mark (BOM)
	 */
	if( utf8_stream_size >= 3 )
	{
		if( ( utf8_stream[ 0 ] == 0x0ef )
		 && ( utf8_stream[ 1 ] == 0x0bb )
		 && ( utf8_stream[ 2 ] == 0x0bf ) )
		{
			utf8_stream_iterator += 3;
		}
	}
	/* Check if the UTF-8 stream is terminated with a zero byte
	 */
	if( utf8_stream[ utf8_stream_size - 1 ] != 0 )
	{
		*utf16_string_size += 1;
	}
	while( utf8_stream_iterator < utf8_stream_size )
	{
		/* Convert the UTF-8 stream bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_stream,
		     utf8_stream_size,
		     &utf8_stream_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
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
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_copy_from_utf8_stream";
	size_t utf16_string_iterator                 = 0;
	size_t utf8_stream_iterator                  = 0;
	libuna_unicode_character_t unicode_character = 0;
	uint8_t zero_byte                            = 0;

	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 stream.",
		 function );

		return( -1 );
	}
	if( utf8_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_stream_size < 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-8 stream bytes.",
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
			utf8_stream_iterator += 3;
		}
	}
	/* Check if the UTF-8 stream is terminated with zero bytes
	 */
	if( utf8_stream[ utf8_stream_size - 1 ] != 0 )
	{
		zero_byte = 1;
	}
	while( utf8_stream_iterator < utf8_stream_size )
	{
		/* Convert the UTF-8 stream bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_stream,
		     utf8_stream_size,
		     &utf8_stream_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
		     &utf16_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
	}
	if( zero_byte != 0 )
	{
		if( utf16_string_iterator >= utf16_string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ utf16_string_iterator++ ] = 0;
	}
	return( 1 );
}

/* Determines the size of a UTF-16 string from a UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf16_stream(
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     uint8_t byte_order,
     size_t *utf16_string_size,
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf16_stream";
	size_t utf16_stream_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;
	uint8_t read_byte_order                      = 0;

	if( utf16_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size < 2 )
	 || ( ( utf16_stream_size % 2 ) != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream bytes.",
		 function );

		return( -1 );
	}
	if( ( byte_order != 0 )
	 && ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	/* Check if UTF-16 stream is in big or little endian
	 */
	if( ( utf16_stream[ 0 ] == 0x0ff )
	 && ( utf16_stream[ 1 ] == 0x0fe ) )
	{
		read_byte_order       = LIBUNA_ENDIAN_LITTLE;
		utf16_stream_iterator = 2;
	}
	else if( ( utf16_stream[ 0 ] == 0x0fe )
	      && ( utf16_stream[ 1 ] == 0x0ff ) )
	{
		read_byte_order       = LIBUNA_ENDIAN_BIG;
		utf16_stream_iterator = 2;
	}
	else
	{
		if( ( utf16_stream[ 0 ] == 0 )
		 && ( utf16_stream[ 1 ] != 0 ) )
		{
			read_byte_order = LIBUNA_ENDIAN_BIG;
		}
		else if( ( utf16_stream[ 0 ] != 0 )
		      && ( utf16_stream[ 1 ] == 0 ) )
		{
			read_byte_order = LIBUNA_ENDIAN_LITTLE;
		}
		else if( byte_order == 0 )
		{
			read_byte_order = LIBUNA_ENDIAN_BIG;
		}
		else
		{
			read_byte_order = byte_order;
		}
		utf16_stream_iterator = 0;
	}
	/* Check if the UTF-16 stream is terminated with zero bytes
	 */
	if( ( utf16_stream[ utf16_stream_size - 2 ] != 0 )
	 || ( utf16_stream[ utf16_stream_size - 1 ] != 0 ) )
	{
		*utf16_string_size += 1;
	}
	while( ( utf16_stream_iterator + 1 ) < utf16_stream_size )
	{
		/* Convert the UTF-16 stream bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16_stream(
		     &unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_iterator,
		     read_byte_order,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 stream.",
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
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
	}
	if( utf16_stream_iterator != utf16_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream bytes.",
		 function );

		return( -1 );
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
     uint8_t byte_order,
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_copy_from_utf16_stream";
	size_t utf16_string_iterator                 = 0;
	size_t utf16_stream_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;
	uint8_t read_byte_order                      = 0;
	uint8_t zero_byte                            = 0;

	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size < 2 )
	 || ( ( utf16_stream_size % 2 ) != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream bytes.",
		 function );

		return( -1 );
	}
	if( ( byte_order != 0 )
	 && ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	/* Check if UTF-16 stream is in big or little endian
	 */
	if( ( utf16_stream[ 0 ] == 0x0ff )
	 && ( utf16_stream[ 1 ] == 0x0fe ) )
	{
		read_byte_order       = LIBUNA_ENDIAN_LITTLE;
		utf16_stream_iterator = 2;
	}
	else if( ( utf16_stream[ 0 ] == 0x0fe )
	      && ( utf16_stream[ 1 ] == 0x0ff ) )
	{
		read_byte_order       = LIBUNA_ENDIAN_BIG;
		utf16_stream_iterator = 2;
	}
	else
	{
		if( ( utf16_stream[ 0 ] == 0 )
		 && ( utf16_stream[ 1 ] != 0 ) )
		{
			read_byte_order = LIBUNA_ENDIAN_BIG;
		}
		else if( ( utf16_stream[ 0 ] != 0 )
		      && ( utf16_stream[ 1 ] == 0 ) )
		{
			read_byte_order = LIBUNA_ENDIAN_LITTLE;
		}
		else if( byte_order == 0 )
		{
			read_byte_order = LIBUNA_ENDIAN_BIG;
		}
		else
		{
			read_byte_order = byte_order;
		}
		utf16_stream_iterator = 0;
	}
	/* Check if the UTF-16 stream is terminated with zero bytes
	 */
	if( ( utf16_stream[ utf16_stream_size - 2 ] != 0 )
	 || ( utf16_stream[ utf16_stream_size - 1 ] != 0 ) )
	{
		zero_byte = 1;
	}
	while( ( utf16_stream_iterator + 1 ) < utf16_stream_size )
	{
		/* Convert the UTF-16 stream bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16_stream(
		     &unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_iterator,
		     read_byte_order,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 stream.",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 character bytes
		 */
		if( libuna_unicode_character_copy_to_utf16(
		     unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
	}
	if( utf16_stream_iterator != utf16_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream bytes.",
		 function );

		return( -1 );
	}
	if( zero_byte != 0 )
	{
		if( utf16_string_iterator >= utf16_string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ utf16_string_iterator++ ] = 0;
	}
	return( 1 );
}

/* Determines the size of a UTF-16 string from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf32(
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf16_string_size,
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf32";
	size_t utf32_string_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf32_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	while( utf32_string_iterator < utf32_string_size )
	{
		/* Convert the UTF-32 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
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
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_copy_from_utf32";
	size_t utf16_string_iterator                 = 0;
	size_t utf32_string_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	while( utf32_string_iterator < utf32_string_size )
	{
		/* Convert the UTF-32 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
		     &utf16_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the size of a UTF-16 string from a UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_string_size_from_utf32_stream(
     const uint8_t *utf32_stream,
     size_t utf32_stream_size,
     uint8_t byte_order,
     size_t *utf16_string_size,
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_size_from_utf32_stream";
	size_t utf32_stream_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;
	uint8_t read_byte_order                      = 0;

	if( utf32_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream.",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf32_stream_size < 4 )
	 || ( ( utf32_stream_size % 4 ) != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-32 stream bytes.",
		 function );

		return( -1 );
	}
	if( ( byte_order != 0 )
	 && ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = 0;

	/* Check if UTF-32 stream is in big or little endian
	 */
	if( ( utf32_stream[ 0 ] == 0x00 )
	 && ( utf32_stream[ 1 ] == 0x00 )
	 && ( utf32_stream[ 2 ] == 0xfe )
	 && ( utf32_stream[ 3 ] == 0xff ) )
	{
		read_byte_order       = LIBUNA_ENDIAN_BIG;
		utf32_stream_iterator = 4;
	}
	else if( ( utf32_stream[ 0 ] == 0xff )
	      && ( utf32_stream[ 1 ] == 0xfe )
	      && ( utf32_stream[ 2 ] == 0x00 )
	      && ( utf32_stream[ 3 ] == 0x00 ) )
	{
		read_byte_order       = LIBUNA_ENDIAN_LITTLE;
		utf32_stream_iterator = 4;
	}
	else
	{
		if( ( utf32_stream[ 0 ] == 0 )
		 && ( utf32_stream[ 1 ] == 0 )
		 && ( utf32_stream[ 2 ] == 0 )
		 && ( utf32_stream[ 3 ] != 0 ) )
		{
			read_byte_order = LIBUNA_ENDIAN_BIG;
		}
		else if( ( utf32_stream[ 0 ] != 0 )
		      && ( utf32_stream[ 1 ] == 0 )
		      && ( utf32_stream[ 2 ] == 0 )
		      && ( utf32_stream[ 3 ] == 0 ) )
		{
			read_byte_order = LIBUNA_ENDIAN_LITTLE;
		}
		else if( byte_order == 0 )
		{
			read_byte_order = LIBUNA_ENDIAN_BIG;
		}
		else
		{
			read_byte_order = byte_order;
		}
		utf32_stream_iterator = 0;
	}
	/* Check if the UTF-32 stream is terminated with zero bytes
	 */
	if( ( utf32_stream[ utf32_stream_size - 4 ] != 0 )
	 || ( utf32_stream[ utf32_stream_size - 3 ] != 0 )
	 || ( utf32_stream[ utf32_stream_size - 2 ] != 0 )
	 || ( utf32_stream[ utf32_stream_size - 1 ] != 0 ) )
	{
		*utf16_string_size += 1;
	}
	while( ( utf32_stream_iterator + 1 ) < utf32_stream_size )
	{
		/* Convert the UTF-32 stream bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32_stream(
		     &unicode_character,
		     utf32_stream,
		     utf32_stream_size,
		     &utf32_stream_iterator,
		     read_byte_order,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to unable to determine size of Unicode character in UTF-16.",
			 function );

			return( -1 );
		}
	}
	if( utf32_stream_iterator != utf32_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-32 stream bytes.",
		 function );

		return( -1 );
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
     uint8_t byte_order,
     liberror_error_t **error )
{
	static char *function                        = "libuna_utf16_string_copy_from_utf32_stream";
	size_t utf16_string_iterator                 = 0;
	size_t utf32_stream_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;
	uint8_t read_byte_order                      = 0;
	uint8_t zero_byte                            = 0;

	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream.",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf32_stream_size < 4 )
	 || ( ( utf32_stream_size % 4 ) != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-32 stream bytes.",
		 function );

		return( -1 );
	}
	if( ( byte_order != 0 )
	 && ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	/* Check if UTF-32 stream is in big or little endian
	 */
	if( ( utf32_stream[ 0 ] == 0x00 )
	 && ( utf32_stream[ 1 ] == 0x00 )
	 && ( utf32_stream[ 2 ] == 0xfe )
	 && ( utf32_stream[ 3 ] == 0xff ) )
	{
		read_byte_order       = LIBUNA_ENDIAN_BIG;
		utf32_stream_iterator = 4;
	}
	else if( ( utf32_stream[ 0 ] == 0xff )
	      && ( utf32_stream[ 1 ] == 0xfe )
	      && ( utf32_stream[ 2 ] == 0x00 )
	      && ( utf32_stream[ 3 ] == 0x00 ) )
	{
		read_byte_order       = LIBUNA_ENDIAN_LITTLE;
		utf32_stream_iterator = 4;
	}
	else
	{
		if( ( utf32_stream[ 0 ] == 0 )
		 && ( utf32_stream[ 1 ] == 0 )
		 && ( utf32_stream[ 2 ] == 0 )
		 && ( utf32_stream[ 3 ] != 0 ) )
		{
			read_byte_order = LIBUNA_ENDIAN_BIG;
		}
		else if( ( utf32_stream[ 0 ] != 0 )
		      && ( utf32_stream[ 1 ] == 0 )
		      && ( utf32_stream[ 2 ] == 0 )
		      && ( utf32_stream[ 3 ] == 0 ) )
		{
			read_byte_order = LIBUNA_ENDIAN_LITTLE;
		}
		else if( byte_order == 0 )
		{
			read_byte_order = LIBUNA_ENDIAN_BIG;
		}
		else
		{
			read_byte_order = byte_order;
		}
		utf32_stream_iterator = 0;
	}
	/* Check if the UTF-32 stream is terminated with zero bytes
	 */
	if( ( utf32_stream[ utf32_stream_size - 4 ] != 0 )
	 || ( utf32_stream[ utf32_stream_size - 3 ] != 0 )
	 || ( utf32_stream[ utf32_stream_size - 2 ] != 0 )
	 || ( utf32_stream[ utf32_stream_size - 1 ] != 0 ) )
	{
		zero_byte = 1;
	}
	while( ( utf32_stream_iterator + 1 ) < utf32_stream_size )
	{
		/* Convert the UTF-32 stream bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32_stream(
		     &unicode_character,
		     utf32_stream,
		     utf32_stream_size,
		     &utf32_stream_iterator,
		     read_byte_order,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
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
		     &utf16_string_iterator,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character to UTF-16.",
			 function );

			return( -1 );
		}
	}
	if( utf32_stream_iterator != utf32_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-32 stream bytes.",
		 function );

		return( -1 );
	}
	if( zero_byte != 0 )
	{
		if( utf16_string_iterator >= utf16_string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ utf16_string_iterator++ ] = 0;
	}
	return( 1 );
}

