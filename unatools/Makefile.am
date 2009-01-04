AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common

bin_PROGRAMS = unaexport

unaexport_SOURCES = \
	byte_size_string.c byte_size_string.h \
	character_string.c character_string.h \
	date_time.c date_time.h \
	error_string.c error_string.h \
	file_io.c file_io.h \
	glob.c glob.h \
	notify.c notify.h \
	process_status.c process_status.h \
	safe_types.h \
	string_conversion.c string_conversion.h \
	system_string.c system_string.h \
	unacommon.h \
	unaexport.c \
	unagetopt.c unagetopt.h \
	unainput.c unainput.h \
	unaoutput.c unaoutput.h

unaexport_LDADD   = ../libuna/libuna.la

distclean: clean
	/bin/rm -f Makefile

