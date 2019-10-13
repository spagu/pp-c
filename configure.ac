AC_INIT([PushPanel], [1.2], [support@pushpanel.io])
AC_CONFIG_SRCDIR([src/pp.c])
AC_CONFIG_HEADERS([config.h])


AM_INIT_AUTOMAKE([-Wall -Werror])


dnl Checks for programs.
AC_PROG_CXXCPP
AC_PROG_CXX(clang++ llvm-gcc++ gcc++)
AC_PROG_AWK
AC_PROG_CC(clang llvm-gcc gcc)
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

AC_PREREQ
AC_LANG([C++])

CFLAGS="$LFLAGS -I/usr/local/include -I/usr/local/include/json-c/ -I/usr/include -I/usr/include/json-c/ -I/usr/local/include/json-c/"
CPPFLAGS="$CPPFLAGS -I/usr/local/include -I/usr/local/include/json-c/ -I/usr/include -I/usr/include/json-c/ "
LDFLAGS="$LDFLAGS -L/usr/local/lib -lcurl -ljson-c -L/usr/lib -lintl"
AM_CFLAGS="-Wall"


dnl ***********************************************************************
dnl Internationalization
dnl ***********************************************************************

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string config.h curl/curl.h string.h stdio.h stdlib.h unistd.h sys/types.h pwd.h errno.h stdbool.h json.h  libintl.h locale.h json-c/json.h])
AC_CHECK_FUNCS([setlocale])
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])
AC_C_CONST
AC_C_INLINE

AC_CHECK_HEADER([curl/curl.h], [], [
  AC_MSG_ERROR([Unable to find curl/curl.h])
])
AC_CHECK_HEADER([json-c/json.h], [], [
  AC_MSG_ERROR([Unable to find json-c/json.h])
])
AC_CHECK_LIB([curl], [curl_version], [], [
  AC_MSG_ERROR([Unable to find libcurl])
])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T


dnl Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memmove])
AC_CONFIG_FILES([ po/Makefile.in
 Makefile
 src/Makefile
])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION(0.19)

AC_OUTPUT



