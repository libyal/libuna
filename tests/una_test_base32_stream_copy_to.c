/*
 * Unicode and ASCII (byte stream) conversion library base32 stream copy to testing program
 *
 * Copyright (C) 2008-2015, Joachim Metz <joachim.metz@gmail.com>
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

/* Tests copying a base32 stream to a byte stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_base32_stream_copy_to_byte_stream(
     const uint8_t *base32_stream,
     size_t base32_stream_size,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint32_t base32_variant,
     uint8_t flags,
     const uint8_t *expected_byte_stream,
     size_t expected_byte_stream_size,
     int expected_result )
{
	libuna_error_t *error          = NULL;
	size_t result_byte_stream_size = 0;
	int result                     = 0;

        fprintf(
         stdout,
         "Testing copying base32 stream to byte stream with variant: 0x%08" PRIx32 "\t",
	 base32_variant );

	result = libuna_base32_stream_size_to_byte_stream(
	          base32_stream,
	          base32_stream_size,
	          &result_byte_stream_size,
	          base32_variant,
	          flags,
	          &error );

	if( result == 1 )
	{
		if( result_byte_stream_size != expected_byte_stream_size )
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
		result = libuna_base32_stream_copy_to_byte_stream(
			  base32_stream,
			  base32_stream_size,
			  byte_stream,
			  byte_stream_size,
			  base32_variant,
			  flags,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     byte_stream,
		     expected_byte_stream,
		     sizeof( uint8_t ) * expected_byte_stream_size ) != 0 )
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
	uint8_t byte_stream[ 256 ];

	uint8_t expected_byte_stream[ 16 ] = {
		'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.' };

	uint8_t base32_stream[ 32 ] = {
		'K', 'R', 'U', 'G', 'S', '4', 'Z', 'A', 'N', 'F', 'Z', 'S', 'B', 'Q', '5', 'B',
	        'E', 'B', '2', 'G', 'K', '4', '3', 'U', 'F', 'Y', '=', '=', '=', '=', '=', '=' };

	uint8_t utf16le_base32_stream[ 64 ] = {
		'K', 0, 'R', 0, 'U', 0, 'G', 0, 'S', 0, '4', 0, 'Z', 0, 'A', 0,
	        'N', 0, 'F', 0, 'Z', 0, 'S', 0, 'B', 0, 'Q', 0, '5', 0, 'B', 0,
	        'E', 0, 'B', 0, '2', 0, 'G', 0, 'K', 0, '4', 0, '3', 0, 'U', 0,
	        'F', 0, 'Y', 0, '=', 0, '=', 0, '=', 0, '=', 0, '=', 0, '=', 0 };

	uint8_t *expected_long_byte_stream = \
		(uint8_t *) "The test of success is not what you do when you are on top. " \
	                    "Success is how high you bounce when you hit bottom.\n";

	uint8_t *long_base32_stream1 = \
		(uint8_t *) "KRUGKIDUMVZXIIDPMYQHG5LDMNSXG4ZANFZSA3TPOQQHO2DBOQQHS33VEBSG6IDX" \
	                    "NBSW4IDZN52SAYLSMUQG63RAORXXALRAKN2WGY3FONZSA2LTEBUG65ZANBUWO2BA" \
	                    "PFXXKIDCN52W4Y3FEB3WQZLOEB4W65JANBUXIIDCN52HI33NFYFA====";

	libuna_error_t *error = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "This program does not take arguments.\n" );

		return( EXIT_FAILURE );
	}
	/* Case 1: base32 stream is NULL, base32 stream size is 32, variant RFC4648
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     NULL,
	     32,
	     byte_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_RFC4648,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 2: base32 stream is a buffer, base32 stream size is 32, variant RFC4648
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     base32_stream,
	     32,
	     byte_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_RFC4648,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 3: base32 stream is a buffer, base32 stream size is 32, variant RFC4648
	 *         byte stream is a buffer, byte stream size is 8
	 * Expected result: -1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     base32_stream,
	     32,
	     byte_stream,
	     8,
	     LIBUNA_BASE32_VARIANT_RFC4648,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 4: base32 stream is a buffer, base32 stream size is 32, variant RFC4648
	 *         byte stream is NULL, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     base32_stream,
	     32,
	     NULL,
	     256,
	     LIBUNA_BASE32_VARIANT_RFC4648,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 5: base32 stream is a buffer, base32 stream size is 64, variant RFC4648 UTF-16 big-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     utf16le_base32_stream,
	     64,
	     byte_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_RFC4648 | LIBUNA_BASE32_VARIANT_ENCODING_UTF16_BIG_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 6: base32 stream is a buffer, base32 stream size is 64, variant RFC4648 UTF-16 little-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     utf16le_base32_stream,
	     64,
	     byte_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_RFC4648 | LIBUNA_BASE32_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
#ifdef TODO
	/* Case 8: base32 stream is a buffer, base32 stream size is 128, variant upper case UTF-32 big-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     utf32be_upper_case_base32_stream,
	     128,
	     byte_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_CASE_UPPER | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_ENCODING_UTF32_BIG_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 9: base32 stream is a buffer, base32 stream size is 128, variant upper case UTF-32 little-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     utf32be_upper_case_base32_stream,
	     128,
	     byte_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_CASE_UPPER | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 10: base32 stream is a buffer, base32 stream size is 228, variant mixed case with 64 character limit
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     long_base32_stream1,
	     228,
	     byte_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_CASE_MIXED | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64,
	     0,
	     expected_long_byte_stream,
	     112,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 11: base32 stream is a buffer, base32 stream size is 228, variant mixed case with 76 character limit
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     long_base32_stream1,
	     228,
	     byte_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_CASE_MIXED | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_76,
	     0,
	     expected_long_byte_stream,
	     112,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 12: base32 stream is a buffer, base32 stream size is 272, variant mixed case with 64 character limit
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base32_stream_copy_to_byte_stream(
	     long_base32_stream2,
	     272,
	     byte_stream,
	     256,
	     LIBUNA_BASE32_VARIANT_CASE_MIXED | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64,
	     LIBUNA_BASE32_FLAG_STRIP_WHITESPACE,
	     expected_long_byte_stream,
	     112,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base32 stream to byte stream.\n" );

		goto on_error;
	}
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

