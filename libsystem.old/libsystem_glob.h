/*
 * Globbing functions
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

#if !defined( _LIBSYSTEM_GLOB_H )
#define _LIBSYSTEM_GLOB_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libsystem_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_GLOB_H )
#define LIBSYSTEM_HAVE_GLOB	1
#endif

#if !defined( LIBSYSTEM_HAVE_GLOB )

typedef struct libsystem_glob libsystem_glob_t;

struct libsystem_glob
{
	/* The amount of globs resolved
	 */
	int amount_of_results;

	/* The resolved globs
	 */
	libsystem_character_t **result;
};

int libsystem_glob_initialize(
     libsystem_glob_t **glob,
     liberror_error_t **error );

int libsystem_glob_free(
     libsystem_glob_t **glob,
     liberror_error_t **error );

int libsystem_glob_resize(
     libsystem_glob_t *glob,
     int new_amount_of_results,
     liberror_error_t **error );

int libsystem_glob_resolve(
     libsystem_glob_t *glob,
     libsystem_character_t * const patterns[],
     int amount_of_patterns,
     liberror_error_t **error );

#endif

#if defined( __cplusplus )
}
#endif

#endif

