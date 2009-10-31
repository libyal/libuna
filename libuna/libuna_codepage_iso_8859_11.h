/*
 * ISO 8859-11 codepage (Thai) functions
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

#if !defined( _LIBUNA_CODEPAGE_ISO_8859_11_H )
#define _LIBUNA_CODEPAGE_ISO_8859_11_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define libuna_codepage_iso_8859_11_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0xa1 ) ? byte_stream_character : \
	( byte_stream_character < 0xdb ) ? byte_stream_character + 0x0d60 : \
	( byte_stream_character < 0xdf ) ? 0xfffd : \
	( byte_stream_character < 0xfc ) ? byte_stream_character + 0x0d60 : \
	0xfffd

#define libuna_codepage_iso_8859_11_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x00a1 ) ? (uint8_t) unicode_character : \
	( ( unicode_character >= 0x0e01 ) && ( unicode_character < 0x0e3b ) ) ? (uint8_t) ( unicode_character - 0x0d60 ) : \
	( ( unicode_character >= 0x0e3f ) && ( unicode_character < 0x0e5c ) ) ? (uint8_t) ( unicode_character - 0x0d60 ) : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

