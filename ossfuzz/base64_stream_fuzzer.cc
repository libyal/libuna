/*
 * OSS-Fuzz target for libuna base64 stream type
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

static const uint32_t test_variants[ 5 ] = {
	LIBUNA_BASE64_VARIANT_RFC1421,
	LIBUNA_BASE64_VARIANT_RFC1642,
	LIBUNA_BASE64_VARIANT_RFC2045,
	LIBUNA_BASE64_VARIANT_UTF7,
	LIBUNA_BASE64_VARIANT_URL
};

static const uint8_t test_flags[ 2 ] = {
	0,
	LIBUNA_BASE64_FLAG_STRIP_WHITESPACE
};

void fuzzer_decode_base64_stream(
      const uint8_t *data,
      size_t size,
      uint32_t variant,
      uint8_t flags )
{
	uint8_t *byte_stream        = NULL;
	uint32_t base64_triplet     = 0;
	uint8_t padding_size        = 0;
	size_t base64_stream_index  = 0;
	size_t byte_stream_size     = 0;
	size_t number_of_iterations = 0;
	int result                  = 0;

	result = libuna_base64_stream_size_to_byte_stream(
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
			libuna_base64_stream_copy_to_byte_stream(
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
	while( ( base64_stream_index < size )
	    && ( number_of_iterations < size ) )
	{
		base64_triplet = 0;
		padding_size   = 0;

		if( libuna_base64_triplet_copy_from_base64_stream(
		     &base64_triplet,
		     data,
		     size,
		     &base64_stream_index,
		     &padding_size,
		     variant,
		     NULL ) != 1 )
		{
			break;
		}
		number_of_iterations++;
	}
}

void fuzzer_encode_base64_stream(
      const uint8_t *data,
      size_t size,
      uint32_t variant )
{
	uint8_t *base64_stream     = NULL;
	uint8_t *byte_stream       = NULL;
	uint32_t base64_triplet    = 0;
	uint8_t padding_size       = 0;
	size_t base64_stream_index = 0;
	size_t base64_stream_size  = 0;
	size_t byte_stream_index   = 0;
	int result                 = 0;

	result = libuna_base64_triplet_copy_from_byte_stream(
	          &base64_triplet,
	          data,
	          size,
	          &byte_stream_index,
	          &padding_size,
	          NULL );

	if( result == 1 )
	{
		byte_stream = (uint8_t *) malloc( 4 );

		if( byte_stream != NULL )
		{
			byte_stream_index = 0;
			libuna_base64_triplet_copy_to_byte_stream(
			 base64_triplet,
			 byte_stream,
			 4,
			 &byte_stream_index,
			 padding_size,
			 NULL );

			free( byte_stream );

			byte_stream = NULL;
		}
	}
	result = libuna_base64_stream_size_from_byte_stream(
	          data,
	          size,
	          &base64_stream_size,
	          variant,
	          NULL ) ;

	if( ( result == 1 )
	 && ( base64_stream_size > 0 )
	 && ( base64_stream_size < MAXIMUM_STRING_SIZE ) )
	{
		base64_stream = (uint8_t *) malloc( base64_stream_size );

		if( base64_stream != NULL )
		{
			libuna_base64_stream_copy_from_byte_stream(
			 base64_stream,
			 base64_stream_size,
			 data,
			 size,
			 variant,
			 NULL );

			base64_stream_index = 0;

			libuna_base64_stream_with_index_copy_from_byte_stream(
			 base64_stream,
			 base64_stream_size / 2,
			 &base64_stream_index,
			 data,
			 size,
			 variant,
			 NULL );

			base64_stream_index = 0;

			libuna_base64_triplet_copy_to_base64_stream(
			 base64_triplet,
			 base64_stream,
			 base64_stream_size,
			 &base64_stream_index,
			 padding_size,
			 variant,
			 NULL );

			free( base64_stream );

			base64_stream = NULL;
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
			fuzzer_decode_base64_stream(
			 data,
			 size,
			 test_variants[ variant_index ],
			 test_flags[ flags_index ] );
		}
		fuzzer_encode_base64_stream(
		 data,
		 size,
		 test_variants[ variant_index ] );
	}
	return( 0 );
}

} /* extern "C" */
