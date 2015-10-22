
#ifndef _SOURCE_H_
#define _SOURCE_H_

#include <libsoup/soup.h>

typedef int (*snarf_source_alert_dispatch_fn_t)(snarf_source_t *source,
                                                char           *tags,
                                                snarf_alert_t  *alert);

struct snarf_source
{
    snarf_source_alert_dispatch_fn_t dispatch_fn;
    char *source_name;
    char *source_version;
    char *destination;
    void *dest_socket;
    snarf_config_t *config;
    int debug;
    SoupSession *soup_session;
    SoupMessage *soup_message;
};

#endif 
