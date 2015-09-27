/*
 * Unicode and ASCII (byte stream) conversion library base32 stream copy from testing program
 *
 * Copyright (c) 2008-2013, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "una_test_libcstring.h"
#include "una_test_libuna.h"

/* Tests copying a base32 stream from a byte stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_base32_stream_copy_from_byte_stream(
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     uint8_t *base32_stream,
     size_t base32_stream_size,
     uint32_t base32_variant,
     const uint8_t *expected_base32_stream,
     size_t expected_base32_stream_size,
     int expected_result )
{
	libuna_error_t *error            = NULL;
	size_t result_base32_stream_size = 0;
	int result                       = 0;

        fprintf(
         stdout,
         "Testing copying base32 stream from byte stream with variant: 0x%08" PRIx32 "\t",
	 base32_variant );

	result = libuna_base32_stream_size_from_byte_stream(
	          byte_stream,
	          byte_stream_size,
	          &result_base32_stream_size,
	          base32_variant,
	          &error );

	if( result == 1 )
	{
		if( result_base32_stream_size != expected_base32_stream_size )
		{
			result = 0;
		}
	}
	if( result != 0 )
	{
		if( result == -1 )
		{
			libuna_error_free(
			 &error );
		}
		result = libuna_base32_stream_copy_from_byte_stream(
			  base32_stream,
			  base32_stream_size,
			  byte_stream,
			  byte_stream_size,
			  base32_variant,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     base32_stream,
		     expected_base32_stream,
		     sizeof( uint8_t ) * expected_base32_stream_size ) != 0 )
		{
			result = 0;
		}
	}
	if( result == expected_result )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( result == -1 )
	{
		if( expected_result != -1 )
		{
			libuna_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libuna_error_free(
		 &error );
	}
	if( result == expected_result )
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return( result );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	uint8_t base32_stream[ 256 ];

	uint8_t byte_stream[ 32 ] = \
		{ 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.' };

	uint8_t *expected_base32_stream = \
		(uint8_t *) "5468697320697320c3a120746573742e";

	libuna_error_t *error = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "This program does not take arguments.\n" );

		return( EXIT_FAILURE );
	}
#ifdef TODO
	/* Case 1: byte stream is NULL, byte stream size is 16
	 *         base32 stream is a buffer, base32 stream size is 256, variant lower case
	 * Expected result: -1
	 */
	if( una_test_base32_stream_copy_from_byte_stream(
	     NULL,
	     16,
	     base32_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_CASE_LOWER | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE,
	     expected_rfc1421_base32_stream,
	     32,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to base32 stream.\n" );

		goto on_error;
	}
	/* Case 2: byte stream is a buffer, byte stream size is 16
	 *         base32 stream is a buffer, base32 stream size is 256, variant lower case
	 * Expected result: 1
	 */
	if( una_test_base32_stream_copy_from_byte_stream(
	     byte_stream,
	     16,
	     base32_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_CASE_LOWER | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE,
	     expected_rfc1421_base32_stream,
	     32,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to base32 stream.\n" );

		goto on_error;
	}
	/* Case 3: byte stream is a buffer, byte stream size is 16
	 *         base32 stream is a buffer, base32 stream size is 8, variant lower case
	 * Expected result: -1
	 */
	if( una_test_base32_stream_copy_from_byte_stream(
	     byte_stream,
	     16,
	     base32_stream,
	     8,
	     LIBUNA_BASE32_VARIANT_CASE_LOWER | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE,
	     expected_rfc1421_base32_stream,
	     32,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to base32 stream.\n" );

		goto on_error;
	}
	/* Case 4: byte stream is a buffer, byte stream size is 16
	 *         base32 stream is NULL, base32 stream size is 256, variant lower case
	 * Expected result: -1
	 */
	if( una_test_base32_stream_copy_from_byte_stream(
	     byte_stream,
	     16,
	     NULL,
	     256,
	     LIBUNA_BASE32_VARIANT_CASE_LOWER | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE,
	     expected_rfc1421_base32_stream,
	     32,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to base32 stream.\n" );

		goto on_error;
	}
/* TODO test char limit */
/* TODO test encodings */
#endif
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libuna_error_backtrace_fprint(
		 error,
		 stderr );
		libuna_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

