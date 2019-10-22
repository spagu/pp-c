AC_INIT([PushPanel], [1.2], [support@pushpanel.io])
AC_CONFIG_SRCDIR([src/pp.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([-Wall])

dnl Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_LANG_C

dnl ***********************************************************************
dnl Internationalization
dnl ***********************************************************************

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string.h stdio.h stdlib.h unistd.h sys/types.h pwd.h errno.h stdbool.h])
AC_CHECK_FUNCS([setlocale])
AC_C_CONST
AC_C_INLINE

dnl Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

dnl Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memmove])

PKG_CHECK_MODULES(CURL, libcurl)
PKG_CHECK_MODULES(JSON, json-c)

AC_CONFIG_FILES([ po/Makefile.in
 Makefile
 src/Makefile
])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION(0.19)

AC_OUTPUT
