dnl Checks for libuna or required headers and functions
dnl
dnl Version: 20200118

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
  [AC_CHECK_HEADERS([signal.h sys/signal.h unistd.h])

  AC_CHECK_FUNCS([close getopt setvbuf])

  AS_IF(
   [test "x$ac_cv_func_close" != xyes],
   [AC_MSG_FAILURE(
     [Missing function: close],
     [1])
  ])

  dnl Check if tools should be build as static executables
  AX_COMMON_CHECK_ENABLE_STATIC_EXECUTABLES
])

