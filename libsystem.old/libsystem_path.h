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

#if !defined( _LIBSYSTEM_PATH_H )
#define _LIBSYSTEM_PATH_H

#include <common.h>
#include <types.h>

#if defined( WINAPI )
#include <io.h>
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

#if defined( LIBSYSTEM_HAVE_WIDE_CHARACTER )
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

#if defined( __cplusplus )
}
#endif

#endif

