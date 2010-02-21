/*
 * Find functions
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

#if !defined( _LIBSYSTEM_FIND_H )
#define _LIBSYSTEM_FIND_H

#include <common.h>
#include <types.h>

#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#include <dir.h>
#elif defined( WINAPI )
#include <io.h>
#endif

#include "libsystem_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

/* The find data structure type
 */
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )

#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#define libsystem_find_data_t	struct _wffblk
#else
#define libsystem_find_data_t	struct _wfinddata_t
#endif

#else

#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#define libsystem_find_data_t	struct ffblk
#else
#define libsystem_find_data_t	struct _finddata_t
#endif

#endif /* defined( LIBSYSTEM_HAVE_WIDE_CHARACTER ) */

/* The find data structure name variable
 */
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#define libsystem_find_data_get_name( fileinfo ) \
	fileinfo ## .ff_name
#else
#define libsystem_find_data_get_name( fileinfo ) \
	fileinfo ## .name
#endif

/* The find first function
 */
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )

#if defined( __BORLANDC__ )
#if __BORLANDC__ <= 0x0520
#define libsystem_find_first( filter, fileinfo ) \
	_wfindfirst( filter, fileinfo, 0 )
#else
#define libsystem_find_first( filter, fileinfo ) \
	__wfindfirst( filter, fileinfo )
#endif

#else
#define libsystem_find_first( filter, fileinfo ) \
	_wfindfirst( filter, fileinfo )
#endif

#else

#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#define libsystem_find_first( filter, fileinfo ) \
	findfirst( filter, fileinfo, 0 )
#else
#define libsystem_find_first( filter, fileinfo ) \
	_findfirst( filter, fileinfo )
#endif

#endif /* defined( LIBSYSTEM_HAVE_WIDE_CHARACTER ) */

/* The find next function
 */
#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )

#if defined( __BORLANDC__ )
#if __BORLANDC__ <= 0x0520
#define libsystem_find_next( handle, fileinfo ) \
	_wfindnext( fileinfo )
#else
#define libsystem_find_next( handle, fileinfo ) \
	__wfindnext( handle, fileinfo )
#endif

#else
#define libsystem_find_next( handle, fileinfo ) \
	_wfindnext( handle, fileinfo )
#endif

#else

#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#define libsystem_find_next( handle, fileinfo ) \
	findnext( fileinfo )
#else
#define libsystem_find_next( handle, fileinfo ) \
	_findnext( handle, fileinfo )
#endif

#endif /* defined( LIBSYSTEM_HAVE_WIDE_CHARACTER ) */

/* The find close function
 */
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#define libsystem_find_close( handle ) \
	0
#else
#define libsystem_find_close( handle ) \
	_findclose( handle )
#endif

#if defined( __cplusplus )
}
#endif

#endif

