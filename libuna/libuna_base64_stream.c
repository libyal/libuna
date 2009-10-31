/*
 * Base64 stream functions
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

#include "libuna_base64_stream.h"
#include "libuna_definitions.h"
#include "libuna_inline.h"
#include "libuna_types.h"

static uint8_t libuna_base64_sixtet_to_character_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#define libuna_base64_character_from_sixtet( sixtet ) \
	libuna_base64_sixtet_to_character_table[ sixtet ]

/* Copies a base64 character to a base64 sixtet
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_base64_character_copy_to_sixtet(
                   uint8_t base64_character,
                   uint8_t *base64_sixtet,
                   liberror_error_t **error )
{
	static char *function = "libuna_base64_character_copy_to_sixtet";

	if( base64_sixtet == NULL )
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
	if( ( base64_character >= (uint8_t) 'A' )
	 && ( base64_character <= (uint8_t) 'I' ) )
	{
		*base64_sixtet = base64_character - (uint8_t) 'A';
	}
	else if( ( base64_character >= (uint8_t) 'J' )
	      && ( base64_character <= (uint8_t) 'R' ) )
	{
		*base64_sixtet = base64_character - (uint8_t) 'J' + 9;
	}
	else if( ( base64_character >= (uint8_t) 'S' )
	      && ( base64_character <= (uint8_t) 'Z' ) )
	{
		*base64_sixtet = base64_character - (uint8_t) 'S' + 18;
	}
	/* a-z is not a continous range on a EBCDIC based system
	 * it consists of the ranges: a-i, j-r, s-z
	 */
	else if( ( base64_character >= (uint8_t) 'a' )
	      && ( base64_character <= (uint8_t) 'i' ) )
	{
		*base64_sixtet = base64_character - (uint8_t) 'a' + 26;
	}
	else if( ( base64_character >= (uint8_t) 'j' )
	      && ( base64_character <= (uint8_t) 'r' ) )
	{
		*base64_sixtet = base64_character - (uint8_t) 'j' + 35;
	}
	else if( ( base64_character >= (uint8_t) 's' )
	      && ( base64_character <= (uint8_t) 'z' ) )
	{
		*base64_sixtet = base64_character - (uint8_t) 's' + 44;
	}
	else if( ( base64_character >= (uint8_t) '0' )
	      && ( base64_character <= (uint8_t) '9' ) )
	{
		*base64_sixtet = base64_character - (uint8_t) '0' + 52;
	}
	else if( base64_character == (uint8_t) '+' )
	{
		*base64_sixtet = 62;
	}
	else if( base64_character == (uint8_t) '/' )
	{
		*base64_sixtet = 63;
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

/* Copies a base64 triplet from a base64 stream
 * A padding character value of 0 indicates the lack of padding characters
 * Note that the padding size will still be set to indicate the amount of
 * sixtets in the triplet
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_base64_triplet_copy_from_base64_stream(
                   uint32_t *base64_triplet,
                   const uint8_t *base64_stream,
                   size_t base64_stream_size,
                   size_t *base64_stream_index,
                   uint8_t padding_character,
                   uint8_t *padding_size,
                   liberror_error_t **error )
{
	static char *function               = "libuna_base64_triplet_copy_from_base64_stream";
	uint8_t amount_of_base64_characters = 0;
	uint8_t sixtet1                     = 0;
	uint8_t sixtet2                     = 0;
	uint8_t sixtet3                     = 0;
	uint8_t sixtet4                     = 0;

	if( base64_triplet == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 triplet.",
		 function );

		return( -1 );
	}
	if( base64_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 stream.",
		 function );

		return( -1 );
	}
	if( base64_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base64 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( base64_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 stream index.",
		 function );

		return( -1 );
	}
	if( *base64_stream_index >= base64_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 stream string too small.",
		 function );

		return( -1 );
	}
	if( padding_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid padding size.",
		 function );

		return( -1 );
	}
	*padding_size = 0;

	if( libuna_base64_character_copy_to_sixtet(
	     base64_stream[ *base64_stream_index ],
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
	if( ( *base64_stream_index + 1 ) < base64_stream_size )
	{
		if( libuna_base64_character_copy_to_sixtet(
		     base64_stream[ *base64_stream_index + 1 ],
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
	amount_of_base64_characters = 2;

	if( ( *base64_stream_index + 2 ) < base64_stream_size )
	{
		if( ( padding_character != 0 )
		 && ( base64_stream[ *base64_stream_index + 2 ] == padding_character ) )
		{
			sixtet3                      = 0;
			*padding_size               += 1;
			amount_of_base64_characters += 1;
		}
		else
		{
			if( libuna_base64_character_copy_to_sixtet(
			     base64_stream[ *base64_stream_index + 2 ],
			     &sixtet3,
			     error ) != 1 )
			{
				if( padding_character != 0 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
					 "%s: invalid 3rd base64 sixtet.",
					 function );

					return( -1 );
				}
				liberror_error_free(
				 error );

				*padding_size += 1;
			}
			else
			{
				amount_of_base64_characters += 1;
			}
		}
	}
	else
	{
		if( padding_character != 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: missing 3rd base64 character.",
			 function );

			return( -1 );
		}
		*padding_size += 1;
	}
	if( ( *base64_stream_index + 3 ) < base64_stream_size )
	{
		if( ( padding_character != 0 )
		 && ( base64_stream[ *base64_stream_index + 3 ] == padding_character ) )
		{
			sixtet4                      = 0;
			*padding_size               += 1;
			amount_of_base64_characters += 1;
		}
		else
		{
			if( ( padding_character != 0 )
			 && ( *padding_size > 0 ) )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: invalid 4th base64 sixtet.",
				 function );

				return( -1 );
			}
			if( libuna_base64_character_copy_to_sixtet(
			     base64_stream[ *base64_stream_index + 3 ],
			     &sixtet4,
			     error ) != 1 )
			{
				if( padding_character != 0 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
					 "%s: invalid 4rd base64 sixtet.",
					 function );

					return( -1 );
				}
				liberror_error_free(
				 error );

				*padding_size += 1;
			}
			else
			{
				amount_of_base64_characters += 1;
			}
		}
	}
	else
	{
		if( padding_character != 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: missing 4th base64 character.",
			 function );

			return( -1 );
		}
		*padding_size += 1;
	}
	*base64_triplet   = sixtet1;
	*base64_triplet <<= 6;
	*base64_triplet  += sixtet2;
	*base64_triplet <<= 6;
	*base64_triplet  += sixtet3;
	*base64_triplet <<= 6;
	*base64_triplet  += sixtet4;

	*base64_stream_index += amount_of_base64_characters;

	return( 1 );
}

/* Copies a base64 triplet to a base64 stream
 * A padding character value of 0 indicates the lack of padding characters
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_base64_triplet_copy_to_base64_stream(
                   uint32_t base64_triplet,
                   uint8_t *base64_stream,
                   size_t base64_stream_size,
                   size_t *base64_stream_index,
                   uint8_t padding_character,
                   uint8_t padding_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_base64_triplet_copy_to_byte_stream";
	uint8_t sixtet1       = 0;
	uint8_t sixtet2       = 0;
	uint8_t sixtet3       = 0;
	uint8_t sixtet4       = 0;

	if( base64_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 stream.",
		 function );

		return( -1 );
	}
	if( base64_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base64 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( base64_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 stream index.",
		 function );

		return( -1 );
	}
	if( *base64_stream_index >= base64_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 stream string too small.",
		 function );

		return( -1 );
	}
	/* Separate the 3 bytes value into 4 x 6 bit values
	 */
	sixtet4          = (uint8_t) ( base64_triplet & 0x3f );
	base64_triplet >>= 6;
	sixtet3          = (uint8_t) ( base64_triplet & 0x3f );
	base64_triplet >>= 6;
	sixtet2          = (uint8_t) ( base64_triplet & 0x3f );
	base64_triplet >>= 6;
	sixtet1          = (uint8_t) ( base64_triplet & 0x3f );

	/* Spread the encoding over 2 characters if 1 byte is available
	 */
	if( *base64_stream_index >= base64_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 stream is too small.",
		 function );

		return( -1 );
	}
	base64_stream[ *base64_stream_index ] = libuna_base64_character_from_sixtet(
	                                         sixtet1 );

	*base64_stream_index += 1;

	if( *base64_stream_index >= base64_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 stream is too small.",
		 function );

		return( -1 );
	}
	base64_stream[ *base64_stream_index ] = libuna_base64_character_from_sixtet(
	                                         sixtet2 );

	*base64_stream_index += 1;

	if( *base64_stream_index >= base64_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 stream is too small.",
		 function );

		return( -1 );
	}
	/* Spread the encoding over 3 characters if 2 bytes are available
	 * Otherwise pad the remaining bytes if required
	 */
	if( padding_size < 2 )
	{
		base64_stream[ *base64_stream_index ] = libuna_base64_character_from_sixtet(
		                                         sixtet3 );

		*base64_stream_index += 1;
	}
	else if( padding_character != 0 )
	{
		base64_stream[ *base64_stream_index ] = padding_character;

		*base64_stream_index += 1;
	}
	if( *base64_stream_index >= base64_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 stream is too small.",
		 function );

		return( -1 );
	}
	/* Spread the encoding over 4 characters if 3 bytes are available
	 * Otherwise pad the remaining bytes if required
	 */
	if( padding_size >= 1 )
	{
		base64_stream[ *base64_stream_index ] = libuna_base64_character_from_sixtet(
		                                         sixtet4 );

		*base64_stream_index += 1;
	}
	else if( padding_character != 0 )
	{
		base64_stream[ *base64_stream_index ] = padding_character;

		*base64_stream_index += 1;
	}
	return( 1 );
}

/* Copies a base64 triplet from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_base64_triplet_copy_from_byte_stream(
                   uint32_t *base64_triplet,
                   const uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   uint8_t *padding_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_base64_triplet_copy_to_byte_stream";

	if( base64_triplet == NULL )
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
	*base64_triplet      = byte_stream[ *byte_stream_index ] << 16;
	*byte_stream_index += 1;
	*padding_size       = 0;

	if( *byte_stream_index <= byte_stream_size )
	{
		*base64_triplet    += byte_stream[ *byte_stream_index ] << 8;
		*byte_stream_index += 1;
	}
	else
	{
		*padding_size += 1;
	}
	if( *byte_stream_index <= byte_stream_size )
	{
		*base64_triplet    += byte_stream[ *byte_stream_index ];
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
LIBUNA_INLINE int libuna_base64_triplet_copy_to_byte_stream(
                   uint32_t base64_triplet,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   uint8_t padding_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_base64_triplet_copy_to_byte_stream";

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
	byte_stream[ *byte_stream_index ] = (uint8_t) ( ( base64_triplet >> 16 ) & 0xff );

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
		byte_stream[ *byte_stream_index ] = (uint8_t) ( ( base64_triplet >> 8 ) & 0xff );

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
		byte_stream[ *byte_stream_index ] = (uint8_t) ( base64_triplet & 0xff );

		*byte_stream_index += 1;
	}
	return( 1 );
}

/* Determines the size of a byte stream from a base64 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base64_stream_decode_size(
     uint8_t *base64_stream,
     size_t base64_stream_size,
     size_t *byte_stream_size,
     liberror_error_t **error )
{
	static char *function = "libuna_base64_stream_decode_size";

	if( base64_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 stream.",
		 function );

		return( -1 );
	}
	if( base64_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base64 stream size value exceeds maximum.",
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
	/* Make sure the base64 stream is able to hold
	 * at least 3 bytes for each 4 bytes
	 */
	*byte_stream_size = base64_stream_size / 4;

	if( ( base64_stream_size % 4 ) != 0 )
	{
		*byte_stream_size += 1;
	}
	*byte_stream_size *= 3;

	if( base64_stream[ base64_stream_size - 1 ] == (uint8_t) '=' )
	{
		*byte_stream_size -= 1;
	}
	if( base64_stream[ base64_stream_size - 2 ] == (uint8_t) '=' )
	{
		*byte_stream_size -= 1;
	}
	if( base64_stream[ base64_stream_size - 3 ] == (uint8_t) '=' )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
		 "%s: invalid amount of padding.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies a byte stream from a base64 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base64_stream_decode(
     uint8_t *base64_stream,
     size_t base64_stream_size,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     liberror_error_t **error )
{
	static char *function              = "libuna_base64_stream_decode";
	size_t base64_stream_index         = 0;
	size_t byte_stream_index           = 0;
	size_t calculated_byte_stream_size = 0;
	uint32_t base64_triplet            = 0;
	uint8_t padding_size               = 0;

	if( base64_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 stream.",
		 function );

		return( -1 );
	}
	if( base64_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base64 stream size value exceeds maximum.",
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
	calculated_byte_stream_size = ( base64_stream_size / 4 ) * 3;

	if( ( base64_stream_size % 4 ) != 0 )
	{
		calculated_byte_stream_size += 1;
	}
	calculated_byte_stream_size *= 3;

	if( base64_stream[ base64_stream_size - 1 ] == (uint8_t) '=' )
	{
		calculated_byte_stream_size -= 1;
	}
	if( base64_stream[ base64_stream_size - 2 ] == (uint8_t) '=' )
	{
		calculated_byte_stream_size -= 1;
	}
	if( base64_stream[ base64_stream_size - 3 ] == (uint8_t) '=' )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
		 "%s: invalid amount of padding.",
		 function );

		return( -1 );
	}
	if( byte_stream_size < calculated_byte_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream is too small.",
		 function );

		return( -1 );
	}
	while( base64_stream_index < base64_stream_size )
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
		/* Convert the base64 stream into a base64 triplet
		 */
		if( libuna_base64_triplet_copy_from_base64_stream(
		     &base64_triplet,
		     base64_stream,
		     base64_stream_size,
		     &base64_stream_index,
		     (uint8_t ) '=',
		     &padding_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy base64 triplet from base64 stream.",
			 function );

			return( -1 );
		}
		/* Convert the base64 triplet into a byte stream
		 */
		if( libuna_base64_triplet_copy_to_byte_stream(
		     base64_triplet,
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

/* Determines the size of a base64 stream from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base64_stream_encode_size(
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *base64_stream_size,
     liberror_error_t **error )
{
	static char *function = "libuna_base64_stream_encode_size";

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
	if( base64_stream_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 stream size.",
		 function );

		return( -1 );
	}
	/* Make sure the base64 stream is able to hold
	 * at least 4 bytes for each 3 bytes
	 */
	*base64_stream_size = byte_stream_size / 3;

	if( ( byte_stream_size % 3 ) != 0 )
	{
		*base64_stream_size += 1;
	}
	*base64_stream_size *= 4;

	return( 1 );
}

/* Copies a base64 stream from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base64_stream_encode(
     uint8_t *base64_stream,
     size_t base64_stream_size,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     liberror_error_t **error )
{
	static char *function                = "libuna_base64_stream_encode";
	size_t calculated_base64_stream_size = 0;
	size_t base64_stream_index           = 0;
	size_t byte_stream_index             = 0;
	uint32_t base64_triplet              = 0;
	uint8_t padding_size                 = 0;

	if( base64_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid base64 stream.",
		 function );

		return( -1 );
	}
	if( base64_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid base64 stream size value exceeds maximum.",
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
	/* Make sure the base64 stream is able to hold
	 * at least 4 bytes for each 3 bytes
	 */
	calculated_base64_stream_size = byte_stream_size / 3;

	if( ( byte_stream_size % 3 ) != 0 )
	{
		calculated_base64_stream_size += 1;
	}
	calculated_base64_stream_size *= 4;

	if( base64_stream_size < calculated_base64_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 stream is too small.",
		 function );

		return( -1 );
	}
	while( byte_stream_index < byte_stream_size )
	{
		/* Convert the byte stream into a base64 triplet
		 */
		if( libuna_base64_triplet_copy_from_byte_stream(
		     &base64_triplet,
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
		/* Convert the base64 triplet into a base64 stream
		 */
		if( libuna_base64_triplet_copy_to_base64_stream(
		     base64_triplet,
		     base64_stream,
		     base64_stream_size,
		     &base64_stream_index,
		     (uint8_t) '=',
		     padding_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy base64 triplet to base64 stream.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

