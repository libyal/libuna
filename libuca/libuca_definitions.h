/*
 * Definitions
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

#if !defined( _LIBUCA_DEFINITIONS_H )
#define _LIBUCA_DEFINITIONS_H

#include <libuca/definitions.h>

#define LIBUCA_UNICODE_REPLACEMENT_CHARACTER		0x0000fffd
#define LIBUCA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX	0x0000ffff
#define LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START		0x0000dc00
#define LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END		0x0000dfff
#define LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START		0x0000d800
#define LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_END		0x0000dbff
#define LIBUCA_UNICODE_CHARACTER_MAX			0x0010ffff

#define LIBUCA_UTF16_CHARACTER_MAX			0x0010ffff
#define LIBUCA_UTF32_CHARACTER_MAX			0x7fffffff

#define LIBUCA_ASCII_REPLACEMENT_CHARACTER		0x1a

#endif

