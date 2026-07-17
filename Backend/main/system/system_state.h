
#include <stdbool.h>
typedef struct
{
    bool lid_open;
    bool lens_case_present;
    bool alarm_active;
    bool camera_recording;
} system_state_t;

extern volatile system_state_t g_system_state;

void system_state_init(void);
