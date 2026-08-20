#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "tasks/tasks/leds/task_led.h"
#include "tasks/tasks/sensors/reed/task_reed.h"
#include "tasks/tasks/alarm/task_alarm.h"
#include "tasks/tasks/sensors/button/task_button.h"
#include "system/alarm_queue/alarm_queue.h"
#include "system/system_state.h"
#include "wifi/wifi.h"
#include "communication/http_client/http_client.h"
#include "alarm_scheduler.h"


void app_main(void)
{     
     system_state_init();
      wifi_init();

    alarm_queue_init();

   reed_gpio_init();
   buzzer_gpio_init();
   button_buzzer_gpio_init();
   led_task_start();
     reed_task_start();
    buzzer_task_start();
    button_buzzer_task_start();
   alarm_scheduler_start();
   

     
}