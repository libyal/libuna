/*
 * File IO functions
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

#if !defined( _LIBSYSTEM_FILE_IO_H )
#define _LIBSYSTEM_FILE_IO_H

#include <common.h>
#include <types.h>

#if defined( HAVE_SYS_STAT_H ) || defined( WINAPI )
#include <sys/stat.h>
#endif

#if defined( HAVE_FCNTL_H ) || defined( WINAPI )
#include <fcntl.h>
#endif

#if defined( WINAPI )
#include <io.h>

#elif defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#define LIBSYSTEM_FILE_IO_O_CREAT 	_O_CREAT
#define LIBSYSTEM_FILE_IO_O_RDONLY	_O_RDONLY
#define LIBSYSTEM_FILE_IO_O_RDWR	_O_RDWR
#define LIBSYSTEM_FILE_IO_O_WRONLY	_O_WRONLY
#define LIBSYSTEM_FILE_IO_O_TRUNC   	_O_TRUNC

#else
#define LIBSYSTEM_FILE_IO_O_CREAT   	O_CREAT
#define LIBSYSTEM_FILE_IO_O_RDONLY	O_RDONLY
#define LIBSYSTEM_FILE_IO_O_RDWR	O_RDWR
#define LIBSYSTEM_FILE_IO_O_WRONLY	O_WRONLY
#define LIBSYSTEM_FILE_IO_O_TRUNC	O_TRUNC

#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#define libsystem_file_io_open( filename, flags ) \
	_open( filename, flags )

#elif defined( HAVE_OPEN )
#define libsystem_file_io_open( filename, flags ) \
	open( filename, flags, 0644 )
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#define libsystem_file_io_wopen( filename, flags ) \
	_wopen( filename, flags )
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#define libsystem_file_io_close( file_descriptor ) \
	_close( file_descriptor )

#elif defined( HAVE_CLOSE )
#define libsystem_file_io_close( file_descriptor ) \
	close( file_descriptor )
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#define libsystem_file_io_read( file_descriptor, buffer, size ) \
	_read( file_descriptor, (void *) buffer, (unsigned int) size )

#elif defined( HAVE_READ )
#define libsystem_file_io_read( file_descriptor, buffer, size ) \
	read( file_descriptor, (void *) buffer, size )
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#define libsystem_file_io_lseek( file_descriptor, offset, whence ) \
	_lseeki64( file_descriptor, offset, whence )

#elif defined( HAVE_LSEEK )
#define libsystem_file_io_lseek( file_descriptor, offset, whence ) \
	lseek( file_descriptor, offset, whence )
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#define libsystem_file_io_resize( file_descriptor, size ) \
	_chsize( file_descriptor, (long) size )

#elif defined( HAVE_FTRUNCATE )
#define libsystem_file_io_resize( file_descriptor, size ) \
	ftruncate( file_descriptor, (off_t) size )
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#define libsystem_file_io_write( file_descriptor, buffer, size ) \
	_write( file_descriptor, (const void *) buffer, (unsigned int) size )

#elif defined( HAVE_WRITE )
#define libsystem_file_io_write( file_descriptor, buffer, size ) \
	write( file_descriptor, (const void *) buffer, size )
#endif

#if defined( __cplusplus )
}
#endif

#endif

