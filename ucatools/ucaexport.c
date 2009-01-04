/*
 * Exports Unicode and ASCII (single byte character (SBC)) text
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
#include <memory.h>
#include <notify.h>
#include <system_string.h>
#include <types.h>

#include <errno.h>

#include <stdio.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

/* If libtool DLL support is enabled set LIBUCA_DLL_IMPORT
 * before including libuca.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBUCA_DLL_IMPORT
#endif

#include <libuca.h>

#include "ucacommon.h"
#include "ucainput.h"
#include "ucaoutput.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Usage: ucaexport [ -c codepage ] [ -i input_format ] [ -o output_format ] [ -hvV ] source destination\n\n" );

	fprintf( stream, "\tsource:      the source file\n\n" );
	fprintf( stream, "\tdestination: the destination file\n\n" );

	fprintf( stream, "\t-c:          codepage of single byte character strings (SBC), options: ascii (default), windows-1250, windows-1251,\n" );
	fprintf( stream, "\t             windows-1252, windows-1253, windows-1254, windows-1255, windows-1256, windows-1257 or windows-1258\n" );
	fprintf( stream, "\t-h:          shows this help\n" );
	fprintf( stream, "\t-i:          input format, options: sbc (default), utf8, utf16, utf32\n" );
	fprintf( stream, "\t-o:          output format, options: sbc, utf8 (default), utf16, utf32\n" );
	fprintf( stream, "\t-v:          verbose output to stderr\n" );
	fprintf( stream, "\t-V:          print version\n" );
}

/* The main program
 */
#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	character_t *program            = _CHARACTER_T_STRING( "ucaexport" );
	system_character_t *source      = NULL;
	system_character_t *destination = NULL;
	size_t source_length            = 0;
	size_t destination_length       = 0;
	system_integer_t option         = 0;
	int sbc_codepage                = LIBUCA_CODEPAGE_ASCII;
	int input_format                = UCACOMMON_FORMAT_SBC;
	int output_format               = UCACOMMON_FORMAT_UTF8;
	int verbose                     = 0;

	ucaoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_CHARACTER_T_STRING( "c:hi:o:vV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf( stderr, "Invalid argument: %s\n",
				 argv[ optind ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'c':
				if( ucainput_determine_sbc_codepage(
				     optarg,
				     &sbc_codepage ) != 1 )
				{
					fprintf( stderr, "Unsupported single byte codepage defaulting to ascii.\n" );

					sbc_codepage = LIBUCA_CODEPAGE_ASCII;
				}
				break;

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'i':
				if( ucainput_determine_format(
				     optarg,
				     &input_format ) != 1 )
				{
					fprintf( stderr, "Unsupported input format defaulting to sbc.\n" );

					input_format = UCACOMMON_FORMAT_SBC;
				}
				break;

			case (system_integer_t) 'o':
				if( ucainput_determine_format(
				     optarg,
				     &output_format ) != 1 )
				{
					fprintf( stderr, "Unsupported output format defaulting to utf8.\n" );

					output_format = UCACOMMON_FORMAT_UTF8;
				}
				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				ucaoutput_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf( stderr, "Missing source.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind++ ];

	if( optind == argc )
	{
		fprintf( stderr, "Missing destination.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	destination = argv[ optind++ ];

	/* TODO */

	fprintf( stdout, "Export completed.\n" );

	return( EXIT_SUCCESS );
}

