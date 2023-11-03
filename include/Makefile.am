include_HEADERS = \
	libuna.h

pkginclude_HEADERS = \
	libuna/definitions.h \
	libuna/error.h \
	libuna/extern.h \
	libuna/features.h \
	libuna/types.h

EXTRA_DIST = \
	libuna.h.in \
	libuna/definitions.h.in \
	libuna/features.h.in \
	libuna/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libuna.h
	-rm -f libuna/definitions.h
	-rm -f libuna/features.h
	-rm -f libuna/types.h
	-rm -f Makefile

