#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "tasks/tasks/leds/task_led.h"
#include "tasks/tasks/sensors/reed/task_reed.h"
#include "tasks/tasks/alarm/task_alarm.h"


void app_main(void)
{
   
   reed_gpio_init();
   buzzer_gpio_init();
   led_task_start();
     reed_task_start();
    buzzer_task_start();

     
}