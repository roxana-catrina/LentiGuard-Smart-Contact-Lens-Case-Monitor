#include <stdio.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "alarm_scheduler.h"
#include "alarm_queue.h"
#include "ntp.h"
#include "communication/http_client/http_client.h"

static int alarm_hour = 0;
static int alarm_minute = 0;
static bool alarm_enabled = false;

static void alarm_scheduler_task(void *pvParameters)
{
    int last_triggered_hour = -1;
    int last_triggered_minute = -1;

    /*
     * Prima citire a alarmei.
     */
    if (http_client_get_alarm(
            &alarm_hour,
            &alarm_minute,
            &alarm_enabled))
    {
        printf(
            "SCHEDULER ALARM: %02d:%02d enabled=%d\n",
            alarm_hour,
            alarm_minute,
            alarm_enabled
        );
    }
    else
    {
        printf("FAILED TO GET ALARM\n");
    }

    int refresh_counter = 0;

    while (1)
    {
        int current_hour;
        int current_minute;
        int current_second;

        /*
         * =========================
         * REFRESH ALARM
         * =========================
         *
         * Facem GET la fiecare 30 secunde.
         */
        if (refresh_counter >= 30)
        {
            int new_hour;
            int new_minute;
            bool new_enabled;

            printf(
                "REFRESHING ALARM FROM BACKEND\n"
            );

            if (http_client_get_alarm(
                    &new_hour,
                    &new_minute,
                    &new_enabled))
            {
                alarm_hour = new_hour;
                alarm_minute = new_minute;
                alarm_enabled = new_enabled;

                printf(
                    "UPDATED ALARM: %02d:%02d enabled=%d\n",
                    alarm_hour,
                    alarm_minute,
                    alarm_enabled
                );
            }
            else
            {
                printf(
                    "FAILED TO REFRESH ALARM\n"
                );
            }

            refresh_counter = 0;
        }

        /*
         * =========================
         * CURRENT TIME
         * =========================
         */

        if (ntp_get_current(
                &current_hour,
                &current_minute,
                &current_second))
        {
            printf(
                "CURRENT TIME: %02d:%02d:%02d\n",
                current_hour,
                current_minute,
                current_second
            );

            /*
             * =========================
             * ALARM CHECK
             * =========================
             */

            if (alarm_enabled &&
                current_hour == alarm_hour &&
                current_minute == alarm_minute)
            {
                /*
                 * Pornim alarma o singură dată
                 * în minutul respectiv.
                 */
                if (last_triggered_hour != current_hour ||
                    last_triggered_minute != current_minute)
                {
                    printf(
                        "ALARM TIME REACHED!\n"
                    );

                    printf(
                        "Sending ALARM_START\n"
                    );

                    alarm_command_t command =
                        ALARM_START;

                    if (xQueueSend(
                            alarm_queue,
                            &command,
                            portMAX_DELAY) == pdTRUE)
                    {
                        printf(
                            "ALARM_START SENT TO QUEUE\n"
                        );
                    }
                    else
                    {
                        printf(
                            "FAILED TO SEND ALARM_START\n"
                        );
                    }

                    last_triggered_hour =
                        current_hour;

                    last_triggered_minute =
                        current_minute;
                }
            }
        }
        else
        {
            printf(
                "TIME NOT SYNCHRONIZED\n"
            );
        }

        /*
         * Verificăm ora în fiecare secundă.
         */
        vTaskDelay(
            pdMS_TO_TICKS(1000)
        );

        refresh_counter++;
    }
}

void alarm_scheduler_start(void)
{
    xTaskCreate(
        alarm_scheduler_task,
        "alarm_scheduler",
        4096,
        NULL,
        1,
        NULL
    );
}