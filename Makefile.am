SUBDIRS = \
	include \
	common \
	liberror \
	libuna \
	unatools \
	docs \
	manuals \
	macosx \
	msvscpp

REDHAT_FILES = \
	libuna.spec \
	libuna.spec.in

EXTRA_DIST = \
        $(REDHAT_FILES) \
	libuna.pc.in

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libuna.pc

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/liberror && $(MAKE) $(AM_MAKEFLAGS)
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

