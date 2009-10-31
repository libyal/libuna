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

#if !defined( _LIBUNA_SUPPORT_H )
#define _LIBUNA_SUPPORT_H

#include <common.h>
#include <types.h>

#include <stdio.h>

#include "libuna_error.h"
#include "libuna_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBUNA )

LIBUNA_EXTERN const char *libuna_get_version(
                           void );

LIBUNA_EXTERN void libuna_error_free(
                    libuna_error_t **error );

LIBUNA_EXTERN void libuna_error_fprint(
                    libuna_error_t *error,
                    FILE *stream );

LIBUNA_EXTERN void libuna_error_backtrace_fprint(
                    libuna_error_t *error,
                    FILE *stream );

#endif

#if defined( __cplusplus )
}
#endif

#endif

