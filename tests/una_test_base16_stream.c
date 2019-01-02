/*
 * Library base16 stream functions test program
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
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

#include "una_test_libcerror.h"
#include "una_test_libuna.h"
#include "una_test_macros.h"
#include "una_test_unused.h"

#if defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT )

int libuna_base16_character_copy_from_base16_stream(
     uint32_t *base16_character,
     const uint8_t *base16_stream,
     uint32_t base16_variant,
     libcerror_error_t **error );

#endif /* defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT ) */

uint8_t una_test_base16_stream_byte_stream[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.' };

uint8_t una_test_base16_stream_lower_case_base16_stream[ 32 ] = {
	'5', '4', '6', '8', '6', '9', '7', '3', '2', '0', '6', '9', '7', '3', '2', '0',
	'c', '3', 'a', '1', '2', '0', '7', '4', '6', '5', '7', '3', '7', '4', '2', 'e' };

uint8_t una_test_base16_stream_upper_case_base16_stream[ 32 ] = {
	'5', '4', '6', '8', '6', '9', '7', '3', '2', '0', '6', '9', '7', '3', '2', '0',
	'C', '3', 'A', '1', '2', '0', '7', '4', '6', '5', '7', '3', '7', '4', '2', 'E' };

uint8_t una_test_base16_stream_utf16be_lower_case_base16_stream[ 64 ] = {
	0, '5', 0, '4', 0, '6', 0, '8', 0, '6', 0, '9', 0, '7', 0, '3',
	0, '2', 0, '0', 0, '6', 0, '9', 0, '7', 0, '3', 0, '2', 0, '0',
	0, 'c', 0, '3', 0, 'a', 0, '1', 0, '2', 0, '0', 0, '7', 0, '4',
	0, '6', 0, '5', 0, '7', 0, '3', 0, '7', 0, '4', 0, '2', 0, 'e' };

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

uint8_t una_test_base16_stream_utf32le_upper_case_base16_stream[ 128 ] = {
	'5', 0, 0, 0, '4', 0, 0, 0, '6', 0, 0, 0, '8', 0, 0, 0, '6', 0, 0, 0, '9', 0, 0, 0, '7', 0, 0, 0, '3', 0, 0, 0,
	'2', 0, 0, 0, '0', 0, 0, 0, '6', 0, 0, 0, '9', 0, 0, 0, '7', 0, 0, 0, '3', 0, 0, 0, '2', 0, 0, 0, '0', 0, 0, 0,
	'C', 0, 0, 0, '3', 0, 0, 0, 'A', 0, 0, 0, '1', 0, 0, 0, '2', 0, 0, 0, '0', 0, 0, 0, '7', 0, 0, 0, '4', 0, 0, 0,
	'6', 0, 0, 0, '5', 0, 0, 0, '7', 0, 0, 0, '3', 0, 0, 0, '7', 0, 0, 0, '4', 0, 0, 0, '2', 0, 0, 0, 'E', 0, 0, 0 };

uint8_t una_test_base16_stream_utf16be_lower_case_error_first_character[ 64 ] = {
	1, '5', 0, '4', 0, '6', 0, '8', 0, '6', 0, '9', 0, '7', 0, '3',
	0, '2', 0, '0', 0, '6', 0, '9', 0, '7', 0, '3', 0, '2', 0, '0',
	0, 'c', 0, '3', 0, 'a', 0, '1', 0, '2', 0, '0', 0, '7', 0, '4',
	0, '6', 0, '5', 0, '7', 0, '3', 0, '7', 0, '4', 0, '2', 0, 'e' };

uint8_t una_test_base16_stream_utf16be_lower_case_error_second_character[ 64 ] = {
	0, '5', 1, '4', 0, '6', 0, '8', 0, '6', 0, '9', 0, '7', 0, '3',
	0, '2', 0, '0', 0, '6', 0, '9', 0, '7', 0, '3', 0, '2', 0, '0',
	0, 'c', 0, '3', 0, 'a', 0, '1', 0, '2', 0, '0', 0, '7', 0, '4',
	0, '6', 0, '5', 0, '7', 0, '3', 0, '7', 0, '4', 0, '2', 0, 'e' };

char *una_test_base16_stream_byte_stream_long = \
	"The test of success is not what you do when you are on top. " \
	"Success is how high you bounce when you hit bottom.\n";

char *una_test_base16_stream_lower_case_base16_stream_limit64 = \
	"5468652074657374206f662073756363657373206973206e6f74207768617420\n"
	"796f7520646f207768656e20796f7520617265206f6e20746f702e2053756363\n"
	"65737320697320686f77206869676820796f7520626f756e6365207768656e20\n"
	"796f752068697420626f74746f6d2e0a\n";

char *una_test_base16_stream_lower_case_base16_stream_limit64_with_whitespace = \
	"\t5468652074657374206f662073756363657373206973206e6f74207768617420\t\n"
	"  796f7520646f207768656e20796f7520617265206f6e20746f702e2053756363  \n"
	"\t65737320697320686f77206869676820796f7520626f756e6365207768656e20  \n"
	"\t796f752068697420626f74746f6d2e0a                                  \n";

char *una_test_base16_stream_lower_case_base16_stream_limit76 = \
	"5468652074657374206f662073756363657373206973206e6f74207768617420796f7520646f\n"
	"207768656e20796f7520617265206f6e20746f702e205375636365737320697320686f772068\n"
	"69676820796f7520626f756e6365207768656e20796f752068697420626f74746f6d2e0a\n";

#if defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT )

/* Tests the libuna_base16_character_copy_from_base16_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base16_character_copy_from_base16_stream(
     void )
{
	libcerror_error_t *error  = NULL;
	uint32_t base16_character = 0;
	int result                = 0;

	/* Test regular cases
	 */
	base16_character = 0;

	result = libuna_base16_character_copy_from_base16_stream(
	          &base16_character,
	          una_test_base16_stream_lower_case_base16_stream,
	          LIBUNA_BASE16_VARIANT_ENCODING_BYTE_STREAM,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base16_character",
	 base16_character,
	 (uint32_t) 0x00000035UL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base16_character = 0;

	result = libuna_base16_character_copy_from_base16_stream(
	          &base16_character,
	          una_test_base16_stream_utf16be_lower_case_base16_stream,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_BIG_ENDIAN,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base16_character",
	 base16_character,
	 (uint32_t) 0x00000035UL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base16_character = 0;

	result = libuna_base16_character_copy_from_base16_stream(
	          &base16_character,
	          una_test_base16_stream_utf16le_lower_case_base16_stream,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base16_character",
	 base16_character,
	 (uint32_t) 0x00000035UL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base16_character = 0;

	result = libuna_base16_character_copy_from_base16_stream(
	          &base16_character,
	          una_test_base16_stream_utf32be_upper_case_base16_stream,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base16_character",
	 base16_character,
	 (uint32_t) 0x00000035UL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base16_character = 0;

	result = libuna_base16_character_copy_from_base16_stream(
	          &base16_character,
	          una_test_base16_stream_utf32le_upper_case_base16_stream,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base16_character",
	 base16_character,
	 (uint32_t) 0x00000035UL );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base16_character = 0;

	result = libuna_base16_character_copy_from_base16_stream(
	          NULL,
	          una_test_base16_stream_lower_case_base16_stream,
	          LIBUNA_BASE16_VARIANT_ENCODING_BYTE_STREAM,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base16_character",
	 base16_character,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base16_character_copy_from_base16_stream(
	          &base16_character,
	          NULL,
	          LIBUNA_BASE16_VARIANT_ENCODING_BYTE_STREAM,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base16_character",
	 base16_character,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base16_character_copy_from_base16_stream(
	          &base16_character,
	          una_test_base16_stream_lower_case_base16_stream,
	          0xf0000000UL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base16_character",
	 base16_character,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base16_character_copy_from_base16_stream(
	          &base16_character,
	          una_test_base16_stream_utf16be_lower_case_error_first_character,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base16_character",
	 base16_character,
	 (uint32_t) 0 );

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

#endif /* defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT ) */

/* Tests the libuna_base16_stream_size_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base16_stream_size_to_byte_stream(
     void )
{
	libcerror_error_t *error = NULL;
	size_t byte_stream_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	byte_stream_size = 0;

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

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

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

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf16le_lower_case_base16_stream,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf32be_upper_case_base16_stream,
	          128,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base16_stream_size_to_byte_stream(
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit64,
	          228,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 112 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base16_stream_size_to_byte_stream(
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit64_with_whitespace,
	          272,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
	          LIBUNA_BASE16_FLAG_STRIP_WHITESPACE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 112 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base16_stream_size_to_byte_stream(
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit76,
	          227,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_76,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 112 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
	          0,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	byte_stream_size = 0;

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

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 0 );

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

	/* Invalid character limit
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  32,
		  &byte_stream_size,
	          0x000000ffUL,
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

	/* Invalid variant
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_upper_case_base16_stream,
	          32,
		  &byte_stream_size,
	          0x000f0000UL | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Invalid encoding
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf16le_lower_case_base16_stream,
	          64,
		  &byte_stream_size,
	          0xf0000000UL | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Invalid flags
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_upper_case_base16_stream,
	          32,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          0xff,
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

	/* Base16 stream too small for first character
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf16le_lower_case_base16_stream,
	          1,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Base16 stream too small for first character with leading whitespace
	 */

	/* Base16 stream too small for second character
	 */

	/* Incorrect first character
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf16be_lower_case_error_first_character,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Incorrect second character
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          una_test_base16_stream_utf16be_lower_case_error_second_character,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit64,
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

/* TODO Incorrect character limit of only last line */

	/* Missing whitespace flag
	 */
	result = libuna_base16_stream_size_to_byte_stream(
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit64_with_whitespace,
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
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
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

	/* Test regular cases
	 */
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
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit64,
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
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit64_with_whitespace,
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

	result = libuna_base16_stream_copy_to_byte_stream(
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit76,
	          227,
		  byte_stream,
		  112,
	          LIBUNA_BASE16_VARIANT_CASE_MIXED | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_76,
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

	/* Invalid character limit
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  32,
		  byte_stream,
		  16,
	          0x000000ffUL,
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

	/* Invalid variant
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  32,
		  byte_stream,
		  16,
	          0x000f0000UL | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Invalid encoding
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
		  32,
		  byte_stream,
		  16,
	          0xf0000000UL | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Invalid flags
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_lower_case_base16_stream,
	          32,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          0xff,
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

	/* Base16 stream too small for first character with leading whitespace
	 */

	/* Base16 stream too small for second character
	 */

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

	/* Incorrect first character
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_utf16be_lower_case_error_first_character,
	          64,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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

	/* Incorrect second character
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          una_test_base16_stream_utf16be_lower_case_error_second_character,
	          64,
		  byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
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
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit64,
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

/* TODO Incorrect character limit of only last line */

	/* Missing whitespace flag
	 */
	result = libuna_base16_stream_copy_to_byte_stream(
	          (uint8_t *) una_test_base16_stream_lower_case_base16_stream_limit64_with_whitespace,
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
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
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

	/* Test regular cases
	 */
	base16_stream_size = 0;

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

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base16_stream_size = 0;

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

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base16_stream_size = 0;

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 64 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base16_stream_size = 0;

	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 128 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base16_stream_size = 0;

	result = libuna_base16_stream_size_from_byte_stream(
		  (uint8_t *) una_test_base16_stream_byte_stream_long,
		  112,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 228 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base16_stream_size = 0;

	result = libuna_base16_stream_size_from_byte_stream(
		  (uint8_t *) una_test_base16_stream_byte_stream_long,
		  112,
		  &base16_stream_size,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_76,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 227 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base16_stream_size = 0;

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

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 0 );

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

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 0 );

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

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid character limit
	 */
	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          0x000000ffUL,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid variant
	 */
	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          0x000f0000UL | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid encoding
	 */
	result = libuna_base16_stream_size_from_byte_stream(
		  una_test_base16_stream_byte_stream,
		  16,
		  &base16_stream_size,
	          0xf0000000UL | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_size",
	 base16_stream_size,
	 (size_t) 0 );

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

/* Tests the libuna_base16_stream_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base16_stream_copy_from_byte_stream(
     void )
{
	uint8_t base16_stream[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_base16_stream_with_index_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base16_stream_with_index_copy_from_byte_stream(
     void )
{
	uint8_t base16_stream[ 256 ];

	libcerror_error_t *error   = NULL;
	size_t base16_stream_index = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
		  base16_stream,
		  32,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 32 );

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

	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
		  base16_stream,
		  32,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 32 );

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

	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
		  base16_stream,
		  64,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 64 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base16_stream,
	          una_test_base16_stream_utf16be_lower_case_base16_stream,
	          64 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
		  base16_stream,
		  64,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 64 );

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

	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
		  base16_stream,
		  128,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 128 );

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

	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
		  base16_stream,
		  128,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN | LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 128 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base16_stream,
	          una_test_base16_stream_utf32le_upper_case_base16_stream,
	          128 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
		  base16_stream,
		  228,
		  &base16_stream_index,
		  (uint8_t *) una_test_base16_stream_byte_stream_long,
		  112,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_64,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 228 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base16_stream,
	          una_test_base16_stream_lower_case_base16_stream_limit64,
	          228 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
		  base16_stream,
		  227,
		  &base16_stream_index,
		  (uint8_t *) una_test_base16_stream_byte_stream_long,
		  112,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_76,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 227 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base16_stream,
	          una_test_base16_stream_lower_case_base16_stream_limit76,
	          227 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          NULL,
		  32,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          base16_stream,
		  (size_t) SSIZE_MAX + 1,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          base16_stream,
		  32,
		  NULL,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	base16_stream_index = 32;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          base16_stream,
		  32,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          base16_stream,
		  32,
		  &base16_stream_index,
		  NULL,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          base16_stream,
		  32,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  (size_t) SSIZE_MAX + 1,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid character limit
	 */
	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          base16_stream,
		  32,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          0x000000ffUL,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid variant
	 */
	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          base16_stream,
		  32,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          0x000f0000UL | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid encoding
	 */
	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          base16_stream,
		  32,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          0xf0000000UL | LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Base16 stream too small
	 */
	base16_stream_index = 0;

	result = libuna_base16_stream_with_index_copy_from_byte_stream(
	          base16_stream,
		  8,
		  &base16_stream_index,
		  una_test_base16_stream_byte_stream,
		  16,
	          LIBUNA_BASE16_VARIANT_CASE_LOWER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base16_stream_index",
	 base16_stream_index,
	 (size_t) 0 );

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

#if defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT )

	UNA_TEST_RUN(
	 "libuna_base16_character_copy_from_base16_stream",
	 una_test_base16_character_copy_from_base16_stream );

#endif /* defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT ) */

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

	UNA_TEST_RUN(
	 "libuna_base16_stream_with_index_copy_from_byte_stream",
	 una_test_base16_stream_with_index_copy_from_byte_stream );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

