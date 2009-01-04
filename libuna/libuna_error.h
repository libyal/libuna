/*
 * Error functions
 *
 * Copyright (c) 2008, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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

#if !defined( _LIBUNA_INTERNAL_ERROR_H )
#define _LIBUNA_INTERNAL_ERROR_H

#include <common.h>
#include <types.h>

#include <stdio.h>

/* Define HAVE_LOCAL_LIBUNA for local use of libuna
 */
#if !defined( HAVE_LOCAL_LIBUNA )
#include <libuna/error.h>
#endif

#include "libuna_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

/* The definitions in <libuna/error.h> are copied here
 * for local use of libuna
 */
#if defined( HAVE_LOCAL_LIBUNA )

/* External error type definition hides internal structure
 */
typedef intptr_t libuna_error_t;

/* The error domains
 */
enum LIBUNA_ERROR_DOMAINS
{
	LIBUNA_ERROR_DOMAIN_ARGUMENTS           = (int) 'a',
	LIBUNA_ERROR_DOMAIN_CONVERSION          = (int) 'c',
};

/* The argument error codes
 */
enum LIBUNA_ARGUMENT_ERROR
{
	LIBUNA_ARGUMENT_ERROR_INVALID           = 0,
	LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM   = 1,
	LIBUNA_ARGUMENT_ERROR_TOO_SMALL         = 2,
	LIBUNA_ARGUMENT_ERROR_UNSUPPORTED_VALUE = 3
};

/* The conversion error codes
 */
enum LIBUNA_CONVERSION_ERROR
{
	LIBUNA_CONVERSION_ERROR_INVALID_INPUT   = 0,
	LIBUNA_CONVERSION_ERROR_INVALID_OUTPUT  = 1
};

#endif

typedef struct libuna_internal_error libuna_internal_error_t;

struct libuna_internal_error
{
	/* The error domain
	 */
	int domain;

	/* The error code
	 */
	int code;

	/* The amount of messages
	 */
	int amount_of_messages;

	/* The error messages
	 */
	char **message;
};

void libuna_error_set(
      libuna_error_t **error,
      int error_domain,
      int error_code,
      const char *format,
      ... );

void libuna_error_add_message(
      libuna_error_t *error,
      const char *format,
      ... );

LIBUNA_EXTERN void libuna_error_free(
                    libuna_error_t **error );

LIBUNA_EXTERN void libuna_error_fprint(
                    libuna_error_t *error,
                    FILE *stream );

LIBUNA_EXTERN void libuna_error_backtrace_fprint(
                    libuna_error_t *error,
                    FILE *stream );

#if defined( __cplusplus )
}
#endif

#endif

