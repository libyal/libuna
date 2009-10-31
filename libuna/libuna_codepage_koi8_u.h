/*
 * KOI8-U codepage (Ukrainian Cyrillic) functions
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

#if !defined( _LIBUNA_CODEPAGE_KOI8_U_H )
#define _LIBUNA_CODEPAGE_KOI8_U_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuna_codepage_koi8_u_byte_stream_to_unicode_base_0x80[ 128 ];

extern const uint8_t libuna_codepage_koi8_u_unicode_to_byte_stream_base_0x0410[ 64 ];
extern const uint8_t libuna_codepage_koi8_u_unicode_to_byte_stream_base_0x2550[ 32 ];

#define libuna_codepage_koi8_u_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0x80 ) ? byte_stream_character : libuna_codepage_koi8_u_byte_stream_to_unicode_base_0x80[ byte_stream_character - 0x80 ]

#define libuna_codepage_koi8_u_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x0080 ) ? (uint8_t) unicode_character : \
	( unicode_character == 0x00a0 ) ? 0x9a : \
	( unicode_character == 0x00a9 ) ? 0xbf : \
	( unicode_character == 0x00b0 ) ? 0x9c : \
	( unicode_character == 0x00b2 ) ? 0x9d : \
	( unicode_character == 0x00b8 ) ? 0x9e : \
	( unicode_character == 0x00f8 ) ? 0x9f : \
	( unicode_character == 0x0401 ) ? 0xb3 : \
	( unicode_character == 0x0404 ) ? 0xb4 : \
	( unicode_character == 0x0406 ) ? 0xb6 : \
	( unicode_character == 0x0407 ) ? 0xb7 : \
	( ( unicode_character >= 0x0410 ) && ( unicode_character < 0x0450 ) ) ? libuna_codepage_koi8_u_unicode_to_byte_stream_base_0x0410[ unicode_character - 0x0410 ] : \
	( unicode_character == 0x0451 ) ? 0xa3 : \
	( unicode_character == 0x0454 ) ? 0xa4 : \
	( unicode_character == 0x0456 ) ? 0xa6 : \
	( unicode_character == 0x0457 ) ? 0xa7 : \
	( unicode_character == 0x0490 ) ? 0xbd : \
	( unicode_character == 0x0491 ) ? 0xad : \
	( unicode_character == 0x2219 ) ? 0x95 : \
	( unicode_character == 0x221a ) ? 0x96 : \
	( unicode_character == 0x2248 ) ? 0x97 : \
	( unicode_character == 0x2264 ) ? 0x98 : \
	( unicode_character == 0x2265 ) ? 0x99 : \
	( unicode_character == 0x2320 ) ? 0x93 : \
	( unicode_character == 0x2321 ) ? 0x9b : \
	( unicode_character == 0x2500 ) ? 0x80 : \
	( unicode_character == 0x2502 ) ? 0x81 : \
	( unicode_character == 0x250c ) ? 0x82 : \
	( unicode_character == 0x2510 ) ? 0x83 : \
	( unicode_character == 0x2514 ) ? 0x84 : \
	( unicode_character == 0x2518 ) ? 0x85 : \
	( unicode_character == 0x251c ) ? 0x86 : \
	( unicode_character == 0x2524 ) ? 0x87 : \
	( unicode_character == 0x252c ) ? 0x88 : \
	( unicode_character == 0x2534 ) ? 0x89 : \
	( unicode_character == 0x253c ) ? 0x8a : \
	( ( unicode_character >= 0x2550 ) && ( unicode_character < 0x2570 ) ) ? libuna_codepage_koi8_u_unicode_to_byte_stream_base_0x2550[ unicode_character - 0x2550 ] : \
	( unicode_character == 0x2580 ) ? 0x8b : \
	( unicode_character == 0x2584 ) ? 0x8c : \
	( unicode_character == 0x2588 ) ? 0x8d : \
	( unicode_character == 0x258c ) ? 0x8e : \
	( unicode_character == 0x2590 ) ? 0x8f : \
	( unicode_character == 0x2591 ) ? 0x90 : \
	( unicode_character == 0x2592 ) ? 0x91 : \
	( unicode_character == 0x2593 ) ? 0x92 : \
	( unicode_character == 0x25a0 ) ? 0x94 : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

