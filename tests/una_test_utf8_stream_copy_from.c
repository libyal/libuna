/*
 * Unicode and ASCII (byte stream) conversion library UTF-8 stream copy from testing program
 *
 * Copyright (c) 2008-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

/* Tests copying an UTF-8 stream from an UTF-8 string
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf8_stream_copy_from_utf8_string(
     const libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     uint8_t *utf8_stream,
     size_t utf8_stream_size,
     const uint8_t *expected_utf8_stream,
     size_t expected_utf8_stream_size,
     int expected_result )
{
	libuna_error_t *error          = NULL;
	size_t result_utf8_stream_size = 0;
	int result                     = 0;

        fprintf(
         stdout,
         "Testing copying UTF-8 stream from UTF-8 string\t" );

	result = libuna_utf8_stream_size_from_utf8(
	          utf8_string,
	          utf8_string_size,
	          &result_utf8_stream_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf8_stream_size != expected_utf8_stream_size )
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
		result = libuna_utf8_stream_copy_from_utf8(
			  utf8_stream,
			  utf8_stream_size,
			  utf8_string,
			  utf8_string_size,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf8_stream,
		     expected_utf8_stream,
		     sizeof( uint8_t ) * expected_utf8_stream_size ) != 0 )
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

/* Tests copying an UTF-8 stream from an UTF-16 string
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf8_stream_copy_from_utf16_string(
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     uint8_t *utf8_stream,
     size_t utf8_stream_size,
     const uint8_t *expected_utf8_stream,
     size_t expected_utf8_stream_size,
     int expected_result )
{
	libuna_error_t *error          = NULL;
	size_t result_utf8_stream_size = 0;
	int result                     = 0;

        fprintf(
         stdout,
         "Testing copying UTF-8 stream from UTF-16 string\t" );

	result = libuna_utf8_stream_size_from_utf16(
	          utf16_string,
	          utf16_string_size,
	          &result_utf8_stream_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf8_stream_size != expected_utf8_stream_size )
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
		result = libuna_utf8_stream_copy_from_utf16(
			  utf8_stream,
			  utf8_stream_size,
			  utf16_string,
			  utf16_string_size,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf8_stream,
		     expected_utf8_stream,
		     sizeof( uint8_t ) * expected_utf8_stream_size ) != 0 )
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

/* Tests copying an UTF-8 stream from an UTF-32 string
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf8_stream_copy_from_utf32_string(
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     uint8_t *utf8_stream,
     size_t utf8_stream_size,
     const uint8_t *expected_utf8_stream,
     size_t expected_utf8_stream_size,
     int expected_result )
{
	libuna_error_t *error          = NULL;
	size_t result_utf8_stream_size = 0;
	int result                     = 0;

        fprintf(
         stdout,
         "Testing copying UTF-8 stream from UTF-32 string\t" );

	result = libuna_utf8_stream_size_from_utf32(
	          utf32_string,
	          utf32_string_size,
	          &result_utf8_stream_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf8_stream_size != expected_utf8_stream_size )
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
		result = libuna_utf8_stream_copy_from_utf32(
			  utf8_stream,
			  utf8_stream_size,
			  utf32_string,
			  utf32_string_size,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf8_stream,
		     expected_utf8_stream,
		     sizeof( uint8_t ) * expected_utf8_stream_size ) != 0 )
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
	uint8_t utf8_stream[ 256 ];

	uint32_t utf32_string[ 16 ]        = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };
	uint16_t utf16_string[ 16 ]        = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };
	uint8_t expected_utf8_stream[ 20 ] = { 0xef, 0xbb, 0xbf, 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.', 0 };
	uint8_t utf8_string[ 17 ]          = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.', 0 };
	libuna_error_t *error              = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "This program does not take arguments.\n" );

		return( EXIT_FAILURE );
	}
	/* UTF-8 string tests
	 */

	/* Case 1: UTF-8 string is NULL, UTF-8 string size is 17
	 *         UTF-8 stream is a buffer, UTF-8 stream size is 256
	 * Expected result: -1
	 */
	if( una_test_utf8_stream_copy_from_utf8_string(
	     NULL,
	     17,
	     utf8_stream,
	     256,
	     expected_utf8_stream,
	     20,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* Case 2: UTF-8 string is a buffer, UTF-8 string size is 17
	 *         UTF-8 stream is a buffer, UTF-8 stream size is 256
	 * Expected result: 1
	 */
	if( una_test_utf8_stream_copy_from_utf8_string(
	     utf8_string,
	     17,
	     utf8_stream,
	     256,
	     expected_utf8_stream,
	     20,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* Case 3: UTF-8 string is a buffer, UTF-8 string size is 17
	 *         UTF-8 stream is a buffer, UTF-8 stream size is 8
	 * Expected result: -1
	 */
	if( una_test_utf8_stream_copy_from_utf8_string(
	     utf8_string,
	     17,
	     utf8_stream,
	     8,
	     expected_utf8_stream,
	     20,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* Case 4: UTF-8 string is a buffer, UTF-8 string size is 17
	 *         UTF-8 stream is NULL, UTF-8 stream size is 256
	 * Expected result: -1
	 */
	if( una_test_utf8_stream_copy_from_utf8_string(
	     utf8_string,
	     17,
	     NULL,
	     256,
	     expected_utf8_stream,
	     20,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* UTF-16 string tests
	 */

	/* Case 1: UTF-16 string is NULL, UTF-16 string size is 16
	 *         UTF-8 stream is a buffer, UTF-8 stream size is 256
	 * Expected result: -1
	 */
	if( una_test_utf8_stream_copy_from_utf16_string(
	     NULL,
	     16,
	     utf8_stream,
	     256,
	     expected_utf8_stream,
	     20,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-16 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* Case 2: UTF-16 string is a buffer, UTF-16 string size is 16
	 *         UTF-8 stream is a buffer, UTF-8 stream size is 256
	 * Expected result: 1
	 */
	if( una_test_utf8_stream_copy_from_utf16_string(
	     utf16_string,
	     16,
	     utf8_stream,
	     256,
	     expected_utf8_stream,
	     20,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-16 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* Case 3: UTF-16 string is a buffer, UTF-16 string size is 16
	 *         UTF-8 stream is a buffer, UTF-8 stream size is 8
	 * Expected result: -1
	 */
	if( una_test_utf8_stream_copy_from_utf16_string(
	     utf16_string,
	     16,
	     utf8_stream,
	     8,
	     expected_utf8_stream,
	     20,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-16 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* Case 4: UTF-16 string is a buffer, UTF-16 string size is 16
	 *         UTF-8 stream is NULL, UTF-8 stream size is 256
	 * Expected result: -1
	 */
	if( una_test_utf8_stream_copy_from_utf16_string(
	     utf16_string,
	     16,
	     NULL,
	     256,
	     expected_utf8_stream,
	     20,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-16 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* UTF-32 string tests
	 */

	/* Case 1: UTF-32 string is NULL, UTF-32 string size is 16
	 *         UTF-8 stream is a buffer, UTF-8 stream size is 256
	 * Expected result: -1
	 */
	if( una_test_utf8_stream_copy_from_utf32_string(
	     NULL,
	     16,
	     utf8_stream,
	     256,
	     expected_utf8_stream,
	     20,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* Case 2: UTF-32 string is a buffer, UTF-32 string size is 16
	 *         UTF-8 stream is a buffer, UTF-8 stream size is 256
	 * Expected result: 1
	 */
	if( una_test_utf8_stream_copy_from_utf32_string(
	     utf32_string,
	     16,
	     utf8_stream,
	     256,
	     expected_utf8_stream,
	     20,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* Case 3: UTF-32 string is a buffer, UTF-32 string size is 16
	 *         UTF-8 stream is a buffer, UTF-8 stream size is 8
	 * Expected result: -1
	 */
	if( una_test_utf8_stream_copy_from_utf32_string(
	     utf32_string,
	     16,
	     utf8_stream,
	     8,
	     expected_utf8_stream,
	     20,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 string to UTF-8 stream.\n" );

		goto on_error;
	}
	/* Case 4: UTF-32 string is a buffer, UTF-32 string size is 16
	 *         UTF-8 stream is NULL, UTF-8 stream size is 256
	 * Expected result: -1
	 */
	if( una_test_utf8_stream_copy_from_utf32_string(
	     utf32_string,
	     16,
	     NULL,
	     256,
	     expected_utf8_stream,
	     20,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 string to UTF-8 stream.\n" );

		goto on_error;
	}
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

