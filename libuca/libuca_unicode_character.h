/*
 * Unicode character functions
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

#if !defined( _LIBUCA_UNICDODE_CHARACTER_H )
#define _LIBUCA_UNICDODE_CHARACTER_H

#include <common.h>
#include <types.h>

#include "libuca_definitions.h"
#include "libuca_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBUCA_EXTERN int libuca_unicode_character_copy_from_byte_stream(
                   libuca_unicode_character_t *unicode_character,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   int code_page,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_unicode_character_copy_to_byte_stream(
                   libuca_unicode_character_t unicode_character,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   int code_page,
                   uint8_t strict_mode );

#define libuca_unicode_character_size_to_utf8( unicode_character, strict_mode ) \
        ( unicode_character < 0x0000080 ) ? 1 : \
        ( unicode_character < 0x0000800 ) ? 2 : \
        ( unicode_character < 0x0010000 ) ? 3 : \
        ( ( strict_mode != 0 ) && ( unicode_character > LIBUCA_UNICODE_CHARACTER_MAX ) ) ? 3 : \
        ( unicode_character < 0x0200000 ) ? 4 : \
        ( unicode_character < 0x0400000 ) ? 5 : 6

LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf8(
                   libuca_unicode_character_t *unicode_character,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   size_t *utf8_string_index,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf8(
                   libuca_unicode_character_t unicode_character,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   size_t *utf8_string_index,
                   uint8_t strict_mode );

#define libuca_unicode_character_size_to_utf16( unicode_character, strict_mode ) \
        ( ( unicode_character > LIBUCA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX ) \
         && ( unicode_character <= LIBUCA_UTF16_CHARACTER_MAX ) ) ? 2 : 1

LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf16(
                   libuca_unicode_character_t *unicode_character,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   size_t *utf16_string_index,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf16(
                   libuca_unicode_character_t unicode_character,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   size_t *utf16_string_index,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf16_stream(
                   libuca_unicode_character_t *unicode_character,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   size_t *utf16_stream_index,
                   uint8_t byte_order,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf16_stream(
                   libuca_unicode_character_t unicode_character,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   size_t *utf16_stream_index,
                   uint8_t byte_order,
                   uint8_t strict_mode );

#define libuca_unicode_character_size_to_utf32( unicode_character, strict_mode ) \
        1

LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf32(
                   libuca_unicode_character_t *unicode_character,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   size_t *utf32_string_index,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf32(
                   libuca_unicode_character_t unicode_character,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   size_t *utf32_string_index,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf32_stream(
                   libuca_unicode_character_t *unicode_character,
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   size_t *utf32_stream_index,
                   uint8_t byte_order,
                   uint8_t strict_mode );

LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf32_stream(
                   libuca_unicode_character_t unicode_character,
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   size_t *utf32_stream_index,
                   uint8_t byte_order,
                   uint8_t strict_mode );

#if defined( __cplusplus )
}
#endif

#endif

