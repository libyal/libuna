/*
 * Unicode character functions
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
#include "libuna_codepage_ascii.h"
#include "libuna_codepage_iso_8859_1.h"
#include "libuna_codepage_iso_8859_2.h"
#include "libuna_codepage_iso_8859_3.h"
#include "libuna_codepage_iso_8859_4.h"
#include "libuna_codepage_iso_8859_5.h"
#include "libuna_codepage_iso_8859_6.h"
#include "libuna_codepage_iso_8859_7.h"
#include "libuna_codepage_iso_8859_8.h"
#include "libuna_codepage_iso_8859_9.h"
#include "libuna_codepage_iso_8859_10.h"
#include "libuna_codepage_iso_8859_11.h"
#include "libuna_codepage_iso_8859_13.h"
#include "libuna_codepage_iso_8859_14.h"
#include "libuna_codepage_iso_8859_15.h"
#include "libuna_codepage_iso_8859_16.h"
#include "libuna_codepage_koi8_r.h"
#include "libuna_codepage_koi8_u.h"
#include "libuna_codepage_windows_874.h"
#include "libuna_codepage_windows_1250.h"
#include "libuna_codepage_windows_1251.h"
#include "libuna_codepage_windows_1252.h"
#include "libuna_codepage_windows_1253.h"
#include "libuna_codepage_windows_1254.h"
#include "libuna_codepage_windows_1255.h"
#include "libuna_codepage_windows_1256.h"
#include "libuna_codepage_windows_1257.h"
#include "libuna_codepage_windows_1258.h"
#include "libuna_definitions.h"
#include "libuna_inline.h"
#include "libuna_types.h"
#include "libuna_unicode_character.h"

/* Determines the size of a byte stream character from a Unicode character
 * Adds the size to the byte stream character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_size_to_byte_stream(
                   libuna_unicode_character_t unicode_character,
                   int codepage,
                   size_t *byte_stream_character_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_size_to_byte_stream";

	if( byte_stream_character_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream character size.",
		 function );

		return( -1 );
	}
	/* TODO handle multi byte characters
	 */
	switch( codepage )
	{
		case LIBUNA_CODEPAGE_ASCII:
		case LIBUNA_CODEPAGE_ISO_8859_1:
		case LIBUNA_CODEPAGE_ISO_8859_2:
		case LIBUNA_CODEPAGE_ISO_8859_3:
		case LIBUNA_CODEPAGE_ISO_8859_4:
		case LIBUNA_CODEPAGE_ISO_8859_5:
		case LIBUNA_CODEPAGE_ISO_8859_6:
		case LIBUNA_CODEPAGE_ISO_8859_7:
		case LIBUNA_CODEPAGE_ISO_8859_8:
		case LIBUNA_CODEPAGE_ISO_8859_9:
		case LIBUNA_CODEPAGE_ISO_8859_10:
		case LIBUNA_CODEPAGE_ISO_8859_11:
		case LIBUNA_CODEPAGE_ISO_8859_13:
		case LIBUNA_CODEPAGE_ISO_8859_14:
		case LIBUNA_CODEPAGE_ISO_8859_15:
		case LIBUNA_CODEPAGE_ISO_8859_16:
		case LIBUNA_CODEPAGE_KOI8_R:
		case LIBUNA_CODEPAGE_KOI8_U:
		case LIBUNA_CODEPAGE_WINDOWS_874:
		case LIBUNA_CODEPAGE_WINDOWS_1250:
		case LIBUNA_CODEPAGE_WINDOWS_1251:
		case LIBUNA_CODEPAGE_WINDOWS_1252:
		case LIBUNA_CODEPAGE_WINDOWS_1253:
		case LIBUNA_CODEPAGE_WINDOWS_1254:
		case LIBUNA_CODEPAGE_WINDOWS_1255:
		case LIBUNA_CODEPAGE_WINDOWS_1256:
		case LIBUNA_CODEPAGE_WINDOWS_1257:
		case LIBUNA_CODEPAGE_WINDOWS_1258:
			*byte_stream_character_size += 1;
			break;

		default:
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported codepage: %d.",
			 function,
			 codepage );

			return( -1 );
	}
	return( 1 );
}

/* Copies a Unicode character from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_from_byte_stream(
                   libuna_unicode_character_t *unicode_character,
                   const uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   int codepage,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_from_byte_stream";

	if( unicode_character == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
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
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	*unicode_character = byte_stream[ *byte_stream_index ];

	switch( codepage )
	{
		case LIBUNA_CODEPAGE_ASCII:
			*unicode_character = libuna_codepage_ascii_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_1:
			*unicode_character = libuna_codepage_iso_8859_1_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_2:
			*unicode_character = libuna_codepage_iso_8859_2_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_3:
			*unicode_character = libuna_codepage_iso_8859_3_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_4:
			*unicode_character = libuna_codepage_iso_8859_4_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_5:
			*unicode_character = libuna_codepage_iso_8859_5_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_6:
			*unicode_character = libuna_codepage_iso_8859_6_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_7:
			*unicode_character = libuna_codepage_iso_8859_7_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_8:
			*unicode_character = libuna_codepage_iso_8859_8_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_9:
			*unicode_character = libuna_codepage_iso_8859_9_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_10:
			*unicode_character = libuna_codepage_iso_8859_10_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_11:
			*unicode_character = libuna_codepage_iso_8859_11_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_13:
			*unicode_character = libuna_codepage_iso_8859_13_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_14:
			*unicode_character = libuna_codepage_iso_8859_14_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_15:
			*unicode_character = libuna_codepage_iso_8859_15_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_16:
			*unicode_character = libuna_codepage_iso_8859_16_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_KOI8_R:
			*unicode_character = libuna_codepage_koi8_r_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_KOI8_U:
			*unicode_character = libuna_codepage_koi8_u_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_874:
			*unicode_character = libuna_codepage_windows_874_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1250:
			*unicode_character = libuna_codepage_windows_1250_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1251:
			*unicode_character = libuna_codepage_windows_1251_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1252:
			*unicode_character = libuna_codepage_windows_1252_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1253:
			*unicode_character = libuna_codepage_windows_1253_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1254:
			*unicode_character = libuna_codepage_windows_1254_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1255:
			*unicode_character = libuna_codepage_windows_1255_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1256:
			*unicode_character = libuna_codepage_windows_1256_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1257:
			*unicode_character = libuna_codepage_windows_1257_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1258:
			*unicode_character = libuna_codepage_windows_1258_byte_stream_to_unicode(
			                      byte_stream[ *byte_stream_index ] );
			break;

		default:
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			"%s: unsupported codepage: %d.",
			 function,
			 codepage );

			return( -1 );
	}
	*byte_stream_index += 1;

	return( 1 );
}

/* Copies a Unicode character to a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_to_byte_stream(
                   libuna_unicode_character_t unicode_character,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *byte_stream_index,
                   int codepage,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_to_byte_stream";

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
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	switch( codepage )
	{
		case LIBUNA_CODEPAGE_ASCII:
			byte_stream[ *byte_stream_index ] = libuna_codepage_ascii_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_1:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_1_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_2:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_2_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_3:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_3_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_4:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_4_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_5:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_5_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_6:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_6_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_7:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_7_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_8:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_8_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_9:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_9_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_10:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_10_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_11:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_11_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_13:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_13_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_14:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_14_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_15:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_15_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_16:
			byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_16_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_KOI8_R:
			byte_stream[ *byte_stream_index ] = libuna_codepage_koi8_r_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_KOI8_U:
			byte_stream[ *byte_stream_index ] = libuna_codepage_koi8_u_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_874:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_874_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1250:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1250_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1251:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1251_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1252:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1252_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1253:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1253_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1254:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1254_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1255:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1255_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1256:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1256_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1257:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1257_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1258:
			byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1258_unicode_to_byte_stream(
			                                     unicode_character );
			break;

		default:
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			"%s: unsupported codepage: %d.",
			 function,
		         codepage );

			return( -1 );
	}
	*byte_stream_index += 1;

	return( 1 );
}

/* Determines the size of a UTF-7 character from a Unicode character
 * Adds the size to the UTF-7 character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_size_to_utf7(
                   libuna_unicode_character_t unicode_character,
                   size_t *utf7_character_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_size_to_utf7";

	if( utf7_character_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 character size.",
		 function );

		return( -1 );
	}
	/* TODO */
	return( -1 );
}

/* Copies a Unicode character from a UTF-7 string
 * The bits of the base64 data contain:
 *   0 - 23 the base64 triplet
 *  24 - 25 the amount of sixtets in the triplet
 *  26 - 27 unused
 *  28 - 29 the current sixtet
 *       30 unused
 *       31 flag to indicate the current UTF-7 characters are (modified) base64 encoded
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_from_utf7(
                   libuna_unicode_character_t *unicode_character,
                   const libuna_utf7_character_t *utf7_string,
                   size_t utf7_string_size,
                   size_t *utf7_string_index,
                   uint32_t *utf7_base64_data,
                   liberror_error_t **error )
{
	static char *function     = "libuna_unicode_character_copy_from_utf7";
	uint32_t base64_triplet   = 0;
	uint8_t amount_of_sixtets = 0;
	uint8_t current_sixtet    = 0;
	uint8_t padding_size      = 0;
	uint8_t sixtet_bit_shift  = 0;

	if( unicode_character == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf7_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 string.",
		 function );

		return( -1 );
	}
	if( utf7_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-7 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf7_string_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 string index.",
		 function );

		return( -1 );
	}
	if( *utf7_string_index >= utf7_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-7 string too small.",
		 function );

		return( -1 );
	}
	if( utf7_base64_data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 base64 data.",
		 function );

		return( -1 );
	}
	if( ( *utf7_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) == LIBUNA_UTF7_IS_BASE64_ENCODED )
	{
		base64_triplet    = *utf7_base64_data & 0x00ffffff;
		amount_of_sixtets = ( *utf7_base64_data >> 24 ) & 0x03;
		current_sixtet    = ( *utf7_base64_data >> 28 ) & 0x03;

		if( current_sixtet >= amount_of_sixtets )
		{
			if( utf7_string[ *utf7_string_index ] == (uint8_t) '-' )
			{
				*utf7_base64_data   = 0;
				*utf7_string_index += 1;
			}
			/* A-Z is not a continous range on a EBCDIC based system
			 * it consists of the ranges: A-I, J-R, S-Z
			 */
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'A' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'I' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'J' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'R' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'S' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'Z' ) )
			{
			}
			/* a-z is not a continous range on a EBCDIC based system
			 * it consists of the ranges: a-i, j-r, s-z
			 */
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'a' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'i' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'j' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'r' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 's' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'z' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) '0' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) '9' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] == (uint8_t) '+' )
			      || ( utf7_string[ *utf7_string_index ] == (uint8_t) '/' ) )
			{
			}
			/* Any character not in the modified base64 alphabet
			 * terminates the base64 encoded sequence
			 */
			else
			{
				*utf7_base64_data = 0;
			}
		}
	}
	if( ( *utf7_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) == 0 )
	{
		/* Determine if the character is modified base64 encoded
		 * or a + character
		 */
		if( utf7_string[ *utf7_string_index ] == (uint8_t) '+' )
		{
			if( utf7_string[ *utf7_string_index + 1 ] != (uint8_t) '-' )
			{
				*utf7_base64_data = LIBUNA_UTF7_IS_BASE64_ENCODED;
			}
			*utf7_string_index += 1;
		}
		/* Determine if the character is valid directly encoded character
		 */
		else
		{
			/* A-Z is not a continous range on a EBCDIC based system
			 * it consists of the ranges: A-I, J-R, S-Z
			 */
			if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'A' )
			 && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'I' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'J' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'R' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'S' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'Z' ) )
			{
			}
			/* a-z is not a continous range on a EBCDIC based system
			 * it consists of the ranges: a-i, j-r, s-z
			 */
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'a' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'i' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 'j' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'r' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) 's' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) 'z' ) )
			{
			}
			else if( ( utf7_string[ *utf7_string_index ] >= (uint8_t) '0' )
			      && ( utf7_string[ *utf7_string_index ] <= (uint8_t) '9' ) )
			{
			}
			else switch( utf7_string[ *utf7_string_index ] )
			{
				/* Valid directly encoded whitespace
				 */
				case '\t':
				case '\n':
				case '\r':
				case ' ':
				/* Valid directly encoded characters
				 */
				case '\'':
				case '(':
				case ')':
				case ',':
				case '-':
				case '.':
				case '/':
				case ':':
				case '?':

				/* Valid optional directly encoded characters
				 */
				case '!':
				case '"':
				case '#':
				case '$':
				case '%':
				case '&':
				case '*':
				case ';':
				case '<':
				case '=':
				case '>':
				case '@':
				case '[':
				case ']':
				case '^':
				case '_':
				case '`':
				case '{':
				case '|':
				case '}':
					break;

				default:
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
					 "%s: invalid directly encoded UTF-7 character byte: 0x%02" PRIx8 ".",
					 function,
					 utf7_string[ *utf7_string_index ] );

					return( -1 );
			}
		}
	}
	if( ( *utf7_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) == 0 )
	{
		*unicode_character  = utf7_string[ *utf7_string_index ];
		*utf7_string_index += 1;
	}
	else if( ( amount_of_sixtets == 0 )
	      || ( current_sixtet >= amount_of_sixtets ) )
	{
		if( libuna_base64_triplet_copy_from_base64_stream(
		     &base64_triplet,
		     utf7_string,
		     utf7_string_size,
		     utf7_string_index,
		     0,
		     &padding_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy base64 encoded UTF-7 characters.",
			 function );

			return( -1 );
		}
		if( padding_size > 2 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported padding in base64 encoded UTF-7 characters.",
			 function );

			return( -1 );
		}
		amount_of_sixtets = 3 - padding_size;
		current_sixtet    = 0;
	}
	if( ( *utf7_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) == LIBUNA_UTF7_IS_BASE64_ENCODED )
	{
		sixtet_bit_shift   = 16 - ( current_sixtet * 8 );
		*unicode_character = ( ( base64_triplet >> sixtet_bit_shift ) & 0x000000ffUL ) << 8;
		current_sixtet    += 1;

		if( current_sixtet >= amount_of_sixtets )
		{
			if( libuna_base64_triplet_copy_from_base64_stream(
			     &base64_triplet,
			     utf7_string,
			     utf7_string_size,
			     utf7_string_index,
			     0,
			     &padding_size,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_CONVERSION,
				 LIBERROR_CONVERSION_ERROR_OUTPUT_FAILED,
				 "%s: unable to copy base64 encoded UTF-7 characters.",
				 function );

				return( -1 );
			}
			if( padding_size > 2 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported padding in base64 encoded UTF-7 characters.",
				 function );

				return( -1 );
			}
			amount_of_sixtets = 3 - padding_size;
			current_sixtet    = 0;
		}
		sixtet_bit_shift    = 16 - ( current_sixtet * 8 );
		*unicode_character += ( base64_triplet >> sixtet_bit_shift ) & 0x000000ffUL;
		current_sixtet     += 1;

		if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
		 && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_END ) )
		{
			return( -1 );
		}
	}
	if( ( *utf7_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) == LIBUNA_UTF7_IS_BASE64_ENCODED )
	{
		*utf7_base64_data  = LIBUNA_UTF7_IS_BASE64_ENCODED;
		*utf7_base64_data |= (uint32_t) current_sixtet << 28;
		*utf7_base64_data |= (uint32_t) amount_of_sixtets << 24;
		*utf7_base64_data |= base64_triplet & 0x00ffffff;
	}
	return( 1 );
}

/* Copies a Unicode character into a UTF-7 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_to_utf7(
                   libuna_unicode_character_t unicode_character,
                   libuna_utf7_character_t *utf7_string,
                   size_t utf7_string_size,
                   size_t *utf7_string_index,
                   uint32_t *utf7_base64_data,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_to_utf7";

	if( utf7_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 string.",
		 function );

		return( -1 );
	}
	if( utf7_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-7 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf7_string_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 string index.",
		 function );

		return( -1 );
	}
	if( *utf7_string_index >= utf7_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-7 string too small.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	/* Determine how many UTF-7 character bytes are required
	 */
	/* TODO */
	return( -1 );
}

/* Determines the size of a UTF-8 character from a Unicode character
 * Adds the size to the UTF-8 character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_size_to_utf8(
                   libuna_unicode_character_t unicode_character,
                   size_t *utf8_character_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_size_to_utf8";

	if( utf8_character_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 character size.",
		 function );

		return( -1 );
	}
	if( unicode_character < 0x080 )
	{
		*utf8_character_size += 1;
	}
	else if( unicode_character < 0x0800 )
	{
		*utf8_character_size += 2;
	}
	else if( unicode_character < 0x010000 )
	{
		*utf8_character_size += 3;
	}
	else if( unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		*utf8_character_size += 3;
	}
	else
	{
		*utf8_character_size += 4;
	}

/* If UTF-8 USC support is needed it should be implemented in
 * utf8_usc or something, but for now leave this here as a reminder

	else if( unicode_character < 0x010000 )
	{
		*utf8_character_size += 3;
	}
	else if( unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		*utf8_character_size += 2;
	}
	else if( unicode_character < 0x0200000 )
	{
		*utf8_character_size += 4;
	}
	else if( unicode_character < 0x0400000 )
	{
		*utf8_character_size += 5;
	}
	else
	{
		*utf8_character_size += 6;
	}
*/
	return( 1 );
}

/* Copies a Unicode character from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_from_utf8(
                   libuna_unicode_character_t *unicode_character,
                   const libuna_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   size_t *utf8_string_index,
                   liberror_error_t **error )
{
	static char *function                   = "libuna_unicode_character_copy_from_utf8";
	uint8_t utf8_character_additional_bytes = 0;

	if( unicode_character == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	if( *utf8_string_index >= utf8_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string too small.",
		 function );

		return( -1 );
	}
	/* Determine the amount of additional bytes of the UTF-8 character
	 */
	if( utf8_string[ *utf8_string_index ] < 0xc0 )
	{
		utf8_character_additional_bytes = 0;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xe0 )
	{
		utf8_character_additional_bytes = 1;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xf0 )
	{
		utf8_character_additional_bytes = 2;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xf8 )
	{
		utf8_character_additional_bytes = 3;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xfc )
	{
		utf8_character_additional_bytes = 4;
	}
	else
	{
		utf8_character_additional_bytes = 5;
	}
	if( ( *utf8_string_index + utf8_character_additional_bytes + 1 ) > utf8_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-8 character bytes.",
		 function );

		return( -1 );
	}
	/* Determine the UTF-8 character and make sure it is valid
	 * Unicode limits the UTF-8 character to consist of a maximum of 4 bytes
	 * while ISO 10646 Universal Character Set (UCS) allows up to 6 bytes
	 */
	if( utf8_string[ *utf8_string_index ] > 0xf4 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid 1st UTF-8 character byte: 0x%02" PRIx8 ".",
		 function,
		 utf8_string[ *utf8_string_index ] );

		return( -1 );
	}
	*unicode_character = utf8_string[ *utf8_string_index ];

	if( utf8_character_additional_bytes == 0 )
	{
		if( ( utf8_string[ *utf8_string_index ] >= 0x80 )
		 && ( utf8_string[ *utf8_string_index ] < 0xc2 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 1st UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index ] );

			return( -1 );
		}
	}
	if( utf8_character_additional_bytes >= 1 )
	{
		if( utf8_string[ *utf8_string_index + 1 ] > 0xbf )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		if( ( utf8_string[ *utf8_string_index ] == 0xe0 )
		 && ( utf8_string[ *utf8_string_index + 1 ] < 0xa0 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		else if( ( utf8_string[ *utf8_string_index ] == 0xed )
		      && ( utf8_string[ *utf8_string_index + 1 ] > 0x9f ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		else if( ( utf8_string[ *utf8_string_index ] == 0xf0 )
		      && ( utf8_string[ *utf8_string_index + 1 ] < 0x90 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		else if( ( utf8_string[ *utf8_string_index ] == 0xf4 )
		      && ( utf8_string[ *utf8_string_index + 1 ] > 0x8f ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		else if( utf8_string[ *utf8_string_index + 1 ] < 0x80 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 1 ];

		if( utf8_character_additional_bytes == 1 )
		{
			*unicode_character -= 0x03080;
		}
	}
	if( utf8_character_additional_bytes >= 2 )
	{
		if( ( utf8_string[ *utf8_string_index + 2 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 2 ] > 0xbf ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 3rd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 2 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 2 ];

		if( utf8_character_additional_bytes == 2 )
		{
			*unicode_character -= 0x0e2080;
		}
	}
	if( utf8_character_additional_bytes >= 3 )
	{
		if( ( utf8_string[ *utf8_string_index + 3 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 3 ] > 0xbf ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 4th UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 3 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 3 ];

		if( utf8_character_additional_bytes == 3 )
		{
			*unicode_character -= 0x03c82080;
		}
	}
	if( utf8_character_additional_bytes >= 4 )
	{
		if( ( utf8_string[ *utf8_string_index + 4 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 4 ] > 0xbf ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 5th UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 4 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 4 ];

		if( utf8_character_additional_bytes == 4 )
		{
			*unicode_character -= 0x0fa082080;
		}
	}
	if( utf8_character_additional_bytes == 5 )
	{
		if( ( utf8_string[ *utf8_string_index + 5 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 5 ] > 0xbf ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 6th UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 5 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 5 ];
		*unicode_character -= 0x082082080;
	}
	/* Determine if the Unicode character is valid
	 */
	if( *unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	*utf8_string_index += 1 + utf8_character_additional_bytes;

	return( 1 );
}

/* Copies a Unicode character into a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_to_utf8(
                   libuna_unicode_character_t unicode_character,
                   libuna_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   size_t *utf8_string_index,
                   liberror_error_t **error )
{
	static char *function                   = "libuna_unicode_character_copy_to_utf8";
	uint8_t utf8_character_additional_bytes = 0;
	uint8_t utf8_character_iterator         = 0;
	uint8_t utf8_first_character_mark       = 0;

	if( utf8_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	if( *utf8_string_index >= utf8_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string too small.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	/* Determine how many UTF-8 character bytes are required
	 */
	if( unicode_character < 0x080 )
	{
		utf8_character_additional_bytes = 0;
		utf8_first_character_mark       = 0;
	}
	else if( unicode_character < 0x0800 )
	{
		utf8_character_additional_bytes = 1;
		utf8_first_character_mark       = 0x0c0;
	}
	else if( unicode_character < 0x010000 )
	{
		utf8_character_additional_bytes = 2;
		utf8_first_character_mark       = 0x0e0;
	}
	else if( unicode_character < 0x0200000 )
	{
		utf8_character_additional_bytes = 3;
		utf8_first_character_mark       = 0x0f0;
	}
	else if( unicode_character < 0x0400000 )
	{
		utf8_character_additional_bytes = 4;
		utf8_first_character_mark       = 0x0f8;
	}
	else
	{
		utf8_character_additional_bytes = 5;
		utf8_first_character_mark       = 0x0fc;
	}
	/* Convert Unicode character into UTF-8 character bytes
	 */
	if( ( *utf8_string_index + utf8_character_additional_bytes ) >= utf8_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string too small.",
		 function );

		return( -1 );
	}
	for( utf8_character_iterator = utf8_character_additional_bytes; utf8_character_iterator > 0; utf8_character_iterator-- )
	{
		utf8_string[ *utf8_string_index + utf8_character_iterator ] = (libuna_utf8_character_t) ( ( unicode_character & 0x0bf ) | 0x080 );

		unicode_character >>= 6;
	}
	utf8_string[ *utf8_string_index ] = (libuna_utf8_character_t) ( unicode_character | utf8_first_character_mark );

	*utf8_string_index += 1 + utf8_character_additional_bytes;

	return( 1 );
}

/* Determines the size of a UTF-16 character from a Unicode character
 * Adds the size to the UTF-16 character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_size_to_utf16(
                   libuna_unicode_character_t unicode_character,
                   size_t *utf16_character_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_size_to_utf16";

	if( utf16_character_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 character size.",
		 function );

		return( -1 );
	}
	if( ( unicode_character > LIBUNA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
         && ( unicode_character <= LIBUNA_UTF16_CHARACTER_MAX ) )
	{
		*utf16_character_size += 2;
	}
	else
	{
		*utf16_character_size += 1;
	}
	return( 1 );
}

/* Copies a Unicode character from a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_from_utf16(
                   libuna_unicode_character_t *unicode_character,
                   const libuna_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   size_t *utf16_string_index,
                   liberror_error_t **error )
{
	static char *function                    = "libuna_unicode_character_copy_from_utf16";
	libuna_utf16_character_t utf16_surrogate = 0;

	if( unicode_character == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( *utf16_string_index >= utf16_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 string too small.",
		 function );

		return( -1 );
	}
	*unicode_character   = utf16_string[ *utf16_string_index ];
	*utf16_string_index += 1;

	/* Determine if the UTF-16 character is within the high surrogate range
	 */
	if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	 && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_END ) )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: missing surrogate UTF-16 character bytes.",
			 function );

			return( -1 );
		}
		utf16_surrogate      = utf16_string[ *utf16_string_index ];
		*utf16_string_index += 1;

		/* Determine if the UTF-16 character is within the low surrogate range
		 */
		if( ( utf16_surrogate >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( utf16_surrogate <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			*unicode_character  -= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START;
			*unicode_character <<= 10;
			*unicode_character  += utf16_surrogate - LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END;
			*unicode_character  += 0x010000;
		}
		else
		{
			*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
		}
	}
	/* Determine if the Unicode character is valid
	 */
	else if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
	      && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	return( 1 );
}

/* Copies a Unicode character into a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_to_utf16(
                   libuna_unicode_character_t unicode_character,
                   libuna_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   size_t *utf16_string_index,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_to_utf16";

	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( *utf16_string_index >= utf16_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 string too small.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( ( unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	  && ( unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	 || ( unicode_character > LIBUNA_UTF16_CHARACTER_MAX ) )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	if( unicode_character <= LIBUNA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
	{
		utf16_string[ *utf16_string_index ] = (libuna_utf16_character_t) unicode_character;

		*utf16_string_index += 1;
	}
	else
	{
		if( ( *utf16_string_index + 1 ) >= utf16_string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		unicode_character                      -= 0x010000;
		utf16_string[ *utf16_string_index     ] = (libuna_utf16_character_t) ( ( unicode_character >> 10 ) + LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START );
		utf16_string[ *utf16_string_index + 1 ] = (libuna_utf16_character_t) ( ( unicode_character & 0x03ff ) + LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START );

		*utf16_string_index += 2;
	}
	return( 1 );
}

/* Copies a Unicode character from a UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_from_utf16_stream(
                   libuna_unicode_character_t *unicode_character,
                   const uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   size_t *utf16_stream_index,
                   uint8_t byte_order,
                   liberror_error_t **error )
{
	static char *function                    = "libuna_unicode_character_copy_from_utf16_stream";
	libuna_utf16_character_t utf16_surrogate = 0;

	if( unicode_character == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf16_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream index.",
		 function );

		return( -1 );
	}
	if( *utf16_stream_index >= utf16_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 stream too small.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		*unicode_character   = utf16_stream[ *utf16_stream_index ];
		*unicode_character <<= 8;
		*unicode_character  += utf16_stream[ *utf16_stream_index + 1 ];
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		*unicode_character   = utf16_stream[ *utf16_stream_index + 1 ];
		*unicode_character <<= 8;
		*unicode_character  += utf16_stream[ *utf16_stream_index ];
	}
	*utf16_stream_index += 2;

	/* Determine if the UTF-16 character is within the high surrogate range
	 */
	if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	 && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_END ) )
	{
		if( *utf16_stream_index >= utf16_stream_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: missing surrogate UTF-16 character bytes.",
			 function );

			return( -1 );
		}
		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_surrogate   = utf16_stream[ *utf16_stream_index ];
			utf16_surrogate <<= 8;
			utf16_surrogate  += utf16_stream[ *utf16_stream_index + 1 ];
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_surrogate   = utf16_stream[ *utf16_stream_index + 1 ];
			utf16_surrogate <<= 8;
			utf16_surrogate  += utf16_stream[ *utf16_stream_index ];
		}
		*utf16_stream_index += 2;

		/* Determine if the UTF-16 character is within the low surrogate range
		 */
		if( ( utf16_surrogate >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( utf16_surrogate <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			*unicode_character  -= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START;
			*unicode_character <<= 10;
			*unicode_character  += utf16_surrogate - LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END;
			*unicode_character  += 0x010000;
		}
		else
		{
			*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
		}
	}
	/* Determine if the Unicode character is valid
	 */
	else if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
	      && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	return( 1 );
}

/* Copies a Unicode character to an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_to_utf16_stream(
                   libuna_unicode_character_t unicode_character,
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   size_t *utf16_stream_index,
                   uint8_t byte_order,
                   liberror_error_t **error )
{
	static char *function                    = "libuna_unicode_character_copy_to_utf16_stream";
	libuna_utf16_character_t utf16_surrogate = 0;

	if( utf16_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream index.",
		 function );

		return( -1 );
	}
	if( ( *utf16_stream_index + 1 ) >= utf16_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 stream too small.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( ( unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	  && ( unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	 || ( unicode_character > LIBUNA_UTF16_CHARACTER_MAX ) )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	if( unicode_character <= LIBUNA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
	{
		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
			unicode_character                       >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
			unicode_character                       >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		}
		*utf16_stream_index += 2;
	}
	else
	{
		if( ( *utf16_stream_index + 3 ) >= utf16_stream_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 stream too small.",
			 function );

			return( -1 );
		}
		unicode_character -= 0x010000;

		utf16_surrogate = (libuna_utf16_character_t) ( ( unicode_character >> 10 ) + LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START );

		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		*utf16_stream_index += 2;

		utf16_surrogate = (libuna_utf16_character_t) ( ( unicode_character & 0x03ff ) + LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START );

		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		*utf16_stream_index += 2;
	}
	return( 1 );
}

/* Determines the size of a UTF-32 character from a Unicode character
 * Adds the size to the UTF-32 character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_size_to_utf32(
                   libuna_unicode_character_t unicode_character,
                   size_t *utf32_character_size,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_size_to_utf32";

	if( utf32_character_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 character size.",
		 function );

		return( -1 );
	}
	*utf32_character_size += 1;

	return( 1 );
}

/* Copies a Unicode character from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_from_utf32(
                   libuna_unicode_character_t *unicode_character,
                   const libuna_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   size_t *utf32_string_index,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_from_utf32";

	if( unicode_character == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string index.",
		 function );

		return( -1 );
	}
	if( *utf32_string_index >= utf32_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 string too small.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( utf32_string[ *utf32_string_index ] >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
	 && ( utf32_string[ *utf32_string_index ] <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	else
	{
		*unicode_character = utf32_string[ *utf32_string_index ];
	}
	*utf32_string_index += 1;

	return( 1 );
}

/* Copies a Unicode character into a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_to_utf32(
                   libuna_unicode_character_t unicode_character,
                   libuna_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   size_t *utf32_string_index,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_to_utf32";

	if( utf32_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string index.",
		 function );

		return( -1 );
	}
	if( *utf32_string_index >= utf32_string_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 string too small.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( ( unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	  && ( unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	 || ( unicode_character > LIBUNA_UTF32_CHARACTER_MAX ) )
	{
		utf32_string[ *utf32_string_index ] = (libuna_utf32_character_t) LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	else
	{
		utf32_string[ *utf32_string_index ] = (libuna_utf32_character_t) unicode_character;
	}
	*utf32_string_index += 1;

	return( 1 );
}

/* Copies a Unicode character from a UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_from_utf32_stream(
                   libuna_unicode_character_t *unicode_character,
                   const uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   size_t *utf32_stream_index,
                   uint8_t byte_order,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_from_utf32_stream";

	if( unicode_character == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf32_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream.",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream index.",
		 function );

		return( -1 );
	}
	if( *utf32_stream_index >= utf32_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 stream too small.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		*unicode_character   = utf32_stream[ *utf32_stream_index ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index + 1 ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index + 2 ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index + 3 ];
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		*unicode_character   = utf32_stream[ *utf32_stream_index + 3 ];
		*unicode_character <<= 8;
		*unicode_character   = utf32_stream[ *utf32_stream_index + 2 ];
		*unicode_character <<= 8;
		*unicode_character   = utf32_stream[ *utf32_stream_index + 1 ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index ];
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
	 && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	*utf32_stream_index += 4;

	return( 1 );
}

/* Copies a Unicode character to an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_unicode_character_copy_to_utf32_stream(
                   libuna_unicode_character_t unicode_character,
                   uint8_t *utf32_stream,
                   size_t utf32_stream_size,
                   size_t *utf32_stream_index,
                   uint8_t byte_order,
                   liberror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_to_utf32_stream";

	if( utf32_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream.",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_stream_index == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream index.",
		 function );

		return( -1 );
	}
	if( ( *utf32_stream_index + 1 ) >= utf32_stream_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 stream too small.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( ( unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	  && ( unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	 || ( unicode_character > LIBUNA_UTF32_CHARACTER_MAX ) )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		utf32_stream[ *utf32_stream_index + 3 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 2 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		utf32_stream[ *utf32_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 2 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 3 ]   = (uint8_t) ( unicode_character & 0xff );
	}
	*utf32_stream_index += 4;

	return( 1 );
}

