/*
 * Notification library
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

#include <common.h>
#include <file_stream.h>
#include <memory.h>

#include <liberror.h>

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( HAVE_STDARG_H ) || defined( WINAPI )
#include <stdarg.h>
#elif defined( HAVE_VARARGS_H )
#include <varargs.h>
#else
#error Missing headers stdarg.h and varargs.h
#endif

#include "libsystem_notify.h"

/* The notification stream
 */
FILE *libsystem_notify_stream = NULL;

/* Value to indicate if the notification stream
 * was opened by the library
 */
int libsystem_notify_stream_opened_in_library = 0;

/* Value to indicate if the verbose notification
 * is active
 */
int libsystem_notify_verbose = 0;

/* Set the verbose
 */
void libsystem_notify_set_verbose(
      int verbose )
{
	libsystem_notify_verbose = verbose;
}

/* Set the stream
 * Returns 1 if successful or -1 on error
 */
int libsystem_notify_set_stream(
     FILE *stream,
     liberror_error_t **error )
{
	static char *function = "libsystem_notify_set_stream";

	if( ( libsystem_notify_stream_opened_in_library != 0 )
	 && ( libsystem_notify_stream_close(
	       error ) != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to close notify stream.",
		 function );

		return( -1 );
	}
	libsystem_notify_stream = stream;

	return( 1 );
}

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
int libsystem_notify_stream_open(
     const char *filename,
     liberror_error_t **error )
{
	static char *function = "libsystem_notify_stream_open";

	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( libsystem_notify_stream_opened_in_library != 0 )
	 && ( libsystem_notify_stream_close(
	       error ) != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to close notify stream.",
		 function );

		return( -1 );
	}
	libsystem_notify_stream = file_stream_open(
	                    filename,
	                    FILE_STREAM_OPEN_APPEND );
	
	if( libsystem_notify_stream == NULL )
	{
		switch( errno )
		{
			case EACCES:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %s.",
				 function,
				 filename );

				break;

			case ENOENT:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %s.",
				 function,
				 filename );

				break;

			default:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_OPEN_FAILED,
				 "%s: unable to open file: %s.",
				 function,
				 filename );

				break;
		}
		return( -1 );
	}
	libsystem_notify_stream_opened_in_library = 1;

	return( 1 );
}

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
int libsystem_notify_stream_close(
     liberror_error_t **error )
{
	static char *function = "libsystem_notify_stream_close";

	if( libsystem_notify_stream_opened_in_library != 0 )
	{
		if( file_stream_close(
		     libsystem_notify_stream ) != 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to close stream.",
			 function );

			return( -1 );
		}
		libsystem_notify_stream                   = NULL;
		libsystem_notify_stream_opened_in_library = 0;
	}
	return( 0 );
}

#if defined( HAVE_STDARG_H ) || defined( WINAPI )
#define VARARGS( function, type, argument ) \
	function( type argument, ... )
#define VASTART( argument_list, type, name ) \
	va_start( argument_list, name )
#define VAEND( argument_list ) \
	va_end( argument_list )

#elif defined( HAVE_VARARGS_H )
#define VARARGS( function, type, argument ) \
	function( va_alist ) va_dcl
#define VASTART( argument_list, type, name ) \
	{ type name; va_start( argument_list ); name = va_arg( argument_list, type )
#define VAEND( argument_list ) \
	va_end( argument_list ); }

#endif

/* Print a formatted string on the notify stream
 * Returns the amount of printed characters if successful or -1 on error
 */
int VARARGS(
     libsystem_notify_printf,
     const char *,
     format )
{
	va_list argument_list;

	int print_count = 0;

	if( libsystem_notify_stream == NULL )
	{
		return( 0 );
	}
	VASTART(
	 argument_list,
	 char *,
	 format );

#if defined( HAVE_GLIB_H )
	g_logv(
	 G_LOG_DOMAIN,
	 G_LOG_LEVEL_MESSAGE,
	 format,
	 argument_list );

#else
	/* TODO handle narrow and wide streams
	 * for multi platform support
	 */
	print_count = file_stream_vfprintf(
		       libsystem_notify_stream,
		       format,
		       argument_list );
#endif

	VAEND(
	 argument_list );

	if( print_count <= -1 )
	{
		return( -1 );
	}
	return( print_count );
}

#undef VARARGS
#undef VASTART
#undef VAEND

/* Prints the data on the notify stream
 * Returns the amount of printed characters if successful or -1 on error
 */
int libsystem_notify_print_data(
     const uint8_t *data,
     size_t data_size )
{
	size_t byte_iterator  = 0;
	size_t data_iterator  = 0;
	int print_count       = 0;
	int total_print_count = 0;

	if( libsystem_notify_stream == NULL )
	{
		return( 0 );
	}
	if( data == NULL )
	{
		return( -1 );
	}
	while( data_iterator < data_size )
	{
		while( byte_iterator < data_size )
		{
			if( byte_iterator % 16 == 0 )
			{
				print_count = libsystem_notify_printf(
					       "%.8" PRIzx ": ",
					       byte_iterator );

				/* TODO check return value upper range */

				if( print_count <= -1 )
				{
					return( -1 );
				}
				total_print_count += print_count;
			}
			print_count = libsystem_notify_printf(
				       "%.2" PRIx8 " ",
				       data[ byte_iterator++ ] );

			/* TODO check return value upper range */

			if( print_count <= -1 )
			{
				return( -1 );
			}
			total_print_count += print_count;

			if( byte_iterator % 16 == 0 )
			{
				break;
			}
			else if( byte_iterator % 8 == 0 )
			{
				print_count = libsystem_notify_printf(
					       " " );

				/* TODO check return value upper range */

				if( print_count <= -1 )
				{
					return( -1 );
				}
				total_print_count += print_count;
			}
		}
		while( byte_iterator % 16 != 0 )
		{
			byte_iterator++;

			print_count = libsystem_notify_printf(
				       "   " );

			/* TODO check return value upper range */

			if( print_count <= -1 )
			{
				return( -1 );
			}
			total_print_count += print_count;

			if( ( byte_iterator % 8 == 0 )
			 && ( byte_iterator % 16 != 0 ) )
			{
				print_count = libsystem_notify_printf(
					       " " );

				/* TODO check return value upper range */

				if( print_count <= -1 )
				{
					return( -1 );
				}
				total_print_count += print_count;
			}
		}
		print_count = libsystem_notify_printf(
			       "  " );

		/* TODO check return value upper range */

		if( print_count <= -1 )
		{
			return( -1 );
		}
		total_print_count += print_count;

		byte_iterator = data_iterator;

		while( byte_iterator < data_size )
		{
			if( ( data[ byte_iterator ] >= 0x20 )
			 && ( data[ byte_iterator ] <= 0x7e ) )
			{
				print_count = libsystem_notify_printf(
					       "%c",
					       (char) data[ byte_iterator ] );
			}
			else
			{
				print_count = libsystem_notify_printf(
					       "." );
			}
			/* TODO check return value upper range */

			if( print_count <= -1 )
			{
				return( -1 );
			}
			total_print_count += print_count;

			byte_iterator++;

			if( byte_iterator % 16 == 0 )
			{
				break;
			}
			else if( byte_iterator % 8 == 0 )
			{
				print_count = libsystem_notify_printf(
					       " " );

				/* TODO check return value upper range */

				if( print_count <= -1 )
				{
					return( -1 );
				}
				total_print_count += print_count;
			}
		}
		print_count = libsystem_notify_printf(
			       "\n" );

		/* TODO check return value upper range */

		if( print_count <= -1 )
		{
			return( -1 );
		}
		total_print_count += print_count;

		data_iterator = byte_iterator;
	}
	print_count = libsystem_notify_printf(
		       "\n" );

	/* TODO check return value upper range */

	if( print_count <= -1 )
	{
		return( -1 );
	}
	total_print_count += print_count;

	return( total_print_count );
}

/* Prints the backtrace of the error on the notify stream
 * Returns the amount of printed characters if successful or -1 on error
 */
int libsystem_notify_print_error_backtrace(
     liberror_error_t *error )
{
	if( libsystem_notify_stream == NULL )
	{
		return( -1 );
	}
	return( liberror_error_backtrace_fprint(
	         error,
	         libsystem_notify_stream ) );
}

