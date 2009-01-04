/*
 * UTF-32 stream functions
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

#include "libuca_definitions.h"
#include "libuca_inline.h"
#include "libuca_unicode_character.h"
#include "libuca_utf32_stream.h"

/* Copies an UTF-32 stream byte order mark (BOM)
 * Returns 1 if successful or -1 on error
 */
LIBUCA_INLINE int libuca_utf32_stream_copy_byte_order_mark(
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   size_t *utf32_stream_index,
                   uint8_t byte_order )
{
	static char *function = "libuca_utf32_stream_copy_byte_order_mark";

	if( utf32_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 stream.\n",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-32 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf32_stream_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 stream index.\n",
		 function );

		return( -1 );
	}
	if( ( *utf32_stream_index + 3 ) >= utf32_stream_size )
	{
		notify_warning_printf( "%s: UTF-32 stream too small.\n",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUCA_ENDIAN_BIG )
	 && ( byte_order != LIBUCA_ENDIAN_LITTLE ) )
	{
		notify_warning_printf( "%s: unsupported byte order.\n",
		 function );

		return( -1 );
	}
	if( byte_order == LIBUCA_ENDIAN_BIG )
	{
		utf32_stream[ *utf32_stream_index     ] = 0x00;
		utf32_stream[ *utf32_stream_index + 1 ] = 0x00;
		utf32_stream[ *utf32_stream_index + 2 ] = 0xfe;
		utf32_stream[ *utf32_stream_index + 3 ] = 0xff;
	}
	else if( byte_order == LIBUCA_ENDIAN_LITTLE )
	{
		utf32_stream[ *utf32_stream_index     ] = 0xff;
		utf32_stream[ *utf32_stream_index + 1 ] = 0xfe;
		utf32_stream[ *utf32_stream_index + 2 ] = 0x00;
		utf32_stream[ *utf32_stream_index + 3 ] = 0x00;
	}
	*utf32_stream_index += 4;

	return( 1 );
}

/* Determines the size of a UTF-32 stream from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
ssize_t libuca_utf32_stream_size_from_utf8(
         libuca_utf8_character_t *utf8_string,
         size_t utf8_string_size )
{
	static char *function                        = "libuca_utf32_stream_size_from_utf8";
	size_t utf8_string_iterator                  = 0;
	ssize_t utf32_stream_size                    = 0;
	libuca_unicode_character_t unicode_character = 0;

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
	/* Add the byte order mark
	 */
	utf32_stream_size = 1;

	while( utf8_string_iterator < utf8_string_size )
	{
		/* Convert the UTF-8 character bytes into a Unicode character
		 */
		if( libuca_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-8.\n",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-32 character bytes are required
		 */
		utf32_stream_size += libuca_unicode_character_size_to_utf32(
		                      unicode_character );
	}
	/* Convert the amount of characters into bytes
	 */
	utf32_stream_size *= 4;

	return( utf32_stream_size );
}

/* Copies an UTF-32 stream from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuca_utf32_stream_copy_to_utf8(
     uint8_t *utf32_stream,
     size_t utf32_stream_size,
     uint8_t byte_order,
     libuca_utf8_character_t *utf8_string,
     size_t utf8_string_size )
{
	static char *function                        = "libuca_utf32_stream_copy_to_utf8";
	size_t utf8_string_iterator                  = 0;
	size_t utf32_stream_iterator                 = 0;
	libuca_unicode_character_t unicode_character = 0;

	if( utf32_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 stream.\n",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-32 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUCA_ENDIAN_BIG )
	 && ( byte_order != LIBUCA_ENDIAN_LITTLE ) )
	{
		notify_warning_printf( "%s: unsupported byte order.\n",
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
	if( libuca_utf32_stream_copy_byte_order_mark(
	     utf32_stream,
	     utf32_stream_size,
	     &utf32_stream_iterator,
	     byte_order ) != 1 )
	{
		notify_warning_printf( "%s: unable to copy UTF-32 byte order mark.\n",
		 function );

		return( -1 );
	}
	while( utf8_string_iterator < utf8_string_size )
	{
		/* Convert the UTF-8 string bytes into a Unicode character
		 */
		if( libuca_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-8 string.\n",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-32 stream bytes
		 */
		if( libuca_unicode_character_copy_to_utf32_stream(
		     unicode_character,
		     utf32_stream,
		     utf32_stream_size,
		     &utf32_stream_iterator,
		     byte_order ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character to UTF-32 stream.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the size of a UTF-32 stream from a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
ssize_t libuca_utf32_stream_size_from_utf16(
         libuca_utf16_character_t *utf16_string,
         size_t utf16_string_size )
{
	static char *function                        = "libuca_utf32_stream_size_from_utf16";
	size_t utf16_string_iterator                 = 0;
	ssize_t utf32_stream_size                    = 0;
	libuca_unicode_character_t unicode_character = 0;

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
	/* Add the byte order mark
	 */
	utf32_stream_size = 1;

	while( utf16_string_iterator < utf16_string_size )
	{
		/* Convert the UTF-16 character bytes into a Unicode character
		 */
		if( libuca_unicode_character_copy_from_utf16(
		     &unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-16.\n",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-32 character bytes are required
		 */
		utf32_stream_size += libuca_unicode_character_size_to_utf32(
		                      unicode_character );
	}
	/* Convert the amount of characters into bytes
	 */
	utf32_stream_size *= 4;

	return( utf32_stream_size );
}

/* Copies an UTF-32 stream from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libuca_utf32_stream_copy_from_utf16(
     uint8_t *utf32_stream,
     size_t utf32_stream_size,
     uint8_t byte_order,
     libuca_utf16_character_t *utf16_string,
     size_t utf16_string_size )
{
	static char *function                        = "libuca_utf32_stream_copy_from_utf16";
	size_t utf16_string_iterator                 = 0;
	size_t utf32_stream_iterator                 = 0;
	libuca_unicode_character_t unicode_character = 0;

	if( utf32_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 stream.\n",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-32 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUCA_ENDIAN_BIG )
	 && ( byte_order != LIBUCA_ENDIAN_LITTLE ) )
	{
		notify_warning_printf( "%s: unsupported byte order.\n",
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
	if( libuca_utf32_stream_copy_byte_order_mark(
	     utf32_stream,
	     utf32_stream_size,
	     &utf32_stream_iterator,
	     byte_order ) != 1 )
	{
		notify_warning_printf( "%s: unable to copy UTF-32 byte order mark.\n",
		 function );

		return( -1 );
	}
	while( utf16_string_iterator < utf16_string_size )
	{
		/* Convert the UTF-16 string bytes into a Unicode character
		 */
		if( libuca_unicode_character_copy_from_utf16(
		     &unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_iterator ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-16 string.\n",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-32 stream bytes
		 */
		if( libuca_unicode_character_copy_to_utf32_stream(
		     unicode_character,
		     utf32_stream,
		     utf32_stream_size,
		     &utf32_stream_iterator,
		     byte_order ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character to UTF-32 stream.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the size of a UTF-32 stream from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
ssize_t libuca_utf32_stream_size_from_utf32(
         libuca_utf32_character_t *utf32_string,
         size_t utf32_string_size )
{
	static char *function     = "libuca_utf32_stream_size_from_utf32";
	ssize_t utf32_stream_size = 0;

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
	/* Add the byte order mark
	 * Assumes the UTF-32 string is santized
	 */
	utf32_stream_size = 1 + (ssize_t) utf32_string_size;

	/* Convert the amount of characters into bytes
	 */
	utf32_stream_size *= 4;

	return( utf32_stream_size );
}

/* Copies an UTF-32 stream from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuca_utf32_stream_copy_from_utf32(
     uint8_t *utf32_stream,
     size_t utf32_stream_size,
     uint8_t byte_order,
     libuca_utf32_character_t *utf32_string,
     size_t utf32_string_size )
{
	static char *function                    = "libuca_utf32_stream_copy_from_utf32";
	size_t utf32_string_iterator             = 0;
	size_t utf32_stream_iterator             = 0;
	libuca_utf32_character_t utf32_character = 0;

	if( utf32_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 stream.\n",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-32 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUCA_ENDIAN_BIG )
	 && ( byte_order != LIBUCA_ENDIAN_LITTLE ) )
	{
		notify_warning_printf( "%s: unsupported byte order.\n",
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
	if( libuca_utf32_stream_copy_byte_order_mark(
	     utf32_stream,
	     utf32_stream_size,
	     &utf32_stream_iterator,
	     byte_order ) != 1 )
	{
		notify_warning_printf( "%s: unable to copy UTF-32 byte order mark.\n",
		 function );

		return( -1 );
	}
	/* Assumes the UTF-32 string is santized
	 */
	while( utf32_string_iterator < utf32_string_size )
	{
		utf32_character = utf32_string[ utf32_string_iterator++ ];

		if( byte_order == LIBUCA_ENDIAN_BIG )
		{
			utf32_stream[ utf32_stream_iterator + 2 ]   = (uint8_t) ( utf32_character & 0xff );
			utf32_character                           >>= 8;
			utf32_stream[ utf32_stream_iterator + 3 ]   = (uint8_t) ( utf32_character & 0xff );
			utf32_character                           >>= 8;
			utf32_stream[ utf32_stream_iterator + 1 ]   = (uint8_t) ( utf32_character & 0xff );
			utf32_character                           >>= 8;
			utf32_stream[ utf32_stream_iterator     ]   = (uint8_t) ( utf32_character & 0xff );
		}
		else if( byte_order == LIBUCA_ENDIAN_LITTLE )
		{
			utf32_stream[ utf32_stream_iterator     ]   = (uint8_t) ( utf32_character & 0xff );
			utf32_character                           >>= 8;
			utf32_stream[ utf32_stream_iterator + 1 ]   = (uint8_t) ( utf32_character & 0xff );
			utf32_character                           >>= 8;
			utf32_stream[ utf32_stream_iterator + 2 ]   = (uint8_t) ( utf32_character & 0xff );
			utf32_character                           >>= 8;
			utf32_stream[ utf32_stream_iterator + 3 ]   = (uint8_t) ( utf32_character & 0xff );
		}
		utf32_stream_iterator += 4;
	}
	return( 1 );
}
