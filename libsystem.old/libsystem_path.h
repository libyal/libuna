/*
 * Path functions
 *
 * Copyright (c) 2008-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBSYSTEM_PATH_H )
#define _LIBSYSTEM_PATH_H

#include <common.h>
#include <types.h>

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "libsystem_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( WINAPI )
#define LIBSYSTEM_PATH_SEPARATOR	'\\'

#else
#define LIBSYSTEM_PATH_SEPARATOR	'/'
#endif

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if defined( _MSC_VER )
#define libsystem_path_make( path, path_size, drive, directory, filename, extension ) \
	_wmakepath_s( path, path_size, drive, directory, filename, extension )

#define libsystem_path_split( path, drive, drive_size, directory, directory_size, filename, filename_size, extension, extension_size ) \
	_wsplitpath_s( path, drive, drive_size, directory, directory_size, filename, filename_size, extension, extension_size )

#else
#define libsystem_path_make( path, path_size, drive, directory, filename, extension ) \
	_wmakepath( path, drive, directory, filename, extension )

#define libsystem_path_split( path, drive, drive_size, directory, directory_size, filename, filename_size, extension, extension_size ) \
	_wsplitpath( path, drive, directory, filename, extension )

#endif

#else
#if defined( _MSC_VER )
#define libsystem_path_make( path, path_size, drive, directory, filename, extension ) \
	_makepath_s( path, path_size, drive, directory, filename, extension )

#define libsystem_path_split( path, drive, drive_size, directory, directory_size, filename, filename_size, extension, extension_size ) \
	_splitpath_s( path, drive, drive_size, directory, directory_size, filename, filename_size, extension, extension_size )

#else
#define libsystem_path_make( path, path_size, drive, directory, filename, extension ) \
	_makepath( path, drive, directory, filename, extension )

#define libsystem_path_split( path, drive, drive_size, directory, directory_size, filename, filename_size, extension, extension_size ) \
	_splitpath( path, drive, directory, filename, extension )

#endif
#endif

/* TODO
#if defined( WINAPI ) && ( WINVER < 0x0500 )
BOOL libsystem_GetVolumeInformation(
      LPCTSTR root_path_name,
      LPTSTR volume_name,
      DWORD volume_name_size,
      LPDWORD volume_serial_number,
      LPDWORD maximum_component_length,
      LPDWORD file_system_flags,
      LPTSTR file_system_name,
      DWORD file_system_name_size );
#endif
*/

int libsystem_path_create(
     const libcstring_system_character_t *filename,
     size_t filename_length,
     const libcstring_system_character_t *basename,
     size_t basename_length,
     libcstring_system_character_t **path,
     size_t *path_size,
     liberror_error_t **error );

#if defined( WINAPI )
int libsystem_path_create_windows_extended(
     const libcstring_system_character_t *path,
     size_t path_length,
     libcstring_system_character_t **extended_path,
     size_t *extended_path_size,
     liberror_error_t **error );
#endif

int libsystem_path_sanitize(
     libcstring_system_character_t *path,
     size_t *path_size,
     liberror_error_t **error );

int libsystem_path_sanitize_filename(
     libcstring_system_character_t *filename,
     size_t *filename_size,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

