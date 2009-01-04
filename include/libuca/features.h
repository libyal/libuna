/*
 * Features of libuca
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

#if !defined( _LIBUCA_FEATURES_H )
#define _LIBUCA_FEATURES_H

/* The libuca type support features
 */
#if 0 || defined( HAVE_WIDE_CHARACTER_TYPE )
#define LIBUCA_WIDE_CHARACTER_TYPE      1

#if 0 || defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
#define LIBUCA_WIDE_CHARACTER_FILE_FUNCTIONS    1
#endif

#endif

#endif

