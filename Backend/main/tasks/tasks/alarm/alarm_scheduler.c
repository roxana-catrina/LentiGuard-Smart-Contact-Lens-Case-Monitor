#include <stdio.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "alarm_scheduler.h"
#include "alarm_queue.h"
#include "ntp.h"
#include "communication/http_client/http_client.h"

#define MAX_ALARMS 10

static alarm_t alarms[MAX_ALARMS];
static int alarm_count = 0;

static void alarm_scheduler_task(void *pvParameters)
{
    /*
     * Prima citire a alarmelor din backend.
     */
    if (http_client_get_alarms(
            alarms,
            MAX_ALARMS,
            &alarm_count))
    {
        printf(
            "ALARMS LOADED: %d\n",
            alarm_count
        );
    }
    else
    {
        printf(
            "FAILED TO GET ALARMS\n"
        );
    }

    /*
     * Pentru fiecare alarmă memorăm dacă
     * a fost deja declanșată în minutul respectiv.
     *
     * 0 = nu a fost declanșată
     * 1 = a fost declanșată
     */
    bool triggered[MAX_ALARMS] = {false};

    int refresh_counter = 0;

    while (1)
    {
        int current_hour;
        int current_minute;
        int current_second;

        /*
         * =========================
         * REFRESH ALARMS
         * =========================
         *
         * Luăm lista nouă din backend
         * la fiecare 30 secunde.
         */
        if (refresh_counter >= 30)
        {
            int new_alarm_count = 0;

            printf(
                "REFRESHING ALARMS FROM BACKEND\n"
            );

            if (http_client_get_alarms(
                    alarms,
                    MAX_ALARMS,
                    &new_alarm_count))
            {
                alarm_count =
                    new_alarm_count;

                printf(
                    "UPDATED ALARMS: %d\n",
                    alarm_count
                );

                /*
                 * Resetăm starea de trigger
                 * pentru alarmele existente.
                 */
                for (int i = 0;
                     i < MAX_ALARMS;
                     i++)
                {
                    triggered[i] = false;
                }

                /*
                 * Afișăm toate alarmele.
                 */
                for (int i = 0;
                     i < alarm_count;
                     i++)
                {
                    printf(
                        "ALARM[%d]: id=%d "
                        "%02d:%02d enabled=%d\n",

                        i,
                        alarms[i].id,
                        alarms[i].hour,
                        alarms[i].minute,
                        alarms[i].enabled
                    );
                }
            }
            else
            {
                printf(
                    "FAILED TO REFRESH ALARMS\n"
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
             * CHECK ALL ALARMS
             * =========================
             */

            for (int i = 0;
                 i < alarm_count;
                 i++)
            {
                /*
                 * Ignorăm alarma dacă
                 * este dezactivată.
                 */
                if (!alarms[i].enabled)
                {
                    continue;
                }

                /*
                 * Verificăm ora și minutul.
                 */
                if (current_hour ==
                        alarms[i].hour &&
                    current_minute ==
                        alarms[i].minute)
                {
                    /*
                     * Nu declanșăm aceeași alarmă
                     * de mai multe ori în același minut.
                     */
                    if (!triggered[i])
                    {
                        printf(
                            "ALARM TIME REACHED!\n"
                        );

                        printf(
                            "ALARM ID: %d\n",
                            alarms[i].id
                        );

                        printf(
                            "ALARM TIME: %02d:%02d\n",
                            alarms[i].hour,
                            alarms[i].minute
                        );

                        /*
                         * Construim mesajul pentru queue.
                         */
                        alarm_message_t message = {
                            .command = ALARM_START,
                            .alarm_id = alarms[i].id
                        };

                        /*
                         * Trimitem alarma către
                         * buzzer_task.
                         */
                        if (xQueueSend(
                                alarm_queue,
                                &message,
                                portMAX_DELAY)
                                == pdTRUE)
                        {
                            printf(
                                "ALARM_START SENT TO QUEUE\n"
                            );

                            printf(
                                "ALARM ID SENT: %d\n",
                                message.alarm_id
                            );
                        }
                        else
                        {
                            printf(
                                "FAILED TO SEND "
                                "ALARM_START\n"
                            );
                        }

                        triggered[i] = true;
                    }
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