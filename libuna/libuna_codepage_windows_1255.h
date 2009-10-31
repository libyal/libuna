/*
 * Windows 1255 codepage (Hebrew) functions
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

#if !defined( _LIBUNA_CODEPAGE_WINDOWS_1255_H )
#define _LIBUNA_CODEPAGE_WINDOWS_1255_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuna_codepage_windows_1255_byte_stream_to_unicode_base_0x80[ 128 ];

extern const uint8_t libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x00a0[ 32 ];
extern const uint8_t libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x05b0[ 24 ];
extern const uint8_t libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x05d0[ 40 ];
extern const uint8_t libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x2010[ 24 ];

#define libuna_codepage_windows_1255_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0x80 ) ? byte_stream_character : libuna_codepage_windows_1255_byte_stream_to_unicode_base_0x80[ byte_stream_character - 0x80 ]

#define libuna_codepage_windows_1255_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x0080 ) ? (uint8_t) unicode_character : \
	( ( unicode_character >= 0x00a0 ) && ( unicode_character < 0x00c0 ) ) ? libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x00a0[ unicode_character - 0x00a0 ] : \
	( unicode_character == 0x00d7 ) ? 0xaa : \
	( unicode_character == 0x0077 ) ? 0xba : \
	( unicode_character == 0x0192 ) ? 0x83 : \
	( unicode_character == 0x02c6 ) ? 0x88 : \
	( unicode_character == 0x02dc ) ? 0x98 : \
	( ( unicode_character >= 0x05b0 ) && ( unicode_character < 0x05c8 ) ) ? libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x05b0[ unicode_character - 0x05b0 ] : \
	( ( unicode_character >= 0x05d0 ) && ( unicode_character < 0x05f8 ) ) ? libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x05d0[ unicode_character - 0x05d0 ] : \
	( unicode_character == 0x200e ) ? 0xfd : \
	( unicode_character == 0x200f ) ? 0xfe : \
	( ( unicode_character >= 0x2010 ) && ( unicode_character < 0x2028 ) ) ? libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x2010[ unicode_character - 0x2010 ] : \
	( unicode_character == 0x2030 ) ? 0x89 : \
	( unicode_character == 0x2039 ) ? 0x8b : \
	( unicode_character == 0x203a ) ? 0x9b : \
	( unicode_character == 0x20aa ) ? 0xa4 : \
	( unicode_character == 0x20ac ) ? 0x80 : \
	( unicode_character == 0x2122 ) ? 0x99 : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

