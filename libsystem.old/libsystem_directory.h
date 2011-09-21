/*
 * Directory functions
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

#if !defined( _LIBSYSTEM_DIRECTORY_H )
#define _LIBSYSTEM_DIRECTORY_H

#include <common.h>
#include <types.h>

#include "libsystem_directory_io.h"
#include "libsystem_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )

#define libsystem_directory_change( directory_name ) \
	libsystem_directory_io_wchdir( directory_name )

#define libsystem_directory_make( directory_name ) \
	libsystem_directory_io_wmkdir( directory_name )

#else

#define libsystem_directory_change( directory_name ) \
	libsystem_directory_io_chdir( directory_name )

#define libsystem_directory_make( directory_name ) \
	libsystem_directory_io_mkdir( directory_name )

#endif

#if defined( __cplusplus )
}
#endif

#endif

