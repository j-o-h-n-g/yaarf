#include "snarf.h"
#include "source.h"

#include <snarf/snarf.h>
#include <glib.h>

void snarf_init() 
{

}

void snarf_term()
{

}

uint64_t
snarf_get_current_timestamp()
{
    GTimeVal gtv;
    uint64_t res;

    g_get_current_time(&gtv);
    res = (1000 * 1000 * (uint64_t) gtv.tv_sec) + gtv.tv_usec;
    g_debug("get_current_timestamp: %" PRIu64, res);
    return res;
}


