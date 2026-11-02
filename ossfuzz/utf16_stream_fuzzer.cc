/*
 * OSS-Fuzz target for libuna UTF-16 stream type
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

static const int test_codepages[ 3 ] = {
	LIBUNA_CODEPAGE_ASCII,
	LIBUNA_CODEPAGE_WINDOWS_1252,
	LIBUNA_CODEPAGE_WINDOWS_936
};

static const int test_byte_orders[ 2 ] = {
	LIBUNA_ENDIAN_LITTLE,
	LIBUNA_ENDIAN_BIG
};

static const size_t max_string_size = 8 * 1024 * 1024;

static void fuzzer_unicode_character_from_utf16_stream(
     const uint8_t *data,
     size_t size,
     int byte_order )
{
	uint16_t utf16_string[ 2 ]                         = { 0, 0 };
	libuna_unicode_character_t unicode_character        = 0;
	size_t stream_index                                = 0;
	size_t utf16_stream_index                          = 0;
	int result                                         = 0;

	while( stream_index < size )
	{
		unicode_character  = 0;
		utf16_stream_index = stream_index;

		result = libuna_unicode_character_copy_from_utf16_stream(
		          &unicode_character,
		          data,
		          size,
		          &utf16_stream_index,
		          byte_order,
		          NULL );

		if( result < 1 )
		{
			break;
		}
		/* Note the index advances by the size of the consumed character
		 */
		if( utf16_stream_index <= stream_index )
		{
			utf16_stream_index = stream_index + 2;
		}
		stream_index = utf16_stream_index;

		utf16_stream_index = 0;
		libuna_unicode_character_copy_to_utf16_stream(
		 unicode_character,
		 (uint8_t *) utf16_string,
		 sizeof( utf16_string ),
		 &utf16_stream_index,
		 byte_order,
		 NULL );
	}
}

static void fuzzer_utf8_string_from_utf16_stream(
     const uint8_t *data,
     size_t size,
     int byte_order )
{
	libuna_utf8_character_t *utf8_string = NULL;
	size_t utf8_string_index            = 0;
	size_t utf8_string_size             = 0;

	uint8_t utf16_bom_string[ 2 ]          = { 0, 0 };
	size_t utf16_bom_string_index          = 0;

	libuna_utf16_stream_copy_byte_order_mark(
	 utf16_bom_string,
	 sizeof( utf16_bom_string ),
	 &utf16_bom_string_index,
	 byte_order,
	 NULL );

	if( libuna_utf8_string_size_from_utf16_stream(
	     data,
	     size,
	     byte_order,
	     &utf8_string_size,
	     NULL ) == 1
	 && ( utf8_string_size > 0 )
	 && ( utf8_string_size < max_string_size ) )
	{
		utf8_string = (libuna_utf8_character_t *) malloc( utf8_string_size );

		if( utf8_string != NULL )
		{
			libuna_utf8_string_copy_from_utf16_stream(
			 utf8_string,
			 utf8_string_size,
			 data,
			 size,
			 byte_order,
			 NULL );

			utf8_string_index = 0;
			libuna_utf8_string_with_index_copy_from_utf16_stream(
			 utf8_string,
			 utf8_string_size / 2,
			 &utf8_string_index,
			 data,
			 size,
			 byte_order,
			 NULL );

			free( utf8_string );

			utf8_string = NULL;
		}
	}
}

static void fuzzer_utf16_stream_from_utf8_string(
     const uint8_t *data,
     size_t size )
{
	uint8_t *byte_stream             = NULL;
	uint8_t *utf16_stream            = NULL;
	uint8_t *utf32_stream            = NULL;
	size_t byte_stream_size          = 0;
	size_t codepage_index            = 0;
	size_t utf16_stream_size         = 0;
	size_t utf32_stream_size         = 0;

	if( libuna_utf16_stream_size_from_utf8(
	     data,
	     size,
	     &utf16_stream_size,
	     NULL ) == 1
	 && ( utf16_stream_size > 0 )
	 && ( utf16_stream_size < max_string_size ) )
	{
		utf16_stream = (uint8_t *) malloc( utf16_stream_size );

		if( utf16_stream != NULL )
		{
			libuna_utf16_stream_copy_from_utf8(
			 utf16_stream,
			 utf16_stream_size,
			 LIBUNA_ENDIAN_BIG,
			 data,
			 size,
			 NULL );

			free( utf16_stream );

			utf16_stream = NULL;
		}
	}
	if( libuna_utf32_stream_size_from_utf8(
	     data,
	     size,
	     &utf32_stream_size,
	     NULL ) == 1
	 && ( utf32_stream_size > 0 )
	 && ( utf32_stream_size < max_string_size ) )
	{
		utf32_stream = (uint8_t *) malloc( utf32_stream_size );

		if( utf32_stream != NULL )
		{
			libuna_utf32_stream_copy_from_utf8(
			 utf32_stream,
			 utf32_stream_size,
			 LIBUNA_ENDIAN_BIG,
			 data,
			 size,
			 NULL );

			free( utf32_stream );

			utf32_stream = NULL;
		}
	}
	/* Treat the input as UTF-16 source string for codepage conversions
	 */
	for( codepage_index = 0;
	     codepage_index < ( sizeof( test_codepages ) / sizeof( test_codepages[ 0 ] ) );
	     codepage_index++ )
	{
		if( libuna_byte_stream_size_from_utf16(
		     (const libuna_utf16_character_t *) data,
		     size / 2,
		     test_codepages[ codepage_index ],
		     &byte_stream_size,
		     NULL ) == 1
		 && ( byte_stream_size > 0 )
		 && ( byte_stream_size < max_string_size ) )
		{
			byte_stream = (uint8_t *) malloc( byte_stream_size );

			if( byte_stream != NULL )
			{
				libuna_byte_stream_copy_from_utf16(
				 byte_stream,
				 byte_stream_size,
				 test_codepages[ codepage_index ],
				 (const libuna_utf16_character_t *) data,
				 size / 2,
				 NULL );

				free( byte_stream );

				byte_stream = NULL;
			}
		}
	}
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	size_t byte_order_index = 0;

	for( byte_order_index = 0;
	     byte_order_index < ( sizeof( test_byte_orders ) / sizeof( test_byte_orders[ 0 ] ) );
	     byte_order_index++ )
	{
		const int byte_order = test_byte_orders[ byte_order_index ];

		fuzzer_unicode_character_from_utf16_stream(
		 data,
		 size,
		 byte_order );

		fuzzer_utf8_string_from_utf16_stream(
		 data,
		 size,
		 byte_order );
	}
	fuzzer_utf16_stream_from_utf8_string(
	 data,
	 size );

	return( 0 );
}

} /* extern "C" */
