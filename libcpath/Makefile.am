if HAVE_LOCAL_LIBCPATH
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

noinst_LTLIBRARIES = libcpath.la

libcpath_la_SOURCES = \
	libcpath_definitions.h \
	libcpath_extern.h \
	libcpath_path.c libcpath_path.h \
	libcpath_split_string.c libcpath_split_string.h \
	libcpath_string.c libcpath_string.h \
	libcpath_libcstring.h \
	libcpath_libcerror.h \
	libcpath_types.h

libcpath_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libcpath ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libcpath_la_SOURCES) 

