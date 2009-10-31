/*
 * Windows 1256 codepage (Arabic) functions
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

#if !defined( _LIBUNA_CODEPAGE_WINDOWS_1256_H )
#define _LIBUNA_CODEPAGE_WINDOWS_1256_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuna_codepage_windows_1256_byte_stream_to_unicode_base_0x80[ 128 ];

extern const uint8_t libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x00a0[ 32 ];
extern const uint8_t libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x00e0[ 32 ];
extern const uint8_t libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x0618[ 64 ];
extern const uint8_t libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x2008[ 32 ];

#define libuna_codepage_windows_1256_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0x80 ) ? byte_stream_character : libuna_codepage_windows_1256_byte_stream_to_unicode_base_0x80[ byte_stream_character - 0x80 ]

#define libuna_codepage_windows_1256_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x0080 ) ? (uint8_t) unicode_character : \
	( ( unicode_character >= 0x00a0 ) && ( unicode_character < 0x00c0 ) ) ? libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x00a0[ unicode_character - 0x00a0 ] : \
	( unicode_character == 0x00d7 ) ? 0xd7 : \
	( ( unicode_character >= 0x00e0 ) && ( unicode_character < 0x0100 ) ) ? libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x00e0[ unicode_character - 0x00e0 ] : \
	( unicode_character == 0x0152 ) ? 0x8c : \
	( unicode_character == 0x0153 ) ? 0x9c : \
	( unicode_character == 0x0192 ) ? 0x83 : \
	( unicode_character == 0x02c6 ) ? 0x88 : \
	( unicode_character == 0x060c ) ? 0xa1 : \
	( ( unicode_character >= 0x0618 ) && ( unicode_character < 0x0658 ) ) ? libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x0618[ unicode_character - 0x0618 ] : \
	( unicode_character == 0x0679 ) ? 0x8a : \
	( unicode_character == 0x067e ) ? 0x81 : \
	( unicode_character == 0x0686 ) ? 0x8d : \
	( unicode_character == 0x0688 ) ? 0x8f : \
	( unicode_character == 0x0691 ) ? 0x9a : \
	( unicode_character == 0x0698 ) ? 0x8e : \
	( unicode_character == 0x06a9 ) ? 0x98 : \
	( unicode_character == 0x06af ) ? 0x90 : \
	( unicode_character == 0x06ba ) ? 0x9f : \
	( unicode_character == 0x06be ) ? 0xaa : \
	( unicode_character == 0x06c1 ) ? 0xc0 : \
	( unicode_character == 0x06d2 ) ? 0xff : \
	( ( unicode_character >= 0x2008 ) && ( unicode_character < 0x2028 ) ) ? libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x2008[ unicode_character - 0x2008 ] : \
	( unicode_character == 0x2030 ) ? 0x89 : \
	( unicode_character == 0x2039 ) ? 0x8b : \
	( unicode_character == 0x203a ) ? 0x9b : \
	( unicode_character == 0x20ac ) ? 0x80 : \
	( unicode_character == 0x2122 ) ? 0x99 : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

