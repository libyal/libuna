/*
 * ASCII codepage functions
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

#if !defined( _LIBUCA_CODEPAGE_ASCII_H )
#define _LIBUCA_CODEPAGE_ASCII_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define libuca_codepage_ascii_sbc_to_unicode( sbc_character ) \
	( sbc_character < 0x80 ) ? sbc_character : 0xfffd

#define libuca_codepage_ascii_unicode_to_sbc( unicode_character ) \
	( unicode_character < 0x0080 ) ? (uint8_t) unicode_character : 0x1a

#if defined( __cplusplus )
}
#endif

#endif

