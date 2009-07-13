/*
 * Signal handling functions for the unatools
 *
 * Copyright (c) 2006-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _UNASIGNAL_H )
#define _UNASIGNAL_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( WINAPI )
typedef unsigned long unasignal_t;

BOOL WINAPI unasignal_handler(
             unasignal_t signal );

void unasignal_initialize_memory_debug(
      void );

int unasignal_attach(
     void (*signal_handler)( unasignal_t ) );

int unasignal_detach(
     void );

#elif defined( HAVE_SIGNAL_H )
typedef int unasignal_t;

int unasignal_attach(
     void (*signal_handler)( unasignal_t ) );

int unasignal_detach(
     void );

#else

#error missing signal function
#endif


#if defined( __cplusplus )
}
#endif

#endif

