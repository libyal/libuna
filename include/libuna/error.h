/*
 * The error code definitions for libuna
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

#if !defined( _LIBUNA_ERROR_H )
#define _LIBUNA_ERROR_H

/* External error type definition hides internal structure
 */
typedef intptr_t libuna_error_t;

/* The error domains
 */
enum LIBUNA_ERROR_DOMAINS
{
	LIBUNA_ERROR_DOMAIN_ARGUMENTS           = (int) 'a',
	LIBUNA_ERROR_DOMAIN_CONVERSION          = (int) 'c',
};

/* The argument error codes
 */
enum LIBUNA_ARGUMENT_ERROR
{
	LIBUNA_ARGUMENT_ERROR_GENERIC           = 0,
	LIBUNA_ARGUMENT_ERROR_INVALID           = 1,
	LIBUNA_ARGUMENT_ERROR_LESS_THAN_ZERO    = 2,
	LIBUNA_ARGUMENT_ERROR_ZERO_OR_LESS      = 3,
	LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM   = 4,
	LIBUNA_ARGUMENT_ERROR_TOO_SMALL         = 5,
	LIBUNA_ARGUMENT_ERROR_UNSUPPORTED_VALUE = 6,
	LIBUNA_ARGUMENT_ERROR_OUT_OF_BOUNDS     = 7
};

/* The conversion error codes
 */
enum LIBUNA_CONVERSION_ERROR
{
	LIBUNA_CONVERSION_ERROR_GENERIC         = 0,
	LIBUNA_CONVERSION_ERROR_INVALID_INPUT   = 1,
	LIBUNA_CONVERSION_ERROR_INVALID_OUTPUT  = 2
};

#endif

