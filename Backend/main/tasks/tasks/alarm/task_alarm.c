#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

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

    gpio_set_level(BUZZER_GPIO, 0);
}

static void buzzer_task(void *pvParameters)
{
    gpio_set_level(BUZZER_GPIO, 1);

    vTaskDelay(pdMS_TO_TICKS(1000));

    gpio_set_level(BUZZER_GPIO, 0);

    vTaskDelete(NULL);
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