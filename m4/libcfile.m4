dnl Functions for libcfile
dnl
dnl Version: 20120405

dnl Function to detect if libcfile is available
dnl ac_libcfile_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments
AC_DEFUN([AX_LIBCFILE_CHECK_LIB],
 [dnl Check if parameters were provided
 AS_IF(
  [test "x$ac_cv_with_libcfile" != x && test "x$ac_cv_with_libcfile" != xno && test "x$ac_cv_with_libcfile" != xauto-detect],
  [AS_IF(
   [test -d "$ac_cv_with_libcfile"],
   [CFLAGS="$CFLAGS -I${ac_cv_with_libcfile}/include"
   LDFLAGS="$LDFLAGS -L${ac_cv_with_libcfile}/lib"],
   [AC_MSG_WARN([no such directory: $ac_cv_with_libcfile])
   ])
  ])

 AS_IF(
  [test "x$ac_cv_with_libcfile" = xno],
  [ac_cv_libcfile=no],
  [dnl Check for headers
  AC_CHECK_HEADERS([libcfile.h])
 
  AS_IF(
   [test "x$ac_cv_header_libcfile_h" = xno],
   [ac_cv_libcfile=no],
   [ac_cv_libcfile=yes
   AC_CHECK_LIB(
    cfile,
    libcfile_get_version,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])
  
   dnl File functions
   AC_CHECK_LIB(
    cfile,
    libcfile_file_initialize,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])
   AC_CHECK_LIB(
    cfile,
    libcfile_file_free,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])
   AC_CHECK_LIB(
    cfile,
    libcfile_file_open,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])
   AC_CHECK_LIB(
    cfile,
    libcfile_file_close,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])
   AC_CHECK_LIB(
    cfile,
    libcfile_file_read,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])
   AC_CHECK_LIB(
    cfile,
    libcfile_file_write,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])
   AC_CHECK_LIB(
    cfile,
    libcfile_file_seek_offset,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])
   AC_CHECK_LIB(
    cfile,
    libcfile_file_resize,
    [ac_cv_libcfile_dummy=yes],
    [ac_cv_libcfile=no])

   AS_IF(
    [test "x$ac_cv_enable_wide_character_type" != xno],
    [AC_CHECK_LIB(
     cfile,
     libcfile_file_open,
     [ac_cv_libcfile_dummy=yes],
     [ac_cv_libcfile=no])
    ])
   ])
  ])

 AS_IF(
  [test "x$ac_cv_libcfile" = xyes],
  [AC_DEFINE(
   [HAVE_LIBCFILE],
   [1],
   [Define to 1 if you have the `cfile' library (-lcfile).])

  ac_cv_libcfile_LIBADD="-lcfile"
  ])

 AS_IF(
  [test "x$ac_cv_libcfile" = xyes],
  [AC_SUBST(
   [HAVE_LIBCFILE],
   [1]) ],
  [AC_SUBST(
   [HAVE_LIBCFILE],
   [0])
  ])
 ])

dnl Function to detect if libcfile dependencies are available
AC_DEFUN([AX_LIBCFILE_CHECK_LOCAL],
 [dnl Headers included in libcfile/libcfile_file.h and libcfile/libcfile_support.h
 AC_CHECK_HEADERS([errno.h])

 dnl Headers included in libcfile/libcfile_file.h
 AC_CHECK_HEADERS([fcntl.h unistd.h])

 dnl Headers included in libcfile/libcfile_support.h
 AC_CHECK_HEADERS([sys/stat.h])

 dnl File input/output functions used in libcfile/libcfile_file.h
 AC_CHECK_FUNCS([close ftruncate lseek open read write])

 AS_IF(
  [test "x$ac_cv_func_close" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: close],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_ftruncate" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: ftruncate],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_lseek" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: lseek],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_open" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: open],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_read" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: read],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_write" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: write],
   [1])
  ])

 dnl File input/output functions used in libcfile/libcfile_support.h
 AC_CHECK_FUNCS([stat])

 AS_IF(
  [test "x$ac_cv_func_stat" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: stat],
   [1])
  ])
 
 ac_cv_libcfile_CPPFLAGS="-I../libcfile";
 ac_cv_libcfile_LIBADD="../libcfile/libcfile.la";

 ac_cv_libcfile=local
 ])

dnl Function to detect how to enable libcfile
AC_DEFUN([AX_LIBCFILE_CHECK_ENABLE],
 [AX_COMMON_ARG_WITH(
  [libcfile],
  [libcfile],
  [search for libcfile in includedir and libdir or in the specified DIR, or no if to use local version],
  [auto-detect],
  [DIR])

 dnl Check for a pkg-config file
 AS_IF(
  [test "x$PKGCONFIG" != "x"],
  [PKG_CHECK_MODULES(
   [libcfile],
   [libcfile >= 20120405],
   [ac_cv_libcfile=yes],
   [ac_cv_libcfile=no])

  ac_cv_libcfile_CPPFLAGS="$pkg_cv_libcfile_CFLAGS"
  ac_cv_libcfile_LIBADD="$pkg_cv_libcfile_LIBS"
 ])

 dnl Check for a shared library version
 AS_IF(
  [test "x$ac_cv_libcfile" != xyes],
  [AX_LIBCFILE_CHECK_LIB])

 dnl Check if the dependencies for the local library version
 AS_IF(
  [test "x$ac_cv_libcfile" != xyes],
  [AX_LIBCFILE_CHECK_LOCAL

  AC_DEFINE(
   [HAVE_LOCAL_LIBCFILE],
   [1],
   [Define to 1 if the local version of libcfile is used.])
  AC_SUBST(
   [HAVE_LOCAL_LIBCFILE],
   [1])
  ])

 AM_CONDITIONAL(
  [HAVE_LOCAL_LIBCFILE],
  [test "x$ac_cv_libcfile" = xlocal])
 AS_IF(
  [test "x$ac_cv_libcfile_CPPFLAGS" != "x"],
  [AC_SUBST(
   [LIBCFILE_CPPFLAGS],
   [$ac_cv_libcfile_CPPFLAGS])
  ])
 AS_IF(
  [test "x$ac_cv_libcfile_LIBADD" != "x"],
  [AC_SUBST(
   [LIBCFILE_LIBADD],
   [$ac_cv_libcfile_LIBADD])
  ])

 AS_IF(
  [test "x$ac_cv_libcfile" = xyes],
  [AC_SUBST(
   [ax_libcfile_pc_libs_private],
   [-lstring])
  ])

 AS_IF(
  [test "x$ac_cv_libcfile" = xyes],
  [AC_SUBST(
   [ax_libcfile_spec_requires],
   [libcfile])
  AC_SUBST(
   [ax_libcfile_spec_build_requires],
   [libcfile-devel])
  ])
 ])

