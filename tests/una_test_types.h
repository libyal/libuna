/*
 * The type definitions
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _UNA_TEST_TYPES_H )
#define _UNA_TEST_TYPES_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct una_test_byte_stream_to_unicode una_test_byte_stream_to_unicode_t;

struct una_test_byte_stream_to_unicode
{
	/* The byte stream
	 */
	uint8_t byte_stream[ 2 ];

	/* The byte stream size
	 */
	size_t byte_stream_size;

	/* The Unicode character
	 */
	libuna_unicode_character_t unicode_character;

	/* Value to indicate this is a duplicate unicode character entry
	 */
	uint8_t is_duplicate;
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _UNA_TEST_TYPES_H ) */

