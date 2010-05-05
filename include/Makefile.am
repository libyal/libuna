include_HEADERS = \
        libuna.h

pkginclude_HEADERS = \
        libuna/definitions.h \
        libuna/error.h \
        libuna/extern.h \
        libuna/types.h

EXTRA_DIST = \
	libuna.h.in \
	libuna/definitions.h.in \
	libuna/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libuna.h
	/bin/rm -f libuna/definitions.h
	/bin/rm -f libuna/types.h
	/bin/rm -f Makefile

