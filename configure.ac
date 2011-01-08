AC_PREREQ( 2.59 )

AC_INIT(
 [libuna],
 [20110107],
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
LIBUNA_TEST_ENABLE(
 [winapi],
 [winapi],
 [enable WINAPI support for cross-compilation],
 [auto-detect])
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

dnl Support of internationalization (i18n)
AM_GNU_GETTEXT([external])

dnl Check for compiler language support
AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE

dnl Automatically enable winapi support for mingw
AS_IF(
 [test "x$ac_cv_libuna_enable_winapi" = xauto-detect],
 [ac_libuna_target_string="$target";

 AS_IF(
  [test "x$ac_libuna_target_string" = x],
  [ac_libuna_target_string="$build"])

 AS_CASE(
  [$ac_libuna_target_string],
  [*mingw*],[AC_MSG_NOTICE(
             [Detected MinGW enabling WINAPI support for cross-compilation])
            ac_cv_libuna_enable_winapi=yes],
  [*],[ac_cv_libuna_enable_winapi=no])
 ])

dnl Check for headers
dnl Headers included in include/libuna/types.h
AC_CHECK_HEADERS([sys/types.h inttypes.h stdint.h])

AS_IF(
 [test "x$ac_cv_header_sys_types_h" = xyes],
 [AC_SUBST(
  [HAVE_SYS_TYPES_H],
  [1])],
 [AC_SUBST(
  [HAVE_SYS_TYPES_H],
  [0])])

AS_IF(
 [test "x$ac_cv_header_inttypes_h" = xyes],
 [AC_SUBST(
  [HAVE_INTTYPES_H],
  [1])],
 [AC_SUBST(
  [HAVE_INTTYPES_H],
  [0])])

AS_IF(
 [test "x$ac_cv_header_stdint_h" = xyes],
 [AC_SUBST(
  [HAVE_STDINT_H],
  [1])],
 [AC_SUBST(
  [HAVE_STDINT_H],
  [0])])

dnl Headers included in common/common.h
AS_IF(
 [test "x$ac_cv_libuna_enable_winapi" = xyes],
 [AC_CHECK_HEADERS([windows.h])

 AS_IF(
  [test "x$ac_cv_header_windows_h" = xno],
  [AC_MSG_FAILURE(
   [Missing header: windows.h header is required to compile with winapi support],
   [1]) ])
 ])

AS_IF(
 [test "x$ac_cv_libuna_enable_winapi" = xno],
 [AC_CHECK_HEADERS([libintl.h]) ])

dnl Headers included in common/types.h
AC_CHECK_HEADERS([limits.h])

dnl Headers included in common/memory.h and libcstring/libcstring_narrow_string.h
AC_CHECK_HEADERS([stdlib.h string.h])

dnl Headers included in libcstring/libcstring_locale.c
AC_CHECK_HEADERS([langinfo.h locale.h])

dnl Headers included in liberror/liberror_error.h and unatools/notify.h
AC_CHECK_HEADERS([stdarg.h])

AS_IF(
 [test "x$ac_cv_header_stdarg_h" != xyes],
 [AC_CHECK_HEADERS([varargs.h]) ])

AS_IF(
 [test "x$ac_cv_header_stdarg_h" != xyes && test "x$ac_cv_header_varargs_h" != xyes],
 [AC_MSG_FAILURE(
  [Missing headers: stdarg.h and varargs.h],
  [1]) ])

dnl Headers included in unatools/date_time.h
AC_HEADER_TIME

dnl Headers included in libsystem/libsystem_file.h and libsystem/libsystem_string.h
AC_CHECK_HEADERS([errno.h])

dnl Headers included in libsystem/libsystem_directory_io.h and libsystem/libsystem_file_io.h
AC_CHECK_HEADERS([sys/stat.h])

dnl Headers included in libsystem/libsystem_file_io.h
AC_CHECK_HEADERS([fcntl.h unistd.h])

dnl Headers included in libsystem/libsystem_glob.h
AC_CHECK_HEADERS([glob.h])

AS_IF(
 [test "x$ac_cv_header_glob_h" = xno],
 [AC_CHECK_HEADERS([io.h]) ])

dnl Headers included in libsystem/libsystem_signal.h
AC_CHECK_HEADERS([signal.h sys/signal.h])

dnl Other headers

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
dnl File stream functions used in common/file_stream.h
AC_CHECK_FUNCS(
 [fclose],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fclose],
  [1]) ])

AC_CHECK_FUNCS(
 [feof],
 [],
 [AC_MSG_FAILURE(
  [Missing function: feof],
  [1]) ])

AC_CHECK_FUNCS(
 [fgets],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fgets],
  [1]) ])

AC_CHECK_FUNCS(
 [fopen],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fopen],
  [1]) ])

AC_CHECK_FUNCS(
 [fread],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fread],
  [1]) ])

AC_CHECK_FUNCS(
 [fseeko],
 [],
 [AC_CHECK_FUNCS(
  [fseeko64],
  [],
  [AC_MSG_FAILURE(
   [Missing function: fseeko and fseeko64],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [fwrite],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fwrite],
  [1]) ])

AC_CHECK_FUNCS(
 [vfprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: vfprintf],
  [1]) ])

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

dnl Check for environment functions in libcstring/libcstring_locale.c
AC_CHECK_FUNCS(
 [getenv],
 [],
 [AC_MSG_FAILURE(
  [Missing function: getenv],
  [1]) ])

dnl Check for localization functions in libcstring/libcstring_locale.c
AC_CHECK_FUNCS(
 [setlocale],
 [],
 [AC_MSG_FAILURE(
  [Missing function: setlocale],
  [1]) ])

LIBUNA_CHECK_FUNC_LANGINFO_CODESET

dnl Narrow character string functions used in libcstring/libcstring_narrow_string.h
AC_CHECK_FUNCS(
 [fgets],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fgets],
  [1]) ])

AC_CHECK_FUNCS(
 [memchr],
 [],
 [AC_CHECK_FUNCS(
  [strchr],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: memchr and strchr],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [memcmp],
 [],
 [AC_CHECK_FUNCS(
  [strncmp],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: memcmp and strncmp],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [memcpy],
 [],
 [AC_CHECK_FUNCS(
  [strncpy],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: memcpy and strncpy],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [memrchr],
 [AC_CHECK_DECLS(
  [memrchr],
  [ac_libuna_have_memrchr=yes],
  [ac_libuna_have_memrchr=no]) ],
 [ac_libuna_have_memrchr=no])

AS_IF(
 [test "x$ac_libuna_have_memrchr" = xno],
 [AC_CHECK_FUNCS(
  [strrchr],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strrchr and memrchr],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [snprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: snprintf],
  [1]) ])

AC_CHECK_FUNCS(
 [sscanf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: sscanf],
  [1]) ])

AC_CHECK_FUNCS(
 [strlen],
 [],
 [AC_MSG_FAILURE(
  [Missing function: strlen],
  [1]) ])

AC_CHECK_FUNCS(
 [strncasecmp],
 [],
 [AC_CHECK_FUNCS(
  [strcasecmp],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strncasecmp and strcasecmp],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strstr],
 [],
 [AC_MSG_FAILURE(
  [Missing function: strstr],
  [1]) ])

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

dnl File input/output functions used in libsystem/libsystem_file_io.h
AC_CHECK_FUNCS(
 [close],
 [],
 [AC_MSG_FAILURE(
  [Missing function: close],
  [1]) ])

AC_CHECK_FUNCS(
 [fstat],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fstat],
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
 [stat],
 [],
 [AC_MSG_FAILURE(
  [Missing function: stat],
  [1]) ])

AC_CHECK_FUNCS(
 [ftruncate],
 [],
 [AC_MSG_FAILURE(
  [Missing function: ftruncate],
  [1]) ])

AC_CHECK_FUNCS(
 [write],
 [],
 [AC_MSG_FAILURE(
  [Missing function: write],
  [1]) ])

dnl Date and time functions used in libsystem/libsystem_date_time.c
AC_CHECK_FUNCS(
 [localtime_r],
 [],
 [AC_CHECK_FUNCS(
  [localtime],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: localtime_r and localtime],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [mktime],
 [],
 [AC_MSG_FAILURE(
  [Missing function: mktime],
  [1]) ])

dnl Date and time functions used in libsystem/libsystem_date_time.h
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

dnl Directory functions used in libsystem/libsystem_directory_io.h
AC_CHECK_FUNCS(
 [chdir],
 [],
 [AC_MSG_FAILURE(
  [Missing functions: chdir],
  [1]) ])

LIBUNA_CHECK_FUNC_MKDIR

dnl Check for error string functions used in libsystem/libsystem_error_string.c
AC_FUNC_STRERROR_R()

AS_IF(
 [test "x$ac_cv_have_decl_strerror_r" = xno],
 [AC_CHECK_FUNCS(
  [strerror],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strerror_r and strerror],
   [1]) ]) ])

dnl Commandline argument/option parsing functions in libsystem/libsystem_getopt.h
AC_CHECK_FUNCS([getopt])

dnl Check for internationalization functions in <library>/<library>_i18n.c and libsystem/libsystem_support.c
AC_CHECK_FUNCS([bindtextdomain])

dnl Check for internationalization functions in libsystem/libsystem_support.c
AC_CHECK_FUNCS([textdomain])

dnl Other functions

dnl Check for printf conversion specifier support
LIBUNA_CHECK_FUNC_PRINTF_JD
LIBUNA_CHECK_FUNC_PRINTF_ZD

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
   unatools are build as static executables: $ac_cv_libuna_enable_static_executables
]);

