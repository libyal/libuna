AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

TESTS = \
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
	test_utf8_string_copy_from.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	una_test_utf16_stream_copy_from \
	una_test_utf16_string_copy_from \
	una_test_utf32_stream_copy_from \
	una_test_utf32_string_copy_from \
	una_test_utf7_stream_copy_from \
	una_test_utf8_stream_copy_from \
	una_test_utf8_string_copy_from

una_test_utf16_stream_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf16_stream_copy_from.c

una_test_utf16_stream_copy_from_LDADD = \
	@LIBCSTRING_LIBADD@ \
	../libuna/libuna.la \
        @MEMWATCH_LIBADD@

una_test_utf16_string_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf16_string_copy_from.c

una_test_utf16_string_copy_from_LDADD = \
	@LIBCSTRING_LIBADD@ \
	../libuna/libuna.la \
        @MEMWATCH_LIBADD@

una_test_utf32_stream_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf32_stream_copy_from.c

una_test_utf32_stream_copy_from_LDADD = \
	@LIBCSTRING_LIBADD@ \
	../libuna/libuna.la \
        @MEMWATCH_LIBADD@

una_test_utf32_string_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf32_string_copy_from.c

una_test_utf32_string_copy_from_LDADD = \
	@LIBCSTRING_LIBADD@ \
	../libuna/libuna.la \
        @MEMWATCH_LIBADD@

una_test_utf7_stream_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf7_stream_copy_from.c

una_test_utf7_stream_copy_from_LDADD = \
	@LIBCSTRING_LIBADD@ \
	../libuna/libuna.la \
        @MEMWATCH_LIBADD@

una_test_utf8_stream_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf8_stream_copy_from.c

una_test_utf8_stream_copy_from_LDADD = \
	@LIBCSTRING_LIBADD@ \
	../libuna/libuna.la \
        @MEMWATCH_LIBADD@

una_test_utf8_string_copy_from_SOURCES = \
	una_test_libcstring.h \
	una_test_libuna.h \
	una_test_utf8_string_copy_from.c

una_test_utf8_string_copy_from_LDADD = \
	@LIBCSTRING_LIBADD@ \
	../libuna/libuna.la \
        @MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

