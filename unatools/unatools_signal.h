/*
 * Signal handling functions
 *
 * Copyright (C) 2008-2025, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _UNATOOLS_SIGNAL_H )
#define _UNATOOLS_SIGNAL_H

#include <common.h>
#include <types.h>

#include "unatools_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_SIGNAL_H ) && !defined( WINAPI )
#error missing signal functions
#endif

#if defined( WINAPI )
typedef unsigned long unatools_signal_t;

#else
typedef int unatools_signal_t;

#endif /* defined( WINAPI ) */

#if defined( WINAPI )

BOOL WINAPI unatools_signal_handler(
             unatools_signal_t signal );

#if defined( _MSC_VER )

void unatools_signal_initialize_memory_debug(
      void );

#endif /* defined( _MSC_VER ) */

#endif /* defined( WINAPI ) */

int unatools_signal_attach(
     void (*signal_handler)( unatools_signal_t ),
     libcerror_error_t **error );

int unatools_signal_detach(
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _UNATOOLS_SIGNAL_H ) */

