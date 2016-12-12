AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATETIME_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBUNA_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	unabase \
	unaexport

unabase_SOURCES = \
	byte_size_string.c byte_size_string.h \
	export_handle.c export_handle.h \
	process_status.c process_status.h \
	unabase.c \
	unacommon.h \
	unainput.c unainput.h \
	unatools_getopt.c unatools_getopt.h \
	unatools_i18n.h \
	unatools_libcdatetime.h \
	unatools_libcerror.h \
	unatools_libcfile.h \
	unatools_libclocale.h \
	unatools_libcnotify.h \
	unatools_libuna.h \
	unatools_output.c unatools_output.h \
	unatools_signal.c unatools_signal.h \
	unatools_unused.h

unabase_LDADD = \
	@LIBCFILE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATETIME_LIBADD@ \
	../libuna/libuna.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

unaexport_SOURCES = \
	byte_size_string.c byte_size_string.h \
	export_handle.c export_handle.h \
	process_status.c process_status.h \
	unacommon.h \
	unaexport.c \
	unainput.c unainput.h \
	unatools_getopt.c unatools_getopt.h \
	unatools_i18n.h \
	unatools_libcdatetime.h \
	unatools_libcerror.h \
	unatools_libcfile.h \
	unatools_libclocale.h \
	unatools_libcnotify.h \
	unatools_libuna.h \
	unatools_output.c unatools_output.h \
	unatools_signal.c unatools_signal.h \
	unatools_unused.h

unaexport_LDADD = \
	@LIBCFILE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATETIME_LIBADD@ \
	../libuna/libuna.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on unaexport ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(unaexport_SOURCES)

