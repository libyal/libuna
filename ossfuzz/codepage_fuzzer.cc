/*
 * OSS-Fuzz target for libuna codepage types
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

static const int test_codepages[ 43 ] = {
	LIBUNA_CODEPAGE_ASCII,

	LIBUNA_CODEPAGE_ISO_8859_1,
	LIBUNA_CODEPAGE_ISO_8859_2,
	LIBUNA_CODEPAGE_ISO_8859_3,
	LIBUNA_CODEPAGE_ISO_8859_4,
	LIBUNA_CODEPAGE_ISO_8859_5,
	LIBUNA_CODEPAGE_ISO_8859_6,
	LIBUNA_CODEPAGE_ISO_8859_7,
	LIBUNA_CODEPAGE_ISO_8859_8,
	LIBUNA_CODEPAGE_ISO_8859_9,
	LIBUNA_CODEPAGE_ISO_8859_10,
	LIBUNA_CODEPAGE_ISO_8859_11,
	LIBUNA_CODEPAGE_ISO_8859_13,
	LIBUNA_CODEPAGE_ISO_8859_14,
	LIBUNA_CODEPAGE_ISO_8859_15,
	LIBUNA_CODEPAGE_ISO_8859_16,

	LIBUNA_CODEPAGE_KOI8_R,
	LIBUNA_CODEPAGE_KOI8_U,

	LIBUNA_CODEPAGE_MAC_ROMAN,
	LIBUNA_CODEPAGE_MAC_JAPANESE,
	LIBUNA_CODEPAGE_MAC_CHINESETRAD,
	LIBUNA_CODEPAGE_MAC_KOREAN,
	LIBUNA_CODEPAGE_MAC_ARABIC,
	LIBUNA_CODEPAGE_MAC_GREEK,
	LIBUNA_CODEPAGE_MAC_RUSSIAN,
	LIBUNA_CODEPAGE_MAC_CHINESESIMP,
	LIBUNA_CODEPAGE_MAC_ROMANIAN,
	LIBUNA_CODEPAGE_MAC_UKRAINIAN,
	LIBUNA_CODEPAGE_MAC_CYRILLIC,

	LIBUNA_CODEPAGE_WINDOWS_874,
	LIBUNA_CODEPAGE_WINDOWS_932,
	LIBUNA_CODEPAGE_WINDOWS_936,
	LIBUNA_CODEPAGE_WINDOWS_949,
	LIBUNA_CODEPAGE_WINDOWS_950,
	LIBUNA_CODEPAGE_WINDOWS_1250,
	LIBUNA_CODEPAGE_WINDOWS_1251,
	LIBUNA_CODEPAGE_WINDOWS_1252,
	LIBUNA_CODEPAGE_WINDOWS_1253,
	LIBUNA_CODEPAGE_WINDOWS_1254,
	LIBUNA_CODEPAGE_WINDOWS_1255,
	LIBUNA_CODEPAGE_WINDOWS_1256,
	LIBUNA_CODEPAGE_WINDOWS_1257,
	LIBUNA_CODEPAGE_WINDOWS_1258
};

static const size_t max_string_size = 8 * 1024 * 1024;

void fuzzer_unicode_character_from_byte_stream(
      const uint8_t *data,
      size_t size,
      int codepage )
{
	uint8_t byte_stream[ 8 ]                     = { 0 };
	libuna_unicode_character_t unicode_character = 0;
	size_t byte_stream_character_size            = 0;
	size_t byte_stream_index                     = 0;
	size_t stream_index                          = 0;
	int result                                   = 0;

	while( stream_index < size )
	{
		unicode_character = 0;
		byte_stream_index = stream_index;

		result = libuna_unicode_character_copy_from_byte_stream(
		          &unicode_character,
		          data,
		          size,
		          &byte_stream_index,
		          codepage,
		          NULL );

		if( result < 1 )
		{
			break;
		}
		/* Note the index advances by the size of the consumed character
		 */
		if( byte_stream_index <= stream_index )
		{
			byte_stream_index = stream_index + 1;
		}
		libuna_unicode_character_size_to_byte_stream(
		 unicode_character,
		 codepage,
		 &byte_stream_character_size,
		 NULL );

		stream_index = byte_stream_index;

		byte_stream_index = 0;
		libuna_unicode_character_copy_to_byte_stream(
		 unicode_character,
		 byte_stream,
		 sizeof( byte_stream ),
		 &byte_stream_index,
		 codepage,
		 NULL );
	}
}

static void fuzzer_utf8_string_from_byte_stream(
     const uint8_t *data,
     size_t size,
     int codepage )
{
	libuna_utf8_character_t *utf8_string = NULL;
	size_t utf8_string_index             = 0;
	size_t utf8_string_size              = 0;
	int result                           = 0;

	result = libuna_utf8_string_size_from_byte_stream(
	          data,
	          size,
	          codepage,
	          &utf8_string_size,
	          NULL );

	if( ( result == 1 )
	 && ( utf8_string_size > 0 )
	 && ( utf8_string_size < max_string_size ) )
	{
		utf8_string = (libuna_utf8_character_t *) malloc( utf8_string_size );

		if( utf8_string != NULL )
		{
			libuna_utf8_string_copy_from_byte_stream(
			 utf8_string,
			 utf8_string_size,
			 data,
			 size,
			 codepage,
			 NULL );

			utf8_string_index = 0;

			libuna_utf8_string_with_index_copy_from_byte_stream(
			 utf8_string,
			 utf8_string_size / 2,
			 &utf8_string_index,
			 data,
			 size,
			 codepage,
			 NULL );

			free( utf8_string );

			utf8_string = NULL;
		}
	}
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	size_t codepage_index = 0;

	for( codepage_index = 0;
	     codepage_index < ( sizeof( test_codepages ) / sizeof( test_codepages[ 0 ] ) );
	     codepage_index++ )
	{
		const int codepage = test_codepages[ codepage_index ];

		fuzzer_unicode_character_from_byte_stream(
		 data,
		 size,
		 codepage );

		fuzzer_utf8_string_from_byte_stream(
		 data,
		 size,
		 codepage );
	}
	return( 0 );
}

} /* extern "C" */
