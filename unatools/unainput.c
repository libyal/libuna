/*
 * Common input functions for the unatools
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

/* If libtool DLL support is enabled set LIBUNA_DLL_IMPORT
 * before including libuna.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBUNA_DLL_IMPORT
#endif

#include <libuna.h>

#include "notify.h"
#include "system_string.h"
#include "unacommon.h"
#include "unainput.h"

/* Determines the codepage from an argument string
 * Returns 1 if successful or -1 on error
 */
int unainput_determine_byte_stream_codepage(
     const system_character_t *argument,
     int *byte_stream_codepage )
{
	static char *function = "unainput_determine_byte_stream_codepage";
	int result            = -1;

	if( argument == NULL )
	{
		notify_warning_printf( "%s: invalid argument string.\n",
		 function );

		return( -1 );
	}
	if( byte_stream_codepage == NULL )
	{
		notify_warning_printf( "%s: invalid byte stream codepage.\n",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "ascii" ),
	     5 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_ASCII;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "iso" ),
	          3 ) == 0 )
	{
		if( ( argument[ 3 ] != '-' )
		 && ( argument[ 3 ] != '_' ) )
		{
		}
		else if( system_string_compare(
		          &( argument[ 4 ] ),
		          _SYSTEM_CHARACTER_T_STRING( "8859" ),
		          4 ) == 0 )
		{
			if( ( argument[ 8 ] != '-' )
			 && ( argument[ 8 ] != '_' ) )
			{
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "10" ),
				  2 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_10;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "11" ),
				  2 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_11;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "13" ),
				  2 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_13;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "14" ),
				  2 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_14;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "15" ),
				  2 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_15;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "16" ),
				  2 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_16;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "1" ),
				  1 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_1;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "2" ),
				  1 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_2;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "3" ),
				  1 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_3;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "4" ),
				  1 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_4;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "5" ),
				  1 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_5;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "6" ),
				  1 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_6;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "7" ),
				  1 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_7;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "8" ),
				  1 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_8;
				result                = 1;
			}
			else if( system_string_compare(
				  &( argument[ 9 ] ),
				  _SYSTEM_CHARACTER_T_STRING( "9" ),
				  1 ) == 0 )
			{
				*byte_stream_codepage = LIBUNA_CODEPAGE_ISO_8859_9;
				result                = 1;
			}
		}
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows" ),
	          7 ) == 0 )
	{
		if( ( argument[ 7 ] != '-' )
		 && ( argument[ 7 ] != '_' ) )
		{
		}
		else if( system_string_compare(
		          &( argument[ 8 ] ),
		          _SYSTEM_CHARACTER_T_STRING( "1250" ),
		          4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1250;
			result                = 1;
		}
		else if( system_string_compare(
			  &( argument[ 8 ] ),
			  _SYSTEM_CHARACTER_T_STRING( "1251" ),
			  4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1251;
			result                = 1;
		}
		else if( system_string_compare(
			  &( argument[ 8 ] ),
			  _SYSTEM_CHARACTER_T_STRING( "1252" ),
			  4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1252;
			result                = 1;
		}
		else if( system_string_compare(
			  &( argument[ 8 ] ),
			  _SYSTEM_CHARACTER_T_STRING( "1253" ),
			  4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1253;
			result                = 1;
		}
		else if( system_string_compare(
			  &( argument[ 8 ] ),
			  _SYSTEM_CHARACTER_T_STRING( "1253" ),
			  4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1253;
			result                = 1;
		}
		else if( system_string_compare(
			  &( argument[ 8 ] ),
			  _SYSTEM_CHARACTER_T_STRING( "1254" ),
			  4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1254;
			result                = 1;
		}
		else if( system_string_compare(
			  &( argument[ 8 ] ),
			  _SYSTEM_CHARACTER_T_STRING( "1255" ),
			  4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1255;
			result                = 1;
		}
		else if( system_string_compare(
			  &( argument[ 8 ] ),
			  _SYSTEM_CHARACTER_T_STRING( "1256" ),
			  4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1256;
			result                = 1;
		}
		else if( system_string_compare(
			  &( argument[ 8 ] ),
			  _SYSTEM_CHARACTER_T_STRING( "1257" ),
			  4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1257;
			result                = 1;
		}
		else if( system_string_compare(
			  &( argument[ 8 ] ),
			  _SYSTEM_CHARACTER_T_STRING( "1258" ),
			  4 ) == 0 )
		{
			*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1258;
			result                = 1;
		}
	}
	return( result );
}

/* Determines the encoding from an argument string
 * Returns 1 if successful or -1 on error
 */
int unainput_determine_encoding(
     const system_character_t *argument,
     int *encoding )
{
	static char *function = "unainput_determine_encoding";
	int result            = -1;

	if( argument == NULL )
	{
		notify_warning_printf( "%s: invalid argument string.\n",
		 function );

		return( -1 );
	}
	if( encoding == NULL )
	{
		notify_warning_printf( "%s: invalid encoding.\n",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "base16" ),
	     6 ) == 0 )
	{
		*encoding = UNACOMMON_ENCODING_BASE16;
		result    = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "base32" ),
	          6 ) == 0 )
	{
		*encoding = UNACOMMON_ENCODING_BASE32;
		result    = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "base32hex" ),
	          9 ) == 0 )
	{
		*encoding = UNACOMMON_ENCODING_BASE32HEX;
		result    = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "base64" ),
	          6 ) == 0 )
	{
		*encoding = UNACOMMON_ENCODING_BASE64;
		result    = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "base64url" ),
	          9 ) == 0 )
	{
		*encoding = UNACOMMON_ENCODING_BASE64URL;
		result    = 1;
	}
	return( result );
}

/* Determines the format from an argument string
 * Returns 1 if successful or -1 on error
 */
int unainput_determine_format(
     const system_character_t *argument,
     int *format )
{
	static char *function = "unainput_determine_format";
	int result            = -1;

	if( argument == NULL )
	{
		notify_warning_printf( "%s: invalid argument string.\n",
		 function );

		return( -1 );
	}
	if( format == NULL )
	{
		notify_warning_printf( "%s: invalid format.\n",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "byte-stream" ),
	     11 ) == 0 )
	{
		*format = UNACOMMON_FORMAT_BYTE_STREAM;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "byte_stream" ),
	          11 ) == 0 )
	{
		*format = UNACOMMON_FORMAT_BYTE_STREAM;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "utf7" ),
	          4 ) == 0 )
	{
		*format = UNACOMMON_FORMAT_UTF7;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "utf8" ),
	          4 ) == 0 )
	{
		*format = UNACOMMON_FORMAT_UTF8;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "utf16be" ),
	          7 ) == 0 )
	{
		*format = UNACOMMON_FORMAT_UTF16BE;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "utf16le" ),
	          7 ) == 0 )
	{
		*format = UNACOMMON_FORMAT_UTF16LE;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "utf32be" ),
	          7 ) == 0 )
	{
		*format = UNACOMMON_FORMAT_UTF32BE;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "utf32le" ),
	          7 ) == 0 )
	{
		*format = UNACOMMON_FORMAT_UTF32LE;
		result  = 1;
	}
	return( result );
}

/* Determines the newline conversion from an argument string
 * Returns 1 if successful or -1 on error
 */
int unainput_determine_newline_conversion(
     const system_character_t *argument,
     int *newline_conversion )
{
	static char *function = "unainput_determine_newline_conversion";
	int result            = -1;

	if( argument == NULL )
	{
		notify_warning_printf( "%s: invalid argument string.\n",
		 function );

		return( -1 );
	}
	if( newline_conversion == NULL )
	{
		notify_warning_printf( "%s: invalid newline conversion.\n",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "none" ),
	     4 ) == 0 )
	{
		*newline_conversion = UNACOMMON_NEWLINE_CONVERSION_NONE;
		result              = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "crlf" ),
	          4 ) == 0 )
	{
		*newline_conversion = UNACOMMON_NEWLINE_CONVERSION_CRLF;
		result              = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "cr" ),
	          2 ) == 0 )
	{
		*newline_conversion = UNACOMMON_NEWLINE_CONVERSION_CR;
		result              = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "lf" ),
	          2 ) == 0 )
	{
		*newline_conversion = UNACOMMON_NEWLINE_CONVERSION_LF;
		result              = 1;
	}
	return( result );
}

