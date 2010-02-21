/*
 * GetOpt functions
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

#if !defined( _LIBSYSTEM_GETOPT_H )
#define _LIBSYSTEM_GETOPT_H

#include <common.h>
#include <types.h>

/* unistd.h is included here to export getopt, optarg, optind and optopt
 */
#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "libsystem_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_GETOPT )
#define libsystem_getopt( argument_count, argument_values, options_string ) \
	getopt( argument_count, argument_values, options_string )

#else

/* The current option argument
 */
extern libsystem_character_t *optarg;

/* The option index
 */
extern int optind;

/* Value to indicate the current option
 */
extern libsystem_integer_t optopt;

libsystem_integer_t libsystem_getopt(
                     int argument_count,
                     libsystem_character_t * const argument_values[],
                     const libsystem_character_t *options_string );

#endif

#if defined( __cplusplus )
}
#endif

#endif

