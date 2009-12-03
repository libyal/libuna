/*
 * Base16 stream functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libuna_base16_stream.h"
#include "libuna_definitions.h"
#include "libuna_types.h"

/* Determines the size of a base16 stream from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base16_stream_size_from_byte_stream(
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *base16_stream_size,
     liberror_error_t **error )
{
	static char *function = "libuna_base16_stream_size_from_byte_stream";

	if( byte_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( base16_stream_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base16 stream size.",
		 function );

		return( -1 );
	}
	/* The base16 stream contains 2 characters for every byte
	 */
	*base16_stream_size = byte_stream_size * 2;

	return( 1 );
}

/* Copies a base16 stream from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base16_stream_copy_from_byte_stream(
     uint8_t *base16_stream,
     size_t base16_stream_size,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     liberror_error_t **error )
{
	static char *function      = "libuna_base16_stream_copy_from_byte_stream";
	size_t base16_stream_index = 0;
	size_t byte_stream_index   = 0;
	uint8_t byte_value         = 0;

	if( base16_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base16 stream.",
		 function );

		return( -1 );
	}
	if( base16_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( base16_stream_size < ( byte_stream_size * 2 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base16 stream is too small.",
		 function );

		return( -1 );
	}
	while( byte_stream_index < byte_stream_size )
	{
		byte_value = byte_stream[ byte_stream_index ] >> 4;

		if( byte_value <= 9 )
		{
			base16_stream[ base16_stream_index++ ] = (uint8_t) '0' + byte_value;
		}
		else
		{
			base16_stream[ base16_stream_index++ ] = (uint8_t) 'A' + byte_value;
		}
		byte_value = byte_stream[ byte_stream_index ] & 0x0f;

		if( byte_value < 9 )
		{
			base16_stream[ base16_stream_index++ ] = (uint8_t) '0' + byte_value;
		}
		else
		{
			base16_stream[ base16_stream_index++ ] = (uint8_t) 'A' + byte_value;
		}
		byte_stream_index++;
	}
	return( 1 );
}

/* Determines the size of a byte stream from a base16 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base16_stream_size_to_byte_stream(
     uint8_t *base16_stream,
     size_t base16_stream_size,
     size_t *byte_stream_size,
     liberror_error_t **error )
{
	static char *function = "libuna_base16_stream_size_to_byte_stream";

	if( base16_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base16 stream.",
		 function );

		return( -1 );
	}
	if( base16_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( base16_stream_size % 2 ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base16 stream size value not a multitude of 2.",
		 function );

		return( -1 );
	}
	if( byte_stream_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream size.",
		 function );

		return( -1 );
	}
	/* The base16 stream contains 2 characters for every byte
	 */
	*byte_stream_size = base16_stream_size / 2;

	return( 1 );
}

/* Copies a byte stream from a base16 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base16_stream_copy_to_byte_stream(
     uint8_t *base16_stream,
     size_t base16_stream_size,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     liberror_error_t **error )
{
	static char *function      = "libuna_base16_stream_copy_to_byte_stream";
	size_t base16_stream_index = 0;
	size_t byte_stream_index   = 0;
	uint8_t byte_value         = 0;

	if( base16_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base16 stream.",
		 function );

		return( -1 );
	}
	if( base16_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( base16_stream_size % 2 ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base16 stream size value not a multitude of 2.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( byte_stream_size < ( base16_stream_size / 2 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream is too small.",
		 function );

		return( -1 );
	}
	while( base16_stream_index < base16_stream_size )
	{
		byte_value = 0;

		if( ( base16_stream[ base16_stream_index ] >= (uint8_t) '0' )
		 && ( base16_stream[ base16_stream_index ] <= (uint8_t) '9' ) )
		{
			byte_value = base16_stream[ base16_stream_index ] - (uint8_t) '0';
		}
		else if( ( base16_stream[ base16_stream_index ] >= (uint8_t) 'A' )
		      && ( base16_stream[ base16_stream_index ] <= (uint8_t) 'F' ) )
		{
			byte_value = base16_stream[ base16_stream_index ] - (uint8_t) 'A';
		}
		else
		{
			/* TODO print error */
		}
		byte_value <<= 4;

		base16_stream_index++;

		if( ( base16_stream[ base16_stream_index ] >= (uint8_t) '0' )
		 && ( base16_stream[ base16_stream_index ] <= (uint8_t) '9' ) )
		{
			byte_value += base16_stream[ base16_stream_index ] - (uint8_t) '0';
		}
		else if( ( base16_stream[ base16_stream_index ] >= (uint8_t) 'A' )
		      && ( base16_stream[ base16_stream_index ] <= (uint8_t) 'F' ) )
		{
			byte_value += base16_stream[ base16_stream_index ] - (uint8_t) 'A';
		}
		else
		{
			/* TODO print error */
		}
		base16_stream_index++;

		byte_stream[ byte_stream_index++ ] = byte_value;
	}
	return( 1 );
}

