#include "system_state.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

static system_state_t system_state;
static SemaphoreHandle_t state_mutex;

void system_state_init(void)
{
    state_mutex = xSemaphoreCreateMutex();
    system_state.lid_open = false;

    system_state.lens_case_present = false;

    system_state.alarm_active = false;

    system_state.camera_recording = false;

    system_state.wifi_connected = false;
}



void system_state_set_lid_open(bool state)
{    xSemaphoreTake(state_mutex, portMAX_DELAY);

    system_state.lid_open = state;
        xSemaphoreGive(state_mutex);

}



void system_state_set_lens_case_present(bool state)
{xSemaphoreTake(state_mutex, portMAX_DELAY);
    system_state.lens_case_present = state;
      xSemaphoreGive(state_mutex);
}



void system_state_set_alarm_active(bool state)
{xSemaphoreTake(state_mutex, portMAX_DELAY);
    system_state.alarm_active = state;
      xSemaphoreGive(state_mutex);
}



void system_state_set_wifi_connected(bool state)
{xSemaphoreTake(state_mutex, portMAX_DELAY);
    system_state.wifi_connected = state;
      xSemaphoreGive(state_mutex);
}



system_state_t system_state_get(void)
{
    system_state_t copy;


    xSemaphoreTake(state_mutex, portMAX_DELAY);


    copy = system_state;


    xSemaphoreGive(state_mutex);


    return copy;
}