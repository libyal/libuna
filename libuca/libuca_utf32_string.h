/*
 * UTF-32 string functions
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

#if !defined( _LIBUCA_UTF32_STRING_H )
#define _LIBUCA_UTF32_STRING_H

#include <common.h>
#include <types.h>

#include "libuca_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_byte_stream(
                       uint8_t *byte_stream,
                       size_t byte_stream_size,
                       int codepage );

LIBUCA_EXTERN int libuca_utf32_string_copy_from_byte_stream(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int codepage );

/* The functionality for libuca_utf32_string_copy_to_byte_stream is implemented by
 * libuca_byte_stream_copy_from_utf32
 */

LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_utf8(
                       libuca_utf8_character_t *utf8_string,
                       size_t utf8_string_size );

LIBUCA_EXTERN int libuca_utf32_string_copy_from_utf8(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size );

/* The functionality for libuca_utf32_string_copy_to_utf8 is implemented by
 * libuca_utf8_string_copy_from_utf32
 */

LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_utf8_stream(
                       uint8_t *utf32_stream,
                       size_t utf32_stream_size );

LIBUCA_EXTERN int libuca_utf32_string_copy_from_utf8_stream(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *utf8_stream,
                   size_t utf8_stream_size );

/* The functionality for libuca_utf32_string_copy_to_utf8_stream is implemented by
 * libuca_utf8_stream_copy_from_utf32
 */

LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_utf16(
                       libuca_utf16_character_t *utf16_string,
                       size_t utf16_string_size );

LIBUCA_EXTERN int libuca_utf32_string_copy_from_utf16(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size );

/* The functionality for libuca_utf32_string_copy_to_utf16 is implemented by
 * libuca_utf16_string_copy_from_utf32
 */

LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_utf16_stream(
                       uint8_t *utf16_stream,
                       size_t utf16_stream_size,
                       uint8_t byte_order );

LIBUCA_EXTERN int libuca_utf32_string_copy_from_utf16_stream(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order );

/* The functionality for libuca_utf32_string_copy_to_utf16_stream is implemented by
 * libuca_utf16_stream_copy_from_utf32
 */

LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_utf32_stream(
                       uint8_t *utf32_stream,
                       size_t utf32_stream_size,
                       uint8_t byte_order );

LIBUCA_EXTERN int libuca_utf32_string_copy_from_utf32_stream(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   uint8_t byte_order );

/* The functionality for libuca_utf32_string_copy_to_utf32_stream is implemented by
 * libuca_utf32_stream_copy_from_utf32
 */

#if defined( __cplusplus )
}
#endif

#endif

