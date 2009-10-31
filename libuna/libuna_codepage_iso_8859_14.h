/*
 * ISO 8859-14 codepage (Celtic) functions
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

#if !defined( _LIBUNA_CODEPAGE_ISO_8859_14_H )
#define _LIBUNA_CODEPAGE_ISO_8859_14_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuna_codepage_iso_8859_14_byte_stream_to_unicode_base_0xa0[ 96 ];

extern const uint8_t libuna_codepage_iso_8859_14_unicode_to_byte_stream_base_0x00c0[ 64 ];
extern const uint8_t libuna_codepage_iso_8859_14_unicode_to_byte_stream_base_0x0170[ 8 ];
extern const uint8_t libuna_codepage_iso_8859_14_unicode_to_byte_stream_base_0x1e80[ 8 ];

#define libuna_codepage_iso_8859_14_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0xa0 ) ? byte_stream_character : libuna_codepage_iso_8859_14_byte_stream_to_unicode_base_0xa0[ byte_stream_character - 0xa0 ]

#define libuna_codepage_iso_8859_14_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x00a1 ) ? (uint8_t) unicode_character : \
	( unicode_character == 0x00a3 ) ? 0xa3 : \
	( unicode_character == 0x00a7 ) ? 0xa7 : \
	( unicode_character == 0x00a9 ) ? 0xa9 : \
	( unicode_character == 0x00ad ) ? 0xad : \
	( unicode_character == 0x00ae ) ? 0xae : \
	( unicode_character == 0x00b6 ) ? 0xb6 : \
	( ( unicode_character >= 0x00c0 ) && ( unicode_character < 0x0100 ) ) ? libuna_codepage_iso_8859_14_unicode_to_byte_stream_base_0x00c0[ unicode_character - 0x00c0 ] : \
	( unicode_character == 0x010a ) ? 0xa4 : \
	( unicode_character == 0x010b ) ? 0xa5 : \
	( unicode_character == 0x0120 ) ? 0xb2 : \
	( unicode_character == 0x0121 ) ? 0xb3 : \
	( ( unicode_character >= 0x0170 ) && ( unicode_character < 0x0178 ) ) ? libuna_codepage_iso_8859_14_unicode_to_byte_stream_base_0x0170[ unicode_character - 0x0170 ] : \
	( unicode_character == 0x0178 ) ? 0xaf : \
	( unicode_character == 0x1e02 ) ? 0xa1 : \
	( unicode_character == 0x1e03 ) ? 0xa2 : \
	( unicode_character == 0x1e0a ) ? 0xa6 : \
	( unicode_character == 0x1e0b ) ? 0xab : \
	( unicode_character == 0x1e1e ) ? 0xb0 : \
	( unicode_character == 0x1e1f ) ? 0xb1 : \
	( unicode_character == 0x1e40 ) ? 0xb4 : \
	( unicode_character == 0x1e41 ) ? 0xb5 : \
	( unicode_character == 0x1e56 ) ? 0xb7 : \
	( unicode_character == 0x1e57 ) ? 0xb9 : \
	( unicode_character == 0x1e60 ) ? 0xbb : \
	( unicode_character == 0x1e61 ) ? 0xbf : \
	( unicode_character == 0x1e6a ) ? 0xd7 : \
	( unicode_character == 0x1e6b ) ? 0xf7 : \
	( ( unicode_character >= 0x1e80 ) && ( unicode_character < 0x1e88 ) ) ? libuna_codepage_iso_8859_14_unicode_to_byte_stream_base_0x1e80[ unicode_character - 0x1e80 ] : \
	( unicode_character == 0x1ef2 ) ? 0xac : \
	( unicode_character == 0x1ef3 ) ? 0xbc : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

