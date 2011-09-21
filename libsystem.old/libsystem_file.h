/*
 * File functions
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

#if !defined( _LIBSYSTEM_FILE_H )
#define _LIBSYSTEM_FILE_H

#include <common.h>
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The file access flags
 * bit 1	set to 1 for read access
 * bit 2	set to 1 for write access
 * bit 3	set to 1 to truncate an existing file on write
 * bit 4-8	not used
 */
#define LIBSYSTEM_FILE_ACCESS_FLAG_READ			0x01
#define LIBSYSTEM_FILE_ACCESS_FLAG_WRITE		0x02
#define LIBSYSTEM_FILE_ACCESS_FLAG_TRUNCATE		0x04

/* The file access macros
 */
#define LIBSYSTEM_FILE_OPEN_READ			( LIBSYSTEM_FILE_ACCESS_FLAG_READ )
#define LIBSYSTEM_FILE_OPEN_WRITE			( LIBSYSTEM_FILE_ACCESS_FLAG_WRITE )
#define LIBSYSTEM_FILE_OPEN_READ_WRITE			( LIBSYSTEM_FILE_ACCESS_FLAG_READ | LIBSYSTEM_FILE_ACCESS_FLAG_WRITE )
#define LIBSYSTEM_FILE_OPEN_WRITE_TRUNCATE		( LIBSYSTEM_FILE_ACCESS_FLAG_WRITE | LIBSYSTEM_FILE_ACCESS_FLAG_TRUNCATE )
#define LIBSYSTEM_FILE_OPEN_READ_WRITE_TRUNCATE		( LIBSYSTEM_FILE_ACCESS_FLAG_READ | LIBSYSTEM_FILE_ACCESS_FLAG_WRITE | LIBSYSTEM_FILE_ACCESS_FLAG_TRUNCATE )

/* Platform specific macros
 */
#if defined( WINAPI )

#if defined( _MSC_VER )
#define  LIBSYSTEM_FILE_LARGE_INTEGER_ZERO		{ 0, 0 }

#elif defined( __BORLANDC__ )
#define  LIBSYSTEM_FILE_LARGE_INTEGER_ZERO		{ 0 }

#elif defined( __CYGWIN__ )
#define  LIBSYSTEM_FILE_LARGE_INTEGER_ZERO		{ { 0, 0 } }

#elif defined( __MINGW32_VERSION ) || defined( __MINGW64_VERSION_MAJOR )
#define  LIBSYSTEM_FILE_LARGE_INTEGER_ZERO		{ { 0, 0 } }

#endif

#if !defined( INVALID_FILE_ATTRIBUTES )
#define INVALID_FILE_ATTRIBUTES				((DWORD)-1)
#endif

#endif /* defined( WINAPI ) */

#if defined( WINAPI) && !defined( USE_CRT_FUNCTIONS )
typedef HANDLE libsystem_file_handle_t;

#define LIBSYSTEM_FILE_HANDLE_EMPTY			INVALID_HANDLE_VALUE
#else
typedef int libsystem_file_handle_t;

#define LIBSYSTEM_FILE_HANDLE_EMPTY			-1
#endif

#if defined( HAVE_OPEN ) || defined( WINAPI )
int libsystem_file_open(
     libsystem_file_handle_t *file_handle,
     const libcstring_system_character_t *filename,
     int flags,
     liberror_error_t **error );
#endif

#if defined( HAVE_CLOSE ) || defined( WINAPI )
int libsystem_file_close(
     libsystem_file_handle_t *file_handle,
     liberror_error_t **error );
#endif

#if defined( HAVE_READ ) || defined( WINAPI )
ssize_t libsystem_file_read(
         libsystem_file_handle_t file_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error );
#endif

#if defined( HAVE_WRITE ) || defined( WINAPI )
ssize_t libsystem_file_write(
         libsystem_file_handle_t file_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error );
#endif

#if defined( HAVE_LSEEK ) || defined( WINAPI )
off64_t libsystem_file_seek_offset(
         libsystem_file_handle_t file_handle,
         off64_t offset,
         int whence,
         liberror_error_t **error );
#endif

#if defined( HAVE_FTRUNCATE ) || defined( WINAPI )
int libsystem_file_resize(
     libsystem_file_handle_t file_handle,
     size64_t size,
     liberror_error_t **error );
#endif

#if ( defined( HAVE_OPEN ) && defined( HAVE_CLOSE ) ) || defined( HAVE_STAT ) || defined( WINAPI )
int libsystem_file_exists(
     const libcstring_system_character_t *filename,
     liberror_error_t **error );
#endif

#if defined( __cplusplus )
}
#endif

#endif

