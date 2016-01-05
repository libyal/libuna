/*
 * Unicode and ASCII (byte stream) conversion library Unicode character copy from testing program
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

#include <stdio.h>

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
#include "una_test_libcstring.h"
#include "una_test_libuna.h"
#include "una_test_types.h"

/* Tests copying an Unicode character from a byte stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_unicode_character_copy_from_byte_stream(
     const una_test_byte_stream_to_unicode_t *byte_stream_to_unicode,
     size_t number_of_byte_stream_to_unicode_entries,
     int codepage )
{
	libuna_error_t *error                        = NULL;
	libuna_unicode_character_t unicode_character = 0;
	size_t byte_stream_index                     = 0;
	size_t byte_stream_to_unicode_entry_index    = 0;
	int result                                   = 0;

        fprintf(
         stdout,
         "Testing copying Unicode character from byte stream with codepage: %d\t",
	 codepage );

	while( byte_stream_to_unicode_entry_index < number_of_byte_stream_to_unicode_entries )
	{
		byte_stream_index = 0;

		result = libuna_unicode_character_copy_from_byte_stream(
			  &unicode_character,
			  ( byte_stream_to_unicode[ byte_stream_to_unicode_entry_index ] ).byte_stream,
			  ( byte_stream_to_unicode[ byte_stream_to_unicode_entry_index ] ).byte_stream_size,
			  &byte_stream_index,
			  codepage,
			  &error );

		if( result != 1 )
		{
			break;
		}
		if( unicode_character != ( byte_stream_to_unicode[ byte_stream_to_unicode_entry_index ] ).unicode_character )
		{
			result = 0;

			break;
		}
		byte_stream_to_unicode_entry_index++;
	}
	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( result == -1 )
	{
		libuna_error_backtrace_fprint(
		 error,
		 stderr );
		libuna_error_free(
		 &error );
	}
	else if( result == 0 )
	{
		if( byte_stream_to_unicode_entry_index < number_of_byte_stream_to_unicode_entries )
		{
			fprintf(
			 stdout,
			 "Mismatch for: 0x%02" PRIx8 "",
			 ( byte_stream_to_unicode[ byte_stream_to_unicode_entry_index ] ).byte_stream[ 0 ] );

			if( ( byte_stream_to_unicode[ byte_stream_to_unicode_entry_index ] ).byte_stream_size > 1 )
			{
				fprintf(
				 stdout,
				 " 0x%02" PRIx8 "",
				 ( byte_stream_to_unicode[ byte_stream_to_unicode_entry_index ] ).byte_stream[ 1 ] );
			}
			fprintf(
			 stdout,
			 " expected: 0x%08" PRIx32 " got: 0x%08" PRIx32 "\n",
			 ( byte_stream_to_unicode[ byte_stream_to_unicode_entry_index ] ).unicode_character,
			 unicode_character );
		}
	}
	return( result );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libuna_error_t *error = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "This program does not take arguments.\n" );

		return( EXIT_FAILURE );
	}
	/* Case: codepage windows 874
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_874_byte_stream_to_unicode,
	     225,
	     LIBUNA_CODEPAGE_WINDOWS_874 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 874 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 932
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_932_byte_stream_to_unicode,
	     7915,
	     LIBUNA_CODEPAGE_WINDOWS_932 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 932 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 936
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_936_byte_stream_to_unicode,
	     21920,
	     LIBUNA_CODEPAGE_WINDOWS_936 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 936 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 949
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_949_byte_stream_to_unicode,
	     17176,
	     LIBUNA_CODEPAGE_WINDOWS_949 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 949 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 950
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_950_byte_stream_to_unicode,
	     13631,
	     LIBUNA_CODEPAGE_WINDOWS_950 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 950 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 1250
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1250_byte_stream_to_unicode,
	     251,
	     LIBUNA_CODEPAGE_WINDOWS_1250 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 1250 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 1251
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1251_byte_stream_to_unicode,
	     255,
	     LIBUNA_CODEPAGE_WINDOWS_1251 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 1251 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 1252
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1252_byte_stream_to_unicode,
	     251,
	     LIBUNA_CODEPAGE_WINDOWS_1252 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 1252 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 1253
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1253_byte_stream_to_unicode,
	     239,
	     LIBUNA_CODEPAGE_WINDOWS_1253 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 1253 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 1254
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1254_byte_stream_to_unicode,
	     249,
	     LIBUNA_CODEPAGE_WINDOWS_1254 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 1254 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 1255
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1255_byte_stream_to_unicode,
	     233,
	     LIBUNA_CODEPAGE_WINDOWS_1255 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 1255 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 1256
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1256_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_WINDOWS_1256 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 1256 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 1257
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1257_byte_stream_to_unicode,
	     244,
	     LIBUNA_CODEPAGE_WINDOWS_1257 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 1257 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage windows 1258
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1258_byte_stream_to_unicode,
	     247,
	     LIBUNA_CODEPAGE_WINDOWS_1258 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage windows 1258 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 20127 (ASCII)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_ascii_byte_stream_to_unicode,
	     128,
	     LIBUNA_CODEPAGE_ASCII ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage ASCII byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 20866 (koi8-r)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_koi8_r_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_KOI8_R ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage koi8-r byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 21866 (koi8-u)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_koi8_u_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_KOI8_U ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage koi8-u byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28591 (iso-8859-1)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_1_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-1 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28592 (iso-8859-2)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_2_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_2 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-2 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28593 (iso-8859-3)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_3_byte_stream_to_unicode,
	     249,
	     LIBUNA_CODEPAGE_ISO_8859_3 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-3 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28594 (iso-8859-4)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_4_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_4 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-4 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28595 (iso-8859-5)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_5_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_5 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-5 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28596 (iso-8859-6)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_6_byte_stream_to_unicode,
	     211,
	     LIBUNA_CODEPAGE_ISO_8859_6 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-6 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28597 (iso-8859-7)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_7_byte_stream_to_unicode,
	     253,
	     LIBUNA_CODEPAGE_ISO_8859_7 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-7 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28598 (iso-8859-8)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_8_byte_stream_to_unicode,
	     220,
	     LIBUNA_CODEPAGE_ISO_8859_8 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-8 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28599 (iso-8859-9)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_9_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_9 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-9 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28600 (iso-8859-10)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_10_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_10 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-10 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28601 (iso-8859-11)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_11_byte_stream_to_unicode,
	     248,
	     LIBUNA_CODEPAGE_ISO_8859_11 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-11 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28603 (iso-8859-13)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_13_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_13 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-13 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28604 (iso-8859-14)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_14_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_14 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-14 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28605 (iso-8859-15)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_15_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_15 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-15 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 28606 (iso-8859-16)
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_iso_8859_16_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_ISO_8859_16 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage iso-8859-16 byte stream to Unicode character.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libuna_error_backtrace_fprint(
		 error,
		 stderr );
		libuna_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

