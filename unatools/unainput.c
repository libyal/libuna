/*
 * Common input functions for the unatools
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
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#include "unacommon.h"
#include "unainput.h"
#include "unatools_libuna.h"

/* Determines the codepage from a string
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int unainput_determine_byte_stream_codepage(
     const libcstring_system_character_t *string,
     int *byte_stream_codepage,
     liberror_error_t **error )
{
	static char *function = "unainput_determine_byte_stream_codepage";
	size_t string_length  = 0;
	int result            = 0;

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
	if( byte_stream_codepage == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream codepage.",
		 function );

		return( -1 );
	}
	string_length = libcstring_system_string_length(
	                 string );

	if( string_length == 5 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "ascii" ),
		     5 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_ASCII;
			result                = 1;
		}
	}
	if( string_length == 6 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "koi8-r" ),
		     6 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_KOI8_R;
			result                = 1;
		}
		else if( libcstring_system_string_compare(
		          string,
		          _LIBCSTRING_SYSTEM_STRING( "koi8_r" ),
		          6 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_KOI8_R;
			result                = 1;
		}
		else if( libcstring_system_string_compare(
		          string,
		          _LIBCSTRING_SYSTEM_STRING( "koi8-u" ),
		          6 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_KOI8_U;
			result                = 1;
		}
		else if( libcstring_system_string_compare(
		          string,
		          _LIBCSTRING_SYSTEM_STRING( "koi8_u" ),
		          6 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_KOI8_U;
			result                = 1;
		}
	}
	if( ( string_length == 10 )
	 || ( string_length == 11 ) )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "iso" ),
		     3 ) == 0 )
		{
			if( ( string[ 3 ] != '-' )
			 && ( string[ 3 ] != '_' ) )
			{
			}
			else if( libcstring_system_string_compare(
				  &( string[ 4 ] ),
				  _LIBCSTRING_SYSTEM_STRING( "8859" ),
				  4 ) == 0 )
			{
				if( ( string[ 8 ] != '-' )
				 && ( string[ 8 ] != '_' ) )
				{
				}
				else if( string_length == 10 )
				{
					if( libcstring_system_string_compare(
					     &( string[ 9 ] ),
					     _LIBCSTRING_SYSTEM_STRING( "1" ),
					     1 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_1;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "2" ),
						  1 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_2;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "3" ),
						  1 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_3;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "4" ),
						  1 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_4;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "5" ),
						  1 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_5;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "6" ),
						  1 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_6;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "7" ),
						  1 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_7;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "8" ),
						  1 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_8;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "9" ),
						  1 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_9;
						result                = 1;
					}
				}
				else if( string_length == 11 )
				{
					if( libcstring_system_string_compare(
					     &( string[ 9 ] ),
					     _LIBCSTRING_SYSTEM_STRING( "10" ),
					     2 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_10;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "11" ),
						  2 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_11;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "13" ),
						  2 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_13;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "14" ),
						  2 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_14;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "15" ),
						  2 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_15;
						result                = 1;
					}
					else if( libcstring_system_string_compare(
						  &( string[ 9 ] ),
						  _LIBCSTRING_SYSTEM_STRING( "16" ),
						  2 ) == 0 )
					{
						*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_16;
						result                = 1;
					}
				}
			}
		}
	}
	if( ( string_length == 11 )
	 || ( string_length == 12 ) )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "windows" ),
		     7 ) == 0 )
		{
			if( ( string[ 7 ] != '-' )
			 && ( string[ 7 ] != '_' ) )
			{
			}
			else if( string_length == 11 )
			{
				if( libcstring_system_string_compare(
				     &( string[ 8 ] ),
				     _LIBCSTRING_SYSTEM_STRING( "874" ),
				     3 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_874;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
				          &( string[ 8 ] ),
				          _LIBCSTRING_SYSTEM_STRING( "932" ),
				          3 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_932;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
				          &( string[ 8 ] ),
				          _LIBCSTRING_SYSTEM_STRING( "936" ),
				          3 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_936;
					result                = 1;
				}
			}
			else if( string_length == 12 )
			{
				if( libcstring_system_string_compare(
				     &( string[ 8 ] ),
				     _LIBCSTRING_SYSTEM_STRING( "1250" ),
				     4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1250;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
					  &( string[ 8 ] ),
					  _LIBCSTRING_SYSTEM_STRING( "1251" ),
					  4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1251;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
					  &( string[ 8 ] ),
					  _LIBCSTRING_SYSTEM_STRING( "1252" ),
					  4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1252;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
					  &( string[ 8 ] ),
					  _LIBCSTRING_SYSTEM_STRING( "1253" ),
					  4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1253;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
					  &( string[ 8 ] ),
					  _LIBCSTRING_SYSTEM_STRING( "1253" ),
					  4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1253;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
					  &( string[ 8 ] ),
					  _LIBCSTRING_SYSTEM_STRING( "1254" ),
					  4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1254;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
					  &( string[ 8 ] ),
					  _LIBCSTRING_SYSTEM_STRING( "1255" ),
					  4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1255;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
					  &( string[ 8 ] ),
					  _LIBCSTRING_SYSTEM_STRING( "1256" ),
					  4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1256;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
					  &( string[ 8 ] ),
					  _LIBCSTRING_SYSTEM_STRING( "1257" ),
					  4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1257;
					result                = 1;
				}
				else if( libcstring_system_string_compare(
					  &( string[ 8 ] ),
					  _LIBCSTRING_SYSTEM_STRING( "1258" ),
					  4 ) == 0 )
				{
					*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1258;
					result                = 1;
				}
			}
		}
	}
	return( result );
}

/* Determines the encoding from a string
 * Returns 1 if successful or -1 on error
 */
int unainput_determine_encoding(
     const libcstring_system_character_t *string,
     uint8_t *encoding,
     liberror_error_t **error )
{
	static char *function = "unainput_determine_encoding";
	size_t string_length  = 0;
	int result            = -1;

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
	if( encoding == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid encoding.",
		 function );

		return( -1 );
	}
	string_length = libcstring_system_string_length(
	                 string );

	if( string_length == 6 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "base16" ),
		     6 ) == 0 )
		{
			*encoding = UNACOMMON_ENCODING_BASE16;
			result    = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "base32" ),
			  6 ) == 0 )
		{
			*encoding = UNACOMMON_ENCODING_BASE32;
			result    = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "base64" ),
			  6 ) == 0 )
		{
			*encoding = UNACOMMON_ENCODING_BASE64;
			result    = 1;
		}
	}
	else if( string_length == 9 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "base32hex" ),
		     9 ) == 0 )
		{
			*encoding = UNACOMMON_ENCODING_BASE32HEX;
			result    = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "base64url" ),
			  9 ) == 0 )
		{
			*encoding = UNACOMMON_ENCODING_BASE64URL;
			result    = 1;
		}
	}
	return( result );
}

/* Determines the encoding mode from a string
 * Returns 1 if successful or -1 on error
 */
int unainput_determine_encoding_mode(
     const libcstring_system_character_t *string,
     uint8_t *encoding_mode,
     liberror_error_t **error )
{
	static char *function = "unainput_determine_encoding_mode";
	size_t string_length  = 0;
	int result            = -1;

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
	if( encoding_mode == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid encoding mode.",
		 function );

		return( -1 );
	}
	string_length = libcstring_system_string_length(
	                 string );

	if( string_length == 6 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "decode" ),
		     6 ) == 0 )
		{
			*encoding_mode = UNACOMMON_ENCODING_MODE_DECODE;
			result         = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "encode" ),
			  6 ) == 0 )
		{
			*encoding_mode = UNACOMMON_ENCODING_MODE_ENCODE;
			result         = 1;
		}
	}
	return( result );
}

/* Determines the format from a string
 * Returns 1 if successful or -1 on error
 */
int unainput_determine_format(
     const libcstring_system_character_t *string,
     uint8_t *format,
     liberror_error_t **error )
{
	static char *function = "unainput_determine_format";
	size_t string_length  = 0;
	int result            = -1;

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
	if( format == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid format.",
		 function );

		return( -1 );
	}
	string_length = libcstring_system_string_length(
	                 string );

	if( string_length == 4 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "utf7" ),
		     4 ) == 0 )
		{
			*format = UNACOMMON_FORMAT_UTF7;
			result  = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "utf8" ),
			  4 ) == 0 )
		{
			*format = UNACOMMON_FORMAT_UTF8;
			result  = 1;
		}
	}
	else if( string_length == 7 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "utf16be" ),
		     7 ) == 0 )
		{
			*format = UNACOMMON_FORMAT_UTF16BE;
			result  = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "utf16le" ),
			  7 ) == 0 )
		{
			*format = UNACOMMON_FORMAT_UTF16LE;
			result  = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "utf32be" ),
			  7 ) == 0 )
		{
			*format = UNACOMMON_FORMAT_UTF32BE;
			result  = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "utf32le" ),
			  7 ) == 0 )
		{
			*format = UNACOMMON_FORMAT_UTF32LE;
			result  = 1;
		}
	}
	else if( string_length == 11 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "byte-stream" ),
		     11 ) == 0 )
		{
			*format = UNACOMMON_FORMAT_BYTE_STREAM;
			result  = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "byte_stream" ),
			  11 ) == 0 )
		{
			*format = UNACOMMON_FORMAT_BYTE_STREAM;
			result  = 1;
		}
	}
	return( result );
}

/* Determines the newline conversion from a string
 * Returns 1 if successful or -1 on error
 */
int unainput_determine_newline_conversion(
     const libcstring_system_character_t *string,
     uint8_t *newline_conversion,
     liberror_error_t **error )
{
	static char *function = "unainput_determine_newline_conversion";
	size_t string_length  = 0;
	int result            = -1;

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
	if( newline_conversion == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid newline conversion.",
		 function );

		return( -1 );
	}
	string_length = libcstring_system_string_length(
	                 string );

	if( string_length == 2 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "cr" ),
		     2 ) == 0 )
		{
			*newline_conversion = UNACOMMON_NEWLINE_CONVERSION_CR;
			result              = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "lf" ),
			  2 ) == 0 )
		{
			*newline_conversion = UNACOMMON_NEWLINE_CONVERSION_LF;
			result              = 1;
		}
	}
	else if( string_length == 4 )
	{
		if( libcstring_system_string_compare(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "none" ),
		     4 ) == 0 )
		{
			*newline_conversion = UNACOMMON_NEWLINE_CONVERSION_NONE;
			result              = 1;
		}
		else if( libcstring_system_string_compare(
			  string,
			  _LIBCSTRING_SYSTEM_STRING( "crlf" ),
			  4 ) == 0 )
		{
			*newline_conversion = UNACOMMON_NEWLINE_CONVERSION_CRLF;
			result              = 1;
		}
	}
	return( result );
}

