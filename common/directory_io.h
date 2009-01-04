/*
 * Directory IO functions
 *
 * Copyright (c) 2006-2008, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _DIRECTORY_IO_H )
#define _DIRECTORY_IO_H

#include "common.h"
#include "narrow_string.h"
#include "types.h"
#include "wide_string.h"

#if defined( HAVE_SYS_STAT_H )
#include <sys/stat.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_MKDIR )
#if defined( HAVE_WINDOWS_API )
#define directory_io_make( pathname ) \
	_mkdir( pathname )

#else
#define directory_io_make( pathname ) \
	mkdir( pathname, 0755 )
#endif
#endif

#if defined( HAVE_WMKDIR )
#if defined( HAVE_WINDOWS_API )
#define directory_io_wmake( pathname ) \
	_wmkdir( pathname )

#endif
#endif

#if defined( __cplusplus )
}
#endif

#endif

