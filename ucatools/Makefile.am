AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common

bin_PROGRAMS = ucaexport

ucaexport_SOURCES = \
	byte_size_string.c byte_size_string.h \
	character_string.c character_string.h \
	error_string.c error_string.h \
	glob.c glob.h \
	string_conversion.c string_conversion.h \
	system_string.c system_string.h \
	ucacommon.h \
	ucaexport.c \
	ucagetopt.c ucagetopt.h \
	ucainput.c ucainput.h \
	ucaoutput.c ucaoutput.h \
	ucaprocess_status.c ucaprocess_status.h \
	ucatypes.h

ucaexport_LDADD   = ../common/libcommon.la ../libuca/libuca.la

distclean: clean
	/bin/rm -f Makefile

