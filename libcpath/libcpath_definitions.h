/*
 * File functions
 *
 * Copyright (c) 2008-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBCPATH_DEFINITIONS_H )
#define _LIBCPATH_DEFINITIONS_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define LIBCPATH_VERSION				20120401

/* The libcpath version string
 */
#define LIBCPATH_VERSION_STRING				"20120401"

#if defined( WINAPI )
#define LIBCPATH_PATH_SEPARATOR				'\\'

#else
#define LIBCPATH_PATH_SEPARATOR				'/'

#endif /* defined( WINAPI ) */

#if defined( __cplusplus )
}
#endif

#endif

