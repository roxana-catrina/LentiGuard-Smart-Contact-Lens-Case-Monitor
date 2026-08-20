#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "system_state.h"
#include "system/alarm_queue/alarm_queue.h"
#define BUZZER_GPIO GPIO_NUM_23
#include "events/event.h"
#include "communication/http_client/http_client.h"

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
    event_t event;
    event.device_id = 1;

    alarm_message_t message;

    while (1)
    {
        if (xQueueReceive(
                alarm_queue,
                &message,
                portMAX_DELAY) == pdTRUE)
        {
            printf(
                "Command received: %d, alarm ID: %d\n",
                message.command,
                message.alarm_id
            );

            if (message.command == ALARM_START)
            {
                printf(
                    "ALARM_START, ID: %d\n",
                    message.alarm_id
                );

                // Pornim buzzerul
                gpio_set_level(BUZZER_GPIO, 1);

                // Trimitem evenimentul către backend
                event.event_type = ALARM_STARTED;

                http_client_send_alarm_event(&event);

                // Ștergem alarma care tocmai a sunat
                if (http_client_delete_alarm(message.alarm_id))
                {
                    printf(
                        "Alarm %d deleted successfully\n",
                        message.alarm_id
                    );
                }
                else
                {
                    printf(
                        "Failed to delete alarm %d\n",
                        message.alarm_id
                    );
                }
            }
            else if (message.command == ALARM_STOP)
            {
                printf("ALARM_STOP\n");

                // Oprim buzzerul
                gpio_set_level(BUZZER_GPIO, 0);

                // Trimitem evenimentul către backend
                event.event_type = ALARM_STOPPED_DEVICE;

                http_client_send_alarm_event(&event);
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