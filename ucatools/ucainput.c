/*
 * Common input functions for the ucatools
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
#include <notify.h>
#include <system_string.h>

/* If libtool DLL support is enabled set LIBUCA_DLL_IMPORT
 * before including libuca.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBUCA_DLL_IMPORT
#endif

#include <libuca.h>

#include "ucacommon.h"
#include "ucainput.h"

/* Determines the codepage from an argument string
 * Returns 1 if successful or -1 on error
 */
int ucainput_determine_sbc_codepage(
     const system_character_t *argument,
     int *sbc_codepage )
{
	static char *function = "ucainput_determine_sbc_codepage";
	int result            = -1;

	if( argument == NULL )
	{
		notify_warning_printf( "%s: invalid argument string.\n",
		 function );

		return( -1 );
	}
	if( sbc_codepage == NULL )
	{
		notify_warning_printf( "%s: invalid single byte character codepage.\n",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "ascii" ),
	          4 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_ASCII;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1250" ),
	          12 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_WINDOWS_1250;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1251" ),
	          12 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_WINDOWS_1251;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1252" ),
	          12 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_WINDOWS_1252;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1253" ),
	          12 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_WINDOWS_1253;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1254" ),
	          12 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_WINDOWS_1254;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1255" ),
	          12 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_WINDOWS_1255;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1256" ),
	          12 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_WINDOWS_1256;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1257" ),
	          12 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_WINDOWS_1257;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1258" ),
	          12 ) == 0 )
	{
		*sbc_codepage = LIBUCA_CODEPAGE_WINDOWS_1258;
		result        = 1;
	}
	return( result );
}

/* Determines the export format from an argument string
 * Returns 1 if successful or -1 on error
 */
int ucainput_determine_format(
     const system_character_t *argument,
     int *format )
{
	static char *function = "ucainput_determine_format";
	int result            = 1;

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
	     _SYSTEM_CHARACTER_T_STRING( "sbc" ),
	     3 ) == 0 )
	{
		*format = UCACOMMON_FORMAT_SBC;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "utf8" ),
	          4 ) == 0 )
	{
		*format = UCACOMMON_FORMAT_UTF8;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "utf16" ),
	          5 ) == 0 )
	{
		*format = UCACOMMON_FORMAT_UTF16;
		result  = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "utf32" ),
	          5 ) == 0 )
	{
		*format = UCACOMMON_FORMAT_UTF32;
		result  = 1;
	}
	return( result );
}

