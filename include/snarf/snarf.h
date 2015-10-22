/*
 * snarf.h
 * Structured Network Alert Reporting Library - Interface
 *
 * ------------------------------------------------------------------------
 * Copyright (C) 2011-2013 Carnegie Mellon University. All Rights Reserved.
 * ------------------------------------------------------------------------
 * Authors: Tony Cebzanov <tonyc@cert.org>
 * ------------------------------------------------------------------------
 * GNU General Public License (GPL) Rights pursuant to Version 2, June 1991
 * Government Purpose License Rights (GPLR) pursuant to DFARS 252.227.7013
 * ------------------------------------------------------------------------
 */


#ifndef _SNARF_SNARF_H_
#define _SNARF_SNARF_H_

/**
 * @file
 *
 * @mainpage snarf
 *
 * snarf is a distributed alert reporting system.
 *
 */

#ifdef HAVE_CONFIG_H
#    include "config.h"
#endif

#include <stdio.h>

#if STDC_HEADERS
#    include <stdlib.h>
#    include <stddef.h>
#else
#    if   HAVE_STDLIB_H
#        include <stdlib.h>
#    endif
#    if   HAVE_MALLOC_H
#        include <malloc.h>
#    endif
#endif /* if STDC_HEADERS */

#if     HAVE_INTTYPES_H
#    include <inttypes.h>
#else
#    if   HAVE_STDINT_H
#        include <stdint.h>
#    endif
#endif /* if     HAVE_INTTYPES_H */
#if     HAVE_UNISTD_H
#    include <unistd.h>
#endif

#if     HAVE_LIMITS_H
#    include <limits.h>
#endif

#if     HAVE_STRING_H
#    if   !STDC_HEADERS && HAVE_MEMORY_H
#        include <memory.h>
#    endif
#    include <string.h>
#endif /* if     HAVE_STRING_H */
#if     HAVE_STRINGS_H
#    include <strings.h>
#endif

#if     HAVE_STDARG_H
#    include <stdarg.h>
#endif

#if     HAVE_ERRNO_H
#    include <errno.h>
#endif

#if     HAVE_ARPA_INET_H
#    include <arpa/inet.h>
#endif

#ifdef  HAVE_NETDB_H
#    include <netdb.h>
#endif

#if     HAVE_PWD_H
#    include <pwd.h>
#endif

#if     HAVE_SIGNAL_H
#    include <signal.h>
#endif

/* PRI* macros for printing */
#if !defined (PRIu32)
/* Assume we either get them all or get none of them. */
#    define PRId32 "d"
#    define PRIi32 "i"
#    define PRIo32 "o"
#    define PRIu32 "u"
#    define PRIx32 "x"
#    define PRIX32 "X"

#    define PRId16 PRId32
#    define PRIi16 PRIi32
#    define PRIo16 PRIo32
#    define PRIu16 PRIu32
#    define PRIx16 PRIx32
#    define PRIX16 PRIX32

#    define PRId8  PRId32
#    define PRIi8  PRIi32
#    define PRIo8  PRIo32
#    define PRIu8  PRIu32
#    define PRIx8  PRIx32
#    define PRIX8  PRIX32
#endif /* !defined(PRIU32) */
#if !defined (PRIu64)
#    if (SIZEOF_LONG >= 8)
#        define PRId64 "l" PRId32
#        define PRIi64 "l" PRIi32
#        define PRIo64 "l" PRIo32
#        define PRIu64 "l" PRIu32
#        define PRIx64 "l" PRIx32
#        define PRIX64 "l" PRIX32
#    else /* if (SIZEOF_LONG >= 8) */
#        define PRId64 "ll" PRId32
#        define PRIi64 "ll" PRIi32
#        define PRIo64 "ll" PRIo32
#        define PRIu64 "ll" PRIu32
#        define PRIx64 "ll" PRIx32
#        define PRIX64 "ll" PRIX32
#    endif /* if (SIZEOF_LONG >= 8) */
#endif /* !defined(PRIu64) */

typedef void snarf_config_t;

#include <snarf/alert.h>
#include <snarf/source.h>
#include <snarf/sink.h>

#if HAVE_LIBYAML
#    include <snarf/config_parser.h>
#endif

#define SNARF_CONFIG_FILE_ENV "SNARF_CONFIG_FILE"

/*
 * Initialize the snarf library.  Must be called prior to creating any snarf
 * alert sources or sinks.
 */
void
snarf_init();

/*
 * Shutdown the snarf library.  Prior to calling this, shutdown any
 * sources/sink
 */
void
snarf_term();

/* Maybe move to a snarf_util module? */
uint64_t
snarf_get_current_timestamp();

char *get_canonical_hostname();;


#endif /* ifndef _SNARF_SNARF_H_ */

/*
 * Local Variables:
 * mode:c
 * indent-tabs-mode:nil
 * c-basic-offset:4
 * End:
 */
