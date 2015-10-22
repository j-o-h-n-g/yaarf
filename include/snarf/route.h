/*
 * route.h - SNARF message routing functions
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

#ifndef _SNARF_ROUTE_H_
#define _SNARF_ROUTE_H_

#include <zmq.h>

void
snarf_dump_envelope(
    zmq_msg_t *envelope_msg);

int
snarf_match_route(
    zmq_msg_t *envelope_msg,
    void      *generators,
    void      *tags);

void *
snarf_context();

#endif
/*
 * Local Variables:
 * mode:c
 * indent-tabs-mode:nil
 * c-basic-offset:4
 * End:
 */
