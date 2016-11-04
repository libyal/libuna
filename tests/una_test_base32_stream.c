/*
 * Library base32 stream functions test program
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

uint8_t una_test_base32_stream_byte_stream[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.' };

uint8_t una_test_base32_stream_upper_case_base32_stream[ 32 ] = {
	'K', 'R', 'U', 'G', 'S', '4', 'Z', 'A', 'N', 'F', 'Z', 'S', 'B', 'Q', '5', 'B',
	'E', 'B', '2', 'G', 'K', '4', '3', 'U', 'F', 'Y', '=', '=', '=', '=', '=', '=' };

uint8_t una_test_base32_stream_utf16le_base32_stream[ 64 ] = {
	'K', 0, 'R', 0, 'U', 0, 'G', 0, 'S', 0, '4', 0, 'Z', 0, 'A', 0,
        'N', 0, 'F', 0, 'Z', 0, 'S', 0, 'B', 0, 'Q', 0, '5', 0, 'B', 0,
        'E', 0, 'B', 0, '2', 0, 'G', 0, 'K', 0, '4', 0, '3', 0, 'U', 0,
        'F', 0, 'Y', 0, '=', 0, '=', 0, '=', 0, '=', 0, '=', 0, '=', 0 };

char *una_test_base32_stream_byte_stream_long = \
	"The test of success is not what you do when you are on top. " \
	"Success is how high you bounce when you hit bottom.\n";

char *una_test_base32_stream_upper_case_base32_stream_long = \
	"KRUGKIDUMVZXIIDPMYQHG5LDMNSXG4ZANFZSA3TPOQQHO2DBOQQHS33VEBSG6IDX" \
	"NBSW4IDZN52SAYLSMUQG63RAORXXALRAKN2WGY3FONZSA2LTEBUG65ZANBUWO2BA" \
	"PFXXKIDCN52W4Y3FEB3WQZLOEB4W65JANBUXIIDCN52HI33NFYFA====";

/* Tests the libuna_base32_stream_size_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_stream_size_to_byte_stream(
     void )
{
	libcerror_error_t *error = NULL;
	size_t byte_stream_size  = 0;
	int result               = 0;

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_utf16le_base32_stream,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648 | LIBUNA_BASE32_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          (uint8_t *) una_test_base32_stream_upper_case_base32_stream_long,
	          184,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	/* Test error cases
	 */
	result = libuna_base32_stream_size_to_byte_stream(
	          NULL,
		  32,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  (size_t) SSIZE_MAX + 1,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  32,
	          NULL,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
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

	/* Incorrect byte order
	 */
	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_utf16le_base32_stream,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648 | LIBUNA_BASE32_VARIANT_ENCODING_UTF16_BIG_ENDIAN,
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
	result = libuna_base32_stream_size_to_byte_stream(
	          (uint8_t *) una_test_base32_stream_upper_case_base32_stream_long,
	          184,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648 | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64,
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

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libuna_base32_stream_copy_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_stream_copy_to_byte_stream(
     void )
{
	uint8_t byte_stream[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libuna_base32_stream_copy_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
		  byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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
	          una_test_base32_stream_byte_stream,
	          16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base32_stream_copy_to_byte_stream(
	          una_test_base32_stream_utf16le_base32_stream,
	          64,
		  byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648 | LIBUNA_BASE32_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
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
	          una_test_base32_stream_byte_stream,
	          16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base32_stream_copy_to_byte_stream(
	          (uint8_t *) una_test_base32_stream_upper_case_base32_stream_long,
	          184,
		  byte_stream,
		  112,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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
	          una_test_base32_stream_byte_stream_long,
	          112 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_base32_stream_copy_to_byte_stream(
	          NULL,
		  32,
		  byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_copy_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  (size_t) SSIZE_MAX + 1,
		  byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_copy_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  32,
	          NULL,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_copy_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  32,
		  byte_stream,
		  (size_t) SSIZE_MAX + 1,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_copy_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
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
	result = libuna_base32_stream_copy_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
		  byte_stream,
		  8,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	/* Incorrect byte order
	 */
	result = libuna_base32_stream_copy_to_byte_stream(
	          una_test_base32_stream_utf16le_base32_stream,
	          64,
		  byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648 | LIBUNA_BASE32_VARIANT_ENCODING_UTF16_BIG_ENDIAN,
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
	result = libuna_base32_stream_copy_to_byte_stream(
	          (uint8_t *) una_test_base32_stream_upper_case_base32_stream_long,
	          184,
		  byte_stream,
		  112,
	          LIBUNA_BASE32_VARIANT_RFC4648 | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64,
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

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libuna_base32_stream_size_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_stream_size_from_byte_stream(
     void )
{
	libcerror_error_t *error  = NULL;
	size_t base32_stream_size = 0;
	int result                = 0;

	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  16,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 32 );

	result = libuna_base32_stream_size_from_byte_stream(
		  (uint8_t *) una_test_base32_stream_byte_stream_long,
		  112,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 184 );

/* TODO test char limit */
/* TODO test encodings */

	/* Test error cases
	 */
	result = libuna_base32_stream_size_from_byte_stream(
		  NULL,
		  16,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  (size_t) SSIZE_MAX + 1,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  16,
		  NULL,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  16,
		  &base32_stream_size,
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

/* Tests the libuna_base32_stream_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_stream_copy_from_byte_stream(
     void )
{
	uint8_t base32_stream[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libuna_base32_stream_copy_from_byte_stream(
		  base32_stream,
		  32,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          base32_stream,
	          una_test_base32_stream_upper_case_base32_stream,
	          32 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libuna_base32_stream_copy_from_byte_stream(
		  base32_stream,
		  184,
		  (uint8_t *) una_test_base32_stream_byte_stream_long,
		  112,
	          LIBUNA_BASE32_VARIANT_RFC4648,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        UNA_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = memory_compare(
	          base32_stream,
	          una_test_base32_stream_upper_case_base32_stream_long,
	          184 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

/* TODO test char limit */
/* TODO test encodings */

	/* Test error cases
	 */
	result = libuna_base32_stream_copy_from_byte_stream(
	          NULL,
		  32,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_copy_from_byte_stream(
	          base32_stream,
		  (size_t) SSIZE_MAX + 1,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_copy_from_byte_stream(
	          base32_stream,
		  32,
		  NULL,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_copy_from_byte_stream(
	          base32_stream,
		  32,
		  una_test_base32_stream_byte_stream,
		  (size_t) SSIZE_MAX + 1,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	result = libuna_base32_stream_copy_from_byte_stream(
	          base32_stream,
		  32,
		  una_test_base32_stream_byte_stream,
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

	/* Base32 stream too small
	 */
	result = libuna_base32_stream_copy_from_byte_stream(
		  base32_stream,
		  0,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	/* Base32 stream too small
	 */
	result = libuna_base32_stream_copy_from_byte_stream(
		  base32_stream,
		  8,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_RFC4648,
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

	/* TODO add tests for libuna_base32_quintuplet_copy_from_base32_stream */
	/* TODO add tests for libuna_base32_quintuplet_copy_to_base32_stream */
	/* TODO add tests for libuna_base32_quintuplet_copy_from_byte_stream */
	/* TODO add tests for libuna_base32_quintuplet_copy_to_byte_stream */

/* TODO fix issue
 * libuna_base32_stream_size_to_byte_stream: invalid character in base32 stream at index: 26.

	UNA_TEST_RUN(
	 "libuna_base32_stream_size_to_byte_stream",
	 una_test_base32_stream_size_to_byte_stream );
*/

	UNA_TEST_RUN(
	 "libuna_base32_stream_copy_to_byte_stream",
	 una_test_base32_stream_copy_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base32_stream_size_from_byte_stream",
	 una_test_base32_stream_size_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base32_stream_copy_from_byte_stream",
	 una_test_base32_stream_copy_from_byte_stream );

	/* TODO add tests for libuna_base32_stream_with_index_copy_from_byte_stream */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

