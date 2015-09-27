/*
 * Unicode and ASCII (byte stream) conversion library base32 stream copy to testing program
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

	uint8_t lower_case_base16_stream[ 32 ] = {
		'5', '4', '6', '8', '6', '9', '7', '3', '2', '0', '6', '9', '7', '3', '2', '0',
	        'c', '3', 'a', '1', '2', '0', '7', '4', '6', '5', '7', '3', '7', '4', '2', 'e' };

	uint8_t upper_case_base16_stream[ 32 ] = {
		'5', '4', '6', '8', '6', '9', '7', '3', '2', '0', '6', '9', '7', '3', '2', '0',
	        'C', '3', 'A', '1', '2', '0', '7', '4', '6', '5', '7', '3', '7', '4', '2', 'E' };

	uint8_t utf16le_lower_case_base16_stream[ 64 ] = {
		'5', 0, '4', 0, '6', 0, '8', 0, '6', 0, '9', 0, '7', 0, '3', 0,
	        '2', 0, '0', 0, '6', 0, '9', 0, '7', 0, '3', 0, '2', 0, '0', 0,
	        'c', 0, '3', 0, 'a', 0, '1', 0, '2', 0, '0', 0, '7', 0, '4', 0,
	        '6', 0, '5', 0, '7', 0, '3', 0, '7', 0, '4', 0, '2', 0, 'e', 0 };

	uint8_t utf32be_upper_case_base16_stream[ 128 ] = {
		0, 0, 0, '5', 0, 0, 0, '4', 0, 0, 0, '6', 0, 0, 0, '8', 0, 0, 0, '6', 0, 0, 0, '9', 0, 0, 0, '7', 0, 0, 0, '3',
	        0, 0, 0, '2', 0, 0, 0, '0', 0, 0, 0, '6', 0, 0, 0, '9', 0, 0, 0, '7', 0, 0, 0, '3', 0, 0, 0, '2', 0, 0, 0, '0',
	        0, 0, 0, 'C', 0, 0, 0, '3', 0, 0, 0, 'A', 0, 0, 0, '1', 0, 0, 0, '2', 0, 0, 0, '0', 0, 0, 0, '7', 0, 0, 0, '4',
	        0, 0, 0, '6', 0, 0, 0, '5', 0, 0, 0, '7', 0, 0, 0, '3', 0, 0, 0, '7', 0, 0, 0, '4', 0, 0, 0, '2', 0, 0, 0, 'E' };

	uint8_t *expected_long_byte_stream = \
		(uint8_t *) "The test of success is not what you do when you are on top. Success is how high you bounce when you hit bottom.\n";

	uint8_t *long_base16_stream1 = \
		(uint8_t *) "5468652074657374206f662073756363657373206973206e6f74207768617420\n"
	                    "796f7520646f207768656e20796f7520617265206f6e20746f702e2053756363\n"
		            "65737320697320686f77206869676820796f7520626f756e6365207768656e20\n"
	                    "796f752068697420626f74746f6d2e0a\n";

	uint8_t *long_base16_stream2 = \
		(uint8_t *) "\t5468652074657374206f662073756363657373206973206e6f74207768617420\t\n"
	                    "  796f7520646f207768656e20796f7520617265206f6e20746f702e2053756363  \n"
		            "\t65737320697320686f77206869676820796f7520626f756e6365207768656e20  \n"
	                    "\t796f752068697420626f74746f6d2e0a                                  \n";

	libuna_error_t *error = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "This program does not take arguments.\n" );

		return( EXIT_FAILURE );
	}
#ifdef TODO
	/* Case 1: base16 stream is NULL, base16 stream size is 32, variant lower case
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     NULL,
	     32,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 2: base16 stream is a buffer, base16 stream size is 32, variant lower case
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     lower_case_base16_stream,
	     32,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 3: base16 stream is a buffer, base16 stream size is 32, variant lower case
	 *         byte stream is a buffer, byte stream size is 8
	 * Expected result: -1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     lower_case_base16_stream,
	     32,
	     byte_stream,
	     8,
	     LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 4: base16 stream is a buffer, base16 stream size is 32, variant lower case
	 *         byte stream is NULL, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     lower_case_base16_stream,
	     32,
	     NULL,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 5: base16 stream is a buffer, base16 stream size is 32, variant upper case
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     upper_case_base16_stream,
	     32,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 6: base16 stream is a buffer, base16 stream size is 32, variant lower case
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     upper_case_base16_stream,
	     32,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 6: base16 stream is a buffer, base16 stream size is 64, variant lower case UTF-16 big-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     utf16le_lower_case_base16_stream,
	     64,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF16_BIG_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 7: base16 stream is a buffer, base16 stream size is 64, variant lower case UTF-16 little-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     utf16le_lower_case_base16_stream,
	     64,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 8: base16 stream is a buffer, base16 stream size is 128, variant upper case UTF-32 big-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     utf32be_upper_case_base16_stream,
	     128,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 9: base16 stream is a buffer, base16 stream size is 128, variant upper case UTF-32 little-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     utf32be_upper_case_base16_stream,
	     128,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 10: base16 stream is a buffer, base16 stream size is 228, variant mixed case with 64 character limit
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     long_base16_stream1,
	     228,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
	     0,
	     expected_long_byte_stream,
	     112,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 11: base16 stream is a buffer, base16 stream size is 228, variant mixed case with 76 character limit
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     long_base16_stream1,
	     228,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_76,
	     0,
	     expected_long_byte_stream,
	     112,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 12: base16 stream is a buffer, base16 stream size is 272, variant mixed case with 64 character limit
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base16_stream_copy_to_byte_stream(
	     long_base16_stream2,
	     272,
	     byte_stream,
	     256,
	     LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
	     LIBUNA_BASE16_FLAG_STRIP_WHITESPACE,
	     expected_long_byte_stream,
	     112,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base16 stream to byte stream.\n" );

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

