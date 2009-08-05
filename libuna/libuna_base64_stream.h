/*
 * Base64 stream functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBUNA_BASE64_STREAM_H )
#define _LIBUNA_BASE64_STREAM_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libuna_extern.h"
#include "libuna_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBUNA_EXTERN int libuna_base64_stream_decode_size(
                   uint8_t *base64_stream,
                   size_t base64_stream_size,
                   size_t *byte_stream_size,
                   liberror_error_t **error );

LIBUNA_EXTERN int libuna_base64_stream_decode(
                   uint8_t *base64_stream,
                   size_t base64_stream_size,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   liberror_error_t **error );

LIBUNA_EXTERN int libuna_base64_stream_encode_size(
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   size_t *base64_stream_size,
                   liberror_error_t **error );

LIBUNA_EXTERN int libuna_base64_stream_encode(
                   uint8_t *base64_stream,
                   size_t base64_stream_size,
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

