AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBUNA_DLL_IMPORT@

TESTS = \
	test_library.sh

check_SCRIPTS = \
	test_library.sh \
	test_runner.sh \
	test_unaexport.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	una_test_base16_stream \
	una_test_base32_stream \
	una_test_base64_stream_copy_from \
	una_test_base64_stream_copy_to \
	una_test_error \
	una_test_support \
	una_test_utf16_stream_copy_from \
	una_test_utf16_string \
	una_test_utf32_stream_copy_from \
	una_test_utf32_string \
	una_test_utf7_stream_copy_from \
	una_test_utf8_stream_copy_from \
	una_test_utf8_string \
	una_test_unicode_character_copy_from \
	una_test_unicode_character_copy_to

una_test_base16_stream_SOURCES = \
	una_test_base16_stream.c \
	una_test_libcerror.h \
	una_test_libuna.h \
	una_test_macros.h \
	una_test_unused.h

una_test_base16_stream_LDADD = \
	../libuna/libuna.la \
	@LIBCERROR_LIBADD@

una_test_base32_stream_SOURCES = \
	una_test_base32_stream.c \
	una_test_libcerror.h \
	una_test_libuna.h \
	una_test_macros.h \
	una_test_unused.h

una_test_base32_stream_LDADD = \
	../libuna/libuna.la \
	@LIBCERROR_LIBADD@

una_test_base64_stream_copy_from_SOURCES = \
	una_test_base64_stream_copy_from.c \
	una_test_libuna.h

una_test_base64_stream_copy_from_LDADD = \
	../libuna/libuna.la

una_test_base64_stream_copy_to_SOURCES = \
	una_test_base64_stream_copy_to.c \
	una_test_libuna.h

una_test_base64_stream_copy_to_LDADD = \
	../libuna/libuna.la

una_test_error_SOURCES = \
	una_test_error.c \
	una_test_libuna.h \
	una_test_macros.h \
	una_test_unused.h

una_test_error_LDADD = \
	../libuna/libuna.la

una_test_support_SOURCES = \
	una_test_libuna.h \
	una_test_macros.h \
	una_test_support.c \
	una_test_unused.h

una_test_support_LDADD = \
	../libuna/libuna.la

una_test_utf16_stream_copy_from_SOURCES = \
	una_test_libuna.h \
	una_test_utf16_stream_copy_from.c

una_test_utf16_stream_copy_from_LDADD = \
	../libuna/libuna.la

una_test_utf16_string_SOURCES = \
	una_test_libcerror.h \
	una_test_libuna.h \
	una_test_macros.h \
	una_test_unused.h \
	una_test_utf16_string.c

una_test_utf16_string_LDADD = \
	../libuna/libuna.la \
	@LIBCERROR_LIBADD@

una_test_utf32_stream_copy_from_SOURCES = \
	una_test_libuna.h \
	una_test_utf32_stream_copy_from.c

una_test_utf32_stream_copy_from_LDADD = \
	../libuna/libuna.la

una_test_utf32_string_SOURCES = \
	una_test_libcerror.h \
	una_test_libuna.h \
	una_test_macros.h \
	una_test_unused.h \
	una_test_utf32_string.c

una_test_utf32_string_LDADD = \
	../libuna/libuna.la \
	@LIBCERROR_LIBADD@

una_test_utf7_stream_copy_from_SOURCES = \
	una_test_libuna.h \
	una_test_utf7_stream_copy_from.c

una_test_utf7_stream_copy_from_LDADD = \
	../libuna/libuna.la

una_test_utf8_stream_copy_from_SOURCES = \
	una_test_libuna.h \
	una_test_utf8_stream_copy_from.c

una_test_utf8_stream_copy_from_LDADD = \
	../libuna/libuna.la

una_test_utf8_string_SOURCES = \
	una_test_libcerror.h \
	una_test_libuna.h \
	una_test_macros.h \
	una_test_unused.h \
	una_test_utf8_string.c

una_test_utf8_string_LDADD = \
	../libuna/libuna.la \
	@LIBCERROR_LIBADD@

una_test_unicode_character_copy_from_SOURCES = \
	una_test_codepage_ascii.h \
	una_test_codepage_iso_8859_1.h \
	una_test_codepage_iso_8859_2.h \
	una_test_codepage_iso_8859_3.h \
	una_test_codepage_iso_8859_4.h \
	una_test_codepage_iso_8859_5.h \
	una_test_codepage_iso_8859_6.h \
	una_test_codepage_iso_8859_7.h \
	una_test_codepage_iso_8859_8.h \
	una_test_codepage_iso_8859_9.h \
	una_test_codepage_iso_8859_10.h \
	una_test_codepage_iso_8859_11.h \
	una_test_codepage_iso_8859_13.h \
	una_test_codepage_iso_8859_14.h \
	una_test_codepage_iso_8859_15.h \
	una_test_codepage_iso_8859_16.h \
	una_test_codepage_koi8_r.h \
	una_test_codepage_koi8_u.h \
	una_test_codepage_windows_874.h \
	una_test_codepage_windows_932.h \
	una_test_codepage_windows_936.h \
	una_test_codepage_windows_949.h \
	una_test_codepage_windows_950.h \
	una_test_codepage_windows_1250.h \
	una_test_codepage_windows_1251.h \
	una_test_codepage_windows_1252.h \
	una_test_codepage_windows_1253.h \
	una_test_codepage_windows_1254.h \
	una_test_codepage_windows_1255.h \
	una_test_codepage_windows_1256.h \
	una_test_codepage_windows_1257.h \
	una_test_codepage_windows_1258.h \
	una_test_libuna.h \
	una_test_unicode_character_copy_from.c \
	una_test_types.h

una_test_unicode_character_copy_from_LDADD = \
	../libuna/libuna.la

una_test_unicode_character_copy_to_SOURCES = \
	una_test_codepage_iso_8859_1.h \
	una_test_codepage_iso_8859_2.h \
	una_test_codepage_iso_8859_3.h \
	una_test_codepage_iso_8859_4.h \
	una_test_codepage_iso_8859_5.h \
	una_test_codepage_iso_8859_6.h \
	una_test_codepage_iso_8859_7.h \
	una_test_codepage_iso_8859_8.h \
	una_test_codepage_iso_8859_9.h \
	una_test_codepage_iso_8859_10.h \
	una_test_codepage_iso_8859_11.h \
	una_test_codepage_iso_8859_13.h \
	una_test_codepage_iso_8859_14.h \
	una_test_codepage_iso_8859_15.h \
	una_test_codepage_iso_8859_16.h \
	una_test_codepage_koi8_r.h \
	una_test_codepage_koi8_u.h \
	una_test_codepage_windows_874.h \
	una_test_codepage_windows_932.h \
	una_test_codepage_windows_936.h \
	una_test_codepage_windows_949.h \
	una_test_codepage_windows_950.h \
	una_test_codepage_windows_1250.h \
	una_test_codepage_windows_1251.h \
	una_test_codepage_windows_1252.h \
	una_test_codepage_windows_1253.h \
	una_test_codepage_windows_1254.h \
	una_test_codepage_windows_1255.h \
	una_test_codepage_windows_1256.h \
	una_test_codepage_windows_1257.h \
	una_test_codepage_windows_1258.h \
	una_test_libuna.h \
	una_test_unicode_character_copy_to.c \
	una_test_types.h

una_test_unicode_character_copy_to_LDADD = \
	../libuna/libuna.la

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

