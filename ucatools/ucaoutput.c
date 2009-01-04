/*
 * Common output functions for the ucatools
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
#include <character_string.h>

#include <stdio.h>

/* If libtool DLL support is enabled set LIBUCA_DLL_IMPORT
 * before including libuca.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBUCA_DLL_IMPORT
#endif

#include <libuca.h>

#include "ucaoutput.h"

/* Prints the copyright information
 */
void ucaoutput_copyright_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Copyright (c) 2008, Joachim Metz, Hoffmann Investigations <%s> and contributors.\n",
	 PACKAGE_BUGREPORT );
	fprintf( stream, "This is free software; see the source for copying conditions. There is NO\n" );
	fprintf( stream, "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n" );
}

/* Prints the version information
 */
void ucaoutput_version_fprint(
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
        fprintf( stream, "%" PRIs " %" PRIs " (libuca %" PRIs "",
         program, LIBUCA_VERSION_STRING, LIBUCA_VERSION_STRING );

        fprintf( stream, ")\n\n" );
}

