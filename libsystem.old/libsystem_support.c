/*
 * Support functions
 *
 * Copyright (c) 2010, Joachim Metz <jbmetz@users.sourceforge.net>
 * Copyright (c) 2006-2010, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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
#include <narrow_string.h>
#include <memory.h>
#include <wide_string.h>
#include <types.h>

#include <errno.h>

#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#include <locale.h>
#elif defined( HAVE_LOCALE_H )
#include <locale.h>
#endif

#if defined( HAVE_LANGINFO_H )
#include <langinfo.h>
#endif

#include "libsystem_libuna.h"
#include "libsystem_notify.h"
#include "libsystem_string.h"
#include "libsystem_support.h"

/* Initializes the system values
 * Returns 1 if successful or -1 on error
 */
int libsystem_initialize(
     liberror_error_t **error )
{
#if !defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )
	static char *function = "libsystem_initialize";
	char *locale          = NULL;
	char *charset         = NULL;
	size_t charset_length = 0;

#if !defined( HAVE_LANGINFO_CODESET )
	size_t locale_length  = 0;
#endif

	/* Determine the supported locales
	 */
	locale = setlocale(
	          LC_CTYPE,
	          "" );

	if( locale == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine locale.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LANGINFO_CODESET )
	charset = nl_langinfo(
	           CODESET );

	if( charset == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine character set.",
		 function );

		return( -1 );
	}
	charset_length = narrow_string_length(
	                  charset );

#elif defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	/* No need to check there is only support for the locale: C
	 */

#else
	locale_length = narrow_string_length(
	                 locale );

	charset = narrow_string_search(
	           locale,
	           '.',
	           locale_length + 1 );

	if( charset == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine character set.",
		 function );

		return( -1 );
	}
	charset++;

	charset_length = locale_length - (size_t) ( charset - locale );
#endif

#if defined( HAVE_DEBUG_OUTPUT )
	if( libsystem_notify_verbose != 0 )
	{
		libsystem_notify_printf(
		 "%s: charset: %s\n",
		 function,
		 charset );
	}
#endif

	/* Determine codepage
	 */
	libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_ASCII;

	if( charset_length == 5 )
	{
		if( narrow_string_compare(
		     "UTF-8",
		     charset,
		     5 ) == 0 )
		{
			libsystem_string_is_unicode = 1;
		}
	}
	else if( charset_length >= 4 )
	{
		if( narrow_string_compare(
		     "1250",
		     charset,
		     4 ) == 0 )
		{
			libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1250;
		}
		else if( narrow_string_compare(
		          "1251",
		          charset,
		          4 ) == 0 )
		{
			libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1251;
		}
		else if( narrow_string_compare(
		          "1252",
		          charset,
		          4 ) == 0 )
		{
			libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1252;
		}
		else if( narrow_string_compare(
		          "1253",
		          charset,
		          4 ) == 0 )
		{
			libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1253;
		}
		else if( narrow_string_compare(
		          "1254",
		          charset,
		          4 ) == 0 )
		{
			libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1254;
		}
		else if( narrow_string_compare(
		          "1255",
		          charset,
		          4 ) == 0 )
		{
			libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1255;
		}
		else if( narrow_string_compare(
		          "1256",
		          charset,
		          4 ) == 0 )
		{
			libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1256;
		}
		else if( narrow_string_compare(
		          "1257",
		          charset,
		          4 ) == 0 )
		{
			libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1257;
		}
		else if( narrow_string_compare(
		          "1258",
		          charset,
		          4 ) == 0 )
		{
			libsystem_string_byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1258;
		}
		else if( narrow_string_compare(
		          "utf8",
		          charset,
		          4 ) == 0 )
		{
			libsystem_string_is_unicode = 1;
		}
	}
#endif
	return( 1 );
}

