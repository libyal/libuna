AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common

lib_LTLIBRARIES = libuna.la

libuna_la_SOURCES = \
	libuna.c \
	libuna_byte_stream.c libuna_byte_stream.h \
	libuna_compare.c libuna_compare.h \
	libuna_codepage_ascii.h \
	libuna_codepage_windows_1250.c libuna_codepage_windows_1250.h \
	libuna_codepage_windows_1251.c libuna_codepage_windows_1251.h \
	libuna_codepage_windows_1252.c libuna_codepage_windows_1252.h \
	libuna_codepage_windows_1253.c libuna_codepage_windows_1253.h \
	libuna_codepage_windows_1254.c libuna_codepage_windows_1254.h \
	libuna_codepage_windows_1255.c libuna_codepage_windows_1255.h \
	libuna_codepage_windows_1256.c libuna_codepage_windows_1256.h \
	libuna_codepage_windows_1257.c libuna_codepage_windows_1257.h \
	libuna_codepage_windows_1258.c libuna_codepage_windows_1258.h \
	libuna_definitions.h \
	libuna_error.c libuna_error.h \
	libuna_extern.h \
	libuna_inline.h \
	libuna_support.c libuna_support.h \
	libuna_types.h \
	libuna_unicode_character.c libuna_unicode_character.h \
	libuna_utf8_stream.c libuna_utf8_stream.h \
	libuna_utf8_string.c libuna_utf8_string.h \
	libuna_utf16_stream.c libuna_utf16_stream.h \
	libuna_utf16_string.c libuna_utf16_string.h \
	libuna_utf32_stream.c libuna_utf32_stream.h \
	libuna_utf32_string.c libuna_utf32_string.h

distclean: clean
	/bin/rm -f Makefile

