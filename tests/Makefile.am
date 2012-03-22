AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	@MEMWATCH_CPPFLAGS@

TESTS = \
	test_utf8_string_copy_from.sh

check_SCRIPTS = \
	test_utf8_string_copy_from.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	una_test_utf8_string_copy_from

una_test_utf8_string_copy_from_SOURCES = \
	una_test_libuna.h \
	una_test_utf8_string_copy_from.c

una_test_utf8_string_copy_from_LDADD = \
	../libcstring/libcstring.la \
	../libuna/libuna.la \
        @MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

