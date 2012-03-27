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

#include <common.h>
#include <types.h>

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#if defined( WINAPI ) && !defined( __CYGWIN__ )
#include <direct.h>
#endif

#if defined( HAVE_DIRENT_H )
#include <dirent.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "libcdirectory_directory.h"
#include "libcdirectory_directory_entry.h"
#include "libcdirectory_libcerror.h"
#include "libcdirectory_libcstring.h"
#include "libcdirectory_types.h"

/* Initializes the directory
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_initialize(
     libcdirectory_directory_t **directory,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_initialize";

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( 1 );
	}
	if( *directory != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory value already set.",
		 function );

		return( -1 );
	}
	internal_directory = memory_allocate_structure(
		              libcdirectory_internal_directory_t );

	if( internal_directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create directory.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_directory,
	     0,
	     sizeof( libcdirectory_internal_directory_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear directory.",
		 function );

		goto on_error;
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	internal_directory->handle = INVALID_HANDLE_VALUE;
#elif defined( WINAPI )
	internal_directory->handle = -1;
#endif
	*directory = (libcdirectory_directory_t *) internal_directory;

	return( 1 );

on_error:
	if( internal_directory != NULL )
	{
		memory_free(
		 internal_directory );
	}
	return( -1 );
}

/* Frees the directory including elements
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_free(
     libcdirectory_directory_t **directory,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_free";
	int result                                             = 1;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( 1 );
	}
	if( *directory != NULL )
	{
		internal_directory = (libcdirectory_internal_directory_t *) *directory;
	
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
		if( internal_directory->handle != INVALID_HANDLE_VALUE )
#elif defined( WINAPI )
		if( internal_directory->handle != -1 )
#else
		if( internal_directory->stream != NULL )
#endif
		{
			if( libcdirectory_directory_close(
			     *directory,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close directory.",
				 function );

				result = -1;
			}
		}
		*directory = NULL;

		memory_free(
		 internal_directory );
	}
	return( result );
}

#if defined( HAVE_OPENDIR ) || defined( WINAPI )

/* Opens a directory
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_open(
     libcdirectory_directory_t *directory,
     const libcstring_system_character_t *directory_name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_open";

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code                                       = 0;
#endif

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
	if( directory_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
#if !defined( USE_CRT_FUNCTIONS )
	if( internal_directory->handle != INVALID_HANDLE_VALUE )
#else
	if( internal_directory->handle != -1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - handle value already set.",
		 function );

		return( -1 );
	}
	if( internal_directory->first_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - first entry value already set.",
		 function );

		return( -1 );
	}
	if( libcdirectory_directory_entry_initialize(
	     &( internal_directory->first_entry ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create first entry.",
		 function );

		return( -1 );
	}
	if( internal_directory->first_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid directory - missing first entry.",
		 function );

		return( -1 );
	}
#if !defined( USE_CRT_FUNCTIONS )
/* TODO add pre Win2k3 support */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	internal_directory->handle = FindFirstFileW(
	                              (LPCWSTR) directory_name,
	                              &( internal_directory->first_entry->find_data ) );
#else
	internal_directory->handle = FindFirstFileA(
	                              (LPCSTR) directory_name,
	                              &( internal_directory->first_entry->find_data ) );
#endif
	if( internal_directory->handle != INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 error_code,
		 "%s: unable to open directory.",
		 function );

		libcdirectory_directory_entry_free(
		 &( internal_directory->first_entry ),
		 NULL );

		return( -1 );
	}

#else
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	internal_directory->handle = _wfindfirst(
	                              (wchar_t *) directory_name,
	                              &( internal_directory->first_entry->find_data ),
	                              0 );
#else
	internal_directory->handle = findfirst(
	                              (char *) directory_name,
	                              &( internal_directory->first_entry->find_data ),
	                              0 );
#endif

#else /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if defined( __BORLANDC__ )
	internal_directory->handle = __wfindfirst(
	                              (wchar_t *) directory_name,
	                              &( internal_directory->first_entry->find_data ) );
#else
	internal_directory->handle = _wfindfirst(
	                              (wchar_t *) directory_name,
	                              &( internal_directory->first_entry->find_data ) );

#endif /* defined( __BORLANDC__ ) */
#else
	internal_directory->handle = _findfirst(
	                              (char *) directory_name,
	                              &( internal_directory->first_entry->find_data ) );

#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */
#endif /* defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520 */

	if( internal_directory->handle == -1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 errno,
		 "%s: unable to open directory.",
		 function );

		return( -1 );
	}

#endif /* !defined( USE_CRT_FUNCTIONS ) */
#elif defined( HAVE_OPENDIR )
/* Sanity check
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#error Missing wide character opendir function
#endif
	if( internal_directory->stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - stream value already set.",
		 function );

		return( -1 );
	}
	internal_directory->stream = opendir(
	                              directory_name );

	if( internal_directory->stream == NULL )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 errno,
		 "%s: unable to open directory.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

#endif /* defined( HAVE_OPENDIR ) || defined( WINAPI ) */

#if defined( HAVE_CLOSEDIR ) || defined( WINAPI )

/* Closes a directory
 * Returns 0 if successful or -1 on error
 */
int libcdirectory_directory_close(
     libcdirectory_directory_t *directory,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory = NULL;
	static char *function                                  = "libcdirectory_directory_close";
	int result                                             = 0;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code                                       = 0;
#endif

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
#if defined( WINAPI )
#if !defined( USE_CRT_FUNCTIONS )
	if( internal_directory->handle != INVALID_HANDLE_VALUE )
	{
/* TODO add pre Win2k3 support */
		if( FindClose(
		     internal_directory->handle ) != 0 )
		{
			error_code = GetLastError();

			libcerror_system_set_error(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 error_code,
			 "%s: unable to close directory.",
			 function );

			result = -1;
		}
		internal_directory->handle = INVALID_HANDLE_VALUE;
	}
#else
	if( internal_directory->handle != -1 )
	{
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
		if( findclose(
		     internal_directory->handle ) != 0 )
#else
		if( _findclose(
		     internal_directory->handle ) != 0 )
#endif
		{
			libcerror_system_set_error(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 errno,
			 "%s: unable to close directory.",
			 function );

			result = -1;
		}
		internal_directory->handle = -1;
	}
#endif
	if( internal_directory->first_entry != NULL )
	{
		if( libcdirectory_directory_entry_free(
		     &( internal_directory->first_entry ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free first entry.",
			 function );

			result = -1;
		}
	}
#elif defined( HAVE_CLOSEDIR )
	if( internal_directory->stream != NULL )
	{
		if( closedir(
		     internal_directory->stream ) != 0 )
		{
			libcerror_system_set_error(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 errno,
			 "%s: unable to close directory.",
			 function );

			result = -1;
		}
		internal_directory->stream = NULL;
	}
#endif
	return( result );
}

#endif /* defined( HAVE_CLOSEDIR ) || defined( WINAPI ) */

#if defined( HAVE_READDIR_R ) || defined( WINAPI )

/* Reads a directory
 * Returns 1 if successful, 0 if no such entry or -1 on error
 */
int libcdirectory_directory_read_entry(
     libcdirectory_directory_t *directory,
     libcdirectory_directory_entry_t *directory_entry,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_t *internal_directory             = NULL;
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_read_entry";

#if defined( WINAPI )
	size_t finddata_size                                               = 0;
#endif
#if defined( HAVE_READDIR_R )
	struct dirent *result_directory_entry                              = NULL;
#endif
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code                                                   = 0;
#else
	int result                                                         = 0;
#endif

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	internal_directory = (libcdirectory_internal_directory_t *) directory;
	
	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( -1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

#if defined( WINAPI )
#if !defined( USE_CRT_FUNCTIONS )
	if( internal_directory->handle != INVALID_HANDLE_VALUE )
#else
	if( internal_directory->handle != -1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory - handle value already set.",
		 function );

		return( -1 );
	}
	if( internal_directory->first_entry != NULL )
	{
#if !defined( USE_CRT_FUNCTIONS )
		finddata_size = sizeof( WIN32_FIND_DATA );

#elif defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		finddata_size = sizeof( struct _wffblk find_data );
#else
		finddata_size = sizeof( struct ffblk find_data );
#endif

#else
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		finddata_size = sizeof( struct _wfinddata_t find_data );
#else
		finddata_size = sizeof( struct _finddata_t find_data );
#endif

#endif
		if( memory_copy(
		     &( internal_directory_entry->find_data ),
		     &( internal_directory->first_entry->find_data ),
		     finddata_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to set directory entry.",
			 function );

			return( -1 );
		}
		if( libcdirectory_directory_entry_free(
		     &( internal_directory->first_entry ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free first entry.",
			 function );

			return( -1 );
		}
	}
	else
	{
#if !defined( USE_CRT_FUNCTIONS )
/* TODO add pre Win2k3 support */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		if( FindNextFileW(
		     internal_directory->handle,
		     &( internal_directory_entry->find_data ) ) != 0 )
#else
		if( FindNextFileA(
		     internal_directory->handle,
		     &( internal_directory_entry->find_data ) ) != 0 )
#endif
		{
			error_code = GetLastError();

			if( error_code == ERROR_NO_MORE_FILES )
			{
				return( 0 );
			}
			else
			{
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 error_code,
				 "%s: unable to read from directory.",
				 function );
			}
			return( -1 );
		}
#else
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = _wfindnext(
		          internal_directory->handle,
		          &( internal_directory->first_entry->find_data ),
		          0 );
#else
		result = findnext(
		          internal_directory->handle,
		          &( internal_directory->first_entry->find_data ),
		          0 );
#endif

#else /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if defined( __BORLANDC__ )
		result = __wfindnext(
		          internal_directory->handle,
		          &( internal_directory->first_entry->find_data ) );
#else
		result = _wfindnext(
		          internal_directory->handle,
		          &( internal_directory->first_entry->find_data ) );

#endif /* defined( __BORLANDC__ ) */
#else
		result = _findnext(
		          internal_directory->handle,
		          &( internal_directory->first_entry->find_data ) );

#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */
#endif /* defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520 */

		if( result != 0 )
		{
			libcerror_system_set_error(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 errno,
			 "%s: unable to read from directory.",
			 function );

			return( -1 );
		}
#endif
	}
#elif defined( HAVE_READDIR_R )
	if( internal_directory->stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid directory - missing stream.",
		 function );

		return( -1 );
	}
	result = readdir_r(
	          internal_directory->stream,
	          &( internal_directory_entry->entry ),
	          &result_directory_entry );

	if( result != 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 errno,
		 "%s: unable to read from directory.",
		 function );

		return( -1 );
	}
	if( result_directory_entry == NULL )
	{
		return( 0 );
	}
#endif
	return( 1 );
}

#endif /* defined( HAVE_READDIR_R ) || defined( WINAPI ) */

