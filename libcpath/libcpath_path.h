/*
 * Path functions
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

#if !defined( _LIBCPATH_PATH_H )
#define _LIBCPATH_PATH_H

#include <common.h>
#include <types.h>

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "libcpath_extern.h"
#include "libcpath_libcerror.h"
#include "libcpath_libcstring.h"
#include "libcpath_split_string.h"
#include "libcpath_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( WINAPI )
LIBCPATH_EXTERN \
int libcpath_path_create_windows_extended(
     const libcstring_system_character_t *path,
     size_t path_length,
     libcstring_system_character_t **extended_path,
     size_t *extended_path_size,
     libcerror_error_t **error );
#endif

LIBCPATH_EXTERN \
int libcpath_path_change_directory(
     const libcstring_system_character_t *directory_name,
     libcerror_error_t **error );

LIBCPATH_EXTERN \
int libcpath_path_get_current_working_directory(
     libcstring_system_character_t **current_working_directory,
     size_t *current_working_directory_size,
     libcerror_error_t **error );

LIBCPATH_EXTERN \
int libcpath_path_join(
     libcstring_system_character_t **path,
     size_t *path_size,
     const libcstring_system_character_t *directory_name,
     size_t directory_name_length,
     const libcstring_system_character_t *filename,
     size_t filename_length,
     libcerror_error_t **error );

LIBCPATH_EXTERN \
int libcpath_path_make_directory(
     const libcstring_system_character_t *directory_name,
     libcerror_error_t **error );

LIBCPATH_EXTERN \
int libcpath_path_sanitize(
     libcstring_system_character_t *path,
     size_t *path_size,
     libcerror_error_t **error );

LIBCPATH_EXTERN \
int libcpath_path_sanitize_filename(
     libcstring_system_character_t *filename,
     size_t *filename_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

