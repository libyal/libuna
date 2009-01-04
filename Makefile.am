SUBDIRS = \
	common \
	libuna \
	unatools \
	manuals

CONFIG_FILES = \
	common/config.h \
	common/config_windows.h

DOCUMENT_FILES = \
	docs/ascii.txt \
	docs/windows-1250.txt \
	docs/windows-1251.txt \
	docs/windows-1252.txt \
	docs/windows-1253.txt \
	docs/windows-1254.txt \
	docs/windows-1255.txt \
	docs/windows-1256.txt \
	docs/windows-1257.txt \
	docs/windows-1258.txt

INCLUDE_FILES = \
        include/libuna.h.in \
        include/libuna/definitions.h.in \
        include/libuna/types.h.in \
        libuna/libuna_definitions.h.in

MACOSX_FILES = \
	macosx/Introduction.rtf \
	macosx/Introduction.rtf.in \
	macosx/libuna.pmproj \
	macosx/License.rtf \
	macosx/Readme.rtf

MANUAL_FILES = \
	manuals/unaexport.1 \
	manuals/libuna.3

MSVCPP_FILES = \
        msvscpp/unaexport \
        msvscpp/unaexport/unaexport.vcproj \
        msvscpp/libuna_dll \
        msvscpp/libuna_dll/libuna_dll.vcproj \
        msvscpp/libuna.sln

REDHAT_FILES = \
	libuna.spec \
	libuna.spec.in

EXTRA_DIST = \
        $(CONFIG_FILES) \
        $(DOCUMENT_FILES) \
        $(HEADER_FILES) \
        $(MACOSX_FILES) \
        $(MANUAL_FILES) \
        $(MSVCPP_FILES) \
        $(REDHAT_FILES) \
	libuna.pc.in

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libuna.pc

include_HEADERS = \
	include/libuna.h

pkginclude_HEADERS = \
	include/libuna/definitions.h \
	include/libuna/extern.h \
	include/libuna/inline.h \
	include/libuna/types.h

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS)

distclean: clean
	/bin/rm -f Makefile
	/bin/rm -f config.status config.cache config.log
	/bin/rm -f common/config.h
	/bin/rm -f include/libuna.h
	/bin/rm -f include/libuna/definitions.h
	/bin/rm -f include/libuna/types.h
	/bin/rm -f libuna/libuac_definitions.h
	/bin/rm -f libuna.pc
	/bin/rm -f libuna.spec
	/bin/rm -f macosx/Introduction.rtf
	@for dir in ${subdirs}; do \
		(cd $$dir && $(MAKE) distclean) \
		|| case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

