/*
 * Windows 936 codepage (Chinese Simplified) functions
 *
 * Copyright (c) 2008-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBUNA_CODEPAGE_WINDOWS_936_H )
#define _LIBUNA_CODEPAGE_WINDOWS_936_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8140[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8240[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8340[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8440[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8540[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8640[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8740[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8840[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8940[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8a40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8b40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8c40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8d40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8e40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8f40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9040[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9140[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9240[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9340[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9440[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9540[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9640[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9740[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9840[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9940[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9a40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9b40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9c40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9d40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9e40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9f40[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa040[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa040[ 192 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa1a0[ 96 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa2a0[ 96 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa3a0[ 96 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa4a0[ 88 ];
extern const uint16_t libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa5a0[ 88 ];

extern const uint8_t libuna_codepage_windows_936_unicode_to_byte_stream_base_0x2018[ 8 ];

#define libuna_codepage_windows_936_byte_stream_to_unicode( byte_stream ) \
	( byte_stream[ 0 ] < 0x80 ) ? byte_stream[ 0 ] : \
	( byte_stream[ 0 ] == 0x80 ) ? 0x20ac : \
	( ( byte_stream[ 0 ] == 0x81 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8140[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x82 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8240[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x83 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8340[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x84 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8440[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x85 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8540[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x86 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8640[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x87 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8740[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x88 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8840[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x89 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8940[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x8a ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8a40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x8b ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8b40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x8c ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8c40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x8d ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8d40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x8e ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8e40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x8f ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8f40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x90 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9040[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x91 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9140[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x92 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9240[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x93 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9340[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x94 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9440[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x95 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9540[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x96 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9640[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x97 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9740[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x98 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9840[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x99 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9940[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x9a ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9a40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x9b ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9b40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x9c ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9c40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x9d ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9d40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x9e ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9e40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0x9f ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9f40[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0xa0 ) && ( byte_stream[ 1 ] >= 0x40 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa040[ byte_stream[ 1 ] - 0x40 ] : \
	( ( byte_stream[ 0 ] == 0xa1 ) && ( byte_stream[ 1 ] >= 0xa0 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa1a0[ byte_stream[ 1 ] - 0xa0 ] : \
	( ( byte_stream[ 0 ] == 0xa2 ) && ( byte_stream[ 1 ] >= 0xa0 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa2a0[ byte_stream[ 1 ] - 0xa0 ] : \
	( ( byte_stream[ 0 ] == 0xa3 ) && ( byte_stream[ 1 ] >= 0xa0 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa3a0[ byte_stream[ 1 ] - 0xa0 ] : \
	( ( byte_stream[ 0 ] == 0xa4 ) && ( byte_stream[ 1 ] >= 0xa0 ) && ( byte_stream[ 1 ] < 0xf8 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa4a0[ byte_stream[ 1 ] - 0xa0 ] : \
	( ( byte_stream[ 0 ] == 0xa5 ) && ( byte_stream[ 1 ] >= 0xa0 ) && ( byte_stream[ 1 ] < 0xf8 ) ) ? \
		libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa5a0[ byte_stream[ 1 ] - 0xa0 ] : \
	0xfffd

#define libuna_codepage_windows_936_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x0080 ) ? (uint8_t) unicode_character : \
	( ( unicode_character >= 0x00e0 ) && ( unicode_character < 0x0140 ) ) ? libuna_codepage_windows_936_unicode_to_byte_stream_base_0x00e0[ unicode_character - 0x00e0 ] : \
	( unicode_character == 0x20ac ) ? 0x80 : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

