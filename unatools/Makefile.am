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
	unaexport

unaexport_SOURCES = \
	byte_size_string.c byte_size_string.h \
	process_status.c process_status.h \
	unacommon.h \
	unaexport.c \
	unainput.c unainput.h \
	unaoutput.c unaoutput.h

unaexport_LDADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libsystem/libsystem.la \
	@MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on unaexport ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(unaexport_SOURCES) 

