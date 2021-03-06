#include "alert_priv.h"

#include <snarf/snarf.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <time.h>

#include <glib-object.h>
#include <json-glib/json-glib.h>


snarf_alert_t *
snarf_alert_new(
    snarf_alert_severity_t severity,
    uint64_t               timestamp)
{

snarf_alert_t *alert = g_new0(snarf_alert_t, 1);
JsonBuilder *builder;

// Populate the envelope
builder=json_builder_new();
json_builder_begin_object(builder);
json_builder_set_member_name(builder,"envelope");
json_builder_begin_object(builder);
json_builder_set_member_name(builder,"severity");
json_builder_add_int_value (builder, severity);
json_builder_set_member_name(builder,"timestamp");
char jsontime[32];
time_t sectime=timestamp / (1000*1000);
struct tm gmt;
gmtime_r(&sectime,&gmt);
strftime(jsontime,21,"%Y-%m-%dT%H:%M:%SZ",&gmt);
json_builder_add_string_value(builder,jsontime);
json_builder_end_object(builder);
json_builder_set_member_name(builder,"body");

json_builder_begin_object(builder);
json_builder_end_object(builder);
json_builder_end_object(builder);
alert->msg=json_builder_get_root(builder);

return alert;

}

void
snarf_alert_free(snarf_alert_t *alert)
{

  json_node_free (alert->msg);
  g_free (alert);


}

static GString* snarf_alert_flags_to_string(uint8_t flags) {

GString *str = g_string_new(NULL); //TCPFLAGS_STRLEN);

if (flags & FIN_FLAG)
	g_string_append_c(str,'F');
if (flags & SYN_FLAG)
	g_string_append_c(str,'S');
if (flags & RST_FLAG)
        g_string_append_c(str,'R');
if (flags & PSH_FLAG)
        g_string_append_c(str,'P');
if (flags & ACK_FLAG)
        g_string_append_c(str,'A');
if (flags & URG_FLAG)
        g_string_append_c(str,'U');
if (flags & ECE_FLAG)
        g_string_append_c(str,'E');
if (flags & CWR_FLAG)
        g_string_append_c(str,'C');

return str;

}

void
snarf_alert_add_flow_v4(snarf_alert_t *alert,
                        uint64_t stime, uint32_t elapsed,
                        uint32_t sip, uint32_t dip,
                        uint16_t sport, uint16_t dport,
                        uint8_t proto,
                        uint32_t packets, uint32_t bytes,
                        uint8_t flags, uint8_t flags_initial,
                        uint16_t application_id,
                        char *sensor_name,
                        char *flow_class, char *flow_type)
{

JsonBuilder *builder;

// Populate the envelope
builder=json_builder_new();
json_builder_begin_array(builder);
json_builder_begin_object(builder);

json_builder_set_member_name(builder,"stime");
char jsontime[32];
time_t sectime = stime / (1000*1000);
struct tm gmt;
gmtime_r(&sectime,&gmt);
strftime(jsontime,21,"%Y-%m-%dT%H:%M:%SZ",&gmt);
json_builder_add_string_value(builder,jsontime);

json_builder_set_member_name(builder,"elapsed");
json_builder_add_int_value(builder,elapsed);

struct in_addr ip;

ip.s_addr=htonl(sip);
json_builder_set_member_name(builder,"sip");
json_builder_add_string_value(builder,inet_ntoa(ip));

ip.s_addr=htonl(dip);
json_builder_set_member_name(builder,"dip");
json_builder_add_string_value(builder,inet_ntoa(ip));

json_builder_set_member_name(builder,"sport");
json_builder_add_int_value(builder,sport);

json_builder_set_member_name(builder,"dport");
json_builder_add_int_value(builder,dport);

json_builder_set_member_name(builder,"proto");
json_builder_add_int_value(builder,proto);

json_builder_set_member_name(builder,"packets");
json_builder_add_int_value(builder,packets);

json_builder_set_member_name(builder,"bytes");
json_builder_add_int_value(builder,bytes);

// flags
json_builder_set_member_name(builder,"flags");
GString *flag_string = snarf_alert_flags_to_string(flags);
json_builder_add_string_value(builder,flag_string->str);
g_string_free(flag_string,TRUE);


// flags initial
json_builder_set_member_name(builder,"flags_initial");
GString *flag_initial_string = snarf_alert_flags_to_string(flags_initial);
json_builder_add_string_value(builder,flag_initial_string->str);
//g_print(flag_initial_string);
g_string_free(flag_initial_string,TRUE);

// application id
json_builder_set_member_name(builder,"application_id");
json_builder_add_int_value(builder,application_id);

// sensor
json_builder_set_member_name(builder,"sensor_name");
json_builder_add_string_value(builder,sensor_name);

// flow class
json_builder_set_member_name(builder,"flow_class");
json_builder_add_string_value(builder,flow_class);

// flow type
json_builder_set_member_name(builder,"flow_type");
json_builder_add_string_value(builder,flow_type);

json_builder_end_object(builder);
json_builder_end_array(builder);
//json_builder_end_object(builder);

JsonNode *root = json_builder_get_root(builder);

JsonObject * rootobj = json_node_get_object (alert->msg);
JsonObject * bodyobj = json_object_get_object_member(rootobj,"body");
json_object_set_member(bodyobj,"flow",root);

}

void
snarf_alert_add_flow_v6(
    snarf_alert_t *alert,
    uint64_t stime, uint32_t elapsed,
    uint8_t sip[16], uint8_t dip[16],
    uint16_t sport, uint16_t dport,
    uint8_t proto,
    uint32_t packets, uint32_t bytes,
    uint8_t flags, uint8_t flags_initial,
    uint16_t application_id,
    char *sensor_name,
    char *flow_class, char *flow_type)
{
snarf_alert_add_text_field(alert,"add_flow_v6","MISSING");
//NOOP


}

void
snarf_alert_add_ip_field_v4(snarf_alert_t *alert,
                            const char    *name,
                            uint32_t       value)
{
// Add IP field to body
JsonNode *node;

JsonObject * rootobj = json_node_get_object (alert->msg);
JsonObject * bodyobj = json_object_get_object_member(rootobj,"body");

JsonNode * stringnode = json_node_alloc();

struct in_addr ip;
ip.s_addr=htonl(value);
stringnode=json_node_init_string(stringnode,inet_ntoa(ip));
json_object_set_member(bodyobj,name,stringnode);

}

void
snarf_alert_add_ip_field_v6(snarf_alert_t *alert,
                            const char    *name,
                            uint8_t       value[16])
{

snarf_alert_add_text_field(alert,name,"ip_field_v6_MISSING");
}


void
snarf_alert_add_text_field(snarf_alert_t *alert,
                           const char    *name,
                           const char    *value)
{

// Add text field to body
JsonNode *node;

JsonObject * rootobj = json_node_get_object (alert->msg);
JsonObject * bodyobj = json_object_get_object_member(rootobj,"body");

JsonNode * stringnode = json_node_alloc();
stringnode=json_node_init_string(stringnode,value);
json_object_set_member(bodyobj,name,stringnode);

}


void
snarf_alert_add_int_field(snarf_alert_t *alert,
                          const char    *name,
                          int64_t        value)
{

JsonObject * rootobj = json_node_get_object (alert->msg);
JsonObject * bodyobj = json_object_get_object_member(rootobj,"body");
JsonNode * intnode = json_node_alloc();
intnode=json_node_init_int(intnode,value);
json_object_set_member(bodyobj,name,intnode);

}

void
snarf_alert_add_double_field(snarf_alert_t *alert,
                             const char    *name,
                             double         value)
{
JsonObject * rootobj = json_node_get_object (alert->msg);
JsonObject * bodyobj = json_object_get_object_member(rootobj,"body");
JsonNode * doublenode = json_node_alloc();
doublenode=json_node_init_double(doublenode,value);
json_object_set_member(bodyobj,name,doublenode);

}

void
snarf_alert_add_tags(snarf_alert_t *alert, char *tags)
{
    gchar **taglist  = NULL;
    char  **p        = NULL;
    int     tagcount = 0;
    char   *tag      = NULL;

    JsonObject * rootobj = json_node_get_object (alert->msg);
    JsonObject * envelopeobj = json_object_get_object_member(rootobj,"envelope");

    JsonArray *analysis_tags=json_array_new();

    taglist = g_strsplit_set(tags, ", \t\n\v\f\r", 0);
    for (p = taglist, tagcount = 0; p && *p; p++)
    {
	tag=*p;
	if (!strlen(tag))
	{
	    continue;
	}
 	json_array_add_string_element(analysis_tags,tag);
    }

    json_object_set_array_member(envelopeobj,"analysis_tags",analysis_tags);

}

void
snarf_alert_set_generator(snarf_alert_t *alert, char *name, char *version) 
{

    JsonObject * rootobj = json_node_get_object (alert->msg);
    JsonObject * envelopeobj = json_object_get_object_member(rootobj,"envelope");

    json_object_set_string_member(envelopeobj,"generator",name);
    json_object_set_string_member(envelopeobj,"version",version);

}

void
snarf_alert_add_ipset_field(snarf_alert_t *alert,
                            const char    *name,
                            uint8_t       *data,
                            size_t         len)
{

snarf_alert_add_text_field(alert,name,"ipset_field_MISSING");
//NOP    

}    


