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

#if !defined( _LIBUNA_ERROR_H )
#define _LIBUNA_ERROR_H

#include <common.h>
#include <types.h>

#include <stdio.h>

#include <libuna/error.h>

#include "libuna_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libuna_internal_error libuna_internal_error_t;

struct libuna_internal_error
{
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
      int error_code,
      const char *format,
      ... );

void libuna_error_add_message(
      libuna_error_t *error,
      const char *format,
      ... );

LIBUNA_EXTERN void libuna_error_free(
                    libuna_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

