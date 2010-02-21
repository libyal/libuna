/*
 * Signal handling functions
 *
 * Copyright (c) 2010, Joachim Metz <jbmetz@users.sourceforge.net>
 * Copyright (c) 2006-2010, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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

#if !defined( _LIBSYSTEM_SIGNAL_H )
#define _LIBSYSTEM_SIGNAL_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#if defined( HAVE_SIGNAL_H )
#include <signal.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( WINAPI )
typedef unsigned long libsystem_signal_t;

BOOL WINAPI libsystem_signal_handler(
             libsystem_signal_t signal );

#if defined( _MSC_VER )
void libsystem_signal_initialize_memory_debug(
      void );
#endif

int libsystem_signal_attach(
     void (*signal_handler)( libsystem_signal_t ),
     liberror_error_t **error );

int libsystem_signal_detach(
     liberror_error_t **error );

#elif defined( HAVE_SIGNAL_H )
typedef int libsystem_signal_t;

int libsystem_signal_attach(
     void (*signal_handler)( libsystem_signal_t ),
     liberror_error_t **error );

int libsystem_signal_detach(
     liberror_error_t **error );

#else
#error missing signal functions
#endif

#if defined( __cplusplus )
}
#endif

#endif

