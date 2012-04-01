/*
 * Split string functions
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
#include <memory.h>
#include <types.h>

#include "libcpath_libcerror.h"
#include "libcpath_libcstring.h"
#include "libcpath_split_string.h"

/* Initializes the split string
 * Returns 1 if successful or -1 on error
 */
int libcpath_split_string_initialize(
     libcpath_split_string_t **split_string,
     const libcstring_system_character_t *string,
     size_t string_size,
     int number_of_segments,
     libcerror_error_t **error )
{
	static char *function = "libcpath_split_string_initialize";

	if( split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split string.",
		 function );

		return( 1 );
	}
	if( number_of_segments < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid number of segments less than zero.",
		 function );

		return( -1 );
	}
	if( *split_string != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid split string value already set.",
		 function );

		return( -1 );
	}
	*split_string = memory_allocate_structure(
			 libcpath_split_string_t );

	if( *split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create split string.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *split_string,
	     0,
	     sizeof( libcpath_split_string_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear split string.",
		 function );

		memory_free(
		 *split_string );

		*split_string = NULL;

		return( -1 );
	}
	if( ( string != NULL )
	 && ( string_size > 0 ) )
	{
		( *split_string )->string = libcstring_system_string_allocate(
		                             string_size );

		if( ( *split_string )->string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create string.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     ( *split_string )->string,
		     string,
		     sizeof( libcstring_system_character_t ) * ( string_size - 1 ) ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to copy string.",
			 function );

			goto on_error;
		}
		( *split_string )->string[ string_size - 1 ] = 0;
		( *split_string )->string_size               = string_size;
	}
	if( number_of_segments > 0 )
	{
		( *split_string )->segments = (libcstring_system_character_t **) memory_allocate(
		                                                                  sizeof( libcstring_system_character_t * ) * number_of_segments );

		if( ( *split_string )->segments == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create segments.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     ( *split_string )->segments,
		     0,
		     sizeof( libcstring_system_character_t * ) * number_of_segments ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear segments.",
			 function );

			goto on_error;
		}
		( *split_string )->segment_sizes = (size_t *) memory_allocate(
							       sizeof( size_t ) * number_of_segments );

		if( ( *split_string )->segment_sizes == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create segment sizes.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     ( *split_string )->segment_sizes,
		     0,
		     sizeof( size_t ) * number_of_segments ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear segment sizes.",
			 function );

			goto on_error;
		}
	}
	( *split_string )->number_of_segments = number_of_segments;

	return( 1 );

on_error:
	if( *split_string != NULL )
	{
		if( ( *split_string )->segment_sizes != NULL )
		{
			memory_free(
			 ( *split_string )->segment_sizes );
		}
		if( ( *split_string )->segments != NULL )
		{
			memory_free(
			 ( *split_string )->segments );
		}
		if( ( *split_string )->string != NULL )
		{
			memory_free(
			 ( *split_string )->string );
		}
		memory_free(
		 *split_string );

		*split_string = NULL;
	}
	return( -1 );
}

/* Frees the split string including elements
 * Returns 1 if successful or -1 on error
 */
int libcpath_split_string_free(
     libcpath_split_string_t **split_string,
     libcerror_error_t **error )
{
	static char *function = "libcpath_split_string_free";

	if( split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split string.",
		 function );

		return( 1 );
	}
	if( *split_string != NULL )
	{
		if( ( *split_string )->string != NULL )
		{
			memory_free(
			 ( *split_string )->string );
		}
		if( ( *split_string )->segments != NULL )
		{
			memory_free(
			 ( *split_string )->segments );
		}
		if( ( *split_string )->segment_sizes != NULL )
		{
			memory_free(
			 ( *split_string )->segment_sizes );
		}
		memory_free(
		 *split_string );

		*split_string = NULL;
	}
	return( 1 );
}

/* Retrieves the string
 * Returns 1 if successful or -1 on error
 */
int libcpath_split_string_get_string(
     libcpath_split_string_t *split_string,
     libcstring_system_character_t **string,
     size_t *string_size,
     libcerror_error_t **error )
{
	static char *function = "libcpath_split_string_get_string";

	if( split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split string.",
		 function );

		return( 1 );
	}
	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( 1 );
	}
	if( string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string size.",
		 function );

		return( 1 );
	}
	*string      = split_string->string;
	*string_size = split_string->string_size;

	return( 1 );
}

/* Retrieves the number of segments
 * Returns 1 if successful or -1 on error
 */
int libcpath_split_string_get_number_of_segments(
     libcpath_split_string_t *split_string,
     int *number_of_segments,
     libcerror_error_t **error )
{
	static char *function = "libcpath_split_string_get_number_of_segments";

	if( split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split string.",
		 function );

		return( 1 );
	}
	if( number_of_segments == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of segments.",
		 function );

		return( 1 );
	}
	*number_of_segments = split_string->number_of_segments;

	return( 1 );
}

/* Retrieves a specific segment
 * Returns 1 if successful or -1 on error
 */
int libcpath_split_string_get_segment_by_index(
     libcpath_split_string_t *split_string,
     int segment_index,
     libcstring_system_character_t **string_segment,
     size_t *string_segment_size,
     libcerror_error_t **error )
{
	static char *function = "libcpath_split_string_get_segment_by_index";

	if( split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split string.",
		 function );

		return( 1 );
	}
	if( ( segment_index < 0 )
	 || ( segment_index >= split_string->number_of_segments ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment index value out of bounds.",
		 function );

		return( -1 );
	}
	if( string_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string segment.",
		 function );

		return( 1 );
	}
	if( string_segment_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string segment size.",
		 function );

		return( 1 );
	}
	*string_segment      = split_string->segments[ segment_index ];
	*string_segment_size = split_string->segment_sizes[ segment_index ];

	return( 1 );
}

/* Sets a specific segment
 * Returns 1 if successful or -1 on error
 */
int libcpath_split_string_set_segment_by_index(
     libcpath_split_string_t *split_string,
     int segment_index,
     libcstring_system_character_t *string_segment,
     size_t string_segment_size,
     libcerror_error_t **error )
{
	static char *function        = "libcpath_split_string_set_segment_by_index";
	size_t string_segment_offset = 0;

	if( split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split string.",
		 function );

		return( 1 );
	}
	if( ( segment_index < 0 )
	 || ( segment_index >= split_string->number_of_segments ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment index value out of bounds.",
		 function );

		return( -1 );
	}
	if( string_segment_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string segment size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( string_segment == NULL )
	{
		if( string_segment_size != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid string segment size value out of bounds.",
			 function );

			return( -1 );
		}
	}
	else
	{
		if( string_segment < split_string->string )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid string segment value out of bounds.",
			 function );

			return( -1 );
		}
		string_segment_offset = (size_t) ( string_segment - split_string->string );

		if( string_segment_offset > split_string->string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid string segment value out of bounds.",
			 function );

			return( -1 );
		}
		string_segment_offset += string_segment_size;

		if( string_segment_offset > split_string->string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid string segment value out of bounds.",
			 function );

			return( -1 );
		}
	}
	split_string->segments[ segment_index ]      = string_segment;
	split_string->segment_sizes[ segment_index ] = string_segment_size;

	return( 1 );
}

