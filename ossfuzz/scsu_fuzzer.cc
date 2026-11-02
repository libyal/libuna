/*
 * OSS-Fuzz target for libuna SCSU stream type
 *
 * Copyright (C) 2011-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libuna.h"

static const size_t max_string_size = 8 * 1024 * 1024;

static void fuzzer_utf8_string_from_scsu_stream(
     const uint8_t *data,
     size_t size )
{
	libuna_utf8_character_t *utf8_string  = NULL;
	size_t utf8_string_index              = 0;
	size_t utf8_string_size               = 0;

	if( libuna_utf8_string_size_from_scsu_stream(
	     data,
	     size,
	     &utf8_string_size,
	     NULL ) == 1
	 && ( utf8_string_size > 0 )
	 && ( utf8_string_size < max_string_size ) )
	{
		utf8_string = (libuna_utf8_character_t *) malloc( utf8_string_size );

		if( utf8_string != NULL )
		{
			libuna_utf8_string_copy_from_scsu_stream(
			 utf8_string,
			 utf8_string_size,
			 data,
			 size,
			 NULL );

			utf8_string_index = 0;
			libuna_utf8_string_with_index_copy_from_scsu_stream(
			 utf8_string,
			 utf8_string_size / 2,
			 &utf8_string_index,
			 data,
			 size,
			 NULL );

			free( utf8_string );

			utf8_string = NULL;
		}
	}
}

static void fuzzer_utf16_string_from_scsu_stream(
     const uint8_t *data,
     size_t size )
{
	libuna_utf16_character_t *utf16_string   = NULL;
	size_t utf16_string_index                = 0;
	size_t utf16_string_size                 = 0;

	if( libuna_utf16_string_size_from_scsu_stream(
	     data,
	     size,
	     &utf16_string_size,
	     NULL ) == 1
	 && ( utf16_string_size > 0 )
	 && ( utf16_string_size < max_string_size ) )
	{
		utf16_string = (libuna_utf16_character_t *) malloc( utf16_string_size * sizeof( libuna_utf16_character_t ) );

		if( utf16_string != NULL )
		{
			libuna_utf16_string_copy_from_scsu_stream(
			 utf16_string,
			 utf16_string_size,
			 data,
			 size,
			 NULL );

			utf16_string_index = 0;
			libuna_utf16_string_with_index_copy_from_scsu_stream(
			 utf16_string,
			 utf16_string_size / 2,
			 &utf16_string_index,
			 data,
			 size,
			 NULL );

			free( utf16_string );

			utf16_string = NULL;
		}
	}
}

static void fuzzer_utf32_string_from_scsu_stream(
     const uint8_t *data,
     size_t size )
{
	libuna_utf32_character_t *utf32_string   = NULL;
	size_t utf32_string_index                = 0;
	size_t utf32_string_size                 = 0;

	if( libuna_utf32_string_size_from_scsu_stream(
	     data,
	     size,
	     &utf32_string_size,
	     NULL ) == 1
	 && ( utf32_string_size > 0 )
	 && ( utf32_string_size < max_string_size ) )
	{
		utf32_string = (libuna_utf32_character_t *) malloc( utf32_string_size * sizeof( libuna_utf32_character_t ) );

		if( utf32_string != NULL )
		{
			libuna_utf32_string_copy_from_scsu_stream(
			 utf32_string,
			 utf32_string_size,
			 data,
			 size,
			 NULL );

			utf32_string_index = 0;
			libuna_utf32_string_with_index_copy_from_scsu_stream(
			 utf32_string,
			 utf32_string_size / 2,
			 &utf32_string_index,
			 data,
			 size,
			 NULL );

			free( utf32_string );

			utf32_string = NULL;
		}
	}
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	fuzzer_utf8_string_from_scsu_stream(
	 data,
	 size );

	fuzzer_utf16_string_from_scsu_stream(
	 data,
	 size );

	fuzzer_utf32_string_from_scsu_stream(
	 data,
	 size );

	return( 0 );
}

} /* extern "C" */
