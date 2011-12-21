/*
 * Common input functions for the unatools
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

#if !defined( _UNAINPUT_H )
#define _UNAINPUT_H

#include <common.h>
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#if defined( __cplusplus )
extern "C" {
#endif

int unainput_determine_byte_stream_codepage(
     const libcstring_system_character_t *argument,
     int *byte_stream_codepage,
     liberror_error_t **error );

int unainput_determine_encoding(
     const libcstring_system_character_t *string,
     uint8_t *encoding,
     liberror_error_t **error );

int unainput_determine_format(
     const libcstring_system_character_t *string,
     uint8_t *format,
     liberror_error_t **error );

int unainput_determine_format(
     const libcstring_system_character_t *argument,
     uint8_t *format,
     liberror_error_t **error );

int unainput_determine_newline_conversion(
     const libcstring_system_character_t *argument,
     uint8_t *newline_conversion,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

