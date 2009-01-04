/*
 * The internal inline definition
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

#if !defined( _LIBUCA_INTERNAL_INLINE_H )
#define _LIBUCA_INTERNAL_INLINE_H

#include <common.h>

/* Define HAVE_LOCAL_LIBUCA for local use of libuca
 */
#if !defined( HAVE_LOCAL_LIBUCA )

#include <libuca/inline.h>

#elif defined( HAVE_WINDOWS_INLINE )
#define LIBUCA_INLINE _inline

#else
#define LIBUCA_INLINE inline

#endif

#endif

