/*
 * Unicode and ASCII (byte stream) conversion library base16 stream copy from testing program
 *
 * Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
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

#include "una_test_libcerror.h"
#include "una_test_libcstring.h"
#include "una_test_libuna.h"
#include "una_test_macros.h"
#include "una_test_unused.h"

uint8_t una_test_base16_stream_byte_stream[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.' };

uint8_t una_test_base16_stream_lower_case_base16_stream[ 32 ] = {
	'5', '4', '6', '8', '6', '9', '7', '3', '2', '0', '6', '9', '7', '3', '2', '0',
        'c', '3', 'a', '1', '2', '0', '7', '4', '6', '5', '7', '3', '7', '4', '2', 'e' };

uint8_t una_test_base16_stream_upper_case_base16_stream[ 32 ] = {
	'5', '4', '6', '8', '6', '9', '7', '3', '2', '0', '6', '9', '7', '3', '2', '0',
        'C', '3', 'A', '1', '2', '0', '7', '4', '6', '5', '7', '3', '7', '4', '2', 'E' };

uint8_t una_test_base16_stream_utf16le_lower_case_base16_stream[ 64 ] = {
	'5', 0, '4', 0, '6', 0, '8', 0, '6', 0, '9', 0, '7', 0, '3', 0,
        '2', 0, '0', 0, '6', 0, '9', 0, '7', 0, '3', 0, '2', 0, '0', 0,
        'c', 0, '3', 0, 'a', 0, '1', 0, '2', 0, '0', 0, '7', 0, '4', 0,
        '6', 0, '5', 0, '7', 0, '3', 0, '7', 0, '4', 0, '2', 0, 'e', 0 };

uint8_t una_test_base16_stream_utf32be_upper_case_base16_stream[ 128 ] = {
	0, 0, 0, '5', 0, 0, 0, '4', 0, 0, 0, '6', 0, 0, 0, '8', 0, 0, 0, '6', 0, 0, 0, '9', 0, 0, 0, '7', 0, 0, 0, '3',
        0, 0, 0, '2', 0, 0, 0, '0', 0, 0, 0, '6', 0, 0, 0, '9', 0, 0, 0, '7', 0, 0, 0, '3', 0, 0, 0, '2', 0, 0, 0, '0',
        0, 0, 0, 'C', 0, 0, 0, '3', 0, 0, 0, 'A', 0, 0, 0, '1', 0, 0, 0, '2', 0, 0, 0, '0', 0, 0, 0, '7', 0, 0, 0, '4',
        0, 0, 0, '6', 0, 0, 0, '5', 0, 0, 0, '7', 0, 0, 0, '3', 0, 0, 0, '7', 0, 0, 0, '4', 0, 0, 0, '2', 0, 0, 0, 'E' };

uint8_t *una_test_base16_stream_byte_stream_long = \
	(uint8_t *) "The test of success is not what you do when you are on top. Success is how high you bounce when you hit bottom.\n";

uint8_t *una_test_base16_stream_lower_case_base16_stream_long = \
	(uint8_t *) "5468652074657374206f662073756363657373206973206e6f74207768617420\n"
                    "796f7520646f207768656e20796f7520617265206f6e20746f702e2053756363\n"
	            "65737320697320686f77206869676820796f7520626f756e6365207768656e20\n"
                    "796f752068697420626f74746f6d2e0a\n";

uint8_t *una_test_base16_stream_lower_case_base16_stream_long_with_whitespace = \
	(uint8_t *) "\t5468652074657374206f662073756363657373206973206e6f74207768617420\t\n"
                    "  796f7520646f207768656e20796f7520617265206f6e20746f702e2053756363  \n"
	            "\t65737320697320686f77206869676820796f7520626f756e6365207768656e20  \n"
                    "\t796f752068697420626f74746f6d2e0a                                  \n";

/* Tests the libuna_base16_stream_size_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base16_stream_size_to_byte_stream(
     void )
{
	libcerror_error_t *error = NULL;
	size_t byte_stream_size  = 0;
	int result               = 0;

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
	          32,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 16 );

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_upper_case_base16_stream,
	          32,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 16 );

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf16le_lower_case_base16_stream,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 16 );

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf32be_upper_case_base16_stream,
	          128,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 16 );

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream_long,
	          228,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 112 );

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream_long_with_whitespace,
	          272,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
	          LIBUNA_BASE16_FLAG_STRIP_WHITESPACE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 112 );

	/* Test error cases
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          NULL,
		  32,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  (size_t) SSIZE_MAX + 1,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  32,
	          NULL,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  32,
		  &byte_stream_size,
	          0xffffffffUL,
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

	/* Incorrect case
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_upper_case_base16_stream,
	          32,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Incorrect byte order
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf16le_lower_case_base16_stream,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF16_BIG_ENDIAN,
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

	/* Incorrect byte order
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf32be_upper_case_base16_stream,
	          128,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN,
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

	/* Incorrect character limit
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream_long,
	          228,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_76,
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

	/* Missing whitespace flag
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream_long_with_whitespace,
	          272,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
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
	return( 0 );
}

/* Tests the libuna_base16_stream_copy_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base16_stream_copy_to_byte_stream(
     void )
{
	uint8_t byte_stream[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
	          32,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          byte_stream,
	          una_test_base16_stream_byte_stream,
	          16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_upper_case_base16_stream,
	          32,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          byte_stream,
	          una_test_base16_stream_byte_stream,
	          16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_utf16le_lower_case_base16_stream,
	          64,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          byte_stream,
	          una_test_base16_stream_byte_stream,
	          16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_utf32be_upper_case_base16_stream,
	          128,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          byte_stream,
	          una_test_base16_stream_byte_stream,
	          16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream_long,
	          228,
		  byte_stream,
		  112,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          byte_stream,
	          una_test_base16_stream_byte_stream_long,
	          112 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream_long_with_whitespace,
	          272,
		  byte_stream,
		  112,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
	          LIBUNA_BASE16_FLAG_STRIP_WHITESPACE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          byte_stream,
	          una_test_base16_stream_byte_stream_long,
	          112 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          NULL,
		  32,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  (size_t) SSIZE_MAX + 1,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  32,
	          NULL,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  32,
		  byte_stream,
		  (size_t) SSIZE_MAX + 1,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  32,
		  byte_stream,
		  16,
	          0xffffffffUL,
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

	/* Byte stream too small
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
	          32,
		  byte_stream,
		  8,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Incorrect case
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_upper_case_base16_stream,
	          32,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Incorrect byte order
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_utf16le_lower_case_base16_stream,
	          64,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF16_BIG_ENDIAN,
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

	/* Incorrect byte order
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_utf32be_upper_case_base16_stream,
	          128,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN,
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

	/* Incorrect character limit
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream_long,
	          228,
		  byte_stream,
		  112,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_76,
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

	/* Missing whitespace flag
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream_long_with_whitespace,
	          272,
		  byte_stream,
		  112,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
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
	return( 0 );
}

/* Tests the libuna_base16_stream_size_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base16_stream_size_from_byte_stream(
     void )
{
	libcerror_error_t *error  = NULL;
	size_t base16_stream_size = 0;
	int result                = 0;

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 32 );

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 32 );

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 64 );

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 128 );

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream_long,
		  112,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 228 );

	/* Test error cases
	 */
	result = libuna_base16_stream_size_from_byte_stream(
		  NULL,
		  16,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  (size_t) SSIZE_MAX + 1,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  NULL,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          0xffffffffUL,
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
	return( 0 );
}

/* Tests the libuna_base16_stream_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base16_stream_copy_from_byte_stream(
     void )
{
	uint8_t base16_stream[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libuna_base16_stream_copy_from_byte_stream(
		  base16_stream,
		  32,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          base16_stream,
	          una_test_base16_stream_lower_case_base16_stream,
	          32 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base16_stream_copy_from_byte_stream(
		  base16_stream,
		  32,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          base16_stream,
	          una_test_base16_stream_upper_case_base16_stream,
	          32 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base16_stream_copy_from_byte_stream(
		  base16_stream,
		  64,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          base16_stream,
	          una_test_base16_stream_utf16le_lower_case_base16_stream,
	          64 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base16_stream_copy_from_byte_stream(
		  base16_stream,
		  128,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          base16_stream,
	          una_test_base16_stream_utf32be_upper_case_base16_stream,
	          128 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base16_stream_copy_from_byte_stream(
		  base16_stream,
		  228,
		  una_test_base16_stream_byte_stream_long,
		  112,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          base16_stream,
	          una_test_base16_stream_lower_case_base16_stream_long,
	          228 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_base16_stream_copy_from_byte_stream(
	          NULL,
		  32,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_copy_from_byte_stream(
	          base16_stream,
		  (size_t) SSIZE_MAX + 1,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_copy_from_byte_stream(
	          base16_stream,
		  32,
		  NULL,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_copy_from_byte_stream(
	          base16_stream,
		  32,
		  una_test_base16_stream_byte_stream,
		  (size_t) SSIZE_MAX + 1,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	result = libuna_base16_stream_copy_from_byte_stream(
	          base16_stream,
		  32,
		  una_test_base16_stream_byte_stream,
		  16,
	          0xffffffffUL,
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

	/* Base16 stream too small
	 */
	result = libuna_base16_stream_copy_from_byte_stream(
	          base16_stream,
		  8,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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
	return( 0 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
	 "libuna_base16_stream_size_to_byte_stream",
	 una_test_base16_stream_size_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base16_stream_copy_to_byte_stream",
	 una_test_base16_stream_copy_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base16_stream_size_from_byte_stream",
	 una_test_base16_stream_size_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base16_stream_copy_from_byte_stream",
	 una_test_base16_stream_copy_from_byte_stream );

	/* TODO add tests for libuna_base16_stream_with_index_copy_from_byte_stream */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

