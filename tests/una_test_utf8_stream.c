/*
 * Library utf8_stream functions test program
 *
 * Copyright (C) 2008-2024, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "una_test_libcerror.h"
#include "una_test_libuna.h"
#include "una_test_macros.h"
#include "una_test_unused.h"

uint8_t una_test_utf8_stream_byte_order_mark[ 3 ] = {
	0xef, 0xbb, 0xbf };

uint8_t una_test_utf8_stream_utf8_stream[ 20 ] = {
	0xef, 0xbb, 0xbf, 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.', 0 };

uint16_t una_test_utf8_stream_utf16_string[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };

uint32_t una_test_utf8_stream_utf32_string[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };

uint8_t una_test_utf8_stream_utf8_string[ 17 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.', 0 };

uint8_t una_test_utf8_stream_error_utf8_string[ 17 ] = {
	'T', 0xfc, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.', 0 };

/* Tests the libuna_utf8_stream_copy_byte_order_mark function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf8_stream_copy_byte_order_mark(
     void )
{
	uint8_t utf8_stream[ 16 ];

	libuna_error_t *error    = NULL;
	size_t utf8_stream_index = 0;
	int result               = 0;

	/* Test regular cases
	 */
	utf8_stream_index = 0;

	result = libuna_utf8_stream_copy_byte_order_mark(
	          utf8_stream,
	          16,
	          &utf8_stream_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf8_stream_byte_order_mark,
	          utf8_stream,
	          sizeof( uint8_t ) * 3 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf8_stream_index = 0;

	result = libuna_utf8_stream_copy_byte_order_mark(
	          NULL,
	          8,
	          &utf8_stream_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_byte_order_mark(
	          utf8_stream,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_stream_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_byte_order_mark(
	          utf8_stream,
	          8,
	          NULL,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf8_stream_size_from_utf8 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf8_stream_size_from_utf8(
     void )
{
	libuna_error_t *error   = NULL;
	size_t utf8_stream_size = 0;
	int result              = 0;

	/* Test regular cases
	 */
	result = libuna_utf8_stream_size_from_utf8(
	          una_test_utf8_stream_utf8_string,
	          17,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_stream_size",
	 utf8_stream_size,
	 (size_t) 20 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf8_stream_size_from_utf8(
	          NULL,
	          17,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_size_from_utf8(
	          una_test_utf8_stream_utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_size_from_utf8(
	          una_test_utf8_stream_utf8_string,
	          17,
	          NULL,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_size_from_utf8(
	          una_test_utf8_stream_error_utf8_string,
	          17,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf8_stream_copy_from_utf8 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf8_stream_copy_from_utf8(
     void )
{
	uint8_t utf8_stream[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf8_stream_copy_from_utf8(
	          utf8_stream,
	          32,
	          una_test_utf8_stream_utf8_string,
	          17,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf8_stream_utf8_stream,
	          utf8_stream,
	          sizeof( uint8_t ) * 20 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf8_stream_copy_from_utf8(
	          NULL,
	          32,
	          una_test_utf8_stream_utf8_string,
	          17,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf8(
	          utf8_stream,
	          (size_t) SSIZE_MAX + 1,
	          una_test_utf8_stream_utf8_string,
	          17,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf8(
	          utf8_stream,
	          32,
	          NULL,
	          17,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf8(
	          utf8_stream,
	          32,
	          una_test_utf8_stream_utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf8(
	          utf8_stream,
	          32,
	          una_test_utf8_stream_error_utf8_string,
	          17,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf8_stream_size_from_utf16 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf8_stream_size_from_utf16(
     void )
{
	libuna_error_t *error   = NULL;
	size_t utf8_stream_size = 0;
	int result              = 0;

	/* Test regular cases
	 */
	result = libuna_utf8_stream_size_from_utf16(
	          una_test_utf8_stream_utf16_string,
	          16,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_stream_size",
	 utf8_stream_size,
	 (size_t) 20 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf8_stream_size_from_utf16(
	          NULL,
	          16,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_size_from_utf16(
	          una_test_utf8_stream_utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_size_from_utf16(
	          una_test_utf8_stream_utf16_string,
	          16,
	          NULL,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* TODO implement test for una_test_utf8_stream_error_utf16_string */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf8_stream_copy_from_utf16 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf8_stream_copy_from_utf16(
     void )
{
	uint8_t utf8_stream[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf8_stream_copy_from_utf16(
	          utf8_stream,
	          32,
	          una_test_utf8_stream_utf16_string,
	          16,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf8_stream_utf8_stream,
	          utf8_stream,
	          sizeof( uint8_t ) * 20 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf8_stream_copy_from_utf16(
	          NULL,
	          32,
	          una_test_utf8_stream_utf16_string,
	          16,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf16(
	          utf8_stream,
	          (size_t) SSIZE_MAX + 1,
	          una_test_utf8_stream_utf16_string,
	          16,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf16(
	          utf8_stream,
	          32,
	          NULL,
	          17,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf16(
	          utf8_stream,
	          32,
	          una_test_utf8_stream_utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* TODO implement test for una_test_utf8_stream_error_utf16_string */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf8_stream_size_from_utf32 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf8_stream_size_from_utf32(
     void )
{
	libuna_error_t *error   = NULL;
	size_t utf8_stream_size = 0;
	int result              = 0;

	/* Test regular cases
	 */
	result = libuna_utf8_stream_size_from_utf32(
	          una_test_utf8_stream_utf32_string,
	          16,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_stream_size",
	 utf8_stream_size,
	 (size_t) 20 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf8_stream_size_from_utf32(
	          NULL,
	          16,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_size_from_utf32(
	          una_test_utf8_stream_utf32_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_stream_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_size_from_utf32(
	          una_test_utf8_stream_utf32_string,
	          16,
	          NULL,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* TODO implement test for una_test_utf8_stream_error_utf32_string */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf8_stream_copy_from_utf32 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf8_stream_copy_from_utf32(
     void )
{
	uint8_t utf8_stream[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf8_stream_copy_from_utf32(
	          utf8_stream,
	          32,
	          una_test_utf8_stream_utf32_string,
	          16,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf8_stream_utf8_stream,
	          utf8_stream,
	          sizeof( uint8_t ) * 20 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf8_stream_copy_from_utf32(
	          NULL,
	          32,
	          una_test_utf8_stream_utf32_string,
	          16,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf32(
	          utf8_stream,
	          (size_t) SSIZE_MAX + 1,
	          una_test_utf8_stream_utf32_string,
	          16,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf32(
	          utf8_stream,
	          32,
	          NULL,
	          17,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_utf8_stream_copy_from_utf32(
	          utf8_stream,
	          32,
	          una_test_utf8_stream_utf32_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* TODO implement test for una_test_utf8_stream_error_utf32_string */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc UNA_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] UNA_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc UNA_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] UNA_TEST_ATTRIBUTE_UNUSED )
#endif
{
	UNA_TEST_UNREFERENCED_PARAMETER( argc )
	UNA_TEST_UNREFERENCED_PARAMETER( argv )

	UNA_TEST_RUN(
	 "libuna_utf8_stream_copy_byte_order_mark",
	 una_test_utf8_stream_copy_byte_order_mark );

	UNA_TEST_RUN(
	 "libuna_utf8_stream_size_from_utf8",
	 una_test_utf8_stream_size_from_utf8 );

	UNA_TEST_RUN(
	 "libuna_utf8_stream_copy_from_utf8",
	 una_test_utf8_stream_copy_from_utf8 );

	UNA_TEST_RUN(
	 "libuna_utf8_stream_size_from_utf16",
	 una_test_utf8_stream_size_from_utf16 );

	UNA_TEST_RUN(
	 "libuna_utf8_stream_copy_from_utf16",
	 una_test_utf8_stream_copy_from_utf16 );

	UNA_TEST_RUN(
	 "libuna_utf8_stream_size_from_utf32",
	 una_test_utf8_stream_size_from_utf32 );

	UNA_TEST_RUN(
	 "libuna_utf8_stream_copy_from_utf32",
	 una_test_utf8_stream_copy_from_utf32 );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

