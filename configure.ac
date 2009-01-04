AC_PREREQ( 2.59 )

AC_INIT(
 [libuca],
  [20080902],
  [forensics@hoffmannbv.nl])

AC_CONFIG_SRCDIR(
 [include/libuca.h.in])

AM_INIT_AUTOMAKE(
 [libuca],
 [20080902])

dnl Check for host type
AC_CANONICAL_HOST

dnl Check for large file support
AC_SYS_LARGEFILE

dnl Check for configure arguments
LIBUCA_TEST_ENABLE(
 [wide-character-type],
 [wide_character_type],
 [enable wide character type support],
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
AC_C_VOLATILE

dnl Checks for libraries and library functions
dnl ac_libuca_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments

dnl Check for headers
dnl Headers included in libuca/types.h
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

dnl Headers included in common/directory_io.h and common/file_io.h
AC_CHECK_HEADERS([sys/stat.h])

dnl Headers included in common/file_io.h
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([unistd.h])

dnl Headers included in common/narrow_string.h
AC_CHECK_HEADERS([string.h])

dnl Headers included in common/memory.h
AC_CHECK_HEADERS([stdlib.h])

dnl Headers included in common/notify.c
AC_CHECK_HEADERS([stdarg.h])
AC_CHECK_HEADERS([varargs.h])

dnl Other headers
AC_CHECK_HEADERS([glob.h])
AC_CHECK_HEADERS([signal.h])

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

dnl File input/output functions used in common/file_io.h
AC_CHECK_FUNCS(
 [close],
 [],
 [AC_MSG_FAILURE(
  [Missing functions: close],
  [1]) ])

AC_CHECK_FUNCS(
 [lseek],
 [],
 [AC_MSG_FAILURE(
  [Missing functions: lseek],
  [1]) ])

AC_CHECK_FUNCS(
 [open],
 [],
 [AC_MSG_FAILURE(
  [Missing functions: open],
  [1]) ])

AC_CHECK_FUNCS(
 [read],
 [],
 [AC_MSG_FAILURE(
  [Missing functions: read],
  [1]) ])

AC_CHECK_FUNCS(
 [write],
 [],
 [AC_MSG_FAILURE(
  [Missing functions: write],
  [1]) ])

dnl Narrow character string functions used in common/narrow_string.h
AC_CHECK_FUNCS(
 [fgets],
 [],
 [AC_MSG_FAILURE(
  [Missing functions: fgets],
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

dnl Check for error string functions used in common/error_string.h
AC_FUNC_STRERROR_R(
 [],
 [AC_CHECK_FUNCS(
  [strerror],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strerror_r and strerror],
   [1]) ]) ])

dnl Commandline argument/option parsing functions
AC_CHECK_FUNCS([getopt])

dnl Check for printf conversion specifier support
LIBUCA_PRINTF_JD
LIBUCA_PRINTF_ZD

dnl Check if libuca should be build with wide character type support
AS_IF(
	[test "x$ac_libuca_enable_wide_character_type" != xno ],
	[dnl Check for the wide character header
	AC_CHECK_HEADERS(
	 [wchar.h],
	 [AC_DEFINE(
	  [HAVE_WCHAR_H],
	  [1],
	  [Define to 1 if you have the <wchar.h> header file.])
	 AC_SUBST(
	  [HAVE_WCHAR_H],
	  [1]) ],
	 [AC_MSG_FAILURE(
	  [Missing header: wchar.h],
	  [1]) ])

	dnl Determine wide character byte size
	AC_CHECK_SIZEOF([wchar_t])

	dnl Check for wide character string functions
	dnl Wide character string functions used in common/string_conversion.h
	AC_CHECK_FUNCS(
	 [btowc],
	 [],
	 [AC_MSG_FAILURE(
	  [Missing functions: btowc],
	  [1]) ])

	AC_CHECK_FUNCS(
	 [wctob],
	 [],
	 [AC_MSG_FAILURE(
	  [Missing functions: wctob],
	  [1]) ])

	dnl Wide character string functions used in common/wide_string.h
	AC_CHECK_FUNCS(
	 [fgetws],
	 [],
	 [AC_MSG_FAILURE(
	  [Missing functions: fgetws],
	  [1]) ])

	AC_CHECK_FUNCS(
	 [swprintf],
	 [],
	 [AC_MSG_FAILURE(
	  [Missing functions: swprintf],
	  [1]) ])

	AC_CHECK_FUNCS(
	 [wcschr],
	 [],
	 [AC_CHECK_FUNCS(
	  [wmemchr],
	  [],
	  [AC_MSG_FAILURE(
	   [Missing functions: wcschr and wmemchr],
	   [1]) ]) ])

	AC_CHECK_FUNCS(
	 [wcsncmp],
	 [],
	 [AC_CHECK_FUNCS(
	  [wmemcmp],
	  [],
	  [AC_CHECK_FUNCS(
	   [wcscmp],
	   [],
	   [AC_MSG_FAILURE(
	    [Missing functions: wcsncmp, wmemcmp and wcscmp],
	    [1]) ]) ]) ])

	AC_CHECK_FUNCS(
	 [wcsncpy],
	 [],
	 [AC_CHECK_FUNCS(
	  [wmemcpy],
	  [],
	  [AC_CHECK_FUNCS(
	   [wcscpy],
	   [],
	   [AC_MSG_FAILURE(
	    [Missing functions: wcsncpy, wmemcpy and wcscpy],
	    [1]) ]) ]) ])

	AC_CHECK_FUNCS(
	 [wcslen],
	 [],
	 [AC_MSG_FAILURE(
	  [Missing functions: wcslen],
	  [1]) ])

	AC_CHECK_FUNCS(
	 [wcsrchr],
	 [],
	 [AC_CHECK_FUNCS(
	  [wmemrchr],
	  [],
	  [AC_MSG_FAILURE(
	   [Missing functions: wcsrchr and wmemrchr],
	   [1]) ]) ])

	AC_CHECK_FUNCS(
	 [wcstoll],
	 [],
	 [AC_MSG_FAILURE(
	  [Missing functions: wcstoll],
	  [1]) ])

	AC_CHECK_FUNCS(
	 [wcstoull],
	 [],
	 [AC_MSG_FAILURE(
	  [Missing functions: wcstoull],
	  [1]) ])

	dnl Make the necessary definitions
	AC_DEFINE(
	 [HAVE_WIDE_CHARACTER_TYPE],
	 [1],
	 [Defines if wide character type should be used])
	AC_SUBST(
	 [HAVE_WIDE_CHARACTER_TYPE],
	 [1])
	ac_libuca_enable_wide_character_type=yes],

	[AC_SUBST(
	 [HAVE_WIDE_CHARACTER_TYPE],
	 [0])
	AC_SUBST(
	 [HAVE_WCHAR_H],
	 [0]) ])

AC_SUBST(
 [HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS],
 [0])

CFLAGS="$CFLAGS -Wall";

dnl Have configure make the Makefiles
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([common/Makefile])
AC_CONFIG_FILES([libuca/Makefile])
AC_CONFIG_FILES([ucatools/Makefile])
AC_CONFIG_FILES([manuals/Makefile])
dnl Have configure make the include files
AC_CONFIG_FILES([include/libuca.h])
AC_CONFIG_FILES([include/libuca/definitions.h])
AC_CONFIG_FILES([include/libuca/features.h])
AC_CONFIG_FILES([include/libuca/types.h])
AC_CONFIG_FILES([libuca/libuca_definitions.h])
dnl Have configure make distribution specific files
AC_CONFIG_FILES([macosx/Introduction.rtf])
AC_CONFIG_FILES([libuca.pc])
AC_CONFIG_FILES([libuca.spec])
dnl Have configure write its configuration
AC_CONFIG_HEADERS([common/config.h])

AC_OUTPUT

dnl Print a summary
AC_MSG_NOTICE([
Features:
   Wide character type support: $ac_libuca_enable_wide_character_type
]);

