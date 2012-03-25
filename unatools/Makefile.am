AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@ \
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
	unaoutput.c unaoutput.h
	unatools_libcerror.h \
	unatools_libcfile.h \
	unatools_libcstring.h \
	unatools_libuna.h

unabase_LDADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libuna/libuna.la \
	@LIBCSYSTEM_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBINTL@ \
	@MEMWATCH_LIBADD@

unaexport_SOURCES = \
	byte_size_string.c byte_size_string.h \
	export_handle.c export_handle.h \
	process_status.c process_status.h \
	unacommon.h \
	unaexport.c \
	unainput.c unainput.h \
	unaoutput.c unaoutput.h \
	unatools_libcerror.h \
	unatools_libcfile.h \
	unatools_libcstring.h \
	unatools_libuna.h

unaexport_LDADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libuna/libuna.la \
	@LIBCSYSTEM_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBINTL@ \
	@MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on unaexport ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(unaexport_SOURCES) 

