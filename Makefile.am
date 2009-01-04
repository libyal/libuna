SUBDIRS = \
	common \
	libuca \
	ucatools \
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
        include/libuca.h.in \
        include/libuca/definitions.h.in \
	include/libuca/features.h.in \
        include/libuca/types.h.in \
        libuca/libuca_definitions.h.in

MACOSX_FILES = \
	macosx/Introduction.rtf \
	macosx/Introduction.rtf.in \
	macosx/libuca.pmproj \
	macosx/License.rtf \
	macosx/Readme.rtf

MANUAL_FILES = \
	manuals/ucaexport.1 \
	manuals/libuca.3

MSVCPP_FILES = \
        msvscpp/ucaexport \
        msvscpp/ucaexport/ucaexport.vcproj \
        msvscpp/libuca_dll \
        msvscpp/libuca_dll/libuca_dll.vcproj \
        msvscpp/libuca.sln

REDHAT_FILES = \
	libuca.spec \
	libuca.spec.in

EXTRA_DIST = \
        $(CONFIG_FILES) \
        $(DOCUMENT_FILES) \
        $(HEADER_FILES) \
        $(MACOSX_FILES) \
        $(MANUAL_FILES) \
        $(MSVCPP_FILES) \
        $(REDHAT_FILES) \
	libuca.pc.in

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libuca.pc

include_HEADERS = \
	include/libuca.h

pkginclude_HEADERS = \
	include/libuca/definitions.h \
	include/libuca/extern.h \
	include/libuca/features.h \
	include/libuca/inline.h \
	include/libuca/types.h

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libuca && $(MAKE) $(AM_MAKEFLAGS)

distclean: clean
	/bin/rm -f Makefile
	/bin/rm -f config.status config.cache config.log
	/bin/rm -f common/config.h
	/bin/rm -f include/libuca.h
	/bin/rm -f include/libuca/definitions.h
	/bin/rm -f include/libuca/features.h
	/bin/rm -f include/libuca/types.h
	/bin/rm -f libuca/libuac_definitions.h
	/bin/rm -f libuca.pc
	/bin/rm -f libuca.spec
	/bin/rm -f macosx/Introduction.rtf
	@for dir in ${subdirs}; do \
		(cd $$dir && $(MAKE) distclean) \
		|| case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

