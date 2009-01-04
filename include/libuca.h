/*
 * Library to support Unicode and ASCII (byte stream) conversions
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

#if !defined( _LIBUCA_H )
#define _LIBUCA_H

#include <libuca/definitions.h>
#include <libuca/extern.h>
#include <libuca/features.h>
#include <libuca/types.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* Returns the library version as a string
 */
#if defined( LIBUCA_WIDE_CHARACTER_TYPE )
LIBUCA_EXTERN const wchar_t *libuca_get_version(
                              void );
#else
LIBUCA_EXTERN const char *libuca_get_version(
                           void );
#endif

/* Set the notify values
 */
LIBUCA_EXTERN void libuca_set_notify_values(
                    FILE *stream,
                    uint8_t verbose );

/* -------------------------------------------------------------------------
 * Unicode character functions
 * ------------------------------------------------------------------------- */

/* Copies a Unicode character from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_from_byte_stream(
                   libuca_unicode_character_t *unicode_character,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   int code_page,
                   uint8_t strict_mode );

/* Copies a Unicode character to a byte stream string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_to_byte_stream(
                   libuca_unicode_character_t unicode_character,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   int code_page,
                   uint8_t strict_mode );

/* Copies a Unicode character from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf8(
                   libuca_unicode_character_t *unicode_character,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   size_t *utf8_string_index,
                   uint8_t strict_mode );

/* Copies a Unicode character into a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf8(
                   libuca_unicode_character_t unicode_character,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   size_t *utf8_string_index,
                   uint8_t strict_mode );

/* Copies a Unicode character from a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf16(
                   libuca_unicode_character_t *unicode_character,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   size_t *utf16_string_index,
                   uint8_t strict_mode );

/* Copies a Unicode character into a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf16(
                   libuca_unicode_character_t unicode_character,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   size_t *utf16_string_index,
                   uint8_t strict_mode );

/* Copies a Unicode character from a UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf16_stream(
                   libuca_unicode_character_t *unicode_character,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   size_t *utf16_stream_index,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* Copies a Unicode character to an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf16_stream(
                   libuca_unicode_character_t unicode_character,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   size_t *utf16_stream_index,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* Copies a Unicode character from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf32(
                   libuca_unicode_character_t *unicode_character,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   size_t *utf32_string_index,
                   uint8_t strict_mode );

/* Copies a Unicode character into a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf32(
                   libuca_unicode_character_t unicode_character,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   size_t *utf32_string_index,
                   uint8_t strict_mode );

/* Copies a Unicode character from a UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_from_utf32_stream(
                   libuca_unicode_character_t *unicode_character,
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   size_t *utf32_stream_index,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* Copies a Unicode character to an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_unicode_character_copy_to_utf32_stream(
                   libuca_unicode_character_t unicode_character,
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   size_t *utf32_stream_index,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* -------------------------------------------------------------------------
 * Byte stream functions
 * ------------------------------------------------------------------------- */

/* Copies a byte stream from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_byte_stream_copy_from_utf8(
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int code_page,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t strict_mode );

/* Copies a byte stream from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_byte_stream_copy_from_utf16(
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int code_page,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t strict_mode );

/* Copies a byte stream from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_byte_stream_copy_from_utf32(
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int code_page,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t strict_mode );

/* -------------------------------------------------------------------------
 * UTF-8 string functions
 * ------------------------------------------------------------------------- */

/* Determines the size of a UTF-8 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf8_string_size_from_byte_stream(
                       uint8_t *byte_stream,
                       size_t byte_stream_size,
                       int code_page,
                       uint8_t strict_mode );

/* Copies an UTF-8 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf8_string_copy_from_byte_stream(
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int code_page,
                   uint8_t strict_mode );

/* The functionality for libuca_utf8_string_copy_to_byte_stream is implemented by
 * libuca_byte_stream_copy_from_utf8
 */

/* Determines the size of a UTF-8 string from a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf8_string_size_from_utf16(
                       libuca_utf16_character_t *utf16_string,
                       size_t utf16_string_size,
                       uint8_t strict_mode );

/* Copies an UTF-8 string from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf8_string_copy_from_utf16(
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t strict_mode );

/* The functionality for libuca_utf8_string_copy_to_utf16 is implemented by
 * libuca_utf16_string_size_from_utf8
 */

/* Determines the size of a UTF-8 string from a UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf8_string_size_from_utf16_stream(
                       uint8_t *utf16_stream,
                       size_t utf16_stream_size,
                       uint8_t byte_order,
                       uint8_t strict_mode );

/* Copies an UTF-8 string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf8_string_copy_from_utf16_stream(
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* The functionality for libuca_utf8_string_copy_to_utf16_stream is implemented by
 * libuca_utf16_stream_size_from_utf8
 */

/* Determines the size of a UTF-8 string from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf8_string_size_from_utf32(
                       libuca_utf32_character_t *utf32_string,
                       size_t utf32_string_size,
                       uint8_t strict_mode );

/* Copies an UTF-8 string from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf8_string_copy_from_utf32(
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t strict_mode );

/* The functionality for libuca_utf8_string_copy_to_utf32 is implemented by
 * libuca_utf32_string_size_from_utf8
 */

/* Determines the size of a UTF-8 string from a UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf8_string_size_from_utf32_stream(
                       uint8_t *utf32_stream,
                       size_t utf32_stream_size,
                       uint8_t byte_order,
                       uint8_t strict_mode );

/* Copies an UTF-8 string from an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf8_string_copy_from_utf32_stream(
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* The functionality for libuca_utf8_string_copy_to_utf32_stream is implemented by
 * libuca_utf32_stream_size_from_utf8
 */

/* -------------------------------------------------------------------------
 * UTF-16 string functions
 * ------------------------------------------------------------------------- */

/* Determines the size of a UTF-16 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf16_string_size_from_byte_stream(
                       uint8_t *byte_stream,
                       size_t byte_stream_size,
                       int code_page,
                       uint8_t strict_mode );

/* Copies an UTF-16 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_string_copy_from_byte_stream(
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int code_page,
                   uint8_t strict_mode );

/* The functionality for libuca_utf16_string_copy_to_byte_stream is implemented by
 * libuca_byte_stream_copy_from_utf16
 */

/* Determines the size of a UTF-16 string from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf16_string_size_from_utf8(
                       libuca_utf8_character_t *utf8_string,
                       size_t utf8_string_size,
                       uint8_t strict_mode );

/* Copies an UTF-16 string from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_string_copy_from_utf8(
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t strict_mode );

/* The functionality for libuca_utf16_string_copy_to_utf8 is implemented by
 * libuca_utf8_string_size_from_utf16
 */

/* Determines the size of a UTF-16 string from a UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf16_string_size_from_utf16_stream(
                       uint8_t *utf16_stream,
                       size_t utf16_stream_size,
                       uint8_t byte_order,
                       uint8_t strict_mode );

/* Copies an UTF-16 string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_string_copy_from_utf16_stream(
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* The functionality for libuca_utf16_string_copy_to_utf16_stream is implemented by
 * libuca_utf16_stream_copy_from_utf16
 */

/* Determines the size of a UTF-16 string from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf16_string_size_from_utf32(
                       libuca_utf32_character_t *utf32_string,
                       size_t utf32_string_size,
                       uint8_t strict_mode );

/* Copies an UTF-16 string from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_string_copy_from_utf32(
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t strict_mode );

/* The functionality for libuca_utf16_string_copy_to_utf32 is implemented by
 * libuca_utf32_string_size_from_utf16
 */

/* Determines the size of a UTF-16 string from a UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf16_string_size_from_utf32_stream(
                       uint8_t *utf32_stream,
                       size_t utf32_stream_size,
                       uint8_t byte_order,
                       uint8_t strict_mode );

/* Copies an UTF-16 string from an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_string_copy_from_utf32_stream(
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* The functionality for libuca_utf16_string_copy_to_utf32_stream is implemented by
 * libuca_utf32_stream_size_from_utf16
 */

/* -------------------------------------------------------------------------
 * UTF-16 stream functions
 * ------------------------------------------------------------------------- */

/* Copies an UTF-16 stream from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_stream_copy_to_utf8(
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t strict_mode );

/* Copies an UTF-16 stream from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_stream_copy_to_utf16(
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t strict_mode );

/* Copies an UTF-16 stream from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_stream_copy_to_utf32(
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t strict_mode );

/* -------------------------------------------------------------------------
 * UTF-32 string functions
 * ------------------------------------------------------------------------- */

/* Determines the size of a UTF-32 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_byte_stream(
                       uint8_t *byte_stream,
                       size_t byte_stream_size,
                       int code_page,
                       uint8_t strict_mode );

/* Copies an UTF-32 string from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_string_copy_from_byte_stream(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int code_page,
                   uint8_t strict_mode );

/* The functionality for libuca_utf16_string_copy_to_byte_stream is implemented by
 * libuca_byte_stream_copy_from_utf16
 */

/* Determines the size of a UTF-32 string from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_utf8(
                       libuca_utf8_character_t *utf8_string,
                       size_t utf8_string_size,
                       uint8_t strict_mode );

/* Copies an UTF-32 string from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_string_copy_from_utf8(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t strict_mode );

/* The functionality for libuca_utf32_string_copy_to_utf8 is implemented by
 * libuca_utf8_string_size_from_utf32
 */

/* Determines the size of a UTF-32 string from a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_utf16(
                       libuca_utf16_character_t *utf16_string,
                       size_t utf16_string_size,
                       uint8_t strict_mode );

/* Copies an UTF-32 string from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_string_copy_from_utf16(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t strict_mode );

/* Determines the size of a UTF-32 string from a UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_utf16_stream(
                       uint8_t *utf16_stream,
                       size_t utf16_stream_size,
                       uint8_t byte_order,
                       uint8_t strict_mode );

/* Copies an UTF-32 string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_string_copy_from_utf16_stream(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* The functionality for libuca_utf32_string_copy_to_utf16_stream is implemented by
 * libuca_utf16_stream_copy_from_utf32
 */

/* Determines the size of a UTF-32 string from a UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_utf32_stream(
                       uint8_t *utf32_stream,
                       size_t utf32_stream_size,
                       uint8_t byte_order,
                       uint8_t strict_mode );

/* Copies an UTF-32 string from an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_string_copy_from_utf32_stream(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   uint8_t byte_order,
                   uint8_t strict_mode );

/* The functionality for libuca_utf32_string_copy_to_utf32_stream is implemented by
 * libuca_utf32_stream_size_from_utf32
 */

/* -------------------------------------------------------------------------
 * UTF-32 stream functions
 * ------------------------------------------------------------------------- */

/* Copies an UTF-32 stream from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_stream_copy_to_utf8(
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   uint8_t byte_order,
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t strict_mode );

/* Copies an UTF-32 stream from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_stream_copy_to_utf16(
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   uint8_t byte_order,
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t strict_mode );

/* Copies an UTF-32 stream from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_stream_copy_to_utf32(
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   uint8_t byte_order,
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t strict_mode );

#if defined( __cplusplus )
}
#endif

#endif

