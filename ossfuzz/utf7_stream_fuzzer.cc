/*
 * OSS-Fuzz target for libuna UTF-7 stream type
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

static void fuzzer_utf8_string_from_utf7_stream(
     const uint8_t *data,
     size_t size )
{
	libuna_utf8_character_t *utf8_string  = NULL;
	size_t utf8_string_index              = 0;
	size_t utf8_string_size               = 0;

	if( libuna_utf8_string_size_from_utf7_stream(
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
			libuna_utf8_string_copy_from_utf7_stream(
			 utf8_string,
			 utf8_string_size,
			 data,
			 size,
			 NULL );

			utf8_string_index = 0;
			libuna_utf8_string_with_index_copy_from_utf7_stream(
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

static void fuzzer_unicode_character_from_utf7_stream(
     const uint8_t *data,
     size_t size )
{
	uint8_t utf7_stream[ 16 ]                    = { 0 };
	libuna_unicode_character_t unicode_character = 0;
	size_t stream_index                          = 0;
	size_t utf7_stream_index                     = 0;
	uint32_t utf7_stream_base64_data             = 0;
	int result                                   = 0;

	while( stream_index < size )
	{
		unicode_character    = 0;
		utf7_stream_index    = stream_index;
		utf7_stream_base64_data = 0;

		result = libuna_unicode_character_copy_from_utf7_stream(
		          &unicode_character,
		          data,
		          size,
		          &utf7_stream_index,
		         &utf7_stream_base64_data,
		          NULL );

		if( result < 1 )
		{
			break;
		}
		/* Note the index advances by the size of the consumed character
		 */
		if( utf7_stream_index <= stream_index )
		{
			utf7_stream_index = stream_index + 1;
		}
		stream_index = utf7_stream_index;

		/* Round-trip the character to a UTF-7 stream
		 * Note a fresh base64 state is used for each character
		 */
		utf7_stream_index       = 0;
		utf7_stream_base64_data = 0;
		libuna_unicode_character_copy_to_utf7_stream(
		 unicode_character,
		 utf7_stream,
		 sizeof( utf7_stream ),
		 &utf7_stream_index,
		 &utf7_stream_base64_data,
		 NULL );

		/* If the character was base64 encoded with a partial triplet,
		 * continue the encoding using the state produced by the library
		 */
		if( ( utf7_stream_base64_data & 0x80000000UL ) != 0 )
		{
			libuna_unicode_character_copy_to_utf7_stream(
			 unicode_character,
			 utf7_stream,
			 sizeof( utf7_stream ),
			 &utf7_stream_index,
			 &utf7_stream_base64_data,
			 NULL );
		}
	}
}

static void fuzzer_utf7_stream_from_utf8_string(
     const uint8_t *data,
     size_t size )
{
	uint8_t *utf7_stream         = NULL;
	size_t utf7_stream_size      = 0;

	if( libuna_utf7_stream_size_from_utf8(
	     data,
	     size,
	     &utf7_stream_size,
	     NULL ) == 1
	 && ( utf7_stream_size > 0 )
	 && ( utf7_stream_size < max_string_size ) )
	{
		utf7_stream = (uint8_t *) malloc( utf7_stream_size );

		if( utf7_stream != NULL )
		{
			libuna_utf7_stream_copy_from_utf8(
			 utf7_stream,
			 utf7_stream_size,
			 data,
			 size,
			 NULL );

			free( utf7_stream );

			utf7_stream = NULL;
		}
	}
	/* Treat the input as UTF-16 and UTF-32 source strings as well
	 */
	libuna_utf7_stream_size_from_utf16(
	 (const libuna_utf16_character_t *) data,
	 size / 2,
	 &utf7_stream_size,
	 NULL );

	libuna_utf7_stream_size_from_utf32(
	 (const libuna_utf32_character_t *) data,
	 size / 4,
	 &utf7_stream_size,
	 NULL );
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	fuzzer_utf8_string_from_utf7_stream(
	 data,
	 size );

	fuzzer_unicode_character_from_utf7_stream(
	 data,
	 size );

	fuzzer_utf7_stream_from_utf8_string(
	 data,
	 size );

	return( 0 );
}

} /* extern "C" */
