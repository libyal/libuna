/*
 * Common output functions for the ucatools
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

#if !defined( _PFFOUTPUT_H )
#define _PFFOUTPUT_H

#include <common.h>
#include <date_time.h>
#include <types.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

void ucaoutput_copyright_fprint(
      FILE *stream );

void ucaoutput_version_fprint(
      FILE *stream,
      const character_t *program );

void ucaoutput_timestamp_fprint(
      FILE *stream,
      time_t timestamp );

void ucaoutput_bytes_per_second_fprint(
      FILE *stream,
      size64_t bytes,
      time_t seconds );

void ucaoutput_bytes_fprint(
      FILE *stream,
      size64_t bytes );

void ucaoutput_codepages_fprint(
      FILE *stream );

#if defined( __cplusplus )
}
#endif

#endif

