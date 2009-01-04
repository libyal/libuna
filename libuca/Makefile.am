AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common

lib_LTLIBRARIES = libuca.la

libuca_la_SOURCES = \
	libuca.c \
	libuca_byte_stream.c libuca_byte_stream.h \
	libuca_codepage_ascii.h \
	libuca_codepage_windows_1250.c libuca_codepage_windows_1250.h \
	libuca_codepage_windows_1251.c libuca_codepage_windows_1251.h \
	libuca_codepage_windows_1252.c libuca_codepage_windows_1252.h \
	libuca_codepage_windows_1253.c libuca_codepage_windows_1253.h \
	libuca_codepage_windows_1254.c libuca_codepage_windows_1254.h \
	libuca_codepage_windows_1255.c libuca_codepage_windows_1255.h \
	libuca_codepage_windows_1256.c libuca_codepage_windows_1256.h \
	libuca_codepage_windows_1257.c libuca_codepage_windows_1257.h \
	libuca_codepage_windows_1258.c libuca_codepage_windows_1258.h \
	libuca_definitions.h \
	libuca_extern.h \
	libuca_inline.h \
	libuca_support.c libuca_support.h \
	libuca_unicode_character.c libuca_unicode_character.h \
	libuca_utf8_stream.c libuca_utf8_stream.h \
	libuca_utf8_string.c libuca_utf8_string.h \
	libuca_utf16_stream.c libuca_utf16_stream.h \
	libuca_utf16_string.c libuca_utf16_string.h \
	libuca_utf32_stream.c libuca_utf32_stream.h \
	libuca_utf32_string.c libuca_utf32_string.h

distclean: clean
	/bin/rm -f Makefile

