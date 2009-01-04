/*
 * Library to support Unicode and ASCII (single byte character) conversions
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

/* Returns the library version as a UTF-8 string
 */
#if defined( LIBUCA_WIDE_CHARACTER_TYPE )
LIBUCA_EXTERN const wchar_t *libuca_get_version(
                              void );
#else
LIBUCA_EXTERN const char *libuca_get_version(
                           void );
#endif

/* -------------------------------------------------------------------------
 * UTF-8 string functions
 * ------------------------------------------------------------------------- */

/* Determines the size of a UTF-8 string from a single byte character (SBC) string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf8_string_size_from_sbc(
                       uint8_t *sbc_string,
                       size_t sbc_string_size,
                       int code_page,
                       uint8_t strict_mode );

/* Copies an UTF-8 string from a single byte character (SBC) string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf8_string_copy_from_sbc(
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t *sbc_string,
                   size_t sbc_string_size,
                   int code_page,
                   uint8_t strict_mode );

/* Copies an UTF-8 string to a single byte character (SBC) string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf8_string_copy_to_sbc(
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t *sbc_string,
                   size_t sbc_string_size,
                   int code_page,
                   uint8_t strict_mode );

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

/* Copies an UTF-8 string to an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf8_string_copy_to_utf16_stream(
                   libuca_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
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

/* -------------------------------------------------------------------------
 * UTF-16 string functions
 * ------------------------------------------------------------------------- */

/* Determines the size of a UTF-16 string from a single byte character (SBC) string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf16_string_size_from_sbc(
                       uint8_t *sbc_string,
                       size_t sbc_string_size,
                       int code_page,
                       uint8_t strict_mode );

/* Copies an UTF-16 string from a single byte character (SBC) string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_string_copy_from_sbc(
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t *sbc_string,
                   size_t sbc_string_size,
                   int code_page,
                   uint8_t strict_mode );

/* Copies an UTF-16 string to a single byte character (SBC) string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_string_copy_to_sbc(
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t *sbc_string,
                   size_t sbc_string_size,
                   int code_page,
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

/* Copies an UTF-16 string to an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf16_string_copy_to_utf16_stream(
                   libuca_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
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

/* -------------------------------------------------------------------------
 * UTF-32 string functions
 * ------------------------------------------------------------------------- */

/* Determines the size of a UTF-32 string from a single byte character (SBC) string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN ssize_t libuca_utf32_string_size_from_sbc(
                       uint8_t *sbc_string,
                       size_t sbc_string_size,
                       int code_page,
                       uint8_t strict_mode );

/* Copies an UTF-32 string from a single byte character (SBC) string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_string_copy_from_sbc(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *sbc_string,
                   size_t sbc_string_size,
                   int code_page,
                   uint8_t strict_mode );

/* Copies an UTF-32 string to a single byte character (SBC) string
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_string_copy_to_sbc(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *sbc_string,
                   size_t sbc_string_size,
                   int code_page,
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

/* Copies an UTF-32 string to an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUCA_EXTERN int libuca_utf32_string_copy_to_utf16_stream(
                   libuca_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   uint8_t byte_order,
                   uint8_t strict_mode );

#if defined( __cplusplus )
}
#endif

#endif

