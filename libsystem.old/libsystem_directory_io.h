/*
 * Directory IO functions
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

#if !defined( _LIBSYSTEM_DIRECTORY_IO_H )
#define _LIBSYSTEM_DIRECTORY_IO_H

#include <common.h>
#include <types.h>

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#if defined( WINAPI )
#include <direct.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( WINAPI )
#define libsystem_directory_io_chdir( directory_name ) \
	_chdir( directory_name )

#elif defined( HAVE_CHDIR )
#define libsystem_directory_io_chdir( directory_name ) \
	chdir( directory_name )
#endif

#if defined( WINAPI )
#define libsystem_directory_io_wchdir( directory_name ) \
	_wchdir( directory_name )

#endif

#if defined( WINAPI )
#define libsystem_directory_io_mkdir( directory_name ) \
	_mkdir( directory_name )

#elif defined( HAVE_MKDIR )
#define libsystem_directory_io_mkdir( directory_name ) \
	mkdir( directory_name, 0755 )
#endif

#if defined( WINAPI )
#define libsystem_directory_io_wmkdir( directory_name ) \
	_wmkdir( directory_name )

#endif

#if defined( __cplusplus )
}
#endif

#endif

