/*
 * OSS-Fuzz target for libuna UTF-8 stream type
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
	LIBUNA_CODEPAGE_WINDOWS_932
};

static const size_t max_string_size = 8 * 1024 * 1024;

static void fuzzer_unicode_character_from_utf8_string(
     const uint8_t *data,
     size_t size )
{
	uint8_t utf8_string[ 8 ]                       = { 0 };
	libuna_unicode_character_t unicode_character    = 0;
	size_t stream_index                            = 0;
	size_t utf8_string_index                       = 0;
	int result                                     = 0;

	while( stream_index < size )
	{
		unicode_character = 0;
		utf8_string_index = stream_index;

		result = libuna_unicode_character_copy_from_utf8(
		          &unicode_character,
		          data,
		          size,
		          &utf8_string_index,
		          NULL );

		if( result < 1 )
		{
			break;
		}
		/* Note the index advances by the size of the consumed character
		 */
		if( utf8_string_index <= stream_index )
		{
			utf8_string_index = stream_index + 1;
		}
		stream_index = utf8_string_index;

		/* Also exercise the RFC 2279 (6 byte) UTF-8 support
		 */
		unicode_character = 0;
		utf8_string_index = stream_index;
		libuna_unicode_character_copy_from_utf8_rfc2279(
		 &unicode_character,
		 data,
		 size,
		 &utf8_string_index,
		 NULL );

		utf8_string_index = 0;
		libuna_unicode_character_copy_to_utf8(
		 unicode_character,
		 utf8_string,
		 sizeof( utf8_string ),
		 &utf8_string_index,
		 NULL );
	}
}

static void fuzzer_utf8_string_from_utf8_stream(
     const uint8_t *data,
     size_t size )
{
	libuna_utf8_character_t *utf8_string   = NULL;
	uint8_t *byte_stream                 = NULL;
	uint8_t *utf7_stream                 = NULL;
	uint8_t *utf16_stream                = NULL;
	uint8_t *utf32_stream                = NULL;
	size_t byte_stream_size              = 0;
	size_t utf7_stream_size              = 0;
	size_t utf16_stream_size             = 0;
	size_t utf32_stream_size             = 0;
	uint8_t utf8_bom_string[ 4 ]             = { 0 };
	size_t utf8_bom_string_index             = 0;
	size_t utf8_string_index                 = 0;
	size_t utf8_string_size                  = 0;
	size_t codepage_index                    = 0;

	utf8_bom_string_index = 0;
	libuna_utf8_stream_copy_byte_order_mark(
	 utf8_bom_string,
	 sizeof( utf8_bom_string ),
	 &utf8_bom_string_index,
	 NULL );

	if( libuna_utf8_string_size_from_utf8_stream(
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
			libuna_utf8_string_copy_from_utf8_stream(
			 utf8_string,
			 utf8_string_size,
			 data,
			 size,
			 NULL );

			utf8_string_index = 0;
			libuna_utf8_string_with_index_copy_from_utf8_stream(
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
	/* Treat the input as UTF-8 source string for the other conversions
	 */
	for( codepage_index = 0;
	     codepage_index < ( sizeof( test_codepages ) / sizeof( test_codepages[ 0 ] ) );
	     codepage_index++ )
	{
		if( libuna_byte_stream_size_from_utf8(
		     data,
		     size,
		     test_codepages[ codepage_index ],
		     &byte_stream_size,
		     NULL ) == 1
		 && ( byte_stream_size > 0 )
		 && ( byte_stream_size < max_string_size ) )
		{
			byte_stream = (uint8_t *) malloc( byte_stream_size );

			if( byte_stream != NULL )
			{
				libuna_byte_stream_copy_from_utf8(
				 byte_stream,
				 byte_stream_size,
				 test_codepages[ codepage_index ],
				 data,
				 size,
				 NULL );

				free( byte_stream );

				byte_stream = NULL;
			}
		}
	}
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
			 LIBUNA_ENDIAN_LITTLE,
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
			 LIBUNA_ENDIAN_LITTLE,
			 data,
			 size,
			 NULL );

			free( utf32_stream );

			utf32_stream = NULL;
		}
	}
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	fuzzer_unicode_character_from_utf8_string(
	 data,
	 size );

	fuzzer_utf8_string_from_utf8_stream(
	 data,
	 size );

	return( 0 );
}

} /* extern "C" */
