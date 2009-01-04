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
#include <date_time.h>
#include <memory.h>
#include <types.h>

#include <stdio.h>

/* If libtool DLL support is enabled set LIBUCA_DLL_IMPORT
 * before including libuca.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBUCA_DLL_IMPORT
#endif

#include <libuca.h>

#include "ucabyte_size_string.h"
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

/* Prints a time stamp (with a leading space) to a stream
 */
void ucaoutput_timestamp_fprint(
      FILE *stream,
      time_t timestamp )
{
	struct tm *time_elements = NULL;

	if( stream == NULL )
	{
		return;
	}
	time_elements = date_time_gmtime(
	                 &timestamp );

	if( time_elements != NULL )
	{
		fprintf( stream, " in" );

		if( time_elements->tm_isdst != 0 )
		{
			time_elements->tm_hour -= 1;
			time_elements->tm_isdst = 0;	
		}
		if( time_elements->tm_yday > 0 )
		{
			fprintf(
			 stream,
			 " %i day(s), %i hour(s), %i minute(s) and",
			 time_elements->tm_yday,
			 time_elements->tm_hour,
			 time_elements->tm_min );
		}
		else if( time_elements->tm_hour > 0 )
		{
			fprintf(
			 stream,
			 " %i hour(s), %i minute(s) and",
			 time_elements->tm_hour,
			 time_elements->tm_min );
		}
		else if( time_elements->tm_min > 0 )
		{
			fprintf(
			 stream,
			 " %i minute(s) and",
			 time_elements->tm_min );
		}
		fprintf(
		 stream,
		 " %i second(s)",
		 time_elements->tm_sec );

		memory_free(
		 time_elements );
	}
}

/* Prints the amount of bytes per second (with a leading space) to a stream
 */
void ucaoutput_bytes_per_second_fprint(
      FILE *stream,
      size64_t bytes,
      time_t seconds )
{
	character_t bytes_per_second_string[ 16 ];

	size64_t bytes_per_second = 0;
	int result                = 0;

	if( stream == NULL )
	{
		return;
	}
	if( seconds > 0 )
	{
		bytes_per_second = bytes / seconds;

		if( bytes_per_second > 1024 )
		{
			result = ucabyte_size_string_create(
			          bytes_per_second_string,
			          10,
			          bytes_per_second,
			          UCABYTE_SIZE_STRING_UNIT_MEBIBYTE );
		}
		fprintf(
		 stream,
		 " with" );

		if( result == 1 )
		{
			fprintf(
			 stream,
			 " %" PRIs "/s (%" PRIu64 " bytes/second)",
			 bytes_per_second_string, bytes_per_second );
		}
		else
		{
			fprintf(
			 stream,
			 " %" PRIu64 " bytes/second",
			 bytes_per_second );
		}
	}
}

/* Prints the amount of bytes (with a leading space) to a stream
 * Creates a human readable version of the amount of bytes if possible
 */
void ucaoutput_bytes_fprint(
      FILE *stream,
      size64_t bytes )
{
	character_t bytes_string[ 16 ];

	int result = 0;

	if( stream == NULL )
	{
		return;
	}
	if( bytes > 1024 )
	{
		result = ucabyte_size_string_create(
		          bytes_string,
		          10,
		          bytes,
		          UCABYTE_SIZE_STRING_UNIT_MEBIBYTE );
	}
	if( result == 1 )
	{
		fprintf(
		 stream,
		 " %" PRIs " (%" PRIi64 " bytes)",
		 bytes_string, bytes );
	}
	else
	{
		fprintf(
		 stream,
		 " %" PRIi64 " bytes",
		 bytes );
	}
}

/* Prints the codepages information
 */
void ucaoutput_codepages_fprint(
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

