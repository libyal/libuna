/*
 * Common functions for the ucatools
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

#if !defined( _UCACOMMON_H )
#define _UCACOMMON_H

#include <common.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define UCACOMMON_FORMAT_AUTO_DETECT		0
#define UCACOMMON_FORMAT_BYTE_STREAM		1
#define UCACOMMON_FORMAT_UTF8			8
#define UCACOMMON_FORMAT_UTF16BE		16
#define UCACOMMON_FORMAT_UTF16LE		61
#define UCACOMMON_FORMAT_UTF32BE		32
#define UCACOMMON_FORMAT_UTF32LE		23

#define UCACOMMON_NEWLINE_CONVERSION_NONE	0
#define UCACOMMON_NEWLINE_CONVERSION_CR  	1
#define UCACOMMON_NEWLINE_CONVERSION_CRLF	2
#define UCACOMMON_NEWLINE_CONVERSION_LF		3

#if defined( __cplusplus )
}
#endif

#endif

