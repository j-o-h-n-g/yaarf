/*
 * sink.h
 * Structured Network Alert Reporting Library - Sink API Definition
 *
 * ------------------------------------------------------------------------
 * Copyright (C) 2012-2013 Carnegie Mellon University. All Rights Reserved.
 * ------------------------------------------------------------------------
 * Authors: Tony Cebzanov <tonyc@cert.org>
 * ------------------------------------------------------------------------
 * GNU General Public License (GPL) Rights pursuant to Version 2, June 1991
 * Government Purpose License Rights (GPLR) pursuant to DFARS 252.227.7013
 * ------------------------------------------------------------------------
 */


#ifndef _SNARF_SINK_H_
#define _SNARF_SINK_H_

#include <snarf/alert.h>

#define SNARF_ALERT_ORIGIN_ENV "SNARF_ALERT_ORIGIN"
#define SNARF_SINK_LINGER_ENV "SNARF_SINK_LINGER"

#define SNARF_SINK_FLAG_NONE   0
#define SNARF_SINK_FLAG_LOCAL  1

typedef struct snarf_sink snarf_sink_t;


typedef enum snarf_sink_callback_status_en
{
    SNARF_SINK_CALLBACK_OK = 0,
    SNARF_SINK_CALLBACK_ERROR
} snarf_sink_callback_status_t;

typedef snarf_sink_callback_status_t
(*snarf_sink_init_fn_t)(void **
                        sinkconfig,
                        void *config);

typedef snarf_sink_callback_status_t
(*snarf_sink_alert_fn_t)(
    void          *sinkconfig,
    snarf_alert_t *alert);

typedef snarf_sink_callback_status_t
(*snarf_sink_destroy_fn_t)(void **
                           sinkconfig);

/**
 * Initialize an alert sink.
 *
 * The sink will receive alerts on socket 'origin'
 *
 * @param origin a socket specifier for the remote socket where alerts are
 * published.
 */
snarf_sink_t *
snarf_sink_init(
    char *origin);

/**
 * Configure an alert sink using one of the built-in alert output types.
 *
 * @param sink a snarf sink
 * @param sink_id the identifier for the sink in the sink configuration
 * @param config a configuration object passed into the sink callback
 **functions
 *
 * @return zero on success, nonzero on error
 */
int
snarf_sink_configure(
    snarf_sink_t     *sink,
    const char       *sink_id);

/**
 * Configure an alert sink for custom processing using callback functions.
 *
 * @param sink a snarf sink
 * @param init_fn the custom sink's initialization function
 * @param process_fn the custom sink's processing (alert dispatch) function
 * @param destroy_fn the custom sink's termination function
 * @param config a configuration object passed into the sink callback
 **functions
 *
 * @return zero on success, nonzero on error
 */
int
snarf_sink_configure_full(
    snarf_sink_t           *sink,
    snarf_sink_init_fn_t    init_fn,
    snarf_sink_alert_fn_t   process_fn,
    snarf_sink_destroy_fn_t destroy_fn,
    snarf_config_t         *config);

/**
 * Subscribe to the given alert channel
 *
 * @param sink a snarf sink
 * @param channel the name of the channel to subscribe to
 *
 * @return zero on success, nonzero on error
 */
int
snarf_sink_subscribe(
    snarf_sink_t *sink,
    const char   *channel);

/**
 * Begin processing alerts using the sink's processing callback function.
 *
 * The callback function will be executed in a background thread.
 *
 * @param sink a snarf alert sink
 *
 * @return zero on success, nonzero on error
 */
int
snarf_sink_process(
    snarf_sink_t *sink);

/**
 * Shutdown an alert sink, unsubscribing from the alert channel.
 *
 * This will terminate the sink's background processing thread and free up any
 * resources used.
 *
 * @param sink a snarf alert sink
 */
void
snarf_sink_destroy(
    snarf_sink_t *sink);

#endif /* ifndef _SNARF_SINK_H_ */

/*
 * Local Variables:
 * mode:c
 * indent-tabs-mode:nil
 * c-basic-offset:4
 * End:
 */
