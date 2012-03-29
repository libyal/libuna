/*
 * Directory entry functions
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

#include "libcdirectory_definitions.h"
#include "libcdirectory_directory_entry.h"
#include "libcdirectory_libcerror.h"
#include "libcdirectory_libcstring.h"
#include "libcdirectory_types.h"

/* Initializes the directory entry
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_initialize(
     libcdirectory_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_initialize";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( 1 );
	}
	if( *directory_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory entry value already set.",
		 function );

		return( -1 );
	}
	internal_directory_entry = memory_allocate_structure(
			            libcdirectory_internal_directory_entry_t );

	if( internal_directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create directory entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_directory_entry,
	     0,
	     sizeof( libcdirectory_internal_directory_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear directory entry.",
		 function );

		goto on_error;
	}
	*directory_entry = (libcdirectory_directory_entry_t *) internal_directory_entry;

	return( 1 );

on_error:
	if( internal_directory_entry != NULL )
	{
		memory_free(
		 internal_directory_entry );
	}
	return( -1 );
}

/* Frees the directory entry including elements
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_free(
     libcdirectory_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_free";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( 1 );
	}
	if( *directory_entry != NULL )
	{
		internal_directory_entry = (libcdirectory_internal_directory_entry_t *) *directory_entry;
		*directory_entry         = NULL;

		memory_free(
		 internal_directory_entry );
	}
	return( 1 );
}

#if defined( WINAPI ) && ( WINVER >= 0x0501 ) && !defined( USE_CRT_FUNCTIONS )

/* Retrieves the directory entry type
 * This function uses the WINAPI directory entry structure for Windows XP or later
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_type(
     libcdirectory_directory_entry_t *directory_entry,
     uint8_t *type,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_type";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( 1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( 1 );
	}
	if( ( internal_directory_entry->find_data.dwFileAttributes & FILE_ATTRIBUTE_DEVICE ) != 0 )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_DEVICE;
	}
	else if( ( internal_directory_entry->find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) != 0 )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_DIRECTORY;
	}
	else if( ( internal_directory_entry->find_data.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT ) != 0 )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_LINK;
	}
	else
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_FILE;
	}
	return( 1 );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI directory entry structure for Windows 2000 or earlier NOT implemented yet

#elif defined( WINAPI ) && defined( USE_CRT_FUNCTIONS )

/* Retrieves the directory entry type
 * This function uses the Visual Studio C runtime library directory entry structure or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_type(
     libcdirectory_directory_entry_t *directory_entry,
     uint8_t *type,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_type";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( 1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( 1 );
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	if( ( internal_directory_entry->find_data.ff_attrib & FA_DIREC ) != 0 )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_DIRECTORY;
	}
	else
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_FILE;
	}
#else
	if( ( internal_directory_entry->find_data.attrib & _A_SUBDIR ) != 0 )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_DIRECTORY;
	}
	else
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_FILE;
	}
#endif
	return( 1 );
}

#elif defined( HAVE_DIRENT_H )

/* Retrieves the directory entry type
 * This function uses the POSIX directory entry structure
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_type(
     libcdirectory_directory_entry_t *directory_entry,
     uint8_t *type,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_type";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( 1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( 1 );
	}
	if( ( internal_directory_entry->entry.d_type == DT_BLK )
	 || ( internal_directory_entry->entry.d_type == DT_CHR ) )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_DEVICE;
	}
	else if( internal_directory_entry->entry.d_type == DT_DIR )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_DIRECTORY;
	}
	else if( internal_directory_entry->entry.d_type == DT_FIFO )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_PIPE;
	}
	else if( internal_directory_entry->entry.d_type == DT_LNK )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_LINK;
	}
	else if( internal_directory_entry->entry.d_type == DT_REG )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_FILE;
	}
	else if( internal_directory_entry->entry.d_type == DT_SOCK )
	{
		*type = LIBCDIRECTORY_DIRECTORY_ENTRY_TYPE_SOCKET;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported type.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#else
#error Missing directory entry structure definition
#endif

#if defined( WINAPI ) && ( WINVER >= 0x0501 ) && !defined( USE_CRT_FUNCTIONS )

/* Retrieves the directory entry name
 * This function uses the WINAPI directory entry structure for Windows XP or later
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_name(
     libcdirectory_directory_entry_t *directory_entry,
     libcstring_system_character_t **name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_name";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( 1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( 1 );
	}
	*name = internal_directory_entry->find_data.cFileName;

	return( 1 );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI directory entry structure for Windows 2000 or earlier NOT implemented yet

#elif defined( WINAPI ) && defined( USE_CRT_FUNCTIONS )

/* Retrieves the directory entry name
 * This function uses the Visual Studio C runtime library directory entry structure or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_name(
     libcdirectory_directory_entry_t *directory_entry,
     libcstring_system_character_t **name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_name";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( 1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( 1 );
	}
#if defined( __BORLANDC__ ) && __BORLANDC__ <= 0x0520
	*name = internal_directory_entry->find_data.ff_name;
#else
	*name = internal_directory_entry->find_data.name;
#endif
	return( 1 );
}

#elif defined( HAVE_DIRENT_H )

/* Retrieves the directory entry name
 * This function uses the POSIX directory entry structure
 * Returns 1 if successful or -1 on error
 */
int libcdirectory_directory_entry_get_name(
     libcdirectory_directory_entry_t *directory_entry,
     libcstring_system_character_t **name,
     libcerror_error_t **error )
{
	libcdirectory_internal_directory_entry_t *internal_directory_entry = NULL;
	static char *function                                              = "libcdirectory_directory_entry_get_name";

	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry.",
		 function );

		return( 1 );
	}
	internal_directory_entry = (libcdirectory_internal_directory_entry_t *) directory_entry;

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( 1 );
	}
/* Sanity check
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#error Missing wide character directory entry name
#endif

	*name = internal_directory_entry->entry.d_name;

	return( 1 );
}

#else
#error Missing directory entry structure definition
#endif

