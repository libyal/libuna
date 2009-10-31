/*
 * Windows 874 codepage (Thai) functions
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

#if !defined( _LIBUNA_CODEPAGE_WINDOWS_874_H )
#define _LIBUNA_CODEPAGE_WINDOWS_874_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuna_codepage_windows_874_byte_stream_to_unicode_base_0x80[ 128 ];

extern const uint8_t libuna_codepage_windows_874_unicode_to_byte_stream_base_0x00e0[ 96 ];
extern const uint8_t libuna_codepage_windows_874_unicode_to_byte_stream_base_0x2018[ 8 ];

#define libuna_codepage_windows_874_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0x80 ) ? byte_stream_character : libuna_codepage_windows_874_byte_stream_to_unicode_base_0x80[ byte_stream_character - 0x80 ]

#define libuna_codepage_windows_874_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x0080 ) ? (uint8_t) unicode_character : \
	( ( unicode_character >= 0x00e0 ) && ( unicode_character < 0x0140 ) ) ? libuna_codepage_windows_874_unicode_to_byte_stream_base_0x00e0[ unicode_character - 0x00e0 ] : \
	( unicode_character == 0x2013 ) ? 0x96 : \
	( unicode_character == 0x2014 ) ? 0x97 : \
	( ( unicode_character >= 0x2018 ) && ( unicode_character < 0x2020 ) ) ? libuna_codepage_windows_874_unicode_to_byte_stream_base_0x2018[ unicode_character - 0x2018 ] : \
	( unicode_character == 0x2022 ) ? 0x95 : \
	( unicode_character == 0x2026 ) ? 0x85 : \
	( unicode_character == 0x20ac ) ? 0x80 : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

