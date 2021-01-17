/*
 * Windows 1250 codepage (Central European) functions
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

#if !defined( _LIBUNA_CODEPAGE_WINDOWS_1250_H )
#define _LIBUNA_CODEPAGE_WINDOWS_1250_H

#include <common.h>
#include <types.h>

#include "libuna_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBUNA_EXTERN_VARIABLE \
const uint16_t libuna_codepage_windows_1250_byte_stream_to_unicode_base_0x80[ 128 ];

LIBUNA_EXTERN_VARIABLE \
const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x00a0[ 128 ];

LIBUNA_EXTERN_VARIABLE \
const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x0138[ 72 ];

LIBUNA_EXTERN_VARIABLE \
const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x02d8[ 8 ];

LIBUNA_EXTERN_VARIABLE \
const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x2010[ 24 ];

LIBUNA_EXTERN_VARIABLE \
const uint8_t libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x2030[ 16 ];

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBUNA_CODEPAGE_WINDOWS_1250_H ) */

