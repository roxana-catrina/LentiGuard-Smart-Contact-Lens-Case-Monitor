#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "system_state.h"
#include "task_reed.h"
#include "events/event.h"
#include "communication/http_client/http_client.h"
#define REED_GPIO GPIO_NUM_32
#define DEVICE_ID 1

void reed_gpio_init(void)
{
    gpio_config_t reed_config = {
        .pin_bit_mask = 1ULL << GPIO_NUM_32 |
                        1ULL << GPIO_NUM_33,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&reed_config);
}

static void reed_task(void *pvParameters)
{  system_state_t state;

state = system_state_get();
printf("lid_open = %d\n", state.lid_open);
printf("lens_case_present = %d\n", state.lens_case_present);
    bool previous_state = gpio_get_level(GPIO_NUM_32);
    bool previous_state_lens_case = gpio_get_level(GPIO_NUM_33);
   state.lid_open = (previous_state == 0);
    state.lens_case_present = (previous_state_lens_case == 0);
   
    while (1)
    {
        bool current_state = gpio_get_level(GPIO_NUM_32);
        bool current_state_lens_case = gpio_get_level(GPIO_NUM_33);
       system_state_set_lid_open(current_state == 0);
        system_state_set_lens_case_present(current_state_lens_case == 0);
         event_t event;
         event.device_id = DEVICE_ID;
        if (current_state != previous_state)
        {
            if (current_state == 0)
                event.event_type = LID_CLOSED;
            else
                event.event_type = LID_OPENED;

            previous_state = current_state;
            system_state_t state = system_state_get();

printf("REED WIFI STATE: %d\n", state.wifi_connected);
           if (state.wifi_connected)
{
    http_client_send_event(&event);
}
else
{
    printf("WiFi not connected - event not sent\n");
}
        }

        if(current_state_lens_case != previous_state_lens_case)
        {
           if (current_state_lens_case == 0)
                  event.event_type = LENS_CASE_INSERTED;
            else
                event.event_type = LENS_CASE_REMOVED;

            system_state_t state = system_state_get();

printf("REED WIFI STATE: %d\n", state.wifi_connected);
             if (state.wifi_connected)
{
    http_client_send_event(&event);
}
else
{
    printf("WiFi not connected - event not sent\n");
}
            previous_state_lens_case = current_state_lens_case;
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void reed_task_start(void)
{
    xTaskCreate(
        reed_task,
        "reed_task",
        2048,
        NULL,
        1,
        NULL
    );
}
