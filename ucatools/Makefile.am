AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common

bin_PROGRAMS = ucaexport

ucaexport_SOURCES = \
	ucacommon.h \
	ucaexport.c \
	ucagetopt.c ucagetopt.h \
	ucaglob.c ucaglob.h \
	ucainput.c ucainput.h \
	ucaoutput.c ucaoutput.h

ucaexport_LDADD   = ../common/libcommon.la ../libuca/libuca.la

distclean: clean
	/bin/rm -f Makefile

