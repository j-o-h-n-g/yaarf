lib_LTLIBRARIES = libyaarf.la
libyaarf_la_SOURCES = alert.c snarf.c source.c alert_priv.h source.h snarf.h
libyaarf_la_CFLAGS = @GLIB_CFLAGS@ @JSONGLIB_CFLAGS@ @LIBSOUP_CFLAGS@
libyaarf_la_LDFLAGS = @GLIB_LIBS@ @JSONGLIB_LIBS@ @LIBSOUP_LIBS@
libyaarf_la_LDFLAGS += -version-info 0:0:0


bin_PROGRAMS = yaarftest
yaarftest_LDADD = @GLIB_LIBS@ @JSONGLIB_LIBS@ @LIBSOUP_LIBS@ $(top_builddir)/src/libyaarf.la
yaarftest_SOURCES = yaarftest.c
yaarftest_LDFLAGS = @GLIB_LIBS@ @JSONGLIB_LIBS@ @LIBSOUP_LIBS@
yaarftest_CFLAGS = @GLIB_CFLAGS@ @JSONGLIB_CFLAGS@ @LIBSOUP_CFLAGS@

