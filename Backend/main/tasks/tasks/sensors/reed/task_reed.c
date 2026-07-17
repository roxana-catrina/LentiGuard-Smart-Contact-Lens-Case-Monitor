#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "system_state.h"
#include "task_reed.h"

#define REED_GPIO GPIO_NUM_32


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
{
    bool previous_state = gpio_get_level(GPIO_NUM_32);
    bool previous_state_lens_case = gpio_get_level(GPIO_NUM_33);
    g_system_state.lid_open = (previous_state == 0);
    g_system_state.lens_case_present = (previous_state_lens_case == 0);
   /* if (previous_state == 0)
        printf("previous_state = %d inchis\n", previous_state);
    else
        printf("previous_state = %d deschis\n", previous_state);

    if (previous_state_lens_case == 0)
        printf("previous_state_lens_case = %d cutie inauntru\n", previous_state_lens_case);
    else
        printf("previous_state_lens_case = %d cutie absenta\n", previous_state_lens_case);*/
    while (1)
    {
        bool current_state = gpio_get_level(GPIO_NUM_32);
        bool current_state_lens_case = gpio_get_level(GPIO_NUM_33);
        g_system_state.lid_open = (current_state == 0);
        g_system_state.lens_case_present = (current_state_lens_case == 0);
        if (current_state != previous_state)
        {
           /* if (current_state == 0)
                printf("inchis\n");
            else
                printf("deschis\n");*/

            previous_state = current_state;
        }

        if(current_state_lens_case != previous_state_lens_case)
        {
           /* if (current_state_lens_case == 0)
                printf("cutie inauntru\n");
            else
                printf("cutie absenta\n");*/

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
