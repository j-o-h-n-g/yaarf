#ifndef _SNARF_ALERT_PRIV_H_
#define _SNARF_ALERT_PRIV_H_

#include <json-glib/json-glib.h>
#include <snarf/alert.h>


struct snarf_alert
{
	JsonNode *msg;
};

void
snarf_alert_set_generator(
    snarf_alert_t *alert,
    char          *name,
    char          *version);


  
#endif
