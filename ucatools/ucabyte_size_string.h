/*
 * Byte size string functions for the ucatools
 *
 * Copyright (c) 2006-2008, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _UCABYTE_SIZE_STRING_H )
#define _UCABYTE_SIZE_STRING_H

#include <common.h>
#include <character_string.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define UCABYTE_SIZE_STRING_UNIT_MEGABYTE		1000
#define UCABYTE_SIZE_STRING_UNIT_MEBIBYTE		1024

const character_t *ucabyte_size_string_get_factor_string(
                    int8_t factor );

int8_t ucabyte_size_string_get_factor(
        character_t factor );

int ucabyte_size_string_create(
     character_t *byte_size_string,
     size_t byte_size_string_length,
     uint64_t size,
     int units );

int ucabyte_size_string_convert(
     character_t *byte_size_string,
     size_t byte_size_string_length,
     uint64_t *size );

#if defined( __cplusplus )
}
#endif

#endif

