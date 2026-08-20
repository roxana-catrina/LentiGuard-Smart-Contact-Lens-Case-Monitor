#include "events/event.h"
#include <stdbool.h>
void http_client_init(void);

void http_client_send_event(const event_t *event);

void http_client_send_status(void);

void http_client_send_alarm_event(const event_t *event);

bool http_client_get_alarm(int *hour,int *minute,bool *enabled
);


#define MAX_ALARMS 10

typedef struct {
    int id;
    int hour;
    int minute;
    bool enabled;
} alarm_t;

bool http_client_get_alarms(
    alarm_t alarms[],
    int max_alarms,
    int *alarm_count
);


bool http_client_delete_alarm(int alarm_id);