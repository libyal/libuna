if HAVE_LOCAL_LIBCDIRECTORY
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

noinst_LTLIBRARIES = libcdirectory.la

libcdirectory_la_SOURCES = \
	libcdirectory_definitions.h \
	libcdirectory_extern.h \
	libcdirectory_directory.c libcdirectory_directory.h \
	libcdirectory_directory_entry.c libcdirectory_directory_entry.h \
	libcdirectory_libcstring.h \
	libcdirectory_libcerror.h \
	libcdirectory_types.h

libcdirectory_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libcdirectory ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libcdirectory_la_SOURCES) 

