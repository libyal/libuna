/*
 * Common input functions for the unatools
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
	          4 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_ASCII;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1250" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1250;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1250" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1250;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1251" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1251;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1251" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1251;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1252" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1252;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1252" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1252;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1253" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1253;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1253" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1253;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1254" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1254;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1254" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1254;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1255" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1255;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1255" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1255;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1256" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1256;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1256" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1256;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1257" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1257;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1257" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1257;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1258" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1258;
		result                = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1258" ),
	          12 ) == 0 )
	{
		*byte_stream_codepage = LIBUNA_CODEPAGE_WINDOWS_1258;
		result                = 1;
	}
	return( result );
}

/* Determines the export format from an argument string
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

