/*
 * Support functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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
#include <types.h>

#include <liberror.h>

#include <stdio.h>

#include "libuna_definitions.h"
#include "libuna_support.h"

#if !defined( HAVE_LOCAL_LIBUNA )
/* Returns the library version as a string
 */
const char *libuna_get_version(
             void )
{
	return( (const char *) LIBUNA_VERSION_STRING );
}

/* Free an error and its elements
 */
void libuna_error_free(
      libuna_error_t **error )
{
	liberror_error_free(
	 (liberror_error_t **) error );
}

/* Prints a descriptive string of the error to the stream
 */
void libuna_error_fprint(
     libuna_error_t *error,
     FILE *stream )
{
	liberror_error_fprint(
	 (liberror_error_t *) error,
	 stream );
}

/* Prints a backtrace of the error to the stream
 */
void libuna_error_backtrace_fprint(
     libuna_error_t *error,
     FILE *stream )
{
	liberror_error_backtrace_fprint(
	 (liberror_error_t *) error,
	 stream );
}
#endif

