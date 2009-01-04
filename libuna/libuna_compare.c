/*
 * Compare functions
 *
 * Copyright (c) 2008, Joachim Metz <forensics@hoffmannbv.nl>,
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

#include "libuna_compare.h"
#include "libuna_error.h"
#include "libuna_unicode_character.h"
#include "libuna_types.h"

/* Compares an UTF-8 string with an UTF-16 string
 * Returns 1 if the strings are equal, 0 if not or -1 on error
 */
int libuna_compare_utf8_with_utf16(
     libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     libuna_error_t **error )
{
	static char *function                              = "libuna_compare_utf8_with_utf16";
	size_t utf8_string_iterator                        = 0;
	size_t utf16_string_iterator                       = 0;
	libuna_unicode_character_t utf8_unicode_character  = 0;
	libuna_unicode_character_t utf16_unicode_character = 0;

	if( utf8_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-8 string.\n",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 string.\n",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	while( ( utf8_string_iterator < utf8_string_size )
	    && ( utf16_string_iterator < utf16_string_size ) )
	{
		/* Convert the UTF-8 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &utf8_unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_iterator,
		     error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-8.\n",
			 function );

			return( -1 );
		}
		/* Convert the UTF-16 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &utf16_unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_iterator,
                     error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16.\n",
			 function );

			return( -1 );
		}
		if( utf8_unicode_character != utf16_unicode_character )
		{
			break;
		}
	}
	/* Check if both strings were entirely processed
	 */
	if( ( utf8_string_iterator != utf8_string_size )
	 || ( utf16_string_iterator != utf16_string_size ) )
	{
		return( 0 );
	}
	return( 1 );
}

/* Compares an UTF-8 string with an UTF-32 string
 * Returns 1 if the strings are equal, 0 if not or -1 on error
 */
int libuna_compare_utf8_with_utf32(
     libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     libuna_error_t **error )
{
	static char *function                              = "libuna_compare_utf8_with_utf32";
	size_t utf8_string_iterator                        = 0;
	size_t utf32_string_iterator                       = 0;
	libuna_unicode_character_t utf8_unicode_character  = 0;
	libuna_unicode_character_t utf32_unicode_character = 0;

	if( utf8_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-8 string.\n",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-32 string.\n",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	while( ( utf8_string_iterator < utf8_string_size )
	    && ( utf32_string_iterator < utf32_string_size ) )
	{
		/* Convert the UTF-8 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &utf8_unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_iterator,
		     error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-8.\n",
			 function );

			return( -1 );
		}
		/* Convert the UTF-32 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &utf32_unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_iterator,
                     error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-32.\n",
			 function );

			return( -1 );
		}
		if( utf8_unicode_character != utf32_unicode_character )
		{
			break;
		}
	}
	/* Check if both strings were entirely processed
	 */
	if( ( utf8_string_iterator != utf8_string_size )
	 || ( utf32_string_iterator != utf32_string_size ) )
	{
		return( 0 );
	}
	return( 1 );
}

/* Compares an UTF-16 string with an UTF-32 string
 * Returns 1 if the strings are equal, 0 if not or -1 on error
 */
int libuna_compare_utf16_with_utf32(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     libuna_error_t **error )
{
	static char *function                              = "libuna_compare_utf16_with_utf32";
	size_t utf16_string_iterator                       = 0;
	size_t utf32_string_iterator                       = 0;
	libuna_unicode_character_t utf16_unicode_character = 0;
	libuna_unicode_character_t utf32_unicode_character = 0;

	if( utf16_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 string.\n",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-32 string.\n",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	while( ( utf16_string_iterator < utf16_string_size )
	    && ( utf32_string_iterator < utf32_string_size ) )
	{
		/* Convert the UTF-16 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16(
		     &utf16_unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_iterator,
		     error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16.\n",
			 function );

			return( -1 );
		}
		/* Convert the UTF-32 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &utf32_unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_iterator,
                     error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-32.\n",
			 function );

			return( -1 );
		}
		if( utf16_unicode_character != utf32_unicode_character )
		{
			break;
		}
	}
	/* Check if both strings were entirely processed
	 */
	if( ( utf16_string_iterator != utf16_string_size )
	 || ( utf32_string_iterator != utf32_string_size ) )
	{
		return( 0 );
	}
	return( 1 );
}

