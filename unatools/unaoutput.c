/*
 * Common output functions for the unatools
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
#include <memory.h>
#include <types.h>

#include <stdio.h>

/* If libtool DLL support is enabled set LIBUNA_DLL_IMPORT
 * before including libuna.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBUNA_DLL_IMPORT
#endif

#include <libuna.h>

#include "character_string.h"

#include "unaoutput.h"

/* Prints the copyright information
 */
void unaoutput_copyright_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Copyright (c) 2008-2009, Joachim Metz, Hoffmann Investigations <%s> and contributors.\n",
	 PACKAGE_BUGREPORT );
	fprintf( stream, "This is free software; see the source for copying conditions. There is NO\n" );
	fprintf( stream, "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n" );
}

/* Prints the version information
 */
void unaoutput_version_fprint(
      FILE *stream,
      const character_t *program )
{
	if( stream == NULL )
	{
		return;
	}
	if( program == NULL )
	{
		return;
	}
        fprintf( stream, "%" PRIs " %s (libuna %s",
         program, LIBUNA_VERSION_STRING, LIBUNA_VERSION_STRING );

        fprintf( stream, ")\n\n" );
}

/* Prints the codepages information
 */
void unaoutput_codepages_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "\tCodepage:     Description:\n" );
	fprintf( stream, "\tascii:        Support 7-bit ASCII character set\n" );
	fprintf( stream, "\twindows-1250: Supports the Windows 1250 (Central European) character set\n" );
	fprintf( stream, "\twindows-1251: Supports the Windows 1251 (Cyrillic) character set\n" );
	fprintf( stream, "\twindows-1252: Supports the Windows 1250 (Western European/Latin 1)\n" );
	fprintf( stream, "\t              character set\n" );
	fprintf( stream, "\twindows-1253: Supports the Windows 1253 (Greek) character set\n" );
	fprintf( stream, "\twindows-1254: Supports the Windows 1254 (Turkish) character set\n" );
	fprintf( stream, "\twindows-1255: Supports the Windows 1255 (Hebrew) character set\n" );
	fprintf( stream, "\twindows-1256: Supports the Windows 1256 (Arabic) character set\n" );
	fprintf( stream, "\twindows-1257: Supports the Windows 1257 (Baltic) character set\n" );
	fprintf( stream, "\twindows-1258: Supports the Windows 1258 (Vietnamese) character set\n" );
}

