dnl Function to test if a certain feature was enabled
AC_DEFUN([LIBUCA_TEST_ENABLE],
	[AC_ARG_ENABLE(
	 [$1],
	 [AS_HELP_STRING(
	  [--enable-$1],
	  [$3 (default is $4)])],
	 [ac_libuca_enable_$2=$enableval],
	 [ac_libuca_enable_$2=$4])dnl
	 AC_CACHE_CHECK(
	  [whether to enable $3],
	  [ac_libuca_enable_$2],
	  [ac_libuca_enable_$2=$4])dnl
])

dnl Function to detect if printf conversion specifier "%jd" is available
AC_DEFUN([LIBUCA_PRINTF_JD],
	[SAVE_CFLAGS="$CFLAGS"
	CFLAGS="$CFLAGS -Wall -Werror"
	AC_LANG_PUSH(C)
	AC_MSG_CHECKING(
	 [if printf supports the conversion specifier "%jd"])
	dnl First try to see if compilation and linkage without a parameter succeeds
	AC_LINK_IFELSE(
		[AC_LANG_PROGRAM(
		 [[#include <stdio.h>]],
		 [[printf( "%jd" ); ]] )],
		[AC_MSG_RESULT(
		 [no])],
		dnl Second try to see if compilation and linkage with a parameter succeeds
	 	[AC_LINK_IFELSE(
			[AC_LANG_PROGRAM(
			 [[#include <sys/types.h>
#include <stdio.h>]],
		 	 [[printf( "%jd", (off_t) 10 ); ]] )],
			dnl Third try to see if the program runs correctly
	 		 [AC_RUN_IFELSE(
				[AC_LANG_PROGRAM(
				 [[#include <sys/types.h>
#include <stdio.h>]],
				 [[char string[ 3 ];
if( snprintf( string, 3, "%jd", (off_t) 10 ) < 0 ) return( 1 );
if( ( string[ 0 ] != '1' ) || ( string[ 1 ] != '0' ) ) return( 1 ); ]] )],
				[AC_MSG_RESULT(
				 [yes])
				AC_DEFINE(
				 [HAVE_PRINTF_JD],
				 [1],
				 [Define to 1 if printf supports the conversion specifier "%jd".] )],
				[AC_MSG_RESULT(
				 [no])],
				[AC_MSG_RESULT(
				 [undetermined])] )],
			[AC_MSG_RESULT(
			 [no])] )] )
	AC_LANG_POP(C)
	CFLAGS="$SAVE_CFLAGS"])

dnl Function to detect if printf conversion specifier "%zd" is available
AC_DEFUN([LIBUCA_PRINTF_ZD],
	[SAVE_CFLAGS="$CFLAGS"
	 CFLAGS="$CFLAGS -Wall -Werror"
	 AC_LANG_PUSH(C)
	 AC_MSG_CHECKING(
	  [if printf supports the conversion specifier "%zd"])
	dnl First try to see if compilation and linkage without a parameter succeeds
	AC_LINK_IFELSE(
		[AC_LANG_PROGRAM(
		 [[#include <stdio.h>]],
		 [[printf( "%zd" ); ]] )],
		[AC_MSG_RESULT(
		 [no])],
		dnl Second try to see if compilation and linkage with a parameter succeeds
	 	[AC_LINK_IFELSE(
			[AC_LANG_PROGRAM(
			 [[#include <sys/types.h>
#include <stdio.h>]],
		 	 [[printf( "%zd", (size_t) 10 ); ]] )],
			dnl Third try to see if the program runs correctly
	 		 [AC_RUN_IFELSE(
				[AC_LANG_PROGRAM(
				 [[#include <sys/types.h>
#include <stdio.h>]],
				 [[char string[ 3 ];
if( snprintf( string, 3, "%zd", (size_t) 10 ) < 0 ) return( 1 );
if( ( string[ 0 ] != '1' ) || ( string[ 1 ] != '0' ) ) return( 1 ); ]] )],
				[AC_MSG_RESULT(
				 [yes])
				AC_DEFINE(
				 [HAVE_PRINTF_ZD],
				 [1],
				 [Define to 1 if printf supports the conversion specifier "%zd".] )],
				[AC_MSG_RESULT(
				 [no])],
				[AC_MSG_RESULT(
				 [undetermined])] )],
			[AC_MSG_RESULT(
			 [no])] )] )
	AC_LANG_POP(C)
	CFLAGS="$SAVE_CFLAGS"])

