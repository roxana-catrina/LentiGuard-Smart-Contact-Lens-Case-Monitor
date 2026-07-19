#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "system/alarm_queue/alarm_queue.h"
#define BUTTON_BUZZER_GPIO GPIO_NUM_18



void button_buzzer_gpio_init(void)
{
    gpio_config_t button_buzzer_config = {
        .pin_bit_mask = 1ULL << BUTTON_BUZZER_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE ,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&button_buzzer_config);

    gpio_set_level(BUTTON_BUZZER_GPIO, 0);
}

static void button_buzzer_task(void *pvParameters)
{  alarm_command_t command;
    while (1)
    {
        int button_state = gpio_get_level(BUTTON_BUZZER_GPIO);

        if (button_state == 0)
        {    printf("Buton apasat\n");
            command = ALARM_STOP;
            xQueueSend(alarm_queue, &command, 0);
        }
       /* else if (button_state == 1)
        {
            printf("Buton neapasat\n");
            command = ALARM_START;
            xQueueSend(alarm_queue, &command, 0);
        }*/

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}



void button_buzzer_task_start(void)
{
    xTaskCreate(
        button_buzzer_task,
        "button_buzzer_task",
        2048,
        NULL,
        1,
        NULL
    );
}