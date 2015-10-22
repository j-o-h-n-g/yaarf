/*
 * alert_print.h
 * Structured Network Alert Reporting Framework - alert printing helpers
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

#ifndef _SNARF_ALERT_PRINT_H_
#define _SNARF_ALERT_PRINT_H_

#include <snarf/snarf.h>

typedef struct snarf_output_buffer snarf_output_buffer_t;


typedef enum snarf_output_format_en
{
    SNARF_OUTPUT_BUFFER_RAW = 0,       /**< No formatting, (custom sinks) **/
    SNARF_OUTPUT_BUFFER_DELIMITED,     /**< Delimited fields, e.g. CSV */
    SNARF_OUTPUT_BUFFER_JSON,          /**< JavaScript Object Notation */
    SNARF_OUTPUT_BUFFER_XML            /**< XML */
} snarf_output_format_t;

typedef enum snarf_output_severity_format_en
{
    SNARF_OUTPUT_SEVERITY_FORMAT_INT = 0, /**< As an integer */
    SNARF_OUTPUT_SEVERITY_FORMAT_NAME     /**< As the symbolic name */
} snarf_output_severity_format_t;

typedef enum snarf_output_timestamp_format_en
{
    SNARF_OUTPUT_TIMESTAMP_FORMAT_ISO8601 = 0, /**< ISO 8601 format */
    SNARF_OUTPUT_TIMESTAMP_FORMAT_CEF,  /**< Common Event Format */
    SNARF_OUTPUT_TIMESTAMP_FORMAT_EPOCHSEC,
    SNARF_OUTPUT_TIMESTAMP_FORMAT_EPOCHMSEC
} snarf_output_timestamp_format_t;

typedef enum snarf_output_elapsed_format_en
{
    SNARF_OUTPUT_ELAPSED_FORMAT_SEC = 0,
    SNARF_OUTPUT_ELAPSED_FORMAT_MSEC
} snarf_output_elapsed_format_t;

typedef enum snarf_output_tcp_flags_format_en
{
    SNARF_OUTPUT_TCP_FLAGS_FORMAT_COMPACT = 0, /**< No spaces for empty flags */
    SNARF_OUTPUT_TCP_FLAGS_FORMAT_VERBOSE /**< Spaces for empty flags */
} snarf_output_tcp_flags_format_t;

/* Convenience macros for printing IP addresses */
#define SNARF_ALERT_IP4_ARGS(_addr_) \
    (_addr_ & 0xFF000000) >> 24,     \
    (_addr_ & 0x00FF0000) >> 16,     \
    (_addr_ & 0x0000FF00) >> 8,      \
    (_addr_ & 0x000000FF)


#define SNARF_ALERT_IP4_FMT "%u.%u.%u.%u"

#define SNARF_ALERT_PRINT_IP4(addr) g_print(SNARF_ALERT_IP4_FMT, \
                                            SNARF_ALERT_IP4_ARGS(addr))


/**
 * Create a new output buffer for printing alert fields.
 *
 * @param len initial size of the output buffer, which will grow as necessary
 *
 * @return a newly-initialized snarf output buffer
 */
snarf_output_buffer_t *
snarf_output_buffer_new(
    size_t len);

/**
 * Free an output buffer
 *
 * @param outbuf a snarf output buffer
 */
void
snarf_output_buffer_free(
    snarf_output_buffer_t *outbuf);

/**
 * Set the ouput format of a snarf output buffer
 *
 * @param outbuf a snarf output buffer
 * @param format
 */
void
snarf_output_buffer_set_format(
    snarf_output_buffer_t *outbuf,
    snarf_output_format_t  format);

/**
 * Set the delimiting character in a delimited output buffer.
 *
 * @param outbuf a snarf output buffer
 * @param delim a delimiting character
 */
void
snarf_output_buffer_set_delimiter(
    snarf_output_buffer_t *outbuf,
    char                   delim);

/**
 * Set the output format of an alert's severity field
 *
 * @param outbuf a snarf output buffer
 * @param format the severity format
 */
void
snarf_output_buffer_set_severity_format(
    snarf_output_buffer_t         *outbuf,
    snarf_output_severity_format_t format);

/**
 * Set the output format of an alert's timestamp field
 *
 * @param outbuf a snarf output buffer
 * @param format the timestamp format
 */
void
snarf_output_buffer_set_timestamp_format(
    snarf_output_buffer_t          *outbuf,
    snarf_output_timestamp_format_t format);

/**
 * Set the output format of an alert's elapsed field
 *
 * @param outbuf a snarf output buffer
 * @param format the output format
 */
void
snarf_output_buffer_set_elapsed_format(
    snarf_output_buffer_t          *outbuf,
    snarf_output_elapsed_format_t format);

/**
 * Set the output format of TCP flags in an alert's flow fields
 *
 * @param outbuf a snarf output buffer
 * @param format the TCP flags format
 */
void
snarf_output_buffer_set_tcp_flags_format(
    snarf_output_buffer_t          *outbuf,
    snarf_output_tcp_flags_format_t format);

/**
 * Get the content of a snarf output buffer
 *
 * @param outbuf a snarf output buffer
 *
 * @return a pointer to the output buffer's character data
 */
char *
snarf_output_buffer_contents(
    snarf_output_buffer_t *outbuf);

/**
 * Get the length of data in a snarf output buffer
 *
 * @param outbuf a snarf output buffer
 *
 * @return the size in bytes of the output buffer's data
 */
size_t
snarf_output_buffer_length(
    snarf_output_buffer_t *outbuf);


/**
 * Print a field from an alert's envelope
 *
 * @param outbuf a snarf output buffer
 * @param alert a snarf alert
 * @param fieldname the name of the envelope field to print
 */
void
snarf_alert_print_envelope_field(
    snarf_output_buffer_t *outbuf,
    snarf_alert_t         *alert,
    const char            *fieldname);


void
snarf_alert_print_analysis_tags(snarf_output_buffer_t *outbuf,
                                snarf_alert_t         *alert);


/**
 * Print a field value from an alert.
 *
 * @param outbuf a snarf output buffer
 * @param value the value to print
 */
void
snarf_alert_print_value(snarf_output_buffer_t *outbuf,
                        snarf_value_t         *value);

/**
 * Print a string to an output buffer
 *
 * @param outbuf a snarf output buffer
 * @param str the string to append
 */
void
snarf_alert_print_string(
    snarf_output_buffer_t *outbuf,
    char                  *str);

/**
 * Print a string to an output buffer with no field delimiting or special
 * formatting
 *
 * @param outbuf a snarf output buffer
 * @param str the string to append
 */
void
snarf_alert_print_string_raw(
    snarf_output_buffer_t *outbuf,
    char                  *str);

/**
 * Print a flow field value to an output buffer
 *
 * @param outbuf a snarf output buffer
 * @param value a flow value
 * @param fieldname the name of the flow field to print
 */
void
snarf_alert_print_flow_field(
    snarf_output_buffer_t *outbuf,
    snarf_value_t         *value,
    const char            *fieldname);


/**
 * Write an IPset value to a file
 *
 * @param filename the name of the file to write to
 * @param value an IP set value
 */
void
snarf_alert_write_ipset(
    const char    *filename,
    snarf_value_t *value);


#endif /* ifndef _SNARF_ALERT_PRINT_H_ */

/*
 * Local Variables:
 * mode:c
 * indent-tabs-mode:nil
 * c-basic-offset:4
 * End:
 */
