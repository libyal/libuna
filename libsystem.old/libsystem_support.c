/*
 * Support functions
 *
 * Copyright (c) 2008-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <libcstring.h>
#include <liberror.h>

#if defined( HAVE_LIBINTL_H )
#include <libintl.h>
#endif

#include "libsystem_support.h"

/* Initializes the system values
 * Returns 1 if successful or -1 on error
 */
int libsystem_initialize(
     const char *i18n_domain_name,
     liberror_error_t **error )
{
	static char *function = "libsystem_initialize";

#if !defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	libcstring_narrow_system_string_codepage = libcstring_locale_get_codepage();
#endif

	if( i18n_domain_name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internationalization domain name.",
		 function );

		return( -1 );
	}
#if defined( HAVE_BINDTEXTDOMAIN ) && defined( HAVE_TEXTDOMAIN )
	if( bindtextdomain(
	     i18n_domain_name,
	     LOCALEDIR ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to bind text domain.",
		 function );

		return( -1 );
	}
	if( textdomain(
	     i18n_domain_name ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set text domain.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

