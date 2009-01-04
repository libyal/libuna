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

#if !defined( _LIBUCA_ERROR_H )
#define _LIBUCA_ERROR_H

#include <common.h>
#include <types.h>

#include <stdio.h>

#include <libuca/error.h>

#include "libuca_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libuca_internal_error libuca_internal_error_t;

struct libuca_internal_error
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

void libuca_error_set(
      libuca_error_t **error,
      int error_code,
      const char *format,
      ... );

void libuca_error_add_message(
      libuca_error_t *error,
      const char *format,
      ... );

LIBUCA_EXTERN void libuca_error_free(
                    libuca_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

