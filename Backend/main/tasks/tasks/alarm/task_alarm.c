#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "system_state.h"
#include "system/alarm_queue/alarm_queue.h"
#define BUZZER_GPIO GPIO_NUM_23


void buzzer_gpio_init(void)
{
    gpio_config_t buzzer_config = {
        .pin_bit_mask = 1ULL << BUZZER_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&buzzer_config);

    gpio_set_level(BUZZER_GPIO, 1);
}





static void buzzer_task(void *pvParameters)
{
    alarm_command_t command;

    while (1)
    {
        if (xQueueReceive(alarm_queue, &command, portMAX_DELAY) == pdTRUE)
        {
            if (command == ALARM_START)
            {
                gpio_set_level(BUZZER_GPIO, 1);
            }
            else if (command == ALARM_STOP)
            {
                gpio_set_level(BUZZER_GPIO, 0);
            }
        }
    }
}

void buzzer_task_start(void)
{
    xTaskCreate(
        buzzer_task,
        "buzzer_task",
        2048,
        NULL,
        1,
        NULL
    );
}