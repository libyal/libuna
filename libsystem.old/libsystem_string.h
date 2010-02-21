/*
 * System character string functions
 *
 * Copyright (c) 2010, Joachim Metz <jbmetz@users.sourceforge.net>
 * Copyright (c) 2006-2010, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBSYSTEM_STRING_H )
#define _LIBSYSTEM_STRING_H

#include <common.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include <liberror.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* Detect if the code is being compiled with Windows Unicode support
 */
#if defined( WINAPI ) && ( defined( _UNICODE ) || defined( UNICODE ) )
#define LIBSYSTEM_HAVE_WIDE_CHARACTER	1
#endif

/* String functions
 */
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )

typedef wchar_t libsystem_character_t;
typedef wint_t libsystem_integer_t;

#define PRIc_LIBSYSTEM	"lc"
#define PRIs_LIBSYSTEM	"ls"

/* Intermediate version of the macro required
 * for correct evaluation predefined string
 */
#define _LIBSYSTEM_CHARACTER_T_STRING_INTERMEDIATE( string ) \
	L ## string

#define _LIBSYSTEM_CHARACTER_T_STRING( string ) \
	_LIBSYSTEM_CHARACTER_T_STRING_INTERMEDIATE( string )

#define libsystem_string_length( string ) \
	wide_string_length( string )

#define libsystem_string_size( string ) \
	wide_string_size( string )

#define libsystem_string_compare( string1, string2, size ) \
	wide_string_compare( string1, string2, size )

#define libsystem_string_copy( destination, source, size ) \
	wide_string_copy( destination, source, size )

#define libsystem_string_search( string, character, size ) \
	wide_string_search( string, character, size )

#define libsystem_string_search_reverse( string, character, size ) \
	wide_string_search_reverse( string, character, size )

#define libsystem_string_snprintf( target, size, format, ... ) \
	wide_string_swprintf( target, size, format, __VA_ARGS__ )

#define libsystem_string_to_signed_long_long( string, end_of_string, base ) \
	wide_string_to_signed_long_long( string, end_of_string, base )

#define libsystem_string_to_unsigned_long_long( string, end_of_string, base ) \
	wide_string_to_unsigned_long_long( string, end_of_string, base )

/* The system string type contains UTF-8 or ASCII with or without a codepage
 */
#else

typedef char libsystem_character_t;
typedef int libsystem_integer_t;

#define PRIc_LIBSYSTEM	"c"
#define PRIs_LIBSYSTEM	"s"

#define _LIBSYSTEM_CHARACTER_T_STRING( string ) \
	string

#define libsystem_string_length( string ) \
	narrow_string_length( string )

#define libsystem_string_size( string ) \
	narrow_string_size( string )

#define libsystem_string_compare( string1, string2, size ) \
	narrow_string_compare( string1, string2, size )

#define libsystem_string_copy( destination, source, size ) \
	narrow_string_copy( destination, source, size )

#define libsystem_string_search( string, character, size ) \
	narrow_string_search( string, character, size )

#define libsystem_string_search( string, character, size ) \
	narrow_string_search( string, character, size )

#define libsystem_string_search_reverse( string, character, size ) \
	narrow_string_search_reverse( string, character, size )

#if !defined( narrow_string_snprintf )
int libsystem_string_snprintf(
     libsystem_character_t *string,
     size_t string_size,
     const libsystem_character_t *format,
     ... );

#else
#define libsystem_string_snprintf( target, size, format, ... ) \
	narrow_string_snprintf( (char *) target, size, format, __VA_ARGS__ )

#endif

#define libsystem_string_to_signed_long_long( string, end_of_string, base ) \
	narrow_string_to_signed_long_long( string, end_of_string, base )

#define libsystem_string_to_unsigned_long_long( string, end_of_string, base ) \
	narrow_string_to_unsigned_long_long( string, end_of_string, base )

#endif

#if !defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )

extern int libsystem_string_is_unicode;
extern int libsystem_string_byte_stream_codepage;

#endif

#if defined( libsystem_string_to_signed_long_long )
int libsystem_string_to_int64(
     const libsystem_character_t *string,
     size_t string_size,
     int64_t *value,
     liberror_error_t **error );
#endif

#if defined( libsystem_string_to_unsigned_long_long )
int libsystem_string_to_uint64(
     const libsystem_character_t *string,
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
     libsystem_character_t *string,
     size_t string_size,
     const uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

int libsystem_string_size_to_utf8_string(
     const libsystem_character_t *string,
     size_t string_size,
     size_t *utf8_string_size,
     liberror_error_t **error );

int libsystem_string_copy_to_utf8_string(
     const libsystem_character_t *string,
     size_t string_size,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

