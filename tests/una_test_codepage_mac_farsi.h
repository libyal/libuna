/*
 * Definitions for MacFarsi codepage tests
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

#if !defined( _UNA_TEST_CODEPAGE_MAC_FARSI_H )
#define _UNA_TEST_CODEPAGE_MAC_FARSI_H

#include <common.h>
#include <types.h>

#include "una_test_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

una_test_byte_stream_to_unicode_t una_test_codepage_mac_farsi_byte_stream_to_unicode[ 256 ] = {
	{ { 0x00 }, 1, 0x0000, 0 },
	{ { 0x01 }, 1, 0x0001, 0 },
	{ { 0x02 }, 1, 0x0002, 0 },
	{ { 0x03 }, 1, 0x0003, 0 },
	{ { 0x04 }, 1, 0x0004, 0 },
	{ { 0x05 }, 1, 0x0005, 0 },
	{ { 0x06 }, 1, 0x0006, 0 },
	{ { 0x07 }, 1, 0x0007, 0 },
	{ { 0x08 }, 1, 0x0008, 0 },
	{ { 0x09 }, 1, 0x0009, 0 },
	{ { 0x0a }, 1, 0x000a, 0 },
	{ { 0x0b }, 1, 0x000b, 0 },
	{ { 0x0c }, 1, 0x000c, 0 },
	{ { 0x0d }, 1, 0x000d, 0 },
	{ { 0x0e }, 1, 0x000e, 0 },
	{ { 0x0f }, 1, 0x000f, 0 },
	{ { 0x10 }, 1, 0x0010, 0 },
	{ { 0x11 }, 1, 0x0011, 0 },
	{ { 0x12 }, 1, 0x0012, 0 },
	{ { 0x13 }, 1, 0x0013, 0 },
	{ { 0x14 }, 1, 0x0014, 0 },
	{ { 0x15 }, 1, 0x0015, 0 },
	{ { 0x16 }, 1, 0x0016, 0 },
	{ { 0x17 }, 1, 0x0017, 0 },
	{ { 0x18 }, 1, 0x0018, 0 },
	{ { 0x19 }, 1, 0x0019, 0 },
	{ { 0x1a }, 1, 0x001a, 0 },
	{ { 0x1b }, 1, 0x001b, 0 },
	{ { 0x1c }, 1, 0x001c, 0 },
	{ { 0x1d }, 1, 0x001d, 0 },
	{ { 0x1e }, 1, 0x001e, 0 },
	{ { 0x1f }, 1, 0x001f, 0 },
	{ { 0x20 }, 1, 0x0020, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x21 }, 1, 0x0021, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x22 }, 1, 0x0022, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x23 }, 1, 0x0023, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x24 }, 1, 0x0024, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x25 }, 1, 0x0025, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x26 }, 1, 0x0026, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x27 }, 1, 0x0027, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x28 }, 1, 0x0028, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x29 }, 1, 0x0029, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x2a }, 1, 0x002a, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x2b }, 1, 0x002b, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x2c }, 1, 0x002c, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x2d }, 1, 0x002d, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x2e }, 1, 0x002e, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x2f }, 1, 0x002f, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x30 }, 1, 0x0030, 0 },
	{ { 0x31 }, 1, 0x0031, 0 },
	{ { 0x32 }, 1, 0x0032, 0 },
	{ { 0x33 }, 1, 0x0033, 0 },
	{ { 0x34 }, 1, 0x0034, 0 },
	{ { 0x35 }, 1, 0x0035, 0 },
	{ { 0x36 }, 1, 0x0036, 0 },
	{ { 0x37 }, 1, 0x0037, 0 },
	{ { 0x38 }, 1, 0x0038, 0 },
	{ { 0x39 }, 1, 0x0039, 0 },
	{ { 0x3a }, 1, 0x003a, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x3b }, 1, 0x003b, 0 },
	{ { 0x3c }, 1, 0x003c, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x3d }, 1, 0x003d, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x3e }, 1, 0x003e, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x3f }, 1, 0x003f, 0 },
	{ { 0x40 }, 1, 0x0040, 0 },
	{ { 0x41 }, 1, 0x0041, 0 },
	{ { 0x42 }, 1, 0x0042, 0 },
	{ { 0x43 }, 1, 0x0043, 0 },
	{ { 0x44 }, 1, 0x0044, 0 },
	{ { 0x45 }, 1, 0x0045, 0 },
	{ { 0x46 }, 1, 0x0046, 0 },
	{ { 0x47 }, 1, 0x0047, 0 },
	{ { 0x48 }, 1, 0x0048, 0 },
	{ { 0x49 }, 1, 0x0049, 0 },
	{ { 0x4a }, 1, 0x004a, 0 },
	{ { 0x4b }, 1, 0x004b, 0 },
	{ { 0x4c }, 1, 0x004c, 0 },
	{ { 0x4d }, 1, 0x004d, 0 },
	{ { 0x4e }, 1, 0x004e, 0 },
	{ { 0x4f }, 1, 0x004f, 0 },
	{ { 0x50 }, 1, 0x0050, 0 },
	{ { 0x51 }, 1, 0x0051, 0 },
	{ { 0x52 }, 1, 0x0052, 0 },
	{ { 0x53 }, 1, 0x0053, 0 },
	{ { 0x54 }, 1, 0x0054, 0 },
	{ { 0x55 }, 1, 0x0055, 0 },
	{ { 0x56 }, 1, 0x0056, 0 },
	{ { 0x57 }, 1, 0x0057, 0 },
	{ { 0x58 }, 1, 0x0058, 0 },
	{ { 0x59 }, 1, 0x0059, 0 },
	{ { 0x5a }, 1, 0x005a, 0 },
	{ { 0x5b }, 1, 0x005b, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x5c }, 1, 0x005c, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x5d }, 1, 0x005d, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x5e }, 1, 0x005e, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x5f }, 1, 0x005f, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x60 }, 1, 0x0060, 0 },
	{ { 0x61 }, 1, 0x0061, 0 },
	{ { 0x62 }, 1, 0x0062, 0 },
	{ { 0x63 }, 1, 0x0063, 0 },
	{ { 0x64 }, 1, 0x0064, 0 },
	{ { 0x65 }, 1, 0x0065, 0 },
	{ { 0x66 }, 1, 0x0066, 0 },
	{ { 0x67 }, 1, 0x0067, 0 },
	{ { 0x68 }, 1, 0x0068, 0 },
	{ { 0x69 }, 1, 0x0069, 0 },
	{ { 0x6a }, 1, 0x006a, 0 },
	{ { 0x6b }, 1, 0x006b, 0 },
	{ { 0x6c }, 1, 0x006c, 0 },
	{ { 0x6d }, 1, 0x006d, 0 },
	{ { 0x6e }, 1, 0x006e, 0 },
	{ { 0x6f }, 1, 0x006f, 0 },
	{ { 0x70 }, 1, 0x0070, 0 },
	{ { 0x71 }, 1, 0x0071, 0 },
	{ { 0x72 }, 1, 0x0072, 0 },
	{ { 0x73 }, 1, 0x0073, 0 },
	{ { 0x74 }, 1, 0x0074, 0 },
	{ { 0x75 }, 1, 0x0075, 0 },
	{ { 0x76 }, 1, 0x0076, 0 },
	{ { 0x77 }, 1, 0x0077, 0 },
	{ { 0x78 }, 1, 0x0078, 0 },
	{ { 0x79 }, 1, 0x0079, 0 },
	{ { 0x7a }, 1, 0x007a, 0 },
	{ { 0x7b }, 1, 0x007b, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x7c }, 1, 0x007c, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x7d }, 1, 0x007d, UNA_TEST_UNICODE_FLAG_IS_DUPLICATE },
	{ { 0x7e }, 1, 0x007e, 0 },
	{ { 0x7f }, 1, 0x007f, 0 },
	{ { 0x80 }, 1, 0x00c4, 0 },
	{ { 0x81 }, 1, 0x00a0, 0 },
	{ { 0x82 }, 1, 0x00c7, 0 },
	{ { 0x83 }, 1, 0x00c9, 0 },
	{ { 0x84 }, 1, 0x00d1, 0 },
	{ { 0x85 }, 1, 0x00d6, 0 },
	{ { 0x86 }, 1, 0x00dc, 0 },
	{ { 0x87 }, 1, 0x00e1, 0 },
	{ { 0x88 }, 1, 0x00e0, 0 },
	{ { 0x89 }, 1, 0x00e2, 0 },
	{ { 0x8a }, 1, 0x00e4, 0 },
	{ { 0x8b }, 1, 0x06ba, 0 },
	{ { 0x8c }, 1, 0x00ab, 0 },
	{ { 0x8d }, 1, 0x00e7, 0 },
	{ { 0x8e }, 1, 0x00e9, 0 },
	{ { 0x8f }, 1, 0x00e8, 0 },
	{ { 0x90 }, 1, 0x00ea, 0 },
	{ { 0x91 }, 1, 0x00eb, 0 },
	{ { 0x92 }, 1, 0x00ed, 0 },
	{ { 0x93 }, 1, 0x2026, 0 },
	{ { 0x94 }, 1, 0x00ee, 0 },
	{ { 0x95 }, 1, 0x00ef, 0 },
	{ { 0x96 }, 1, 0x00f1, 0 },
	{ { 0x97 }, 1, 0x00f3, 0 },
	{ { 0x98 }, 1, 0x00bb, 0 },
	{ { 0x99 }, 1, 0x00f4, 0 },
	{ { 0x9a }, 1, 0x00f6, 0 },
	{ { 0x9b }, 1, 0x00f7, 0 },
	{ { 0x9c }, 1, 0x00fa, 0 },
	{ { 0x9d }, 1, 0x00f9, 0 },
	{ { 0x9e }, 1, 0x00fb, 0 },
	{ { 0x9f }, 1, 0x00fc, 0 },
	{ { 0xa0 }, 1, 0x0020, 0 },
	{ { 0xa1 }, 1, 0x0021, 0 },
	{ { 0xa2 }, 1, 0x0022, 0 },
	{ { 0xa3 }, 1, 0x0023, 0 },
	{ { 0xa4 }, 1, 0x0024, 0 },
	{ { 0xa5 }, 1, 0x066a, 0 },
	{ { 0xa6 }, 1, 0x0026, 0 },
	{ { 0xa7 }, 1, 0x0027, 0 },
	{ { 0xa8 }, 1, 0x0028, 0 },
	{ { 0xa9 }, 1, 0x0029, 0 },
	{ { 0xaa }, 1, 0x002a, 0 },
	{ { 0xab }, 1, 0x002b, 0 },
	{ { 0xac }, 1, 0x060c, 0 },
	{ { 0xad }, 1, 0x002d, 0 },
	{ { 0xae }, 1, 0x002e, 0 },
	{ { 0xaf }, 1, 0x002f, 0 },
	{ { 0xb0 }, 1, 0x06f0, 0 },
	{ { 0xb1 }, 1, 0x06f1, 0 },
	{ { 0xb2 }, 1, 0x06f2, 0 },
	{ { 0xb3 }, 1, 0x06f3, 0 },
	{ { 0xb4 }, 1, 0x06f4, 0 },
	{ { 0xb5 }, 1, 0x06f5, 0 },
	{ { 0xb6 }, 1, 0x06f6, 0 },
	{ { 0xb7 }, 1, 0x06f7, 0 },
	{ { 0xb8 }, 1, 0x06f8, 0 },
	{ { 0xb9 }, 1, 0x06f9, 0 },
	{ { 0xba }, 1, 0x003a, 0 },
	{ { 0xbb }, 1, 0x061b, 0 },
	{ { 0xbc }, 1, 0x003c, 0 },
	{ { 0xbd }, 1, 0x003d, 0 },
	{ { 0xbe }, 1, 0x003e, 0 },
	{ { 0xbf }, 1, 0x061f, 0 },
	{ { 0xc0 }, 1, 0x274a, 0 },
	{ { 0xc1 }, 1, 0x0621, 0 },
	{ { 0xc2 }, 1, 0x0622, 0 },
	{ { 0xc3 }, 1, 0x0623, 0 },
	{ { 0xc4 }, 1, 0x0624, 0 },
	{ { 0xc5 }, 1, 0x0625, 0 },
	{ { 0xc6 }, 1, 0x0626, 0 },
	{ { 0xc7 }, 1, 0x0627, 0 },
	{ { 0xc8 }, 1, 0x0628, 0 },
	{ { 0xc9 }, 1, 0x0629, 0 },
	{ { 0xca }, 1, 0x062a, 0 },
	{ { 0xcb }, 1, 0x062b, 0 },
	{ { 0xcc }, 1, 0x062c, 0 },
	{ { 0xcd }, 1, 0x062d, 0 },
	{ { 0xce }, 1, 0x062e, 0 },
	{ { 0xcf }, 1, 0x062f, 0 },
	{ { 0xd0 }, 1, 0x0630, 0 },
	{ { 0xd1 }, 1, 0x0631, 0 },
	{ { 0xd2 }, 1, 0x0632, 0 },
	{ { 0xd3 }, 1, 0x0633, 0 },
	{ { 0xd4 }, 1, 0x0634, 0 },
	{ { 0xd5 }, 1, 0x0635, 0 },
	{ { 0xd6 }, 1, 0x0636, 0 },
	{ { 0xd7 }, 1, 0x0637, 0 },
	{ { 0xd8 }, 1, 0x0638, 0 },
	{ { 0xd9 }, 1, 0x0639, 0 },
	{ { 0xda }, 1, 0x063a, 0 },
	{ { 0xdb }, 1, 0x005b, 0 },
	{ { 0xdc }, 1, 0x005c, 0 },
	{ { 0xdd }, 1, 0x005d, 0 },
	{ { 0xde }, 1, 0x005e, 0 },
	{ { 0xdf }, 1, 0x005f, 0 },
	{ { 0xe0 }, 1, 0x0640, 0 },
	{ { 0xe1 }, 1, 0x0641, 0 },
	{ { 0xe2 }, 1, 0x0642, 0 },
	{ { 0xe3 }, 1, 0x0643, 0 },
	{ { 0xe4 }, 1, 0x0644, 0 },
	{ { 0xe5 }, 1, 0x0645, 0 },
	{ { 0xe6 }, 1, 0x0646, 0 },
	{ { 0xe7 }, 1, 0x0647, 0 },
	{ { 0xe8 }, 1, 0x0648, 0 },
	{ { 0xe9 }, 1, 0x0649, 0 },
	{ { 0xea }, 1, 0x064a, 0 },
	{ { 0xeb }, 1, 0x064b, 0 },
	{ { 0xec }, 1, 0x064c, 0 },
	{ { 0xed }, 1, 0x064d, 0 },
	{ { 0xee }, 1, 0x064e, 0 },
	{ { 0xef }, 1, 0x064f, 0 },
	{ { 0xf0 }, 1, 0x0650, 0 },
	{ { 0xf1 }, 1, 0x0651, 0 },
	{ { 0xf2 }, 1, 0x0652, 0 },
	{ { 0xf3 }, 1, 0x067e, 0 },
	{ { 0xf4 }, 1, 0x0679, 0 },
	{ { 0xf5 }, 1, 0x0686, 0 },
	{ { 0xf6 }, 1, 0x06d5, 0 },
	{ { 0xf7 }, 1, 0x06a4, 0 },
	{ { 0xf8 }, 1, 0x06af, 0 },
	{ { 0xf9 }, 1, 0x0688, 0 },
	{ { 0xfa }, 1, 0x0691, 0 },
	{ { 0xfb }, 1, 0x007b, 0 },
	{ { 0xfc }, 1, 0x007c, 0 },
	{ { 0xfd }, 1, 0x007d, 0 },
	{ { 0xfe }, 1, 0x0698, 0 },
	{ { 0xff }, 1, 0x06d2, 0 }
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _UNA_TEST_CODEPAGE_MAC_FARSI_H ) */

