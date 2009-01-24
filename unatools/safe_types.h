/*
 * Type definitions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _SAFE_TYPES_H )
#define _SAFE_TYPES_H

#include <common.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* These definitions make sure the size and offset types
 * are consistent for multiple platforms
 */

#if ! HAVE_SIZE32_T
typedef uint32_t size32_t;
#endif

#if ! HAVE_SSIZE32_T
typedef int32_t ssize32_t;
#endif

#if ! HAVE_SIZE64_T
typedef uint64_t size64_t;
#endif

#if ! HAVE_SSIZE64_T
typedef int64_t ssize64_t;
#endif

#if ! HAVE_OFF64_T
typedef int64_t off64_t;
#endif

#if defined( __cplusplus )
}
#endif

#endif

