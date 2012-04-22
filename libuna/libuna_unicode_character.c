/*
 * Unicode character functions
 *
 * Copyright (c) 2008-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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
#include <types.h>

#include "libuna_base64_stream.h"
#include "libuna_codepage_iso_8859_2.h"
#include "libuna_codepage_iso_8859_3.h"
#include "libuna_codepage_iso_8859_4.h"
#include "libuna_codepage_iso_8859_5.h"
#include "libuna_codepage_iso_8859_6.h"
#include "libuna_codepage_iso_8859_7.h"
#include "libuna_codepage_iso_8859_8.h"
#include "libuna_codepage_iso_8859_9.h"
#include "libuna_codepage_iso_8859_10.h"
#include "libuna_codepage_iso_8859_13.h"
#include "libuna_codepage_iso_8859_14.h"
#include "libuna_codepage_iso_8859_15.h"
#include "libuna_codepage_iso_8859_16.h"
#include "libuna_codepage_koi8_r.h"
#include "libuna_codepage_koi8_u.h"
#include "libuna_codepage_windows_874.h"
#include "libuna_codepage_windows_932.h"
#include "libuna_codepage_windows_936.h"
#include "libuna_codepage_windows_1250.h"
#include "libuna_codepage_windows_1251.h"
#include "libuna_codepage_windows_1252.h"
#include "libuna_codepage_windows_1253.h"
#include "libuna_codepage_windows_1254.h"
#include "libuna_codepage_windows_1255.h"
#include "libuna_codepage_windows_1256.h"
#include "libuna_codepage_windows_1257.h"
#include "libuna_codepage_windows_1258.h"
#include "libuna_definitions.h"
#include "libuna_inline.h"
#include "libuna_libcerror.h"
#include "libuna_types.h"
#include "libuna_unicode_character.h"
#include "libuna_unused.h"

/* Determines the size of a byte stream character from an Unicode character
 * Adds the size to the byte stream character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_size_to_byte_stream(
     libuna_unicode_character_t unicode_character,
     int codepage,
     size_t *byte_stream_character_size,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_size_to_byte_stream";

	if( byte_stream_character_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream character size.",
		 function );

		return( -1 );
	}
	switch( codepage )
	{
		case LIBUNA_CODEPAGE_ASCII:
		case LIBUNA_CODEPAGE_ISO_8859_1:
		case LIBUNA_CODEPAGE_ISO_8859_2:
		case LIBUNA_CODEPAGE_ISO_8859_3:
		case LIBUNA_CODEPAGE_ISO_8859_4:
		case LIBUNA_CODEPAGE_ISO_8859_5:
		case LIBUNA_CODEPAGE_ISO_8859_6:
		case LIBUNA_CODEPAGE_ISO_8859_7:
		case LIBUNA_CODEPAGE_ISO_8859_8:
		case LIBUNA_CODEPAGE_ISO_8859_9:
		case LIBUNA_CODEPAGE_ISO_8859_10:
		case LIBUNA_CODEPAGE_ISO_8859_11:
		case LIBUNA_CODEPAGE_ISO_8859_13:
		case LIBUNA_CODEPAGE_ISO_8859_14:
		case LIBUNA_CODEPAGE_ISO_8859_15:
		case LIBUNA_CODEPAGE_ISO_8859_16:
		case LIBUNA_CODEPAGE_KOI8_R:
		case LIBUNA_CODEPAGE_KOI8_U:
		case LIBUNA_CODEPAGE_WINDOWS_874:
		case LIBUNA_CODEPAGE_WINDOWS_1250:
		case LIBUNA_CODEPAGE_WINDOWS_1251:
		case LIBUNA_CODEPAGE_WINDOWS_1252:
		case LIBUNA_CODEPAGE_WINDOWS_1253:
		case LIBUNA_CODEPAGE_WINDOWS_1254:
		case LIBUNA_CODEPAGE_WINDOWS_1255:
		case LIBUNA_CODEPAGE_WINDOWS_1256:
		case LIBUNA_CODEPAGE_WINDOWS_1257:
		case LIBUNA_CODEPAGE_WINDOWS_1258:
			*byte_stream_character_size += 1;
			break;

		case LIBUNA_CODEPAGE_WINDOWS_932:
			if( unicode_character < 0x00000080UL )
			{
				*byte_stream_character_size += 1;
			}
/* TODO */
			else
			{
				*byte_stream_character_size += 2;
			}
			break;

		case LIBUNA_CODEPAGE_WINDOWS_936:
/* TODO improve check
 * determine non convertable characters
 */
			if( unicode_character < 0x00000080UL )
			{
				*byte_stream_character_size += 1;
			}
			else if( unicode_character == 0x20ac )
			{
				*byte_stream_character_size += 1;
			}
			else
			{
				*byte_stream_character_size += 2;
			}
			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported codepage: %d.",
			 function,
			 codepage );

			return( -1 );
	}
	return( 1 );
}

/* Copies a Unicode character from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_from_byte_stream(
     libuna_unicode_character_t *unicode_character,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     int codepage,
     libcerror_error_t **error )
{
	static char *function         = "libuna_unicode_character_copy_from_byte_stream";
	uint8_t additional_character  = 0;
	uint8_t byte_stream_character = 0;

	if( unicode_character == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( byte_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream index.",
		 function );

		return( -1 );
	}
	if( *byte_stream_index >= byte_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	byte_stream_character = byte_stream[ *byte_stream_index ];

	switch( codepage )
	{
		case LIBUNA_CODEPAGE_ASCII:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				*unicode_character = 0xfffd;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_1:
			*unicode_character = byte_stream_character;

			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_2:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_2_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_3:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_3_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_4:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_4_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_5:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_5_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_6:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_6_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_7:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_7_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_8:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_8_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_9:
			if( byte_stream_character < 0xd0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xd0;

				*unicode_character = libuna_codepage_iso_8859_9_byte_stream_to_unicode_base_0xd0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_10:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_10_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_11:
			if( byte_stream_character < 0xa1 )
			{
				*unicode_character = byte_stream_character;
			}
			else if( byte_stream_character < 0xdb )
			{
				*unicode_character = byte_stream_character + 0x0d60;
			}
			else if( byte_stream_character < 0xdf )
			{
				*unicode_character = 0xfffd;
			}
			else if( byte_stream_character < 0xfc )
			{
				*unicode_character = byte_stream_character + 0x0d60;
			}
			else
			{
				*unicode_character = 0xfffd;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_13:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_13_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_14:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_14_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_15:
			if( ( byte_stream_character >= 0xa0 )
			 && ( byte_stream_character < 0xc0 ) )
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_15_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			else
			{
				*unicode_character = byte_stream_character;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_16:
			if( byte_stream_character < 0xa0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xa0;

				*unicode_character = libuna_codepage_iso_8859_16_byte_stream_to_unicode_base_0xa0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_KOI8_R:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_koi8_r_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_KOI8_U:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_koi8_u_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_874:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_874_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_932:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else if( ( byte_stream_character >= 0xa1 )
			      && ( byte_stream_character < 0xe0 ) ) 
			{
				*unicode_character = 0xff61 + byte_stream_character - 0xa1;
			}
			else if( ( *byte_stream_index + 1 ) <= byte_stream_size )
			{
				*byte_stream_index += 1;

				additional_character = byte_stream[ *byte_stream_index ];

				if( byte_stream_character == 0x81 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xad ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8140[ additional_character ];
					}
					else if( ( additional_character >= 0xb8 )
					      && ( additional_character < 0xc0 ) )
					{
						additional_character -= 0xb8;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x81b8[ additional_character ];
					}
					else if( ( additional_character >= 0xc8 )
					      && ( additional_character < 0xcf ) )
					{
						additional_character -= 0xc8;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x81c8[ additional_character ];
					}
					else if( ( additional_character >= 0xda )
					      && ( additional_character < 0xea ) )
					{
						additional_character -= 0xda;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x81da[ additional_character ];
					}
					else if( ( additional_character >= 0xf0 )
					      && ( additional_character < 0xf8 ) )
					{
						additional_character -= 0xf0;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x81f0[ additional_character ];
					}
					else if( additional_character == 0xfc )
					{
						*unicode_character = 0x25ef;
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x82 )
				{
					if( ( additional_character >= 0x4f )
					 && ( additional_character < 0x59 ) )
					{
						*unicode_character = 0xff10 - 0x4f + additional_character;
					}
					else if( ( additional_character >= 0x60 )
					      && ( additional_character < 0x7a ) )
					{
						*unicode_character = 0xff21 - 0x60 + additional_character;
					}
					else if( ( additional_character >= 0x81 )
					      && ( additional_character < 0x9b ) )
					{
						*unicode_character = 0xff41 - 0x81 + additional_character;
					}
					else if( ( additional_character >= 0x9f )
					      && ( additional_character < 0xf2 ) )
					{
						*unicode_character = 0x3041 - 0x9f + additional_character;
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x83 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0x7f ) )
					{
						*unicode_character = 0x30a1 - 0x40 + additional_character;
					}
					else if( ( additional_character >= 0x80 )
					      && ( additional_character < 0x97 ) )
					{
						*unicode_character = 0x30e0 - 0x80 + additional_character;
					}
					else if( ( additional_character >= 0x9f )
					      && ( additional_character < 0xb0 ) )
					{
						*unicode_character = 0x0391 - 0x9f + additional_character;
					}
					else if( ( additional_character >= 0xb0 )
					      && ( additional_character < 0xb7 ) )
					{
						*unicode_character = 0x03a3 - 0xb0 + additional_character;
					}
					else if( ( additional_character >= 0xbf )
					      && ( additional_character < 0xd0 ) )
					{
						*unicode_character = 0x03b1 - 0xbf + additional_character;
					}
					else if( ( additional_character >= 0xd0 )
					      && ( additional_character < 0xd7 ) )
					{
						*unicode_character = 0x03c3 - 0xd0 + additional_character;
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x84 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0x61 ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8440[ additional_character ];
					}
					else if( ( additional_character >= 0x70 )
					      && ( additional_character < 0x7f ) )
					{
						additional_character -= 0x70;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8470[ additional_character ];
					}
					else if( ( additional_character >= 0x80 )
					      && ( additional_character < 0x92 ) )
					{
						*unicode_character = 0x043e - 0x80 + additional_character;
					}
					else if( ( additional_character >= 0x9f )
					      && ( additional_character < 0xbf ) )
					{
						additional_character -= 0x9f;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x849f[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x87 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0x54 ) )
					{
						*unicode_character = 0x2460 - 0x40 + additional_character;
					}
					else if( ( additional_character >= 0x54 )
					      && ( additional_character < 0x5e ) )
					{
						*unicode_character = 0x2160 - 0x54 + additional_character;
					}
					else if( ( additional_character >= 0x5f )
					      && ( additional_character < 0x76 ) )
					{
						additional_character -= 0x5f;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x875f[ additional_character ];
					}
					else if( additional_character == 0x7e )
					{
						*unicode_character = 0x337b;
					}
					else if( ( additional_character >= 0x80 )
					      && ( additional_character < 0x9d ) )
					{
						additional_character -= 0x80;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8780[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x88 )
				{
					if( ( additional_character >= 0x9f )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x9f;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x889f[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x89 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8940[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x8a )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8a40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x8b )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8b40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x8c )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8c40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x8d )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8d40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x8e )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8e40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x8f )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x8f40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x90 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9040[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x91 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9140[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x92 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9240[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x93 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9340[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x94 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9440[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x95 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9540[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x96 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9640[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x97 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9740[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x98 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0x73 ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9840[ additional_character ];
					}
					else if( ( additional_character >= 0x9f )
					      && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x9f;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x989f[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x99 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9940[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x9a )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9a40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x9b )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9b40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x9c )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9c40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x9d )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9d40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x9e )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9e40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0x9f )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0x9f40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe0 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe040[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe1 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe140[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe2 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe240[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe3 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe340[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe4 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe440[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe5 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe540[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe6 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe640[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe7 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe740[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe8 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe840[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xe9 )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xe940[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xea )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xa5 ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xea40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xed )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xed40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xee )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xee40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xfa )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xfa40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xfb )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0xfd ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xfb40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else if( byte_stream_character == 0xfc )
				{
					if( ( additional_character >= 0x40 )
					 && ( additional_character < 0x4c ) )
					{
						additional_character -= 0x40;

						*unicode_character = libuna_codepage_windows_932_byte_stream_to_unicode_base_0xfc40[ additional_character ];
					}
					else
					{
						*unicode_character = 0xfffd;
					}
				}
				else
				{
					*unicode_character = 0xfffd;
				}
			}
			else
			{
				*unicode_character = 0xfffd;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_936:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else if( byte_stream_character == 0x80 )
			{
				*unicode_character = 0x20ac;
			}
			else if( ( *byte_stream_index + 1 ) <= byte_stream_size )
			{
				*byte_stream_index += 1;

				additional_character = byte_stream[ *byte_stream_index ];

				if( ( byte_stream_character == 0x81 )
				  && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8140[ additional_character ];
				}
				else if( ( byte_stream_character == 0x82 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8240[ additional_character ];
				}
				else if( ( byte_stream_character == 0x83 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8340[ additional_character ];
				}
				else if( ( byte_stream_character == 0x84 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8440[ additional_character ];
				}
				else if( ( byte_stream_character == 0x85 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8540[ additional_character ];
				}
				else if( ( byte_stream_character == 0x86 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8640[ additional_character ];
				}
				else if( ( byte_stream_character == 0x87 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8740[ additional_character ];
				}
				else if( ( byte_stream_character == 0x88 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8840[ additional_character ];
				}
				else if( ( byte_stream_character == 0x89 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8940[ additional_character ];
				}
				else if( ( byte_stream_character == 0x8a )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8a40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x8b )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8b40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x8c )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8c40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x8d )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8d40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x8e )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8e40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x8f )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x8f40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x90 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9040[ additional_character ];
				}
				else if( ( byte_stream_character == 0x91 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9140[ additional_character ];
				}
				else if( ( byte_stream_character == 0x92 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9240[ additional_character ];
				}
				else if( ( byte_stream_character == 0x93 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9340[ additional_character ];
				}
				else if( ( byte_stream_character == 0x94 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9440[ additional_character ];
				}
				else if( ( byte_stream_character == 0x95 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9540[ additional_character ];
				}
				else if( ( byte_stream_character == 0x96 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9640[ additional_character ];
				}
				else if( ( byte_stream_character == 0x97 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9740[ additional_character ];
				}
				else if( ( byte_stream_character == 0x98 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9840[ additional_character ];
				}
				else if( ( byte_stream_character == 0x99 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9940[ additional_character ];
				}
				else if( ( byte_stream_character == 0x9a )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9a40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x9b )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9b40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x9c )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9c40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x9d )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9d40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x9e )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9e40[ additional_character ];
				}
				else if( ( byte_stream_character == 0x9f )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0x9f40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa0 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa040[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa1 )
				      && ( additional_character >= 0xa0 ) )
				{
					additional_character -= 0xa0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa1a0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa2 )
				      && ( additional_character >= 0xa0 ) )
				{
					additional_character -= 0xa0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa2a0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa3 )
				      && ( additional_character >= 0xa0 ) )
				{
					additional_character -= 0xa0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa3a0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa4 )
				      && ( additional_character >= 0xa0 )
				      && ( additional_character < 0xf8 ) )
				{
					additional_character -= 0xa0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa4a0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa5 )
				      && ( additional_character >= 0xa0 )
				      && ( additional_character < 0xf8 ) )
				{
					additional_character -= 0xa0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa5a0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa6 )
				      && ( additional_character >= 0xa0 )
				      && ( additional_character < 0xf8 ) )
				{
					additional_character -= 0xa0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa6a0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa7 )
				      && ( additional_character >= 0xa0 )
				      && ( additional_character < 0xc8 ) )
				{
					additional_character -= 0xa0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa7a0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa7 )
				      && ( additional_character >= 0xd0 )
				      && ( additional_character < 0xf8 ) )
				{
					additional_character -= 0xd0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa7d0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa8 )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0x98 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa840[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa8 )
				      && ( additional_character >= 0xa0 )
				      && ( additional_character < 0xf0 ) )
				{
					additional_character -= 0xa0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa8a0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa9 )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0x88 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa940[ additional_character ];
				}
				else if( ( byte_stream_character == 0xa9 )
				      && ( additional_character == 0x88 ) )
				{
					*unicode_character = 0xfe6b;
				}
				else if( ( byte_stream_character == 0xa9 )
				      && ( additional_character == 0x96 ) )
				{
					*unicode_character = 0x3007;
				}
				else if( ( byte_stream_character == 0xa9 )
				      && ( additional_character >= 0xa0 )
				      && ( additional_character < 0xf0 ) )
				{
					additional_character -= 0xa0;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xa9a0[ additional_character ];
				}
				else if( ( byte_stream_character == 0xaa )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xaa40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xaa )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x7371;
				}
				else if( ( byte_stream_character == 0xab )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xab40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xab )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x73f7;
				}
				else if( ( byte_stream_character == 0xac )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xac40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xac )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x747a;
				}
				else if( ( byte_stream_character == 0xad )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xad40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xad )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x74f2;
				}
				else if( ( byte_stream_character == 0xae )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xae40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xae )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x7587;
				}
				else if( ( byte_stream_character == 0xaf )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xaf40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xaf )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x7644;
				}
				else if( ( byte_stream_character == 0xb0 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb040[ additional_character ];
				}
				else if( ( byte_stream_character == 0xb1 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb140[ additional_character ];
				}
				else if( ( byte_stream_character == 0xb2 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb240[ additional_character ];
				}
				else if( ( byte_stream_character == 0xb3 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb340[ additional_character ];
				}
				else if( ( byte_stream_character == 0xb4 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb440[ additional_character ];
				}
				else if( ( byte_stream_character == 0xb5 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb540[ additional_character ];
				}
				else if( ( byte_stream_character == 0xb6 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb640[ additional_character ];
				}
				else if( ( byte_stream_character == 0xb7 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb740[ additional_character ];
				}
				else if( ( byte_stream_character == 0xb8 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb840[ additional_character ];
				}
				else if( ( byte_stream_character == 0xb9 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xb940[ additional_character ];
				}
				else if( ( byte_stream_character == 0xba )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xba40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xbb )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xbb40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xbc )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xbc40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xbd )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xbd40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xbe )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xbe40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xbf )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xbf40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc0 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc040[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc1 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc140[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc2 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc240[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc3 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc340[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc4 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc440[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc5 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc540[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc6 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc640[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc7 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc740[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc8 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc840[ additional_character ];
				}
				else if( ( byte_stream_character == 0xc9 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xc940[ additional_character ];
				}
				else if( ( byte_stream_character == 0xca )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xca40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xcb )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xcb40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xcc )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xcc40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xcd )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xcd40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xce )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xce40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xcf )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xcf40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd0 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd040[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd1 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd140[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd2 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd240[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd3 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd340[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd4 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd440[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd5 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd540[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd6 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd640[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd7 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd740[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd8 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd840[ additional_character ];
				}
				else if( ( byte_stream_character == 0xd9 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xd940[ additional_character ];
				}
				else if( ( byte_stream_character == 0xda )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xda40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xdb )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xdb40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xdc )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xdc40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xdd )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xdd40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xde )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xde40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xdf )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xdf40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe0 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe040[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe1 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe140[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe2 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe240[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe3 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe340[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe4 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe440[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe5 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe540[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe6 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe640[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe7 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe740[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe8 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe840[ additional_character ];
				}
				else if( ( byte_stream_character == 0xe9 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xe940[ additional_character ];
				}
				else if( ( byte_stream_character == 0xea )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xea40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xeb )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xeb40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xec )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xec40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xed )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xed40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xee )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xee40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xef )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xef40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf0 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf040[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf1 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf140[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf2 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf240[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf3 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf340[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf4 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf440[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf5 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf540[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf6 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf640[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf7 )
				      && ( additional_character >= 0x40 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf740[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf8 )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf840[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf8 )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x9d42;
				}
				else if( ( byte_stream_character == 0xf9 )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xf940[ additional_character ];
				}
				else if( ( byte_stream_character == 0xf9 )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x9da2;
				}
				else if( ( byte_stream_character == 0xfa )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xfa40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xfa )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x9e02;
				}
				else if( ( byte_stream_character == 0xfb )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xfb40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xfb )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x9eaa;
				}
				else if( ( byte_stream_character == 0xfc )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xfc40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xfc )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0x9f31;
				}
				else if( ( byte_stream_character == 0xfd )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0xa0 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xfd40[ additional_character ];
				}
				else if( ( byte_stream_character == 0xfd )
				      && ( additional_character == 0xa0 ) )
				{
					*unicode_character = 0xf9f1;
				}
				else if( ( byte_stream_character == 0xfe )
				      && ( additional_character >= 0x40 )
				      && ( additional_character < 0x50 ) )
				{
					additional_character -= 0x40;

					*unicode_character = libuna_codepage_windows_936_byte_stream_to_unicode_base_0xfe40[ additional_character ];
				}
				else
				{
					*unicode_character = 0xfffd;
				}
			}
			else
			{
				*unicode_character = 0xfffd;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1250:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_1250_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1251:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_1251_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1252:
			if( ( byte_stream_character < 0x80 )
			 || ( byte_stream_character >= 0xa0 ) )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_1252_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1253:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_1253_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1254:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else if( byte_stream_character < 0xa0 )
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_1254_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			else if( byte_stream_character < 0xd0 )
			{
				*unicode_character = byte_stream_character;
			}
			else if( byte_stream_character < 0xe0 )
			{
				byte_stream_character -= 0xd0;

				*unicode_character = libuna_codepage_windows_1254_byte_stream_to_unicode_base_0xd0[ byte_stream_character ];
			}
			else if( byte_stream_character < 0xf0 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0xf0;

				*unicode_character = libuna_codepage_windows_1254_byte_stream_to_unicode_base_0xf0[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1255:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_1255_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1256:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_1256_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1257:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_1257_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1258:
			if( byte_stream_character < 0x80 )
			{
				*unicode_character = byte_stream_character;
			}
			else
			{
				byte_stream_character -= 0x80;

				*unicode_character = libuna_codepage_windows_1258_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
			}
			*byte_stream_index += 1;

			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			"%s: unsupported codepage: %d.",
			 function,
			 codepage );

			return( -1 );
	}
	return( 1 );
}

/* Copies a Unicode character to a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_to_byte_stream(
     libuna_unicode_character_t unicode_character,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     int codepage,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_to_byte_stream";

	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( byte_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream index.",
		 function );

		return( -1 );
	}
	if( *byte_stream_index >= byte_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	switch( codepage )
	{
		case LIBUNA_CODEPAGE_ASCII:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_1:
			if( unicode_character < 0x0100 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_2:
			if( unicode_character < 0x00a0 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x0120 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_2_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0138 )
			      && ( unicode_character < 0x0180 ) )
			{
				unicode_character -= 0x0138;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_2_unicode_to_byte_stream_base_0x0138[ unicode_character ];
			}
			else if( unicode_character == 0x02c7 )
			{
				byte_stream[ *byte_stream_index ] = 0xb7;
			}
			else if( ( unicode_character >= 0x02d8 )
			      && ( unicode_character < 0x02e0 ) )
			{
				unicode_character -= 0x02d8;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_2_unicode_to_byte_stream_base_0x02d8[ unicode_character ];
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_3:
			if( unicode_character < 0x00a0 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x0100 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0108 )
			      && ( unicode_character < 0x0110 ) )
			{
				unicode_character -= 0x0108;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x0108[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0118 )
			      && ( unicode_character < 0x0128 ) )
			{
				unicode_character -= 0x0118;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x0118[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0130 )
			      && ( unicode_character < 0x0138 ) )
			{
				unicode_character -= 0x0130;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x0130[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0158 )
			      && ( unicode_character < 0x0160 ) )
			{
				unicode_character -= 0x0158;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x0158[ unicode_character ];
			}
			else if( unicode_character == 0x016c )
			{
				byte_stream[ *byte_stream_index ] = 0xdd;
			}
			else if( unicode_character == 0x016d )
			{
				byte_stream[ *byte_stream_index ] = 0xfd;
			}
			else if( unicode_character == 0x017b )
			{
				byte_stream[ *byte_stream_index ] = 0xaf;
			}
			else if( unicode_character == 0x017c )
			{
				byte_stream[ *byte_stream_index ] = 0xbf;
			}
			else if( unicode_character == 0x02d8 )
			{
				byte_stream[ *byte_stream_index ] = 0xa2;
			}
			else if( unicode_character == 0x02d9 )
			{
				byte_stream[ *byte_stream_index ] = 0xff;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_4:
			if( unicode_character < 0x00a0 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x0158 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_4_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0160 )
			      && ( unicode_character < 0x0180 ) )
			{
				unicode_character -= 0x0160;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_4_unicode_to_byte_stream_base_0x0160[ unicode_character ];
			}
			else if( unicode_character == 0x02c7 )
			{
				byte_stream[ *byte_stream_index ] = 0xb7;
			}
			else if( unicode_character == 0x02d9 )
			{
				byte_stream[ *byte_stream_index ] = 0xff;
			}
			else if( unicode_character == 0x02db )
			{
				byte_stream[ *byte_stream_index ] = 0xb2;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_5:
			if( unicode_character < 0x00a1 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( unicode_character == 0x00a7 )
			{
				byte_stream[ *byte_stream_index ] = 0xfd;
			}
			else if( unicode_character == 0x00ad )
			{
				byte_stream[ *byte_stream_index ] = 0xad;
			}
			else if( ( unicode_character >= 0x0400 )
			      && ( unicode_character < 0x0460 ) )
			{
				unicode_character -= 0x0400;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_5_unicode_to_byte_stream_base_0x0400[ unicode_character ];
			}
			else if( unicode_character == 0x2116 )
			{
				byte_stream[ *byte_stream_index ] = 0xf0;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_6:
			if( unicode_character < 0x00a1 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( unicode_character == 0x00a4 )
			{
				byte_stream[ *byte_stream_index ] = 0xa4;
			}
			else if( unicode_character == 0x00ad )
			{
				byte_stream[ *byte_stream_index ] = 0xad;
			}
			else if( unicode_character == 0x060c )
			{
				byte_stream[ *byte_stream_index ] = 0xac;
			}
			else if( ( unicode_character >= 0x0618 )
			      && ( unicode_character < 0x658 ) )
			{
				unicode_character -= 0x0618;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_6_unicode_to_byte_stream_base_0x0618[ unicode_character ];
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_7:
			if( unicode_character < 0x00a0 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x00b8 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_7_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( unicode_character == 0x00bb )
			{
				byte_stream[ *byte_stream_index ] = 0xbb;
			}
			else if( unicode_character == 0x00bd )
			{
				byte_stream[ *byte_stream_index ] = 0xbd;
			}
			else if( unicode_character == 0x037a )
			{
				byte_stream[ *byte_stream_index ] = 0xaa;
			}
			else if( ( unicode_character >= 0x0380 )
			      && ( unicode_character < 0x03d0 ) )
			{
				unicode_character -= 0x0380;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_7_unicode_to_byte_stream_base_0x0380[ unicode_character ];
			}
			else if( unicode_character == 0x2016 )
			{
				byte_stream[ *byte_stream_index ] = 0xaf;
			}
			else if( unicode_character == 0x2018 )
			{
				byte_stream[ *byte_stream_index ] = 0xa1;
			}
			else if( unicode_character == 0x2019 )
			{
				byte_stream[ *byte_stream_index ] = 0xa2;
			}
			else if( unicode_character == 0x20ac )
			{
				byte_stream[ *byte_stream_index ] = 0xa4;
			}
			else if( unicode_character == 0x20af )
			{
				byte_stream[ *byte_stream_index ] = 0xa5;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_8:
			if( unicode_character < 0x00a0 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x00c0 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_8_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( unicode_character == 0x00d7 )
			{
				byte_stream[ *byte_stream_index ] = 0xaa;
			}
			else if( unicode_character == 0x00f7 )
			{
				byte_stream[ *byte_stream_index ] = 0xba;
			}
			else if( ( unicode_character >= 0x05d0 )
			      && ( unicode_character < 0x05f0 ) )
			{
				unicode_character -= 0x05d0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_8_unicode_to_byte_stream_base_0x05d0[ unicode_character ];
			}
			else if( unicode_character == 0x200e )
			{
				byte_stream[ *byte_stream_index ] = 0xfd;
			}
			else if( unicode_character == 0x200f )
			{
				byte_stream[ *byte_stream_index ] = 0xfe;
			}
			else if( unicode_character == 0x2017 )
			{
				byte_stream[ *byte_stream_index ] = 0xdf;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_9:
			if( unicode_character < 0x00d0 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00d0 )
			      && ( unicode_character < 0x0100 ) )
			{
				unicode_character -= 0x00d0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_9_unicode_to_byte_stream_base_0x00d0[ unicode_character ];
			}
			else if( unicode_character == 0x011e )
			{
				byte_stream[ *byte_stream_index ] = 0xd0;
			}
			else if( unicode_character == 0x011f )
			{
				byte_stream[ *byte_stream_index ] = 0xf0;
			}
			else if( unicode_character == 0x0130 )
			{
				byte_stream[ *byte_stream_index ] = 0xdd;
			}
			else if( unicode_character == 0x0131 )
			{
				byte_stream[ *byte_stream_index ] = 0xfd;
			}
			else if( unicode_character == 0x015e )
			{
				byte_stream[ *byte_stream_index ] = 0xde;
			}
			else if( unicode_character == 0x015f )
			{
				byte_stream[ *byte_stream_index ] = 0xfe;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_10:
			if( unicode_character < 0x00a1 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( unicode_character == 0x00a7 )
			{
				byte_stream[ *byte_stream_index ] = 0xa7;
			}
			else if( unicode_character == 0x00ad )
			{
				byte_stream[ *byte_stream_index ] = 0xad;
			}
			else if( unicode_character == 0x00b0 )
			{
				byte_stream[ *byte_stream_index ] = 0xb0;
			}
			else if( unicode_character == 0x00b7 )
			{
				byte_stream[ *byte_stream_index ] = 0xb7;
			}
			else if( ( unicode_character >= 0x00c0 )
			      && ( unicode_character < 0x0150 ) )
			{
				unicode_character -= 0x00c0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_10_unicode_to_byte_stream_base_0x00c0[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0160 )
			      && ( unicode_character < 0x0170 ) )
			{
				unicode_character -= 0x0160;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_10_unicode_to_byte_stream_base_0x0160[ unicode_character ];
			}
			else if( unicode_character == 0x0172 )
			{
				byte_stream[ *byte_stream_index ] = 0xd9;
			}
			else if( unicode_character == 0x0173 )
			{
				byte_stream[ *byte_stream_index ] = 0xf9;
			}
			else if( unicode_character == 0x017d )
			{
				byte_stream[ *byte_stream_index ] = 0xac;
			}
			else if( unicode_character == 0x017e )
			{
				byte_stream[ *byte_stream_index ] = 0xbc;
			}
			else if( unicode_character == 0x2015 )
			{
				byte_stream[ *byte_stream_index ] = 0xbd;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_11:
			if( unicode_character < 0x00a1 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x0e01 )
			      && ( unicode_character < 0x0e3b ) )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) ( unicode_character - 0x0d60 );
			}
			else if( ( unicode_character >= 0x0e3f )
			      && ( unicode_character < 0x0e5c ) )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) ( unicode_character - 0x0d60 );
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_13:
			if( unicode_character < 0x00a0 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x0180 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_13_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( ( unicode_character >= 0x2018 )
			       && ( unicode_character < 0x2020 ) )
			{
				unicode_character -= 0x2018;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_13_unicode_to_byte_stream_base_0x2018[ unicode_character ];
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_14:
			if( unicode_character < 0x00a1 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( unicode_character == 0x00a3 )
			{
				byte_stream[ *byte_stream_index ] = 0xa3;
			}
			else if( unicode_character == 0x00a7 )
			{
				byte_stream[ *byte_stream_index ] = 0xa7;
			}
			else if( unicode_character == 0x00a9 )
			{
				byte_stream[ *byte_stream_index ] = 0xa9;
			}
			else if( unicode_character == 0x00ad )
			{
				byte_stream[ *byte_stream_index ] = 0xad;
			}
			else if( unicode_character == 0x00ae )
			{
				byte_stream[ *byte_stream_index ] = 0xae;
			}
			else if( unicode_character == 0x00b6 )
			{
				byte_stream[ *byte_stream_index ] = 0xb6;
			}
			else if( ( unicode_character >= 0x00c0 )
			      && ( unicode_character < 0x0100 ) )
			{
				unicode_character -= 0x00c0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_14_unicode_to_byte_stream_base_0x00c0[ unicode_character ];
			}
			else if( unicode_character == 0x010a )
			{
				byte_stream[ *byte_stream_index ] = 0xa4;
			}
			else if( unicode_character == 0x010b )
			{
				byte_stream[ *byte_stream_index ] = 0xa5;
			}
			else if( unicode_character == 0x0120 )
			{
				byte_stream[ *byte_stream_index ] = 0xb2;
			}
			else if( unicode_character == 0x0121 )
			{
				byte_stream[ *byte_stream_index ] = 0xb3;
			}
			else if( ( unicode_character >= 0x0170 )
			      && ( unicode_character < 0x0178 ) )
			{
				unicode_character -= 0x0170;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_14_unicode_to_byte_stream_base_0x0170[ unicode_character ];
			}
			else if( unicode_character == 0x0178 )
			{
				byte_stream[ *byte_stream_index ] = 0xaf;
			}
			else if( unicode_character == 0x1e02 )
			{
				byte_stream[ *byte_stream_index ] = 0xa1;
			}
			else if( unicode_character == 0x1e03 )
			{
				byte_stream[ *byte_stream_index ] = 0xa2;
			}
			else if( unicode_character == 0x1e0a )
			{
				byte_stream[ *byte_stream_index ] = 0xa6;
			}
			else if( unicode_character == 0x1e0b )
			{
				byte_stream[ *byte_stream_index ] = 0xab;
			}
			else if( unicode_character == 0x1e1e )
			{
				byte_stream[ *byte_stream_index ] = 0xb0;
			}
			else if( unicode_character == 0x1e1f )
			{
				byte_stream[ *byte_stream_index ] = 0xb1;
			}
			else if( unicode_character == 0x1e40 )
			{
				byte_stream[ *byte_stream_index ] = 0xb4;
			}
			else if( unicode_character == 0x1e41 )
			{
				byte_stream[ *byte_stream_index ] = 0xb5;
			}
			else if( unicode_character == 0x1e56 )
			{
				byte_stream[ *byte_stream_index ] = 0xb7;
			}
			else if( unicode_character == 0x1e57 )
			{
				byte_stream[ *byte_stream_index ] = 0xb9;
			}
			else if( unicode_character == 0x1e60 )
			{
				byte_stream[ *byte_stream_index ] = 0xbb;
			}
			else if( unicode_character == 0x1e61 )
			{
				byte_stream[ *byte_stream_index ] = 0xbf;
			}
			else if( unicode_character == 0x1e6a )
			{
				byte_stream[ *byte_stream_index ] = 0xd7;
			}
			else if( unicode_character == 0x1e6b )
			{
				byte_stream[ *byte_stream_index ] = 0xf7;
			}
			else if( ( unicode_character >= 0x1e80 )
			      && ( unicode_character < 0x1e88 ) )
			{
				unicode_character -= 0x1e80;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_14_unicode_to_byte_stream_base_0x1e80[ unicode_character ];
			}
			else if( unicode_character == 0x1ef2 )
			{
				byte_stream[ *byte_stream_index ] = 0xac;
			}
			else if( unicode_character == 0x1ef3 )
			{
				byte_stream[ *byte_stream_index ] = 0xbc;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_15:
			if( unicode_character < 0x00a0 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x00c0 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_15_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( unicode_character < 0x0100 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( unicode_character == 0x0152 )
			{
				byte_stream[ *byte_stream_index ] = 0xbc;
			}
			else if( unicode_character == 0x0153 )
			{
				byte_stream[ *byte_stream_index ] = 0xbd;
			}
			else if( unicode_character == 0x0160 )
			{
				byte_stream[ *byte_stream_index ] = 0xa6;
			}
			else if( unicode_character == 0x0161 )
			{
				byte_stream[ *byte_stream_index ] = 0xa8;
			}
			else if( unicode_character == 0x0178 )
			{
				byte_stream[ *byte_stream_index ] = 0xbe;
			}
			else if( unicode_character == 0x017d )
			{
				byte_stream[ *byte_stream_index ] = 0xb4;
			}
			else if( unicode_character == 0x017e )
			{
				byte_stream[ *byte_stream_index ] = 0xb8;
			}
			else if( unicode_character == 0x20ac )
			{
				byte_stream[ *byte_stream_index ] = 0xa4;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_ISO_8859_16:
			if( unicode_character < 0x00a1 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( unicode_character == 0x00a7 )
			{
				byte_stream[ *byte_stream_index ] = 0xa7;
			}
			else if( ( unicode_character >= 0x00a8 )
			      && ( unicode_character < 0x0108 ) )
			{
				unicode_character -= 0x00a8;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x00a8[ unicode_character ];
			}
			else if( unicode_character == 0x010c )
			{
				byte_stream[ *byte_stream_index ] = 0xb2;
			}
			else if( unicode_character == 0x010d )
			{
				byte_stream[ *byte_stream_index ] = 0xb9;
			}
			else if( unicode_character == 0x0110 )
			{
				byte_stream[ *byte_stream_index ] = 0xd0;
			}
			else if( unicode_character == 0x0111 )
			{
				byte_stream[ *byte_stream_index ] = 0xf0;
			}
			else if( unicode_character == 0x0118 )
			{
				byte_stream[ *byte_stream_index ] = 0xdd;
			}
			else if( unicode_character == 0x0119 )
			{
				byte_stream[ *byte_stream_index ] = 0xfd;
			}
			else if( ( unicode_character >= 0x0140 )
			      && ( unicode_character < 0x0148 ) )
			{
				unicode_character -= 0x0140;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0140[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0150 )
			      && ( unicode_character < 0x0158 ) )
			{
				unicode_character -= 0x0150;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0150[ unicode_character ];
			}
			else if( unicode_character == 0x015a )
			{
				byte_stream[ *byte_stream_index ] = 0xd7;
			}
			else if( unicode_character == 0x015b )
			{
				byte_stream[ *byte_stream_index ] = 0xf7;
			}
			else if( unicode_character == 0x0160 )
			{
				byte_stream[ *byte_stream_index ] = 0xa6;
			}
			else if( unicode_character == 0x0161 )
			{
				byte_stream[ *byte_stream_index ] = 0xa8;
			}
			else if( unicode_character == 0x0170 )
			{
				byte_stream[ *byte_stream_index ] = 0xd8;
			}
			else if( unicode_character == 0x0171 )
			{
				byte_stream[ *byte_stream_index ] = 0xf8;
			}
			else if( ( unicode_character >= 0x0178 )
			      && ( unicode_character < 0x0180 ) )
			{
				unicode_character -= 0x0178;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0178[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0218 )
			      && ( unicode_character < 0x0220 ) )
			{
				unicode_character -= 0x0218;

				byte_stream[ *byte_stream_index ] = libuna_codepage_iso_8859_16_unicode_to_byte_stream_base_0x0218[ unicode_character ];
			}
			else if( unicode_character == 0x201d )
			{
				byte_stream[ *byte_stream_index ] = 0xb5;
			}
			else if( unicode_character == 0x201e )
			{
				byte_stream[ *byte_stream_index ] = 0xa5;
			}
			else if( unicode_character == 0x20ac )
			{
				byte_stream[ *byte_stream_index ] = 0xa4;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_KOI8_R:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( unicode_character == 0x00a0 )
			{
				byte_stream[ *byte_stream_index ] = 0x9a;
			}
			else if( unicode_character == 0x00a9 )
			{
				byte_stream[ *byte_stream_index ] = 0xbf;
			}
			else if( unicode_character == 0x00b0 )
			{
				byte_stream[ *byte_stream_index ] = 0x9c;
			}
			else if( unicode_character == 0x00b2 )
			{
				byte_stream[ *byte_stream_index ] = 0x9d;
			}
			else if( unicode_character == 0x00b8 )
			{
				byte_stream[ *byte_stream_index ] = 0x9e;
			}
			else if( unicode_character == 0x00f8 )
			{
				byte_stream[ *byte_stream_index ] = 0x9f;
			}
			else if( unicode_character == 0x0401 )
			{
				byte_stream[ *byte_stream_index ] = 0xb3;
			}
			else if( ( unicode_character >= 0x0410 )
			      && ( unicode_character < 0x0450 ) )
			{
				unicode_character -= 0x0410;

				byte_stream[ *byte_stream_index ] = libuna_codepage_koi8_r_unicode_to_byte_stream_base_0x0410[ unicode_character ];
			}
			else if( unicode_character == 0x0451 )
			{
				byte_stream[ *byte_stream_index ] = 0xa3;
			}
			else if( unicode_character == 0x2219 )
			{
				byte_stream[ *byte_stream_index ] = 0x95;
			}
			else if( unicode_character == 0x221a )
			{
				byte_stream[ *byte_stream_index ] = 0x96;
			}
			else if( unicode_character == 0x2248 )
			{
				byte_stream[ *byte_stream_index ] = 0x97;
			}
			else if( unicode_character == 0x2264 )
			{
				byte_stream[ *byte_stream_index ] = 0x98;
			}
			else if( unicode_character == 0x2265 )
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else if( unicode_character == 0x2320 )
			{
				byte_stream[ *byte_stream_index ] = 0x93;
			}
			else if( unicode_character == 0x2321 )
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x2500 )
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2502 )
			{
				byte_stream[ *byte_stream_index ] = 0x81;
			}
			else if( unicode_character == 0x250c )
			{
				byte_stream[ *byte_stream_index ] = 0x82;
			}
			else if( unicode_character == 0x2510 )
			{
				byte_stream[ *byte_stream_index ] = 0x83;
			}
			else if( unicode_character == 0x2514 )
			{
				byte_stream[ *byte_stream_index ] = 0x84;
			}
			else if( unicode_character == 0x2518 )
			{
				byte_stream[ *byte_stream_index ] = 0x85;
			}
			else if( unicode_character == 0x251c )
			{
				byte_stream[ *byte_stream_index ] = 0x86;
			}
			else if( unicode_character == 0x2524 )
			{
				byte_stream[ *byte_stream_index ] = 0x87;
			}
			else if( unicode_character == 0x252c )
			{
				byte_stream[ *byte_stream_index ] = 0x88;
			}
			else if( unicode_character == 0x2534 )
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x253c )
			{
				byte_stream[ *byte_stream_index ] = 0x8a;
			}
			else if( ( unicode_character >= 0x2550 )
			      && ( unicode_character < 0x2570 ) )
			{
				unicode_character -= 0x2550;

				byte_stream[ *byte_stream_index ] = libuna_codepage_koi8_r_unicode_to_byte_stream_base_0x2550[ unicode_character ];
			}
			else if( unicode_character == 0x2580 )
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x2584 )
			{
				byte_stream[ *byte_stream_index ] = 0x8c;
			}
			else if( unicode_character == 0x2588 )
			{
				byte_stream[ *byte_stream_index ] = 0x8d;
			}
			else if( unicode_character == 0x258c )
			{
				byte_stream[ *byte_stream_index ] = 0x8e;
			}
			else if( unicode_character == 0x2590 )
			{
				byte_stream[ *byte_stream_index ] = 0x8f;
			}
			else if( unicode_character == 0x2591 )
			{
				byte_stream[ *byte_stream_index ] = 0x90;
			}
			else if( unicode_character == 0x2592 )
			{
				byte_stream[ *byte_stream_index ] = 0x91;
			}
			else if( unicode_character == 0x2593 )
			{
				byte_stream[ *byte_stream_index ] = 0x92;
			}
			else if( unicode_character == 0x25a0 )
			{
				byte_stream[ *byte_stream_index ] = 0x94;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_KOI8_U:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( unicode_character == 0x00a0 )
			{
				byte_stream[ *byte_stream_index ] = 0x9a;
			}
			else if( unicode_character == 0x00a9 )
			{
				byte_stream[ *byte_stream_index ] = 0xbf;
			}
			else if( unicode_character == 0x00b0 )
			{
				byte_stream[ *byte_stream_index ] = 0x9c;
			}
			else if( unicode_character == 0x00b2 )
			{
				byte_stream[ *byte_stream_index ] = 0x9d;
			}
			else if( unicode_character == 0x00b8 )
			{
				byte_stream[ *byte_stream_index ] = 0x9e;
			}
			else if( unicode_character == 0x00f8 )
			{
				byte_stream[ *byte_stream_index ] = 0x9f;
			}
			else if( unicode_character == 0x0401 )
			{
				byte_stream[ *byte_stream_index ] = 0xb3;
			}
			else if( unicode_character == 0x0404 )
			{
				byte_stream[ *byte_stream_index ] = 0xb4;
			}
			else if( unicode_character == 0x0406 )
			{
				byte_stream[ *byte_stream_index ] = 0xb6;
			}
			else if( unicode_character == 0x0407 )
			{
				byte_stream[ *byte_stream_index ] = 0xb7;
			}
			else if( ( unicode_character >= 0x0410 )
			      && ( unicode_character < 0x0450 ) )
			{
				unicode_character -= 0x0410;

				byte_stream[ *byte_stream_index ] = libuna_codepage_koi8_u_unicode_to_byte_stream_base_0x0410[ unicode_character ];
			}
			else if( unicode_character == 0x0451 )
			{
				byte_stream[ *byte_stream_index ] = 0xa3;
			}
			else if( unicode_character == 0x0454 )
			{
				byte_stream[ *byte_stream_index ] = 0xa4;
			}
			else if( unicode_character == 0x0456 )
			{
				byte_stream[ *byte_stream_index ] = 0xa6;
			}
			else if( unicode_character == 0x0457 )
			{
				byte_stream[ *byte_stream_index ] = 0xa7;
			}
			else if( unicode_character == 0x0490 )
			{
				byte_stream[ *byte_stream_index ] = 0xbd;
			}
			else if( unicode_character == 0x0491 )
			{
				byte_stream[ *byte_stream_index ] = 0xad;
			}
			else if( unicode_character == 0x2219 )
			{
				byte_stream[ *byte_stream_index ] = 0x95;
			}
			else if( unicode_character == 0x221a )
			{
				byte_stream[ *byte_stream_index ] = 0x96;
			}
			else if( unicode_character == 0x2248 )
			{
				byte_stream[ *byte_stream_index ] = 0x97;
			}
			else if( unicode_character == 0x2264 )
			{
				byte_stream[ *byte_stream_index ] = 0x98;
			}
			else if( unicode_character == 0x2265 )
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else if( unicode_character == 0x2320 )
			{
				byte_stream[ *byte_stream_index ] = 0x93;
			}
			else if( unicode_character == 0x2321 )
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x2500 )
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2502 )
			{
				byte_stream[ *byte_stream_index ] = 0x81;
			}
			else if( unicode_character == 0x250c )
			{
				byte_stream[ *byte_stream_index ] = 0x82;
			}
			else if( unicode_character == 0x2510 )
			{
				byte_stream[ *byte_stream_index ] = 0x83;
			}
			else if( unicode_character == 0x2514 )
			{
				byte_stream[ *byte_stream_index ] = 0x84;
			}
			else if( unicode_character == 0x2518 )
			{
				byte_stream[ *byte_stream_index ] = 0x85;
			}
			else if( unicode_character == 0x251c )
			{
				byte_stream[ *byte_stream_index ] = 0x86;
			}
			else if( unicode_character == 0x2524 )
			{
				byte_stream[ *byte_stream_index ] = 0x87;
			}
			else if( unicode_character == 0x252c )
			{
				byte_stream[ *byte_stream_index ] = 0x88;
			}
			else if( unicode_character == 0x2534 )
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x253c )
			{
				byte_stream[ *byte_stream_index ] = 0x8a;
			}
			else if( ( unicode_character >= 0x2550 )
			      && ( unicode_character < 0x2570 ) )
			{
				unicode_character -= 0x2550;

				byte_stream[ *byte_stream_index ] = libuna_codepage_koi8_u_unicode_to_byte_stream_base_0x2550[ unicode_character ];
			}
			else if( unicode_character == 0x2580 )
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x2584 )
			{
				byte_stream[ *byte_stream_index ] = 0x8c;
			}
			else if( unicode_character == 0x2588 )
			{
				byte_stream[ *byte_stream_index ] = 0x8d;
			}
			else if( unicode_character == 0x258c )
			{
				byte_stream[ *byte_stream_index ] = 0x8e;
			}
			else if( unicode_character == 0x2590 )
			{
				byte_stream[ *byte_stream_index ] = 0x8f;
			}
			else if( unicode_character == 0x2591 )
			{
				byte_stream[ *byte_stream_index ] = 0x90;
			}
			else if( unicode_character == 0x2592 )
			{
				byte_stream[ *byte_stream_index ] = 0x91;
			}
			else if( unicode_character == 0x2593 )
			{
				byte_stream[ *byte_stream_index ] = 0x92;
			}
			else if( unicode_character == 0x25a0 )
			{
				byte_stream[ *byte_stream_index ] = 0x94;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_874:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00e0 )
			      && ( unicode_character < 0x0140 ) )
			{
				unicode_character -= 0x00e0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_874_unicode_to_byte_stream_base_0x00e0[ unicode_character ];
			}
			else if( unicode_character == 0x2013 )
			{
				byte_stream[ *byte_stream_index ] = 0x96;
			}
			else if( unicode_character == 0x2014 )
			{
				byte_stream[ *byte_stream_index ] = 0x97;
			}
			else if( ( unicode_character >= 0x2018 )
			      && ( unicode_character < 0x2020 ) )
			{
				unicode_character -= 0x2018;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_874_unicode_to_byte_stream_base_0x2018[ unicode_character ];
			}
			else if( unicode_character == 0x2022 )
			{
				byte_stream[ *byte_stream_index ] = 0x95;
			}
			else if( unicode_character == 0x2026 )
			{
				byte_stream[ *byte_stream_index ] = 0x85;
			}
			else if( unicode_character == 0x20ac )
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_932:
/* TODO */
			break;

		case LIBUNA_CODEPAGE_WINDOWS_936:
/* TODO */
			break;

		case LIBUNA_CODEPAGE_WINDOWS_1250:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x0120 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0138 )
			      && ( unicode_character < 0x0180 ) )
			{
				unicode_character -= 0x0138;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x0138[ unicode_character ];
			}
			else if( unicode_character == 0x02c7 )
			{
				byte_stream[ *byte_stream_index ] = 0xa1;
			}
			else if( ( unicode_character >= 0x02d8 )
			      && ( unicode_character < 0x02e0 ) )
			{
				unicode_character -= 0x02d8;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x02d8[ unicode_character ];
			}
			else if( ( unicode_character >= 0x2010 )
			      && ( unicode_character < 0x2028 ) )
			{
				unicode_character -= 0x2010;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x2010[ unicode_character ];
			}
			else if( ( unicode_character >= 0x2030 )
			      && ( unicode_character < 0x2040 ) )
			{
				unicode_character -= 0x2030;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1250_unicode_to_byte_stream_base_0x2030[ unicode_character ];
			}
			else if( unicode_character == 0x20ac )
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2122 )
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1251:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x00c0 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1251_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( ( unicode_character >= 0x0400 )
			      && ( unicode_character < 0x0460 ) )
			{
				unicode_character -= 0x0400;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1251_unicode_to_byte_stream_base_0x0400[ unicode_character ];
			}
			else if( unicode_character == 0x0490 )
			{
				byte_stream[ *byte_stream_index ] = 0xa5;
			}
			else if( unicode_character == 0x0491 )
			{
				byte_stream[ *byte_stream_index ] = 0xb4;
			}
			else if( ( unicode_character >= 0x2010 )
			      && ( unicode_character < 0x2028 ) )
			{
				unicode_character -= 0x2010;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1251_unicode_to_byte_stream_base_0x2010[ unicode_character ];
			}
			else if( unicode_character == 0x2030 )
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x2039 )
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x203a )
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x20ac )
			{
				byte_stream[ *byte_stream_index ] = 0x88;
			}
			else if( unicode_character == 0x2116 )
			{
				byte_stream[ *byte_stream_index ] = 0xb9;
			}
			else if( unicode_character == 0x2122 )
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1252:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x0100 ) )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( unicode_character == 0x0152 )
			{
				byte_stream[ *byte_stream_index ] = 0x8c;
			}
			else if( unicode_character == 0x0153 )
			{
				byte_stream[ *byte_stream_index ] = 0x9c;
			}
			else if( unicode_character == 0x0160 )
			{
				byte_stream[ *byte_stream_index ] = 0x8a;
			}
			else if( unicode_character == 0x0161 )
			{
				byte_stream[ *byte_stream_index ] = 0x9a;
			}
			else if( unicode_character == 0x0178 )
			{
				byte_stream[ *byte_stream_index ] = 0x9f;
			}
			else if( unicode_character == 0x017d )
			{
				byte_stream[ *byte_stream_index ] = 0x8e;
			}
			else if( unicode_character == 0x017e )
			{
				byte_stream[ *byte_stream_index ] = 0x9e;
			}
			else if( unicode_character == 0x0192 )
			{
				byte_stream[ *byte_stream_index ] = 0x83;
			}
			else if( unicode_character == 0x02c6 )
			{
				byte_stream[ *byte_stream_index ] = 0x88;
			}
			else if( unicode_character == 0x02dc )
			{
				byte_stream[ *byte_stream_index ] = 0x98;
			}
			else if( ( unicode_character >= 0x2010 )
			      && ( unicode_character < 0x2028 ) )
			{
				unicode_character -= 0x2010;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1252_unicode_to_byte_stream_base_0x2010[ unicode_character ];
			}
			else if( unicode_character == 0x2030 )
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x2039 )
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x203a )
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x20ac )
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2122 )
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1253:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x00c0 ) )
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1253_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( unicode_character == 0x0192 )
			{
				byte_stream[ *byte_stream_index ] = 0x83;
			}
			else if( ( unicode_character >= 0x0380 )
			      && ( unicode_character < 0x03d0 ) )
			{
				unicode_character -= 0x0380;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1253_unicode_to_byte_stream_base_0x0380[ unicode_character ];
			}
			else if( ( unicode_character >= 0x2010 )
			      && ( unicode_character < 0x2028 ) )
			{
				unicode_character -= 0x2010;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1253_unicode_to_byte_stream_base_0x2010[ unicode_character ];
			}
			else if( unicode_character == 0x2030 )
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x2039 )
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x203a )
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x20ac )
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2122 )
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1254:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x00d0 ) )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00d0 )
			      && ( unicode_character < 0x0100 ) )
			{
				unicode_character -= 0x00d0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1254_unicode_to_byte_stream_base_0x00d0[ unicode_character ];
			}
			else if( unicode_character == 0x011e )
			{
				byte_stream[ *byte_stream_index ] = 0xd0;
			}
			else if( unicode_character == 0x011f )
			{
				byte_stream[ *byte_stream_index ] = 0xf0;
			}
			else if( unicode_character == 0x0130 )
			{
				byte_stream[ *byte_stream_index ] = 0xdd;
			}
			else if( unicode_character == 0x0131 )
			{
				byte_stream[ *byte_stream_index ] = 0xfd;
			}
			else if( unicode_character == 0x0152 )
			{
				byte_stream[ *byte_stream_index ] = 0x8c;
			}
			else if( unicode_character == 0x0153 )
			{
				byte_stream[ *byte_stream_index ] = 0x9c;
			}
			else if( unicode_character == 0x015e )
			{
				byte_stream[ *byte_stream_index ] = 0xde;
			}
			else if( unicode_character == 0x015f )
			{
				byte_stream[ *byte_stream_index ] = 0xfe;
			}
			else if( unicode_character == 0x0160 )
			{
				byte_stream[ *byte_stream_index ] = 0x8a;
			}
			else if( unicode_character == 0x0161 )
			{
				byte_stream[ *byte_stream_index ] = 0x9a;
			}
			else if( unicode_character == 0x0178 )
			{
				byte_stream[ *byte_stream_index ] = 0x9f;
			}
			else if( unicode_character == 0x0192 )
			{
				byte_stream[ *byte_stream_index ] = 0x83;
			}
			else if( unicode_character == 0x02c6 )
			{
				byte_stream[ *byte_stream_index ] = 0x88;
			}
			else if( unicode_character == 0x02dc )
			{
				byte_stream[ *byte_stream_index ] = 0x98;
			}
			else if( ( unicode_character >= 0x2010 )
			      && ( unicode_character < 0x2028 ) )
			{
				unicode_character -= 0x2010;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1254_unicode_to_byte_stream_base_0x2010[ unicode_character ];
			}
			else if( unicode_character == 0x2030 )
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x2039 )
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x203a )
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x20ac )
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2122 )
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1255:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x00c0 ) ) 
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( unicode_character == 0x00d7 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xaa;
			}
			else if( unicode_character == 0x0077 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xba;
			}
			else if( unicode_character == 0x0192 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x83;
			}
			else if( unicode_character == 0x02c6 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x88;
			}
			else if( unicode_character == 0x02dc ) 
			{
				byte_stream[ *byte_stream_index ] = 0x98;
			}
			else if( ( unicode_character >= 0x05b0 )
			      && ( unicode_character < 0x05c8 ) ) 
			{
				unicode_character -= 0x05b0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x05b0[ unicode_character ];
			}
			else if( ( unicode_character >= 0x05d0 )
			      && ( unicode_character < 0x05f8 ) ) 
			{
				unicode_character -= 0x05d0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x05d0[ unicode_character ];
			}
			else if( unicode_character == 0x200e ) 
			{
				byte_stream[ *byte_stream_index ] = 0xfd;
			}
			else if( unicode_character == 0x200f ) 
			{
				byte_stream[ *byte_stream_index ] = 0xfe;
			}
			else if( ( unicode_character >= 0x2010 )
			      && ( unicode_character < 0x2028 ) ) 
			{
				unicode_character -= 0x2010;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1255_unicode_to_byte_stream_base_0x2010[ unicode_character ];
			}
			else if( unicode_character == 0x2030 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x2039 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x203a ) 
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x20aa ) 
			{
				byte_stream[ *byte_stream_index ] = 0xa4;
			}
			else if( unicode_character == 0x20ac ) 
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2122 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1256:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x00c0 ) ) 
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( unicode_character == 0x00d7 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xd7;
			}
			else if( ( unicode_character >= 0x00e0 )
			      && ( unicode_character < 0x0100 ) ) 
			{
				unicode_character -= 0x00e0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x00e0[ unicode_character ];
			}
			else if( unicode_character == 0x0152 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8c;
			}
			else if( unicode_character == 0x0153 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x9c;
			}
			else if( unicode_character == 0x0192 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x83;
			}
			else if( unicode_character == 0x02c6 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x88;
			}
			else if( unicode_character == 0x060c ) 
			{
				byte_stream[ *byte_stream_index ] = 0xa1;
			}
			else if( ( unicode_character >= 0x0618 )
			      && ( unicode_character < 0x0658 ) ) 
			{
				unicode_character -= 0x0618;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x0618[ unicode_character ];
			}
			else if( unicode_character == 0x0679 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8a;
			}
			else if( unicode_character == 0x067e ) 
			{
				byte_stream[ *byte_stream_index ] = 0x81;
			}
			else if( unicode_character == 0x0686 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8d;
			}
			else if( unicode_character == 0x0688 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8f;
			}
			else if( unicode_character == 0x0691 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x9a;
			}
			else if( unicode_character == 0x0698 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8e;
			}
			else if( unicode_character == 0x06a9 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x98;
			}
			else if( unicode_character == 0x06af ) 
			{
				byte_stream[ *byte_stream_index ] = 0x90;
			}
			else if( unicode_character == 0x06ba ) 
			{
				byte_stream[ *byte_stream_index ] = 0x9f;
			}
			else if( unicode_character == 0x06be ) 
			{
				byte_stream[ *byte_stream_index ] = 0xaa;
			}
			else if( unicode_character == 0x06c1 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xc0;
			}
			else if( unicode_character == 0x06d2 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xff;
			}
			else if( ( unicode_character >= 0x2008 )
			      && ( unicode_character < 0x2028 ) ) 
			{
				unicode_character -= 0x2008;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1256_unicode_to_byte_stream_base_0x2008[ unicode_character ];
			}
			else if( unicode_character == 0x2030 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x2039 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x203a ) 
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x20ac ) 
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2122 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1257:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x0180 ) ) 
			{
				unicode_character -= 0x00a0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1257_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
			}
			else if( unicode_character == 0x02c7 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8e;
			}
			else if( unicode_character == 0x02d9 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xff;
			}
			else if( unicode_character == 0x02db ) 
			{
				byte_stream[ *byte_stream_index ] = 0x9e;
			}
			else if( ( unicode_character >= 0x2010 )
			      && ( unicode_character < 0x2028 ) ) 
			{
				unicode_character -= 0x2010;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1257_unicode_to_byte_stream_base_0x2010[ unicode_character ];
			}
			else if( unicode_character == 0x2030 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x2039 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x203a ) 
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x20ac ) 
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2122 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		case LIBUNA_CODEPAGE_WINDOWS_1258:
			if( unicode_character < 0x0080 )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00a0 )
			      && ( unicode_character < 0x00c0 ) )
			{
				byte_stream[ *byte_stream_index ] = (uint8_t) unicode_character;
			}
			else if( ( unicode_character >= 0x00c0 )
			      && ( unicode_character < 0x0108 ) ) 
			{
				unicode_character -= 0x00c0;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1258_unicode_to_byte_stream_base_0x00c0[ unicode_character ];
			}
			else if( unicode_character == 0x0110 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xd0;
			}
			else if( unicode_character == 0x0111 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xf0;
			}
			else if( unicode_character == 0x0152 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8c;
			}
			else if( unicode_character == 0x0153 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x9c;
			}
			else if( unicode_character == 0x01af ) 
			{
				byte_stream[ *byte_stream_index ] = 0xdd;
			}
			else if( unicode_character == 0x01b0 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xfd;
			}
			else if( unicode_character == 0x02c6 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x88;
			}
			else if( unicode_character == 0x02dc ) 
			{
				byte_stream[ *byte_stream_index ] = 0x98;
			}
			else if( unicode_character == 0x0300 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xcc;
			}
			else if( unicode_character == 0x0301 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xec;
			}
			else if( unicode_character == 0x0303 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xde;
			}
			else if( unicode_character == 0x0309 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xd2;
			}
			else if( unicode_character == 0x0323 ) 
			{
				byte_stream[ *byte_stream_index ] = 0xf2;
			}
			else if( ( unicode_character >= 0x2010 )
			      && ( unicode_character < 0x2028 ) ) 
			{
				unicode_character -= 0x2010;

				byte_stream[ *byte_stream_index ] = libuna_codepage_windows_1258_unicode_to_byte_stream_base_0x2010[ unicode_character ];
			}
			else if( unicode_character == 0x2030 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x89;
			}
			else if( unicode_character == 0x2039 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x8b;
			}
			else if( unicode_character == 0x203a ) 
			{
				byte_stream[ *byte_stream_index ] = 0x9b;
			}
			else if( unicode_character == 0x20ab ) 
			{
				byte_stream[ *byte_stream_index ] = 0xfe;
			}
			else if( unicode_character == 0x20ac ) 
			{
				byte_stream[ *byte_stream_index ] = 0x80;
			}
			else if( unicode_character == 0x2122 ) 
			{
				byte_stream[ *byte_stream_index ] = 0x99;
			}
			else
			{
				byte_stream[ *byte_stream_index ] = 0x1a;
			}
			*byte_stream_index += 1;

			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			"%s: unsupported codepage: %d.",
			 function,
		         codepage );

			return( -1 );
	}
	return( 1 );
}

/* Determines the size of an UTF-7 stream character from an Unicode character
 * Adds the size to the UTF-7 stream character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_size_to_utf7_stream(
     libuna_unicode_character_t unicode_character,
     size_t *utf7_stream_character_size,
     uint32_t *utf7_stream_base64_data,
     libcerror_error_t **error )
{
	libuna_utf16_character_t utf16_surrogate = 0;
	static char *function                    = "libuna_unicode_character_size_to_utf7_stream";
	uint8_t base64_encode_character          = 0;
	uint32_t base64_triplet                  = 0;
	uint8_t number_of_bytes                  = 0;
	uint8_t current_byte                     = 0;
	uint8_t byte_bit_shift                   = 0;

	if( utf7_stream_character_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream character size.",
		 function );

		return( -1 );
	}
	if( utf7_stream_base64_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream base64 data.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	/* A-Z is not a continous range on a EBCDIC based system
	 * it consists of the ranges: A-I, J-R, S-Z
	 */
	if( ( unicode_character >= 0x41 )
	 && ( unicode_character <= 0x49 ) )
	{
	}
	else if( ( unicode_character >= 0x4a )
	      && ( unicode_character <= 0x52 ) )
	{
	}
	else if( ( unicode_character >= 0x53 )
	      && ( unicode_character <= 0x5a ) )
	{
	}
	/* a-z is not a continous range on a EBCDIC based system
	 * it consists of the ranges: a-i, j-r, s-z
	 */
	else if( ( unicode_character >= 0x61 )
	      && ( unicode_character <= 0x69 ) )
	{
	}
	else if( ( unicode_character >= 0x6a )
	      && ( unicode_character <= 0x72 ) )
	{
	}
	else if( ( unicode_character >= 0x73 )
	      && ( unicode_character <= 0x7a ) )
	{
	}
	/* 0-9
	 */
	else if( ( unicode_character >= 0x30 )
	      && ( unicode_character <= 0x39 ) )
	{
	}
	/* Valid directly encoded whitespace
	 */
	else if( ( unicode_character == (libuna_unicode_character_t) '\t' )
	      || ( unicode_character == (libuna_unicode_character_t) '\n' )
	      || ( unicode_character == (libuna_unicode_character_t) '\r' )
	      || ( unicode_character == (libuna_unicode_character_t) ' ' ) )
	{
	}
	/* The + character must be escaped
	 */
	else if( unicode_character == (libuna_unicode_character_t) '+' )
	{
	}
	/* Valid directly encoded characters
	 */
	else if( ( unicode_character == (libuna_unicode_character_t) '\'' )
	      || ( unicode_character == (libuna_unicode_character_t) '(' )
	      || ( unicode_character == (libuna_unicode_character_t) ')' )
	      || ( unicode_character == (libuna_unicode_character_t) ',' )
	      || ( unicode_character == (libuna_unicode_character_t) '-' )
	      || ( unicode_character == (libuna_unicode_character_t) '.' )
	      || ( unicode_character == (libuna_unicode_character_t) '/' )
	      || ( unicode_character == (libuna_unicode_character_t) ':' )
	      || ( unicode_character == (libuna_unicode_character_t) '?' ) )
	{
	}
	/* Valid optional directly encoded characters
	 */
	else if( ( unicode_character == (libuna_unicode_character_t) '!' )
	      || ( unicode_character == (libuna_unicode_character_t) '"' )
	      || ( unicode_character == (libuna_unicode_character_t) '#' )
	      || ( unicode_character == (libuna_unicode_character_t) '$' )
	      || ( unicode_character == (libuna_unicode_character_t) '%' )
	      || ( unicode_character == (libuna_unicode_character_t) '&' )
	      || ( unicode_character == (libuna_unicode_character_t) '*' )
	      || ( unicode_character == (libuna_unicode_character_t) ';' )
	      || ( unicode_character == (libuna_unicode_character_t) '<' )
	      || ( unicode_character == (libuna_unicode_character_t) '=' )
	      || ( unicode_character == (libuna_unicode_character_t) '>' )
	      || ( unicode_character == (libuna_unicode_character_t) '@' )
	      || ( unicode_character == (libuna_unicode_character_t) '[' )
	      || ( unicode_character == (libuna_unicode_character_t) ']' )
	      || ( unicode_character == (libuna_unicode_character_t) '^' )
	      || ( unicode_character == (libuna_unicode_character_t) '_' )
	      || ( unicode_character == (libuna_unicode_character_t) '`' )
	      || ( unicode_character == (libuna_unicode_character_t) '{' )
	      || ( unicode_character == (libuna_unicode_character_t) '|' )
	      || ( unicode_character == (libuna_unicode_character_t) '}' ) )
	{
	}
	/* Allow for the end of string character
	 */
	else if( unicode_character == 0 )
	{
	}
	else
	{
		base64_encode_character = 1;
	}
	if( base64_encode_character == 0 )
	{
		if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) != 0 )
		{
			*utf7_stream_base64_data = 0;
		}
		*utf7_stream_character_size += 1;

		/* The + character must be escaped
		 */
		if( unicode_character == (libuna_unicode_character_t) '+' )
		{
			*utf7_stream_character_size += 1;
		}
	}
	else
	{
		/* Escape the base64 encoded characters with a +
		 */
		if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) == 0 )
		{
			*utf7_stream_character_size += 1;
		}
		/* Otherwise continue the previously base64 encoded characters
		 */
		else
		{
			base64_triplet  = *utf7_stream_base64_data & 0x00ffffff;
			number_of_bytes = ( *utf7_stream_base64_data >> 24 ) & 0x03;
			current_byte    = ( *utf7_stream_base64_data >> 28 ) & 0x03;

			if( number_of_bytes > 0 )
			{
				if( *utf7_stream_character_size < (size_t) ( number_of_bytes + 1 ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid UTF-7 stream character size value out of bounds.",
					 function );

					return( -1 );
				}
				/* Correct the size for the last partial base64 stream
				 */
				*utf7_stream_character_size -= number_of_bytes + 1;
			}
			if( *utf7_stream_character_size < 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid UTF-7 stream character size value out of bounds.",
				 function );

				return( -1 );
			}
			/* Correct the size for the base64 stream termination character
			 */
			*utf7_stream_character_size -= 1;
		}
		*utf7_stream_base64_data = LIBUNA_UTF7_IS_BASE64_ENCODED;

		if( unicode_character > LIBUNA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
		{
			unicode_character -= 0x010000;

			utf16_surrogate = (libuna_utf16_character_t) ( ( unicode_character >> 10 ) + LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START );

			byte_bit_shift   = 16 - ( current_byte * 8 );
			base64_triplet  += (uint32_t) ( ( utf16_surrogate >> 8 ) & 0xff ) << byte_bit_shift;
			current_byte    += 1;
			number_of_bytes += 1;

			if( number_of_bytes == 3 )
			{
				*utf7_stream_character_size += 4;
				number_of_bytes              = 0;
				current_byte                 = 0;
				base64_triplet               = 0;
			}
			byte_bit_shift   = 16 - ( current_byte * 8 );
			base64_triplet  += (uint32_t) ( utf16_surrogate & 0xff ) << byte_bit_shift;
			current_byte    += 1;
			number_of_bytes += 1;

			if( number_of_bytes == 3 )
			{
				*utf7_stream_character_size += 4;
				number_of_bytes              = 0;
				current_byte                 = 0;
				base64_triplet               = 0;
			}
			unicode_character = (libuna_utf16_character_t) ( ( unicode_character & 0x03ff ) + LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START );
		}
		byte_bit_shift   = 16 - ( current_byte * 8 );
		base64_triplet  += (uint32_t) ( ( unicode_character >> 8 ) & 0xff ) << byte_bit_shift;
		current_byte    += 1;
		number_of_bytes += 1;

		if( number_of_bytes == 3 )
		{
			*utf7_stream_character_size += 4;
			number_of_bytes              = 0;
			current_byte                 = 0;
			base64_triplet               = 0;
		}
		byte_bit_shift   = 16 - ( current_byte * 8 );
		base64_triplet  += (uint32_t) ( unicode_character & 0xff ) << byte_bit_shift;
		current_byte    += 1;
		number_of_bytes += 1;

		if( number_of_bytes == 3 )
		{
			*utf7_stream_character_size += 4;
			number_of_bytes              = 0;
			current_byte                 = 0;
			base64_triplet               = 0;
		}
		/* Terminate the base64 encoded characters
		 */
		if( number_of_bytes > 0 )
		{
			*utf7_stream_character_size += number_of_bytes + 1;
		}
		*utf7_stream_character_size += 1;
	}
	if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) != 0 )
	{
		*utf7_stream_base64_data  = LIBUNA_UTF7_IS_BASE64_ENCODED;
		*utf7_stream_base64_data |= (uint32_t) current_byte << 28;
		*utf7_stream_base64_data |= (uint32_t) number_of_bytes << 24;
		*utf7_stream_base64_data |= base64_triplet & 0x00ffffff;
	}
	return( 1 );
}

/* Copies a Unicode character from an UTF-7 stream
 * The bits of the base64 data contain:
 *   0 - 23 the base64 triplet
 *  24 - 25 the number of bytes in the triplet
 *  26 - 27 unused
 *  28 - 29 the current byte
 *       30 unused
 *       31 flag to indicate the current UTF-7 characters are (modified) base64 encoded
 *
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_from_utf7_stream(
     libuna_unicode_character_t *unicode_character,
     const uint8_t *utf7_stream,
     size_t utf7_stream_size,
     size_t *utf7_stream_index,
     uint32_t *utf7_stream_base64_data,
     libcerror_error_t **error )
{
	static char *function                    = "libuna_unicode_character_copy_from_utf7_stream";
	libuna_utf16_character_t utf16_surrogate = 0;
	uint32_t base64_triplet                  = 0;
	uint8_t number_of_bytes                  = 0;
	uint8_t current_byte                     = 0;
	uint8_t padding_size                     = 0;
	uint8_t byte_bit_shift                   = 0;

	if( unicode_character == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf7_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream.",
		 function );

		return( -1 );
	}
	if( utf7_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-7 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf7_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream index.",
		 function );

		return( -1 );
	}
	if( *utf7_stream_index >= utf7_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-7 stream too small.",
		 function );

		return( -1 );
	}
	if( utf7_stream_base64_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 base64 data.",
		 function );

		return( -1 );
	}
	if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) != 0 )
	{
		base64_triplet  = *utf7_stream_base64_data & 0x00ffffff;
		number_of_bytes = ( *utf7_stream_base64_data >> 24 ) & 0x03;
		current_byte    = ( *utf7_stream_base64_data >> 28 ) & 0x03;

		if( current_byte >= number_of_bytes )
		{
			/* A-Z is not a continous range on a EBCDIC based system
			 * it consists of the ranges: A-I, J-R, S-Z
			 */
			if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'A' )
			 && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'I' ) )
			{
			}
			else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'J' )
			      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'R' ) )
			{
			}
			else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'S' )
			      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'Z' ) )
			{
			}
			/* a-z is not a continous range on a EBCDIC based system
			 * it consists of the ranges: a-i, j-r, s-z
			 */
			else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'a' )
			      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'i' ) )
			{
			}
			else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'j' )
			      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'r' ) )
			{
			}
			else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 's' )
			      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'z' ) )
			{
			}
			/* 0-9
			 */
			else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) '0' )
			      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) '9' ) )
			{
			}
			/* + or /
			 */
			else if( ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '+' )
			      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '/' ) )
			{
			}
			/* Any character not in the modified base64 alphabet
			 * terminates the base64 encoded sequence
			 */
			else
			{
				*utf7_stream_base64_data = 0;
			}
		}
	}
	if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) == 0 )
	{
		/* Determine if the character is modified base64 encoded
		 * or a + character
		 */
		if( utf7_stream[ *utf7_stream_index ] == (uint8_t) '+' )
		{
			if( utf7_stream[ *utf7_stream_index + 1 ] != (uint8_t) '-' )
			{
				*utf7_stream_base64_data = LIBUNA_UTF7_IS_BASE64_ENCODED;

				*utf7_stream_index += 1;
			}
		}
		/* A-Z is not a continous range on a EBCDIC based system
		 * it consists of the ranges: A-I, J-R, S-Z
		 */
		else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'A' )
		      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'I' ) )
		{
		}
		else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'J' )
		      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'R' ) )
		{
		}
		else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'S' )
		      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'Z' ) )
		{
		}
		/* a-z is not a continous range on a EBCDIC based system
		 * it consists of the ranges: a-i, j-r, s-z
		 */
		else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'a' )
		      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'i' ) )
		{
		}
		else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 'j' )
		      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'r' ) )
		{
		}
		else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) 's' )
		      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) 'z' ) )
		{
		}
		/* 0-9
		 */
		else if( ( utf7_stream[ *utf7_stream_index ] >= (uint8_t) '0' )
		      && ( utf7_stream[ *utf7_stream_index ] <= (uint8_t) '9' ) )
		{
		}
		/* Valid directly encoded whitespace
		 */
		else if( ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '\t' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '\n' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '\r' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) ' ' ) )
		{
		}
		/* Valid directly encoded characters
		 */
		else if( ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '\'' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '(' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) ')' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) ',' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '-' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '.' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '/' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) ':' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '?' ) )
		{
		}
		/* Valid optional directly encoded characters
		 */
		else if( ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '!' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '"' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '#' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '$' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '%' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '&' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '*' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) ';' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '<' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '=' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '>' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '@' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '[' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) ']' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '^' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '_' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '`' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '{' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '|' )
		      || ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '}' ) )
		{
		}
		/* Allow for the end of string character
		 */
		else if( utf7_stream[ *utf7_stream_index ] == 0 )
		{
		}
		else
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid directly encoded UTF-7 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf7_stream[ *utf7_stream_index ] );

			return( -1 );
		}
	}
	if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) == 0 )
	{
		*unicode_character  = utf7_stream[ *utf7_stream_index ];
		*utf7_stream_index += 1;

		if( ( *unicode_character == (libuna_unicode_character_t) '+' )
		 && ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '-' ) )
		{
			*utf7_stream_index += 1;
		}
	}
	else if( ( number_of_bytes == 0 )
	      || ( current_byte >= number_of_bytes ) )
	{
		if( libuna_base64_triplet_copy_from_base64_stream(
		     &base64_triplet,
		     utf7_stream,
		     utf7_stream_size,
		     utf7_stream_index,
		     &padding_size,
		     LIBUNA_BASE64_VARIANT_UTF7,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
			 "%s: unable to copy base64 encoded UTF-7 characters.",
			 function );

			return( -1 );
		}
		if( padding_size > 2 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported padding in base64 encoded UTF-7 characters.",
			 function );

			return( -1 );
		}
		number_of_bytes = 3 - padding_size;
		current_byte    = 0;
	}
	if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) != 0 )
	{
		byte_bit_shift     = 16 - ( current_byte * 8 );
		*unicode_character = ( ( base64_triplet >> byte_bit_shift ) & 0x000000ffUL ) << 8;
		current_byte      += 1;

		if( current_byte >= number_of_bytes )
		{
			if( libuna_base64_triplet_copy_from_base64_stream(
			     &base64_triplet,
			     utf7_stream,
			     utf7_stream_size,
			     utf7_stream_index,
			     &padding_size,
			     LIBUNA_BASE64_VARIANT_UTF7,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_CONVERSION,
				 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
				 "%s: unable to copy base64 encoded UTF-7 characters.",
				 function );

				return( -1 );
			}
			if( padding_size > 2 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported padding in base64 encoded UTF-7 characters.",
				 function );

				return( -1 );
			}
			number_of_bytes = 3 - padding_size;
			current_byte    = 0;
		}
		byte_bit_shift      = 16 - ( current_byte * 8 );
		*unicode_character += ( base64_triplet >> byte_bit_shift ) & 0x000000ffUL;
		current_byte       += 1;

		if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
		 && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_END ) )
		{
			if( current_byte >= number_of_bytes )
			{
				if( libuna_base64_triplet_copy_from_base64_stream(
				     &base64_triplet,
				     utf7_stream,
				     utf7_stream_size,
				     utf7_stream_index,
				     &padding_size,
				     LIBUNA_BASE64_VARIANT_UTF7,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_CONVERSION,
					 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
					 "%s: unable to copy base64 encoded UTF-7 characters.",
					 function );

					return( -1 );
				}
				if( padding_size > 2 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
					 "%s: unsupported padding in base64 encoded UTF-7 characters.",
					 function );

					return( -1 );
				}
				number_of_bytes = 3 - padding_size;
				current_byte    = 0;
			}
			byte_bit_shift  = 16 - ( current_byte * 8 );
			utf16_surrogate = ( ( base64_triplet >> byte_bit_shift ) & 0x000000ffUL ) << 8;
			current_byte   += 1;

			if( current_byte >= number_of_bytes )
			{
				if( libuna_base64_triplet_copy_from_base64_stream(
				     &base64_triplet,
				     utf7_stream,
				     utf7_stream_size,
				     utf7_stream_index,
				     &padding_size,
				     LIBUNA_BASE64_VARIANT_UTF7,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve base64 encoded UTF-7 characters.",
					 function );

					return( -1 );
				}
				if( padding_size > 2 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
					 "%s: unsupported padding in base64 encoded UTF-7 characters.",
					 function );

					return( -1 );
				}
				number_of_bytes = 3 - padding_size;
				current_byte    = 0;
			}
			byte_bit_shift   = 16 - ( current_byte * 8 );
			utf16_surrogate += ( base64_triplet >> byte_bit_shift ) & 0x000000ffUL;
			current_byte    += 1;

			/* Determine if the UTF-16 character is within the low surrogate range
			 */
			if( ( utf16_surrogate >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
			 && ( utf16_surrogate <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
			{
				*unicode_character  -= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START;
				*unicode_character <<= 10;
				*unicode_character  += utf16_surrogate - LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END;
				*unicode_character  += 0x010000;
			}
			else
			{
				*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
			}
		}
		if( *utf7_stream_index >= utf7_stream_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-7 stream too small.",
			 function );

			return( -1 );
		}
		if( ( current_byte >= number_of_bytes )
		 && ( utf7_stream[ *utf7_stream_index ] == (uint8_t) '-' ) )
		{
			*utf7_stream_base64_data = 0;
			*utf7_stream_index      += 1;
		}
	}
	if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) != 0 )
	{
		*utf7_stream_base64_data  = LIBUNA_UTF7_IS_BASE64_ENCODED;
		*utf7_stream_base64_data |= (uint32_t) current_byte << 28;
		*utf7_stream_base64_data |= (uint32_t) number_of_bytes << 24;
		*utf7_stream_base64_data |= base64_triplet & 0x00ffffff;
	}
	return( 1 );
}

/* Copies a Unicode character into a UTF-7 stream
 * The bits of the base64 data contain:
 *   0 - 23 the base64 triplet
 *  24 - 25 the number of bytes in the triplet
 *  26 - 27 unused
 *  28 - 29 the current byte
 *       30 unused
 *       31 flag to indicate the current UTF-7 characters are (modified) base64 encoded
 *
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_to_utf7_stream(
     libuna_unicode_character_t unicode_character,
     uint8_t *utf7_stream,
     size_t utf7_stream_size,
     size_t *utf7_stream_index,
     uint32_t *utf7_stream_base64_data,
     libcerror_error_t **error )
{
	static char *function                    = "libuna_unicode_character_copy_to_utf7_stream";
	libuna_utf16_character_t utf16_surrogate = 0;
	uint32_t base64_triplet                  = 0;
	uint8_t number_of_bytes                  = 0;
	uint8_t base64_encode_character          = 0;
	uint8_t current_byte                     = 0;
	uint8_t byte_bit_shift                   = 0;

	if( utf7_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream.",
		 function );

		return( -1 );
	}
	if( utf7_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-7 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf7_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream index.",
		 function );

		return( -1 );
	}
	if( utf7_stream_base64_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-7 stream base64 data.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	/* A-Z is not a continous range on a EBCDIC based system
	 * it consists of the ranges: A-I, J-R, S-Z
	 */
	if( ( unicode_character >= 0x41 )
	 && ( unicode_character <= 0x49 ) )
	{
		unicode_character = ( unicode_character - 0x41 ) + (libuna_unicode_character_t) 'A';
	}
	else if( ( unicode_character >= 0x4a )
	      && ( unicode_character <= 0x52 ) )
	{
		unicode_character = ( unicode_character - 0x4a ) + (libuna_unicode_character_t) 'J';
	}
	else if( ( unicode_character >= 0x53 )
	      && ( unicode_character <= 0x5a ) )
	{
		unicode_character = ( unicode_character - 0x53 ) + (libuna_unicode_character_t) 'S';
	}
	/* a-z is not a continous range on a EBCDIC based system
	 * it consists of the ranges: a-i, j-r, s-z
	 */
	else if( ( unicode_character >= 0x61 )
	      && ( unicode_character <= 0x69 ) )
	{
		unicode_character = ( unicode_character - 0x61 ) + (libuna_unicode_character_t) 'a';
	}
	else if( ( unicode_character >= 0x6a )
	      && ( unicode_character <= 0x72 ) )
	{
		unicode_character = ( unicode_character - 0x6a ) + (libuna_unicode_character_t) 'j';
	}
	else if( ( unicode_character >= 0x73 )
	      && ( unicode_character <= 0x7a ) )
	{
		unicode_character = ( unicode_character - 0x73 ) + (libuna_unicode_character_t) 's';
	}
	/* 0-9
	 */
	else if( ( unicode_character >= 0x30 )
	      && ( unicode_character <= 0x39 ) )
	{
		unicode_character = ( unicode_character - 0x30 ) + (libuna_unicode_character_t) '0';
	}
	/* Valid directly encoded whitespace
	 */
	else if( ( unicode_character == (libuna_unicode_character_t) '\t' )
	      || ( unicode_character == (libuna_unicode_character_t) '\n' )
	      || ( unicode_character == (libuna_unicode_character_t) '\r' )
	      || ( unicode_character == (libuna_unicode_character_t) ' ' ) )
	{
	}
	/* The + character must be escaped
	 */
	else if( unicode_character == (libuna_unicode_character_t) '+' )
	{
	}
	/* Valid directly encoded characters
	 */
	else if( ( unicode_character == (libuna_unicode_character_t) '\'' )
	      || ( unicode_character == (libuna_unicode_character_t) '(' )
	      || ( unicode_character == (libuna_unicode_character_t) ')' )
	      || ( unicode_character == (libuna_unicode_character_t) ',' )
	      || ( unicode_character == (libuna_unicode_character_t) '-' )
	      || ( unicode_character == (libuna_unicode_character_t) '.' )
	      || ( unicode_character == (libuna_unicode_character_t) '/' )
	      || ( unicode_character == (libuna_unicode_character_t) ':' )
	      || ( unicode_character == (libuna_unicode_character_t) '?' ) )
	{
	}
	/* Valid optional directly encoded characters
	 */
	else if( ( unicode_character == (libuna_unicode_character_t) '!' )
	      || ( unicode_character == (libuna_unicode_character_t) '"' )
	      || ( unicode_character == (libuna_unicode_character_t) '#' )
	      || ( unicode_character == (libuna_unicode_character_t) '$' )
	      || ( unicode_character == (libuna_unicode_character_t) '%' )
	      || ( unicode_character == (libuna_unicode_character_t) '&' )
	      || ( unicode_character == (libuna_unicode_character_t) '*' )
	      || ( unicode_character == (libuna_unicode_character_t) ';' )
	      || ( unicode_character == (libuna_unicode_character_t) '<' )
	      || ( unicode_character == (libuna_unicode_character_t) '=' )
	      || ( unicode_character == (libuna_unicode_character_t) '>' )
	      || ( unicode_character == (libuna_unicode_character_t) '@' )
	      || ( unicode_character == (libuna_unicode_character_t) '[' )
	      || ( unicode_character == (libuna_unicode_character_t) ']' )
	      || ( unicode_character == (libuna_unicode_character_t) '^' )
	      || ( unicode_character == (libuna_unicode_character_t) '_' )
	      || ( unicode_character == (libuna_unicode_character_t) '`' )
	      || ( unicode_character == (libuna_unicode_character_t) '{' )
	      || ( unicode_character == (libuna_unicode_character_t) '|' )
	      || ( unicode_character == (libuna_unicode_character_t) '}' ) )
	{
	}
	/* Allow for the end of string character
	 */
	else if( unicode_character == 0 )
	{
	}
	else
	{
		base64_encode_character = 1;
	}
	if( base64_encode_character == 0 )
	{
		if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) != 0 )
		{
			*utf7_stream_base64_data = 0;
		}
		if( *utf7_stream_index >= utf7_stream_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-7 stream too small.",
			 function );

			return( -1 );
		}
		utf7_stream[ *utf7_stream_index ] = (uint8_t) unicode_character;

		*utf7_stream_index += 1;

		/* The + character must be escaped
		 */
		if( unicode_character == (libuna_unicode_character_t) '+' )
		{
			if( *utf7_stream_index >= utf7_stream_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-7 stream too small.",
				 function );

				return( -1 );
			}
			utf7_stream[ *utf7_stream_index ] = (uint8_t) '-';

			*utf7_stream_index += 1;
		}
	}
	else
	{
		/* Escape the base64 encoded chracters with a +
		 */
		if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) == 0 )
		{
			if( *utf7_stream_index >= utf7_stream_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-7 stream too small.",
				 function );

				return( -1 );
			}
			utf7_stream[ *utf7_stream_index ] = (uint8_t) '+';

			*utf7_stream_index += 1;
		}
		/* Otherwise continue the previously base64 encoded characters
		 */
		else
		{
			base64_triplet  = *utf7_stream_base64_data & 0x00ffffff;
			number_of_bytes = ( *utf7_stream_base64_data >> 24 ) & 0x03;
			current_byte    = ( *utf7_stream_base64_data >> 28 ) & 0x03;

			if( number_of_bytes > 0 )
			{
				/* Correct the index for the last partial base64 stream
				 */
				*utf7_stream_index -= number_of_bytes + 1;
			}
			/* Correct the index for the base64 stream termination character
			 */
			*utf7_stream_index -= 1;
		}
		*utf7_stream_base64_data = LIBUNA_UTF7_IS_BASE64_ENCODED;

		if( unicode_character > LIBUNA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
		{
			unicode_character -= 0x010000;

			utf16_surrogate = (libuna_utf16_character_t) ( ( unicode_character >> 10 )
			                + LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START );

			byte_bit_shift   = 16 - ( current_byte * 8 );
			base64_triplet  += (uint32_t) ( ( utf16_surrogate >> 8 ) & 0xff ) << byte_bit_shift;
			current_byte    += 1;
			number_of_bytes += 1;

			if( number_of_bytes == 3 )
			{
				if( libuna_base64_triplet_copy_to_base64_stream(
				     base64_triplet,
				     utf7_stream,
				     utf7_stream_size,
				     utf7_stream_index,
				     0,
				     LIBUNA_BASE64_VARIANT_UTF7,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set base64 encoded UTF-7 characters.",
					 function );

					return( -1 );
				}
				number_of_bytes = 0;
				current_byte    = 0;
				base64_triplet  = 0;
			}
			byte_bit_shift   = 16 - ( current_byte * 8 );
			base64_triplet  += (uint32_t) ( utf16_surrogate & 0xff ) << byte_bit_shift;
			current_byte    += 1;
			number_of_bytes += 1;

			if( number_of_bytes == 3 )
			{
				if( libuna_base64_triplet_copy_to_base64_stream(
				     base64_triplet,
				     utf7_stream,
				     utf7_stream_size,
				     utf7_stream_index,
				     0,
				     LIBUNA_BASE64_VARIANT_UTF7,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set base64 encoded UTF-7 characters.",
					 function );

					return( -1 );
				}
				number_of_bytes = 0;
				current_byte    = 0;
				base64_triplet  = 0;
			}
			unicode_character = (libuna_utf16_character_t) ( ( unicode_character & 0x03ff )
			                  + LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START );
		}
		byte_bit_shift   = 16 - ( current_byte * 8 );
		base64_triplet  += (uint32_t) ( ( unicode_character >> 8 ) & 0xff ) << byte_bit_shift;
		current_byte    += 1;
		number_of_bytes += 1;

		if( number_of_bytes == 3 )
		{
			if( libuna_base64_triplet_copy_to_base64_stream(
			     base64_triplet,
			     utf7_stream,
			     utf7_stream_size,
			     utf7_stream_index,
			     0,
			     LIBUNA_BASE64_VARIANT_UTF7,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set base64 encoded UTF-7 characters.",
				 function );

				return( -1 );
			}
			number_of_bytes = 0;
			current_byte    = 0;
			base64_triplet  = 0;
		}
		byte_bit_shift   = 16 - ( current_byte * 8 );
		base64_triplet  += (uint32_t) ( unicode_character & 0xff ) << byte_bit_shift;
		current_byte    += 1;
		number_of_bytes += 1;

		if( number_of_bytes == 3 )
		{
			if( libuna_base64_triplet_copy_to_base64_stream(
			     base64_triplet,
			     utf7_stream,
			     utf7_stream_size,
			     utf7_stream_index,
			     0,
			     LIBUNA_BASE64_VARIANT_UTF7,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set base64 encoded UTF-7 characters.",
				 function );

				return( -1 );
			}
			number_of_bytes = 0;
			current_byte    = 0;
			base64_triplet  = 0;
		}
		/* Terminate the base64 encoded characters
		 */
		if( number_of_bytes > 0 )
		{
			if( libuna_base64_triplet_copy_to_base64_stream(
			     base64_triplet,
			     utf7_stream,
			     utf7_stream_size,
			     utf7_stream_index,
			     3 - number_of_bytes,
			     LIBUNA_BASE64_VARIANT_UTF7,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set base64 encoded UTF-7 characters.",
				 function );

				return( -1 );
			}
		}
		if( *utf7_stream_index >= utf7_stream_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-7 stream too small.",
			 function );

			return( -1 );
		}
		utf7_stream[ *utf7_stream_index ] = (uint8_t) '-';

		*utf7_stream_index += 1;
	}
	if( ( *utf7_stream_base64_data & LIBUNA_UTF7_IS_BASE64_ENCODED ) != 0 )
	{
		*utf7_stream_base64_data  = LIBUNA_UTF7_IS_BASE64_ENCODED;
		*utf7_stream_base64_data |= (uint32_t) current_byte << 28;
		*utf7_stream_base64_data |= (uint32_t) number_of_bytes << 24;
		*utf7_stream_base64_data |= base64_triplet & 0x00ffffff;
	}
	return( 1 );
}

/* Determines the size of an UTF-8 character from an Unicode character
 * Adds the size to the UTF-8 character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_size_to_utf8(
     libuna_unicode_character_t unicode_character,
     size_t *utf8_character_size,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_size_to_utf8";

	if( utf8_character_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 character size.",
		 function );

		return( -1 );
	}
	if( unicode_character < 0x080 )
	{
		*utf8_character_size += 1;
	}
	else if( unicode_character < 0x0800 )
	{
		*utf8_character_size += 2;
	}
	else if( unicode_character < 0x010000 )
	{
		*utf8_character_size += 3;
	}
	else if( unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		*utf8_character_size += 3;
	}
	else
	{
		*utf8_character_size += 4;
	}

/* If UTF-8 USC support is needed it should be implemented in
 * utf8_usc or something, but for now leave this here as a reminder

	else if( unicode_character < 0x010000 )
	{
		*utf8_character_size += 3;
	}
	else if( unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		*utf8_character_size += 2;
	}
	else if( unicode_character < 0x0200000 )
	{
		*utf8_character_size += 4;
	}
	else if( unicode_character < 0x0400000 )
	{
		*utf8_character_size += 5;
	}
	else
	{
		*utf8_character_size += 6;
	}
*/
	return( 1 );
}

/* Copies a Unicode character from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_from_utf8(
     libuna_unicode_character_t *unicode_character,
     const libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	static char *function                   = "libuna_unicode_character_copy_from_utf8";
	uint8_t utf8_character_additional_bytes = 0;

	if( unicode_character == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	if( *utf8_string_index >= utf8_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string too small.",
		 function );

		return( -1 );
	}
	/* Determine the number of additional bytes of the UTF-8 character
	 */
	if( utf8_string[ *utf8_string_index ] < 0xc0 )
	{
		utf8_character_additional_bytes = 0;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xe0 )
	{
		utf8_character_additional_bytes = 1;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xf0 )
	{
		utf8_character_additional_bytes = 2;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xf8 )
	{
		utf8_character_additional_bytes = 3;
	}
	else if( utf8_string[ *utf8_string_index ] < 0xfc )
	{
		utf8_character_additional_bytes = 4;
	}
	else
	{
		utf8_character_additional_bytes = 5;
	}
	if( ( *utf8_string_index + utf8_character_additional_bytes + 1 ) > utf8_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-8 character bytes.",
		 function );

		return( -1 );
	}
	/* Determine the UTF-8 character and make sure it is valid
	 * Unicode limits the UTF-8 character to consist of a maximum of 4 bytes
	 * while ISO 10646 Universal Character Set (UCS) allows up to 6 bytes
	 */
	if( utf8_string[ *utf8_string_index ] > 0xf4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid 1st UTF-8 character byte: 0x%02" PRIx8 ".",
		 function,
		 utf8_string[ *utf8_string_index ] );

		return( -1 );
	}
	*unicode_character = utf8_string[ *utf8_string_index ];

	if( utf8_character_additional_bytes == 0 )
	{
		if( ( utf8_string[ *utf8_string_index ] >= 0x80 )
		 && ( utf8_string[ *utf8_string_index ] < 0xc2 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 1st UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index ] );

			return( -1 );
		}
	}
	if( utf8_character_additional_bytes >= 1 )
	{
		if( utf8_string[ *utf8_string_index + 1 ] > 0xbf )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		if( ( utf8_string[ *utf8_string_index ] == 0xe0 )
		 && ( utf8_string[ *utf8_string_index + 1 ] < 0xa0 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		else if( ( utf8_string[ *utf8_string_index ] == 0xed )
		      && ( utf8_string[ *utf8_string_index + 1 ] > 0x9f ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		else if( ( utf8_string[ *utf8_string_index ] == 0xf0 )
		      && ( utf8_string[ *utf8_string_index + 1 ] < 0x90 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		else if( ( utf8_string[ *utf8_string_index ] == 0xf4 )
		      && ( utf8_string[ *utf8_string_index + 1 ] > 0x8f ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		else if( utf8_string[ *utf8_string_index + 1 ] < 0x80 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 2nd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 1 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 1 ];

		if( utf8_character_additional_bytes == 1 )
		{
			*unicode_character -= 0x03080;
		}
	}
	if( utf8_character_additional_bytes >= 2 )
	{
		if( ( utf8_string[ *utf8_string_index + 2 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 2 ] > 0xbf ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 3rd UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 2 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 2 ];

		if( utf8_character_additional_bytes == 2 )
		{
			*unicode_character -= 0x0e2080;
		}
	}
	if( utf8_character_additional_bytes >= 3 )
	{
		if( ( utf8_string[ *utf8_string_index + 3 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 3 ] > 0xbf ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 4th UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 3 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 3 ];

		if( utf8_character_additional_bytes == 3 )
		{
			*unicode_character -= 0x03c82080;
		}
	}
	if( utf8_character_additional_bytes >= 4 )
	{
		if( ( utf8_string[ *utf8_string_index + 4 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 4 ] > 0xbf ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 5th UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 4 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 4 ];

		if( utf8_character_additional_bytes == 4 )
		{
			*unicode_character -= 0x0fa082080;
		}
	}
	if( utf8_character_additional_bytes == 5 )
	{
		if( ( utf8_string[ *utf8_string_index + 5 ] < 0x80 )
		  || ( utf8_string[ *utf8_string_index + 5 ] > 0xbf ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid 6th UTF-8 character byte: 0x%02" PRIx8 ".",
			 function,
			 utf8_string[ *utf8_string_index + 5 ] );

			return( -1 );
		}
		*unicode_character <<= 6;
		*unicode_character += utf8_string[ *utf8_string_index + 5 ];
		*unicode_character -= 0x082082080;
	}
	/* Determine if the Unicode character is valid
	 */
	if( *unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	*utf8_string_index += 1 + utf8_character_additional_bytes;

	return( 1 );
}

/* Copies a Unicode character into a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_to_utf8(
     libuna_unicode_character_t unicode_character,
     libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	static char *function                   = "libuna_unicode_character_copy_to_utf8";
	uint8_t utf8_character_additional_bytes = 0;
	uint8_t utf8_character_iterator         = 0;
	uint8_t utf8_first_character_mark       = 0;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	if( *utf8_string_index >= utf8_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string too small.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( unicode_character > LIBUNA_UNICODE_CHARACTER_MAX )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	/* Determine how many UTF-8 character bytes are required
	 */
	if( unicode_character < 0x080 )
	{
		utf8_character_additional_bytes = 0;
		utf8_first_character_mark       = 0;
	}
	else if( unicode_character < 0x0800 )
	{
		utf8_character_additional_bytes = 1;
		utf8_first_character_mark       = 0x0c0;
	}
	else if( unicode_character < 0x010000 )
	{
		utf8_character_additional_bytes = 2;
		utf8_first_character_mark       = 0x0e0;
	}
	else if( unicode_character < 0x0200000 )
	{
		utf8_character_additional_bytes = 3;
		utf8_first_character_mark       = 0x0f0;
	}
	else if( unicode_character < 0x0400000 )
	{
		utf8_character_additional_bytes = 4;
		utf8_first_character_mark       = 0x0f8;
	}
	else
	{
		utf8_character_additional_bytes = 5;
		utf8_first_character_mark       = 0x0fc;
	}
	/* Convert Unicode character into UTF-8 character bytes
	 */
	if( ( *utf8_string_index + utf8_character_additional_bytes ) >= utf8_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string too small.",
		 function );

		return( -1 );
	}
	for( utf8_character_iterator = utf8_character_additional_bytes;
	     utf8_character_iterator > 0;
	     utf8_character_iterator-- )
	{
		utf8_string[ *utf8_string_index + utf8_character_iterator ] = (libuna_utf8_character_t) ( ( unicode_character & 0x0bf ) | 0x080 );

		unicode_character >>= 6;
	}
	utf8_string[ *utf8_string_index ] = (libuna_utf8_character_t) ( unicode_character | utf8_first_character_mark );

	*utf8_string_index += 1 + utf8_character_additional_bytes;

	return( 1 );
}

/* Determines the size of an UTF-16 character from an Unicode character
 * Adds the size to the UTF-16 character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_size_to_utf16(
     libuna_unicode_character_t unicode_character,
     size_t *utf16_character_size,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_size_to_utf16";

	if( utf16_character_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 character size.",
		 function );

		return( -1 );
	}
	if( ( unicode_character > LIBUNA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
         && ( unicode_character <= LIBUNA_UTF16_CHARACTER_MAX ) )
	{
		*utf16_character_size += 2;
	}
	else
	{
		*utf16_character_size += 1;
	}
	return( 1 );
}

/* Copies a Unicode character from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_from_utf16(
     libuna_unicode_character_t *unicode_character,
     const libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	static char *function                    = "libuna_unicode_character_copy_from_utf16";
	libuna_utf16_character_t utf16_surrogate = 0;

	if( unicode_character == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( *utf16_string_index >= utf16_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 string too small.",
		 function );

		return( -1 );
	}
	*unicode_character   = utf16_string[ *utf16_string_index ];
	*utf16_string_index += 1;

	/* Determine if the UTF-16 character is within the high surrogate range
	 */
	if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	 && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_END ) )
	{
		if( *utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: missing surrogate UTF-16 character bytes.",
			 function );

			return( -1 );
		}
		utf16_surrogate      = utf16_string[ *utf16_string_index ];
		*utf16_string_index += 1;

		/* Determine if the UTF-16 character is within the low surrogate range
		 */
		if( ( utf16_surrogate >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( utf16_surrogate <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			*unicode_character  -= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START;
			*unicode_character <<= 10;
			*unicode_character  += utf16_surrogate - LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END;
			*unicode_character  += 0x010000;
		}
		else
		{
			*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
		}
	}
	/* Determine if the Unicode character is valid
	 */
	else if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
	      && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	return( 1 );
}

/* Copies a Unicode character into a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_to_utf16(
     libuna_unicode_character_t unicode_character,
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_to_utf16";

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( *utf16_string_index >= utf16_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 string too small.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( ( unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	  && ( unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	 || ( unicode_character > LIBUNA_UTF16_CHARACTER_MAX ) )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	if( unicode_character <= LIBUNA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
	{
		utf16_string[ *utf16_string_index ] = (libuna_utf16_character_t) unicode_character;

		*utf16_string_index += 1;
	}
	else
	{
		if( ( *utf16_string_index + 1 ) >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		unicode_character                      -= 0x010000;
		utf16_string[ *utf16_string_index     ] = (libuna_utf16_character_t) ( ( unicode_character >> 10 ) + LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START );
		utf16_string[ *utf16_string_index + 1 ] = (libuna_utf16_character_t) ( ( unicode_character & 0x03ff ) + LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START );

		*utf16_string_index += 2;
	}
	return( 1 );
}

/* Copies a Unicode character from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_from_utf16_stream(
     libuna_unicode_character_t *unicode_character,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     size_t *utf16_stream_index,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function                    = "libuna_unicode_character_copy_from_utf16_stream";
	libuna_utf16_character_t utf16_surrogate = 0;

	if( unicode_character == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf16_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream index.",
		 function );

		return( -1 );
	}
	if( *utf16_stream_index >= utf16_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 stream too small.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		*unicode_character   = utf16_stream[ *utf16_stream_index ];
		*unicode_character <<= 8;
		*unicode_character  += utf16_stream[ *utf16_stream_index + 1 ];
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		*unicode_character   = utf16_stream[ *utf16_stream_index + 1 ];
		*unicode_character <<= 8;
		*unicode_character  += utf16_stream[ *utf16_stream_index ];
	}
	*utf16_stream_index += 2;

	/* Determine if the UTF-16 character is within the high surrogate range
	 */
	if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	 && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_END ) )
	{
		if( *utf16_stream_index >= utf16_stream_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: missing surrogate UTF-16 character bytes.",
			 function );

			return( -1 );
		}
		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_surrogate   = utf16_stream[ *utf16_stream_index ];
			utf16_surrogate <<= 8;
			utf16_surrogate  += utf16_stream[ *utf16_stream_index + 1 ];
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_surrogate   = utf16_stream[ *utf16_stream_index + 1 ];
			utf16_surrogate <<= 8;
			utf16_surrogate  += utf16_stream[ *utf16_stream_index ];
		}
		*utf16_stream_index += 2;

		/* Determine if the UTF-16 character is within the low surrogate range
		 */
		if( ( utf16_surrogate >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
		 && ( utf16_surrogate <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
		{
			*unicode_character  -= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START;
			*unicode_character <<= 10;
			*unicode_character  += utf16_surrogate - LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END;
			*unicode_character  += 0x010000;
		}
		else
		{
			*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
		}
	}
	/* Determine if the Unicode character is valid
	 */
	else if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
	      && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	return( 1 );
}

/* Copies a Unicode character to an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_to_utf16_stream(
     libuna_unicode_character_t unicode_character,
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     size_t *utf16_stream_index,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function                    = "libuna_unicode_character_copy_to_utf16_stream";
	libuna_utf16_character_t utf16_surrogate = 0;

	if( utf16_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream index.",
		 function );

		return( -1 );
	}
	if( ( *utf16_stream_index + 1 ) >= utf16_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 stream too small.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( ( unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	  && ( unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	 || ( unicode_character > LIBUNA_UTF16_CHARACTER_MAX ) )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	if( unicode_character <= LIBUNA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX )
	{
		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
			unicode_character                       >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
			unicode_character                       >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		}
		*utf16_stream_index += 2;
	}
	else
	{
		if( ( *utf16_stream_index + 3 ) >= utf16_stream_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 stream too small.",
			 function );

			return( -1 );
		}
		unicode_character -= 0x010000;

		utf16_surrogate = (libuna_utf16_character_t) ( ( unicode_character >> 10 ) + LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START );

		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		*utf16_stream_index += 2;

		utf16_surrogate = (libuna_utf16_character_t) ( ( unicode_character & 0x03ff ) + LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START );

		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_stream[ *utf16_stream_index     ]   = (uint8_t) ( utf16_surrogate & 0xff );
			utf16_surrogate                         >>= 8;
			utf16_stream[ *utf16_stream_index + 1 ]   = (uint8_t) ( utf16_surrogate & 0xff );
		}
		*utf16_stream_index += 2;
	}
	return( 1 );
}

/* Determines the size of an UTF-32 character from an Unicode character
 * Adds the size to the UTF-32 character size value
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_size_to_utf32(
     libuna_unicode_character_t unicode_character LIBUNA_ATTRIBUTE_UNUSED,
     size_t *utf32_character_size,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_size_to_utf32";

	LIBUNA_UNREFERENCED_PARAMETER( unicode_character )

	if( utf32_character_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 character size.",
		 function );

		return( -1 );
	}
	*utf32_character_size += 1;

	return( 1 );
}

/* Copies a Unicode character from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_from_utf32(
     libuna_unicode_character_t *unicode_character,
     const libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf32_string_index,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_from_utf32";

	if( unicode_character == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string index.",
		 function );

		return( -1 );
	}
	if( *utf32_string_index >= utf32_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 string too small.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( utf32_string[ *utf32_string_index ] >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
	 && ( utf32_string[ *utf32_string_index ] <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	else
	{
		*unicode_character = utf32_string[ *utf32_string_index ];
	}
	*utf32_string_index += 1;

	return( 1 );
}

/* Copies a Unicode character into a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_to_utf32(
     libuna_unicode_character_t unicode_character,
     libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf32_string_index,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_to_utf32";

	if( utf32_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string index.",
		 function );

		return( -1 );
	}
	if( *utf32_string_index >= utf32_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 string too small.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( ( unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	  && ( unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	 || ( unicode_character > LIBUNA_UTF32_CHARACTER_MAX ) )
	{
		utf32_string[ *utf32_string_index ] = (libuna_utf32_character_t) LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	else
	{
		utf32_string[ *utf32_string_index ] = (libuna_utf32_character_t) unicode_character;
	}
	*utf32_string_index += 1;

	return( 1 );
}

/* Copies a Unicode character from an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_from_utf32_stream(
     libuna_unicode_character_t *unicode_character,
     const uint8_t *utf32_stream,
     size_t utf32_stream_size,
     size_t *utf32_stream_index,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_from_utf32_stream";

	if( unicode_character == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
		 function );

		return( -1 );
	}
	if( utf32_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream.",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream index.",
		 function );

		return( -1 );
	}
	if( *utf32_stream_index >= utf32_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 stream too small.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		*unicode_character   = utf32_stream[ *utf32_stream_index ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index + 1 ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index + 2 ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index + 3 ];
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		*unicode_character   = utf32_stream[ *utf32_stream_index + 3 ];
		*unicode_character <<= 8;
		*unicode_character   = utf32_stream[ *utf32_stream_index + 2 ];
		*unicode_character <<= 8;
		*unicode_character   = utf32_stream[ *utf32_stream_index + 1 ];
		*unicode_character <<= 8;
		*unicode_character  += utf32_stream[ *utf32_stream_index ];
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( *unicode_character >= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_START )
	 && ( *unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	{
		*unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	*utf32_stream_index += 4;

	return( 1 );
}

/* Copies a Unicode character to an UTF-32 stream
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE \
int libuna_unicode_character_copy_to_utf32_stream(
     libuna_unicode_character_t unicode_character,
     uint8_t *utf32_stream,
     size_t utf32_stream_size,
     size_t *utf32_stream_index,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function = "libuna_unicode_character_copy_to_utf32_stream";

	if( utf32_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream.",
		 function );

		return( -1 );
	}
	if( utf32_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 stream index.",
		 function );

		return( -1 );
	}
	if( ( *utf32_stream_index + 1 ) >= utf32_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 stream too small.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	/* Determine if the Unicode character is valid
	 */
	if( ( ( unicode_character >= LIBUNA_UNICODE_SURROGATE_HIGH_RANGE_START )
	  && ( unicode_character <= LIBUNA_UNICODE_SURROGATE_LOW_RANGE_END ) )
	 || ( unicode_character > LIBUNA_UTF32_CHARACTER_MAX ) )
	{
		unicode_character = LIBUNA_UNICODE_REPLACEMENT_CHARACTER;
	}
	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		utf32_stream[ *utf32_stream_index + 3 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 2 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		utf32_stream[ *utf32_stream_index     ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 1 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 2 ]   = (uint8_t) ( unicode_character & 0xff );
		unicode_character                       >>= 8;
		utf32_stream[ *utf32_stream_index + 3 ]   = (uint8_t) ( unicode_character & 0xff );
	}
	*utf32_stream_index += 4;

	return( 1 );
}

