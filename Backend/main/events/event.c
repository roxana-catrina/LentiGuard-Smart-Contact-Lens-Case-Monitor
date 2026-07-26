#include "event.h"


const char *event_type_to_string(event_type_t type)
{
    switch (type)
    {
        case DEVICE_ONLINE:
    return "DEVICE_ONLINE";
        case DEVICE_OFFLINE:
            return "DEVICE_OFFLINE";
        case LID_OPENED:
            return "LID_OPENED";
        case LID_CLOSED:
            return "LID_CLOSED";
        case LENS_CASE_INSERTED:
            return "LENS_CASE_INSERTED";
        case LENS_CASE_REMOVED:
            return "LENS_CASE_REMOVED";
        case ALARM_STARTED:
            return "ALARM_STARTED";
        case ALARM_STOPPED_DEVICE:
            return "ALARM_STOPPED_DEVICE";
        default:
            return "UNKNOWN_EVENT_TYPE";
    }
}