/*
 * ISO 8859-10 codepage (Nordic) functions
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

#if !defined( _LIBUNA_CODEPAGE_ISO_8859_10_H )
#define _LIBUNA_CODEPAGE_ISO_8859_10_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuna_codepage_iso_8859_10_byte_stream_to_unicode_base_0xa0[ 96 ];

extern const uint8_t libuna_codepage_iso_8859_10_unicode_to_byte_stream_base_0x00c0[ 144 ];
extern const uint8_t libuna_codepage_iso_8859_10_unicode_to_byte_stream_base_0x0160[ 16 ];

#define libuna_codepage_iso_8859_10_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0xa0 ) ? byte_stream_character : libuna_codepage_iso_8859_10_byte_stream_to_unicode_base_0xa0[ byte_stream_character - 0xa0 ]

#define libuna_codepage_iso_8859_10_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x00a1 ) ? (uint8_t) unicode_character : \
	( unicode_character == 0x00a7 ) ? 0xa7 : \
	( unicode_character == 0x00ad ) ? 0xad : \
	( unicode_character == 0x00b0 ) ? 0xb0 : \
	( unicode_character == 0x00b7 ) ? 0xb7 : \
	( ( unicode_character >= 0x00c0 ) && ( unicode_character < 0x0150 ) ) ? libuna_codepage_iso_8859_10_unicode_to_byte_stream_base_0x00c0[ unicode_character - 0x00c0 ] : \
	( ( unicode_character >= 0x0160 ) && ( unicode_character < 0x0170 ) ) ? libuna_codepage_iso_8859_10_unicode_to_byte_stream_base_0x0160[ unicode_character - 0x0160 ] : \
	( unicode_character == 0x0172 ) ? 0xd9 : \
	( unicode_character == 0x0173 ) ? 0xf9 : \
	( unicode_character == 0x017d ) ? 0xac : \
	( unicode_character == 0x017e ) ? 0xbc : \
	( unicode_character == 0x2015 ) ? 0xbd : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

