if HAVE_LIB_FUZZING_ENGINE
AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common

bin_PROGRAMS = \
	base16_stream_fuzzer \
	base32_stream_fuzzer \
	base64_stream_fuzzer \
	codepage_fuzzer \
	scsu_fuzzer \
	utf16_stream_fuzzer \
	utf32_stream_fuzzer \
	utf7_stream_fuzzer \
	utf8_stream_fuzzer

base16_stream_fuzzer_SOURCES = \
	base16_stream_fuzzer.cc \
	ossfuzz_libuna.h

base16_stream_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libuna/libuna.la

base32_stream_fuzzer_SOURCES = \
	base32_stream_fuzzer.cc \
	ossfuzz_libuna.h

base32_stream_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libuna/libuna.la

base64_stream_fuzzer_SOURCES = \
	base64_stream_fuzzer.cc \
	ossfuzz_libuna.h

base64_stream_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libuna/libuna.la

codepage_fuzzer_SOURCES = \
	codepage_fuzzer.cc \
	ossfuzz_libuna.h

codepage_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libuna/libuna.la

scsu_fuzzer_SOURCES = \
	scsu_fuzzer.cc \
	ossfuzz_libuna.h

scsu_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libuna/libuna.la

utf16_stream_fuzzer_SOURCES = \
	ossfuzz_libuna.h \
	utf16_stream_fuzzer.cc

utf16_stream_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libuna/libuna.la

utf32_stream_fuzzer_SOURCES = \
	ossfuzz_libuna.h \
	utf32_stream_fuzzer.cc

utf32_stream_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libuna/libuna.la

utf7_stream_fuzzer_SOURCES = \
	ossfuzz_libuna.h \
	utf7_stream_fuzzer.cc

utf7_stream_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libuna/libuna.la

utf8_stream_fuzzer_SOURCES = \
	ossfuzz_libuna.h \
	utf8_stream_fuzzer.cc

utf8_stream_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libuna/libuna.la
endif

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on base16_stream_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(base16_stream_fuzzer_SOURCES)
	@echo "Running splint on base32_stream_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(base32_stream_fuzzer_SOURCES)
	@echo "Running splint on base64_stream_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(base64_stream_fuzzer_SOURCES)
	@echo "Running splint on codepage_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(codepage_fuzzer_SOURCES)
	@echo "Running splint on scsu_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(scsu_fuzzer_SOURCES)
	@echo "Running splint on utf16_stream_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(utf16_stream_fuzzer_SOURCES)
	@echo "Running splint on utf32_stream_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(utf32_stream_fuzzer_SOURCES)
	@echo "Running splint on utf7_stream_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(utf7_stream_fuzzer_SOURCES)
	@echo "Running splint on utf8_stream_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(utf8_stream_fuzzer_SOURCES)
