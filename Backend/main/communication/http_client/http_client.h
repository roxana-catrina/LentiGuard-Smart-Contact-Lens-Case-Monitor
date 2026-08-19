#include "events/event.h"
#include <stdbool.h>
void http_client_init(void);

void http_client_send_event(const event_t *event);

void http_client_send_status(void);

void http_client_send_alarm_event(const event_t *event);

bool http_client_get_alarm(int *hour,int *minute,bool *enabled
);
