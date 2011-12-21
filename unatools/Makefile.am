AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libsystem \
	@MEMWATCH_CPPFLAGS@ \
	@LIBUNA_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	unabase \
	unaexport

unabase_SOURCES = \
	unacommon.h \
	unabase.c \
	unainput.c unainput.h \
	unatools_libuna.h \
	unaoutput.c unaoutput.h

unabase_LDADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libsystem/libsystem.la \
	@LIBINTL@ \
	@MEMWATCH_LIBADD@

unaexport_SOURCES = \
	byte_size_string.c byte_size_string.h \
	export_handle.c export_handle.h \
	process_status.c process_status.h \
	unacommon.h \
	unaexport.c \
	unainput.c unainput.h \
	unatools_libuna.h \
	unaoutput.c unaoutput.h

unaexport_LDADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libsystem/libsystem.la \
	@LIBINTL@ \
	@MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on unaexport ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(unaexport_SOURCES) 

