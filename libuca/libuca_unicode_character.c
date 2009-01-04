/*
 * Unicode character functions
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

#include "libuca_codepage_ascii.h"
#include "libuca_codepage_windows_1250.h"
#include "libuca_codepage_windows_1251.h"
#include "libuca_codepage_windows_1252.h"
#include "libuca_codepage_windows_1253.h"
#include "libuca_codepage_windows_1254.h"
#include "libuca_codepage_windows_1256.h"
#include "libuca_codepage_windows_1257.h"
#include "libuca_definitions.h"
#include "libuca_unicode_character.h"

/* Copies a Unicode character from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_from_byte_stream(
     libuca_unicode_character_t *unicode_character,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     int code_page,
     uint8_t strict_mode )
{
	static char *function = "libuca_unicode_character_copy_from_byte_stream";

	if( unicode_character == NULL )
	{
		notify_warning_printf( "%s: invalid Unicode character.\n",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		notify_warning_printf( "%s: invalid byte stream.\n",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid byte stream  size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( byte_stream_index == NULL )
	{
		notify_warning_printf( "%s: invalid byte stream index.\n",
		 function );

		return( -1 );
	}
	if( *byte_stream_index >= byte_stream_size )
	{
		notify_warning_printf( "%s: byte stream too small.\n",
		 function );

		return( -1 );
	}
	*unicode_character = byte_stream[ *byte_stream_index ];

	switch( code_page )
	{
		case LIBUCA_CODEPAGE_WINDOWS_1250:
			*unicode_character = libuca_codepage_windows_1250_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1251:
			*unicode_character = libuca_codepage_windows_1251_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1252:
			*unicode_character = libuca_codepage_windows_1252_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1253:
			*unicode_character = libuca_codepage_windows_1253_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1254:
			*unicode_character = libuca_codepage_windows_1254_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1256:
			*unicode_character = libuca_codepage_windows_1256_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1257:
			*unicode_character = libuca_codepage_windows_1257_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUCA_CODEPAGE_ASCII:
		default:
			*unicode_character = libuca_codepage_ascii_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;
	}
	if( ( strict_mode != 0 )
	 && ( *unicode_character == LIBUCA_UNICODE_REPLACEMENT_CHARACTER ) )
	{
		notify_warning_printf( "%s: unable to convert byte stream into Unicode.\n",
		 function );

		return( -1 );
	}
	*byte_stream_index += 1;

	return( 1 );
}

/* Copies a Unicode character to a byte stream string
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_to_byte_stream(
     libuca_unicode_character_t unicode_character,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     int code_page,
     uint8_t strict_mode )
{
	static char *function = "libuca_unicode_character_copy_to_byte_stream";

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
	if( byte_stream_index == NULL )
	{
		notify_warning_printf( "%s: invalid byte stream index.\n",
		 function );

		return( -1 );
	}
	if( *byte_stream_index >= byte_stream_size )
	{
		notify_warning_printf( "%s: byte stream too small.\n",
		 function );

		return( -1 );
	}
	switch( code_page )
	{
		case LIBUCA_CODEPAGE_WINDOWS_1250:
			byte_stream[ *byte_stream_index ] = libuca_codepage_windows_1250_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1251:
			byte_stream[ *byte_stream_index ] = libuca_codepage_windows_1251_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1252:
			byte_stream[ *byte_stream_index ] = libuca_codepage_windows_1252_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1253:
			byte_stream[ *byte_stream_index ] = libuca_codepage_windows_1253_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1254:
			byte_stream[ *byte_stream_index ] = libuca_codepage_windows_1254_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1256:
			byte_stream[ *byte_stream_index ] = libuca_codepage_windows_1256_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUCA_CODEPAGE_WINDOWS_1257:
			byte_stream[ *byte_stream_index ] = libuca_codepage_windows_1257_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUCA_CODEPAGE_ASCII:
		default:
			byte_stream[ *byte_stream_index ] = libuca_codepage_ascii_unicode_to_byte_stream(
			                                     unicode_character );
			break;
	}
	if( ( strict_mode != 0 )
	 && ( byte_stream[ *byte_stream_index ] == LIBUCA_ASCII_REPLACEMENT_CHARACTER ) )
	{
		notify_warning_printf( "%s: unable to convert Unicode character into byte stream.\n",
		 function );

		return( -1 );
	}
	*byte_stream_index += 1;

	return( 1 );
}

/* Copies a Unicode character from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_from_utf8(
     libuca_unicode_character_t *unicode_character,
     libuca_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint8_t strict_mode )
{
	static char *function                   = "libuca_unicode_character_copy_from_utf8";
	uint8_t utf8_character_additional_bytes = 0;

	if( unicode_character == NULL )
	{
		notify_warning_printf( "%s: invalid Unicode character.\n",
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
	if( utf8_string_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 string index.\n",
		 function );

		return( -1 );
	}
	if( *utf8_string_index >= utf8_string_size )
	{
		notify_warning_printf( "%s: UTF-8 string too small.\n",
		 function );

		return( -1 );
	}
	/* Determine the amount of additional bytes of the UTF-8 character
	 */
	if( utf8_string[ *utf8_string_index ] < 0xc0 )
	{
		utf8_character_additional_bytes = 0;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xe0 )
	{
		utf8_character_additional_bytes = 1;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xf0 )
	{
		utf8_character_additional_bytes = 2;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xf8 )
	{
		utf8_character_additional_bytes = 3;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xfc )
	{
		utf8_character_additional_bytes = 4;
	}
	else
	{
		utf8_character_additional_bytes = 5;
	}
	if( ( *utf8_string_index + utf8_character_additional_bytes + 1 ) > utf8_string_size )
	{
		notify_warning_printf( "%s: missing UTF-8 character bytes.\n",
		 function );

		return( -1 );
	}
	/* Determine the UTF-8 character and make sure it is valid
	 * Unicode limits the UTF-8 character to consist of a maximum of 4 bytes
	 * while ISO 10646 Universal Character Set (UCS) allows up to 6 bytes
	 */
	if( utf8_string[ *utf8_string_index ] > 0xf4 )
	{
		notify_warning_printf( "%s: invalid 1st UTF-8 character byte.\n",
		 function );

		return( -1 );
	}
	*unicode_character = utf8_string[ *utf8_string_index ];

	if( utf8_character_additional_bytes == 0 )
	{
		if( ( utf8_string[ *utf8_string_index ] >= 0x80 )
		 && ( utf8_string[ *utf8_string_index ] < 0xc2 ) )
		{
			notify_warning_printf( "%s: invalid 1st UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
	}
	if( utf8_character_additional_bytes >= 1 )
	{
		if( utf8_string[ *utf8_string_index + 1 ] > 0xbf )
		{
			notify_warning_printf( "%s: invalid 2nd UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		if( ( utf8_string[ *utf8_string_index ] == 0xe0 )
		 && ( utf8_string[ *utf8_string_index + 1 ] < 0xa0 ) )
		{
			notify_warning_printf( "%s: invalid 2nd UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		else if( ( utf8_string[ *utf8_string_index ] == 0xed )
		      && ( utf8_string[ *utf8_string_index + 1 ] > 0x9f ) )
		{
			notify_warning_printf( "%s: invalid 2nd UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		else if( ( utf8_string[ *utf8_string_index ] == 0xf0 )
		      && ( utf8_string[ *utf8_string_index + 1 ] < 0x90 ) )
		{
			notify_warning_printf( "%s: invalid 2nd UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		else if( ( utf8_string[ *utf8_string_index ] == 0xf4 )
		      && ( utf8_string[ *utf8_string_index + 1 ] > 0x8f ) )
		{
			notify_warning_printf( "%s: invalid 2nd UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		else if( utf8_string[ *utf8_string_index + 1 ] < 0x80 )
		{
			notify_warning_printf( "%s: invalid 2nd UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 1 ];

		if( utf8_character_additional_bytes == 1 )
		{
			*unicode_character -= 0x03080;
		}
	}
	if( utf8_character_additional_bytes >= 2 )
	{
		if( ( utf8_string[ *utf8_string_index + 2 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 2 ] > 0xbf ) )
		{
			notify_warning_printf( "%s: invalid 3rd UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 2 ];

		if( utf8_character_additional_bytes == 2 )
		{
			*unicode_character -= 0x0e2080;
		}
	}
	if( utf8_character_additional_bytes >= 3 )
	{
		if( ( utf8_string[ *utf8_string_index + 3 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 3 ] > 0xbf ) )
		{
			notify_warning_printf( "%s: invalid 4th UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 3 ];

		if( utf8_character_additional_bytes == 3 )
		{
			*unicode_character -= 0x03c82080;
		}
	}
	if( utf8_character_additional_bytes >= 4 )
	{
		if( ( utf8_string[ *utf8_string_index + 4 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 4 ] > 0xbf ) )
		{
			notify_warning_printf( "%s: invalid 5th UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 4 ];

		if( utf8_character_additional_bytes == 4 )
		{
			*unicode_character -= 0x0fa082080;
		}
	}
	if( utf8_character_additional_bytes == 5 )
	{
		if( ( utf8_string[ *utf8_string_index + 5 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 5 ] > 0xbf ) )
		{
			notify_warning_printf( "%s: invalid 6th UTF-8 character byte.\n",
			 function );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 5 ];
		*unicode_character -= 0x082082080;
	}
	if( ( strict_mode != 0 )
	 && ( *unicode_character > LIBUCA_UNICODE_CHARACTER_MAX ) )
	{
		*unicode_character = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;
	}
	*utf8_string_index += 1 + utf8_character_additional_bytes;

	return( 1 );
}

/* Copies a Unicode character into a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_to_utf8(
     libuca_unicode_character_t unicode_character,
     libuca_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint8_t strict_mode )
{
	static char *function                   = "libuca_unicode_character_copy_to_utf8";
	uint8_t utf8_character_additional_bytes = 0;
	uint8_t utf8_character_iterator         = 0;
	uint8_t utf8_first_character_mark       = 0;

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
	if( utf8_string_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 string index.\n",
		 function );

		return( -1 );
	}
	if( *utf8_string_index >= utf8_string_size )
	{
		notify_warning_printf( "%s: UTF-8 string too small.\n",
		 function );

		return( -1 );
	}
	if( ( strict_mode != 0 )
	 && ( unicode_character > LIBUCA_UNICODE_CHARACTER_MAX ) )
	{
		unicode_character = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;
	}
	/* Determine how many UTF-8 character bytes are required
	 */
	if( unicode_character < 0x080 )
	{
		utf8_character_additional_bytes = 0;
		utf8_first_character_mark       = 0;
	}
	else if( unicode_character < 0x0800 )
	{
		utf8_character_additional_bytes = 1;
		utf8_first_character_mark       = 0x0c0;
	}
	else if( unicode_character < 0x010000 )
	{
		utf8_character_additional_bytes = 2;
		utf8_first_character_mark       = 0x0e0;
	}
	else if( unicode_character < 0x0200000 )
	{
		utf8_character_additional_bytes = 3;
		utf8_first_character_mark       = 0x0f0;
	}
	else if( unicode_character < 0x0400000 )
	{
		utf8_character_additional_bytes = 4;
		utf8_first_character_mark       = 0x0f8;
	}
	else
	{
		utf8_character_additional_bytes = 5;
		utf8_first_character_mark       = 0x0fc;
	}
	/* Convert Unicode character into UTF-8 character bytes
	 */
	if( ( *utf8_string_index + utf8_character_additional_bytes ) >= utf8_string_size )
	{
		notify_warning_printf( "%s: UTF-8 string too small.\n",
		 function );

		return( -1 );
	}
	for( utf8_character_iterator = utf8_character_additional_bytes; utf8_character_iterator > 0; utf8_character_iterator-- )
	{
		utf8_string[ *utf8_string_index + utf8_character_iterator ] = (libuca_utf8_character_t) ( ( unicode_character & 0x0bf ) | 0x080 );

		unicode_character >>= 6;
	}
	utf8_string[ *utf8_string_index ] = (libuca_utf8_character_t) ( unicode_character | utf8_first_character_mark );

	*utf8_string_index += 1 + utf8_character_additional_bytes;

	return( 1 );
}

/* Copies a Unicode character from a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_from_utf16(
     libuca_unicode_character_t *unicode_character,
     libuca_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint8_t strict_mode )
{
	static char *function                          = "libuca_unicode_character_copy_from_utf16";
	libuca_utf16_character_t utf16_surrogate = 0;

	if( unicode_character == NULL )
	{
		notify_warning_printf( "%s: invalid Unicode character.\n",
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
	if( utf16_string_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 string index.\n",
		 function );

		return( -1 );
	}
	if( *utf16_string_index >= utf16_string_size )
	{
		notify_warning_printf( "%s: UTF-16 string too small.\n",
		 function );

		return( -1 );
	}
	*unicode_character   = utf16_string[ *utf16_string_index ];
	*utf16_string_index += 1;

	/* Determine if the UTF-16 character is within the high surrogate range
	 */
	if( ( *unicode_character >= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START )
	 && ( *unicode_character <= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_END ) )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			notify_warning_printf( "%s: missing surrogate UTF-16 character bytes.\n",
			 function );

			return( -1 );
		}
		utf16_surrogate      = utf16_string[ *utf16_string_index ];
		*utf16_string_index += 1;

		/* Determine if the UTF-16 character is within the low surrogate range
		 */
		if( ( utf16_surrogate >= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( utf16_surrogate <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			*unicode_character  -= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START;
			*unicode_character <<= 10;
			*unicode_character  += utf16_surrogate - LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END;
			*unicode_character  += 0x010000;
		}
		else
		{
			notify_warning_printf( "%s: invalid surrogate UTF-16 character bytes.\n",
			 function );

			return( -1 );
		}
	}
	else if( strict_mode != 0 )
	{
		if( ( *unicode_character >= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( *unicode_character <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			notify_warning_printf( "%s: invalid UTF-16 character value in low surrogate range.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Copies a Unicode character into a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_to_utf16(
     libuca_unicode_character_t unicode_character,
     libuca_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint8_t strict_mode )
{
	static char *function = "libuca_unicode_character_copy_to_utf16";

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
	if( utf16_string_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 string index.\n",
		 function );

		return( -1 );
	}
	if( *utf16_string_index >= utf16_string_size )
	{
		notify_warning_printf( "%s: UTF-16 string too small.\n",
		 function );

		return( -1 );
	}
	if( unicode_character <= LIBUCA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
	{
		if( ( unicode_character >= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START )
		 && ( unicode_character <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			if( strict_mode != 0 )
			{
				notify_warning_printf( "%s: invalid Unicode character value in surrogate range.\n",
				 function );

				return( -1 );
			}
			unicode_character = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;
		}
		utf16_string[ *utf16_string_index ] = (libuca_utf16_character_t) unicode_character;

		*utf16_string_index += 1;
	}
	else if( unicode_character > LIBUCA_UTF16_CHARACTER_MAX )
	{
		if( strict_mode != 0 )
		{
			notify_warning_printf( "%s: invalid Unicode character value exceeds UTF-16 maximum.\n",
			 function );

			return( -1 );
		}
		utf16_string[ *utf16_string_index ] = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;

		*utf16_string_index += 1;
	}
	else
	{
		if( ( *utf16_string_index + 1 ) >= utf16_string_size )
		{
			notify_warning_printf( "%s: UTF-16 string too small.\n",
			 function );

			return( -1 );
		}
		unicode_character                      -= 0x010000;
		utf16_string[ *utf16_string_index     ] = (libuca_utf16_character_t) ( ( unicode_character >> 10 ) + LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START );
		utf16_string[ *utf16_string_index + 1 ] = (libuca_utf16_character_t) ( ( unicode_character & 0x03ff ) + LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START );

		*utf16_string_index += 2;
	}
	return( 1 );
}

/* Copies a Unicode character from a UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_from_utf16_stream(
     libuca_unicode_character_t *unicode_character,
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     size_t *utf16_stream_index,
     uint8_t byte_order,
     uint8_t strict_mode )
{
	static char *function                    = "libuca_unicode_character_copy_from_utf16_stream";
	libuca_utf16_character_t utf16_surrogate = 0;

	if( unicode_character == NULL )
	{
		notify_warning_printf( "%s: invalid Unicode character.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 stream.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-16 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 stream index.\n",
		 function );

		return( -1 );
	}
	if( *utf16_stream_index >= utf16_stream_size )
	{
		notify_warning_printf( "%s: UTF-16 stream too small.\n",
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
		*unicode_character   = utf16_stream[ *utf16_stream_index ];
		*unicode_character <<= 8;
		*unicode_character  += utf16_stream[ *utf16_stream_index + 1 ];
	}
	else if( byte_order == LIBUCA_ENDIAN_LITTLE )
	{
		*unicode_character   = utf16_stream[ *utf16_stream_index + 1 ];
		*unicode_character <<= 8;
		*unicode_character  += utf16_stream[ *utf16_stream_index ];
	}
	*utf16_stream_index += 2;

	/* Determine if the UTF-16 character is within the high surrogate range
	 */
	if( ( *unicode_character >= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START )
	 && ( *unicode_character <= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_END ) )
	{
		if( *utf16_stream_index >= utf16_stream_size )
		{
			notify_warning_printf( "%s: missing surrogate UTF-16 character bytes.\n",
			 function );

			return( -1 );
		}
		if( byte_order == LIBUCA_ENDIAN_BIG )
		{
			utf16_surrogate   = utf16_stream[ *utf16_stream_index ];
			utf16_surrogate <<= 8;
			utf16_surrogate  += utf16_stream[ *utf16_stream_index + 1 ];
		}
		else if( byte_order == LIBUCA_ENDIAN_LITTLE )
		{
			utf16_surrogate   = utf16_stream[ *utf16_stream_index + 1 ];
			utf16_surrogate <<= 8;
			utf16_surrogate  += utf16_stream[ *utf16_stream_index ];
		}
		*utf16_stream_index += 2;

		/* Determine if the UTF-16 character is within the low surrogate range
		 */
		if( ( utf16_surrogate >= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( utf16_surrogate <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			*unicode_character  -= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START;
			*unicode_character <<= 10;
			*unicode_character  += utf16_surrogate - LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END;
			*unicode_character  += 0x010000;
		}
		else
		{
			notify_warning_printf( "%s: invalid surrogate UTF-16 character bytes.\n",
			 function );

			return( -1 );
		}
	}
	else if( strict_mode != 0 )
	{
		if( ( *unicode_character >= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( *unicode_character <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			notify_warning_printf( "%s: invalid UTF-16 character value in low surrogate range.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Copies a Unicode character to an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_to_utf16_stream(
     libuca_unicode_character_t unicode_character,
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     size_t *utf16_stream_index,
     uint8_t byte_order,
     uint8_t strict_mode )
{
	static char *function                    = "libuca_unicode_character_copy_to_utf16_stream";
	libuca_utf16_character_t utf16_surrogate = 0;

	if( utf16_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 stream.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-16 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 stream index.\n",
		 function );

		return( -1 );
	}
	if( ( *utf16_stream_index + 1 ) >= utf16_stream_size )
	{
		notify_warning_printf( "%s: UTF-16 stream too small.\n",
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
	if( unicode_character <= LIBUCA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
	{
		if( ( unicode_character <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END )
		 && ( unicode_character >= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START ) )
		{
			if( strict_mode != 0 )
			{
				notify_warning_printf( "%s: invalid Unicode character value in surrogate range.\n",
				 function );

				return( -1 );
			}
			unicode_character = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;
		}
		if( byte_order == LIBUCA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
			unicode_character                       >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
		}
		else if( byte_order == LIBUCA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
			unicode_character                       >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		}
		*utf16_stream_index += 2;
	}
	else if( unicode_character > LIBUCA_UTF16_CHARACTER_MAX )
	{
		if( strict_mode != 0 )
		{
			notify_warning_printf( "%s: invalid Unicode character value exceeds UTF-16 maximum.\n",
			 function );

			return( -1 );
		}
		unicode_character = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;

		if( byte_order == LIBUCA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
			unicode_character                       >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
		}
		else if( byte_order == LIBUCA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
			unicode_character                       >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		}
		*utf16_stream_index += 2;
	}
	else
	{
		if( ( *utf16_stream_index + 3 ) >= utf16_stream_size )
		{
			notify_warning_printf( "%s: UTF-16 stream too small.\n",
			 function );

			return( -1 );
		}
		unicode_character -= 0x010000;

		utf16_surrogate = (libuca_utf16_character_t) ( ( unicode_character >> 10 ) + LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START );

		if( byte_order == LIBUCA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		else if( byte_order == LIBUCA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		*utf16_stream_index += 2;

		utf16_surrogate = (libuca_utf16_character_t) ( ( unicode_character & 0x03ff ) + LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START );

		if( byte_order == LIBUCA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		else if( byte_order == LIBUCA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		*utf16_stream_index += 2;
	}
	return( 1 );
}

/* Copies a Unicode character from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_from_utf32(
     libuca_unicode_character_t *unicode_character,
     libuca_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf32_string_index,
     uint8_t strict_mode )
{
	static char *function = "libuca_unicode_character_copy_from_utf32";

	if( unicode_character == NULL )
	{
		notify_warning_printf( "%s: invalid Unicode character.\n",
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
	if( utf32_string_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 string index.\n",
		 function );

		return( -1 );
	}
	if( *utf32_string_index >= utf32_string_size )
	{
		notify_warning_printf( "%s: UTF-32 string too small.\n",
		 function );

		return( -1 );
	}
	*unicode_character = utf32_string[ *utf32_string_index ];

	if( strict_mode != 0 )
	{
		/* Determine if the UTF-32 character is within the high surrogate range
		 */
		if( ( *unicode_character >= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( *unicode_character <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			notify_warning_printf( "%s: invalid UTF-32 character value in low surrogate range.\n",
			 function );

			return( -1 );
		}
	}
	*utf32_string_index += 1;

	return( 1 );
}

/* Copies a Unicode character into a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_to_utf32(
     libuca_unicode_character_t unicode_character,
     libuca_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf32_string_index,
     uint8_t strict_mode )
{
	static char *function = "libuca_unicode_character_copy_to_utf32";

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
	if( utf32_string_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 string index.\n",
		 function );

		return( -1 );
	}
	if( *utf32_string_index >= utf32_string_size )
	{
		notify_warning_printf( "%s: UTF-32 string too small.\n",
		 function );

		return( -1 );
	}
	if( unicode_character > LIBUCA_UTF32_CHARACTER_MAX )
	{
		if( strict_mode != 0 )
		{
			notify_warning_printf( "%s: invalid Unicode character value exceeds UTF-32 maximum.\n",
			 function );

			return( -1 );
		}
		unicode_character = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;
	}
	else if( ( unicode_character <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END )
	      && ( unicode_character >= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START ) )
	{
		if( strict_mode != 0 )
		{
			notify_warning_printf( "%s: invalid Unicode character value in surrogate range.\n",
			 function );

			return( -1 );
		}
		unicode_character = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;
	}
	utf32_string[ *utf32_string_index ] = (libuca_utf32_character_t) unicode_character;

	*utf32_string_index += 1;

	return( 1 );
}

/* Copies a Unicode character from a UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_from_utf32_stream(
     libuca_unicode_character_t *unicode_character,
     uint8_t *utf32_stream,
     size_t utf32_stream_size,
     size_t *utf32_stream_index,
     uint8_t byte_order,
     uint8_t strict_mode )
{
	static char *function = "libuca_unicode_character_copy_from_utf32_stream";

	if( unicode_character == NULL )
	{
		notify_warning_printf( "%s: invalid Unicode character.\n",
		 function );

		return( -1 );
	}
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
	if( *utf32_stream_index >= utf32_stream_size )
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
		*unicode_character   = utf32_stream[ *utf32_stream_index ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index + 1 ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index + 2 ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index + 3 ];
	}
	else if( byte_order == LIBUCA_ENDIAN_LITTLE )
	{
		*unicode_character   = utf32_stream[ *utf32_stream_index + 3 ];
		*unicode_character <<= 8;
		*unicode_character   = utf32_stream[ *utf32_stream_index + 2 ];
		*unicode_character <<= 8;
		*unicode_character   = utf32_stream[ *utf32_stream_index + 1 ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index ];
	}
	*utf32_stream_index += 4;

	if( strict_mode != 0 )
	{
		/* Determine if the UTF-32 character is within the high surrogate range
		 */
		if( ( *unicode_character >= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( *unicode_character <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			notify_warning_printf( "%s: invalid UTF-32 character value in low surrogate range.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Copies a Unicode character to an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
int libuca_unicode_character_copy_to_utf32_stream(
     libuca_unicode_character_t unicode_character,
     uint8_t *utf32_stream,
     size_t utf32_stream_size,
     size_t *utf32_stream_index,
     uint8_t byte_order,
     uint8_t strict_mode )
{
	static char *function = "libuca_unicode_character_copy_to_utf32_stream";

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
	if( ( *utf32_stream_index + 1 ) >= utf32_stream_size )
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
	if( unicode_character > LIBUCA_UTF32_CHARACTER_MAX )
	{
		if( strict_mode != 0 )
		{
			notify_warning_printf( "%s: invalid Unicode character value exceeds UTF-32 maximum.\n",
			 function );

			return( -1 );
		}
		unicode_character = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;
	}
	else if( ( unicode_character <= LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END )
	      && ( unicode_character >= LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START ) )
	{
		if( strict_mode != 0 )
		{
			notify_warning_printf( "%s: invalid Unicode character value in surrogate range.\n",
			 function );

			return( -1 );
		}
		unicode_character = LIBUCA_UNICODE_REPLACEMENT_CHARACTER;
	}
	if( byte_order == LIBUCA_ENDIAN_BIG )
	{
		utf32_stream[ *utf32_stream_index + 3 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 2 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
	}
	else if( byte_order == LIBUCA_ENDIAN_LITTLE )
	{
		utf32_stream[ *utf32_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 2 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 3 ]   = (uint8_t) ( unicode_character & 0xff );
	}
	*utf32_stream_index += 4;

	return( 1 );
}

