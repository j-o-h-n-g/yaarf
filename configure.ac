#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([yaarf], [1.1.3], [github@giggled.org])
AC_CONFIG_SRCDIR([src/source.c])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_AUX_DIR([autoconf])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.

AM_INIT_AUTOMAKE

AC_PROG_CC

AC_PROG_LIBTOOL

AC_SUBST(AM_CPPFLAGS)
AC_SUBST(AM_CFLAGS)
AC_SUBST(AM_LDFLAGS)

CPPFLAGS='-I$(top_builddir)/include -I$(top_srcdir)/include'" $CPPFLAGS"


# Checks for libraries.
PKG_CHECK_MODULES([GLIB], [glib-2.0])
PKG_CHECK_MODULES([JSONGLIB], [json-glib-1.0])
PKG_CHECK_MODULES([LIBSOUP], [libsoup-2.4 > 2.26])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h inttypes.h limits.h malloc.h memory.h netdb.h stddef.h stdint.h stdlib.h string.h strings.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.



AC_CONFIG_FILES([Makefile src/Makefile libyaarf.pc yaarf.spec include/snarf/Makefile])
AC_OUTPUT
