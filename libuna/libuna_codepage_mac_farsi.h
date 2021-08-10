/*
 * MacFarsi codepage functions
 *
 * Copyright (C) 2008-2021, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBUNA_CODEPAGE_MAC_FARSI_H )
#define _LIBUNA_CODEPAGE_MAC_FARSI_H

#include <common.h>
#include <types.h>

#include "libuna_libcerror.h"
#include "libuna_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libuna_codepage_mac_farsi_copy_from_byte_stream(
     libuna_unicode_character_t *unicode_character,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     libcerror_error_t **error );

int libuna_codepage_mac_farsi_copy_to_byte_stream(
     libuna_unicode_character_t unicode_character,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBUNA_CODEPAGE_MAC_FARSI_H ) */

