/*
 * alert.h
 * Structured Network Alert Reporting Library - Alert Interface
 *
 * ------------------------------------------------------------------------
 * Copyright (C) 2011-2014 Carnegie Mellon University. All Rights Reserved.
 * ------------------------------------------------------------------------
 * Authors: Tony Cebzanov <tonyc@cert.org>
 * ------------------------------------------------------------------------
 * GNU General Public License (GPL) Rights pursuant to Version 2, June 1991
 * Government Purpose License Rights (GPLR) pursuant to DFARS 252.227.7013
 * ------------------------------------------------------------------------
 */

#ifndef _SNARF_ALERT_H_
#define _SNARF_ALERT_H_

typedef struct snarf_alert snarf_alert_t;

typedef struct _SnarfField snarf_field_t;

typedef struct _SnarfValue snarf_value_t;

#include <snarf/alert_print.h>

/**
 * Represents the relative importance of the alert.
 */
typedef enum _snarf_alert_severity
{
    ALERT_VERYLOW  = 1,
    ALERT_LOW      = 2,
    ALERT_MEDIUM   = 3,
    ALERT_HIGH     = 4,
    ALERT_VERYHIGH = 5
} snarf_alert_severity_t;

/**
 * Create a new alert.
 *
 * The new alert will have the 'severity' and 'timestamp' fields set based on
 * those arguments.
 *
 * @param severity the severity of the alert
 * @param timestamp 64-bit (epoch microsecond) timestamp of the alert
 *
 */
snarf_alert_t *
snarf_alert_new(
    snarf_alert_severity_t severity,
    uint64_t               timestamp);

/**
 * Add a set of tags to an alert.
 *
 * @param alert a snarf alert
 * @param tags a comma-separated list of tags to add to the alert
 */
void
snarf_alert_add_tags(
    snarf_alert_t *alert,
    char          *tags);

/**
 * Add an IPv4 flow to an alert. The sip and dip arguments should be in the
 * host machine's byte order, as in struct sockaddr_in.sin_addr.s_addr
 */
void
snarf_alert_add_flow_v4(
    snarf_alert_t *alert,
    uint64_t       stime,
    uint32_t       elapsed,
    uint32_t       sip,
    uint32_t       dip,
    uint16_t       sport,
    uint16_t       dport,
    uint8_t        proto,
    uint32_t       packets,
    uint32_t       bytes,
    uint8_t        flags,
    uint8_t        flags_initial,
    uint16_t       application_id,
    char          *sensor_name,
    char          *flow_class,
    char          *flow_type);

/**
 * Add an IPv6 flow to an alert. The sip and dip arguments should be in
 * network byte order, as in sockaddr_in6.sin6_addr
 */
void
snarf_alert_add_flow_v6(
    snarf_alert_t *alert,
    uint64_t       stime,
    uint32_t       elapsed,
    uint8_t        sip[16],
    uint8_t        dip[16],
    uint16_t       sport,
    uint16_t       dport,
    uint8_t        proto,
    uint32_t       packets,
    uint32_t       bytes,
    uint8_t        flags,
    uint8_t        flags_initial,
    uint16_t       application_id,
    char          *sensor_name,
    char          *flow_class,
    char          *flow_type);

/**
 * Add a text field to an alert
 *
 * @param alert a snarf alert structure
 * @param name the name of the field to add
 * @param value the text to add
 */
void
snarf_alert_add_text_field(
    snarf_alert_t *alert,
    const char    *name,
    const char    *value);

/**
 * Add an integer field to an alert
 *
 * @param alert a snarf alert structure
 * @param name the name of the field to add
 * @param value the integer to add
 */
void
snarf_alert_add_int_field(
    snarf_alert_t *alert,
    const char    *name,
    int64_t        value);

/**
 * Add a double field to an alert
 *
 * @param alert a snarf alert structure
 * @param name the name of the field to add
 * @param value the double value to add
 */
void
snarf_alert_add_double_field(
    snarf_alert_t *alert,
    const char    *name,
    double         value);

/**
 * Add an ipv4 address field to an alert
 *
 * @param alert a snarf alert structure
 * @param name the name of the field to add
 * @param the 32-bit IPv4 address to add, which must be in the host machine's
 * byte order, as in struct sockaddr_in.sin_addr.s_addr
 */
void
snarf_alert_add_ip_field_v4(
    snarf_alert_t *alert,
    const char    *name,
    uint32_t       value);

/**
 * Add an ipv6 address field to an alert
 *
 * @param alert a snarf alert structure
 * @param name the name of the field to add
 * @param the 16-byte IPv6 address to add, in network byte order, as in
 * sockaddr_in6.sin6_addr
 */
void
snarf_alert_add_ip_field_v6(
    snarf_alert_t *alert,
    const char    *name,
    uint8_t       value[16]);

/**
 * Add an IPSet field to an alert
 *
 * @param alert a snarf alert structure
 * @param name the name of the field to add
 * @param data the IPset's binary data
 * @param len the length of the IPset's binary data
 */
void
snarf_alert_add_ipset_field(
    snarf_alert_t *alert,
    const char    *name,
    uint8_t       *data,
    size_t         len);

/**
 * Free an alert's memory
 *
 * @param alert Pointer to the alert structure to be freed
 */
void
snarf_alert_free(
    snarf_alert_t *alert);

/**
 * Retrieve an analysis tag based on a prefix
 *
 * @param alert a snarf alert structure
 * @param prefix tag prefix
 *
 * @return the remainder of the tag after the prefix:, or NULL
 */
char *
snarf_alert_get_analysis_tag(
    snarf_alert_t *alert,
    const char    *prefix);

/**
 * Retrieve a field from an alert
 *
 * @param alert a snarf alert structure
 * @param key the name of the field to retrieve
 *
 * @return a snarf field structure
 */
snarf_field_t *
snarf_alert_get_field(
    snarf_alert_t *alert,
    const char    *key);

/**
 * Get a value stored in an alert field.
 *
 * @param alert a snarf alert structure
 * @param fieldname  the name of the field to retrieve
 * @param index an index into the list of values
 *
 * @return a snarf value structure
 */
snarf_value_t *
snarf_alert_field_value(
    snarf_alert_t *alert,
    char          *fieldname,
    int            index);

/**
 * Get an alert's severity as an integer
 *
 * @param alert a snarf alert structure
 *
 * @return the alert's severity
 */
int
snarf_alert_severity(
    snarf_alert_t *alert);

/**
 * Get the number of values in the given field.
 */
int
snarf_alert_field_value_count(
    snarf_field_t *field);


#endif /* ifndef _SNARF_ALERT_H_ */

/*
 * Local Variables:
 * mode:c
 * indent-tabs-mode:nil
 * c-basic-offset:4
 * End:
 */
