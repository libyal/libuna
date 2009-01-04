/*
 * Signal handling functions for the ucatools
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

#if !defined( _UCASIGNAL_H )
#define _UCASIGNAL_H

#include <common.h>

#if defined( HAVE_WINDOWS_API )
#include <windows.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_SIGNAL_H )
typedef int ucasignal_t;

int ucasignal_attach(
     void (*signal_handler)( ucasignal_t ) );

int ucasignal_detach(
     void );

#elif defined( HAVE_WINDOWS_API )
typedef unsigned long ucasignal_t;

BOOL WINAPI ucasignal_handler(
             ucasignal_t signal );

void ucasignal_initialize_memory_debug(
      void );

int ucasignal_attach(
     void (*signal_handler)( ucasignal_t ) );

int ucasignal_detach(
     void );

#else

#error missing signal function
#endif


#if defined( __cplusplus )
}
#endif

#endif

