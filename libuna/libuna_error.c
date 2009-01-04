/*
 * Error functions
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
#include <notify.h>

#if defined( HAVE_STDARG_H )
#include <stdarg.h>
#elif defined( HAVE_VARARGS_H )
#include <varargs.h>
#else
#error Missing headers stdarg.h and varargs.h
#endif

#include "libuna_definitions.h"
#include "libuna_error.h"

#if defined( HAVE_STDARG_H )
#define VARARGS( function, error, error_code, type, argument ) \
        function( type argument, ... )
#define VASTART( argument_list, type, name ) \
        va_start( argument_list, name )
#define VAEND( argument_list ) \
        va_end( argument_list )

#elif defined( HAVE_VARARGS_H )
#define VARARGS( function, error, error_code, type, argument ) \
        function( va_alist ) va_dcl
#define VASTART( argument_list, type, name ) \
        { type name; va_start( argument_list ); name = va_arg( argument_list, type )
#define VAEND( argument_list ) \
        va_end( argument_list ); }

#endif

/* Set an error initializes the error structure with the error code if necessary
 * Otherwise it will just append the error message for back tracing
 */
void VARARGS(
      libuna_error_set,
      libuna_error_t **error,
      int error_code,
      char *,
      format )
{
	if( error == NULL )
	{
		return;
	}
	if( *error == NULL )
	{
		*error = (libuna_error_t *) memory_allocate(
		                             sizeof( libuna_internal_error_t ) );

		if( *error == NULL )
		{
			return;
		}
		( (libuna_internal_error_t *) *error )->code               = error_code;
		( (libuna_internal_error_t *) *error )->amount_of_messages = 0;
		( (libuna_internal_error_t *) *error )->message            = NULL;

	}
	VASTART(
	 argument_list,
	 char *,
	 format );

	libuna_error_add_message(
	 error,
	 format,
	 argument_list );

	VAEND(
	 argument_list );
}

#undef VARARGS
#undef VASTART
#undef VAEND

#if defined( HAVE_STDARG_H )
#define VARARGS( function, error, type, argument ) \
        function( type argument, ... )
#define VASTART( argument_list, type, name ) \
        va_start( argument_list, name )
#define VAEND( argument_list ) \
        va_end( argument_list )

#elif defined( HAVE_VARARGS_H )
#define VARARGS( function, error, type, argument ) \
        function( va_alist ) va_dcl
#define VASTART( argument_list, type, name ) \
        { type name; va_start( argument_list ); name = va_arg( argument_list, type )
#define VAEND( argument_list ) \
        va_end( argument_list ); }

#endif

/* Adds a message to an error structure
 */
void VARARGS(
      libuna_error_add_message,
      libuna_error_t *error,
      char *,
      format )
{
	void *reallocation  = NULL;
	size_t message_size = 64;
	int print_count     = 0;

	if( error == NULL )
	{
		return;
	}
	reallocation = memory_reallocate(
	                ( (libuna_internal_error_t *) error )->message,
	                sizeof( char * ) * ( ( (libuna_internal_error_t *) error )->amount_of_messages + 1 ) );

	if( reallocation == NULL )
	{
		return;
	}
	( (libuna_internal_error_t *) error )->amount_of_messages += 1;
	( (libuna_internal_error_t *) error )->message             = (char **) reallocation;

	VASTART(
	 argument_list,
	 char *,
	 format );

	do
	{
		reallocation = memory_reallocate(
		                ( (libuna_internal_error_t *) error )->message[ ( (libuna_internal_error_t *) error )->amount_of_messages - 1 ],
		                sizeof( char ) * message_size );

		if( reallocation == NULL )
		{
			memory_free(
			 ( (libuna_internal_error_t *) error )->message[ ( (libuna_internal_error_t *) error )->amount_of_messages - 1 ] );

			( (libuna_internal_error_t *) error )->message[ ( (libuna_internal_error_t *) error )->amount_of_messages - 1 ] = NULL;
		}
		( (libuna_internal_error_t *) error )->message[ ( (libuna_internal_error_t *) error )->amount_of_messages - 1 ] = reallocation;

		print_count = vsnprintf(
		               ( (libuna_internal_error_t *) error )->message[ ( (libuna_internal_error_t *) error )->amount_of_messages - 1 ],
		               message_size,
		               format,
		               argument_list );

		if( ( print_count > -1 )
		 && ( (size_t) print_count > message_size ) )
		{
			message_size = (size_t) ( print_count + 1 );
		}
		else if( print_count <= -1 )
		{
			message_size += 64;
		}
	}
	while( ( print_count <= -1 )
	 || ( (size_t) print_count > message_size ) );

	VAEND(
	 argument_list );
}

#undef VARARGS
#undef VASTART
#undef VAEND

/* Free an error structure and its elements
 */
void libuna_error_free(
      libuna_error_t **error )
{
	int message_iterator = 0;

	if( error == NULL )
	{
		return;
	}
	if( *error != NULL )
	{
		for( message_iterator = 0; message_iterator < ( (libuna_internal_error_t *) error )->amount_of_messages; message_iterator++ )
		{
			if( ( (libuna_internal_error_t *) error )->message[ message_iterator ] != NULL )
			{
				memory_free(
				 ( (libuna_internal_error_t *) error )->message[ message_iterator ] );
			}
		}
		memory_free(
		 ( (libuna_internal_error_t *) error )->message );
		memory_free(
		 *error );

		*error = NULL;
	}
}

