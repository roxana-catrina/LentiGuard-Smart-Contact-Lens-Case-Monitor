#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "alarm_commands.h"

extern QueueHandle_t alarm_queue;


void alarm_queue_init(void);