/*
 * System character string functions
 *
 * Copyright (c) 2008-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBSYSTEM_STRING_H )
#define _LIBSYSTEM_STRING_H

#include <common.h>
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( libcstring_system_string_to_signed_long_long )
int libsystem_string_to_int64(
     const libcstring_system_character_t *string,
     size_t string_size,
     int64_t *value,
     liberror_error_t **error );
#endif

#if defined( libcstring_system_string_to_unsigned_long_long )
int libsystem_string_to_uint64(
     const libcstring_system_character_t *string,
     size_t string_size,
     uint64_t *value,
     liberror_error_t **error );
#endif

int libsystem_string_size_from_utf8_string(
     const uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *string_size,
     liberror_error_t **error );

int libsystem_string_copy_from_utf8_string(
     libcstring_system_character_t *string,
     size_t string_size,
     const uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

int libsystem_string_size_to_utf8_string(
     const libcstring_system_character_t *string,
     size_t string_size,
     size_t *utf8_string_size,
     liberror_error_t **error );

int libsystem_string_copy_to_utf8_string(
     const libcstring_system_character_t *string,
     size_t string_size,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

