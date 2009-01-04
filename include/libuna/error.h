/*
 * The error code definitions
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

/* The error domains
 */
#define LIBUNA_ERROR_DOMAIN_ARGUMENTS			(int) 'a'
#define LIBUNA_ERROR_DOMAIN_CONVERSION			(int) 'c'
#define LIBUNA_ERROR_DOMAIN_IO				(int) 'i'
#define LIBUNA_ERROR_DOMAIN_MEMORY			(int) 'm'

/* Argument error codes
 */
#define LIBUNA_ERROR_ARGUMENT_INVALID			1
#define LIBUNA_ERROR_ARGUMENT_EXCEEDS_MAXIMUM		2
#define LIBUNA_ERROR_ARGUMENT_TOO_SMALL			3
#define LIBUNA_ERROR_ARGUMENT_UNSUPPORTED_VALUE		4

/* Libuna error codes
 */
#define LIBUNA_ERROR_CONVERSION_INVALID_INPUT		5
#define LIBUNA_ERROR_CONVERSION_INVALID_OUTPUT		6

/* The error domains
 */
typedef enum libuna_error_domain libuna_error_domain_t;

enum libuna_error_domain
{
	arguments  = (int) 'a',
	conversion = (int) 'c',
	input      = (int) 'i',
	memory     = (int) 'm',
	output     = (int) 'o'
};

/* The argument error codes
 */
typedef enum libuna_argument_error libuca_argument_error_t;

enum libuna_argument_error
{
	invalid           = 0,
	exceeds_maximum   = 1,
	too_small         = 2,
	unsupported_value = 3
};

/* The conversion error codes
 */
typedef enum libuna_conversion_error libuca_conversion_error_t;

enum libuna_conversion_error
{
	invalid_input  = 0,
	invalid_output = 1
};

#endif

