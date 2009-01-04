AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common

bin_PROGRAMS = unaexport

unaexport_SOURCES = \
	byte_size_string.c byte_size_string.h \
	character_string.c character_string.h \
	error_string.c error_string.h \
	glob.c glob.h \
	process_status.c process_status.h \
	string_conversion.c string_conversion.h \
	system_string.c system_string.h \
	unacommon.h \
	unaexport.c \
	unagetopt.c unagetopt.h \
	unainput.c unainput.h \
	unaoutput.c unaoutput.h \
	unatypes.h

unaexport_LDADD   = ../common/libcommon.la ../libuna/libuna.la

distclean: clean
	/bin/rm -f Makefile

