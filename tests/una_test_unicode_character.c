/*
 * Library unicode_character functions test program
 *
 * Copyright (C) 2008-2022, Joachim Metz <joachim.metz@gmail.com>
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
#include "una_test_codepage_mac_arabic.h"
#include "una_test_codepage_mac_celtic.h"
#include "una_test_codepage_mac_centraleurroman.h"
#include "una_test_codepage_mac_croatian.h"
#include "una_test_codepage_mac_cyrillic.h"
#include "una_test_codepage_mac_dingbats.h"
#include "una_test_codepage_mac_farsi.h"
#include "una_test_codepage_mac_gaelic.h"
#include "una_test_codepage_mac_greek.h"
#include "una_test_codepage_mac_icelandic.h"
#include "una_test_codepage_mac_inuit.h"
#include "una_test_codepage_mac_roman.h"
#include "una_test_codepage_mac_romanian.h"
#include "una_test_codepage_mac_russian.h"
#include "una_test_codepage_mac_symbol.h"
#include "una_test_codepage_mac_thai.h"
#include "una_test_codepage_mac_turkish.h"
#include "una_test_codepage_mac_ukrainian.h"
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

#define UNA_TEST_UNICODE_CHARACTER_NUMBER_OF_CODEPAGES	50

una_test_unicode_character_codepage_t una_test_unicode_character_codepages[ UNA_TEST_UNICODE_CHARACTER_NUMBER_OF_CODEPAGES ] = {
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
	{ LIBUNA_CODEPAGE_MAC_ARABIC, 256, una_test_codepage_mac_arabic_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_CELTIC, 256, una_test_codepage_mac_celtic_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_CENTRALEURROMAN, 256, una_test_codepage_mac_centraleurroman_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_CROATIAN, 256, una_test_codepage_mac_croatian_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_CYRILLIC, 256, una_test_codepage_mac_cyrillic_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_DINGBATS, 235, una_test_codepage_mac_dingbats_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_FARSI, 256, una_test_codepage_mac_farsi_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_GAELIC, 256, una_test_codepage_mac_gaelic_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_GREEK, 256, una_test_codepage_mac_greek_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_ICELANDIC, 256, una_test_codepage_mac_icelandic_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_INUIT, 256, una_test_codepage_mac_inuit_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_ROMAN, 256, una_test_codepage_mac_roman_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_ROMANIAN, 256, una_test_codepage_mac_romanian_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_RUSSIAN, 256, una_test_codepage_mac_russian_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_SYMBOL, 223, una_test_codepage_mac_symbol_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_THAI, 250, una_test_codepage_mac_thai_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_TURKISH, 256, una_test_codepage_mac_turkish_byte_stream_to_unicode },
	{ LIBUNA_CODEPAGE_MAC_UKRAINIAN, 256, una_test_codepage_mac_ukrainian_byte_stream_to_unicode },
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
	     codepage_number < UNA_TEST_UNICODE_CHARACTER_NUMBER_OF_CODEPAGES;
	     codepage_number++ )
	{
		test_codepage = &( una_test_unicode_character_codepages[ codepage_number ] );

		for( test_number = 0;
		     test_number < test_codepage->number_of_test_values;
		     test_number++ )
		{
			test_values = &( test_codepage->test_values[ test_number ] );

			if( test_values->flags != 0 )
			{
				continue;
			}
			byte_stream_character_size = 0;

			result = libuna_unicode_character_size_to_byte_stream(
				  test_values->unicode_character,
				  test_codepage->codepage,
				  &byte_stream_character_size,
				  &error );

fprintf( stdout, "X: 0x%08x\n", test_values->unicode_character );

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
	uint8_t byte_stream1[ 2 ]                            = { 'A', 0 };

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
	     codepage_number < UNA_TEST_UNICODE_CHARACTER_NUMBER_OF_CODEPAGES;
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
	byte_stream_index = 0;

	result = libuna_unicode_character_copy_from_byte_stream(
		  &unicode_character,
		  (uint8_t *) "\x80",
		  1,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ASCII,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x0000fffdUL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_from_byte_stream(
		  &unicode_character,
		  (uint8_t *) "\xdb",
		  1,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_11,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x0000fffdUL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "byte_stream_index",
	 byte_stream_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_from_byte_stream(
		  &unicode_character,
		  (uint8_t *) "\xfc",
		  1,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_11,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x0000fffdUL );

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

	result = libuna_unicode_character_copy_from_byte_stream(
	          NULL,
	          byte_stream1,
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
	          byte_stream1,
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
	          byte_stream1,
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
	          byte_stream1,
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

	uint8_t expected_byte_stream1[ 2 ]                   = { 0x1a, 0 };

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
	     codepage_number < UNA_TEST_UNICODE_CHARACTER_NUMBER_OF_CODEPAGES;
	     codepage_number++ )
	{
		test_codepage = &( una_test_unicode_character_codepages[ codepage_number ] );

		for( test_number = 0;
		     test_number < test_codepage->number_of_test_values;
		     test_number++ )
		{
			test_values = &( test_codepage->test_values[ test_number ] );

			if( test_values->flags != 0 )
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
	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x00000080UL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ASCII,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x00000100UL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_1,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x000002c8UL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_2,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x000002daUL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_3,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x000002dcUL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_4,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x00002117UL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_5,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x0000060dUL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_6,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x000020b0UL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_7,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x00002018UL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_8,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x00000160UL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_9,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x00002016UL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_10,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	byte_stream_index = 0;

	result = libuna_unicode_character_copy_to_byte_stream(
		  0x00000e5cUL,
		  byte_stream,
		  16,
		  &byte_stream_index,
		  LIBUNA_CODEPAGE_ISO_8859_11,
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

	result = memory_compare(
		  expected_byte_stream1,
		  byte_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

/* TODO add more tests for replacement characters continue with LIBUNA_CODEPAGE_ISO_8859_13 */

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

	byte_stream_index = 16;

	result = libuna_unicode_character_copy_to_byte_stream(
	          0x00000041UL,
	          byte_stream,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libuna_unicode_character_size_to_utf7_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_size_to_utf7_stream(
     void )
{
	libuna_error_t *error             = NULL;
	size_t utf7_stream_character_size = 0;
	uint32_t utf7_stream_base64_data  = 0;
	int result                        = 0;

	/* Test regular cases
	 */
	utf7_stream_character_size = 0;
	utf7_stream_base64_data    = 0;

	result = libuna_unicode_character_size_to_utf7_stream(
	          0x00000041UL,
	          &utf7_stream_character_size,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf7_stream_character_size",
	 utf7_stream_character_size,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf7_stream_character_size = 0;
	utf7_stream_base64_data    = 0;

	result = libuna_unicode_character_size_to_utf7_stream(
	          0x0001f9eaUL,
	          &utf7_stream_character_size,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf7_stream_character_size",
	 utf7_stream_character_size,
	 (size_t) 8 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf7_stream_character_size = 0;
	utf7_stream_base64_data    = 0;

	result = libuna_unicode_character_size_to_utf7_stream(
	          0x00000041UL,
	          NULL,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_size_to_utf7_stream(
	          0x00000041UL,
	          &utf7_stream_character_size,
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

/* Tests the libuna_unicode_character_copy_from_utf7_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_from_utf7_stream(
     void )
{
	uint8_t utf7_stream1[ 2 ]                    = { 'A', 0 };
	uint8_t utf7_stream2[ 9 ]                    = { '+', '2', 'D', '7', 'd', '6', 'g', '-', 0 };

	libuna_error_t *error                        = NULL;
	libuna_unicode_character_t unicode_character = 0;
	size_t utf7_stream_index                     = 0;
	uint32_t utf7_stream_base64_data             = 0;
	int result                                   = 0;

	/* Test regular cases
	 */
	utf7_stream_index       = 0;
	utf7_stream_base64_data = 0;

	result = libuna_unicode_character_copy_from_utf7_stream(
	          &unicode_character,
	          utf7_stream1,
	          1,
	          &utf7_stream_index,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x00000041UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf7_stream_index",
	 utf7_stream_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf7_stream_index       = 0;
	utf7_stream_base64_data = 0;

	result = libuna_unicode_character_copy_from_utf7_stream(
	          &unicode_character,
	          utf7_stream2,
	          8,
	          &utf7_stream_index,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x0001f9eaUL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf7_stream_index",
	 utf7_stream_index,
	 (size_t) 8 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf7_stream_index       = 0;
	utf7_stream_base64_data = 0;

	result = libuna_unicode_character_copy_from_utf7_stream(
	          NULL,
	          utf7_stream1,
	          1,
	          &utf7_stream_index,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf7_stream(
	          &unicode_character,
	          NULL,
	          1,
	          &utf7_stream_index,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf7_stream(
	          &unicode_character,
	          utf7_stream1,
	          (size_t) SSIZE_MAX + 1,
	          &utf7_stream_index,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf7_stream(
	          &unicode_character,
	          utf7_stream1,
	          1,
	          NULL,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf7_stream(
	          &unicode_character,
	          utf7_stream1,
	          1,
	          &utf7_stream_index,
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

/* Tests the libuna_unicode_character_copy_to_utf7_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_to_utf7_stream(
     void )
{
	uint8_t utf7_stream[ 16 ];

	uint8_t expected_utf7_stream1[ 2 ] = { 'A', 0 };
	uint8_t expected_utf7_stream2[ 9 ] = { '+', '2', 'D', '7', 'd', '6', 'g', '-', 0 };

	libuna_error_t *error              = NULL;
	size_t utf7_stream_index           = 0;
	uint32_t utf7_stream_base64_data   = 0;
	int result                         = 0;

	/* Test regular cases
	 */
	utf7_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf7_stream(
		  0x00000041UL,
		  utf7_stream,
		  16,
		  &utf7_stream_index,
		  &utf7_stream_base64_data,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf7_stream_index",
	 utf7_stream_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf7_stream1,
		  utf7_stream,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf7_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf7_stream(
		  0x0001f9eaUL,
		  utf7_stream,
		  16,
		  &utf7_stream_index,
		  &utf7_stream_base64_data,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf7_stream_index",
	 utf7_stream_index,
	 (size_t) 8 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf7_stream2,
		  utf7_stream,
		  8 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf7_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf7_stream(
	          0x00000041UL,
	          NULL,
	          16,
	          &utf7_stream_index,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_to_utf7_stream(
	          0x00000041UL,
	          utf7_stream,
	          (size_t) SSIZE_MAX + 1,
	          &utf7_stream_index,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_to_utf7_stream(
	          0x00000041UL,
	          utf7_stream,
	          16,
	          NULL,
	          &utf7_stream_base64_data,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_to_utf7_stream(
	          0x00000041UL,
	          utf7_stream,
	          16,
	          &utf7_stream_index,
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

/* Tests the libuna_unicode_character_size_to_utf8 function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_size_to_utf8(
     void )
{
	libuna_error_t *error      = NULL;
	size_t utf8_character_size = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	utf8_character_size = 0;

	result = libuna_unicode_character_size_to_utf8(
	          0x00000041UL,
	          &utf8_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_character_size",
	 utf8_character_size,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_character_size = 0;

	result = libuna_unicode_character_size_to_utf8(
	          0x00000080UL,
	          &utf8_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_character_size",
	 utf8_character_size,
	 (size_t) 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_character_size = 0;

	result = libuna_unicode_character_size_to_utf8(
	          0x00000800UL,
	          &utf8_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_character_size",
	 utf8_character_size,
	 (size_t) 3 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_character_size = 0;

	result = libuna_unicode_character_size_to_utf8(
	          0x00010000UL,
	          &utf8_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_character_size",
	 utf8_character_size,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_character_size = 0;

	result = libuna_unicode_character_size_to_utf8(
	          0x0001f9eaUL,
	          &utf8_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_character_size",
	 utf8_character_size,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_character_size = 0;

	result = libuna_unicode_character_size_to_utf8(
	          LIBUNA_UNICODE_CHARACTER_MAX + 1,
	          &utf8_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_character_size",
	 utf8_character_size,
	 (size_t) 3 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf8_character_size = 0;

	result = libuna_unicode_character_size_to_utf8(
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

/* Tests the libuna_unicode_character_copy_from_utf8 function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_from_utf8(
     void )
{
	uint8_t utf8_stream1[ 2 ]                    = { 'A', 0 };
	uint8_t utf8_stream2[ 5 ]                    = { 0xf0, 0x9f, 0xa7, 0xaa, 0 };

	libuna_error_t *error                        = NULL;
	libuna_unicode_character_t unicode_character = 0;
	size_t utf8_string_index                     = 0;
	int result                                   = 0;

	/* Test regular cases
	 */
	utf8_string_index = 0;

	result = libuna_unicode_character_copy_from_utf8(
	          &unicode_character,
	          utf8_stream1,
	          1,
	          &utf8_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x00000041UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_string_index = 0;

	result = libuna_unicode_character_copy_from_utf8(
	          &unicode_character,
	          utf8_stream2,
	          4,
	          &utf8_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x0001f9eaUL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf8_string_index = 0;

	result = libuna_unicode_character_copy_from_utf8(
	          NULL,
	          utf8_stream1,
	          1,
	          &utf8_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf8(
	          &unicode_character,
	          NULL,
	          1,
	          &utf8_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf8(
	          &unicode_character,
	          utf8_stream1,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf8(
	          &unicode_character,
	          utf8_stream1,
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

	utf8_string_index = 1;

	result = libuna_unicode_character_copy_from_utf8(
	          &unicode_character,
	          utf8_stream1,
	          1,
	          &utf8_string_index,
	          &error );

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

/* Tests the libuna_unicode_character_copy_to_utf8 function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_to_utf8(
     void )
{
	uint8_t utf8_string[ 16 ];

	uint8_t expected_utf8_stream1[ 2 ] = { 'A', 0 };
	uint8_t expected_utf8_stream2[ 5 ] = { 0xf0, 0x9f, 0xa7, 0xaa, 0 };

	libuna_error_t *error              = NULL;
	size_t utf8_string_index           = 0;
	int result                         = 0;

	/* Test regular cases
	 */
	utf8_string_index = 0;

	result = libuna_unicode_character_copy_to_utf8(
		  0x00000041UL,
		  utf8_string,
		  16,
		  &utf8_string_index,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf8_stream1,
		  utf8_string,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf8_string_index = 0;

	result = libuna_unicode_character_copy_to_utf8(
		  0x0001f9eaUL,
		  utf8_string,
		  16,
		  &utf8_string_index,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf8_stream2,
		  utf8_string,
		  4 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf8_string_index = 0;

	result = libuna_unicode_character_copy_to_utf8(
	          0x00000041UL,
	          NULL,
	          16,
	          &utf8_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_to_utf8(
	          0x00000041UL,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_to_utf8(
	          0x00000041UL,
	          utf8_string,
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

/* Tests the libuna_unicode_character_size_to_utf16 function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_size_to_utf16(
     void )
{
	libuna_error_t *error              = NULL;
	size_t utf16_string_character_size = 0;
	int result                         = 0;

	/* Test regular cases
	 */
	utf16_string_character_size = 0;

	result = libuna_unicode_character_size_to_utf16(
	          0x00000041UL,
	          &utf16_string_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_character_size",
	 utf16_string_character_size,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_string_character_size = 0;

	result = libuna_unicode_character_size_to_utf16(
	          0x0001f9eaUL,
	          &utf16_string_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_character_size",
	 utf16_string_character_size,
	 (size_t) 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_unicode_character_size_to_utf16(
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

/* Tests the libuna_unicode_character_copy_from_utf16 function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_from_utf16(
     void )
{
	uint16_t utf16_string1[ 2 ]                  = { 'A', 0 };
	uint16_t utf16_string2[ 3 ]                  = { 0xd83e, 0xddea, 0 };

	libuna_error_t *error                        = NULL;
	libuna_unicode_character_t unicode_character = 0;
	size_t utf16_string_index                    = 0;
	int result                                   = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_unicode_character_copy_from_utf16(
	          &unicode_character,
	          utf16_string1,
	          1,
	          &utf16_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x00000041UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_string_index = 0;

	result = libuna_unicode_character_copy_from_utf16(
	          &unicode_character,
	          utf16_string2,
	          2,
	          &utf16_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x0001f9eaUL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_unicode_character_copy_from_utf16(
	          NULL,
	          utf16_string1,
	          1,
	          &utf16_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf16(
	          &unicode_character,
	          NULL,
	          1,
	          &utf16_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf16(
	          &unicode_character,
	          utf16_string1,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf16(
	          &unicode_character,
	          utf16_string1,
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

	utf16_string_index = 1;

	result = libuna_unicode_character_copy_from_utf16(
	          &unicode_character,
	          utf16_string1,
	          1,
	          &utf16_string_index,
	          &error );

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

/* Tests the libuna_unicode_character_copy_to_utf16 function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_to_utf16(
     void )
{
	uint16_t utf16_string[ 16 ];

	uint16_t expected_utf16_string1[ 2 ] = { 'A', 0 };
	uint16_t expected_utf16_string2[ 3 ] = { 0xd83e, 0xddea, 0 };

	libuna_error_t *error                = NULL;
	size_t utf16_string_index            = 0;
	int result                           = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libuna_unicode_character_copy_to_utf16(
		  0x00000041UL,
		  utf16_string,
		  16,
		  &utf16_string_index,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf16_string1,
		  utf16_string,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_string_index = 0;

	result = libuna_unicode_character_copy_to_utf16(
		  0x0001f9eaUL,
		  utf16_string,
		  16,
		  &utf16_string_index,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf16_string2,
		  utf16_string,
		  2 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libuna_unicode_character_copy_to_utf16(
	          0x00000041UL,
	          NULL,
	          16,
	          &utf16_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_to_utf16(
	          0x00000041UL,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_to_utf16(
	          0x00000041UL,
	          utf16_string,
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

/* Tests the libuna_unicode_character_copy_from_utf16_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_from_utf16_stream(
     void )
{
	uint8_t utf16_stream1[ 4 ]                   = { 0, 'A', 0, 0 };
	uint8_t utf16_stream2[ 4 ]                   = { 'A', 0, 0, 0 };
	uint8_t utf16_stream3[ 6 ]                   = { 0x3e, 0xd8, 0xea, 0xdd, 0, 0 };

	libuna_error_t *error                        = NULL;
	libuna_unicode_character_t unicode_character = 0;
	size_t utf16_stream_index                    = 0;
	int result                                   = 0;

	/* Test regular cases
	 */
	utf16_stream_index = 0;

	result = libuna_unicode_character_copy_from_utf16_stream(
	          &unicode_character,
	          utf16_stream1,
	          2,
	          &utf16_stream_index,
	          LIBUNA_ENDIAN_BIG,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x00000041UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_stream_index",
	 utf16_stream_index,
	 (size_t) 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_stream_index = 0;

	result = libuna_unicode_character_copy_from_utf16_stream(
	          &unicode_character,
	          utf16_stream2,
	          2,
	          &utf16_stream_index,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x00000041UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_stream_index",
	 utf16_stream_index,
	 (size_t) 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_stream_index = 0;

	result = libuna_unicode_character_copy_from_utf16_stream(
	          &unicode_character,
	          utf16_stream3,
	          4,
	          &utf16_stream_index,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x0001f9eaUL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_stream_index",
	 utf16_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf16_stream_index = 0;

	result = libuna_unicode_character_copy_from_utf16_stream(
	          NULL,
	          utf16_stream2,
	          2,
	          &utf16_stream_index,
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

	result = libuna_unicode_character_copy_from_utf16_stream(
	          &unicode_character,
	          NULL,
	          2,
	          &utf16_stream_index,
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

	result = libuna_unicode_character_copy_from_utf16_stream(
	          &unicode_character,
	          utf16_stream2,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_stream_index,
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

	result = libuna_unicode_character_copy_from_utf16_stream(
	          &unicode_character,
	          utf16_stream2,
	          2,
	          NULL,
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

	result = libuna_unicode_character_copy_from_utf16_stream(
	          &unicode_character,
	          utf16_stream2,
	          2,
	          &utf16_stream_index,
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

	utf16_stream_index = 2;

	result = libuna_unicode_character_copy_from_utf16_stream(
	          &unicode_character,
	          utf16_stream2,
	          2,
	          &utf16_stream_index,
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

/* Tests the libuna_unicode_character_copy_to_utf16_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_to_utf16_stream(
     void )
{
	uint8_t utf16_stream[ 16 ];

	uint8_t expected_utf16_stream1[ 4 ] = { 0, 'A', 0, 0 };
	uint8_t expected_utf16_stream2[ 4 ] = { 'A', 0, 0, 0 };
	uint8_t expexted_utf16_stream3[ 6 ] = { 0x3e, 0xd8, 0xea, 0xdd, 0, 0 };

	libuna_error_t *error               = NULL;
	size_t utf16_stream_index           = 0;
	int result                          = 0;

	/* Test regular cases
	 */
	utf16_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf16_stream(
		  0x00000041UL,
		  utf16_stream,
		  16,
		  &utf16_stream_index,
		  LIBUNA_ENDIAN_BIG,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_stream_index",
	 utf16_stream_index,
	 (size_t) 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf16_stream1,
		  utf16_stream,
		  2 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf16_stream(
		  0x00000041UL,
		  utf16_stream,
		  16,
		  &utf16_stream_index,
		  LIBUNA_ENDIAN_LITTLE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_stream_index",
	 utf16_stream_index,
	 (size_t) 2 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf16_stream2,
		  utf16_stream,
		  2 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf16_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf16_stream(
		  0x0001f9eaUL,
		  utf16_stream,
		  16,
		  &utf16_stream_index,
		  LIBUNA_ENDIAN_LITTLE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_stream_index",
	 utf16_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expexted_utf16_stream3,
		  utf16_stream,
		  4 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf16_stream(
	          0x00000041UL,
	          NULL,
	          16,
	          &utf16_stream_index,
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

	result = libuna_unicode_character_copy_to_utf16_stream(
	          0x00000041UL,
	          utf16_stream,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_stream_index,
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

	result = libuna_unicode_character_copy_to_utf16_stream(
	          0x00000041UL,
	          utf16_stream,
	          16,
	          NULL,
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

	result = libuna_unicode_character_copy_to_utf16_stream(
	          0x00000041UL,
	          utf16_stream,
	          16,
	          &utf16_stream_index,
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

	utf16_stream_index = 16;

	result = libuna_unicode_character_copy_to_utf16_stream(
	          0x00000041UL,
	          utf16_stream,
	          16,
	          &utf16_stream_index,
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

/* Tests the libuna_unicode_character_size_to_utf32 function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_size_to_utf32(
     void )
{
	libuna_error_t *error              = NULL;
	size_t utf32_string_character_size = 0;
	int result                         = 0;

	/* Test regular cases
	 */
	utf32_string_character_size = 0;

	result = libuna_unicode_character_size_to_utf32(
	          0x00000041UL,
	          &utf32_string_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_string_character_size",
	 utf32_string_character_size,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf32_string_character_size = 0;

	result = libuna_unicode_character_size_to_utf32(
	          0x0001f9eaUL,
	          &utf32_string_character_size,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_string_character_size",
	 utf32_string_character_size,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libuna_unicode_character_size_to_utf32(
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

/* Tests the libuna_unicode_character_copy_from_utf32 function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_from_utf32(
     void )
{
	uint32_t utf32_string1[ 2 ]                  = { 'A', 0 };
	uint32_t utf32_string2[ 3 ]                  = { 0x0001f9ea, 0 };

	libuna_error_t *error                        = NULL;
	libuna_unicode_character_t unicode_character = 0;
	size_t utf32_string_index                    = 0;
	int result                                   = 0;

	/* Test regular cases
	 */
	utf32_string_index = 0;

	result = libuna_unicode_character_copy_from_utf32(
	          &unicode_character,
	          utf32_string1,
	          1,
	          &utf32_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x00000041UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_string_index",
	 utf32_string_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf32_string_index = 0;

	result = libuna_unicode_character_copy_from_utf32(
	          &unicode_character,
	          utf32_string2,
	          1,
	          &utf32_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x0001f9eaUL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_string_index",
	 utf32_string_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf32_string_index = 0;

	result = libuna_unicode_character_copy_from_utf32(
	          NULL,
	          utf32_string1,
	          1,
	          &utf32_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf32(
	          &unicode_character,
	          NULL,
	          1,
	          &utf32_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf32(
	          &unicode_character,
	          utf32_string1,
	          (size_t) SSIZE_MAX + 1,
	          &utf32_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_from_utf32(
	          &unicode_character,
	          utf32_string1,
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

	utf32_string_index = 1;

	result = libuna_unicode_character_copy_from_utf32(
	          &unicode_character,
	          utf32_string1,
	          1,
	          &utf32_string_index,
	          &error );

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

/* Tests the libuna_unicode_character_copy_to_utf32 function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_to_utf32(
     void )
{
	uint32_t utf32_string[ 16 ];

	uint32_t expected_utf32_string1[ 2 ] = { 'A', 0 };
	uint32_t expected_utf32_string2[ 2 ] = { 0x0001f9ea, 0 };

	libuna_error_t *error                = NULL;
	size_t utf32_string_index            = 0;
	int result                           = 0;

	/* Test regular cases
	 */
	utf32_string_index = 0;

	result = libuna_unicode_character_copy_to_utf32(
		  0x00000041UL,
		  utf32_string,
		  16,
		  &utf32_string_index,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_string_index",
	 utf32_string_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf32_string1,
		  utf32_string,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf32_string_index = 0;

	result = libuna_unicode_character_copy_to_utf32(
		  0x0001f9eaUL,
		  utf32_string,
		  16,
		  &utf32_string_index,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_string_index",
	 utf32_string_index,
	 (size_t) 1 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf32_string2,
		  utf32_string,
		  1 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf32_string_index = 0;

	result = libuna_unicode_character_copy_to_utf32(
	          0x00000041UL,
	          NULL,
	          16,
	          &utf32_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_to_utf32(
	          0x00000041UL,
	          utf32_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf32_string_index,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	UNA_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libuna_unicode_character_copy_to_utf32(
	          0x00000041UL,
	          utf32_string,
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

/* Tests the libuna_unicode_character_copy_from_utf32_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_from_utf32_stream(
     void )
{
	uint8_t utf32_stream1[ 8 ]                   = { 0, 0, 0, 'A', 0, 0, 0, 0 };
	uint8_t utf32_stream2[ 8 ]                   = { 'A', 0, 0, 0, 0, 0, 0, 0 };
	uint8_t utf32_stream3[ 8 ]                   = { 0xea, 0xf9, 0x01, 0x00, 0, 0, 0, 0 };

	libuna_error_t *error                        = NULL;
	libuna_unicode_character_t unicode_character = 0;
	size_t utf32_stream_index                    = 0;
	int result                                   = 0;

	/* Test regular cases
	 */
	utf32_stream_index = 0;

	result = libuna_unicode_character_copy_from_utf32_stream(
	          &unicode_character,
	          utf32_stream1,
	          4,
	          &utf32_stream_index,
	          LIBUNA_ENDIAN_BIG,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x00000041UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_stream_index",
	 utf32_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf32_stream_index = 0;

	result = libuna_unicode_character_copy_from_utf32_stream(
	          &unicode_character,
	          utf32_stream2,
	          4,
	          &utf32_stream_index,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x00000041UL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_stream_index",
	 utf32_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf32_stream_index = 0;

	result = libuna_unicode_character_copy_from_utf32_stream(
	          &unicode_character,
	          utf32_stream3,
	          4,
	          &utf32_stream_index,
	          LIBUNA_ENDIAN_LITTLE,
	          &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_UINT32(
	 "unicode_character",
	 unicode_character,
	 (uint32_t) 0x0001f9eaUL );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_stream_index",
	 utf32_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf32_stream_index = 0;

	result = libuna_unicode_character_copy_from_utf32_stream(
	          NULL,
	          utf32_stream2,
	          4,
	          &utf32_stream_index,
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

	result = libuna_unicode_character_copy_from_utf32_stream(
	          &unicode_character,
	          NULL,
	          4,
	          &utf32_stream_index,
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

	result = libuna_unicode_character_copy_from_utf32_stream(
	          &unicode_character,
	          utf32_stream2,
	          (size_t) SSIZE_MAX + 1,
	          &utf32_stream_index,
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

	result = libuna_unicode_character_copy_from_utf32_stream(
	          &unicode_character,
	          utf32_stream2,
	          4,
	          NULL,
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

	result = libuna_unicode_character_copy_from_utf32_stream(
	          &unicode_character,
	          utf32_stream2,
	          4,
	          &utf32_stream_index,
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

	utf32_stream_index = 4;

	result = libuna_unicode_character_copy_from_utf32_stream(
	          &unicode_character,
	          utf32_stream2,
	          4,
	          &utf32_stream_index,
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

/* Tests the libuna_unicode_character_copy_to_utf32_stream function
 * Returns 1 if successful or 0 if not
 */
int una_test_unicode_character_copy_to_utf32_stream(
     void )
{
	uint8_t utf32_stream[ 16 ];

	uint8_t expected_utf32_stream1[ 8 ] = { 0, 0, 0, 'A', 0, 0, 0, 0 };
	uint8_t expected_utf32_stream2[ 8 ] = { 'A', 0, 0, 0, 0, 0, 0, 0 };
	uint8_t expected_utf32_stream3[ 8 ] = { 0xea, 0xf9, 0x01, 0x00, 0, 0, 0, 0 };

	libuna_error_t *error               = NULL;
	size_t utf32_stream_index           = 0;
	int result                          = 0;

	/* Test regular cases
	 */
	utf32_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf32_stream(
		  0x00000041UL,
		  utf32_stream,
		  16,
		  &utf32_stream_index,
		  LIBUNA_ENDIAN_BIG,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_stream_index",
	 utf32_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf32_stream1,
		  utf32_stream,
		  4 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf32_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf32_stream(
		  0x00000041UL,
		  utf32_stream,
		  16,
		  &utf32_stream_index,
		  LIBUNA_ENDIAN_LITTLE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_stream_index",
	 utf32_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf32_stream2,
		  utf32_stream,
		  4 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf32_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf32_stream(
		  0x0001f9eaUL,
		  utf32_stream,
		  16,
		  &utf32_stream_index,
		  LIBUNA_ENDIAN_LITTLE,
		  &error );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	UNA_TEST_ASSERT_EQUAL_SIZE(
	 "utf32_stream_index",
	 utf32_stream_index,
	 (size_t) 4 );

	UNA_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
		  expected_utf32_stream3,
		  utf32_stream,
		  4 );

	UNA_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf32_stream_index = 0;

	result = libuna_unicode_character_copy_to_utf32_stream(
	          0x00000041UL,
	          NULL,
	          16,
	          &utf32_stream_index,
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

	result = libuna_unicode_character_copy_to_utf32_stream(
	          0x00000041UL,
	          utf32_stream,
	          (size_t) SSIZE_MAX + 1,
	          &utf32_stream_index,
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

	result = libuna_unicode_character_copy_to_utf32_stream(
	          0x00000041UL,
	          utf32_stream,
	          16,
	          NULL,
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

	result = libuna_unicode_character_copy_to_utf32_stream(
	          0x00000041UL,
	          utf32_stream,
	          16,
	          &utf32_stream_index,
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

	utf32_stream_index = 16;

	result = libuna_unicode_character_copy_to_utf32_stream(
	          0x00000041UL,
	          utf32_stream,
	          16,
	          &utf32_stream_index,
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

	UNA_TEST_RUN(
	 "libuna_unicode_character_size_to_utf7_stream",
	 una_test_unicode_character_size_to_utf7_stream );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_from_utf7_stream",
	 una_test_unicode_character_copy_from_utf7_stream );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_to_utf7_stream",
	 una_test_unicode_character_copy_to_utf7_stream );

	UNA_TEST_RUN(
	 "libuna_unicode_character_size_to_utf8",
	 una_test_unicode_character_size_to_utf8 );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_from_utf8",
	 una_test_unicode_character_copy_from_utf8 );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_to_utf8",
	 una_test_unicode_character_copy_to_utf8 );

	UNA_TEST_RUN(
	 "libuna_unicode_character_size_to_utf16",
	 una_test_unicode_character_size_to_utf16 );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_from_utf16",
	 una_test_unicode_character_copy_from_utf16 );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_to_utf16",
	 una_test_unicode_character_copy_to_utf16 );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_from_utf16_stream",
	 una_test_unicode_character_copy_from_utf16_stream );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_to_utf16_stream",
	 una_test_unicode_character_copy_to_utf16_stream );

	UNA_TEST_RUN(
	 "libuna_unicode_character_size_to_utf32",
	 una_test_unicode_character_size_to_utf32 );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_from_utf32",
	 una_test_unicode_character_copy_from_utf32 );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_to_utf32",
	 una_test_unicode_character_copy_to_utf32 );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_from_utf32_stream",
	 una_test_unicode_character_copy_from_utf32_stream );

	UNA_TEST_RUN(
	 "libuna_unicode_character_copy_to_utf32_stream",
	 una_test_unicode_character_copy_to_utf32_stream );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

