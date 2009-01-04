/*
 * Windows 1254 codepage functions
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

#if !defined( _LIBUCA_CODEPAGE_WINDOWS_1254_H )
#define _LIBUCA_CODEPAGE_WINDOWS_1254_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuca_codepage_windows_1254_byte_stream_to_unicode_base_0x80[];
extern const uint16_t libuca_codepage_windows_1254_byte_stream_to_unicode_base_0xd0[];
extern const uint16_t libuca_codepage_windows_1254_byte_stream_to_unicode_base_0xf0[];

extern const uint8_t libuca_codepage_windows_1254_unicode_to_byte_stream_base_0x00d0[];
extern const uint8_t libuca_codepage_windows_1254_unicode_to_byte_stream_base_0x0118[];
extern const uint8_t libuca_codepage_windows_1254_unicode_to_byte_stream_base_0x02c0[];
extern const uint8_t libuca_codepage_windows_1254_unicode_to_byte_stream_base_0x2010[];

#define libuca_codepage_windows_1254_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0x80 ) ? byte_stream_character : \
	( byte_stream_character < 0xa0 ) ? libuca_codepage_windows_1254_byte_stream_to_unicode_base_0x80[ byte_stream_character - 0x80 ] : \
	( byte_stream_character < 0xd0 ) ? byte_stream_character : \
	( byte_stream_character < 0xe0 ) ? libuca_codepage_windows_1254_byte_stream_to_unicode_base_0xd0[ byte_stream_character - 0xd0 ] : \
	( byte_stream_character < 0xf0 ) ? byte_stream_character : libuca_codepage_windows_1254_byte_stream_to_unicode_base_0xd0[ byte_stream_character - 0xf0 ]

#define libuca_codepage_windows_1254_unicode_to_byte_stream( unicode_character ) \
	( ( unicode_character < 0x0080 ) || ( ( unicode_character >= 0x00a0 ) && ( unicode_character < 0x00d0 ) ) ) ? (uint8_t) unicode_character : \
	( ( unicode_character >= 0x00d0 ) && ( unicode_character < 0x0100 ) ) ? libuca_codepage_windows_1254_unicode_to_byte_stream_base_0x00d0[ unicode_character - 0x00d0 ] : \
	( ( unicode_character >= 0x0118 ) && ( unicode_character < 0x0198 ) ) ? libuca_codepage_windows_1254_unicode_to_byte_stream_base_0x0118[ unicode_character - 0x0118 ] : \
	( ( unicode_character >= 0x02c0 ) && ( unicode_character < 0x02e0 ) ) ? libuca_codepage_windows_1254_unicode_to_byte_stream_base_0x02c0[ unicode_character - 0x02c0 ] : \
	( ( unicode_character >= 0x2010 ) && ( unicode_character < 0x2040 ) ) ? libuca_codepage_windows_1254_unicode_to_byte_stream_base_0x2010[ unicode_character - 0x2010 ] : \
	( unicode_character == 0x2010 ) ? 0x80 : \
	( unicode_character == 0x2122 ) ? 0x99 : 0x1a

#if defined( __cplusplus )
}
#endif

#endif

