#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "system_state.h"
#include "task_led.h"
#include "task_reed.h"
#define LED_GPIO_GREEN GPIO_NUM_25
#define LED_GPIO_RED   GPIO_NUM_26
#define LED_GPIO_WHITE GPIO_NUM_27


static void led_test_task(void *pvParameters)
{
    while (1) {
      /* // 1. LED verde aprins
        gpio_set_level(LED_GPIO_GREEN, 1);
        gpio_set_level(LED_GPIO_RED, 0);
        gpio_set_level(LED_GPIO_WHITE, 0);

        printf("LED verde aprins\n");
        vTaskDelay(pdMS_TO_TICKS(1000));


        // 2. LED roșu aprins
        gpio_set_level(LED_GPIO_GREEN, 0);
        gpio_set_level(LED_GPIO_RED, 1);
        gpio_set_level(LED_GPIO_WHITE, 0);

        printf("LED rosu aprins\n");
        vTaskDelay(pdMS_TO_TICKS(1000));


        // 3. LED alb aprins
        gpio_set_level(LED_GPIO_GREEN, 0);
        gpio_set_level(LED_GPIO_RED, 0);
        gpio_set_level(LED_GPIO_WHITE, 1);

        printf("LED alb aprins\n");
        vTaskDelay(pdMS_TO_TICKS(1000));


        // 4. Toate LED-urile stinse
        gpio_set_level(LED_GPIO_GREEN, 0);
        gpio_set_level(LED_GPIO_RED, 0);
        gpio_set_level(LED_GPIO_WHITE, 0);

        printf("Toate LED-urile sunt stinse\n");
        vTaskDelay(pdMS_TO_TICKS(1000));

        UBaseType_t stack_ramasa = uxTaskGetStackHighWaterMark(NULL);

        printf("Stack minim ramas pentru led_test_task: %u bytes\n",(unsigned int)stack_ramasa);  
   */ 
  system_state_t state = system_state_get();
  if(state.lid_open==0){
    gpio_set_level(LED_GPIO_WHITE, 1);
    gpio_set_level(LED_GPIO_RED, 0);
    gpio_set_level(LED_GPIO_GREEN, 0);
  //  printf("capac deschis\n");
  }
  else if(state.lid_open==1 && state.lens_case_present==1){
    gpio_set_level(LED_GPIO_GREEN, 1);
    gpio_set_level(LED_GPIO_RED, 0);
    gpio_set_level(LED_GPIO_WHITE, 0);
   // printf("capac inchis, cutie inauntru\n");

  }
  else if(state.lid_open==1 && state.lens_case_present==0){
    gpio_set_level(LED_GPIO_RED, 1);
    gpio_set_level(LED_GPIO_GREEN, 0);
    gpio_set_level(LED_GPIO_WHITE, 0);
   // printf("capac inchis, cutie absenta\n");
  }
   vTaskDelay(pdMS_TO_TICKS(50));
        }
}


void led_task_start(void)
{
   
    gpio_reset_pin(LED_GPIO_GREEN);
    gpio_reset_pin(LED_GPIO_RED);
    gpio_reset_pin(LED_GPIO_WHITE);

   
    gpio_set_direction(LED_GPIO_GREEN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GPIO_RED, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GPIO_WHITE, GPIO_MODE_OUTPUT);

    
    gpio_set_level(LED_GPIO_GREEN, 0);
    gpio_set_level(LED_GPIO_RED, 0);
    gpio_set_level(LED_GPIO_WHITE, 0);

    // Creează task-ul FreeRTOS
    xTaskCreate(
        led_test_task,      // Funcția task-ului
        "led_test_task",    // Numele task-ului
        2048,               // Memoria stivei în bytes
        NULL,               // Nu trimitem parametri
        1,                  // Prioritatea task-ului
        NULL                // Nu păstrăm handle-ul
    );
}