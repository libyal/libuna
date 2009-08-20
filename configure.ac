AC_PREREQ( 2.59 )

AC_INIT(
 [libuna],
  [20090820],
  [forensics@hoffmannbv.nl])

AC_CONFIG_SRCDIR(
 [include/libuna.h.in])

AM_INIT_AUTOMAKE(
 [libuna],
 [20090820])

AC_CONFIG_MACRO_DIR([m4])

dnl Check for host type
AC_CANONICAL_HOST

dnl Check for large file support
AC_SYS_LARGEFILE

dnl Check for configure arguments
LIBUNA_TEST_ENABLE(
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

dnl Check for compiler language support
AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE

dnl Checks for libraries and library functions
dnl ac_libuna_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments

dnl Check for headers
dnl Headers included in include/libuna/types.h
AC_CHECK_HEADER(
 [sys/types.h],
 [AC_DEFINE(
  [HAVE_SYS_TYPES_H],
  [1],
  [Define to 1 if you have the <sys/types.h> header file.])
 AC_SUBST(
  [HAVE_SYS_TYPES_H],
  [1])],
 [AC_SUBST(
  [HAVE_SYS_TYPES_H],
  [0])])

AC_CHECK_HEADER(
 [inttypes.h],
 [AC_DEFINE(
  [HAVE_INTTYPES_H],
  [1],
  [Define to 1 if you have the <inttypes.h> header file.])
 AC_SUBST(
  [HAVE_INTTYPES_H],
  [1])],
 [AC_SUBST(
  [HAVE_INTTYPES_H],
  [0])])

AC_CHECK_HEADER(
 [stdint.h],
 [AC_DEFINE(
  [HAVE_STDINT_H],
  [1],
  [Define to 1 if you have the <stdint.h> header file.])
 AC_SUBST(
  [HAVE_STDINT_H],
  [1])],
 [AC_SUBST(
  [HAVE_STDINT_H],
  [0])])

dnl Headers included in common/types.h
AC_CHECK_HEADERS([limits.h])

dnl Headers included in common/memory.h
AC_CHECK_HEADERS([stdlib.h])

dnl Headers included in common/narrow_string.h
AC_CHECK_HEADERS([string.h])

dnl Headers included in liberror/liberror_error.h and unatools/notify.h
AC_CHECK_HEADERS(
 [stdarg.h],
 [],
 [AC_CHECK_HEADERS(
  [varargs.h],
  [],
  [AC_MSG_FAILURE(
   [Missing headers: stdarg.h and varargs.h],
   [1]) ]) ])

dnl Headers included in unatools/date_time.h
AC_HEADER_TIME

dnl Headers included in unatools/file_io.h
AC_CHECK_HEADERS([sys/stat.h])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([unistd.h])

dnl Headers included in unatools/glob.h
AC_CHECK_HEADERS([glob.h])

dnl Headers included in unatools/unasignal.h
AC_CHECK_HEADERS([signal.h])
AC_CHECK_HEADERS([sys/signal.h])

dnl Headers included in unatools/system_string.h
AC_CHECK_HEADERS([langinfo.h])
AC_CHECK_HEADERS([locale.h])

dnl Other headers
AC_CHECK_HEADERS([errno.h])

dnl Check for declarations and type definitions
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

AC_CHECK_TYPE(
 [size32_t],
 [AC_SUBST(
  [HAVE_SIZE32_T],
  [1])],
 [AC_SUBST(
  [HAVE_SIZE32_T],
  [0])])

AC_CHECK_TYPE(
 [ssize32_t],
 [AC_SUBST(
  [HAVE_SSIZE32_T],
  [1])],
 [AC_SUBST(
  [HAVE_SSIZE32_T],
  [0])])

AC_CHECK_TYPE(
 [size64_t],
 [AC_SUBST(
  [HAVE_SIZE64_T],
  [1])],
 [AC_SUBST(
  [HAVE_SIZE64_T],
  [0])])

AC_CHECK_TYPE(
 [ssize64_t],
 [AC_SUBST(
  [HAVE_SSIZE64_T],
  [1])],
 [AC_SUBST(
  [HAVE_SSIZE64_T],
  [0])])

AC_CHECK_TYPE(
 [off64_t],
 [AC_SUBST(
  [HAVE_OFF64_T],
  [1])],
 [AC_SUBST(
  [HAVE_OFF64_T],
  [0])])

AC_CHECK_TYPE([ssize_t])

AC_CHECK_SIZEOF([off_t])
AC_CHECK_SIZEOF([size_t])

dnl Check for functions
dnl Memory functions used in common/memory.h
AC_CHECK_FUNCS(
 [free],
 [],
 [AC_MSG_FAILURE(
  [Missing function: free],
  [1]) ])

AC_CHECK_FUNCS(
 [malloc],
 [],
 [AC_MSG_FAILURE(
  [Missing function: malloc],
  [1]) ])

AC_CHECK_FUNCS(
 [memcmp],
 [],
 [AC_MSG_FAILURE(
  [Missing function: memcmp],
  [1]) ])

AC_CHECK_FUNCS(
 [memcpy],
 [],
 [AC_MSG_FAILURE(
  [Missing function: memcpy],
  [1]) ])

AC_CHECK_FUNCS(
 [memset],
 [],
 [AC_MSG_FAILURE(
  [Missing function: memset],
  [1]) ])

AC_CHECK_FUNCS(
 [realloc],
 [],
 [AC_MSG_FAILURE(
  [Missing function: realloc],
  [1]) ])

dnl Narrow character string functions used in common/narrow_string.h
AC_CHECK_FUNCS(
 [fgets],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fgets],
  [1]) ])

AC_CHECK_FUNCS(
 [snprintf],
 [],
 [AC_CHECK_FUNCS(
  [sprintf],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: snprintf and sprintf],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strlen],
 [],
 [AC_MSG_FAILURE(
  [Missing function: strlen],
  [1]) ])

AC_CHECK_FUNCS(
 [strchr],
 [],
 [AC_CHECK_FUNCS(
  [memchr],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strchr and memchr],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strncmp],
 [],
 [AC_CHECK_FUNCS(
  [strcmp],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strncmp and strcmp],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strncpy],
 [],
 [AC_CHECK_FUNCS(
  [strcpy],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strncpy and strcpy],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strrchr],
 [],
 [AC_CHECK_FUNCS(
  [memrchr],
  [AC_CHECK_DECLS(
   [memrchr],
   [],
   [AC_MSG_FAILURE(
    [Missing declaration for function memrchr],
    [1]) ]) ],
  [AC_MSG_FAILURE(
   [Missing functions: strrchr and memrchr],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strtoll],
 [],
 [AC_CHECK_FUNCS(
  [atoll],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strtoll and atoll],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strtoull],
 [],
 [AC_CHECK_FUNCS(
  [atoll],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strtoull and atoll],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [vsnprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: vsnprintf],
  [1]) ])

dnl Check for error string functions used in unatools/error_string.h
AC_FUNC_STRERROR_R(
 [],
 [AC_CHECK_FUNCS(
  [strerror],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strerror_r and strerror],
   [1]) ]) ])

dnl Date and time functions used in unatools/date_time.h
LIBUNA_CHECK_FUNC_CTIME

AC_CHECK_FUNCS(
 [gmtime_r],
 [],
 [AC_CHECK_FUNCS(
  [gmtime],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: gmtime_r and gmtime],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [time],
 [],
 [AC_MSG_FAILURE(
  [Missing function: time],
  [1]) ])

dnl File input/output functions used in unatools/file_io.h
AC_CHECK_FUNCS(
 [close],
 [],
 [AC_MSG_FAILURE(
  [Missing function: close],
  [1]) ])

AC_CHECK_FUNCS(
 [lseek],
 [],
 [AC_MSG_FAILURE(
  [Missing function: lseek],
  [1]) ])

AC_CHECK_FUNCS(
 [open],
 [],
 [AC_MSG_FAILURE(
  [Missing function: open],
  [1]) ])

AC_CHECK_FUNCS(
 [read],
 [],
 [AC_MSG_FAILURE(
  [Missing function: read],
  [1]) ])

AC_CHECK_FUNCS(
 [write],
 [],
 [AC_MSG_FAILURE(
  [Missing function: write],
  [1]) ])

dnl File input/output functions used in unatools/notify.h
AC_CHECK_FUNCS(
 [vfprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: vfprintf],
  [1]) ])

dnl Commandline argument/option parsing functions used in unatools/unagetopt.h
AC_CHECK_FUNCS([getopt])

dnl Check for locale functions
AC_CHECK_FUNCS(
 [setlocale],
 [],
 [AC_MSG_FAILURE(
  [Missing function: setlocale],
  [1]) ])

LIBUNA_LANGINFO_CODESET

dnl System functions

dnl Check for printf conversion specifier support
LIBUNA_CHECK_PRINTF_JD
LIBUNA_CHECK_PRINTF_ZD

dnl Check if unatools should be build as static executables
AS_IF(
	[test "x$ac_cv_libuna_enable_static_executables" != xno],
	[STATIC_LDFLAGS="-all-static";
	AC_SUBST(
	 [STATIC_LDFLAGS])
	ac_cv_libuna_enable_static_executables=yes])

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
AC_CONFIG_FILES([liberror/Makefile])
AC_CONFIG_FILES([libuna/Makefile])
AC_CONFIG_FILES([libsystem/Makefile])
AC_CONFIG_FILES([unatools/Makefile])
AC_CONFIG_FILES([documents/Makefile])
AC_CONFIG_FILES([manuals/Makefile])
AC_CONFIG_FILES([macosx/Makefile])
AC_CONFIG_FILES([borland/Makefile])
AC_CONFIG_FILES([msvscpp/Makefile])
dnl Have configure make the include files
AC_CONFIG_FILES([include/libuna.h])
AC_CONFIG_FILES([include/libuna/definitions.h])
AC_CONFIG_FILES([include/libuna/types.h])
AC_CONFIG_FILES([libuna/libuna_definitions.h])
dnl Have configure make distribution specific files
AC_CONFIG_FILES([common/types.h])
AC_CONFIG_FILES([macosx/Introduction.rtf])
AC_CONFIG_FILES([libuna.pc])
AC_CONFIG_FILES([libuna.spec])
dnl Have configure write its configuration
AC_CONFIG_HEADERS([common/config.h])

AC_OUTPUT

dnl Print a summary
AC_MSG_NOTICE([
Features:
   unatools are build as static executables: $ac_cv_libuna_enable_static_executables
]);

