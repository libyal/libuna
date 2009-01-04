/*
 * Globbing functions for the ucatools
 *
 * Copyright (c) 2006-2008, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _UCAGLOB_H )
#define _UCAGLOB_H

#include <common.h>
#include <system_string.h>

#include <libuca/types.h>

#include "ucacommon.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_GLOB_H )

typedef struct ucaglob ucaglob_t;

struct ucaglob
{
	/* The amount of globs resolved
	 */
	int amount_of_results;

	/* The resolved globs
	 */
	system_character_t **result;
};

int ucaglob_initialize(
     ucaglob_t **glob );

int ucaglob_free(
     ucaglob_t **glob );

int ucaglob_resize(
     ucaglob_t *glob,
     int new_amount_of_results );

int ucaglob_resolve(
     ucaglob_t *glob,
     system_character_t * const patterns[],
     int amount_of_patterns );

#endif

#if defined( __cplusplus )
}
#endif

#endif

