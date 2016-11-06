/*
 * Common output functions for the unatools
 *
 * Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#include "unacommon.h"
#include "unaoutput.h"
#include "unatools_libcerror.h"
#include "unatools_libcsystem.h"
#include "unatools_libuna.h"

/* Prints the copyright information
 */
void unaoutput_copyright_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf(
	 stream,
	 "Copyright (C) 2008-2016, Joachim Metz <%s>.\n"
	 "This is free software; see the source for copying conditions. There is NO\n"
	 "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n",
	 PACKAGE_BUGREPORT );
}

/* Prints the version information
 */
void unaoutput_version_fprint(
      FILE *stream,
      const char *program )
{
	if( stream == NULL )
	{
		return;
	}
	if( program == NULL )
	{
		return;
	}
        fprintf(
	 stream,
	 "%s %s (libuna %s)\n\n",
         program,
	 LIBUNA_VERSION_STRING,
	 LIBUNA_VERSION_STRING );
}

/* Prints the codepage information
 */
void unaoutput_codepage_fprint(
      FILE *stream,
      int codepage )
{
	if( stream == NULL )
	{
		return;
	}
	switch( codepage )
	{
		case LIBUNA_CODEPAGE_ASCII:
			fprintf(
			 stream,
			 "ASCII (US-ASCII)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_1:
			fprintf(
			 stream,
			 "ISO 8859-1 (Western European)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_2:
			fprintf(
			 stream,
			 "ISO 8859-2 (Central European)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_3:
			fprintf(
			 stream,
			 "ISO 8859-3 (South European)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_4:
			fprintf(
			 stream,
			 "ISO 8859-4 (North European)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_5:
			fprintf(
			 stream,
			 "ISO 8859-5 (Cyrillic)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_6:
			fprintf(
			 stream,
			 "ISO 8859-6 (Arabic)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_7:
			fprintf(
			 stream,
			 "ISO 8859-7 (Greek)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_8:
			fprintf(
			 stream,
			 "ISO 8859-8 (Hebrew)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_9:
			fprintf(
			 stream,
			 "ISO 8859-9 (Turkish)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_10:
			fprintf(
			 stream,
			 "ISO 8859-10 (Nordic)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_11:
			fprintf(
			 stream,
			 "ISO 8859-11 (Thai)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_13:
			fprintf(
			 stream,
			 "ISO 8859-13 (Baltic)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_14:
			fprintf(
			 stream,
			 "ISO 8859-14 (Celtic)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_15:
			fprintf(
			 stream,
			 "ISO 8859-15 (Latin-9)" );
			break;

		case LIBUNA_CODEPAGE_ISO_8859_16:
			fprintf(
			 stream,
			 "ISO 8859-16 (Latin-10)" );
			break;

		case LIBUNA_CODEPAGE_KOI8_R:
			fprintf(
			 stream,
			 "koi8-r (Russian)" );
			break;

		case LIBUNA_CODEPAGE_KOI8_U:
			fprintf(
			 stream,
			 "koi8-u (Ukrainian)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_874:
			fprintf(
			 stream,
			 "Windows 874 (Thai)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_932:
			fprintf(
			 stream,
			 "Windows 932 (Japanese)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_936:
			fprintf(
			 stream,
			 "Windows 936 (Simplified Chinese GBK)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1250:
			fprintf(
			 stream,
			 "Windows 1250 (Central European)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1251:
			fprintf(
			 stream,
			 "Windows 1251 (Cyrillic)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1252:
			fprintf(
			 stream,
			 "Windows 1252 (Western European/Latin 1)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1253:
			fprintf(
			 stream,
			 "Windows 1253 (Greek)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1254:
			fprintf(
			 stream,
			 "Windows 1254 (Turkish)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1255:
			fprintf(
			 stream,
			 "Windows 1255 (Hebrew)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1256:
			fprintf(
			 stream,
			 "Windows 1256 (Arabic)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1257:
			fprintf(
			 stream,
			 "Windows 1257 (Baltic)" );
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1258:
			fprintf(
			 stream,
			 "Windows 1258 (Vietnamese)" );
			break;

		default:
			fprintf(
			 stream,
			 "unsupported" );
			break;
	}
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
	fprintf(
	 stream,
	 "\tCodepage:     Description:\n"
	 "\tascii:        Support 7-bit ASCII (US-ASCII) character set\n"
	 "\tiso-8859-1:   Support ISO 8859-1 (Western European) character set\n"
	 "\tiso-8859-2:   Support ISO 8859-2 (Central European) character set\n"
	 "\tiso-8859-3:   Support ISO 8859-3 (South European) character set\n"
	 "\tiso-8859-4:   Support ISO 8859-4 (North European) character set\n"
	 "\tiso-8859-5:   Support ISO 8859-5 (Cyrillic) character set\n"
	 "\tiso-8859-6:   Support ISO 8859-6 (Arabic) character set\n"
	 "\tiso-8859-7:   Support ISO 8859-7 (Greek) character set\n"
	 "\tiso-8859-8:   Support ISO 8859-8 (Hebrew) character set\n"
	 "\tiso-8859-9:   Support ISO 8859-9 (Turkish) character set\n"
	 "\tiso-8859-10:  Support ISO 8859-10 (Nordic) character set\n"
	 "\tiso-8859-11:  Support ISO 8859-11 (Thai) character set\n"
	 "\tiso-8859-13:  Support ISO 8859-13 (Baltic) character set\n"
	 "\tiso-8859-14:  Support ISO 8859-14 (Celtic) character set\n"
	 "\tiso-8859-15:  Support ISO 8859-14 (Latin-9) character set\n"
	 "\tiso-8859-16:  Support ISO 8859-16 (Latin-10) character set\n"
	 "\tkoi8-r:       Support KOI8-R (Russian) character set\n"
	 "\tkoi8-u:       Support KOI8-U (Ukrainian) character set\n"
	 "\twindows-874:  Supports the Windows 874 (Thai) character set\n"
	 "\twindows-1250: Supports the Windows 1250 (Central European) character set\n"
	 "\twindows-1251: Supports the Windows 1251 (Cyrillic) character set\n"
	 "\twindows-1252: Supports the Windows 1250 (Western European/Latin 1)\n"
	 "\t              character set\n"
	 "\twindows-1253: Supports the Windows 1253 (Greek) character set\n"
	 "\twindows-1254: Supports the Windows 1254 (Turkish) character set\n"
	 "\twindows-1255: Supports the Windows 1255 (Hebrew) character set\n"
	 "\twindows-1256: Supports the Windows 1256 (Arabic) character set\n"
	 "\twindows-1257: Supports the Windows 1257 (Baltic) character set\n"
	 "\twindows-1258: Supports the Windows 1258 (Vietnamese) character set\n" );
}

/* Prints the format (encoding) information
 */
void unaoutput_format_fprint(
      FILE *stream,
      int format )
{
	if( stream == NULL )
	{
		return;
	}
	switch( format )
	{
		case UNACOMMON_FORMAT_AUTO_DETECT:
			fprintf(
			 stream,
			 "auto detect" );
			break;

		case UNACOMMON_FORMAT_BYTE_STREAM:
			fprintf(
			 stream,
			 "byte stream" );
			break;

		case UNACOMMON_FORMAT_UTF7:
			fprintf(
			 stream,
			 "UTF-7" );
			break;

		case UNACOMMON_FORMAT_UTF8:
			fprintf(
			 stream,
			 "UTF-8" );
			break;

		case UNACOMMON_FORMAT_UTF16BE:
			fprintf(
			 stream,
			 "UTF-16 big endian" );
			break;

		case UNACOMMON_FORMAT_UTF16LE:
			fprintf(
			 stream,
			 "UTF-16 little endian" );
			break;

		case UNACOMMON_FORMAT_UTF32BE:
			fprintf(
			 stream,
			 "UTF-32 big endian" );
			break;

		case UNACOMMON_FORMAT_UTF32LE:
			fprintf(
			 stream,
			 "UTF-32 little endian" );
			break;

		default:
			fprintf(
			 stream,
			 "unsupported" );
			break;
	}
}

