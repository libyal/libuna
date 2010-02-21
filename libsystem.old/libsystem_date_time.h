/*
 * Date and time functions
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

#if !defined( _LIBSYSTEM_DATE_TIME_H )
#define _LIBSYSTEM_DATE_TIME_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#if defined( TIME_WITH_SYS_TIME )
#include <sys/time.h>
#include <time.h>
#elif defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#else
#include <time.h>
#endif

#include "libsystem_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_TIME ) || defined( WINAPI )
#define libsystem_date_time_time( timestamp ) \
	time( timestamp )
#endif

#if defined( HAVE_MKTIME ) || defined( WINAPI )
#define libsystem_date_time_mktime( time_elements ) \
	mktime( time_elements )
#endif

#if defined( HAVE_CTIME ) || defined( HAVE_CTIME_R ) || defined( WINAPI )
int libsystem_date_time_get_ctime_string(
     const time_t *timestamp,
     libsystem_character_t *string,
     size_t string_size,
     liberror_error_t **error );
#endif

#if defined( HAVE_LOCALTIME ) || defined( HAVE_LOCALTIME_R ) || defined( WINAPI )
int libsystem_date_time_get_time_elements_in_localtime(
     const time_t *timestamp,
     struct tm *time_elements,
     liberror_error_t **error );
#endif

#if defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) || defined( WINAPI )
int libsystem_date_time_get_time_elements_in_utc(
     const time_t *timestamp,
     struct tm *time_elements,
     liberror_error_t **error );
#endif

#if defined( __cplusplus )
}
#endif

#endif

