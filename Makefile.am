ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	common \
	libcstring \
	libcerror \
	libuna \
	libcfile \
	libcsystem \
	unatools \
	po \
	documents \
	manuals \
	tests \
	macosx \
	borlandc \
	msvscpp

GETTEXT_FILES = \
	config.rpath \
	po/Makevars.in

PKGCONFIG_FILES = \
	libuna.pc.in

SPEC_FILES = \
	libuna.spec \
	libuna.spec.in

EXTRA_DIST = \
	README.dll \
	README.macosx \
	README.mingw \
	README.static \
	$(GETTEXT_FILES) \
	$(PKGCONFIG_FILES) \
        $(SPEC_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libuna.pc

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libcstring && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libcerror && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS)

distclean: clean
	/bin/rm -f Makefile
	/bin/rm -f config.status
	/bin/rm -f config.cache
	/bin/rm -f config.log
	/bin/rm -f libuna.pc
	/bin/rm -f libuna.spec
	@for dir in ${subdirs}; do \
		(cd $$dir && $(MAKE) distclean) \
		|| case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

splint:
	(cd $(srcdir)/libcstring && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcerror && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libuna && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcfile && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcsystem && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/unatools && $(MAKE) splint $(AM_MAKEFLAGS))

