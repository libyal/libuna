/*
 * String functions
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

#include "libcpath_libcerror.h"
#include "libcpath_libcstring.h"
#include "libcpath_split_string.h"
#include "libcpath_string.h"

/* Splits a string
 * Returns 1 if successful or -1 on error
 */
int libcpath_string_split(
     const libcstring_system_character_t *string,
     size_t string_size,
     libcstring_system_character_t delimiter,
     libcpath_split_string_t **split_string,
     libcerror_error_t **error )
{
	libcstring_system_character_t *segment_start = NULL;
	libcstring_system_character_t *segment_end   = NULL;
	libcstring_system_character_t *string_end    = NULL;
	static char *function                        = "libcpath_string_split";
	ssize_t segment_length                       = 0;
	int number_of_segments                       = 0;
	int segment_index                            = 0;

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid split string.",
		 function );

		return( -1 );
	}
	if( *split_string != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid split string already set.",
		 function );

		return( -1 );
	}
	/* An empty string has no segments
	 */
	if( ( string_size == 0 )
	 || ( string[ 0 ] == 0 ) )
	{
		return( 1 );
	}
	/* Determine the number of segments
	 */
	segment_start = (libcstring_system_character_t *) string;
	string_end    = (libcstring_system_character_t *) &( string[ string_size - 1 ] );

	do
	{
		segment_end = segment_start;

		while( segment_end <= string_end )
		{
			if( ( segment_end == string_end )
			 || ( *segment_end == 0 ) )
			{
				segment_end = NULL;

				break;
			}
			else if( *segment_end == delimiter )
			{
				break;
			}
			segment_end++;
		}
		if( segment_end > string_end )
		{
			break;
		}
		segment_index++;

		if( segment_end == NULL )
		{
			break;
		}
		if( segment_end == segment_start )
		{
			segment_start++;
		}
		else if( segment_end != string )
		{
			segment_start = segment_end + 1;
		}
	}
	while( segment_end != NULL );

	number_of_segments = segment_index;

	if( libcpath_split_string_initialize(
	     split_string,
	     string,
	     string_size,
	     number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to intialize split string.",
		 function );

		goto on_error;
	}
	if( *split_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing split string.",
		 function );

		goto on_error;
	}
	/* Do not bother splitting empty strings
	 */
	if( number_of_segments == 0 )
	{
		return( 1 );
	}
	/* Determine the segments
	 * empty segments are stored as strings only containing the end of character
	 */
	if( libcpath_split_string_get_string(
	     *split_string,
	     &segment_start,
	     &string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve split string.",
		 function );

		goto on_error;
	}
	if( segment_start == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing segment start.",
		 function );

		goto on_error;
	}
	if( string_size < 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid string size value out of bounds.",
		 function );

		goto on_error;
	}
	segment_end = segment_start;
	string_end  = &( segment_start[ string_size - 1 ] );

	for( segment_index = 0;
	     segment_index < number_of_segments;
	     segment_index++ )
	{
		segment_end = segment_start;

		while( segment_end <= string_end )
		{
			if( ( segment_end == string_end )
			 || ( *segment_end == 0 ) )
			{
				segment_end = NULL;

				break;
			}
			else if( *segment_end == delimiter )
			{
				break;
			}
			segment_end++;
		}
		if( segment_end == NULL )
		{
			segment_length = (ssize_t) ( string_end - segment_start );
		}
		else
		{
			segment_length = (ssize_t) ( segment_end - segment_start );
		}
		if( segment_length >= 0 )
		{
			segment_start[ segment_length ] = 0;

			if( libcpath_split_string_set_segment_by_index(
			     *split_string,
			     segment_index,
			     segment_start,
			     segment_length + 1,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set split string segment: %d.",
				 function,
				 segment_index );

				goto on_error;
			}
		}
		if( segment_end == NULL )
		{
			break;
		}
		if( segment_end == ( *split_string )->string )
		{
			segment_start++;
		}
		if( segment_end != ( *split_string )->string )
		{
			segment_start = segment_end + 1;
		}
	}
	return( 1 );

on_error:
	if( *split_string != NULL )
	{
		libcpath_split_string_free(
		 split_string,
		 NULL );
	}
	return( -1 );
}

