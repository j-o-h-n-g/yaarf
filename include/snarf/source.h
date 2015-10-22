/*
 * source.h
 * Structured Network Alert Reporting Library - Source API Definition
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


#ifndef _SNARF_SOURCE_H_
#define _SNARF_SOURCE_H_

#include <snarf/alert.h>

#define SNARF_ALERT_DESTINATION_ENV "SNARF_ALERT_DESTINATION"
#define SNARF_SOURCE_LINGER_ENV "SNARF_SOURCE_LINGER"

typedef struct snarf_source snarf_source_t;

/**
 * Initialize an alert source.
 *
 * Should be called once on program startup.
 *
 * @param source_name name of the alerting software
 * @param source_version  version of the alerting progrma
 * @param destination socket specifier for the remote socket to send alerts to,
          which may be NULL to print alerts locally
 *
 * @return a snarf alert source
 */
snarf_source_t *
snarf_source_init(
    char *source_name,
    char *source_version,
    char *destination);

/**
 * Shutdown the alert source and free its resources.
 *
 * @param source a snarf alert source
 */
void
snarf_source_destroy(
    snarf_source_t *source);


/**
 * Send an alert.
 *
 * Sends the alert to the destination given when the alert context was
 * created.  The alert is freed once it has been sent.
 *
 * @param source a snarf alert source
 * @param tags a comma-separated list of tags that inform upstream components of
 * what type of analysis was used to generate the alert.
 * @param alert a snarf alert
 */
int
snarf_source_send_alert(
    snarf_source_t *source,
    char           *tags,
    snarf_alert_t  *alert);

#endif /* ifndef _SNARF_SOURCE_H_ */

/*
 * Local Variables:
 * mode:c
 * indent-tabs-mode:nil
 * c-basic-offset:4
 * End:
 */
