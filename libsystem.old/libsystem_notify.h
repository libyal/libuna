/*
 * Notification functions
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

#if !defined( _LIBSYSTEM_NOTIFY_H )
#define _LIBSYSTEM_NOTIFY_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern int libsystem_notify_verbose;

extern FILE *libsystem_notify_stream;

void libsystem_notify_set_verbose(
      int verbose );

int libsystem_notify_set_stream(
     FILE *stream,
     liberror_error_t **error );

int libsystem_notify_stream_open(
     const char *filename,
     liberror_error_t **error );

int libsystem_notify_stream_close(
     liberror_error_t **error );

int libsystem_notify_printf(
     const char *format,
     ... );

int libsystem_notify_print_data(
     const uint8_t *data,
     size_t data_size );

int libsystem_notify_print_error_backtrace(
     liberror_error_t *error );

#if defined( __cplusplus )
}
#endif

#endif

