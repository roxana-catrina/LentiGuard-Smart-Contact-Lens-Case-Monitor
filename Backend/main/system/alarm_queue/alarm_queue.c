#include "alarm_queue.h"
#include "freertos/queue.h"

QueueHandle_t alarm_queue;


void alarm_queue_init(void)
{
    alarm_queue = xQueueCreate(
        5,
        sizeof(alarm_command_t)
    );
}