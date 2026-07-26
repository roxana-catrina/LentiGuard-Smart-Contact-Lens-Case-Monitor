#include <stdint.h>
#pragma once
typedef enum
{   DEVICE_ONLINE,
    DEVICE_OFFLINE,
    LID_OPENED,
    LID_CLOSED,
    LENS_CASE_INSERTED,
    LENS_CASE_REMOVED,
    ALARM_STARTED,
    ALARM_STOPPED_DEVICE
} event_type_t;

typedef struct
{
    uint32_t device_id;

    event_type_t event_type;

} event_t;


const char *event_type_to_string(event_type_t type);