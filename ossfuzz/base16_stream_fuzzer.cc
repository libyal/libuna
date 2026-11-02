/*
 * OSS-Fuzz target for libuna base16 stream type
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

#define MAXIMUM_STRING_SIZE	8 * 1024 * 1024

static const uint32_t test_variants[ 6 ] = {
	LIBUNA_BASE16_VARIANT_CASE_LOWER,
	LIBUNA_BASE16_VARIANT_CASE_MIXED,
	LIBUNA_BASE16_VARIANT_CASE_UPPER,
	LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
	LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
	LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN
};

static const uint8_t test_flags[ 2 ] = {
	0,
	LIBUNA_BASE16_FLAG_STRIP_WHITESPACE
};

void fuzzer_decode_base16_stream(
      const uint8_t *data,
      size_t size,
      uint32_t variant,
      uint8_t flags )
{
	uint8_t *byte_stream    = NULL;
	size_t byte_stream_size = 0;
	int result              = 0;

	result = libuna_base16_stream_size_to_byte_stream(
	          data,
	          size,
	          &byte_stream_size,
	          variant,
	          flags,
	          NULL );

	if( ( result == 1 )
	 && ( byte_stream_size > 0 )
	 && ( byte_stream_size < MAXIMUM_STRING_SIZE ) )
	{
		byte_stream = (uint8_t *) malloc( byte_stream_size );

		if( byte_stream != NULL )
		{
			libuna_base16_stream_copy_to_byte_stream(
			 data,
			 size,
			 byte_stream,
			 byte_stream_size,
			 variant,
			 flags,
			 NULL );

			free( byte_stream );

			byte_stream = NULL;
		}
	}
}

void fuzzer_encode_base16_stream(
      const uint8_t *data,
      size_t size,
      uint32_t variant )
{
	uint8_t *base16_stream     = NULL;
	size_t base16_stream_index = 0;
	size_t base16_stream_size  = 0;
	int result                 = 0;

	result = libuna_base16_stream_size_from_byte_stream(
	          data,
	          size,
	          &base16_stream_size,
	          variant,
	          NULL );

	if( ( result == 1 )
	 && ( base16_stream_size > 0 )
	 && ( base16_stream_size < MAXIMUM_STRING_SIZE ) )
	{
		base16_stream = (uint8_t *) malloc( base16_stream_size );

		if( base16_stream != NULL )
		{
			libuna_base16_stream_copy_from_byte_stream(
			 base16_stream,
			 base16_stream_size,
			 data,
			 size,
			 variant,
			 NULL );

			base16_stream_index = 0;

			libuna_base16_stream_with_index_copy_from_byte_stream(
			 base16_stream,
			 base16_stream_size / 2,
			 &base16_stream_index,
			 data,
			 size,
			 variant,
			 NULL );

			free( base16_stream );

			base16_stream = NULL;
		}
	}
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	size_t variant_index = 0;
	size_t flags_index   = 0;

	for( variant_index = 0;
	     variant_index < ( sizeof( test_variants ) / sizeof( test_variants[ 0 ] ) );
	     variant_index++ )
	{
		for( flags_index = 0;
		     flags_index < ( sizeof( test_flags ) / sizeof( test_flags[ 0 ] ) );
		     flags_index++ )
		{
			fuzzer_decode_base16_stream(
			 data,
			 size,
			 test_variants[ variant_index ],
			 test_flags[ flags_index ] );
		}
		fuzzer_encode_base16_stream(
		 data,
		 size,
		 test_variants[ variant_index ] );
	}
	return( 0 );
}

} /* extern "C" */
