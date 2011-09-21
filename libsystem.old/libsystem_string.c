/*
 * Character string functions
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

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( HAVE_LOCALE_H ) || defined( WINAPI )
#include <locale.h>
#endif

#if defined( HAVE_LANGINFO_H )
#include <langinfo.h>
#endif

#include "libsystem_libuna.h"
#include "libsystem_string.h"

#if defined( libcstring_system_string_to_signed_long_long )

/* Determines the value represented by a string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_to_int64(
     const libcstring_system_character_t *string,
     size_t string_size,
     int64_t *value,
     liberror_error_t **error )
{
	libcstring_system_character_t *end_of_string = NULL;
	static char *function                        = "libcstring_system_string_to_int64";

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid string size is zero.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	end_of_string = (libcstring_system_character_t *) &( string[ string_size - 1 ] );

	errno = 0;

	*value = libcstring_system_string_to_signed_long_long(
	          string,
	          &end_of_string,
	          0 );

	if( errno != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine value.",
		 function );

		return( -1 );
	}
	return( 1 );
}
#endif

#if defined( libcstring_system_string_to_unsigned_long_long )

/* Determines the value represented by a string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_to_uint64(
     const libcstring_system_character_t *string,
     size_t string_size,
     uint64_t *value,
     liberror_error_t **error )
{
	libcstring_system_character_t *end_of_string = NULL;
	static char *function                        = "libsystem_string_to_uint64";

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid string size s zero.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	end_of_string = (libcstring_system_character_t *) &( string[ string_size - 1 ] );

	errno = 0;

	*value = libcstring_system_string_to_unsigned_long_long(
	          string,
	          &end_of_string,
	          0 );

	if( errno != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine value.",
		 function );

		return( -1 );
	}
	return( 1 );
}
#endif

/* Determines the system string size from the UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_size_from_utf8_string(
     const uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *string_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_string_size_from_utf8_string";

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
	if( string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string size.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf32_string_size_from_utf8(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf16_string_size_from_utf8(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     string_size,
	     error ) != 1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine string size.",
		 function );

		return( -1 );
	}
#else
	if( libcstring_narrow_system_string_codepage == 0 )
	{
		*string_size = 1 + libcstring_narrow_string_length(
		                    (char *) utf8_string );
	}
	else if( libuna_byte_stream_size_from_utf8(
	          (libuna_utf8_character_t *) utf8_string,
	          utf8_string_size,
	          libcstring_narrow_system_string_codepage,
	          string_size,
	          error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine string size.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Copies the system string size from the UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_copy_from_utf8_string(
     libcstring_system_character_t *string,
     size_t string_size,
     const uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_string_copy_from_utf8_string";

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf32_string_copy_from_utf8(
	     (libuna_utf32_character_t *) string,
	     string_size,
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf16_string_copy_from_utf8(
	     (libuna_utf16_character_t *) string,
	     string_size,
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     error ) != 1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
#else
	if( libcstring_narrow_system_string_codepage == 0 )
	{
		if( string_size < utf8_string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: string too small.",
			 function );

			return( -1 );
		}
		if( memory_copy(
		     string,
		     utf8_string,
		     utf8_string_size ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to set string.",
			 function );

			return( -1 );
		}
	}
	else if( libuna_byte_stream_copy_from_utf8(
	          (uint8_t *) string,
	          string_size,
	          libcstring_narrow_system_string_codepage,
	          (libuna_utf8_character_t *) utf8_string,
	          utf8_string_size,
	          error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Determines the UTF-8 string size from the system string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_size_to_utf8_string(
     const libcstring_system_character_t *string,
     size_t string_size,
     size_t *utf8_string_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_string_size_to_utf8_string";

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf8_string_size_from_utf32(
	     (libuna_utf32_character_t *) string,
	     string_size,
	     utf8_string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf8_string_size_from_utf16(
	     (libuna_utf16_character_t *) string,
	     string_size,
	     utf8_string_size,
	     error ) != 1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine UTF-8 string size.",
		 function );

		return( -1 );
	}
#else
	if( libcstring_narrow_system_string_codepage == 0 )
	{
		*utf8_string_size = 1 + libcstring_system_string_length(
		                         string );
	}
	else if( libuna_utf8_string_size_from_byte_stream(
	          (uint8_t *) string,
	          string_size,
	          libcstring_narrow_system_string_codepage,
	          utf8_string_size,
	          error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine UTF-8 string size.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Copies the UTF-8 string size from the system string
 * Returns 1 if successful or -1 on error
 */
int libsystem_string_copy_to_utf8_string(
     const libcstring_system_character_t *string,
     size_t string_size,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error )
{
	static char *function = "libsystem_string_copy_to_utf8_string";

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
	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf8_string_copy_from_utf32(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     (libuna_utf32_character_t *) string,
	     string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf8_string_copy_from_utf16(
	     (libuna_utf8_character_t *) utf8_string,
	     utf8_string_size,
	     (libuna_utf16_character_t *) string,
	     string_size,
	     error ) != 1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
#else
	if( libcstring_narrow_system_string_codepage == 0 )
	{
		if( utf8_string_size < string_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string too small.",
			 function );

			return( -1 );
		}
		if( memory_copy(
		     utf8_string,
		     string,
		     string_size ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to set string.",
			 function );

			return( -1 );
		}
	}
	else if( libuna_utf8_string_copy_from_byte_stream(
	          (libuna_utf8_character_t *) utf8_string,
	          utf8_string_size,
	          (uint8_t *) string,
	          string_size,
	          libcstring_narrow_system_string_codepage,
	          error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

