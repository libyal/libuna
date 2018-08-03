/*
 * Library base32 stream functions test program
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

#include "una_test_libcerror.h"
#include "una_test_libuna.h"
#include "una_test_macros.h"
#include "una_test_unused.h"

#if defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT )

int libuna_base32_character_copy_to_quintet(
     uint8_t base32_character,
     uint8_t *base32_quintet,
     uint32_t base32_variant,
     libcerror_error_t **error );

#endif /* defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT ) */

uint8_t una_test_base32_stream_byte_stream[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.' };

uint8_t una_test_base32_stream_upper_case_base32_stream[ 32 ] = {
	'K', 'R', 'U', 'G', 'S', '4', 'Z', 'A', 'N', 'F', 'Z', 'S', 'B', 'Q', '5', 'B',
	'E', 'B', '2', 'G', 'K', '4', '3', 'U', 'F', 'Y', '=', '=', '=', '=', '=', '=' };

uint8_t una_test_base32_stream_upper_case_base32_stream_hex[ 32 ] = {
	'A', 'H', 'K', '6', 'I', 'S', 'P', '0', 'D', '5', 'P', 'I', '1', 'G', 'T', '1',
	'4', '1', 'Q', '6', 'A', 'S', 'R', 'K', '5', 'O', '=', '=', '=', '=', '=', '=' };

uint8_t una_test_base32_stream_utf16be_base32_stream[ 64 ] = {
	0, 'K', 0, 'R', 0, 'U', 0, 'G', 0, 'S', 0, '4', 0, 'Z', 0, 'A',
	0, 'N', 0, 'F', 0, 'Z', 0, 'S', 0, 'B', 0, 'Q', 0, '5', 0, 'B',
	0, 'E', 0, 'B', 0, '2', 0, 'G', 0, 'K', 0, '4', 0, '3', 0, 'U',
	0, 'F', 0, 'Y', 0, '=', 0, '=', 0, '=', 0, '=', 0, '=', 0, '=' };

uint8_t una_test_base32_stream_utf16le_base32_stream[ 64 ] = {
	'K', 0, 'R', 0, 'U', 0, 'G', 0, 'S', 0, '4', 0, 'Z', 0, 'A', 0,
	'N', 0, 'F', 0, 'Z', 0, 'S', 0, 'B', 0, 'Q', 0, '5', 0, 'B', 0,
	'E', 0, 'B', 0, '2', 0, 'G', 0, 'K', 0, '4', 0, '3', 0, 'U', 0,
	'F', 0, 'Y', 0, '=', 0, '=', 0, '=', 0, '=', 0, '=', 0, '=', 0 };

uint8_t una_test_base32_stream_utf32be_base32_stream[ 128 ] = {
	0, 0, 0, 'K', 0, 0, 0, 'R', 0, 0, 0, 'U', 0, 0, 0, 'G',
	0, 0, 0, 'S', 0, 0, 0, '4', 0, 0, 0, 'Z', 0, 0, 0, 'A',
	0, 0, 0, 'N', 0, 0, 0, 'F', 0, 0, 0, 'Z', 0, 0, 0, 'S',
	0, 0, 0, 'B', 0, 0, 0, 'Q', 0, 0, 0, '5', 0, 0, 0, 'B',
	0, 0, 0, 'E', 0, 0, 0, 'B', 0, 0, 0, '2', 0, 0, 0, 'G',
	0, 0, 0, 'K', 0, 0, 0, '4', 0, 0, 0, '3', 0, 0, 0, 'U',
	0, 0, 0, 'F', 0, 0, 0, 'Y', 0, 0, 0, '=', 0, 0, 0, '=',
	0, 0, 0, '=', 0, 0, 0, '=', 0, 0, 0, '=', 0, 0, 0, '=' };

uint8_t una_test_base32_stream_utf32le_base32_stream[ 128 ] = {
	'K', 0, 0, 0, 'R', 0, 0, 0, 'U', 0, 0, 0, 'G', 0, 0, 0,
	'S', 0, 0, 0, '4', 0, 0, 0, 'Z', 0, 0, 0, 'A', 0, 0, 0,
	'N', 0, 0, 0, 'F', 0, 0, 0, 'Z', 0, 0, 0, 'S', 0, 0, 0,
	'B', 0, 0, 0, 'Q', 0, 0, 0, '5', 0, 0, 0, 'B', 0, 0, 0,
	'E', 0, 0, 0, 'B', 0, 0, 0, '2', 0, 0, 0, 'G', 0, 0, 0,
	'K', 0, 0, 0, '4', 0, 0, 0, '3', 0, 0, 0, 'U', 0, 0, 0,
	'F', 0, 0, 0, 'Y', 0, 0, 0, '=', 0, 0, 0, '=', 0, 0, 0,
	'=', 0, 0, 0, '=', 0, 0, 0, '=', 0, 0, 0, '=', 0, 0, 0 };

char *una_test_base32_stream_byte_stream_long = \
	"The test of success is not what you do when you are on top. " \
	"Success is how high you bounce when you hit bottom.\n";

char *una_test_base32_stream_upper_case_base32_stream_long = \
	"KRUGKIDUMVZXIIDPMYQHG5LDMNSXG4ZANFZSA3TPOQQHO2DBOQQHS33VEBSG6IDX" \
	"NBSW4IDZN52SAYLSMUQG63RAORXXALRAKN2WGY3FONZSA2LTEBUG65ZANBUWO2BA" \
	"PFXXKIDCN52W4Y3FEB3WQZLOEB4W65JANBUXIIDCN52HI33NFYFA====";

char *una_test_base32_stream_upper_case_base32_stream_long_with_whitespace = \
	"\tKRUGKIDUMVZXIIDPMYQHG5LDMNSXG4ZANFZSA3TPOQQHO2DBOQQHS33VEBSG6IDX\r\n" \
	"\tNBSW4IDZN52SAYLSMUQG63RAORXXALRAKN2WGY3FONZSA2LTEBUG65ZANBUWO2BA\r\n" \
	"\tPFXXKIDCN52W4Y3FEB3WQZLOEB4W65JANBUXIIDCN52HI33NFYFA====\r\n";

#if defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT )

/* Tests the libuna_base32_character_copy_to_quintet function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_character_copy_to_quintet(
     void )
{
	libcerror_error_t *error = NULL;
	uint8_t base32_quintet   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	base32_quintet = 0;

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) 'A',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintet = 0;

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) 'J',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 9 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintet = 0;

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) 'S',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 18 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintet = 0;

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) '2',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 26 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintet = 0;

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) '0',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_HEX,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintet = 0;

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) 'A',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_HEX,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 10 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintet = 0;

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) 'J',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_HEX,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 19 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintet = 0;

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) 'S',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_HEX,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 27 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base32_quintet = 0;

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) '0',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) 'Z',
		  &base32_quintet,
	          LIBUNA_BASE32_VARIANT_ALPHABET_HEX,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) 'A',
		  NULL,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_character_copy_to_quintet(
	          (uint8_t) 'A',
		  &base32_quintet,
	          0x000f0000UL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "base32_quintet",
	 base32_quintet,
	 0 );

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

/* Tests the libuna_base32_quintuplet_copy_from_base32_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_quintuplet_copy_from_base32_stream(
     void )
{
	libcerror_error_t *error   = NULL;
	size_t base32_stream_index = 0;
	uint64_t base32_quintuplet = 0;
	uint8_t padding_size       = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	base32_quintuplet   = 0;
	base32_stream_index = 0;
	padding_size        = 0;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x5468697320UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 8 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintuplet   = 0;
	base32_stream_index = 0;
	padding_size        = 0;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_utf16be_base32_stream,
	          64,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x5468697320UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintuplet   = 0;
	base32_stream_index = 0;
	padding_size        = 0;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_utf16le_base32_stream,
	          64,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x5468697320UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintuplet   = 0;
	base32_stream_index = 0;
	padding_size        = 0;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_utf32be_base32_stream,
	          128,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x5468697320UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 32 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintuplet   = 0;
	base32_stream_index = 0;
	padding_size        = 0;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_utf32le_base32_stream,
	          128,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x5468697320UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 32 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintuplet   = 0;
	base32_stream_index = 32 - 8;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32 - 6,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x2e00000000UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 26 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 6 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintuplet   = 0;
	base32_stream_index = 32 - 8;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_OPTIONAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x2e00000000UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 32 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 6 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintuplet   = 0;
	base32_stream_index = 32 - 8;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x2e00000000UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 32 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 6 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base32_quintuplet   = 0;
	base32_stream_index = 0;
	padding_size        = 0;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  NULL,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
		  NULL,
	          32,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          (size_t) SSIZE_MAX + 1,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
		  NULL,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	base32_stream_index = 32;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
		  NULL,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	base32_stream_index = 0;

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
	          &base32_stream_index,
		  NULL,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid padding variant
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | 0x0f000000UL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid encoding
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
	          &base32_stream_index,
	          &padding_size,
	          0xf0000000UL | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Missing 1st character
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          0,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Missing 2nd character
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          1,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Missing 3rd character
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          2,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Missing 4th character
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          3,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Missing 5th character
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          4,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Missing 6th character
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          5,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Missing 7th character
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          6,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Missing 8th character
	 */
	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          7,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Padding where not supposed to
	 */
	base32_quintuplet   = 0;
	base32_stream_index = 32 - 8;

	result = libuna_base32_quintuplet_copy_from_base32_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
	          &base32_stream_index,
	          &padding_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 24 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

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

/* Tests the libuna_base32_quintuplet_copy_to_base32_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_quintuplet_copy_to_base32_stream(
     void )
{
	uint8_t base32_stream[ 32 ];

	libcerror_error_t *error   = NULL;
	size_t base32_stream_index = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	base32_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 8 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base32_stream,
	          una_test_base32_stream_upper_case_base32_stream,
	          8 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base32_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base32_stream,
	          una_test_base32_stream_utf16be_base32_stream,
	          16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base32_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base32_stream,
	          una_test_base32_stream_utf16le_base32_stream,
	          16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base32_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base32_stream,
	          una_test_base32_stream_utf32be_base32_stream,
	          32 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base32_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base32_stream,
	          una_test_base32_stream_utf32le_base32_stream,
	          32 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base32_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ALPHABET_HEX | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 8 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base32_stream,
	          una_test_base32_stream_upper_case_base32_stream_hex,
	          8 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base32_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x2e00000000UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          6,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 8 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base32_stream,
	          &( una_test_base32_stream_upper_case_base32_stream[ 24 ] ),
	          8 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base32_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x2e00000000UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          6,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base32_stream,
	          &( una_test_base32_stream_upper_case_base32_stream[ 24 ] ),
	          2 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	base32_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
		  NULL,
	          32,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          (size_t) SSIZE_MAX + 1,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
		  NULL,
	          0,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	base32_stream_index = 32;

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	base32_stream_index = 0;

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          8,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid alphabet
	 */
	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          0x000f0000UL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid padding variant
	 */
	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | 0x0f000000UL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid encoding
	 */
	result = libuna_base32_quintuplet_copy_to_base32_stream(
		  0x5468697320UL,
	          base32_stream,
	          32,
	          &base32_stream_index,
	          0,
	          0xf0000000UL | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_index",
	 base32_stream_index,
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

/* Tests the libuna_base32_quintuplet_copy_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_quintuplet_copy_to_byte_stream(
     void )
{
	uint8_t byte_stream[ 32 ];

	libcerror_error_t *error = NULL;
	size_t byte_stream_index = 0;
	int result               = 0;

	/* Test regular cases
	 */
	byte_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_byte_stream(
		  0x5468697320UL,
	          byte_stream,
	          32,
	          &byte_stream_index,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 5 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_byte_stream(
		  0x2e00000000UL,
	          byte_stream,
	          32,
	          &byte_stream_index,
	          6,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	byte_stream_index = 0;

	result = libuna_base32_quintuplet_copy_to_byte_stream(
		  0x5468697320UL,
		  NULL,
	          32,
	          &byte_stream_index,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_to_byte_stream(
		  0x5468697320UL,
	          byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          &byte_stream_index,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_to_byte_stream(
		  0x5468697320UL,
	          byte_stream,
	          32,
		  NULL,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_to_byte_stream(
		  0x5468697320UL,
	          byte_stream,
	          32,
	          &byte_stream_index,
	          7,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
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

/* Tests the libuna_base32_quintuplet_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_quintuplet_copy_from_byte_stream(
     void )
{
	libcerror_error_t *error   = NULL;
	size_t byte_stream_index   = 0;
	uint64_t base32_quintuplet = 0;
	uint8_t padding_size       = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	base32_quintuplet = 0;
	byte_stream_index = 0;
	padding_size      = 0;

	result = libuna_base32_quintuplet_copy_from_byte_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_byte_stream,
	          16,
	          &byte_stream_index,
	          &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x5468697320UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 5 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_quintuplet = 0;
	byte_stream_index = 15;
	padding_size      = 0;

	result = libuna_base32_quintuplet_copy_from_byte_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_byte_stream,
	          16,
	          &byte_stream_index,
	          &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0x2e00000000UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 6 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base32_quintuplet = 0;
	byte_stream_index = 0;
	padding_size      = 0;

	result = libuna_base32_quintuplet_copy_from_byte_stream(
		  NULL,
	          una_test_base32_stream_byte_stream,
	          16,
	          &byte_stream_index,
	          &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_from_byte_stream(
		  &base32_quintuplet,
		  NULL,
	          16,
	          &byte_stream_index,
	          &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_from_byte_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_byte_stream,
	          (size_t) SSIZE_MAX + 1,
	          &byte_stream_index,
	          &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_from_byte_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_byte_stream,
	          16,
		  NULL,
	          &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_quintuplet_copy_from_byte_stream(
		  &base32_quintuplet,
	          una_test_base32_stream_byte_stream,
	          16,
	          &byte_stream_index,
		  NULL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT64(
	 "base32_quintuplet",
	 base32_quintuplet,
	 (uint64_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 (uint8_t) 0 );

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

/* Tests the libuna_base32_stream_size_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_stream_size_to_byte_stream(
     void )
{
	libcerror_error_t *error = NULL;
	size_t byte_stream_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	byte_stream_size = 0;

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_utf16be_base32_stream,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_utf16le_base32_stream,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_utf32be_base32_stream,
	          128,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 64 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_utf32le_base32_stream,
	          128,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          0,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_size",
	 byte_stream_size,
	 (size_t) 64 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_size = 0;

	result = libuna_base32_stream_size_to_byte_stream(
	          (uint8_t *) una_test_base32_stream_upper_case_base32_stream_long,
	          184,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          (uint8_t *) una_test_base32_stream_upper_case_base32_stream_long_with_whitespace,
	          193,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64 | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          LIBUNA_BASE32_FLAG_STRIP_WHITESPACE,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
	          0,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          NULL,
		  32,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  (size_t) SSIZE_MAX + 1,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  32,
	          NULL,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	/* Invalid character limit
	 */
	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  32,
	          NULL,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | 0x000000ffUL | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	/* Invalid alphabet
	 */
	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  32,
	          NULL,
	          0x000f0000UL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	/* Invalid encoding
	 */
	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  32,
	          NULL,
	          0xf0000000UL | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	/* Invalid flags
	 */
	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
		  32,
	          NULL,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          0xff,
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

	/* Incorrect case
	 */

	/* Incorrect byte order
	 */
	result = libuna_base32_stream_size_to_byte_stream(
	          una_test_base32_stream_utf16le_base32_stream,
	          64,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	/* Incorrect character limit
	 */
	result = libuna_base32_stream_size_to_byte_stream(
	          (uint8_t *) una_test_base32_stream_upper_case_base32_stream_long,
	          184,
		  &byte_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64 | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	/* Missing whitespace flag
	 */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
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

	/* Test regular cases
	 */
	result = libuna_base32_stream_copy_to_byte_stream(
	          una_test_base32_stream_upper_case_base32_stream,
	          32,
		  byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64 | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
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

	/* Test regular cases
	 */
	base32_stream_size = 0;

	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  16,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_stream_size = 0;

	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  16,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 64 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_stream_size = 0;

	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  16,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 128 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_stream_size = 0;

	result = libuna_base32_stream_size_from_byte_stream(
		  (uint8_t *) una_test_base32_stream_byte_stream_long,
		  112,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 184 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base32_stream_size = 0;

	result = libuna_base32_stream_size_from_byte_stream(
		  (uint8_t *) una_test_base32_stream_byte_stream_long,
		  112,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_64 | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 187 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base32_stream_size = 0;

	result = libuna_base32_stream_size_from_byte_stream(
		  NULL,
		  16,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  (size_t) SSIZE_MAX + 1,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  16,
		  NULL,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid character limit
	 */
	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  16,
		  &base32_stream_size,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | 0x000000ffUL | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid encoding
	 */
	result = libuna_base32_stream_size_from_byte_stream(
		  una_test_base32_stream_byte_stream,
		  16,
		  &base32_stream_size,
	          0xf0000000UL | LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base32_stream_size",
	 base32_stream_size,
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

/* Tests the libuna_base32_stream_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_stream_copy_from_byte_stream(
     void )
{
	uint8_t base32_stream[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_base32_stream_copy_from_byte_stream(
		  base32_stream,
		  32,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	/* Test error cases
	 */
	result = libuna_base32_stream_copy_from_byte_stream(
	          NULL,
		  32,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

/* Tests the libuna_base32_stream_with_index_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base32_stream_with_index_copy_from_byte_stream(
     void )
{
	uint8_t base32_stream[ 256 ];

	libcerror_error_t *error   = NULL;
	size_t base32_stream_index = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	base32_stream_index = 0;

	result = libuna_base32_stream_with_index_copy_from_byte_stream(
		  base32_stream,
		  32,
		  &base32_stream_index,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	base32_stream_index = 0;

	result = libuna_base32_stream_with_index_copy_from_byte_stream(
		  base32_stream,
		  184,
		  &base32_stream_index,
		  (uint8_t *) una_test_base32_stream_byte_stream_long,
		  112,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	base32_stream_index = 0;

	result = libuna_base32_stream_with_index_copy_from_byte_stream(
		  base32_stream,
		  32,
		  &base32_stream_index,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_HEX | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	          una_test_base32_stream_upper_case_base32_stream_hex,
	          32 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

/* TODO test char limit */
/* TODO test encodings */

	/* Test error cases
	 */
	base32_stream_index = 0;

	result = libuna_base32_stream_with_index_copy_from_byte_stream(
	          NULL,
		  32,
		  &base32_stream_index,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_with_index_copy_from_byte_stream(
	          base32_stream,
		  (size_t) SSIZE_MAX + 1,
		  &base32_stream_index,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_with_index_copy_from_byte_stream(
	          base32_stream,
		  32,
		  NULL,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_with_index_copy_from_byte_stream(
	          base32_stream,
		  32,
		  &base32_stream_index,
		  NULL,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_with_index_copy_from_byte_stream(
	          base32_stream,
		  32,
		  &base32_stream_index,
		  una_test_base32_stream_byte_stream,
		  (size_t) SSIZE_MAX + 1,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base32_stream_with_index_copy_from_byte_stream(
	          base32_stream,
		  32,
		  &base32_stream_index,
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
	result = libuna_base32_stream_with_index_copy_from_byte_stream(
		  base32_stream,
		  0,
		  &base32_stream_index,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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
	result = libuna_base32_stream_with_index_copy_from_byte_stream(
		  base32_stream,
		  8,
		  &base32_stream_index,
		  una_test_base32_stream_byte_stream,
		  16,
	          LIBUNA_BASE32_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE32_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE32_VARIANT_PADDING_REQUIRED,
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

#if defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT )

	UNA_TEST_RUN(
	 "libuna_base32_character_copy_to_quintet",
	 una_test_base32_character_copy_to_quintet );

#endif /* defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT ) */

	UNA_TEST_RUN(
	 "libuna_base32_quintuplet_copy_from_base32_stream",
	 una_test_base32_quintuplet_copy_from_base32_stream );

	UNA_TEST_RUN(
	 "libuna_base32_quintuplet_copy_to_base32_stream",
	 una_test_base32_quintuplet_copy_to_base32_stream );

	UNA_TEST_RUN(
	 "libuna_base32_quintuplet_copy_from_byte_stream",
	 una_test_base32_quintuplet_copy_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base32_quintuplet_copy_to_byte_stream",
	 una_test_base32_quintuplet_copy_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base32_stream_size_to_byte_stream",
	 una_test_base32_stream_size_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base32_stream_copy_to_byte_stream",
	 una_test_base32_stream_copy_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base32_stream_size_from_byte_stream",
	 una_test_base32_stream_size_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base32_stream_copy_from_byte_stream",
	 una_test_base32_stream_copy_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base32_stream_with_index_copy_from_byte_stream",
	 una_test_base32_stream_with_index_copy_from_byte_stream );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

