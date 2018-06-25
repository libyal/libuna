/*
 * Library codepage_windows_949 functions test program
 *
 * Copyright (C) 2008-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "una_test_codepage_windows_949.h"
#include "una_test_libcerror.h"
#include "una_test_libuna.h"
#include "una_test_macros.h"
#include "una_test_types.h"
#include "una_test_unused.h"

#include "../libuna/libuna_codepage_windows_949.h"

una_test_byte_stream_to_unicode_t una_test_codepage_windows_949_replacement_byte_stream_to_unicode[ 17 ] = {
	{ { 0xa1, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xa2, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xa4, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xa5, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xa6, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xa7, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xa9, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xab, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xac, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xad, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xae, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xaf, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xc5, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xc6, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xc8, 0x3f }, 2, 0xfffd, 0 },
	{ { 0xfd, 0x9f }, 2, 0xfffd, 0 },
	{ { 0xfe, 0x00 }, 2, 0xfffd, 0 },
};

/* Tests the libuna_codepage_windows_949_unicode_character_size_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_codepage_windows_949_unicode_character_size_to_byte_stream(
     void )
{
	libuna_error_t *error                          = NULL;
	una_test_byte_stream_to_unicode_t *test_values = NULL;
	size_t byte_stream_character_size              = 0;
	int result                                     = 0;
	int test_number                                = 0;

	/* Test regular cases
	 */
	for( test_number = 0;
	     test_number < 17176;
	     test_number++ )
	{
		test_values = &( una_test_codepage_windows_949_byte_stream_to_unicode[ test_number ] );

		byte_stream_character_size = 0;

		result = libuna_codepage_windows_949_unicode_character_size_to_byte_stream(
		          test_values->unicode_character,
		          &byte_stream_character_size,
		          &error );

		UNA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		UNA_TEST_ASSERT_EQUAL_SIZE(
		 "byte_stream_character_size",
		 byte_stream_character_size,
		 test_values->byte_stream_size );

		UNA_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libuna_codepage_windows_949_unicode_character_size_to_byte_stream(
	          0x00000041UL,
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

/* Tests the libuna_codepage_windows_949_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_codepage_windows_949_copy_from_byte_stream(
     void )
{
	libuna_error_t *error                          = NULL;
	una_test_byte_stream_to_unicode_t *test_values = NULL;
	libuna_unicode_character_t unicode_character   = 0;
	size_t byte_stream_index                       = 0;
	int result                                     = 0;
	int test_number                                = 0;

	/* Test regular cases
	 */
	for( test_number = 0;
	     test_number < 17176;
	     test_number++ )
	{
		test_values = &( una_test_codepage_windows_949_byte_stream_to_unicode[ test_number ] );

		byte_stream_index = 0;

		result = libuna_codepage_windows_949_copy_from_byte_stream(
		          &unicode_character,
		          test_values->byte_stream,
		          test_values->byte_stream_size,
		          &byte_stream_index,
		          &error );

		UNA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		UNA_TEST_ASSERT_EQUAL_UINT32(
		 "unicode_character",
		 unicode_character,
		 test_values->unicode_character );

		UNA_TEST_ASSERT_EQUAL_SIZE(
		 "byte_stream_index",
		 byte_stream_index,
		 test_values->byte_stream_size );

		UNA_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	for( test_number = 0;
	     test_number < 17;
	     test_number++ )
	{
		test_values = &( una_test_codepage_windows_949_replacement_byte_stream_to_unicode[ test_number ] );

		byte_stream_index = 0;

		result = libuna_codepage_windows_949_copy_from_byte_stream(
		          &unicode_character,
		          test_values->byte_stream,
		          test_values->byte_stream_size,
		          &byte_stream_index,
		          &error );

		UNA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		UNA_TEST_ASSERT_EQUAL_UINT32(
		 "unicode_character",
		 unicode_character,
		 test_values->unicode_character );

		UNA_TEST_ASSERT_EQUAL_SIZE(
		 "byte_stream_index",
		 byte_stream_index,
		 test_values->byte_stream_size );

		UNA_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
/* TODO add test for replacements */

	/* Test error cases
	 */
	byte_stream_index = 0;

	result = libuna_codepage_windows_949_copy_from_byte_stream(
	          NULL,
	          (uint8_t *) "A",
	          1,
	          &byte_stream_index,
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

	result = libuna_codepage_windows_949_copy_from_byte_stream(
	          &unicode_character,
	          NULL,
	          1,
	          &byte_stream_index,
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

	result = libuna_codepage_windows_949_copy_from_byte_stream(
	          &unicode_character,
	          (uint8_t *) "A",
	          (size_t) SSIZE_MAX + 1,
	          &byte_stream_index,
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

	result = libuna_codepage_windows_949_copy_from_byte_stream(
	          &unicode_character,
	          (uint8_t *) "A",
	          1,
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

	byte_stream_index = 1;

	result = libuna_codepage_windows_949_copy_from_byte_stream(
	          &unicode_character,
	          (uint8_t *) "A",
	          1,
	          &byte_stream_index,
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

/* Tests the libuna_codepage_windows_949_copy_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_codepage_windows_949_copy_to_byte_stream(
     void )
{
	uint8_t byte_stream[ 16 ];

	libuna_error_t *error                          = NULL;
	una_test_byte_stream_to_unicode_t *test_values = NULL;
	size_t byte_stream_index                       = 0;
	int result                                     = 0;
	int test_number                                = 0;

	/* Test regular cases
	 */
	for( test_number = 0;
	     test_number < 17176;
	     test_number++ )
	{
		test_values = &( una_test_codepage_windows_949_byte_stream_to_unicode[ test_number ] );

		if( test_values->is_duplicate != 0 )
		{
			continue;
		}
		byte_stream_index = 0;

		result = libuna_codepage_windows_949_copy_to_byte_stream(
		          test_values->unicode_character,
		          byte_stream,
		          16,
		          &byte_stream_index,
		          &error );

		UNA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		UNA_TEST_ASSERT_EQUAL_SIZE(
		 "byte_stream_index",
		 byte_stream_index,
		 test_values->byte_stream_size );

		UNA_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = memory_compare(
		          test_values->byte_stream,
		          byte_stream,
		          test_values->byte_stream_size );

		UNA_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );
	}
	/* Test error cases
	 */
	byte_stream_index = 0;

	result = libuna_codepage_windows_949_copy_to_byte_stream(
	          0x00000041UL,
	          NULL,
	          16,
	          &byte_stream_index,
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

	result = libuna_codepage_windows_949_copy_to_byte_stream(
	          0x00000041UL,
	          byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          &byte_stream_index,
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

	result = libuna_codepage_windows_949_copy_to_byte_stream(
	          0x00000041UL,
	          byte_stream,
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

	byte_stream_index = 16;

	result = libuna_codepage_windows_949_copy_to_byte_stream(
	          0x00000041UL,
	          byte_stream,
	          16,
	          &byte_stream_index,
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
	 "libuna_codepage_windows_949_unicode_character_size_to_byte_stream",
	 una_test_codepage_windows_949_unicode_character_size_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_codepage_windows_949_copy_from_byte_stream",
	 una_test_codepage_windows_949_copy_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_codepage_windows_949_copy_to_byte_stream",
	 una_test_codepage_windows_949_copy_to_byte_stream );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

