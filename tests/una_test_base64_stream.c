/*
 * Library base64 stream functions test program
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

#if defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT )

int libuna_base64_character_copy_to_sixtet(
     uint32_t base64_character,
     uint8_t *base64_sixtet,
     uint32_t base64_variant,
     libcerror_error_t **error );

#endif /* defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT ) */

uint8_t una_test_base64_stream_byte_stream[ 16 ] = {
	'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.' };

uint8_t una_test_base64_stream_rfc1421_byte_stream[ 25 ] = {
	'V', 'G', 'h', 'p', 'c', 'y', 'B', 'p', 'c', 'y', 'D', 'D', 'o', 'S', 'B', '0', 'Z', 'X', 'N', '0',
        'L', 'g', '=', '=', '\n' };

uint8_t una_test_base64_stream_rfc1642_byte_stream[ 22 ] = {
	'V', 'G', 'h', 'p', 'c', 'y', 'B', 'p', 'c', 'y', 'D', 'D', 'o', 'S', 'B', '0', 'Z', 'X', 'N', '0',
        'L', 'g' };

uint8_t una_test_base64_stream_rfc1421_utf16be_stream[ 48 ] = {
	0, 'V', 0, 'G', 0, 'h', 0, 'p', 0, 'c', 0, 'y', 0, 'B', 0, 'p', 0, 'c', 0, 'y', 0, 'D', 0, 'D',
        0, 'o', 0, 'S', 0, 'B', 0, '0', 0, 'Z', 0, 'X', 0, 'N', 0, '0', 0, 'L', 0, 'g', 0, '=', 0, '=' };

uint8_t una_test_base64_stream_rfc1421_utf16le_stream[ 48 ] = {
	'V', 0, 'G', 0, 'h', 0, 'p', 0, 'c', 0, 'y', 0, 'B', 0, 'p', 0, 'c', 0, 'y', 0, 'D', 0, 'D', 0,
        'o', 0, 'S', 0, 'B', 0, '0', 0, 'Z', 0, 'X', 0, 'N', 0, '0', 0, 'L', 0, 'g', 0, '=', 0, '=', 0 };

uint8_t una_test_base64_stream_rfc1421_utf32be_stream[ 96 ] = {
	0, 0, 0, 'V', 0, 0, 0, 'G', 0, 0, 0, 'h', 0, 0, 0, 'p', 0, 0, 0, 'c', 0, 0, 0, 'y', 0, 0, 0, 'B',
        0, 0, 0, 'p', 0, 0, 0, 'c', 0, 0, 0, 'y', 0, 0, 0, 'D', 0, 0, 0, 'D', 0, 0, 0, 'o', 0, 0, 0, 'S',
        0, 0, 0, 'B', 0, 0, 0, '0', 0, 0, 0, 'Z', 0, 0, 0, 'X', 0, 0, 0, 'N', 0, 0, 0, '0', 0, 0, 0, 'L',
        0, 0, 0, 'g', 0, 0, 0, '=', 0, 0, 0, '=' };

uint8_t una_test_base64_stream_rfc1421_utf32le_stream[ 96 ] = {
	'V', 0, 0, 0, 'G', 0, 0, 0, 'h', 0, 0, 0, 'p', 0, 0, 0, 'c', 0, 0, 0, 'y', 0, 0, 0, 'B', 0, 0, 0,
        'p', 0, 0, 0, 'c', 0, 0, 0, 'y', 0, 0, 0, 'D', 0, 0, 0, 'D', 0, 0, 0, 'o', 0, 0, 0, 'S', 0, 0, 0,
        'B', 0, 0, 0, '0', 0, 0, 0, 'Z', 0, 0, 0, 'X', 0, 0, 0, 'N', 0, 0, 0, '0', 0, 0, 0, 'L', 0, 0, 0,
        'g', 0, 0, 0, '=', 0, 0, 0, '=', 0, 0, 0 };

#if defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT )

/* Tests the libuna_base64_character_copy_to_sixtet function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_character_copy_to_sixtet(
     void )
{
	libcerror_error_t *error = NULL;
	uint8_t base64_sixtet    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) 'A',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) 'J',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 9 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) 'S',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 18 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) 'a',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 26 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) 'j',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 35 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) 's',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 44 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) '0',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 52 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) '+',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 62 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) '/',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 63 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) '-',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_URL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 62 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) 0xffffffffUL,
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) '#',
		  &base64_sixtet,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base64_sixtet = 0;

	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) 'A',
		  NULL,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid alphabet
	 */
	result = libuna_base64_character_copy_to_sixtet(
	          (uint32_t) 'A',
		  &base64_sixtet,
	          0x000f0000UL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "result",
	 base64_sixtet,
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

/* Tests the libuna_base64_triplet_copy_from_base64_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_triplet_copy_from_base64_stream(
     void )
{
	libcerror_error_t *error   = NULL;
	size_t base64_stream_index = 0;
	uint32_t base64_triplet    = 0;
	uint8_t padding_size       = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	base64_triplet      = 0;
	base64_stream_index = 0;
	padding_size        = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0x00546869UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_triplet      = 0;
	base64_stream_index = 0;
	padding_size        = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_utf16be_stream,
	          48,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0x00546869UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 8 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_triplet      = 0;
	base64_stream_index = 0;
	padding_size        = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_utf16le_stream,
	          48,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0x00546869UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 8 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_triplet      = 0;
	base64_stream_index = 0;
	padding_size        = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_utf32be_stream,
	          96,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0x00546869UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_triplet      = 0;
	base64_stream_index = 0;
	padding_size        = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_utf32le_stream,
	          96,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0x00546869UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_triplet      = 0;
	base64_stream_index = 20;
	padding_size        = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          22,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0x002e0000UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 22 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_triplet      = 0;
	base64_stream_index = 20;
	padding_size        = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_OPTIONAL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0x002e0000UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 24 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_triplet      = 0;
	base64_stream_index = 20;
	padding_size        = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0x002e0000UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 24 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base64_triplet      = 0;
	base64_stream_index = 0;
	padding_size        = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          NULL,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          NULL,
	          24,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          (size_t) SSIZE_MAX + 1,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  NULL,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	base64_stream_index = 24;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &base64_stream_index,
		  &padding_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 24 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	base64_stream_index = 0;

	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &base64_stream_index,
		  NULL,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid character limit
	 */
	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &base64_stream_index,
		  &padding_size,
	          0x000000ffUL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid alphabet
	 */
	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &base64_stream_index,
		  &padding_size,
	          0x000f0000UL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid encoding
	 */
	result = libuna_base64_triplet_copy_from_base64_stream(
	          &base64_triplet,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &base64_stream_index,
		  &padding_size,
	          0xf0000000UL | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* TODO add tests for missing 1st base64 character */

	/* TODO add tests for missing 2nd base64 character */

	/* TODO add tests for missing 3rd base64 character */

	/* TODO add tests for missing 4th base64 character */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_base64_triplet_copy_to_base64_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_triplet_copy_to_base64_stream(
     void )
{
	uint8_t base64_stream[ 32 ];

	libcerror_error_t *error   = NULL;
	size_t base64_stream_index = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	base64_stream_index = 0;

	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          base64_stream,
	          32,
		  &base64_stream_index,
		  0,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	base64_stream_index = 0;

	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          base64_stream,
	          32,
		  &base64_stream_index,
		  0,
	          LIBUNA_BASE64_VARIANT_ALPHABET_URL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base64_stream_index = 0;

	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          NULL,
	          32,
		  &base64_stream_index,
		  0,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          base64_stream,
	          (size_t) SSIZE_MAX + 1,
		  &base64_stream_index,
		  0,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          base64_stream,
	          32,
		  NULL,
		  0,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	base64_stream_index = 32;

	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          base64_stream,
	          32,
		  &base64_stream_index,
		  0,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	base64_stream_index = 0;

	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          base64_stream,
	          32,
		  &base64_stream_index,
		  3,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid character limit
	 */
	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          base64_stream,
	          32,
		  &base64_stream_index,
		  0,
	          0x000000ffUL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid alphabet
	 */
	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          base64_stream,
	          32,
		  &base64_stream_index,
		  0,
	          0x000f0000UL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid encoding
	 */
	result = libuna_base64_triplet_copy_to_base64_stream(
	          0x00546869UL,
	          base64_stream,
	          32,
		  &base64_stream_index,
		  0,
	          0xf0000000UL | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_index",
	 base64_stream_index,
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

/* Tests the libuna_base64_triplet_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_triplet_copy_from_byte_stream(
     void )
{
	libcerror_error_t *error = NULL;
	size_t byte_stream_index = 0;
	uint32_t base64_triplet  = 0;
	uint8_t padding_size     = 0;
	int result               = 0;

	/* Test regular cases
	 */
	base64_triplet    = 0;
	byte_stream_index = 0;
	padding_size      = 0;

	result = libuna_base64_triplet_copy_from_byte_stream(
	          &base64_triplet,
	          una_test_base64_stream_byte_stream,
	          16,
		  &byte_stream_index,
		  &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0x00546869UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 3 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	base64_triplet    = 0;
	byte_stream_index = 0;
	padding_size      = 0;

	result = libuna_base64_triplet_copy_from_byte_stream(
	          NULL,
	          una_test_base64_stream_byte_stream,
	          16,
		  &byte_stream_index,
		  &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_triplet_copy_from_byte_stream(
	          &base64_triplet,
	          NULL,
	          16,
		  &byte_stream_index,
		  &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_triplet_copy_from_byte_stream(
	          &base64_triplet,
	          una_test_base64_stream_byte_stream,
	          (size_t) SSIZE_MAX + 1,
		  &byte_stream_index,
		  &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_triplet_copy_from_byte_stream(
	          &base64_triplet,
	          una_test_base64_stream_byte_stream,
	          16,
		  NULL,
		  &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	byte_stream_index = 16;

	result = libuna_base64_triplet_copy_from_byte_stream(
	          &base64_triplet,
	          una_test_base64_stream_byte_stream,
	          16,
		  &byte_stream_index,
		  &padding_size,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 16 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
	 0 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	byte_stream_index = 0;

	result = libuna_base64_triplet_copy_from_byte_stream(
	          &base64_triplet,
	          una_test_base64_stream_byte_stream,
	          16,
		  &byte_stream_index,
		  NULL,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "base64_triplet",
	 base64_triplet,
	 (uint32_t) 0 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 0 );

	UNA_TEST_ASSERT_EQUAL_UINT8(
	 "padding_size",
	 padding_size,
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

/* Tests the libuna_base64_triplet_copy_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_triplet_copy_to_byte_stream(
     void )
{
	uint8_t byte_stream[ 32 ];

	libcerror_error_t *error = NULL;
	size_t byte_stream_index = 0;
	int result               = 0;

	/* Test regular cases
	 */
	byte_stream_index = 0;

	result = libuna_base64_triplet_copy_to_byte_stream(
	          0x00546869UL,
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
	 (size_t) 3 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	byte_stream_index = 0;

	result = libuna_base64_triplet_copy_to_byte_stream(
	          0x00546869UL,
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

	result = libuna_base64_triplet_copy_to_byte_stream(
	          0x00546869UL,
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

	result = libuna_base64_triplet_copy_to_byte_stream(
	          0x00546869UL,
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

	byte_stream_index = 32;

	result = libuna_base64_triplet_copy_to_byte_stream(
	          0x00546869UL,
	          byte_stream,
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
	 (size_t) 32 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	byte_stream_index = 0;

	result = libuna_base64_triplet_copy_to_byte_stream(
	          0x00546869UL,
	          byte_stream,
	          32,
		  &byte_stream_index,
		  3,
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

/* Tests the libuna_base64_stream_size_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_stream_size_to_byte_stream(
     void )
{
	libcerror_error_t *error = NULL;
	size_t byte_stream_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	byte_stream_size = 0;

	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &byte_stream_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_utf16be_stream,
	          48,
		  &byte_stream_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_utf16le_stream,
	          48,
		  &byte_stream_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_utf32be_stream,
	          96,
		  &byte_stream_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_utf32le_stream,
	          96,
		  &byte_stream_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	/* Test error cases
	 */
	byte_stream_size = 0;

	result = libuna_base64_stream_size_to_byte_stream(
	          NULL,
		  24,
		  &byte_stream_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
		  (size_t) SSIZE_MAX + 1,
		  &byte_stream_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
		  24,
	          NULL,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	byte_stream_size = 0;

	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
	          25,
		  &byte_stream_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_64 | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	/* Invalid character limit
	 */
	byte_stream_size = 0;

	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
		  24,
		  &byte_stream_size,
	          0x000000ffUL,
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
	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &byte_stream_size,
	          0x000f0000UL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
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
	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &byte_stream_size,
	          0xf0000000UL | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
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
	result = libuna_base64_stream_size_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  &byte_stream_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_base64_stream_copy_to_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_stream_copy_to_byte_stream(
     void )
{
	uint8_t byte_stream[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_base64_stream_copy_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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
	          una_test_base64_stream_byte_stream,
	          16 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_base64_stream_copy_to_byte_stream(
	          NULL,
		  24,
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

	result = libuna_base64_stream_copy_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
		  (size_t) SSIZE_MAX + 1,
		  byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base64_stream_copy_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
		  24,
	          NULL,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	result = libuna_base64_stream_copy_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
		  24,
		  byte_stream,
		  (size_t) SSIZE_MAX + 1,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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
	result = libuna_base64_stream_copy_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
		  24,
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

	/* Invalid alphabet
	 */
	result = libuna_base64_stream_copy_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
		  24,
		  byte_stream,
		  16,
	          0x000f0000UL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
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
	result = libuna_base64_stream_copy_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
		  24,
		  byte_stream,
		  16,
	          0xf0000000UL | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
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
	result = libuna_base64_stream_copy_to_byte_stream(
	          una_test_base64_stream_rfc1421_byte_stream,
	          24,
		  byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_base64_stream_size_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_stream_size_from_byte_stream(
     void )
{
	libcerror_error_t *error  = NULL;
	size_t base64_stream_size = 0;
	int result                = 0;

	/* Test regular cases
	 */
	base64_stream_size = 0;

	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  &base64_stream_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_size",
	 base64_stream_size,
	 (size_t) 24 );

	base64_stream_size = 0;

	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  &base64_stream_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_size",
	 base64_stream_size,
	 (size_t) 48 );

	base64_stream_size = 0;

	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  &base64_stream_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_size",
	 base64_stream_size,
	 (size_t) 48 );

	base64_stream_size = 0;

	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  &base64_stream_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_size",
	 base64_stream_size,
	 (size_t) 96 );

	base64_stream_size = 0;

	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  &base64_stream_size,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_size",
	 base64_stream_size,
	 (size_t) 96 );

	base64_stream_size = 0;

	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  &base64_stream_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_64 | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "base64_stream_size",
	 base64_stream_size,
	 (size_t) 25 );

	/* Test error cases
	 */
	base64_stream_size = 0;

	result = libuna_base64_stream_size_from_byte_stream(
		  NULL,
		  16,
		  &base64_stream_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  (size_t) SSIZE_MAX + 1,
		  &base64_stream_size,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  NULL,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
	          &error );

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
	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  &base64_stream_size,
	          0x000000ffUL,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid alphabet
	 */
	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  &base64_stream_size,
	          0x000f0000UL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

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
	result = libuna_base64_stream_size_from_byte_stream(
		  una_test_base64_stream_byte_stream,
		  16,
		  &base64_stream_size,
	          0xf0000000UL | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

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

/* Tests the libuna_base64_stream_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_stream_copy_from_byte_stream(
     void )
{
	uint8_t base64_stream[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libuna_base64_stream_copy_from_byte_stream(
		  base64_stream,
		  24,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base64_stream,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libuna_base64_stream_copy_from_byte_stream(
	          NULL,
		  24,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
	          &error );

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

/* Tests the libuna_base64_stream_with_index_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_base64_stream_with_index_copy_from_byte_stream(
     void )
{
	uint8_t base64_stream[ 256 ];

	libcerror_error_t *error   = NULL;
	size_t base64_stream_index = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	base64_stream_index = 0;

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
		  base64_stream,
		  24,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base64_stream,
	          una_test_base64_stream_rfc1421_byte_stream,
	          24 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base64_stream_index = 0;

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
		  base64_stream,
		  48,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF16_BIG_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base64_stream,
	          una_test_base64_stream_rfc1421_utf16be_stream,
	          48 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base64_stream_index = 0;

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
		  base64_stream,
		  48,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base64_stream,
	          una_test_base64_stream_rfc1421_utf16le_stream,
	          48 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base64_stream_index = 0;

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
		  base64_stream,
		  96,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF32_BIG_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base64_stream,
	          una_test_base64_stream_rfc1421_utf32be_stream,
	          96 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base64_stream_index = 0;

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
		  base64_stream,
		  96,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base64_stream,
	          una_test_base64_stream_rfc1421_utf32le_stream,
	          96 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	base64_stream_index = 0;

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
		  base64_stream,
		  25,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_64 | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          base64_stream,
	          una_test_base64_stream_rfc1421_byte_stream,
	          25 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	base64_stream_index = 0;

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
	          NULL,
		  25,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
	          base64_stream,
		  (size_t) SSIZE_MAX + 1,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
	          base64_stream,
		  25,
		  NULL,
		  una_test_base64_stream_byte_stream,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
	          base64_stream,
		  25,
		  &base64_stream_index,
		  NULL,
		  16,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_base64_stream_with_index_copy_from_byte_stream(
	          base64_stream,
		  25,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  (size_t) SSIZE_MAX + 1,
	          LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE | LIBUNA_BASE64_VARIANT_PADDING_REQUIRED,
	          &error );

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
	result = libuna_base64_stream_with_index_copy_from_byte_stream(
	          base64_stream,
		  25,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          0x000000ffUL,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Invalid alphabet
	 */
	result = libuna_base64_stream_with_index_copy_from_byte_stream(
	          base64_stream,
		  25,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          0x000f0000UL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

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
	result = libuna_base64_stream_with_index_copy_from_byte_stream(
	          base64_stream,
		  25,
		  &base64_stream_index,
		  una_test_base64_stream_byte_stream,
		  16,
	          0xf0000000UL | LIBUNA_BASE64_VARIANT_ALPHABET_NORMAL | LIBUNA_BASE64_VARIANT_CHARACTER_LIMIT_NONE,
	          &error );

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
	 "libuna_base64_character_copy_to_sixtet",
	 una_test_base64_character_copy_to_sixtet );

#endif /* defined( __GNUC__ ) && !defined( LIBUNA_DLL_IMPORT ) */

	UNA_TEST_RUN(
	 "libuna_base64_triplet_copy_from_base64_stream",
	 una_test_base64_triplet_copy_from_base64_stream );

	UNA_TEST_RUN(
	 "libuna_base64_triplet_copy_to_base64_stream",
	 una_test_base64_triplet_copy_to_base64_stream );

	UNA_TEST_RUN(
	 "libuna_base64_triplet_copy_from_byte_stream",
	 una_test_base64_triplet_copy_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base64_triplet_copy_to_byte_stream",
	 una_test_base64_triplet_copy_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base64_stream_size_to_byte_stream",
	 una_test_base64_stream_size_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base64_stream_copy_to_byte_stream",
	 una_test_base64_stream_copy_to_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base64_stream_size_from_byte_stream",
	 una_test_base64_stream_size_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base64_stream_copy_from_byte_stream",
	 una_test_base64_stream_copy_from_byte_stream );

	UNA_TEST_RUN(
	 "libuna_base64_stream_with_index_copy_from_byte_stream",
	 una_test_base64_stream_with_index_copy_from_byte_stream );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

