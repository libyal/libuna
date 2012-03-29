/*
 * Directory functions
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

#if !defined( _LIBCDIRECTORY_INTERNAL_DIRECTORY_H )
#define _LIBCDIRECTORY_INTERNAL_DIRECTORY_H

#include <common.h>
#include <types.h>

#if defined( HAVE_DIRENT_H )
#include <dirent.h>
#endif

#include "libcdirectory_directory_entry.h"
#include "libcdirectory_extern.h"
#include "libcdirectory_libcerror.h"
#include "libcdirectory_libcstring.h"
#include "libcdirectory_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libcdirectory_internal_directory libcdirectory_internal_directory_t;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
struct libcdirectory_internal_directory
{
	HANDLE handle;

	libcdirectory_internal_directory_entry_t *first_entry;
};

#elif defined( WINAPI ) && defined( USE_CRT_FUNCTIONS )
struct libcdirectory_internal_directory
{
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	int handle;

#elif defined( __BORLANDC__ )
	long handle;

#else
	intptr_t handle;

#endif

	libcdirectory_internal_directory_entry_t *first_entry;
};

#elif defined( HAVE_DIRENT_H )
struct libcdirectory_internal_directory
{
	DIR *stream;
};

#endif

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_initialize(
     libcdirectory_directory_t **directory,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_free(
     libcdirectory_directory_t **directory,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_open(
     libcdirectory_directory_t *directory,
     const libcstring_system_character_t *directory_name,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_close(
     libcdirectory_directory_t *directory,
     libcerror_error_t **error );

LIBCDIRECTORY_EXTERN \
int libcdirectory_directory_read_entry(
     libcdirectory_directory_t *directory,
     libcdirectory_directory_entry_t *directory_entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

