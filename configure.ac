AC_PREREQ( 2.59 )

AC_INIT(
 [libuna],
 [20110921],
 [jbmetz@users.sourceforge.net])

AC_CONFIG_SRCDIR(
 [include/libuna.h.in])

AM_INIT_AUTOMAKE([gnu 1.6])

AC_CONFIG_MACRO_DIR([m4])

dnl Check for host type
AC_CANONICAL_HOST

dnl Check for large file support
AC_SYS_LARGEFILE

dnl Check for configure arguments
COMMON_ARG_ENABLE(
 [winapi],
 [winapi],
 [enable WINAPI support for cross-compilation],
 [auto-detect])
COMMON_ARG_ENABLE(
 [static-executables],
 [static_executables],
 [build the unatools as static executables],
 [no])

dnl Check for libtool DLL support
AC_LIBTOOL_WIN32_DLL

dnl Checks for programs
AC_PROG_CC
AC_PROG_GCC_TRADITIONAL
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

dnl Support of internationalization (i18n)
AM_GNU_GETTEXT([external])

dnl Check for compiler language support
AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE

dnl Automatically enable winapi support for mingw
AC_CHECK_WINAPI

dnl Check for type definitions
AC_CHECK_LOCAL_TYPES

dnl Check for headers

dnl Check for functions

dnl Check for printf conversion specifier support
AC_CHECK_FUNC_PRINTF_JD
AC_CHECK_FUNC_PRINTF_ZD

dnl Checks for libraries and library functions
dnl ac_libuna_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments
AC_CHECK_LOCAL_COMMON
AC_CHECK_LOCAL_LIBCSTRING
AC_CHECK_LOCAL_LIBERROR
AC_CHECK_LOCAL_LIBNOTIFY
AC_CHECK_LOCAL_LIBSYSTEM

dnl Check if unatools should be build as static executables
AS_IF(
 [test "x$ac_cv_enable_static_executables" != xno],
 [STATIC_LDFLAGS="-all-static";
 AC_SUBST(
  [STATIC_LDFLAGS])
 AC_DEFINE(
  [HAVE_STATIC_EXECUTABLES],
  [1],
  [Define if executables should be static compiled.])
 ac_cv_enable_static_executables=yes])

dnl Set memwatch support
ac_libuna_have_memwatch=no

AS_IF(
 [test "x$ac_libuna_have_memwatch" != xno ],
 [AC_SUBST(
  [MEMWATCH_CPPFLAGS],
  ["-DMEMWATCH -DMEMWATCH_STDIO"])
 AC_SUBST(
  [MEMWATCH_LIBADD],
  [../common/libmemwatch.la]) ])

AM_CONDITIONAL(
 [HAVE_MEMWATCH],
 [test "x$ac_libuna_have_memwatch" != xno])

dnl Set additional compiler flags
CFLAGS="$CFLAGS -Wall";

dnl Check if DLL support is needed in unatools
AS_IF(
 [test x"$enable_shared" = xyes],
 [AS_CASE(
  [$host],
  [*cygwin* | *mingw*],
  [AC_SUBST(
   [LIBUNA_DLL_IMPORT],
   ["-DLIBUNA_DLL_IMPORT"])
  ])
 ])

dnl Have configure make the Makefiles
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([common/Makefile])
AC_CONFIG_FILES([libcstring/Makefile])
AC_CONFIG_FILES([liberror/Makefile])
AC_CONFIG_FILES([libuna/Makefile])
AC_CONFIG_FILES([libsystem/Makefile])
AC_CONFIG_FILES([unatools/Makefile])
AC_CONFIG_FILES([po/Makefile.in])
AC_CONFIG_FILES([po/Makevars])
AC_CONFIG_FILES([documents/Makefile])
AC_CONFIG_FILES([manuals/Makefile])
AC_CONFIG_FILES([macosx/Makefile])
AC_CONFIG_FILES([borlandc/Makefile])
AC_CONFIG_FILES([msvscpp/Makefile])
dnl Have configure make the include files
AC_CONFIG_FILES([include/libuna.h])
AC_CONFIG_FILES([include/libuna/definitions.h])
AC_CONFIG_FILES([include/libuna/types.h])
AC_CONFIG_FILES([libuna/libuna_definitions.h])
dnl Have configure make distribution specific files
AC_CONFIG_FILES([common/types.h])
AC_CONFIG_FILES([macosx/Introduction.rtf])
AC_CONFIG_FILES([libuna/libuna.rc])
AC_CONFIG_FILES([libuna.pc])
AC_CONFIG_FILES([libuna.spec])
dnl Have configure write its configuration
AC_CONFIG_HEADERS([common/config.h])

AC_OUTPUT

dnl Print a summary
AC_MSG_NOTICE([
Features:
   unatools are build as static executables: $ac_cv_enable_static_executables
]);

