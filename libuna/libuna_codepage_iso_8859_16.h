/*
 * ISO 8859-16 codepage (Latin 10) functions
 *
 * Copyright (c) 2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBUNA_CODEPAGE_ISO_8859_16_H )
#define _LIBUNA_CODEPAGE_ISO_8859_16_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuna_codepage_iso_8859_16_byte_stream_to_unicode_base_0xa0[ 96 ];

extern const uint8_t libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x00a8[ 96 ];
extern const uint8_t libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0140[ 8 ];
extern const uint8_t libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0150[ 8 ];
extern const uint8_t libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0178[ 8 ];
extern const uint8_t libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0218[ 8 ];

#define libuna_codepage_iso_8859_16_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0xa0 ) ? byte_stream_character : libuna_codepage_iso_8859_16_byte_stream_to_unicode_base_0xa0[ byte_stream_character - 0xa0 ]

#define libuna_codepage_iso_8859_16_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x00a1 ) ? (uint8_t) unicode_character : \
	( unicode_character == 0x00a7 ) ? 0xa7 : \
	( ( unicode_character >= 0x00a8 ) && ( unicode_character < 0x0108 ) ) ? libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x00a8[ unicode_character - 0x00a8 ] : \
	( unicode_character == 0x010c ) ? 0xb2 : \
	( unicode_character == 0x010d ) ? 0xb9 : \
	( unicode_character == 0x0110 ) ? 0xd0 : \
	( unicode_character == 0x0111 ) ? 0xf0 : \
	( unicode_character == 0x0118 ) ? 0xdd : \
	( unicode_character == 0x0119 ) ? 0xfd : \
	( ( unicode_character >= 0x0140 ) && ( unicode_character < 0x0148 ) ) ? libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0140[ unicode_character - 0x0140 ] : \
	( ( unicode_character >= 0x0150 ) && ( unicode_character < 0x0158 ) ) ? libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0150[ unicode_character - 0x0150 ] : \
	( unicode_character == 0x015a ) ? 0xd7 : \
	( unicode_character == 0x015b ) ? 0xf7 : \
	( unicode_character == 0x0160 ) ? 0xa6 : \
	( unicode_character == 0x0161 ) ? 0xa8 : \
	( unicode_character == 0x0170 ) ? 0xd8 : \
	( unicode_character == 0x0171 ) ? 0xf8 : \
	( ( unicode_character >= 0x0178 ) && ( unicode_character < 0x0180 ) ) ? libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0178[ unicode_character - 0x0178 ] : \
	( ( unicode_character >= 0x0218 ) && ( unicode_character < 0x0220 ) ) ? libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0218[ unicode_character - 0x0218 ] : \
	( unicode_character == 0x201d ) ? 0xb5 : \
	( unicode_character == 0x201e ) ? 0xa5 : \
	( unicode_character == 0x20ac ) ? 0xa4 : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

