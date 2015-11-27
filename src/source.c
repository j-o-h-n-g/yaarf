#include <snarf/snarf.h>
#include <libsoup/soup.h>
#include "source.h"
#include "alert_priv.h"

#include <glib.h>
#include <glib/gstdio.h>
#include <json-glib/json-glib.h>


snarf_source_t *
snarf_source_init(char *source_name,
                  char *source_version,
                  char *destination)
{
//printf("source_init\n");

struct snarf_source *ctx = g_new0(struct snarf_source, 1);

    ctx->source_name    = g_strdup(source_name);
    ctx->source_version = g_strdup(source_version);
    //ctx->destination    = g_strdup("http://localhost:8080");
    ctx->destination    = g_strdup(destination);

    ctx->soup_session = soup_session_new();

    ctx->soup_message = soup_message_new("POST",destination);

    if (ctx->soup_message == NULL) {
	g_error("Error creating soup message");
    }


    // Connect to webserver 
    return ctx;
}

int snarf_source_send_alert(
    snarf_source_t *source,
    char           *tags,
    snarf_alert_t  *alert)
{
//printf("source send alert\n");

snarf_alert_set_generator(alert,source->source_name,source->source_version);

snarf_alert_add_tags(alert,tags);

JsonGenerator *generator = json_generator_new ();
JsonNode * root = (alert->msg);

json_generator_set_root (generator, root);
gchar * str = json_generator_to_data (generator, NULL);

SoupMessage *soup_message;
soup_message = soup_message_new("POST",source->destination); //destination);

soup_message_set_request(soup_message,"application/json",SOUP_MEMORY_COPY,str,strlen(str));
guint status = soup_session_send_message(source->soup_session,soup_message);

if (status < 200 || status > 299) {
	g_critical("Error connecting to webserver status=%d reason=%s\n",status,soup_message->reason_phrase);
	return -1;
}

g_object_unref (soup_message);

snarf_alert_free(alert);

return 0;

}

void
snarf_source_destroy(snarf_source_t *source)
{
   // printf("Source destroy\n");
    g_free(source->source_name);
    g_free(source->source_version);
    g_free(source);
}
