/*
 * MacInuit codepage functions
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

#include "libuna_codepage_mac_inuit.h"
#include "libuna_libcerror.h"
#include "libuna_types.h"

/* Extended ASCII to Unicode character lookup table for the MacInuit codepage
 * Unknown are filled with the Unicode replacement character 0xfffd
 */
const uint16_t libuna_codepage_mac_inuit_byte_stream_to_unicode_base_0x80[ 128 ] = {
	0x1403, 0x1404, 0x1405, 0x1406, 0x140a, 0x140b, 0x1431, 0x1432,
	0x1433, 0x1434, 0x1438, 0x1439, 0x1449, 0x144e, 0x144f, 0x1450,
	0x1451, 0x1455, 0x1456, 0x1466, 0x146d, 0x146e, 0x146f, 0x1470,
	0x1472, 0x1473, 0x1483, 0x148b, 0x148c, 0x148d, 0x148e, 0x1490,
	0x1491, 0x00b0, 0x14a1, 0x14a5, 0x14a6, 0x2022, 0x00b6, 0x14a7,
	0x00ae, 0x00a9, 0x2122, 0x14a8, 0x14aa, 0x14ab, 0x14bb, 0x14c2,
	0x14c3, 0x14c4, 0x14c5, 0x14c7, 0x14c8, 0x14d0, 0x14ef, 0x14f0,
	0x14f1, 0x14f2, 0x14f4, 0x14f5, 0x1505, 0x14d5, 0x14d6, 0x14d7,
	0x14d8, 0x14da, 0x14db, 0x14ea, 0x1528, 0x1529, 0x152a, 0x152b,
	0x152d, 0x2026, 0x00a0, 0x152e, 0x153e, 0x1555, 0x1556, 0x1557,
	0x2013, 0x2014, 0x201c, 0x201d, 0x2018, 0x2019, 0x1558, 0x1559,
	0x155a, 0x155d, 0x1546, 0x1547, 0x1548, 0x1549, 0x154b, 0x154c,
	0x1550, 0x157f, 0x1580, 0x1581, 0x1582, 0x1583, 0x1584, 0x1585,
	0x158f, 0x1590, 0x1591, 0x1592, 0x1593, 0x1594, 0x1595, 0x1671,
	0x1672, 0x1673, 0x1674, 0x1675, 0x1676, 0x1596, 0x15a0, 0x15a1,
	0x15a2, 0x15a3, 0x15a4, 0x15a5, 0x15a6, 0x157c, 0x0141, 0x0142
};

/* Unicode to ASCII character lookup tables for the MacInuit codepage
 * Unknown are filled with the ASCII replacement character 0x1a
 */
const uint8_t libuna_codepage_mac_inuit_unicode_to_byte_stream_base_0x1430[ 216 ] = {
	0x1a, 0x86, 0x87, 0x88, 0x89, 0x1a, 0x1a, 0x1a,
	0x8a, 0x8b, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x8c, 0x1a, 0x1a, 0x1a, 0x1a, 0x8d, 0x8e,
	0x8f, 0x90, 0x1a, 0x1a, 0x1a, 0x91, 0x92, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x93, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x94, 0x95, 0x96,
	0x97, 0x1a, 0x98, 0x99, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x9a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x9b, 0x9c, 0x9d, 0x9e, 0x1a,
	0x9f, 0xa0, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0xa2, 0x1a, 0x1a, 0x1a, 0xa3, 0xa4, 0xa7,
	0xab, 0x1a, 0xac, 0xad, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0xae, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0xaf, 0xb0, 0xb1, 0xb2, 0x1a, 0xb3,
	0xb4, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0xb5, 0x1a, 0x1a, 0x1a, 0x1a, 0xbd, 0xbe, 0xbf,
	0xc0, 0x1a, 0xc1, 0xc2, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0xc3, 0x1a, 0x1a, 0x1a, 0x1a, 0xb6,
	0xb7, 0xb8, 0xb9, 0x1a, 0xba, 0xbb, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0xbc, 0x1a, 0x1a
};

const uint8_t libuna_codepage_mac_inuit_unicode_to_byte_stream_base_0x1528[ 56 ] = {
	0xc4, 0xc5, 0xc6, 0xc7, 0x1a, 0xc8, 0xcb, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0xcc, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0xda, 0xdb,
	0xdc, 0xdd, 0x1a, 0xde, 0xdf, 0x1a, 0x1a, 0x1a,
	0xe0, 0x1a, 0x1a, 0x1a, 0x1a, 0xcd, 0xce, 0xcf,
	0xd6, 0xd7, 0xd8, 0x1a, 0x1a, 0xd9, 0x1a, 0x1a
};

const uint8_t libuna_codepage_mac_inuit_unicode_to_byte_stream_base_0x1578[ 48 ] = {
	0x1a, 0x1a, 0x1a, 0x1a, 0xfd, 0x1a, 0x1a, 0xe1,
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0xe8,
	0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xf5, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0x1a
};

const uint8_t libuna_codepage_mac_inuit_unicode_to_byte_stream_base_0x2010[ 24 ] = {
	0x1a, 0x1a, 0x1a, 0xd0, 0xd1, 0x1a, 0x1a, 0x1a,
	0xd4, 0xd5, 0x1a, 0x1a, 0xd2, 0xd3, 0x1a, 0x1a,
	0x1a, 0x1a, 0xa5, 0x1a, 0x1a, 0x1a, 0xc9, 0x1a
};

/* Copies an Unicode character from a MacInuit encoded byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_codepage_mac_inuit_copy_from_byte_stream(
     libuna_unicode_character_t *unicode_character,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     libcerror_error_t **error )
{
	static char *function                             = "libuna_codepage_mac_inuit_copy_from_byte_stream";
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

		safe_unicode_character = libuna_codepage_mac_inuit_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
	}
	*unicode_character = safe_unicode_character;
	*byte_stream_index = safe_byte_stream_index;

	return( 1 );
}

/* Copies an Unicode character to a MacInuit encoded byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_codepage_mac_inuit_copy_to_byte_stream(
     libuna_unicode_character_t unicode_character,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     libcerror_error_t **error )
{
	static char *function         = "libuna_codepage_mac_inuit_copy_to_byte_stream";
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
	if( ( unicode_character < 0x0080 )
	 || ( unicode_character == 0x00a9 ) )
	{
		byte_stream_value = (uint16_t) unicode_character;
	}
	else if( ( unicode_character >= 0x1430 )
	      && ( unicode_character < 0x1508 ) )
	{
		unicode_character -= 0x1430;

		byte_stream_value = libuna_codepage_mac_inuit_unicode_to_byte_stream_base_0x1430[ unicode_character ];
	}
	else if( ( unicode_character >= 0x1528 )
	      && ( unicode_character < 0x1560 ) )
	{
		unicode_character -= 0x1528;

		byte_stream_value = libuna_codepage_mac_inuit_unicode_to_byte_stream_base_0x1528[ unicode_character ];
	}
	else if( ( unicode_character >= 0x1578 )
	      && ( unicode_character < 0x15a8 ) )
	{
		unicode_character -= 0x1578;

		byte_stream_value = libuna_codepage_mac_inuit_unicode_to_byte_stream_base_0x1578[ unicode_character ];
	}
	else if( ( unicode_character >= 0x2010 )
	      && ( unicode_character < 0x2028 ) )
	{
		unicode_character -= 0x2010;

		byte_stream_value = libuna_codepage_mac_inuit_unicode_to_byte_stream_base_0x2010[ unicode_character ];
	}
	else switch( unicode_character )
	{
		case 0x00a0:
			byte_stream_value = 0xca;
			break;

		case 0x00ae:
			byte_stream_value = 0xa8;
			break;

		case 0x00b0:
			byte_stream_value = 0xa1;
			break;

		case 0x00b6:
			byte_stream_value = 0xa6;
			break;

		case 0x0141:
			byte_stream_value = 0xfe;
			break;

		case 0x0142:
			byte_stream_value = 0xff;
			break;

		case 0x1403:
			byte_stream_value = 0x80;
			break;

		case 0x1404:
			byte_stream_value = 0x81;
			break;

		case 0x1405:
			byte_stream_value = 0x82;
			break;

		case 0x1406:
			byte_stream_value = 0x83;
			break;

		case 0x140a:
			byte_stream_value = 0x84;
			break;

		case 0x140b:
			byte_stream_value = 0x85;
			break;

		case 0x1671:
			byte_stream_value = 0xef;
			break;

		case 0x1672:
			byte_stream_value = 0xf0;
			break;

		case 0x1673:
			byte_stream_value = 0xf1;
			break;

		case 0x1674:
			byte_stream_value = 0xf2;
			break;

		case 0x1675:
			byte_stream_value = 0xf3;
			break;

		case 0x1676:
			byte_stream_value = 0xf4;
			break;

		case 0x2122:
			byte_stream_value = 0xaa;
			break;

		default:
			byte_stream_value = 0x1a;
			break;
	}
	byte_stream[ safe_byte_stream_index++ ] = (uint8_t) ( byte_stream_value & 0x00ff );

	*byte_stream_index = safe_byte_stream_index;

	return( 1 );
}

