dnl Checks for required headers and functions
dnl
dnl Version: 20230219

dnl Function to detect if a specific libuna definition is available.
AC_DEFUN([AX_LIBUNA_CHECK_DEFINITION],
  [AC_CACHE_CHECK(
    [if `$1' is defined],
    [$2],
    [AC_LANG_PUSH(C)
    AC_LINK_IFELSE(
      [AC_LANG_PROGRAM(
        [[#include <libuna.h>]],
        [[int test = $1;

return( 0 ); ]] )],
      [$2=yes],
      [$2=no])
    AC_LANG_POP(C)])
  ])

dnl Function to detect if libuna dependencies are available
AC_DEFUN([AX_LIBUNA_CHECK_LOCAL],
  [dnl No additional checks.
  ])

dnl Function to detect if unatools dependencies are available
AC_DEFUN([AX_UNATOOLS_CHECK_LOCAL],
  [AC_CHECK_HEADERS([signal.h sys/signal.h sys/time.h unistd.h])

  AC_CHECK_FUNCS([close getopt setvbuf])

  AS_IF(
   [test "x$ac_cv_func_close" != xyes],
   [AC_MSG_FAILURE(
     [Missing function: close],
     [1])
  ])
])

dnl Function to check if DLL support is needed
AC_DEFUN([AX_LIBUNA_CHECK_DLL_SUPPORT],
  [AS_IF(
    [test "x$enable_shared" = xyes && test "x$ac_cv_enable_static_executables" = xno],
    [AS_CASE(
      [$host],
      [*cygwin* | *mingw* | *msys*],
      [AC_DEFINE(
        [HAVE_DLLMAIN],
        [1],
        [Define to 1 to enable the DllMain function.])
      AC_SUBST(
        [HAVE_DLLMAIN],
        [1])

      AC_SUBST(
        [LIBUNA_DLL_EXPORT],
        ["-DLIBUNA_DLL_EXPORT"])

      AC_SUBST(
        [LIBUNA_DLL_IMPORT],
        ["-DLIBUNA_DLL_IMPORT"])
      ])
    ])
  ])

