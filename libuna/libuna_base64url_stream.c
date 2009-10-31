/*
 * Base64 URL stream functions
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

#include "libuna_base64url_stream.h"
#include "libuna_definitions.h"
#include "libuna_inline.h"
#include "libuna_types.h"

#ifdef TODO

static uint8_t libuna_base64url_sixtet_to_character_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

#define libuna_base64url_character_from_sixtet( sixtet ) \
	libuna_base64url_sixtet_to_character_table[ sixtet ]

/* Copies a base64 character to a base64 sixtet
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_base64url_character_copy_to_sixtet(
                   uint8_t base64url_character,
                   uint8_t *base64url_sixtet,
                   liberror_error_t **error )
{
	static char *function = "libuna_base64url_character_copy_to_sixtet";

	if( base64url_sixtet == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 sixtet.",
		 function );

		return( -1 );
	}
	/* A-Z is not a continous range on a EBCDIC based system
	 * it consists of the ranges: A-I, J-R, S-Z
	 */
	if( ( base64url_character >= (uint8_t) 'A' )
	 && ( base64url_character <= (uint8_t) 'I' ) )
	{
		*base64url_sixtet = base64url_character - (uint8_t) 'A';
	}
	else if( ( base64url_character >= (uint8_t) 'J' )
	      && ( base64url_character <= (uint8_t) 'R' ) )
	{
		*base64url_sixtet = base64url_character - (uint8_t) 'J' + 9;
	}
	else if( ( base64url_character >= (uint8_t) 'S' )
	      && ( base64url_character <= (uint8_t) 'Z' ) )
	{
		*base64url_sixtet = base64url_character - (uint8_t) 'S' + 18;
	}
	/* a-z is not a continous range on a EBCDIC based system
	 * it consists of the ranges: a-i, j-r, s-z
	 */
	else if( ( base64url_character >= (uint8_t) 'a' )
	      && ( base64url_character <= (uint8_t) 'i' ) )
	{
		*base64url_sixtet = base64url_character - (uint8_t) 'a' + 26;
	}
	else if( ( base64url_character >= (uint8_t) 'j' )
	      && ( base64url_character <= (uint8_t) 'r' ) )
	{
		*base64url_sixtet = base64url_character - (uint8_t) 'j' + 32;
	}
	else if( ( base64url_character >= (uint8_t) 's' )
	      && ( base64url_character <= (uint8_t) 'z' ) )
	{
		*base64url_sixtet = base64url_character - (uint8_t) 's' + 44;
	}
	else if( ( base64url_character >= (uint8_t) '0' )
	      && ( base64url_character <= (uint8_t) '9' ) )
	{
		*base64url_sixtet = base64url_character - (uint8_t) '0' + 52;
	}
	else if( base64url_character == (uint8_t) '-' )
	{
		*base64url_sixtet = 62;
	}
	else if( base64url_character == (uint8_t) '_' )
	{
		*base64url_sixtet = 63;
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid base64 character.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies a base64 triplet from a base64 URL stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_base64url_triplet_copy_from_base64url_stream(
                   uint32_t *base64url_triplet,
                   const uint8_t *base64url_stream,
                   size_t base64url_stream_size,
                   size_t *base64url_stream_index,
                   liberror_error_t **error )
{
	static char *function = "libuna_base64url_triplet_copy_from_base64url_stream";
	uint8_t sixtet1       = 0;
	uint8_t sixtet2       = 0;
	uint8_t sixtet3       = 0;
	uint8_t sixtet4       = 0;

	if( base64url_triplet == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 triplet.",
		 function );

		return( -1 );
	}
	if( base64url_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 URL stream.",
		 function );

		return( -1 );
	}
	if( base64url_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base64 URL stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( base64url_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 URL stream index.",
		 function );

		return( -1 );
	}
	if( *base64url_stream_index >= base64url_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 URL stream string too small.",
		 function );

		return( -1 );
	}
	if( libuna_base64url_character_copy_to_sixtet(
	     base64url_stream[ *base64url_stream_index ],
	     &sixtet1,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
		 "%s: unable to copy base64 character to 1st sixtet.",
		 function );

		return( -1 );
	}
	if( ( *base64url_stream_index + 1 ) < base64url_stream_size )
	{
		if( libuna_base64url_character_copy_to_sixtet(
		     base64url_stream[ *base64url_stream_index + 1 ],
		     &sixtet2,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy base64 character to 2nd sixtet.",
			 function );

			return( -1 );
		}
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing 2nd base64 character.",
		 function );

		return( -1 );
	}
	if( ( *base64url_stream_index + 2 ) < base64url_stream_size )
	{
		if( libuna_base64url_character_copy_to_sixtet(
		     base64url_stream[ *base64url_stream_index + 2 ],
		     &sixtet3,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 3rd base64 sixtet.",
			 function );

			return( -1 );
		}
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing 3rd base64 character.",
		 function );

		return( -1 );
	}
	if( ( *base64url_stream_index + 3 ) < base64url_stream_size )
	{
		if( libuna_base64url_character_copy_to_sixtet(
		     base64url_stream[ *base64url_stream_index + 3 ],
		     &sixtet4,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 4th base64 sixtet.",
			 function );

			return( -1 );
		}
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing 4th base64 character.",
		 function );

		return( -1 );
	}
	*base64url_triplet   = sixtet1;
	*base64url_triplet <<= 6;
	*base64url_triplet  += sixtet2;
	*base64url_triplet <<= 6;
	*base64url_triplet  += sixtet3;
	*base64url_triplet <<= 6;
	*base64url_triplet  += sixtet4;

	*base64url_stream_index += 4;

	return( 1 );
}

/* Copies a base64 triplet to a base64 URL stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_base64url_triplet_copy_to_base64url_stream(
                   uint32_t base64url_triplet,
                   uint8_t *base64url_stream,
                   size_t base64url_stream_size,
                   size_t *base64url_stream_index,
                   liberror_error_t **error )
{
	static char *function = "libuna_base64url_triplet_copy_to_byte_stream";
	uint8_t sixtet1       = 0;
	uint8_t sixtet2       = 0;
	uint8_t sixtet3       = 0;
	uint8_t sixtet4       = 0;

	if( base64url_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 URL stream.",
		 function );

		return( -1 );
	}
	if( base64url_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base64 URL stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( base64url_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 URL stream index.",
		 function );

		return( -1 );
	}
	if( *base64url_stream_index >= base64url_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 URL stream string too small.",
		 function );

		return( -1 );
	}
	/* Separate the 3 bytes value into 4 x 6 bit values
	 */
	sixtet4          = (uint8_t) ( base64url_triplet & 0x3f );
	base64url_triplet >>= 6;
	sixtet3          = (uint8_t) ( base64url_triplet & 0x3f );
	base64url_triplet >>= 6;
	sixtet2          = (uint8_t) ( base64url_triplet & 0x3f );
	base64url_triplet >>= 6;
	sixtet1          = (uint8_t) ( base64url_triplet & 0x3f );

	/* Spread the encoding over 2 characters if 1 byte is available
	 */
	if( *base64url_stream_index >= base64url_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 URL stream is too small.",
		 function );

		return( -1 );
	}
	base64url_stream[ *base64url_stream_index ] = libuna_base64url_character_from_sixtet(
	                                               sixtet1 );

	*base64url_stream_index += 1;

	if( *base64url_stream_index >= base64url_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 URL stream is too small.",
		 function );

		return( -1 );
	}
	base64url_stream[ *base64url_stream_index ] = libuna_base64url_character_from_sixtet(
	                                               sixtet2 );

	*base64url_stream_index += 1;

	if( *base64url_stream_index >= base64url_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 URL stream is too small.",
		 function );

		return( -1 );
	}
	/* Spread the encoding over 3 characters if 2 bytes are available
	 * Otherwise pad the remaining bytes
	 */

	/* TODO fix */
	if( padding_size < 2 )
	{
		base64url_stream[ *base64url_stream_index ] = libuna_base64url_character_from_sixtet(
		                                               sixtet3 );
	}
	*base64url_stream_index += 1;

	if( *base64url_stream_index >= base64url_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 URL stream is too small.",
		 function );

		return( -1 );
	}
	/* Spread the encoding over 4 characters if 3 bytes are available
	 * Otherwise pad the remaining bytes
	 */
	if( padding_size >= 1 )
	{
		base64url_stream[ *base64url_stream_index ] = libuna_base64url_character_from_sixtet(
		                                               sixtet4 );
	}
	*base64url_stream_index += 1;

	return( 1 );
}

/* Copies a base64 triplet from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_base64url_triplet_copy_from_byte_stream(
                   uint32_t *base64url_triplet,
                   const uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   uint8_t *padding_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_base64url_triplet_copy_to_byte_stream";

	if( base64url_triplet == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 triplet.",
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
	if( byte_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream index.",
		 function );

		return( -1 );
	}
	if( *byte_stream_index >= byte_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream string too small.",
		 function );

		return( -1 );
	}
	/* Determine the value of 3 bytes (24 bits)
	 */
	*base64url_triplet      = byte_stream[ *byte_stream_index ] << 16;
	*byte_stream_index += 1;
	*padding_size       = 0;

	if( *byte_stream_index <= byte_stream_size )
	{
		*base64url_triplet    += byte_stream[ *byte_stream_index ] << 8;
		*byte_stream_index += 1;
	}
	else
	{
		*padding_size += 1;
	}
	if( *byte_stream_index <= byte_stream_size )
	{
		*base64url_triplet    += byte_stream[ *byte_stream_index ];
		*byte_stream_index += 1;
	}
	else
	{
		*padding_size += 1;
	}
	return( 1 );
}

/* Copies a base64 triplet to a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_base64url_triplet_copy_to_byte_stream(
                   uint32_t base64url_triplet,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   uint8_t padding_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_base64url_triplet_copy_to_byte_stream";

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
	if( byte_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream index.",
		 function );

		return( -1 );
	}
	if( *byte_stream_index >= byte_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream string too small.",
		 function );

		return( -1 );
	}
	byte_stream[ *byte_stream_index ] = (uint8_t) ( ( base64url_triplet >> 16 ) & 0xff );

	*byte_stream_index += 1;

	if( padding_size <= 1 )
	{
		if( *byte_stream_index >= byte_stream_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: byte stream string too small.",
			 function );

			return( -1 );
		}
		byte_stream[ *byte_stream_index ] = (uint8_t) ( ( base64url_triplet >> 8 ) & 0xff );

		*byte_stream_index += 1;
	}
	if( padding_size == 0 )
	{
		if( *byte_stream_index >= byte_stream_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: byte stream is too small.",
			 function );

			return( -1 );
		}
		byte_stream[ *byte_stream_index ] = (uint8_t) ( base64url_triplet & 0xff );

		*byte_stream_index += 1;
	}
	return( 1 );
}

/* Determines the size of a byte stream from a base64 URL stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base64url_stream_decode_size(
     uint8_t *base64url_stream,
     size_t base64url_stream_size,
     size_t *byte_stream_size,
     liberror_error_t **error );

/* Copies a byte stream from a base64 URL stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base64url_stream_decode(
     uint8_t *base64url_stream,
     size_t base64url_stream_size,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     liberror_error_t **error )
{
	static char *function      = "libuna_base64url_stream_decode";
	size_t base64url_stream_index = 0;
	size_t byte_stream_index   = 0;
	uint32_t base64url_triplet    = 0;
	uint8_t padding_size       = 0;

	if( base64url_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 URL stream.",
		 function );

		return( -1 );
	}
	if( base64url_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base64 URL stream size value exceeds maximum.",
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
	/* Make sure the byte stream is able to hold
	 * at least 3 bytes for each 4 bytes
	 */
	if( ( ( base64url_stream_size * 3 ) / 4 ) < byte_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream is too small.",
		 function );

		return( -1 );
	}
	while( base64url_stream_index < base64url_stream_size )
	{
		if( padding_size > 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 1st base64 sixtet.",
			 function );

			return( -1 );
		}
		/* Convert the base64 URL stream into a base64 triplet
		 */
		if( libuna_base64url_triplet_copy_from_base64url_stream(
		     &base64url_triplet,
		     base64url_stream,
		     base64url_stream_size,
		     &base64url_stream_index,
		     (uint8_t ) '=',
		     &padding_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy base64 triplet from base64 URL stream.",
			 function );

			return( -1 );
		}
		/* Convert the base64 triplet into a byte stream
		 */
		if( libuna_base64url_triplet_copy_to_byte_stream(
		     base64url_triplet,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_index,
		     padding_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy base64 triplet to byte stream.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the size of a base64 URL stream from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base64url_stream_encode_size(
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *base64url_stream_size,
     liberror_error_t **error );

/* Copies a base64 URL stream from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base64url_stream_encode(
     uint8_t *base64url_stream,
     size_t base64url_stream_size,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     liberror_error_t **error )
{
	static char *function      = "libuna_base64url_stream_encode";
	size_t base64url_stream_index = 0;
	size_t byte_stream_index   = 0;
	uint32_t base64url_triplet    = 0;
	uint8_t padding_size       = 0;

	if( base64url_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 URL stream.",
		 function );

		return( -1 );
	}
	if( base64url_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base64 URL stream size value exceeds maximum.",
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
	/* Make sure the base64 URL stream is able to hold
	 * at least 4 bytes for each 3 bytes
	 */
	if( ( ( byte_stream_size * 4 ) / 3 ) < base64url_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 URL stream is too small.",
		 function );

		return( -1 );
	}
	while( byte_stream_index < byte_stream_size )
	{
		/* Convert the byte stream into a base64 triplet
		 */
		if( libuna_base64url_triplet_copy_from_byte_stream(
		     &base64url_triplet,
		     byte_stream,
		     byte_stream_size,
		     &byte_stream_index,
		     &padding_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy base64 triplet from byte stream.",
			 function );

			return( -1 );
		}
		/* Convert the base64 triplet into a base64 URL stream
		 */
		if( libuna_base64url_triplet_copy_to_base64url_stream(
		     base64url_triplet,
		     base64url_stream,
		     base64url_stream_size,
		     &base64url_stream_index,
		     (uint8_t) '=',
		     padding_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy base64 triplet to base64 URL stream.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

#endif /* TODO */

