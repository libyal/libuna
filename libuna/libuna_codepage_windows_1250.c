/*
 * Windows 1250 codepage (Central European) functions
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

#include "libuna_codepage_windows_1250.h"
#include "libuna_libcerror.h"
#include "libuna_types.h"

/* Extended ASCII to Unicode character lookup table for the Windows 1250 codepage
 * Unknown are filled with the Unicode replacement character 0xfffd
 */
const uint16_t libuna_codepage_windows_1250_byte_stream_to_unicode_base_0x80[ 128 ] = {
	0x20ac, 0xfffd, 0x201a, 0xfffd, 0x201e, 0x2026, 0x2020, 0x2021,
	0xfffd, 0x2030, 0x0160, 0x2039, 0x015a, 0x0164, 0x017d, 0x0179,
	0xfffd, 0x2018, 0x2019, 0x201c, 0x201d, 0x2022, 0x2013, 0x2014,
	0xfffd, 0x2122, 0x0161, 0x203a, 0x015b, 0x0165, 0x017e, 0x017a,
	0x00a0, 0x02c7, 0x02d8, 0x0141, 0x00a4, 0x0104, 0x00a6, 0x00a7,
	0x00a8, 0x00a9, 0x015e, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x017b,
	0x00b0, 0x00b1, 0x02db, 0x0142, 0x00b4, 0x00b5, 0x00b6, 0x00b7,
	0x00b8, 0x0105, 0x015f, 0x00bb, 0x013d, 0x02dd, 0x013e, 0x017c,
	0x0154, 0x00c1, 0x00c2, 0x0102, 0x00c4, 0x0139, 0x0106, 0x00c7,
	0x010c, 0x00c9, 0x0118, 0x00cb, 0x011a, 0x00cd, 0x00ce, 0x010e,
	0x0110, 0x0143, 0x0147, 0x00d3, 0x00d4, 0x0150, 0x00d6, 0x00d7,
	0x0158, 0x016e, 0x00da, 0x0170, 0x00dc, 0x00dd, 0x0162, 0x00df,
	0x0155, 0x00e1, 0x00e2, 0x0103, 0x00e4, 0x013a, 0x0107, 0x00e7,
	0x010d, 0x00e9, 0x0119, 0x00eb, 0x011b, 0x00ed, 0x00ee, 0x010f,
	0x0111, 0x0144, 0x0148, 0x00f3, 0x00f4, 0x0151, 0x00f6, 0x00f7,
	0x0159, 0x016f, 0x00fa, 0x0171, 0x00fc, 0x00fd, 0x0163, 0x02d9
};

/* Unicode to ASCII character lookup tables for the Windows 1250 codepage
 * Unknown are filled with the ASCII replacement character 0x1a
 */
const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x00a0[ 128 ] = {
	0xa0, 0x1a, 0x1a, 0x1a, 0xa4, 0x1a, 0xa6, 0xa7,
	0xa8, 0xa9, 0x1a, 0xab, 0xac, 0xad, 0xae, 0x1a,
	0xb0, 0xb1, 0x1a, 0x1a, 0xb4, 0xb5, 0xb6, 0xb7,
	0xb8, 0x1a, 0x1a, 0xbb, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0xc1, 0xc2, 0x1a, 0xc4, 0x1a, 0x1a, 0xc7,
	0x1a, 0xc9, 0x1a, 0xcb, 0x1a, 0xcd, 0xce, 0x1a,
	0x1a, 0x1a, 0x1a, 0xd3, 0xd4, 0x1a, 0xd6, 0xd7,
	0x1a, 0x1a, 0xda, 0x1a, 0xdc, 0xdd, 0x1a, 0xdf,
	0x1a, 0xe1, 0xe2, 0x1a, 0xe4, 0x1a, 0x1a, 0xe7,
	0x1a, 0xe9, 0x1a, 0xeb, 0x1a, 0xed, 0xee, 0x1a,
	0x1a, 0x1a, 0x1a, 0xf3, 0xf4, 0x1a, 0xf6, 0xf7,
	0x1a, 0x1a, 0xfa, 0x1a, 0xfc, 0xfd, 0x1a, 0x1a,
	0x1a, 0x1a, 0xc3, 0xe3, 0xa5, 0xb9, 0xc6, 0xe6,
	0x1a, 0x1a, 0x1a, 0x1a, 0xc8, 0xe8, 0xcf, 0xef,
	0xd0, 0xf0, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0xca, 0xea, 0xcc, 0xec, 0x1a, 0x1a, 0x1a, 0x1a
};

const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x0138[ 72 ] = {
	0x1a, 0xc5, 0xe5, 0x1a, 0x1a, 0xbc, 0xbe, 0x1a,
	0x1a, 0xa3, 0xb3, 0xd1, 0xf1, 0x1a, 0x1a, 0xd2,
	0xf2, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0xd5, 0xf5, 0x1a, 0x1a, 0xc0, 0xe0, 0x1a, 0x1a,
	0xd8, 0xf8, 0x8c, 0x9c, 0x1a, 0x1a, 0xaa, 0xba,
	0x8a, 0x9a, 0xde, 0xfe, 0x8d, 0x9d, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0xd9, 0xf9,
	0xdb, 0xfb, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x8f, 0x9f, 0xaf, 0xbf, 0x8e, 0x9e, 0x1a
};

const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x02d8[ 8 ] = {
	0xa2, 0xff, 0x1a, 0xb2, 0x1a, 0xbd, 0x1a, 0x1a
};

const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x2010[ 24 ] = {
	0x1a, 0x1a, 0x1a, 0x96, 0x97, 0x1a, 0x1a, 0x1a,
	0x91, 0x92, 0x82, 0x1a, 0x93, 0x94, 0x84, 0x1a,
	0x86, 0x87, 0x95, 0x1a, 0x1a, 0x1a, 0x85, 0x1a
};

const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x2030[ 16 ] = {
	0x89, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x8b, 0x9b, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a
};

/* Copies an Unicode character from a Windows 1250 encoded byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_codepage_windows_1250_copy_from_byte_stream(
     libuna_unicode_character_t *unicode_character,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     libcerror_error_t **error )
{
	static char *function                             = "libuna_codepage_windows_1250_copy_from_byte_stream";
	libuna_unicode_character_t safe_unicode_character = 0xfffd;
	size_t safe_byte_stream_index                     = 0;
	uint8_t byte_stream_character                     = 0;

	if( unicode_character == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
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
	if( byte_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream index.",
		 function );

		return( -1 );
	}
	safe_byte_stream_index = *byte_stream_index;

	if( safe_byte_stream_index >= byte_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	byte_stream_character = byte_stream[ safe_byte_stream_index++ ];

	if( byte_stream_character < 0x80 )
	{
		safe_unicode_character = byte_stream_character;
	}
	else
	{
		byte_stream_character -= 0x80;

		safe_unicode_character = libuna_codepage_windows_1250_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
	}
	*unicode_character = safe_unicode_character;
	*byte_stream_index = safe_byte_stream_index;

	return( 1 );
}

/* Copies an Unicode character to a Windows 1250 encoded byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_codepage_windows_1250_copy_to_byte_stream(
     libuna_unicode_character_t unicode_character,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     libcerror_error_t **error )
{
	static char *function         = "libuna_codepage_windows_1250_copy_to_byte_stream";
	size_t safe_byte_stream_index = 0;
	uint16_t byte_stream_value    = 0x001a;

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
	if( byte_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream index.",
		 function );

		return( -1 );
	}
	safe_byte_stream_index = *byte_stream_index;

	if( safe_byte_stream_index >= byte_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	if( unicode_character < 0x0080 )
	{
		byte_stream_value = (uint16_t) unicode_character;
	}
	else if( ( unicode_character >= 0x00a0 )
	      && ( unicode_character < 0x0120 ) )
	{
		unicode_character -= 0x00a0;

		byte_stream_value = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
	}
	else if( ( unicode_character >= 0x0138 )
	      && ( unicode_character < 0x0180 ) )
	{
		unicode_character -= 0x0138;

		byte_stream_value = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x0138[ unicode_character ];
	}
	else if( ( unicode_character >= 0x02d8 )
	      && ( unicode_character < 0x02e0 ) )
	{
		unicode_character -= 0x02d8;

		byte_stream_value = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x02d8[ unicode_character ];
	}
	else if( ( unicode_character >= 0x2010 )
	      && ( unicode_character < 0x2028 ) )
	{
		unicode_character -= 0x2010;

		byte_stream_value = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x2010[ unicode_character ];
	}
	else if( ( unicode_character >= 0x2030 )
	      && ( unicode_character < 0x2040 ) )
	{
		unicode_character -= 0x2030;

		byte_stream_value = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x2030[ unicode_character ];
	}
	else switch( unicode_character )
	{
		case 0x02c7:
			byte_stream_value = 0xa1;
			break;

		case 0x20ac:
			byte_stream_value = 0x80;
			break;

		case 0x2122:
			byte_stream_value = 0x99;
			break;

		default:
			byte_stream_value = 0x1a;
			break;
	}
	byte_stream[ safe_byte_stream_index++ ] = (uint8_t) ( byte_stream_value & 0x00ff );

	*byte_stream_index = safe_byte_stream_index;

	return( 1 );
}

