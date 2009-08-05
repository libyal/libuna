/*
 * Byte stream functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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
#include "libuna_types.h"
#include "libuna_unicode_character.h"

static uint8_t libuna_base64_sixtet_to_character_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#define libuna_base64_character_from_sixtet( sixtet ) \
	libuna_base64_sixtet_to_character_table[ sixtet ]

/* A-Z is not a continous range on a EBCDIC based system
 * it consists of A-I, J-R, S-Z
 * so is a-z is not a continous range on a EBCDIC based system
 * it consists of a-i, j-r, s-z
 */
#define libuna_base64_character_to_sixtet( character ) \
	( ( character >= (uint8_t) 'A' ) && ( character <= (uint8_t) 'I' ) ) ? character - (uint8_t) 'A' : \
	( ( character >= (uint8_t) 'J' ) && ( character <= (uint8_t) 'R' ) ) ? character - (uint8_t) 'J' + 9 : \
	( ( character >= (uint8_t) 'S' ) && ( character <= (uint8_t) 'Z' ) ) ? character - (uint8_t) 'S' + 18 : \
	( ( character >= (uint8_t) 'a' ) && ( character <= (uint8_t) 'i' ) ) ? character - (uint8_t) 'a' + 26 : \
	( ( character >= (uint8_t) 'j' ) && ( character <= (uint8_t) 'r' ) ) ? character - (uint8_t) 'j' + 32 : \
	( ( character >= (uint8_t) 's' ) && ( character <= (uint8_t) 'z' ) ) ? character - (uint8_t) 's' + 44 : \
	( ( character >= (uint8_t) '0' ) && ( character <= (uint8_t) '9' ) ) ? character - (uint8_t) '0' + 52 : \
	( character >= (uint8_t) '+' ) ? 62 : \
	( character >= (uint8_t) '/' ) ? 63 : \
	0xff

/* Determines the size of a byte stream from a base64 stream
 * Returns 1 if successful or -1 on error
 */
int libuna_base64_stream_decode_size(
     uint8_t *base64_stream,
     size_t base64_stream_size,
     size_t *byte_stream_size,
     liberror_error_t **error );

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
	static char *function         = "libuna_base64_stream_decode";
	size_t base64_stream_iterator = 0;
	size_t byte_stream_iterator   = 0;
	size_t padding_size           = 0;
	uint32_t triplet_value        = 0;
	uint8_t sixtet1               = 0;
	uint8_t sixtet2               = 0;
	uint8_t sixtet3               = 0;
	uint8_t sixtet4               = 0;

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
	if( ( ( base64_stream_size * 3 ) / 4 ) < byte_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream is too small.",
		 function );

		return( -1 );
	}
	/* Increment over the base64 stream 4 bytes at a time
	 */
	for( base64_stream_iterator = 0;
	     base64_stream_iterator < base64_stream_size;
	     base64_stream_iterator += 4 )
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
		sixtet1 = libuna_base64_character_to_sixtet(
		           base64_stream[ base64_stream_iterator ] );

		if( sixtet1 > 64 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 1st base64 sixtet.",
			 function );

			return( -1 );
		}
		if( ( base64_stream_iterator + 1 ) < base64_stream_size )
		{
			sixtet2 = libuna_base64_character_to_sixtet(
				   base64_stream[ base64_stream_iterator + 1 ] );

			if( sixtet2 > 64 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: invalid 2nd base64 sixtet.",
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
	                 "%s: missing 2nd base64 sixtets.",
	                 function );

			return( -1 );
		}
		if( ( base64_stream_iterator + 2 ) < base64_stream_size )
		{
			if( base64_stream[ base64_stream_iterator + 2 ] == (uint8_t) '=' )
			{
				sixtet3 = 0;

				padding_size++;
			}
			else
			{
				sixtet3 = libuna_base64_character_to_sixtet(
					   base64_stream[ base64_stream_iterator + 2 ] );

				if( sixtet3 > 64 )
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
		}
		else
		{
	                liberror_error_set(
	                 error,
	                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
	                 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
	                 "%s: missing 3rd base64 sixtet.",
	                 function );

			return( -1 );
		}
		if( ( base64_stream_iterator + 3 ) < base64_stream_size )
		{
			if( base64_stream[ base64_stream_iterator + 3 ] == (uint8_t) '=' )
			{
				sixtet4 = 0;

				padding_size++;
			}
			else
			{
				if( padding_size > 0 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
					 "%s: invalid 4th base64 sixtet.",
					 function );

					return( -1 );
				}
				sixtet4 = libuna_base64_character_to_sixtet(
					   base64_stream[ base64_stream_iterator + 3 ] );

				if( sixtet4 > 64 )
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
		}
		else
		{
	                liberror_error_set(
	                 error,
	                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
	                 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
	                 "%s: missing 4th base64 sixtet.",
	                 function );

			return( -1 );
		}
		triplet_value   = sixtet1;
		triplet_value <<= 6;
		triplet_value  += sixtet2;
		triplet_value <<= 6;
		triplet_value  += sixtet3;
		triplet_value <<= 6;
		triplet_value  += sixtet4;

		if( ( byte_stream_iterator + 1 ) >= byte_stream_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: byte stream is too small.",
			 function );

			return( -1 );
		}
		byte_stream[ byte_stream_iterator++ ] = (uint8_t) ( ( triplet_value >> 16 ) & 0xff );

		if( padding_size <= 1 )
		{
			if( ( byte_stream_iterator + 1 ) >= byte_stream_size )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: byte stream is too small.",
				 function );

				return( -1 );
			}
			byte_stream[ byte_stream_iterator++ ] = (uint8_t) ( ( triplet_value >> 8 ) & 0xff );
		}
		if( padding_size == 0 )
		{
			if( ( byte_stream_iterator + 1 ) >= byte_stream_size )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: byte stream is too small.",
				 function );

				return( -1 );
			}
			byte_stream[ byte_stream_iterator++ ] = (uint8_t) ( triplet_value & 0xff );
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
     liberror_error_t **error );

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
	static char *function         = "libuna_base64_stream_encode";
	size_t base64_stream_iterator = 0;
	size_t byte_stream_iterator   = 0;
	size_t padding_size           = 0;
	uint32_t triplet_value        = 0;
	uint8_t sixtet1               = 0;
	uint8_t sixtet2               = 0;
	uint8_t sixtet3               = 0;
	uint8_t sixtet4               = 0;

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
	if( ( ( byte_stream_size * 4 ) / 3 ) < base64_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: base64 stream is too small.",
		 function );

		return( -1 );
	}
	/* Increment over the byte stream 3 bytes at a time
	 */
	for( byte_stream_iterator = 0;
	     byte_stream_iterator < byte_stream_size;
	     byte_stream_iterator += 3 )
	{
		/* Determine the value of 3 bytes (24 bits)
		 */
		triplet_value = byte_stream[ byte_stream_iterator ] << 16;

		if( ( byte_stream_iterator + 1 ) < byte_stream_size )
		{
			triplet_value = byte_stream[ byte_stream_iterator + 1 ] << 8;
		}
		if( ( byte_stream_iterator + 2 ) < byte_stream_size )
		{
			triplet_value = byte_stream[ byte_stream_iterator + 2 ];
		}

		/* Separate the 3 bytes value into 4 x 6 bit values
		 */
		sixtet4         = (uint8_t) ( triplet_value & 0x3f );
		triplet_value >>= 6;
		sixtet3         = (uint8_t) ( triplet_value & 0x3f );
		triplet_value >>= 6;
		sixtet2         = (uint8_t) ( triplet_value & 0x3f );
		triplet_value >>= 6;
		sixtet1         = (uint8_t) ( triplet_value & 0x3f );

		/* Spread the encoding over 2 characters if 1 byte is available
		 */
		if( ( base64_stream_iterator + 1 ) >= base64_stream_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: base64 stream is too small.",
			 function );

			return( -1 );
		}
		base64_stream[ base64_stream_iterator++ ] = libuna_base64_character_from_sixtet(
		                                             sixtet1 );

		if( ( base64_stream_iterator + 1 ) >= base64_stream_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: base64 stream is too small.",
			 function );

			return( -1 );
		}
		base64_stream[ base64_stream_iterator++ ] = libuna_base64_character_from_sixtet(
		                                             sixtet2 );

		/* Spread the encoding over 3 characters if 2 bytes are available
		 */
		if( ( byte_stream_iterator + 1 ) < byte_stream_size )
		{
			if( ( base64_stream_iterator + 1 ) >= base64_stream_size )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: base64 stream is too small.",
				 function );

				return( -1 );
			}
			base64_stream[ base64_stream_iterator++ ] = libuna_base64_character_from_sixtet(
			                                             sixtet3 );
		}
		/* Spread the encoding over 4 characters if 3 bytes are available
		 */
		if( ( byte_stream_iterator + 1 ) < byte_stream_size )
		{
			if( ( base64_stream_iterator + 1 ) >= base64_stream_size )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: base64 stream is too small.",
				 function );

				return( -1 );
			}
			base64_stream[ base64_stream_iterator++ ] = libuna_base64_character_from_sixtet(
			                                             sixtet4 );
		}
	}
	/* Add padding if no modulo of 3 bytes was available
	 */
	for( padding_size = byte_stream_size % 3;
	     padding_size > 0;
	     padding_size-- )
	{
		base64_stream[ base64_stream_iterator++ ] = (uint8_t) '=';

		if( base64_stream_iterator > base64_stream_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: base64 stream is too small.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

