/*
 * UTF-16 stream functions
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

#if !defined( _LIBUCA_UTF16_STREAM_H )
#define _LIBUCA_UTF16_STREAM_H

#include <common.h>
#include <types.h>

#include "libuca_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBUCA_EXTERN int libuca_utf16_stream_copy_from_utf8(
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_utf16_stream_copy_from_utf16(
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_utf16_stream_copy_from_utf32(
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t strict_mode );

#if defined( __cplusplus )
}
#endif

#endif

