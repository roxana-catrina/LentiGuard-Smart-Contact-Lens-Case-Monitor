#include "system_state.h"

volatile system_state_t g_system_state;

void system_state_init(void)
{
    g_system_state.lid_open = false;
    g_system_state.lens_case_present = false;
    g_system_state.alarm_active = false;
    g_system_state.camera_recording = false;
}