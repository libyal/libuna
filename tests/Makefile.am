AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

TESTS = \
	test_unicode_character_copy_from.sh \
	test_utf16_stream_copy_from.sh \
	test_utf16_string_copy_from.sh \
	test_utf32_stream_copy_from.sh \
	test_utf32_string_copy_from.sh \
	test_utf7_stream_copy_from.sh \
	test_utf8_stream_copy_from.sh \
	test_utf8_string_copy_from.sh

check_SCRIPTS = \
	test_utf16_stream_copy_from.sh \
	test_utf16_string_copy_from.sh \
	test_utf32_stream_copy_from.sh \
	test_utf32_string_copy_from.sh \
	test_utf7_stream_copy_from.sh \
	test_utf8_stream_copy_from.sh \
	test_utf8_string_copy_from.sh \
	test_unicode_character_copy_from.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	una_test_utf16_stream_copy_from \
	una_test_utf16_string_copy_from \
	una_test_utf32_stream_copy_from \
	una_test_utf32_string_copy_from \
	una_test_utf7_stream_copy_from \
	una_test_utf8_stream_copy_from \
	una_test_utf8_string_copy_from \
	una_test_unicode_character_copy_from

una_test_utf16_stream_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf16_stream_copy_from.c

una_test_utf16_stream_copy_from_LDADD = \
	../libuna/libuna.la \
	@LIBCSTRING_LIBADD@ \
        @MEMWATCH_LIBADD@

una_test_utf16_string_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf16_string_copy_from.c

una_test_utf16_string_copy_from_LDADD = \
	../libuna/libuna.la \
	@LIBCSTRING_LIBADD@ \
        @MEMWATCH_LIBADD@

una_test_utf32_stream_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf32_stream_copy_from.c

una_test_utf32_stream_copy_from_LDADD = \
	../libuna/libuna.la \
	@LIBCSTRING_LIBADD@ \
        @MEMWATCH_LIBADD@

una_test_utf32_string_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf32_string_copy_from.c

una_test_utf32_string_copy_from_LDADD = \
	../libuna/libuna.la \
	@LIBCSTRING_LIBADD@ \
        @MEMWATCH_LIBADD@

una_test_utf7_stream_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf7_stream_copy_from.c

una_test_utf7_stream_copy_from_LDADD = \
	../libuna/libuna.la \
	@LIBCSTRING_LIBADD@ \
        @MEMWATCH_LIBADD@

una_test_utf8_stream_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf8_stream_copy_from.c

una_test_utf8_stream_copy_from_LDADD = \
	../libuna/libuna.la \
	@LIBCSTRING_LIBADD@ \
        @MEMWATCH_LIBADD@

una_test_utf8_string_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf8_string_copy_from.c

una_test_utf8_string_copy_from_LDADD = \
	../libuna/libuna.la \
	@LIBCSTRING_LIBADD@ \
        @MEMWATCH_LIBADD@

una_test_unicode_character_copy_from_SOURCES = \
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
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_unicode_character_copy_from.c \
	una_test_types.h

una_test_unicode_character_copy_from_LDADD = \
	../libuna/libuna.la \
	@LIBCSTRING_LIBADD@ \
        @MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

