/*
 * Unicode and ASCII (byte stream) conversion library UTF-16 string copy from testing program
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

/* Tests copying an UTF-16 string from a byte stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf16_string_copy_from_byte_stream(
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int codepage,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     const uint16_t *expected_utf16_string,
     size_t expected_utf16_string_size,
     int expected_result )
{
	libuna_error_t *error           = NULL;
	size_t result_utf16_string_size = 0;
	int result                      = 0;

        fprintf(
         stdout,
         "Testing copying UTF-16 string from byte stream\t" );

	result = libuna_utf16_string_size_from_byte_stream(
	          byte_stream,
	          byte_stream_size,
	          codepage,
	          &result_utf16_string_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf16_string_size != expected_utf16_string_size )
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
		result = libuna_utf16_string_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  byte_stream,
			  byte_stream_size,
			  codepage,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf16_string,
		     expected_utf16_string,
		     sizeof( uint16_t ) * expected_utf16_string_size ) != 0 )
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

/* Tests copying an UTF-16 string from an UTF-7 stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf16_string_copy_from_utf7_stream(
     const uint8_t *utf7_stream,
     size_t utf7_stream_size,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     const uint16_t *expected_utf16_string,
     size_t expected_utf16_string_size,
     int expected_result )
{
	libuna_error_t *error           = NULL;
	size_t result_utf16_string_size = 0;
	int result                      = 0;

        fprintf(
         stdout,
         "Testing copying UTF-16 string from UTF-7 stream\t" );

	result = libuna_utf16_string_size_from_utf7_stream(
	          utf7_stream,
	          utf7_stream_size,
	          &result_utf16_string_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf16_string_size != expected_utf16_string_size )
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
		result = libuna_utf16_string_copy_from_utf7_stream(
			  utf16_string,
			  utf16_string_size,
			  utf7_stream,
			  utf7_stream_size,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf16_string,
		     expected_utf16_string,
		     sizeof( uint16_t ) * expected_utf16_string_size ) != 0 )
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

/* Tests copying an UTF-16 string from an UTF-8 stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf16_string_copy_from_utf8_stream(
     const uint8_t *utf8_stream,
     size_t utf8_stream_size,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     const uint16_t *expected_utf16_string,
     size_t expected_utf16_string_size,
     int expected_result )
{
	libuna_error_t *error           = NULL;
	size_t result_utf16_string_size = 0;
	int result                      = 0;

        fprintf(
         stdout,
         "Testing copying UTF-16 string from UTF-8 stream\t" );

	result = libuna_utf16_string_size_from_utf8_stream(
	          utf8_stream,
	          utf8_stream_size,
	          &result_utf16_string_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf16_string_size != expected_utf16_string_size )
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
		result = libuna_utf16_string_copy_from_utf8_stream(
			  utf16_string,
			  utf16_string_size,
			  utf8_stream,
			  utf8_stream_size,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf16_string,
		     expected_utf16_string,
		     sizeof( uint16_t ) * expected_utf16_string_size ) != 0 )
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

/* Tests copying an UTF-16 string from an UTF-16 stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf16_string_copy_from_utf16_stream(
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     uint8_t byte_order,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     const uint16_t *expected_utf16_string,
     size_t expected_utf16_string_size,
     int expected_result )
{
	libuna_error_t *error           = NULL;
	const char *byte_order_string   = "unknown";
	size_t result_utf16_string_size = 0;
	int result                      = 0;

	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		byte_order_string = "big-endian";
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		byte_order_string = "little-endian";
	}
        fprintf(
         stdout,
         "Testing copying UTF-16 string from UTF-16 stream with byte-order: %s\t",
	 byte_order_string );

	result = libuna_utf16_string_size_from_utf16_stream(
	          utf16_stream,
	          utf16_stream_size,
	          byte_order,
	          &result_utf16_string_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf16_string_size != expected_utf16_string_size )
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
		result = libuna_utf16_string_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  utf16_stream,
			  utf16_stream_size,
			  byte_order,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf16_string,
		     expected_utf16_string,
		     sizeof( uint16_t ) * expected_utf16_string_size ) != 0 )
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

/* Tests copying an UTF-16 string from an UTF-32 stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf16_string_copy_from_utf32_stream(
     const uint8_t *utf32_stream,
     size_t utf32_stream_size,
     uint8_t byte_order,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     const uint16_t *expected_utf16_string,
     size_t expected_utf16_string_size,
     int expected_result )
{
	libuna_error_t *error           = NULL;
	const char *byte_order_string   = "unknown";
	size_t result_utf16_string_size = 0;
	int result                      = 0;

	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		byte_order_string = "big-endian";
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		byte_order_string = "little-endian";
	}
        fprintf(
         stdout,
         "Testing copying UTF-16 string from UTF-32 stream with byte-order: %s\t",
	 byte_order_string );

	result = libuna_utf16_string_size_from_utf32_stream(
	          utf32_stream,
	          utf32_stream_size,
	          byte_order,
	          &result_utf16_string_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf16_string_size != expected_utf16_string_size )
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
		result = libuna_utf16_string_copy_from_utf32_stream(
			  utf16_string,
			  utf16_string_size,
			  utf32_stream,
			  utf32_stream_size,
			  byte_order,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf16_string,
		     expected_utf16_string,
		     sizeof( uint16_t ) * expected_utf16_string_size ) != 0 )
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

/* Tests copying an UTF-16 string from an UTF-8 string
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf16_string_copy_from_utf8_string(
     const libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     const uint16_t *expected_utf16_string,
     size_t expected_utf16_string_size,
     int expected_result )
{
	libuna_error_t *error           = NULL;
	size_t result_utf16_string_size = 0;
	int result                      = 0;

        fprintf(
         stdout,
         "Testing copying UTF-16 string from UTF-8 string\t" );

	result = libuna_utf16_string_size_from_utf8(
	          utf8_string,
	          utf8_string_size,
	          &result_utf16_string_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf16_string_size != expected_utf16_string_size )
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
		result = libuna_utf16_string_copy_from_utf8(
			  utf16_string,
			  utf16_string_size,
			  utf8_string,
			  utf8_string_size,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf16_string,
		     expected_utf16_string,
		     sizeof( uint16_t ) * expected_utf16_string_size ) != 0 )
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

/* Tests copying an UTF-16 string from an UTF-32 string
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_utf16_string_copy_from_utf32_string(
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     const uint16_t *expected_utf16_string,
     size_t expected_utf16_string_size,
     int expected_result )
{
	libuna_error_t *error           = NULL;
	size_t result_utf16_string_size = 0;
	int result                      = 0;

        fprintf(
         stdout,
         "Testing copying UTF-16 string from UTF-32 string\t" );

	result = libuna_utf16_string_size_from_utf32(
	          utf32_string,
	          utf32_string_size,
	          &result_utf16_string_size,
	          &error );

	if( result == 1 )
	{
		if( result_utf16_string_size != expected_utf16_string_size )
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
		result = libuna_utf16_string_copy_from_utf32(
			  utf16_string,
			  utf16_string_size,
			  utf32_string,
			  utf32_string_size,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     utf16_string,
		     expected_utf16_string,
		     sizeof( uint16_t ) * expected_utf16_string_size ) != 0 )
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
	uint16_t utf16_string[ 256 ];

	uint32_t utf32_string[ 16 ]          = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };
	uint16_t expected_utf16_string[ 16 ] = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };
	uint8_t byte_stream[ 16 ]            = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };
	uint8_t utf32_stream[ 64 ]           = { 'T', 0, 0, 0, 'h', 0, 0, 0, 'i', 0, 0, 0, 's', 0, 0, 0, ' ', 0, 0, 0,
	                                         'i', 0, 0, 0, 's', 0, 0, 0, ' ', 0, 0, 0, 0xe1, 0, 0, 0, ' ', 0, 0, 0,
	                                         't', 0, 0, 0, 'e', 0, 0, 0, 's', 0, 0, 0, 't', 0, 0, 0, '.', 0, 0, 0, 0, 0, 0, 0 };
	uint8_t utf16_stream[ 32 ]           = { 'T', 0, 'h', 0, 'i', 0, 's', 0, ' ', 0, 'i', 0, 's', 0, ' ', 0, 0xe1, 0,
	                                         ' ', 0, 't', 0, 'e', 0, 's', 0, 't', 0, '.', 0, 0, 0 };
	uint8_t utf7_stream[ 20 ]            = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', '+', 'A', 'O', 'E', '-', ' ', 't', 'e', 's', 't', '.', 0 };
	uint8_t utf8_stream[ 17 ]            = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.', 0 };
	uint8_t utf8_string[ 17 ]            = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.', 0 };
	libuna_error_t *error                = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "This program does not take arguments.\n" );

		return( EXIT_FAILURE );
	}
	/* byte stream tests
	 */

	/* Case 1: byte stream is NULL, byte stream size is 16
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_byte_stream(
	     NULL,
	     16,
	     LIBUNA_CODEPAGE_WINDOWS_1252,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 2: byte stream is a buffer, byte stream size is 16
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: 1
	 */
	if( una_test_utf16_string_copy_from_byte_stream(
	     byte_stream,
	     16,
	     LIBUNA_CODEPAGE_WINDOWS_1252,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 3: byte stream is a buffer, byte stream size is 16
	 *         UTF-16 string is a buffer, UTF-16 string size is 8
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_byte_stream(
	     byte_stream,
	     16,
	     LIBUNA_CODEPAGE_WINDOWS_1252,
	     utf16_string,
	     8,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 4: byte stream is a buffer, byte stream size is 16
	 *         UTF-16 string is NULL, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_byte_stream(
	     byte_stream,
	     16,
	     LIBUNA_CODEPAGE_WINDOWS_1252,
	     NULL,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy byte stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* UTF-7 stream tests
	 */

	/* Case 1: UTF-7 stream is NULL, UTF-7 stream size is 20
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf7_stream(
	     NULL,
	     20,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-7 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 2: UTF-7 stream is a buffer, UTF-7 stream size is 20
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: 1
	 */
	if( una_test_utf16_string_copy_from_utf7_stream(
	     utf7_stream,
	     20,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-7 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 3: UTF-7 stream is a buffer, UTF-7 stream size is 20
	 *         UTF-16 string is a buffer, UTF-16 string size is 8
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf7_stream(
	     utf7_stream,
	     20,
	     utf16_string,
	     8,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-7 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 4: UTF-7 stream is a buffer, UTF-7 stream size is 20
	 *         UTF-16 string is NULL, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf7_stream(
	     utf7_stream,
	     20,
	     NULL,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-7 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* UTF-8 stream tests
	 */

	/* Case 1: UTF-8 stream is NULL, UTF-8 stream size is 17
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf8_stream(
	     NULL,
	     17,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 2: UTF-8 stream is a buffer, UTF-8 stream size is 17
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: 1
	 */
	if( una_test_utf16_string_copy_from_utf8_stream(
	     utf8_stream,
	     17,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 3: UTF-8 stream is a buffer, UTF-8 stream size is 17
	 *         UTF-16 string is a buffer, UTF-16 string size is 8
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf8_stream(
	     utf8_stream,
	     17,
	     utf16_string,
	     8,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 4: UTF-8 stream is a buffer, UTF-8 stream size is 17
	 *         UTF-16 string is NULL, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf8_stream(
	     utf8_stream,
	     17,
	     NULL,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* UTF-16 stream tests
	 */

	/* Case 1: UTF-16 stream is NULL, UTF-16 stream size is 32 and byte order is little-endian
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf16_stream(
	     NULL,
	     32,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-16 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 2: UTF-16 stream is a buffer, UTF-16 stream size is 32 and byte order is little-endian
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: 1
	 */
	if( una_test_utf16_string_copy_from_utf16_stream(
	     utf16_stream,
	     32,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-16 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 3: UTF-16 stream is a buffer, UTF-16 stream size is 32 and byte order is big-endian
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: 0
	 */
	if( una_test_utf16_string_copy_from_utf16_stream(
	     utf16_stream,
	     32,
	     LIBUNA_ENDIAN_BIG,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     0 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-16 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 4: UTF-16 stream is a buffer, UTF-16 stream size is 32 and byte order is little-endian
	 *         UTF-16 string is a buffer, UTF-16 string size is 8
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf16_stream(
	     utf16_stream,
	     32,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string,
	     8,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-16 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 5: UTF-16 stream is a buffer, UTF-16 stream size is 32 and byte order is little-endian
	 *         UTF-16 string is NULL, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf16_stream(
	     utf16_stream,
	     32,
	     LIBUNA_ENDIAN_LITTLE,
	     NULL,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-16 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* UTF-32 stream tests
	 */

	/* Case 1: UTF-32 stream is NULL, UTF-32 stream size is 64 and byte order is little-endian
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf32_stream(
	     NULL,
	     64,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 2: UTF-32 stream is a buffer, UTF-32 stream size is 64 and byte order is little-endian
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: 1
	 */
	if( una_test_utf16_string_copy_from_utf32_stream(
	     utf32_stream,
	     64,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 3: UTF-32 stream is a buffer, UTF-32 stream size is 64 and byte order is big-endian
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: 0
	 */
	if( una_test_utf16_string_copy_from_utf32_stream(
	     utf32_stream,
	     64,
	     LIBUNA_ENDIAN_BIG,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     0 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 4: UTF-32 stream is a buffer, UTF-32 stream size is 64 and byte order is little-endian
	 *         UTF-16 string is a buffer, UTF-16 string size is 8
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf32_stream(
	     utf32_stream,
	     64,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string,
	     8,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 5: UTF-32 stream is a buffer, UTF-32 stream size is 64 and byte order is little-endian
	 *         UTF-16 string is NULL, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf32_stream(
	     utf32_stream,
	     64,
	     LIBUNA_ENDIAN_LITTLE,
	     NULL,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 stream to UTF-16 string.\n" );

		goto on_error;
	}
	/* UTF-8 string tests
	 */

	/* Case 1: UTF-8 string is NULL, UTF-8 string size is 17
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf8_string(
	     NULL,
	     17,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 string to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 2: UTF-8 string is a buffer, UTF-8 string size is 17
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: 1
	 */
	if( una_test_utf16_string_copy_from_utf8_string(
	     utf8_string,
	     17,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 string to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 3: UTF-8 string is a buffer, UTF-8 string size is 17
	 *         UTF-16 string is a buffer, UTF-16 string size is 8
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf8_string(
	     utf8_string,
	     17,
	     utf16_string,
	     8,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 string to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 4: UTF-8 string is a buffer, UTF-8 string size is 17
	 *         UTF-16 string is NULL, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf8_string(
	     utf8_string,
	     17,
	     NULL,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-8 string to UTF-16 string.\n" );

		goto on_error;
	}
	/* UTF-32 string tests
	 */

	/* Case 1: UTF-32 string is NULL, UTF-32 string size is 16
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf32_string(
	     NULL,
	     16,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 string to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 2: UTF-32 string is a buffer, UTF-32 string size is 16
	 *         UTF-16 string is a buffer, UTF-16 string size is 256
	 * Expected result: 1
	 */
	if( una_test_utf16_string_copy_from_utf32_string(
	     utf32_string,
	     16,
	     utf16_string,
	     256,
	     expected_utf16_string,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 string to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 3: UTF-32 string is a buffer, UTF-32 string size is 16
	 *         UTF-16 string is a buffer, UTF-16 string size is 8
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf32_string(
	     utf32_string,
	     16,
	     utf16_string,
	     8,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 string to UTF-16 string.\n" );

		goto on_error;
	}
	/* Case 4: UTF-32 string is a buffer, UTF-32 string size is 16
	 *         UTF-16 string is NULL, UTF-16 string size is 256
	 * Expected result: -1
	 */
	if( una_test_utf16_string_copy_from_utf32_string(
	     utf32_string,
	     16,
	     NULL,
	     256,
	     expected_utf16_string,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy UTF-32 string to UTF-16 string.\n" );

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

