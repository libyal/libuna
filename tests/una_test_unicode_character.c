/*
 * Library unicode_character functions test program
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

#include "una_test_codepage_ascii.h"
#include "una_test_codepage_iso_8859_1.h"
#include "una_test_codepage_iso_8859_2.h"
#include "una_test_codepage_iso_8859_3.h"
#include "una_test_codepage_iso_8859_4.h"
#include "una_test_codepage_iso_8859_5.h"
#include "una_test_codepage_iso_8859_6.h"
#include "una_test_codepage_iso_8859_7.h"
#include "una_test_codepage_iso_8859_8.h"
#include "una_test_codepage_iso_8859_9.h"
#include "una_test_codepage_iso_8859_10.h"
#include "una_test_codepage_iso_8859_11.h"
#include "una_test_codepage_iso_8859_13.h"
#include "una_test_codepage_iso_8859_14.h"
#include "una_test_codepage_iso_8859_15.h"
#include "una_test_codepage_iso_8859_16.h"
#include "una_test_codepage_koi8_r.h"
#include "una_test_codepage_koi8_u.h"
#include "una_test_codepage_windows_874.h"
#include "una_test_codepage_windows_932.h"
#include "una_test_codepage_windows_936.h"
#include "una_test_codepage_windows_949.h"
#include "una_test_codepage_windows_950.h"
#include "una_test_codepage_windows_1250.h"
#include "una_test_codepage_windows_1251.h"
#include "una_test_codepage_windows_1252.h"
#include "una_test_codepage_windows_1253.h"
#include "una_test_codepage_windows_1254.h"
#include "una_test_codepage_windows_1255.h"
#include "una_test_codepage_windows_1256.h"
#include "una_test_codepage_windows_1257.h"
#include "una_test_codepage_windows_1258.h"
#include "una_test_libcerror.h"
#include "una_test_libuna.h"
#include "una_test_macros.h"
#include "una_test_types.h"
#include "una_test_unused.h"

#include "../libuna/libuna_unicode_character.h"

typedef struct una_test_unicode_character_codepage una_test_unicode_character_codepage_t;

struct una_test_unicode_character_codepage
{
	/* Codepage
	 */
	int codepage;

	/* Number of test values
	 */
	int number_of_test_values;

	/* Codepage test values
	 */
	una_test_byte_stream_to_unicode_t *test_values;
};

una_test_unicode_character_codepage_t una_test_unicode_character_codepages[ 32 ] = {
	{ LIBUNA_CODEPAGE_ASCII, 128, una_test_codepage_ascii_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_1, 256, una_test_codepage_iso_8859_1_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_2, 256, una_test_codepage_iso_8859_2_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_3, 249, una_test_codepage_iso_8859_3_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_4, 256, una_test_codepage_iso_8859_4_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_5, 256, una_test_codepage_iso_8859_5_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_6, 211, una_test_codepage_iso_8859_6_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_7, 253, una_test_codepage_iso_8859_7_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_8, 220, una_test_codepage_iso_8859_8_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_9, 256, una_test_codepage_iso_8859_9_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_10, 256, una_test_codepage_iso_8859_10_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_11, 248, una_test_codepage_iso_8859_11_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_13, 256, una_test_codepage_iso_8859_13_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_14, 256, una_test_codepage_iso_8859_14_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_15, 256, una_test_codepage_iso_8859_15_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_ISO_8859_16, 256, una_test_codepage_iso_8859_16_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_KOI8_R, 256, una_test_codepage_koi8_r_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_KOI8_U, 256, una_test_codepage_koi8_u_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_874, 225, una_test_codepage_windows_874_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_932, 7915, una_test_codepage_windows_932_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_936, 21920, una_test_codepage_windows_936_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_949, 17176, una_test_codepage_windows_949_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_950, 13631, una_test_codepage_windows_950_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_1250, 251, una_test_codepage_windows_1250_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_1251, 255, una_test_codepage_windows_1251_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_1252, 251, una_test_codepage_windows_1252_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_1253, 239, una_test_codepage_windows_1253_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_1254, 249, una_test_codepage_windows_1254_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_1255, 233, una_test_codepage_windows_1255_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_1256, 256, una_test_codepage_windows_1256_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_1257, 244, una_test_codepage_windows_1257_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_WINDOWS_1258, 247, una_test_codepage_windows_1258_byte_stream_to_unicode },
};

/* Tests the libuna_unicode_character_size_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_size_to_byte_stream(
     void )
{
	libuna_error_t *error                                = NULL;
	una_test_byte_stream_to_unicode_t *test_values       = NULL;
	una_test_unicode_character_codepage_t *test_codepage = NULL;
	size_t byte_stream_character_size                    = 0;
	int codepage_number                                  = 0;
	int result                                           = 0;
	int test_number                                      = 0;

	/* Test regular cases
	 */
	for( codepage_number = 0;
	     codepage_number < 32;
	     codepage_number++ )
	{
		test_codepage = &( una_test_unicode_character_codepages[ codepage_number ] );

		for( test_number = 0;
		     test_number < test_codepage->number_of_test_values;
		     test_number++ )
		{
			test_values = &( test_codepage->test_values[ test_number ] );

			byte_stream_character_size = 0;

			result = libuna_unicode_character_size_to_byte_stream(
				  test_values->unicode_character,
				  test_codepage->codepage,
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
	}
	/* Test error cases
	 */
	result = libuna_unicode_character_size_to_byte_stream(
	          0x00000041UL,
	          -1,
	          &byte_stream_character_size,
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

	result = libuna_unicode_character_size_to_byte_stream(
	          0x00000041UL,
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

/* Tests the libuna_unicode_character_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_from_byte_stream(
     void )
{
	libuna_error_t *error                                = NULL;
	una_test_byte_stream_to_unicode_t *test_values       = NULL;
	una_test_unicode_character_codepage_t *test_codepage = NULL;
	libuna_unicode_character_t unicode_character         = 0;
	size_t byte_stream_index                             = 0;
	int codepage_number                                  = 0;
	int result                                           = 0;
	int test_number                                      = 0;

	/* Test regular cases
	 */
	for( codepage_number = 0;
	     codepage_number < 32;
	     codepage_number++ )
	{
		test_codepage = &( una_test_unicode_character_codepages[ codepage_number ] );

		for( test_number = 0;
		     test_number < test_codepage->number_of_test_values;
		     test_number++ )
		{
			test_values = &( test_codepage->test_values[ test_number ] );

			byte_stream_index = 0;

			result = libuna_unicode_character_copy_from_byte_stream(
				  &unicode_character,
			          test_values->byte_stream,
			          test_values->byte_stream_size,
			          &byte_stream_index,
				  test_codepage->codepage,
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
	}
	/* Test error cases
	 */
	byte_stream_index = 0;

	result = libuna_unicode_character_copy_from_byte_stream(
	          NULL,
	          (uint8_t *) "A",
	          1,
	          &byte_stream_index,
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

	result = libuna_unicode_character_copy_from_byte_stream(
	          &unicode_character,
	          NULL,
	          1,
	          &byte_stream_index,
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

	result = libuna_unicode_character_copy_from_byte_stream(
	          &unicode_character,
	          (uint8_t *) "A",
	          (size_t) SSIZE_MAX + 1,
	          &byte_stream_index,
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

	result = libuna_unicode_character_copy_from_byte_stream(
	          &unicode_character,
	          (uint8_t *) "A",
	          1,
	          NULL,
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

	result = libuna_unicode_character_copy_from_byte_stream(
	          &unicode_character,
	          (uint8_t *) "A",
	          1,
	          &byte_stream_index,
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

/* Tests the libuna_unicode_character_copy_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_to_byte_stream(
     void )
{
	uint8_t byte_stream[ 16 ];

	libuna_error_t *error                                = NULL;
	una_test_byte_stream_to_unicode_t *test_values       = NULL;
	una_test_unicode_character_codepage_t *test_codepage = NULL;
	size_t byte_stream_index                             = 0;
	int codepage_number                                  = 0;
	int result                                           = 0;
	int test_number                                      = 0;

	/* Test regular cases
	 */
	for( codepage_number = 0;
	     codepage_number < 32;
	     codepage_number++ )
	{
		test_codepage = &( una_test_unicode_character_codepages[ codepage_number ] );

		for( test_number = 0;
		     test_number < test_codepage->number_of_test_values;
		     test_number++ )
		{
			test_values = &( test_codepage->test_values[ test_number ] );

			if( test_values->is_duplicate != 0 )
			{
				continue;
			}
			byte_stream_index = 0;

			result = libuna_unicode_character_copy_to_byte_stream(
			          test_values->unicode_character,
			          byte_stream,
			          16,
			          &byte_stream_index,
			          test_codepage->codepage,
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
	}
	/* Test error cases
	 */
	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
	          0x00000041UL,
	          NULL,
	          16,
	          &byte_stream_index,
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

	result = libuna_unicode_character_copy_to_byte_stream(
	          0x00000041UL,
	          byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          &byte_stream_index,
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

	result = libuna_unicode_character_copy_to_byte_stream(
	          0x00000041UL,
	          byte_stream,
	          16,
	          NULL,
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

	result = libuna_unicode_character_copy_to_byte_stream(
	          0x00000041UL,
	          byte_stream,
	          16,
	          &byte_stream_index,
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
	 "libuna_unicode_character_size_to_byte_stream",
	 una_test_unicode_character_size_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_from_byte_stream",
	 una_test_unicode_character_copy_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_to_byte_stream",
	 una_test_unicode_character_copy_to_byte_stream );

	/* TODO libuna_unicode_character_size_to_utf7_stream */
	/* TODO libuna_unicode_character_copy_from_utf7_stream */
	/* TODO libuna_unicode_character_copy_to_utf7_stream */

	/* TODO libuna_unicode_character_size_to_utf8 */
	/* TODO libuna_unicode_character_copy_from_utf8 */
	/* TODO libuna_unicode_character_copy_to_utf8 */

	/* TODO libuna_unicode_character_size_to_utf16 */
	/* TODO libuna_unicode_character_copy_from_utf16 */
	/* TODO libuna_unicode_character_copy_to_utf16 */

	/* TODO libuna_unicode_character_size_to_utf16_stream */
	/* TODO libuna_unicode_character_copy_from_utf16_stream */
	/* TODO libuna_unicode_character_copy_to_utf16_stream */

	/* TODO libuna_unicode_character_size_to_utf32 */
	/* TODO libuna_unicode_character_copy_from_utf32 */
	/* TODO libuna_unicode_character_copy_to_utf32 */

	/* TODO libuna_unicode_character_size_to_utf32_stream */
	/* TODO libuna_unicode_character_copy_from_utf32_stream */
	/* TODO libuna_unicode_character_copy_to_utf32_stream */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

