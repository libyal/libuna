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
#include "libuca_inline.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_size_to_byte_stream(
                                 libuca_unicode_character_t unicode_character,
                                 int codepage,
                                 size_t *byte_stream_character_size,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_from_byte_stream(
                                 libuca_unicode_character_t *unicode_character,
                                 uint8_t *byte_stream,
                                 size_t byte_stream_size,
                                 size_t *byte_stream_index,
                                 int codepage,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_to_byte_stream(
                                 libuca_unicode_character_t unicode_character,
                                 uint8_t *byte_stream,
                                 size_t byte_stream_size,
                                 size_t *byte_stream_index,
                                 int codepage,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_size_to_utf8(
                                 libuca_unicode_character_t unicode_character,
                                 size_t *utf8_character_size,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_from_utf8(
                                 libuca_unicode_character_t *unicode_character,
                                 libuca_utf8_character_t *utf8_string,
                                 size_t utf8_string_size,
                                 size_t *utf8_string_index,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_to_utf8(
                                 libuca_unicode_character_t unicode_character,
                                 libuca_utf8_character_t *utf8_string,
                                 size_t utf8_string_size,
                                 size_t *utf8_string_index,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE ssize_t libuca_unicode_character_size_to_utf16(
                                     libuca_unicode_character_t unicode_character,
                                     libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_from_utf16(
                                 libuca_unicode_character_t *unicode_character,
                                 libuca_utf16_character_t *utf16_string,
                                 size_t utf16_string_size,
                                 size_t *utf16_string_index,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_to_utf16(
                                 libuca_unicode_character_t unicode_character,
                                 libuca_utf16_character_t *utf16_string,
                                 size_t utf16_string_size,
                                 size_t *utf16_string_index,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_from_utf16_stream(
                                 libuca_unicode_character_t *unicode_character,
                                 uint8_t *utf16_stream,
                                 size_t utf16_stream_size,
                                 size_t *utf16_stream_index,
                                 uint8_t byte_order,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_to_utf16_stream(
                                 libuca_unicode_character_t unicode_character,
                                 uint8_t *utf16_stream,
                                 size_t utf16_stream_size,
                                 size_t *utf16_stream_index,
                                 uint8_t byte_order,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE ssize_t libuca_unicode_character_size_to_utf32(
                                     libuca_unicode_character_t unicode_character,
                                     libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_from_utf32(
                                 libuca_unicode_character_t *unicode_character,
                                 libuca_utf32_character_t *utf32_string,
                                 size_t utf32_string_size,
                                 size_t *utf32_string_index,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_to_utf32(
                                 libuca_unicode_character_t unicode_character,
                                 libuca_utf32_character_t *utf32_string,
                                 size_t utf32_string_size,
                                 size_t *utf32_string_index,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_from_utf32_stream(
                                 libuca_unicode_character_t *unicode_character,
                                 uint8_t *utf32_stream,
                                 size_t utf32_stream_size,
                                 size_t *utf32_stream_index,
                                 uint8_t byte_order,
                                 libuca_error_t **error );

LIBUCA_EXTERN LIBUCA_INLINE int libuca_unicode_character_copy_to_utf32_stream(
                                 libuca_unicode_character_t unicode_character,
                                 uint8_t *utf32_stream,
                                 size_t utf32_stream_size,
                                 size_t *utf32_stream_index,
                                 uint8_t byte_order,
                                 libuca_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

