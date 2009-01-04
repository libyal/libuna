/*
 * Byte stream functions
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
#include <notify.h>
#include <types.h>

#include "libuna_definitions.h"
#include "libuna_error.h"
#include "libuna_unicode_character.h"
#include "libuna_byte_stream.h"

/* Determines the size of a byte stream from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
ssize_t libuna_byte_stream_size_from_utf8(
         libuna_utf8_character_t *utf8_string,
         size_t utf8_string_size,
         int codepage )
{
	static char *function                        = "libuna_byte_stream_size_from_utf8";
	size_t utf8_string_iterator                  = 0;
	ssize_t byte_stream_size                     = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf8_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 string.\n",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-8 string size value exceeds maximum.\n",
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
		     &utf8_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-8.\n",
			 function );

			return( -1 );
		}
		/* Determine how many byte stream character bytes are required
		 */
		byte_stream_size += libuna_unicode_character_size_to_byte_stream(
		                     unicode_character,
		                     codepage );
	}
	return( byte_stream_size );
}

/* Copies a byte stream from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuna_byte_stream_copy_from_utf8(
     uint8_t *byte_stream,
     size_t byte_stream_size,
     int codepage,
     libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size )
{
	static char *function                        = "libuna_byte_stream_copy_from_utf8";
	size_t utf8_string_iterator                  = 0;
	size_t byte_stream_iterator                  = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( byte_stream == NULL )
	{
		notify_warning_printf( "%s: invalid byte stream.\n",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid byte stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 string.\n",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-8 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	while( utf8_string_iterator < utf8_string_size )
	{
		/* Convert the UTF-8 string bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-8 string.\n",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into a byte stream
		 */
		if( libuna_unicode_character_copy_to_byte_stream(
		     unicode_character,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_iterator,
		     codepage ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character to byte stream.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the size of a byte stream from a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
ssize_t libuna_byte_stream_size_from_utf16(
         libuna_utf16_character_t *utf16_string,
         size_t utf16_string_size,
         int codepage )
{
	static char *function                        = "libuna_byte_stream_size_from_utf16";
	size_t utf16_string_iterator                 = 0;
	ssize_t byte_stream_size                     = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf16_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 string.\n",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-16 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	while( utf16_string_iterator < utf16_string_size )
	{
		/* Convert the UTF-16 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-16.\n",
			 function );

			return( -1 );
		}
		/* Determine how many byte stream character bytes are required
		 */
		byte_stream_size += libuna_unicode_character_size_to_byte_stream(
		                     unicode_character,
		                     codepage );
	}
	return( byte_stream_size );
}

/* Copies a byte stream from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libuna_byte_stream_copy_from_utf16(
     uint8_t *byte_stream,
     size_t byte_stream_size,
     int codepage,
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size )
{
	static char *function                        = "libuna_byte_stream_copy_from_utf16";
	size_t utf16_string_iterator                 = 0;
	size_t byte_stream_iterator                  = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( byte_stream == NULL )
	{
		notify_warning_printf( "%s: invalid byte stream.\n",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid byte stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 string.\n",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-16 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	while( utf16_string_iterator < utf16_string_size )
	{
		/* Convert the UTF-16 string bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-16 string.\n",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into a byte stream
		 */
		if( libuna_unicode_character_copy_to_byte_stream(
		     unicode_character,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_iterator,
		     codepage ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character to byte stream.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the size of a byte stream from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
ssize_t libuna_byte_stream_size_from_utf32(
         libuna_utf32_character_t *utf32_string,
         size_t utf32_string_size,
         int codepage )
{
	static char *function                        = "libuna_byte_stream_size_from_utf32";
	size_t utf32_string_iterator                 = 0;
	ssize_t byte_stream_size                     = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf32_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 string.\n",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-32 string size value exceeds maximum.\n",
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
		     &utf32_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-32.\n",
			 function );

			return( -1 );
		}
		/* Determine how many byte stream character bytes are required
		 */
		byte_stream_size += libuna_unicode_character_size_to_byte_stream(
		                     unicode_character,
		                     codepage );
	}
	return( byte_stream_size );
}

/* Copies a byte stream from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuna_byte_stream_copy_from_utf32(
     uint8_t *byte_stream,
     size_t byte_stream_size,
     int codepage,
     libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size )
{
	static char *function                        = "libuna_byte_stream_copy_from_utf32";
	size_t utf32_string_iterator                 = 0;
	size_t byte_stream_iterator                  = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( byte_stream == NULL )
	{
		notify_warning_printf( "%s: invalid byte stream.\n",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid byte stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 string.\n",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-32 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	while( utf32_string_iterator < utf32_string_size )
	{
		/* Convert the UTF-32 string bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-32 string.\n",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into a byte stream
		 */
		if( libuna_unicode_character_copy_to_byte_stream(
		     unicode_character,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_iterator,
		     codepage ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character to byte stream.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

