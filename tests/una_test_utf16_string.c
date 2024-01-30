/*
 * Library utf16_string functions test program
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

uint8_t una_test_utf16_string_byte_stream[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };

uint8_t una_test_utf16_string_scsu_stream1[ 9 ] = {
	0xd6, 0x6c, 0x20, 0x66, 0x6c, 0x69, 0x65, 0xdf, 0x74 };

uint8_t una_test_utf16_string_scsu_stream2[ 7 ] = {
	0x12, 0x9c, 0xbe, 0xc1, 0xba, 0xb2, 0xb0 };

uint8_t una_test_utf16_string_scsu_stream3[ 178 ] = {
	0x08, 0x00, 0x1b, 0x4c, 0xea, 0x16, 0xca, 0xd3, 0x94, 0x0f, 0x53, 0xef, 0x61, 0x1b, 0xe5, 0x84,
	0xc4, 0x0f, 0x53, 0xef, 0x61, 0x1b, 0xe5, 0x84, 0xc4, 0x16, 0xca, 0xd3, 0x94, 0x08, 0x02, 0x0f,
	0x53, 0x4a, 0x4e, 0x16, 0x7d, 0x00, 0x30, 0x82, 0x52, 0x4d, 0x30, 0x6b, 0x6d, 0x41, 0x88, 0x4c,
	0xe5, 0x97, 0x9f, 0x08, 0x0c, 0x16, 0xca, 0xd3, 0x94, 0x15, 0xae, 0x0e, 0x6b, 0x4c, 0x08, 0x0d,
	0x8c, 0xb4, 0xa3, 0x9f, 0xca, 0x99, 0xcb, 0x8b, 0xc2, 0x97, 0xcc, 0xaa, 0x84, 0x08, 0x02, 0x0e,
	0x7c, 0x73, 0xe2, 0x16, 0xa3, 0xb7, 0xcb, 0x93, 0xd3, 0xb4, 0xc5, 0xdc, 0x9f, 0x0e, 0x79, 0x3e,
	0x06, 0xae, 0xb1, 0x9d, 0x93, 0xd3, 0x08, 0x0c, 0xbe, 0xa3, 0x8f, 0x08, 0x88, 0xbe, 0xa3, 0x8d,
	0xd3, 0xa8, 0xa3, 0x97, 0xc5, 0x17, 0x89, 0x08, 0x0d, 0x15, 0xd2, 0x08, 0x01, 0x93, 0xc8, 0xaa,
	0x8f, 0x0e, 0x61, 0x1b, 0x99, 0xcb, 0x0e, 0x4e, 0xba, 0x9f, 0xa1, 0xae, 0x93, 0xa8, 0xa0, 0x08,
	0x02, 0x08, 0x0c, 0xe2, 0x16, 0xa3, 0xb7, 0xcb, 0x0f, 0x4f, 0xe1, 0x80, 0x05, 0xec, 0x60, 0x8d,
	0xea, 0x06, 0xd3, 0xe6, 0x0f, 0x8a, 0x00, 0x30, 0x44, 0x65, 0xb9, 0xe4, 0xfe, 0xe7, 0xc2, 0x06,
	0xcb, 0x82 };

uint8_t una_test_utf16_string_scsu_stream4[ 35 ] = {
	0x41, 0xdf, 0x12, 0x81, 0x03, 0x5f, 0x10, 0xdf, 0x1b, 0x03, 0xdf, 0x1c, 0x88, 0x80, 0x0b, 0xbf,
	0xff, 0xff, 0x0d, 0x0a, 0x41, 0x10, 0xdf, 0x12, 0x81, 0x03, 0x5f, 0x10, 0xdf, 0x13, 0xdf, 0x14,
	0x80, 0x15, 0xff };

uint8_t una_test_utf16_string_utf16_stream[ 32 ] = {
	'T', 0, 'h', 0, 'i', 0, 's', 0, ' ', 0, 'i', 0, 's', 0, ' ', 0, 0xe1, 0,
	' ', 0, 't', 0, 'e', 0, 's', 0, 't', 0, '.', 0, 0, 0 };

uint8_t una_test_utf16_string_utf32_stream[ 64 ] = {
	'T', 0, 0, 0, 'h', 0, 0, 0, 'i', 0, 0, 0, 's', 0, 0, 0, ' ', 0, 0, 0,
	'i', 0, 0, 0, 's', 0, 0, 0, ' ', 0, 0, 0, 0xe1, 0, 0, 0, ' ', 0, 0, 0,
	't', 0, 0, 0, 'e', 0, 0, 0, 's', 0, 0, 0, 't', 0, 0, 0, '.', 0, 0, 0, 0, 0, 0, 0 };

uint8_t una_test_utf16_string_utf7_stream[ 20 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', '+', 'A', 'O', 'E', '-', ' ', 't', 'e', 's', 't', '.', 0 };

uint8_t una_test_utf16_string_utf8_stream[ 17 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.', 0 };

uint16_t una_test_utf16_string_utf16_string[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };

uint32_t una_test_utf16_string_utf32_string[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xe1, ' ', 't', 'e', 's', 't', '.', 0 };

uint8_t una_test_utf16_string_utf8_string[ 17 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.', 0 };

/* Tests the libuna_utf16_string_size_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_size_from_byte_stream(
     void )
{
	libuna_error_t *error    = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_size_from_byte_stream(
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_byte_stream(
	          una_test_utf16_string_byte_stream,
	          15,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_byte_stream(
	          una_test_utf16_string_byte_stream,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_size_from_byte_stream(
	          NULL,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_byte_stream(
	          una_test_utf16_string_byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_byte_stream(
	          una_test_utf16_string_byte_stream,
	          16,
	          -1,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_byte_stream(
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

/* Tests the libuna_utf16_string_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_copy_from_byte_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_copy_from_byte_stream(
	          utf16_string,
	          32,
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf16_string_copy_from_byte_stream(
	          NULL,
	          32,
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

/* Tests the libuna_utf16_string_with_index_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_with_index_copy_from_byte_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error     = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_byte_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_byte_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_byte_stream,
	          15,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_byte_stream(
	          NULL,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_with_index_copy_from_byte_stream(
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_with_index_copy_from_byte_stream(
	          utf16_string,
	          32,
	          NULL,
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_with_index_copy_from_byte_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          NULL,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_with_index_copy_from_byte_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_with_index_copy_from_byte_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_byte_stream,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_with_index_copy_from_byte_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_byte_stream,
	          16,
	          -1,
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

/* Tests the libuna_utf16_string_compare_with_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_compare_with_byte_stream(
     void )
{
	uint8_t byte_stream_equal[ 5 ]     = { 'e', 'q', 'u', 'a', 'l' };
	uint8_t byte_stream_great[ 5 ]     = { 'g', 'r', 'e', 'a', 't' };
	uint8_t byte_stream_less[ 4 ]      = { 'l', 'e', 's', 's' };
	uint8_t byte_stream_lesser[ 6 ]    = { 'l', 'e', 's', 's', 'e', 'r' };
	uint8_t byte_stream_more[ 4 ]      = { 'm', 'o', 'r', 'e' };
	uint16_t utf16_string_equal[ 5 ]   = { 'e', 'q', 'u', 'a', 'l' };
	uint16_t utf16_string_greater[ 7 ] = { 'g', 'r', 'e', 'a', 't', 'e', 'r' };
	uint16_t utf16_string_less[ 4 ]    = { 'l', 'e', 's', 's' };
	uint16_t utf16_string_more[ 4 ]    = { 'm', 'o', 'r', 'e' };

	libuna_error_t *error              = NULL;
	int result                         = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_compare_with_byte_stream(
	          utf16_string_equal,
	          5,
	          byte_stream_equal,
	          5,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_EQUAL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_byte_stream(
	          utf16_string_more,
	          4,
	          byte_stream_less,
	          4,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_byte_stream(
	          utf16_string_less,
	          4,
	          byte_stream_more,
	          4,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_byte_stream(
	          utf16_string_greater,
	          7,
	          byte_stream_great,
	          5,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_byte_stream(
	          utf16_string_less,
	          4,
	          byte_stream_lesser,
	          6,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_compare_with_byte_stream(
	          NULL,
	          16,
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_compare_with_byte_stream(
	          una_test_utf16_string_utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          una_test_utf16_string_byte_stream,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_compare_with_byte_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          NULL,
	          16,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_compare_with_byte_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          una_test_utf16_string_byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libuna_utf16_string_compare_with_byte_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          una_test_utf16_string_byte_stream,
	          16,
	          -1,
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

/* Tests the libuna_utf16_string_size_from_utf7_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_size_from_utf7_stream(
     void )
{
	libuna_error_t *error    = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_size_from_utf7_stream(
	          una_test_utf16_string_utf7_stream,
	          20,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf7_stream(
	          una_test_utf16_string_utf7_stream,
	          19,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf7_stream(
	          una_test_utf16_string_utf7_stream,
	          0,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_size_from_utf7_stream(
	          NULL,
	          20,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf7_stream(
	          una_test_utf16_string_utf7_stream,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf7_stream(
	          una_test_utf16_string_utf7_stream,
	          20,
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

/* Tests the libuna_utf16_string_copy_from_utf7_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_copy_from_utf7_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_copy_from_utf7_stream(
	          utf16_string,
	          32,
	          una_test_utf16_string_utf7_stream,
	          20,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf16_string_copy_from_utf7_stream(
	          NULL,
	          32,
	          una_test_utf16_string_utf7_stream,
	          20,
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

/* Tests the libuna_utf16_string_with_index_copy_from_utf7_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_with_index_copy_from_utf7_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error     = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf7_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf7_stream,
	          20,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf7_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf7_stream,
	          19,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf7_stream(
	          NULL,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf7_stream,
	          20,
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

	result = libuna_utf16_string_with_index_copy_from_utf7_stream(
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          una_test_utf16_string_utf7_stream,
	          20,
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

	result = libuna_utf16_string_with_index_copy_from_utf7_stream(
	          utf16_string,
	          32,
	          NULL,
	          una_test_utf16_string_utf7_stream,
	          20,
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

	result = libuna_utf16_string_with_index_copy_from_utf7_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          NULL,
	          20,
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

	result = libuna_utf16_string_with_index_copy_from_utf7_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf7_stream,
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

	result = libuna_utf16_string_with_index_copy_from_utf7_stream(
	          utf16_string,
	          0,
	          &utf16_string_index,
	          una_test_utf16_string_utf7_stream,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf16_string_compare_with_utf7_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_compare_with_utf7_stream(
     void )
{
	uint8_t utf7_stream_equal[ 5 ]     = { 'e', 'q', 'u', 'a', 'l' };
	uint8_t utf7_stream_great[ 5 ]     = { 'g', 'r', 'e', 'a', 't' };
	uint8_t utf7_stream_less[ 4 ]      = { 'l', 'e', 's', 's' };
	uint8_t utf7_stream_lesser[ 6 ]    = { 'l', 'e', 's', 's', 'e', 'r' };
	uint8_t utf7_stream_more[ 4 ]      = { 'm', 'o', 'r', 'e' };
	uint16_t utf16_string_equal[ 5 ]   = { 'e', 'q', 'u', 'a', 'l' };
	uint16_t utf16_string_greater[ 7 ] = { 'g', 'r', 'e', 'a', 't', 'e', 'r' };
	uint16_t utf16_string_less[ 4 ]    = { 'l', 'e', 's', 's' };
	uint16_t utf16_string_more[ 4 ]    = { 'm', 'o', 'r', 'e' };

	libuna_error_t *error              = NULL;
	int result                         = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_compare_with_utf7_stream(
	          utf16_string_equal,
	          5,
	          utf7_stream_equal,
	          5,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_EQUAL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf7_stream(
	          utf16_string_more,
	          4,
	          utf7_stream_less,
	          4,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf7_stream(
	          utf16_string_less,
	          4,
	          utf7_stream_more,
	          4,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf7_stream(
	          utf16_string_greater,
	          7,
	          utf7_stream_great,
	          5,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf7_stream(
	          utf16_string_less,
	          4,
	          utf7_stream_lesser,
	          6,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_compare_with_utf7_stream(
	          NULL,
	          16,
	          una_test_utf16_string_utf7_stream,
	          20,
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

	result = libuna_utf16_string_compare_with_utf7_stream(
	          una_test_utf16_string_utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          una_test_utf16_string_utf7_stream,
	          20,
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

	result = libuna_utf16_string_compare_with_utf7_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          NULL,
	          20,
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

	result = libuna_utf16_string_compare_with_utf7_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          una_test_utf16_string_utf7_stream,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf16_string_size_from_utf8 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_size_from_utf8(
     void )
{
	libuna_error_t *error    = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_size_from_utf8(
	          una_test_utf16_string_utf8_string,
	          17,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf8(
	          una_test_utf16_string_utf8_string,
	          16,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf8(
	          una_test_utf16_string_utf8_string,
	          0,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_size_from_utf8(
	          NULL,
	          17,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf8(
	          una_test_utf16_string_utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf8(
	          una_test_utf16_string_utf8_string,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf16_string_copy_from_utf8 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_copy_from_utf8(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_copy_from_utf8(
	          utf16_string,
	          32,
	          una_test_utf16_string_utf8_string,
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
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf16_string_copy_from_utf8(
	          NULL,
	          32,
	          una_test_utf16_string_utf8_string,
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

/* Tests the libuna_utf16_string_with_index_copy_from_utf8 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_with_index_copy_from_utf8(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error     = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf8(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_string,
	          17,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf8(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_string,
	          16,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf8(
	          NULL,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_string,
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

	result = libuna_utf16_string_with_index_copy_from_utf8(
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_string,
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

	result = libuna_utf16_string_with_index_copy_from_utf8(
	          utf16_string,
	          32,
	          NULL,
	          una_test_utf16_string_utf8_string,
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

	result = libuna_utf16_string_with_index_copy_from_utf8(
	          utf16_string,
	          32,
	          &utf16_string_index,
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

	result = libuna_utf16_string_with_index_copy_from_utf8(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_string,
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

	result = libuna_utf16_string_with_index_copy_from_utf8(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_string,
	          0,
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

/* Tests the libuna_utf16_string_size_from_utf8_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_size_from_utf8_stream(
     void )
{
	libuna_error_t *error    = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_size_from_utf8_stream(
	          una_test_utf16_string_utf8_stream,
	          17,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf8_stream(
	          una_test_utf16_string_utf8_stream,
	          16,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf8_stream(
	          una_test_utf16_string_utf8_stream,
	          0,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_size_from_utf8_stream(
	          NULL,
	          17,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf8_stream(
	          una_test_utf16_string_utf8_stream,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf8_stream(
	          una_test_utf16_string_utf8_stream,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf16_string_copy_from_utf8_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_copy_from_utf8_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_copy_from_utf8_stream(
	          utf16_string,
	          32,
	          una_test_utf16_string_utf8_stream,
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
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf16_string_copy_from_utf8_stream(
	          NULL,
	          32,
	          una_test_utf16_string_utf8_stream,
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

/* Tests the libuna_utf16_string_with_index_copy_from_utf8_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_with_index_copy_from_utf8_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error     = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf8_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_stream,
	          17,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf8_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_stream,
	          16,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf8_stream(
	          NULL,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_stream,
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

	result = libuna_utf16_string_with_index_copy_from_utf8_stream(
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_stream,
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

	result = libuna_utf16_string_with_index_copy_from_utf8_stream(
	          utf16_string,
	          32,
	          NULL,
	          una_test_utf16_string_utf8_stream,
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

	result = libuna_utf16_string_with_index_copy_from_utf8_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
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

	result = libuna_utf16_string_with_index_copy_from_utf8_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_stream,
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

	result = libuna_utf16_string_with_index_copy_from_utf8_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf8_stream,
	          0,
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

/* Tests the libuna_utf16_string_compare_with_utf8_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_compare_with_utf8_stream(
     void )
{
	uint8_t utf8_stream_equal[ 5 ]     = { 'e', 'q', 'u', 'a', 'l' };
	uint8_t utf8_stream_great[ 5 ]     = { 'g', 'r', 'e', 'a', 't' };
	uint8_t utf8_stream_less[ 4 ]      = { 'l', 'e', 's', 's' };
	uint8_t utf8_stream_lesser[ 6 ]    = { 'l', 'e', 's', 's', 'e', 'r' };
	uint8_t utf8_stream_more[ 4 ]      = { 'm', 'o', 'r', 'e' };
	uint16_t utf16_string_equal[ 5 ]   = { 'e', 'q', 'u', 'a', 'l' };
	uint16_t utf16_string_greater[ 7 ] = { 'g', 'r', 'e', 'a', 't', 'e', 'r' };
	uint16_t utf16_string_less[ 4 ]    = { 'l', 'e', 's', 's' };
	uint16_t utf16_string_more[ 4 ]    = { 'm', 'o', 'r', 'e' };

	libuna_error_t *error              = NULL;
	int result                         = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_compare_with_utf8_stream(
	          utf16_string_equal,
	          5,
	          utf8_stream_equal,
	          5,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_EQUAL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf8_stream(
	          utf16_string_more,
	          4,
	          utf8_stream_less,
	          4,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf8_stream(
	          utf16_string_less,
	          4,
	          utf8_stream_more,
	          4,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf8_stream(
	          utf16_string_greater,
	          7,
	          utf8_stream_great,
	          5,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf8_stream(
	          utf16_string_less,
	          4,
	          utf8_stream_lesser,
	          6,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_compare_with_utf8_stream(
	          NULL,
	          16,
	          una_test_utf16_string_utf8_stream,
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

	result = libuna_utf16_string_compare_with_utf8_stream(
	          una_test_utf16_string_utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          una_test_utf16_string_utf8_stream,
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

	result = libuna_utf16_string_compare_with_utf8_stream(
	          una_test_utf16_string_utf16_string,
	          16,
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

	result = libuna_utf16_string_compare_with_utf8_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          una_test_utf16_string_utf8_stream,
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


	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf16_string_size_from_utf16_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_size_from_utf16_stream(
     void )
{
	libuna_error_t *error    = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_size_from_utf16_stream(
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf16_stream(
	          una_test_utf16_string_utf16_stream,
	          30,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf16_stream(
	          una_test_utf16_string_utf16_stream,
	          0,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_size_from_utf16_stream(
	          NULL,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf16_stream(
	          una_test_utf16_string_utf16_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf16_stream(
	          una_test_utf16_string_utf16_stream,
	          32,
	          -1,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf16_stream(
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
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

/* Tests the libuna_utf16_string_copy_from_utf16_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_copy_from_utf16_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_copy_from_utf16_stream(
	          utf16_string,
	          32,
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf16_string_copy_from_utf16_stream(
	          NULL,
	          32,
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
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

/* Tests the libuna_utf16_string_with_index_copy_from_utf16_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_with_index_copy_from_utf16_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error     = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf16_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf16_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf16_stream,
	          30,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf16_stream(
	          NULL,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf16_stream(
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf16_stream(
	          utf16_string,
	          32,
	          NULL,
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf16_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          NULL,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf16_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf16_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf16_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf16_stream,
	          0,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf16_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf16_stream,
	          32,
	          -1,
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

/* Tests the libuna_utf16_string_compare_with_utf16_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_compare_with_utf16_stream(
     void )
{
	uint8_t utf16_stream_equal[ 10 ]   = { 'e', 0, 'q', 0, 'u', 0, 'a', 0, 'l', 0 };
	uint8_t utf16_stream_great[ 10 ]   = { 'g', 0, 'r', 0, 'e', 0, 'a', 0, 't', 0 };
	uint8_t utf16_stream_less[ 8 ]     = { 'l', 0, 'e', 0, 's', 0, 's', 0 };
	uint8_t utf16_stream_lesser[ 12 ]  = { 'l', 0, 'e', 0, 's', 0, 's', 0, 'e', 0, 'r', 0 };
	uint8_t utf16_stream_more[ 8 ]     = { 'm', 0, 'o', 0, 'r', 0, 'e', 0 };
	uint16_t utf16_string_equal[ 5 ]   = { 'e', 'q', 'u', 'a', 'l' };
	uint16_t utf16_string_greater[ 7 ] = { 'g', 'r', 'e', 'a', 't', 'e', 'r' };
	uint16_t utf16_string_less[ 4 ]    = { 'l', 'e', 's', 's' };
	uint16_t utf16_string_more[ 4 ]    = { 'm', 'o', 'r', 'e' };

	libuna_error_t *error              = NULL;
	int result                         = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_compare_with_utf16_stream(
	          utf16_string_equal,
	          5,
	          utf16_stream_equal,
	          10,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_EQUAL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf16_stream(
	          utf16_string_more,
	          4,
	          utf16_stream_less,
	          8,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf16_stream(
	          utf16_string_less,
	          4,
	          utf16_stream_more,
	          8,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf16_stream(
	          utf16_string_greater,
	          7,
	          utf16_stream_great,
	          10,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf16_stream(
	          utf16_string_less,
	          4,
	          utf16_stream_lesser,
	          12,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_compare_with_utf16_stream(
	          NULL,
	          16,
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_compare_with_utf16_stream(
	          una_test_utf16_string_utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          una_test_utf16_string_utf16_stream,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_compare_with_utf16_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          NULL,
	          32,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_compare_with_utf16_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          una_test_utf16_string_utf16_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_compare_with_utf16_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          una_test_utf16_string_utf16_stream,
	          32,
	          -1,
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

/* Tests the libuna_utf16_string_size_from_utf32 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_size_from_utf32(
     void )
{
	libuna_error_t *error    = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_size_from_utf32(
	          una_test_utf16_string_utf32_string,
	          16,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf32(
	          una_test_utf16_string_utf32_string,
	          15,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf32(
	          una_test_utf16_string_utf32_string,
	          0,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_size_from_utf32(
	          NULL,
	          16,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf32(
	          una_test_utf16_string_utf32_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf32(
	          una_test_utf16_string_utf32_string,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf16_string_copy_from_utf32 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_copy_from_utf32(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_copy_from_utf32(
	          utf16_string,
	          32,
	          una_test_utf16_string_utf32_string,
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
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf16_string_copy_from_utf32(
	          NULL,
	          32,
	          una_test_utf16_string_utf32_string,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf16_string_with_index_copy_from_utf32 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_with_index_copy_from_utf32(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error     = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf32(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_string,
	          16,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf32(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_string,
	          15,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf32(
	          NULL,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_string,
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

	result = libuna_utf16_string_with_index_copy_from_utf32(
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_string,
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

	result = libuna_utf16_string_with_index_copy_from_utf32(
	          utf16_string,
	          32,
	          NULL,
	          una_test_utf16_string_utf32_string,
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

	result = libuna_utf16_string_with_index_copy_from_utf32(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          NULL,
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

	result = libuna_utf16_string_with_index_copy_from_utf32(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_string,
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

	result = libuna_utf16_string_with_index_copy_from_utf32(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_string,
	          0,
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

/* Tests the libuna_utf16_string_compare_with_utf32 function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_compare_with_utf32(
     void )
{
	uint32_t utf32_string_equal[ 5 ]   = { 'e', 'q', 'u', 'a', 'l' };
	uint32_t utf32_string_great[ 5 ]   = { 'g', 'r', 'e', 'a', 't' };
	uint32_t utf32_string_less[ 4 ]    = { 'l', 'e', 's', 's' };
	uint32_t utf32_string_lesser[ 6 ]  = { 'l', 'e', 's', 's', 'e', 'r' };
	uint32_t utf32_string_more[ 4 ]    = { 'm', 'o', 'r', 'e' };
	uint16_t utf16_string_equal[ 5 ]   = { 'e', 'q', 'u', 'a', 'l' };
	uint16_t utf16_string_greater[ 7 ] = { 'g', 'r', 'e', 'a', 't', 'e', 'r' };
	uint16_t utf16_string_less[ 4 ]    = { 'l', 'e', 's', 's' };
	uint16_t utf16_string_more[ 4 ]    = { 'm', 'o', 'r', 'e' };

	libuna_error_t *error              = NULL;
	int result                         = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_compare_with_utf32(
	          utf16_string_equal,
	          5,
	          utf32_string_equal,
	          5,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_EQUAL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf32(
	          utf16_string_more,
	          4,
	          utf32_string_less,
	          4,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf32(
	          utf16_string_less,
	          4,
	          utf32_string_more,
	          4,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf32(
	          utf16_string_greater,
	          7,
	          utf32_string_great,
	          5,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf32(
	          utf16_string_less,
	          4,
	          utf32_string_lesser,
	          6,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_compare_with_utf32(
	          NULL,
	          16,
	          una_test_utf16_string_utf32_string,
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

	result = libuna_utf16_string_compare_with_utf32(
	          una_test_utf16_string_utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          una_test_utf16_string_utf32_string,
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

	result = libuna_utf16_string_compare_with_utf32(
	          una_test_utf16_string_utf16_string,
	          16,
	          NULL,
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

	result = libuna_utf16_string_compare_with_utf32(
	          una_test_utf16_string_utf16_string,
	          16,
	          una_test_utf16_string_utf32_string,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_utf16_string_size_from_utf32_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_size_from_utf32_stream(
     void )
{
	libuna_error_t *error    = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_size_from_utf32_stream(
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf32_stream(
	          una_test_utf16_string_utf32_stream,
	          60,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_utf32_stream(
	          una_test_utf16_string_utf32_stream,
	          0,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_size_from_utf32_stream(
	          NULL,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf32_stream(
	          una_test_utf16_string_utf32_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBUNA_ENDIAN_LITTLE,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf32_stream(
	          una_test_utf16_string_utf32_stream,
	          64,
	          -1,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_utf32_stream(
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
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

/* Tests the libuna_utf16_string_copy_from_utf32_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_copy_from_utf32_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_copy_from_utf32_stream(
	          utf16_string,
	          32,
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf16_string_copy_from_utf32_stream(
	          NULL,
	          32,
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
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

/* Tests the libuna_utf16_string_with_index_copy_from_utf32_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_with_index_copy_from_utf32_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	libuna_error_t *error     = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf32_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf32_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_stream,
	          60,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          una_test_utf16_string_utf16_string,
	          utf16_string,
	          sizeof( uint16_t ) * 16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_utf32_stream(
	          NULL,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf32_stream(
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf32_stream(
	          utf16_string,
	          32,
	          NULL,
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf32_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          NULL,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf32_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf32_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_stream,
	          0,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_with_index_copy_from_utf32_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_utf32_stream,
	          64,
	          -1,
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

/* Tests the libuna_utf16_string_compare_with_utf32_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_compare_with_utf32_stream(
     void )
{
	uint8_t utf32_stream_equal[ 20 ]   = { 'e', 0, 0, 0, 'q', 0, 0, 0, 'u', 0, 0, 0, 'a', 0, 0, 0, 'l', 0, 0, 0 };
	uint8_t utf32_stream_great[ 20 ]   = { 'g', 0, 0, 0, 'r', 0, 0, 0, 'e', 0, 0, 0, 'a', 0, 0, 0, 't', 0, 0, 0 };
	uint8_t utf32_stream_less[ 16 ]    = { 'l', 0, 0, 0, 'e', 0, 0, 0, 's', 0, 0, 0, 's', 0, 0, 0 };
	uint8_t utf32_stream_lesser[ 24 ]  = { 'l', 0, 0, 0, 'e', 0, 0, 0, 's', 0, 0, 0, 's', 0, 0, 0, 'e', 0, 0, 0, 'r', 0, 0, 0 };
	uint8_t utf32_stream_more[ 16 ]    = { 'm', 0, 0, 0, 'o', 0, 0, 0, 'r', 0, 0, 0, 'e', 0, 0, 0 };
	uint16_t utf16_string_equal[ 5 ]   = { 'e', 'q', 'u', 'a', 'l' };
	uint16_t utf16_string_greater[ 7 ] = { 'g', 'r', 'e', 'a', 't', 'e', 'r' };
	uint16_t utf16_string_less[ 4 ]    = { 'l', 'e', 's', 's' };
	uint16_t utf16_string_more[ 4 ]    = { 'm', 'o', 'r', 'e' };

	libuna_error_t *error              = NULL;
	int result                         = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_compare_with_utf32_stream(
	          utf16_string_equal,
	          5,
	          utf32_stream_equal,
	          20,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_EQUAL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf32_stream(
	          utf16_string_more,
	          4,
	          utf32_stream_less,
	          16,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf32_stream(
	          utf16_string_less,
	          4,
	          utf32_stream_more,
	          16,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf32_stream(
	          utf16_string_greater,
	          7,
	          utf32_stream_great,
	          20,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_GREATER );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_compare_with_utf32_stream(
	          utf16_string_less,
	          4,
	          utf32_stream_lesser,
	          24,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_LESS );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_compare_with_utf32_stream(
	          NULL,
	          16,
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_compare_with_utf32_stream(
	          una_test_utf16_string_utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          una_test_utf16_string_utf32_stream,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_compare_with_utf32_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          NULL,
	          64,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_compare_with_utf32_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          una_test_utf16_string_utf32_stream,
	          (size_t) SSIZE_MAX + 1,
	          LIBUNA_ENDIAN_LITTLE,
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

	result = libuna_utf16_string_compare_with_utf32_stream(
	          una_test_utf16_string_utf16_string,
	          16,
	          una_test_utf16_string_utf32_stream,
	          64,
	          -1,
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

/* Tests the libuna_utf16_string_size_from_scsu_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_size_from_scsu_stream(
     void )
{
	libuna_error_t *error    = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_size_from_scsu_stream(
	          una_test_utf16_string_scsu_stream1,
	          9,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 10 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_scsu_stream(
	          una_test_utf16_string_scsu_stream2,
	          7,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 7 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_scsu_stream(
	          una_test_utf16_string_scsu_stream3,
	          178,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 117 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libuna_utf16_string_size_from_scsu_stream(
	          una_test_utf16_string_scsu_stream4,
	          35,
	          &utf16_string_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 21 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_utf16_string_size_from_scsu_stream(
	          NULL,
	          64,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_scsu_stream(
	          una_test_utf16_string_scsu_stream1,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_size,
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

	result = libuna_utf16_string_size_from_scsu_stream(
	          una_test_utf16_string_scsu_stream1,
	          64,
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

/* Tests the libuna_utf16_string_copy_from_scsu_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_copy_from_scsu_stream(
     void )
{
	uint16_t utf16_string[ 32 ];

	uint16_t expected_utf16_string1[ 10 ] = {
		0x00d6, 0x006c, 0x0020, 0x0066, 0x006c, 0x0069, 0x0065, 0x00df, 0x0074, 0 };

	libuna_error_t *error = NULL;
	int result            = 0;

	/* Test regular cases
	 */
	result = libuna_utf16_string_copy_from_scsu_stream(
	          utf16_string,
	          32,
	          una_test_utf16_string_scsu_stream1,
	          9,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf16_string1,
	          utf16_string,
	          sizeof( uint16_t ) * 10 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_utf16_string_copy_from_scsu_stream(
	          NULL,
	          32,
	          una_test_utf16_string_scsu_stream1,
	          9,
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

/* Tests the libuna_utf16_string_with_index_copy_from_scsu_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_utf16_string_with_index_copy_from_scsu_stream(
     void )
{
	uint16_t utf16_string[ 256 ];

	uint16_t expected_utf16_string1[ 10 ] = {
		0x00d6, 0x006c, 0x0020, 0x0066, 0x006c, 0x0069, 0x0065, 0x00df, 0x0074, 0 };
	uint16_t expected_utf16_string2[ 7 ] = {
		0x041c, 0x043e, 0x0441, 0x043a, 0x0432, 0x0430, 0 };
	uint16_t expected_utf16_string3[ 117 ] = {
		0x3000, 0x266a, 0x30ea, 0x30f3, 0x30b4, 0x53ef, 0x611b, 0x3044, 0x3084, 0x53ef, 0x611b, 0x3044,
		0x3084, 0x30ea, 0x30f3, 0x30b4, 0x3002, 0x534a, 0x4e16, 0x7d00, 0x3082, 0x524d, 0x306b, 0x6d41,
		0x884c, 0x3057, 0x305f, 0x300c, 0x30ea, 0x30f3, 0x30b4, 0x306e, 0x6b4c, 0x300d, 0x304c, 0x3074,
		0x3063, 0x305f, 0x308a, 0x3059, 0x308b, 0x304b, 0x3082, 0x3057, 0x308c, 0x306a, 0x3044, 0x3002,
		0x7c73, 0x30a2, 0x30c3, 0x30d7, 0x30eb, 0x30b3, 0x30f3, 0x30d4, 0x30e5, 0x30fc, 0x30bf, 0x793e,
		0x306e, 0x30d1, 0x30bd, 0x30b3, 0x30f3, 0x300c, 0x30de, 0x30c3, 0x30af, 0xff08, 0x30de, 0x30c3,
		0x30ad, 0x30f3, 0x30c8, 0x30c3, 0x30b7, 0x30e5, 0xff09, 0x300d, 0x3092, 0x3001, 0x3053, 0x3088,
		0x306a, 0x304f, 0x611b, 0x3059, 0x308b, 0x4eba, 0x305f, 0x3061, 0x306e, 0x3053, 0x3068, 0x3060,
		0x3002, 0x300c, 0x30a2, 0x30c3, 0x30d7, 0x30eb, 0x4fe1, 0x8005, 0x300d, 0x306a, 0x3093, 0x3066,
		0x8a00, 0x3044, 0x65b9, 0x307e, 0x3067, 0x3042, 0x308b, 0x3002 };
	uint16_t expected_utf16_string4[ 21 ] = {
		0x0041, 0x00df, 0x0401, 0x015f, 0x00df, 0x01df, 0xf000, 0xdbff, 0xdfff, 0x000d, 0x000a, 0x0041,
		0x00df, 0x0401, 0x015f, 0x00df, 0x01df, 0xf000, 0xdbff, 0xdfff, 0 };

	libuna_error_t *error     = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_scsu_stream1,
	          9,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 10 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf16_string1,
	          utf16_string,
	          sizeof( uint16_t ) * 10 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_scsu_stream2,
	          7,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 7 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf16_string2,
	          utf16_string,
	          sizeof( uint16_t ) * 7 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          utf16_string,
	          256,
	          &utf16_string_index,
	          una_test_utf16_string_scsu_stream3,
	          178,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 117 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf16_string3,
	          utf16_string,
	          sizeof( uint16_t ) * 117 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_scsu_stream4,
	          35,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 21 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf16_string4,
	          utf16_string,
	          sizeof( uint16_t ) * 21 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          NULL,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_scsu_stream1,
	          9,
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

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          una_test_utf16_string_scsu_stream1,
	          9,
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

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          utf16_string,
	          32,
	          NULL,
	          una_test_utf16_string_scsu_stream1,
	          9,
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

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          NULL,
	          9,
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

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_scsu_stream1,
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

	result = libuna_utf16_string_with_index_copy_from_scsu_stream(
	          utf16_string,
	          32,
	          &utf16_string_index,
	          una_test_utf16_string_scsu_stream1,
	          0,
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
	 "libuna_utf16_string_size_from_byte_stream",
	 una_test_utf16_string_size_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_copy_from_byte_stream",
	 una_test_utf16_string_copy_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_with_index_copy_from_byte_stream",
	 una_test_utf16_string_with_index_copy_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_compare_with_byte_stream",
	 una_test_utf16_string_compare_with_byte_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_size_from_utf7_stream",
	 una_test_utf16_string_size_from_utf7_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_copy_from_utf7_stream",
	 una_test_utf16_string_copy_from_utf7_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_with_index_copy_from_utf7_stream",
	 una_test_utf16_string_with_index_copy_from_utf7_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_compare_with_utf7_stream",
	 una_test_utf16_string_compare_with_utf7_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_size_from_utf8",
	 una_test_utf16_string_size_from_utf8 );

	UNA_TEST_RUN(
	 "libuna_utf16_string_copy_from_utf8",
	 una_test_utf16_string_copy_from_utf8 );

	UNA_TEST_RUN(
	 "libuna_utf16_string_with_index_copy_from_utf8",
	 una_test_utf16_string_with_index_copy_from_utf8 );

	UNA_TEST_RUN(
	 "libuna_utf16_string_size_from_utf8_stream",
	 una_test_utf16_string_size_from_utf8_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_copy_from_utf8_stream",
	 una_test_utf16_string_copy_from_utf8_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_with_index_copy_from_utf8_stream",
	 una_test_utf16_string_with_index_copy_from_utf8_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_compare_with_utf8_stream",
	 una_test_utf16_string_compare_with_utf8_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_size_from_utf16_stream",
	 una_test_utf16_string_size_from_utf16_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_copy_from_utf16_stream",
	 una_test_utf16_string_copy_from_utf16_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_with_index_copy_from_utf16_stream",
	 una_test_utf16_string_with_index_copy_from_utf16_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_compare_with_utf16_stream",
	 una_test_utf16_string_compare_with_utf16_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_size_from_utf32",
	 una_test_utf16_string_size_from_utf32 );

	UNA_TEST_RUN(
	 "libuna_utf16_string_copy_from_utf32",
	 una_test_utf16_string_copy_from_utf32 );

	UNA_TEST_RUN(
	 "libuna_utf16_string_with_index_copy_from_utf32",
	 una_test_utf16_string_with_index_copy_from_utf32 );

	UNA_TEST_RUN(
	 "libuna_utf16_string_compare_with_utf32",
	 una_test_utf16_string_compare_with_utf32 );

	UNA_TEST_RUN(
	 "libuna_utf16_string_size_from_utf32_stream",
	 una_test_utf16_string_size_from_utf32_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_copy_from_utf32_stream",
	 una_test_utf16_string_copy_from_utf32_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_with_index_copy_from_utf32_stream",
	 una_test_utf16_string_with_index_copy_from_utf32_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_compare_with_utf32_stream",
	 una_test_utf16_string_compare_with_utf32_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_size_from_scsu_stream",
	 una_test_utf16_string_size_from_scsu_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_copy_from_scsu_stream",
	 una_test_utf16_string_copy_from_scsu_stream );

	UNA_TEST_RUN(
	 "libuna_utf16_string_with_index_copy_from_scsu_stream",
	 una_test_utf16_string_with_index_copy_from_scsu_stream );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

