AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBUNA_DLL_EXPORT@

lib_LTLIBRARIES = libuna.la

libuna_la_SOURCES = \
	libuna.c \
	libuna_base16_stream.c libuna_base16_stream.h \
	libuna_base32_stream.c libuna_base32_stream.h \
	libuna_base64_stream.c libuna_base64_stream.h \
	libuna_byte_stream.c libuna_byte_stream.h \
	libuna_codepage_iso_8859_2.c libuna_codepage_iso_8859_2.h \
	libuna_codepage_iso_8859_3.c libuna_codepage_iso_8859_3.h \
	libuna_codepage_iso_8859_4.c libuna_codepage_iso_8859_4.h \
	libuna_codepage_iso_8859_5.c libuna_codepage_iso_8859_5.h \
	libuna_codepage_iso_8859_6.c libuna_codepage_iso_8859_6.h \
	libuna_codepage_iso_8859_7.c libuna_codepage_iso_8859_7.h \
	libuna_codepage_iso_8859_8.c libuna_codepage_iso_8859_8.h \
	libuna_codepage_iso_8859_9.c libuna_codepage_iso_8859_9.h \
	libuna_codepage_iso_8859_10.c libuna_codepage_iso_8859_10.h \
	libuna_codepage_iso_8859_13.c libuna_codepage_iso_8859_13.h \
	libuna_codepage_iso_8859_14.c libuna_codepage_iso_8859_14.h \
	libuna_codepage_iso_8859_15.c libuna_codepage_iso_8859_15.h \
	libuna_codepage_iso_8859_16.c libuna_codepage_iso_8859_16.h \
	libuna_codepage_koi8_r.c libuna_codepage_koi8_r.h \
	libuna_codepage_koi8_u.c libuna_codepage_koi8_u.h \
	libuna_codepage_mac_arabic.c libuna_codepage_mac_arabic.h \
	libuna_codepage_mac_celtic.c libuna_codepage_mac_celtic.h \
	libuna_codepage_mac_centraleurroman.c libuna_codepage_mac_centraleurroman.h \
	libuna_codepage_mac_croatian.c libuna_codepage_mac_croatian.h \
	libuna_codepage_mac_cyrillic.c libuna_codepage_mac_cyrillic.h \
	libuna_codepage_mac_dingbats.c libuna_codepage_mac_dingbats.h \
	libuna_codepage_mac_farsi.c libuna_codepage_mac_farsi.h \
	libuna_codepage_mac_gaelic.c libuna_codepage_mac_gaelic.h \
	libuna_codepage_mac_greek.c libuna_codepage_mac_greek.h \
	libuna_codepage_mac_icelandic.c libuna_codepage_mac_icelandic.h \
	libuna_codepage_mac_inuit.c libuna_codepage_mac_inuit.h \
	libuna_codepage_mac_roman.c libuna_codepage_mac_roman.h \
	libuna_codepage_mac_romanian.c libuna_codepage_mac_romanian.h \
	libuna_codepage_mac_russian.c libuna_codepage_mac_russian.h \
	libuna_codepage_mac_symbol.c libuna_codepage_mac_symbol.h \
	libuna_codepage_mac_thai.c libuna_codepage_mac_thai.h \
	libuna_codepage_mac_turkish.c libuna_codepage_mac_turkish.h \
	libuna_codepage_mac_ukrainian.c libuna_codepage_mac_ukrainian.h \
	libuna_codepage_windows_874.c libuna_codepage_windows_874.h \
	libuna_codepage_windows_932.c libuna_codepage_windows_932.h \
	libuna_codepage_windows_936.c libuna_codepage_windows_936.h \
	libuna_codepage_windows_949.c libuna_codepage_windows_949.h \
	libuna_codepage_windows_950.c libuna_codepage_windows_950.h \
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
	libuna_libcerror.h \
	libuna_scsu.c libuna_scsu.h \
	libuna_support.c libuna_support.h \
	libuna_types.h \
	libuna_unicode_character.c libuna_unicode_character.h \
	libuna_unused.h \
	libuna_url_stream.c libuna_url_stream.h \
	libuna_utf16_stream.c libuna_utf16_stream.h \
	libuna_utf16_string.c libuna_utf16_string.h \
	libuna_utf32_stream.c libuna_utf32_stream.h \
	libuna_utf32_string.c libuna_utf32_string.h \
	libuna_utf7_stream.c libuna_utf7_stream.h \
	libuna_utf8_stream.c libuna_utf8_stream.h \
	libuna_utf8_string.c libuna_utf8_string.h

libuna_la_LIBADD = \
	@LIBCERROR_LIBADD@

libuna_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libuna_definitions.h.in \
	libuna.rc \
	libuna.rc.in

DISTCLEANFILES = \
	libuna_definitions.h \
	libuna.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libuna ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libuna_la_SOURCES)

