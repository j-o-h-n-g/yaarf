#ifndef _SNARF_ALERT_PRIV_H_
#define _SNARF_ALERT_PRIV_H_

#include <json-glib/json-glib.h>
#include <snarf/alert.h>

#ifndef TCPFLAGS_STRLEN
#    define TCPFLAGS_STRLEN 9

/* Shamelessly stolen from sku-string.c */
#    define CWR_FLAG (1 << 7)          /* 128 */
#    define ECE_FLAG (1 << 6)          /*  64 */
#    define URG_FLAG (1 << 5)          /*  32 */
#    define ACK_FLAG (1 << 4)          /*  16 */
#    define PSH_FLAG (1 << 3)          /*   8 */
#    define RST_FLAG (1 << 2)          /*   4 */
#    define SYN_FLAG (1 << 1)          /*   2 */
#    define FIN_FLAG (1)               /*   1 */
#endif /* ifndef TCPFLAGS_STRLEN */


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
