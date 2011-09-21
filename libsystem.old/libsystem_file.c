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

#include <common.h>
#include <memory.h>
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#include <share.h>
#endif

#include "libsystem_error_string.h"
#include "libsystem_file.h"
#include "libsystem_file_io.h"

#if defined( HAVE_OPEN ) || defined( WINAPI )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int libsystem_file_open(
     libsystem_file_handle_t *file_handle,
     const libcstring_system_character_t *filename,
     int flags,
     liberror_error_t **error )
{
	libcstring_system_character_t error_string[ 128 ];

	static char *function        = "libsystem_file_open";

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code             = 0;
	DWORD file_io_access_flags   = 0;
	DWORD file_io_creation_flags = 0;
	DWORD file_io_shared_flags   = 0;
#else
#if defined( WINAPI )
	int file_io_shared_flags     = 0;
	int file_io_permission_flags = 0;
#endif
	int file_io_flags            = 0;
#endif

	if( file_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( ( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_READ ) != 0 )
	 && ( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_WRITE ) != 0 ) )
	{
		file_io_access_flags   = GENERIC_WRITE | GENERIC_READ;
		file_io_creation_flags = OPEN_ALWAYS;
		file_io_shared_flags   = FILE_SHARE_READ;
	}
	else if( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_READ ) != 0 )
	{
		file_io_access_flags   = GENERIC_READ;
		file_io_creation_flags = OPEN_EXISTING;
		file_io_shared_flags   = FILE_SHARE_READ;
	}
	else if( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_WRITE ) != 0 )
	{
		file_io_access_flags   = GENERIC_WRITE;
		file_io_creation_flags = OPEN_ALWAYS;
		file_io_shared_flags   = 0;
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.",
		 function );

		return( -1 );
	}
	if( ( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_WRITE ) != 0 )
	 && ( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_TRUNCATE ) != 0 ) )
	{
		file_io_creation_flags = CREATE_ALWAYS;
	}
	*file_handle = CreateFile(
	                (LPCTSTR) filename,
	                file_io_access_flags,
	                file_io_shared_flags,
	                NULL,
	                file_io_creation_flags,
	                FILE_ATTRIBUTE_NORMAL,
	                NULL );

	if( *file_handle == INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				if( libsystem_error_string_copy_from_error_number(
				     error_string,
				     128,
				     error_code,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM " with error: %" PRIs_LIBCSTRING_SYSTEM "",
					 function,
					 filename,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
					 function,
					 filename );
				}
				break;
		}
		return( -1 );
	}
#else
	if( ( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_READ ) != 0 )
	 && ( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_WRITE ) != 0 ) )
	{
#if defined( WINAPI )
		file_io_flags            = _O_RDWR | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
#else
		file_io_flags = O_RDWR | O_CREAT;
#endif
#if defined( _MSC_VER )
		file_io_shared_flags = _SH_DENYWR;
#endif
	}
	else if( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_READ ) != 0 )
	{
#if defined( WINAPI )
		file_io_flags = _O_RDONLY;
#else
		file_io_flags = O_RDONLY;
#endif
#if defined( _MSC_VER )
		file_io_shared_flags = _SH_DENYWR;
#endif
	}
	else if( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_WRITE ) != 0 )
	{
#if defined( WINAPI )
		file_io_flags            = _O_WRONLY | _O_CREAT;
		file_io_permission_flags = _S_IREAD | _S_IWRITE;
#else
		file_io_flags = O_WRONLY | O_CREAT;
#endif
#if defined( _MSC_VER )
		file_io_shared_flags = _SH_DENYRW;
#endif
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.",
		 function );

		return( -1 );
	}
	if( ( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_WRITE ) != 0 )
	 && ( ( flags & LIBSYSTEM_FILE_ACCESS_FLAG_TRUNCATE ) != 0 ) )
	{
#if defined( WINAPI )
		file_io_flags |= _O_TRUNC;
#else
		file_io_flags |= O_TRUNC;
#endif
	}
#if defined( WINAPI )
#if defined( _MSC_VER )
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( _wsopen_s(
	     file_handle,
	     (wchar_t *) filename,
	     file_io_flags | _O_BINARY,
	     file_io_shared_flags,
	     file_io_permission_flags ) != 0 )
#else
	if( _sopen_s(
	     file_handle,
	     (char *) filename,
	     file_io_flags | _O_BINARY,
	     file_io_shared_flags,
	     file_io_permission_flags ) != 0 )
#endif /* LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER */
#else
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	*file_handle = _wsopen(
	                (wchar_t *) filename,
	                file_io_flags | _O_BINARY,
	                file_io_permission_flags );
#else
	*file_handle = _sopen(
	                (char *) filename,
	                file_io_flags | _O_BINARY,
	                file_io_permission_flags );
#endif /* LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER */
	if( *file_handle == -1 )
#endif /* _MSC_VER */
	{
		switch( errno )
		{
			case EACCES:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ENOENT:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				if( libsystem_error_string_copy_from_error_number(
				     error_string,
				     128,
				     errno,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM " with error: %" PRIs_LIBCSTRING_SYSTEM "",
					 function,
					 filename,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
					 function,
					 filename );
				}
				break;
		}
		return( -1 );
	}
#if defined( _MSC_VER )
	if( *file_handle == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: invalid file handle: %d returned.",
		 function,
		 *file_handle );

		return( -1 );
	}
#endif
#else
/* Sanity check
*/
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#error Missing wide character open function
#endif

	*file_handle = open(
	                (char *) filename,
	                file_io_flags,
	                0644 );

	if( *file_handle == -1 )
	{
		switch( errno )
		{
			case EACCES:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			case ENOENT:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 filename );

				break;

			default:
				if( libsystem_error_string_copy_from_error_number(
				     error_string,
				     128,
				     errno,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM " with error: %" PRIs_LIBCSTRING_SYSTEM "",
					 function,
					 filename,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
					 function,
					 filename );
				}
				break;
		}
		return( -1 );
	}
#endif
#endif
	return( 1 );
}

#endif

#if defined( HAVE_CLOSE ) || defined( WINAPI )

/* Closes the file handle
 * Returns 0 if successful or -1 on error
 */
int libsystem_file_close(
     libsystem_file_handle_t *file_handle,
     liberror_error_t **error )
{
	libcstring_system_character_t error_string[ 128 ];

	static char *function = "libsystem_file_close";

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code      = 0;
#endif

	if( file_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( *file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( *file_handle == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#endif
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( CloseHandle(
	     *file_handle ) == 0 )
	{
		error_code = GetLastError();

		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     error_code,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file.",
			 function );
		}
		return( -1 );
	}
	*file_handle = INVALID_HANDLE_VALUE;
#else
#if defined( WINAPI )
	if( _close(
	     *file_handle ) != 0 )
#else
	if( close(
	     *file_handle ) != 0 )
#endif
	{
		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     errno,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file.",
			 function );
		}
		return( -1 );
	}
	*file_handle = -1;
#endif
	return( 0 );
}

#endif

#if defined( HAVE_READ ) || defined( WINAPI )

/* Reads a buffer from the file handle
 * Returns the number of bytes read if successful, or -1 on error
 */
ssize_t libsystem_file_read(
         libsystem_file_handle_t file_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libcstring_system_character_t error_string[ 128 ];

	static char *function = "libsystem_file_read";
	ssize_t read_count    = 0;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code      = 0;
#endif

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( file_handle == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#endif
	if( buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
#if UINT32_MAX < SSIZE_MAX
	if( size > (size_t) UINT32_MAX )
#else
	if( size > (size_t) SSIZE_MAX )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( ReadFile(
	     file_handle,
	     buffer,
	     (DWORD) size,
	     (LPDWORD) &read_count,
	     NULL ) == 0 )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_HANDLE_EOF:
				break;

			default:
				if( libsystem_error_string_copy_from_error_number(
				     error_string,
				     128,
				     error_code,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to read from file with error: %" PRIs_LIBCSTRING_SYSTEM "",
					 function,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to read from file.",
					 function );
				}
				break;
		}
		return( -1 );
	}
	if( read_count < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: invalid read count: %" PRIzd " returned.",
		 function,
		 read_count );
	}
#else
#if defined( WINAPI )
	read_count = _read(
	              file_handle,
	              (void *) buffer,
	              (unsigned int) size );
#else
	read_count = read(
	              file_handle,
	              (void *) buffer,
	              size );
#endif

	if( read_count < 0 )
	{
		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     errno,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to read from file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to read from file.",
			 function );
		}
		return( -1 );
	}
#endif
	return( read_count );
}

#endif

#if defined( HAVE_WRITE ) || defined( WINAPI )

/* Writes a buffer to the file handle
 * Returns the number of bytes written if successful, or -1 on error
 */
ssize_t libsystem_file_write(
         libsystem_file_handle_t file_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libcstring_system_character_t error_string[ 128 ];

	static char *function = "libsystem_file_write";
	ssize_t write_count   = 0;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code      = 0;
#endif

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( file_handle == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#endif
	if( buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
#if UINT32_MAX < SSIZE_MAX
	if( size > (size_t) UINT32_MAX )
#else
	if( size > (size_t) SSIZE_MAX )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( WriteFile(
	     file_handle,
	     buffer,
	     (DWORD) size,
	     (LPDWORD) &write_count,
	     NULL ) == 0 )
	{
		error_code = GetLastError();

		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     error_code,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to write to file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to write to file.",
			 function );
		}
		return( -1 );
	}
	if( write_count < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_WRITE_FAILED,
		 "%s: invalid write count: %" PRIzd " returned.",
		 function,
		 write_count );
	}
#else
#if defined( WINAPI )
	write_count = _write(
	               file_handle,
	               (void *) buffer,
	               (unsigned int) size );
#else
	write_count = write(
	               file_handle,
	               (void *) buffer,
	               size );
#endif

	if( write_count < 0 )
	{
		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     errno,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to write to file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to write to file.",
			 function );
		}
		return( -1 );
	}
#endif
	return( write_count );
}

#endif

#if defined( HAVE_LSEEK ) || defined( WINAPI )

/* Seeks a certain offset within the file handle
 * Returns the offset if the seek is successful or -1 on error
 */
off64_t libsystem_file_seek_offset(
         libsystem_file_handle_t file_handle,
         off64_t offset,
         int whence,
         liberror_error_t **error )
{
	libcstring_system_character_t error_string[ 128 ];

	static char *function              = "libsystem_file_seek_offset";

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	LARGE_INTEGER large_integer_offset = LIBSYSTEM_FILE_LARGE_INTEGER_ZERO;
	DWORD error_code                   = 0;
	DWORD move_method                  = 0;
#endif

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( file_handle == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#endif
	if( offset > (off64_t) INT64_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid offset value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( whence == SEEK_SET )
	{
		move_method = FILE_BEGIN;
	}
	else if( whence == SEEK_CUR )
	{
		move_method = FILE_CURRENT;
	}
	else if( whence == SEEK_END )
	{
		move_method = FILE_END;
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	large_integer_offset.QuadPart = (LONGLONG) offset;
#else
	large_integer_offset.LowPart  = (DWORD) ( 0x0ffffffff & offset );
	large_integer_offset.HighPart = (LONG) ( offset >> 32 );
#endif

	if( SetFilePointerEx(
	     file_handle,
	     large_integer_offset,
	     &large_integer_offset,
	     move_method ) == 0 )
	{
		error_code = GetLastError();

		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     error_code,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to find offset in file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to find offset in file.",
			 function );
		}
		return( -1 );
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	offset = (off64_t) large_integer_offset.QuadPart;
#else
	offset = ( (off64_t) large_integer_offset.HighPart << 32 ) + large_integer_offset.LowPart;
#endif

	if( offset < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: invalid offset: %" PRIi64 " returned.",
		 function,
		 offset );

		return( -1 );
	}
#else
#if defined( WINAPI )
	offset = _lseeki64(
	          file_handle,
	          offset,
	          whence );
#else
	offset = lseek(
	          file_handle,
	          (off_t) offset,
	          whence );
#endif
	if( offset < 0 )
	{
		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     errno,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to find offset in file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to find offset in file.",
			 function );
		}
		return( -1 );
	}
#endif
	return( offset );
}

#endif

#if defined( HAVE_FTRUNCATE ) || defined( WINAPI )

/* Resizes the file handle
 * Returns 1 if successful or -1 on error
 */
int libsystem_file_resize(
     libsystem_file_handle_t file_handle,
     size64_t size,
     liberror_error_t **error )
{
	libcstring_system_character_t error_string[ 128 ];

	static char *function              = "libsystem_file_resize";

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	off64_t offset                     = 0;
	LARGE_INTEGER large_integer_offset = LIBSYSTEM_FILE_LARGE_INTEGER_ZERO;
	DWORD error_code                   = 0;
#endif

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( file_handle == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file handle.",
		 function );

		return( -1 );
	}
#endif
	if( size > (size64_t) INT64_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	large_integer_offset.QuadPart = (LONGLONG) size;
#else
	large_integer_offset.LowPart  = (DWORD) ( 0x0ffffffff & size );
	large_integer_offset.HighPart = (LONG) ( size >> 32 );
#endif

	if( SetFilePointerEx(
	     file_handle,
	     large_integer_offset,
	     &large_integer_offset,
	     FILE_BEGIN ) == 0 )
	{
		error_code = GetLastError();

		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     error_code,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to find offset in file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to find offset in file.",
			 function );
		}
		return( -1 );
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	offset = (off64_t) large_integer_offset.QuadPart;
#else
	offset = ( (off64_t) large_integer_offset.HighPart << 32 ) + large_integer_offset.LowPart;
#endif

	if( offset < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: invalid offset: %" PRIi64 " returned.",
		 function,
		 offset );

		return( -1 );
	}
	if( SetEndOfFile(
	     file_handle ) == 0 )
	{
		error_code = GetLastError();

		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     error_code,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to resize file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to resize file.",
			 function );
		}
		return( -1 );
	}
#else
#if defined( WINAPI )
	if( _chsize(
	     file_handle,
	     size ) != 0 )
#else
	if( ftruncate(
	     file_handle,
	     size ) != 0 )
#endif
	{
		if( libsystem_error_string_copy_from_error_number(
		     error_string,
		     128,
		     errno,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to resize file with error: %" PRIs_LIBCSTRING_SYSTEM "",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to resize file.",
			 function );
		}
		return( -1 );
	}
#endif
	return( 1 );
}

#endif

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS ) && ( WINVER >= 0x0500 )

/* Determines if a file exists
 * Optimized version for Windows 2000 (WINAPI 5) or later
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libsystem_file_exists(
     const libcstring_system_character_t *filename,
     liberror_error_t **error )
{
	libcstring_system_character_t error_string[ 128 ];

	static char *function = "libsystem_file_exists";
	int result            = 1;
	DWORD error_code      = 0;
	DWORD file_attributes = 0;

	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	/* Must use GetFileAttributesW here because filename is a 
	 * wide character string and GetFileAttributes is dependent
	 * on UNICODE directives
	 */
	file_attributes = GetFileAttributesW(
	                   (LPCWSTR) filename );
#else
	/* Must use GetFileAttributesA here because filename is a 
	 * narrow character string and GetFileAttributes is dependent
	 * on UNICODE directives
	 */
	file_attributes = GetFileAttributesA(
	                   (LPCSTR) filename );
#endif
	if( file_attributes == INVALID_FILE_ATTRIBUTES )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				result = 1;

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				result = 0;

				break;

			default:
				if( libsystem_error_string_copy_from_error_number(
				     error_string,
				     128,
				     error_code,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_GENERIC,
					 "%s: unable to determine attributes of file: %" PRIs_LIBCSTRING_SYSTEM " with error: %" PRIs_LIBCSTRING_SYSTEM "",
					 function,
					 filename,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_GENERIC,
					 "%s: unable to determine attributes of file: %" PRIs_LIBCSTRING_SYSTEM ".",
					 function,
					 filename );
				}
				result = -1;

				break;
		}
	}
	return( result );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* Determines if a file exists
 * WINAPI version
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libsystem_file_exists(
     const libcstring_system_character_t *filename,
     liberror_error_t **error )
{
	libcstring_system_character_t error_string[ 128 ];

	libsystem_file_handle_t file_handle = LIBSYSTEM_FILE_HANDLE_EMPTY;
	static char *function               = "libsystem_file_exists";
	int result                          = 1;
	DWORD error_code                    = 0;

	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	/* Must use CreateFileW here because filename is a 
	 * wide character string and CreateFile is dependent
	 * on UNICODE directives
	 */
	file_handle = CreateFileW(
	               (LPCWSTR) filename,
	               GENERIC_READ,
	               FILE_SHARE_READ,
	               NULL,
	               OPEN_EXISTING,
	               FILE_ATTRIBUTE_NORMAL,
	               NULL );
#else
	/* Must use CreateFileA here because filename is a 
	 * narrow character string and CreateFile is dependent
	 * on UNICODE directives
	 */
	file_handle = CreateFileA(
	               (LPCSTR) filename,
	               GENERIC_READ,
	               FILE_SHARE_READ,
	               NULL,
	               OPEN_EXISTING,
	               FILE_ATTRIBUTE_NORMAL,
	               NULL );
#endif
	if( file_handle == INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				result = 1;

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				result = 0;

				break;

			default:
				if( libsystem_error_string_copy_from_error_number(
				     error_string,
				     128,
				     error_code,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM " with error: %" PRIs_LIBCSTRING_SYSTEM "",
					 function,
					 filename,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
					 function,
					 filename );
				}
				result = -1;

				break;
		}
	}
	else if( CloseHandle(
	          file_handle ) == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file: %s.",
		 function,
		 filename );

		return( -1 );
	}
	file_handle = INVALID_HANDLE_VALUE;

	return( result );
}

#elif defined( HAVE_STAT ) && !defined( WINAPI )

/* Determines if a file exists
 * Optimized version for platforms with the stat function
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libsystem_file_exists(
     const libcstring_system_character_t *filename,
     liberror_error_t **error )
{
	struct stat file_statistics;

	libcstring_system_character_t error_string[ 128 ];

	static char *function = "libsystem_file_exists";
	int result            = 0;

	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#error Missing wide character stat function
#endif
	result = stat(
	          (char *) filename,
	          &file_statistics );

	if( result != 0 )
	{
		switch( errno )
		{
			case EACCES:
				result = 1;

				break;

			case ENOENT:
				result = 0;

				break;

			default:
				if( libsystem_error_string_copy_from_error_number(
				     error_string,
				     128,
				     errno,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_GENERIC,
					 "%s: unable to stat file: %" PRIs_LIBCSTRING_SYSTEM " with error: %" PRIs_LIBCSTRING_SYSTEM "",
					 function,
					 filename,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_GENERIC,
					 "%s: unable to stat file: %" PRIs_LIBCSTRING_SYSTEM ".",
					 function,
					 filename );
				}
				result = -1;

				break;
		}
	}
	else
	{
		result = 1;
	}
	return( result );
}

#elif ( defined( HAVE_OPEN ) && defined( HAVE_CLOSE ) ) || defined( WINAPI )

/* Determines if a file exists
 * Returns 1 if the file exists, 0 if not or -1 on error
 */
int libsystem_file_exists(
     const libcstring_system_character_t *filename,
     liberror_error_t **error )
{
	libcstring_system_character_t error_string[ 128 ];

	libsystem_file_handle_t file_handle = LIBSYSTEM_FILE_HANDLE_EMPTY;
	static char *function               = "libsystem_file_exists";
	int result                          = 1;

	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if defined( _MSC_VER )
	if( _wsopen_s(
	     &file_handle,
	     (wchar_t *) filename,
	     _O_RDONLY | _O_BINARY,
	     _SH_DENYWR,
	     0 ) != 0 )
	{
		file_handle = -1;
	}
#elif defined( WINAPI )
	file_handle = _wsopen(
	               (wchar_t *) filename,
	               _O_RDONLY | _O_BINARY,
	               0 );
#else
#error Missing wide character open function
#endif

#else
#if defined( _MSC_VER )
	if( _sopen_s(
	     &file_handle,
	     (char *) filename,
	     _O_RDONLY | _O_BINARY,
	     _SH_DENYWR,
	     0 ) != 0 )
	{
		file_handle = -1;
	}
#elif defined( WINAPI )
	file_handle = _sopen(
	               (char *) filename,
	               _O_RDONLY | _O_BINARY,
	               0 );
#else
	file_handle = open(
	               (char *) filename,
	               O_RDONLY,
	               0644 );
#endif
#endif
	if( file_handle == -1 )
	{
		switch( errno )
		{
			case EACCES:
				result = 1;

				break;

			case ENOENT:
				result = 0;

				break;

			default:
				if( libsystem_error_string_copy_from_error_number(
				     error_string,
				     128,
				     errno,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM " with error: %" PRIs_LIBCSTRING_SYSTEM "",
					 function,
					 filename,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBCSTRING_SYSTEM ".",
					 function,
					 filename );
				}
				result = -1;

				break;
		}
	}
	else if( libsystem_file_io_close(
		  file_handle ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file: %s.",
		 function,
		 filename );

		return( -1 );
	}
	file_handle = -1;

	return( result );
}

#endif

