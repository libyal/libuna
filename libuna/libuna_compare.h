/*
 * Compare functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBUNA_COMPARE_H )
#define _LIBUNA_COMPARE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libuna_extern.h"
#include "libuna_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

/* Compares an UTF-8 string with an UTF-16 string
 * Returns 1 if the strings are equal, 0 if not or -1 on error
 */
LIBUNA_EXTERN int libuna_compare_utf8_with_utf16(
                   const libuna_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   const libuna_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   liberror_error_t **error );

/* Compares an UTF-8 string with an UTF-32 string
 * Returns 1 if the strings are equal, 0 if not or -1 on error
 */
LIBUNA_EXTERN int libuna_compare_utf8_with_utf32(
                   const libuna_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   const libuna_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   liberror_error_t **error );

/* The functionality for libuna_compare_utf16_with_utf8 is implemented by
 * libuna_compare_utf8_with_utf16
 */

/* Compares an UTF-16 string with an UTF-32 string
 * Returns 1 if the strings are equal, 0 if not or -1 on error
 */
LIBUNA_EXTERN int libuna_compare_utf16_with_utf32(
                   const libuna_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   const libuna_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   liberror_error_t **error );

/* The functionality for libuna_compare_utf32_with_utf8 is implemented by
 * libuna_compare_utf8_with_utf32
 */

/* The functionality for libuna_compare_utf32_with_utf16 is implemented by
 * libuna_compare_utf16_with_utf32
 */

#if defined( __cplusplus )
}
#endif

#endif

