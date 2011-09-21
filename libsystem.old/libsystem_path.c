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

#include <common.h>
#include <memory.h>
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#include "libsystem_path.h"
#include "libsystem_split_values.h"

enum LIBSYSTEM_PATH_TYPES
{
	LIBSYSTEM_PATH_TYPE_ABSOLUTE,
	LIBSYSTEM_PATH_TYPE_RELATIVE,
	LIBSYSTEM_PATH_TYPE_UNC
};

/* Creates the path from the basename and filename
 * Returns 1 if successful or -1 on error
 */
int libsystem_path_create(
     const libcstring_system_character_t *filename,
     size_t filename_length,
     const libcstring_system_character_t *basename,
     size_t basename_length,
     libcstring_system_character_t **path,
     size_t *path_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_path_create";
	size_t path_index     = 0;

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
	if( filename_length > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid filename length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( basename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename.",
		 function );

		return( -1 );
	}
	if( basename_length > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid basename length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( *path != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid path already set.",
		 function );

		return( -1 );
	}
	if( path_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path size.",
		 function );

		return( -1 );
	}
	/* Include space for the separator and the end of string character
	 */
	*path_size = basename_length + filename_length + 2;

	*path = libcstring_system_string_allocate(
	         *path_size );

	if( *path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create path.",
		 function );

		goto on_error;
	}
	if( libcstring_system_string_copy(
	     *path,
	     basename,
	     basename_length ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy basename to path.",
		 function );

		goto on_error;
	}
	path_index = basename_length;

	( *path )[ path_index++ ] = (libcstring_system_character_t) LIBSYSTEM_PATH_SEPARATOR;

	if( libcstring_system_string_copy(
	     &( ( *path )[ path_index ] ),
	     filename,
	     filename_length ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filename to path.",
		 function );

		goto on_error;
	}
	path_index += filename_length;

	( *path )[ path_index ] = 0;

	return( 1 );

on_error:
	if( *path != NULL )
	{
		memory_free(
		 path );

		*path = NULL;
	}
	*path_size = 0;

	return( -1 );
}

#if defined( WINAPI )

/* Creates a Windows extended-length path from a path (path with \\?\ prefix)
 *
 * Possible scenario's that are not extended:
 * Device path:			\\.\PhysicalDrive0
 * Extended-length path:	\\?\C:\directory\file.txt
 * Extended-length UNC path:	\\?\UNC\server\share\directory\file.txt
 *
 * Possible scenario's that are extended:
 * Local 'absolute' path:	\directory\file.txt
 * Local 'relative' path:	..\directory\file.txt
 * Local 'relative' path:	.\directory\file.txt
 * Volume 'absolute' path:	C:\directory\file.txt
 * Volume 'relative' path:	C:directory\file.txt
 * UNC path:			\\server\share\directory\file.txt
 *
 * This function does not support paths like (although Windows does):
 * C:\..\directory\file.txt
 *
 * Returns 1 if succesful, 0 if the path cannot be converted into an extended-length path, or -1 on error
 */
int libsystem_path_create_windows_extended(
     const libcstring_system_character_t *path,
     size_t path_length,
     libcstring_system_character_t **extended_path,
     size_t *extended_path_size,
     liberror_error_t **error )
{
	libcstring_system_character_t *change_volume_name        = NULL;
	libcstring_system_character_t *current_working_directory = NULL;
	libcstring_system_character_t *current_directory         = NULL;
	libcstring_system_character_t *volume_name               = NULL;
	libsystem_split_values_t *current_directory_split_values = NULL;
	libsystem_split_values_t *path_split_values              = NULL;
	static char *function                                    = "libsystem_path_create_windows_extended";
	size_t current_directory_name_index                      = 0;
	size_t extended_path_index                               = 0;
	size_t path_directory_name_index                         = 0;
	size_t share_name_index                                  = 0;
	size_t volume_name_length                                = 0;
	DWORD current_directory_size                             = 0;
	DWORD current_working_directory_size                     = 0;
	uint8_t path_type                                        = LIBSYSTEM_PATH_TYPE_RELATIVE;
	int error_abort                                          = 0;
	int current_directory_split_value_iterator               = 0;
	int last_used_path_split_value_iterator                  = 0;
	int path_split_value_iterator                            = 0;

	if( path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid path length is zero.",
		 function );

		return( -1 );
	}
	if( path_length >= (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( extended_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extended path.",
		 function );

		return( -1 );
	}
	if( *extended_path != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid extended path value already set.",
		 function );

		return( -1 );
	}
	if( extended_path_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extended path size.",
		 function );

		return( -1 );
	}
	if( path_length >= 2 )
	{
		/* Check if the path starts with a volume letter
		 */
		if( ( path[ 1 ] == (libcstring_system_character_t) ':' )
		 && ( ( ( path[ 0 ] >= (libcstring_system_character_t) 'A' )
		   && ( path[ 0 ] <= (libcstring_system_character_t) 'Z' ) )
		  || ( ( path[ 0 ] >= (libcstring_system_character_t) 'a' )
		   && ( path[ 0 ] <= (libcstring_system_character_t) 'z' ) ) ) )
		{
			volume_name               = (libcstring_system_character_t *) &( path[ 0 ] );
			volume_name_length        = 2;
			path_directory_name_index = 2;

			if( ( path_length >= 3 )
			 && ( path[ 2 ] == (libcstring_system_character_t) '\\' ) )
			{
				path_type                  = LIBSYSTEM_PATH_TYPE_ABSOLUTE;
				path_directory_name_index += 1;
			}
		}
		/* Check for special paths
		 * paths with prefix: \\
		 */
		else if( ( path[ 0 ] == (libcstring_system_character_t) '\\' )
		      && ( path[ 1 ] == (libcstring_system_character_t) '\\' ) )
		{
			/* Ignore the following special paths
			 * device path prefix:          \\.\
			 * extended-length path prefix: \\?\
			 */
			if( ( path_length >= 4 )
			 && ( ( path[ 2 ] == (libcstring_system_character_t) '.' )
			   || ( path[ 2 ] == (libcstring_system_character_t) '?' ) )
			 && ( path[ 3 ] == (libcstring_system_character_t) '\\' ) )
			{
				return( 0 );
			}
			else
			{
				/* Determine the volume in an UNC path
				 * \\server\share
				 */
				for( share_name_index = 2;
				     share_name_index <= path_length;
				     share_name_index++ )
				{
					if( path[ share_name_index ] == (libcstring_system_character_t) '\\' )
					{
						break;
					}
				}
				if( share_name_index > path_length )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: invalid path - missing share name.",
					 function );

					return( -1 );
				}
				for( path_directory_name_index = share_name_index + 1;
				     path_directory_name_index <= path_length;
				     path_directory_name_index++ )
				{
					if( path[ path_directory_name_index ] == (libcstring_system_character_t) '\\' )
					{
						break;
					}
				}
				path_type          = LIBSYSTEM_PATH_TYPE_UNC;
				volume_name        = (libcstring_system_character_t *) &( path[ 2 ] );
				volume_name_length = path_directory_name_index - 2;
			}
		}
	}
	/* If the path is an UNC do not bother to lookup the current directory
	 */
	if( path_type != LIBSYSTEM_PATH_TYPE_UNC )
	{
		/* If the path contains a volume name switch to that
		 * volume to determine the current directory
		 */
		if( volume_name != NULL )
		{
#if !defined( USE_CRT_FUNCTIONS )
			current_working_directory_size = GetCurrentDirectory(
							  0,
							  NULL );

			if( current_working_directory_size == 0 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve current working directory size.",
				 function );

				return( -1 );
			}
#else
			current_working_directory_size = (DWORD) _MAX_PATH;
#endif /* !defined( USE_CRT_FUNCTIONS ) */

			current_working_directory = libcstring_system_string_allocate(
			                             (size_t) current_working_directory_size );

			if( current_working_directory == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create current working directory.",
				 function );

				return( -1 );
			}
#if !defined( USE_CRT_FUNCTIONS )
			if( GetCurrentDirectory(
			     current_working_directory_size,
			     current_working_directory ) != ( current_working_directory_size - 1 ) )
#else
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			if( _wgetcwd(
			     current_working_directory,
			     current_working_directory_size ) == NULL )
#else
			if( _getcwd(
			     current_working_directory,
			     current_working_directory_size ) == NULL )
#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */
#endif /* !defined( USE_CRT_FUNCTIONS ) */
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve current working directory.",
				 function );

				goto on_error;
			}
			change_volume_name = libcstring_system_string_allocate(
			                      volume_name_length + 1 );

			if( change_volume_name == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create change volume name.",
				 function );

				goto on_error;
			}
			if( libcstring_system_string_copy(
			     change_volume_name,
			     volume_name,
			     volume_name_length ) == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to set change volume name.",
				 function );

				goto on_error;
			}
			change_volume_name[ volume_name_length ] = 0;

#if !defined( USE_CRT_FUNCTIONS )
			if( SetCurrentDirectory(
			     change_volume_name ) == 0 )
#else
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			if( _wchdir(
			     change_volume_name ) != 0 )
#else
			if( _chdir(
			     change_volume_name ) != 0 )
#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */
#endif /* !defined( USE_CRT_FUNCTIONS ) */
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set current working directory.",
				 function );

				goto on_error;
			}
			memory_free(
			 change_volume_name );

			change_volume_name = NULL;
		}
#if !defined( USE_CRT_FUNCTIONS )
		current_directory_size = GetCurrentDirectory(
					  0,
					  NULL );

		if( current_directory_size == 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve current directory size.",
			 function );

			error_abort = 1;
		}
#else
		current_directory_size = (DWORD) _MAX_PATH;
#endif /* !defined( USE_CRT_FUNCTIONS ) */

		if( error_abort == 0 )
		{
			current_directory = libcstring_system_string_allocate(
			                     (size_t) current_directory_size );

			if( current_directory == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create current directory.",
				 function );

				error_abort = 1;
			}
		}
		if( error_abort == 0 )
		{
#if !defined( USE_CRT_FUNCTIONS )
			if( GetCurrentDirectory(
			     current_directory_size,
			     current_directory ) != ( current_directory_size - 1 ) )
#else
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			if( _wgetcwd(
			     current_directory,
			     current_directory_size ) == NULL )
#else
			if( _getcwd(
			     current_directory,
			     current_directory_size ) == NULL )
#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */
#endif /* !defined( USE_CRT_FUNCTIONS ) */
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve current directory.",
				 function );

				error_abort = 1;
			}
		}
		if( current_working_directory != NULL )
		{
#if !defined( USE_CRT_FUNCTIONS )
			if( SetCurrentDirectory(
			     current_working_directory ) == 0 )
#else
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			if( _wchdir(
			     current_working_directory ) != 0 )
#else
			if( _chdir(
			     current_working_directory ) != 0 )
#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */
#endif /* !defined( USE_CRT_FUNCTIONS ) */
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set current working directory.",
				 function );

				goto on_error;
			}
			memory_free(
			 current_working_directory );

			current_working_directory = NULL;
		}
		/* Make sure the current working directory has been changed
		 * back to its original value
		 */
		if( error_abort != 0 )
		{
			goto on_error;
		}
		/* Determine the volume name using the current directory if necessary
		 */
		if( current_directory_size >= 3 )
		{
			/* Check if the path starts with a volume letter
			 */
			if( ( current_directory[ 1 ] == (libcstring_system_character_t) ':' )
			 && ( ( ( current_directory[ 0 ] >= (libcstring_system_character_t) 'A' )
			   && ( current_directory[ 0 ] <= (libcstring_system_character_t) 'Z' ) )
			  || ( ( current_directory[ 0 ] >= (libcstring_system_character_t) 'a' )
			   && ( current_directory[ 0 ] <= (libcstring_system_character_t) 'z' ) ) ) )
			{
				if( volume_name == NULL )
				{
					volume_name        = &( current_directory[ 0 ] );
					volume_name_length = 2;
				}
				current_directory_name_index = 2;

				if( current_directory[ 2 ] == (libcstring_system_character_t) '\\' )
				{
					current_directory_name_index += 1;
				}
			}
			/* Check for special paths
			 * paths with prefix: \\
			 */
			else if( ( current_directory[ 0 ] == (libcstring_system_character_t) '\\' )
			      && ( current_directory[ 1 ] == (libcstring_system_character_t) '\\' ) )
			{
				/* Ignore the following special paths
				 * device path prefix:          \\.\
				 */
				if( ( current_directory_size >= 4 )
				 && ( current_directory[ 2 ] == (libcstring_system_character_t) '.' )
				 && ( current_directory[ 3 ] == (libcstring_system_character_t) '\\' ) )
				{
					return( 0 );
				}
				else
				{
					/* Determine the volume in an UNC path
					 * \\server\share
					 */
					for( share_name_index = 2;
					     share_name_index < current_directory_size;
					     share_name_index++ )
					{
						if( current_directory[ share_name_index ] == (libcstring_system_character_t) '\\' )
						{
							break;
						}
					}
					if( share_name_index >= current_directory_size )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: invalid path - missing share name.",
						 function );

						goto on_error;
					}
					for( current_directory_name_index = share_name_index + 1;
					     current_directory_name_index < current_directory_size;
					     current_directory_name_index++ )
					{
						if( current_directory[ current_directory_name_index ] == (libcstring_system_character_t) '\\' )
						{
							break;
						}
					}
					if( volume_name == NULL )
					{
						volume_name        = &( current_directory[ 2 ] );
						volume_name_length = current_directory_name_index - 2;
					}
				}
			}
		}
	}
	if( volume_name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume name value missing.",
		 function );

		goto on_error;
	}
	if( current_directory != NULL )
	{
		if( libsystem_split_values_parse_string(
		     &current_directory_split_values,
		     &( current_directory[ current_directory_name_index ] ),
		     current_directory_size - ( current_directory_name_index + 1 ),
		     (libcstring_system_character_t) '\\',
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to split current directory.",
			 function );

			goto on_error;
		}
	}
	if( libsystem_split_values_parse_string(
	     &path_split_values,
	     &( path[ path_directory_name_index ] ),
	     path_length - path_directory_name_index,
	     (libcstring_system_character_t) '\\',
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to split path.",
		 function );

		goto on_error;
	}
	/* The size of the extended path consists of:
	 * the size of the \\?\ prefix
	 * the length of the volume name
	 * a directory separator
	 */
	*extended_path_size = 5 + volume_name_length;

	/* And if the path contains an UNC path
	 * add the size of the UNC\ prefix
	 */
	if( share_name_index > 0 )
	{
		*extended_path_size += 4;
	}
	/* And if the path is relative
	 * add the size of the current directory
	 * a directory separator, if necessary
	 */
	if( path_type == LIBSYSTEM_PATH_TYPE_RELATIVE )
	{
		*extended_path_size += ( current_directory_size - ( current_directory_name_index + 1 ) );

		if( ( current_directory_size >= 2 )
		 && ( current_directory[ current_directory_size - 2 ] != (libcstring_system_character_t) '\\' ) )
		{
			*extended_path_size += 1;
		}
	}
	if( current_directory_split_values != NULL )
	{
		current_directory_split_value_iterator = current_directory_split_values->number_of_values - 1;
	}
	for( path_split_value_iterator = 0;
	     path_split_value_iterator < path_split_values->number_of_values;
	     path_split_value_iterator++ )
	{
		/* If the path is .. reverse the current path by one directory
		 */
		if( ( path_split_values->sizes[ path_split_value_iterator ] == 3 )
		 && ( ( path_split_values->values[ path_split_value_iterator ] )[ 0 ] == (libcstring_system_character_t) '.' )
		 && ( ( path_split_values->values[ path_split_value_iterator ] )[ 1 ] == (libcstring_system_character_t) '.' ) )
		{
			if( last_used_path_split_value_iterator == 0 )
			{
				if( current_directory_split_value_iterator <= 0 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid current directory split value iterator value out of bounds.",
					 function );

					goto on_error;
				}
				/* Remove the size of the parent directory name and a directory separator
				 * Note that the size includes the end of string character
				 */
				*extended_path_size -= current_directory_split_values->sizes[ current_directory_split_value_iterator ];

				current_directory_split_values->sizes[ current_directory_split_value_iterator ] = 0;

				current_directory_split_value_iterator--;
			}
			else
			{
				/* Remove the size of the parent directory name and a directory separator
				 * Note that the size includes the end of string character
				 */
				*extended_path_size -= path_split_values->sizes[ last_used_path_split_value_iterator ];

				path_split_values->sizes[ path_split_value_iterator ] = 0;

				/* Find the previous path split value that contains a name
				 */
				while( last_used_path_split_value_iterator > 0 )
				{
					last_used_path_split_value_iterator--;

					if( path_split_values->sizes[ last_used_path_split_value_iterator ] != 0 )
					{
						break;
					}
				}
			}
			path_split_values->sizes[ path_split_value_iterator ] = 0;
		}
		/* If the path is . ignore the entry
		 */
		else if( ( path_split_values->sizes[ path_split_value_iterator ] == 2 )
		      && ( ( path_split_values->values[ path_split_value_iterator ] )[ 0 ] == (libcstring_system_character_t) '.' ) )
		{
			path_split_values->sizes[ path_split_value_iterator ] = 0;
		}
		else
		{
			/* Add the size of the directory or file name and a directory separator
			 * Note that the size includes the end of string character
			 */
			*extended_path_size += path_split_values->sizes[ path_split_value_iterator ];

			last_used_path_split_value_iterator = path_split_value_iterator;
		}
	}
	/* Note that the last path separator serves as the end of string
	 */
	extended_path_index = 0;

	*extended_path = libcstring_system_string_allocate(
	                  *extended_path_size );

	if( *extended_path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create extended path.",
		 function );

		goto on_error;
	}
	if( libcstring_system_string_copy(
	     &( ( *extended_path )[ extended_path_index ] ),
	     _LIBCSTRING_SYSTEM_STRING( "\\\\?\\" ),
	     4 ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set \\\\?\\ prefix in extended path.",
		 function );

		goto on_error;
	}
	extended_path_index += 4;

	/* If there is a share name the path is an UNC path
	 */
	if( share_name_index > 0 )
	{
		if( libcstring_system_string_copy(
		     &( ( *extended_path )[ extended_path_index ] ),
		     _LIBCSTRING_SYSTEM_STRING( "UNC\\" ),
		     4 ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set UNC\\ prefix in extended path.",
			 function );

			goto on_error;
		}
		extended_path_index += 4;
	}
	if( libcstring_system_string_copy(
	     &( ( *extended_path )[ extended_path_index ] ),
	     volume_name,
	     volume_name_length ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set volume name in extended path.",
		 function );

		goto on_error;
	}
	extended_path_index += volume_name_length;

	( *extended_path )[ extended_path_index ] = (libcstring_system_character_t) '\\';

	extended_path_index += 1;

	/* If the path is relative
	 * add the current directory elements
	 */
	if( ( path_type == LIBSYSTEM_PATH_TYPE_RELATIVE )
	 && ( current_directory_split_values != NULL ) )
	{
		for( current_directory_split_value_iterator = 0;
		     current_directory_split_value_iterator < current_directory_split_values->number_of_values;
		     current_directory_split_value_iterator++ )
		{
			if( current_directory_split_values->sizes[ current_directory_split_value_iterator ] != 0 )
			{
				if( libcstring_system_string_copy(
				     &( ( *extended_path )[ extended_path_index ] ),
				     current_directory_split_values->values[ current_directory_split_value_iterator ],
				     current_directory_split_values->sizes[ current_directory_split_value_iterator ] - 1 ) == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set current directory split value: %d in extended path.",
					 function,
					 current_directory_split_value_iterator );

					goto on_error;
				}
				extended_path_index += current_directory_split_values->sizes[ current_directory_split_value_iterator ] - 1;

				( *extended_path )[ extended_path_index ] = (libcstring_system_character_t) '\\';

				extended_path_index += 1;
			}
		}
	}
	for( path_split_value_iterator = 0;
	     path_split_value_iterator < path_split_values->number_of_values;
	     path_split_value_iterator++ )
	{
		if( path_split_values->sizes[ path_split_value_iterator ] != 0 )
		{
			if( libcstring_system_string_copy(
			     &( ( *extended_path )[ extended_path_index ] ),
			     path_split_values->values[ path_split_value_iterator ],
			     path_split_values->sizes[ path_split_value_iterator ] - 1 ) == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set path split value: %d in extended path.",
				 function,
				 path_split_value_iterator );

				goto on_error;
			}
			extended_path_index += path_split_values->sizes[ path_split_value_iterator ] - 1;

			( *extended_path )[ extended_path_index ] = (libcstring_system_character_t) '\\';

			extended_path_index += 1;
		}
	}
	( *extended_path )[ extended_path_index - 1 ] = 0;

	if( libsystem_split_values_free(
	     &path_split_values,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free path split values.",
		 function );

		goto on_error;
	}
	if( current_directory_split_values != NULL )
	{
		if( libsystem_split_values_free(
		     &current_directory_split_values,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free current directory split values.",
			 function );

			goto on_error;
		}
	}
	if( current_directory != NULL )
	{
		memory_free(
		 current_directory );
	}
	return( 1 );

on_error:
	if( *extended_path != NULL )
	{
		memory_free(
		 *extended_path );

		*extended_path      = NULL;
		*extended_path_size = 0;
	}
	if( path_split_values != NULL )
	{
		libsystem_split_values_free(
		 &path_split_values,
		 NULL );
	}
	if( current_directory_split_values != NULL )
	{
		libsystem_split_values_free(
		 &current_directory_split_values,
		 NULL );
	}
	if( current_directory != NULL )
	{
		memory_free(
		 current_directory );
	}
	if( change_volume_name != NULL )
	{
		memory_free(
		 change_volume_name );
	}
	if( current_working_directory != NULL )
	{
		memory_free(
		 current_working_directory );
	}
	return( -1 );
}

#endif

/* Sanitizes the path
 * Returns 1 if successful or -1 on error
 */
int libsystem_path_sanitize(
     libcstring_system_character_t *path,
     size_t *path_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_path_sanitize";
	size_t path_index     = 0;

	if( path == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path size.",
		 function );

		return( -1 );
	}
	if( *path_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) || defined( __CYGWIN__ )
	if( *path_size > 32767 )
	{
		path[ 32766 ] = 0;

		*path_size = 32767;
	}
#endif
	for( path_index = 0;
	     path_index < *path_size;
	     path_index++ )
	{
		if( path[ path_index ] == 0x00 )
		{
			break;
		}
		else if( ( path[ path_index ] >= 0x01 )
		      && ( path[ path_index ] <= 0x1f ) )
		{
			path[ path_index ] = (libcstring_system_character_t) '_';
		}
#if defined( WINAPI )
		else if( path[ path_index ] == (libcstring_system_character_t) '/' )
#else
		else if( path[ path_index ] == (libcstring_system_character_t) '\\' )
#endif
		{
			path[ path_index ] = (libcstring_system_character_t) '_';
		}
		else if( ( path[ path_index ] == (libcstring_system_character_t) '!' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '$' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '%' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '&' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '*' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '+' )
		      || ( path[ path_index ] == (libcstring_system_character_t) ':' )
		      || ( path[ path_index ] == (libcstring_system_character_t) ';' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '<' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '>' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '?' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '@' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '|' )
		      || ( path[ path_index ] == (libcstring_system_character_t) '~' )
		      || ( path[ path_index ] == 0x7e ) )
		{
			path[ path_index ] = (libcstring_system_character_t) '_';
		}
	}
	return( 1 );
}

/* Sanitizes the filename
 * Returns 1 if successful or -1 on error
 */
int libsystem_path_sanitize_filename(
     libcstring_system_character_t *filename,
     size_t *filename_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_path_sanitize_filename";
	size_t filename_index = 0;

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
	if( filename_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename size.",
		 function );

		return( -1 );
	}
	if( *filename_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid filename size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) || defined( __CYGWIN__ )
	if( *filename_size > 256 )
	{
		filename[ 255 ] = 0;

		*filename_size = 256;
	}
#endif
	for( filename_index = 0;
	     filename_index < *filename_size;
	     filename_index++ )
	{
		if( filename[ filename_index ] == 0x00 )
		{
			break;
		}
		else if( ( filename[ filename_index ] >= 0x01 )
		      && ( filename[ filename_index ] <= 0x1f ) )
		{
			filename[ filename_index ] = (libcstring_system_character_t) '_';
		}
		else if( ( filename[ filename_index ] == (libcstring_system_character_t) '/' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '\\' ) )
		{
			filename[ filename_index ] = (libcstring_system_character_t) '_';
		}
		else if( ( filename[ filename_index ] == (libcstring_system_character_t) '!' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '$' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '%' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '&' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '*' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '+' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) ':' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) ';' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '<' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '>' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '?' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '@' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '~' )
		      || ( filename[ filename_index ] == (libcstring_system_character_t) '|' )
		      || ( filename[ filename_index ] == 0x7e ) )
		{
			filename[ filename_index ] = (libcstring_system_character_t) '_';
		}
	}
	return( 1 );
}

