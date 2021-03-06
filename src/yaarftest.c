#include <snarf/snarf.h>

int main () {

snarf_alert_t *alert;
snarf_alert_severity_t severity = 1;
uint64_t timestamp = 12345;
snarf_source_t *source;

source = snarf_source_init("testyaarf","1.0.0","http://whois:8080/alert");


alert=snarf_alert_new(severity,timestamp);
snarf_alert_add_text_field(alert,"hello","blah");
snarf_alert_add_text_field(alert,"goodbye","wang");

snarf_alert_add_int_field(alert,"an int",1234);

snarf_alert_add_double_field(alert,"a double",122.345);

snarf_alert_add_flow_v4(alert,123,345,222,333,666,777,7,4321,5432,1,2,4,"sensor1","all","in");
uint8_t sip[16] = {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6};

snarf_alert_add_flow_v6(alert,123,345,sip,sip,222,333,666,777,7,1,1,1,"sensor1","all","in");

snarf_source_send_alert(source,"abcd",alert);

alert=snarf_alert_new(severity,timestamp);
snarf_alert_add_flow_v4(alert,123,345,222,333,666,777,7,4321,54321,1,1,1,"sensor1","all","in");

snarf_alert_add_ip_field_v4(alert,"foo",256);
snarf_source_send_alert(source,"abcd",alert);

snarf_source_destroy(source);

}
