/*
 * config_parser.h
 * Structured Network Alert Reporting Framework Config File Parsing Routines
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

#include <snarf/snarf.h>

#ifndef _SNARF_CONFIG_PARSER_H_
#define _SNARF_CONFIG_PARSER_H_

snarf_config_t *
snarf_load_config(
    char *cfgfile,
    char *section);
snarf_config_t *
snarf_find_config_key(
    snarf_config_t *root,
    const char     *key);
void *
snarf_get_config_value(
    snarf_config_t *root,
    char           *key);

#endif /* ifndef _SNARF_CONFIG_PARSER_H_ */

/*
 * Local Variables:
 * mode:c
 * indent-tabs-mode:nil
 * c-basic-offset:4
 * End:
 */
