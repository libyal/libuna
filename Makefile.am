ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	common \
	libcerror \
	libuna \
	libcdatetime \
	libclocale \
	libcnotify \
	libcfile \
	unatools \
	po \
	documents \
	manuals \
	tests \
	msvscpp

DPKG_FILES = \
	dpkg/changelog \
	dpkg/changelog.in \
	dpkg/compat \
	dpkg/control \
	dpkg/copyright \
	dpkg/rules \
	dpkg/libuna-dev.install \
	dpkg/libuna.install \
	dpkg/libuna-tools.install \
	dpkg/source/format

GETTEXT_FILES = \
	config.rpath \
	po/Makevars.in

PKGCONFIG_FILES = \
	libuna.pc.in

SPEC_FILES = \
	libuna.spec \
	libuna.spec.in

EXTRA_DIST = \
	$(DPKG_FILES) \
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
	cd $(srcdir)/libcerror && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/po && $(MAKE) $(AM_MAKEFLAGS)

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
	(cd $(srcdir)/libcerror && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libuna && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcdatetime && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libclocale && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcnotify && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/libcfile && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/unatools && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/po && $(MAKE) splint $(AM_MAKEFLAGS))
	(cd $(srcdir)/tests && $(MAKE) splint $(AM_MAKEFLAGS))

