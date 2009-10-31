/*
 * ISO 8859-1 codepage (Western European) functions
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

#if !defined( _LIBUNA_CODEPAGE_ISO_8859_1_H )
#define _LIBUNA_CODEPAGE_ISO_8859_1_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define libuna_codepage_iso_8859_1_byte_stream_to_unicode( byte_stream_character ) \
	byte_stream_character

#define libuna_codepage_iso_8859_1_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x0100 ) ? (uint8_t) unicode_character : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

