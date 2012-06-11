/*
 * Unicode and ASCII (byte stream) conversion library Unicode character copy from testing program
 *
 * Copyright (c) 2008-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include "una_test_codepage_koi8_r.h"
#include "una_test_codepage_koi8_u.h"
#include "una_test_codepage_windows_874.h"
#include "una_test_codepage_windows_932.h"
#include "una_test_codepage_windows_936.h"
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
	/* Case: codepage 874
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_874_byte_stream_to_unicode,
	     225,
	     LIBUNA_CODEPAGE_WINDOWS_874 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 874 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 932
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_932_byte_stream_to_unicode,
	     7915,
	     LIBUNA_CODEPAGE_WINDOWS_932 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 932 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 936
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_936_byte_stream_to_unicode,
	     21920,
	     LIBUNA_CODEPAGE_WINDOWS_936 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 936 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 1250
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1250_byte_stream_to_unicode,
	     251,
	     LIBUNA_CODEPAGE_WINDOWS_1250 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 1250 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 1251
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1251_byte_stream_to_unicode,
	     255,
	     LIBUNA_CODEPAGE_WINDOWS_1251 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 1251 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 1252
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1252_byte_stream_to_unicode,
	     251,
	     LIBUNA_CODEPAGE_WINDOWS_1252 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 1252 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 1253
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1253_byte_stream_to_unicode,
	     239,
	     LIBUNA_CODEPAGE_WINDOWS_1253 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 1253 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 1254
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1254_byte_stream_to_unicode,
	     249,
	     LIBUNA_CODEPAGE_WINDOWS_1254 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 1254 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 1255
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1255_byte_stream_to_unicode,
	     233,
	     LIBUNA_CODEPAGE_WINDOWS_1255 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 1255 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 1256
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1256_byte_stream_to_unicode,
	     256,
	     LIBUNA_CODEPAGE_WINDOWS_1256 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 1256 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 1257
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1257_byte_stream_to_unicode,
	     244,
	     LIBUNA_CODEPAGE_WINDOWS_1257 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 1257 byte stream to Unicode character.\n" );

		goto on_error;
	}
	/* Case: codepage 1258
	 */
	if( una_test_unicode_character_copy_from_byte_stream(
	     una_test_codepage_windows_1258_byte_stream_to_unicode,
	     247,
	     LIBUNA_CODEPAGE_WINDOWS_1258 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy codepage 1258 byte stream to Unicode character.\n" );

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

