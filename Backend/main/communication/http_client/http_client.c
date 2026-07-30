#include "http_client.h"
#include <stdio.h>
#include "esp_http_client.h"
#include "system_state.h"

void http_client_send_event(const event_t *event)
{
char json[128];

snprintf(
    json,
    sizeof(json),
    "{"
    "\"deviceId\":%u,"
    "\"event\":\"%s\""
    "}",
    (unsigned int)event->device_id,
    event_type_to_string(event->event_type)

);
printf("Sending event: %s\n", json);


esp_http_client_config_t config =
{
    .url = "http://192.168.1.129:8080/api/events"
};

esp_http_client_handle_t client =
    esp_http_client_init(&config);

esp_http_client_set_method(
    client,
    HTTP_METHOD_POST
);


esp_http_client_set_header(
    client,
    "Content-Type",
    "application/json"
);
  
esp_http_client_set_post_field(
    client,
    json,
    strlen(json)
);

esp_err_t err = esp_http_client_perform(client); // trimitere backend

if (err == ESP_OK)
{
    printf("Eveniment trimis cu succes!\n");
}
else
{
    printf("Eroare la trimitere: %s\n", esp_err_to_name(err));
}

esp_http_client_cleanup(client);
}


void http_client_send_alarm_event(const event_t *event)
{
char json[128];

snprintf(
    json,
    sizeof(json),
    "{"
    "\"deviceId\":%u,"
    "\"event\":\"%s\""
    "}",
    (unsigned int)event->device_id,
    event_type_to_string(event->event_type)

);
printf("Sending event: %s\n", json);


esp_http_client_config_t config =
{
    .url = "http://192.168.1.129:8080/api/alarm/events"
};

esp_http_client_handle_t client =
    esp_http_client_init(&config);

esp_http_client_set_method(
    client,
    HTTP_METHOD_POST
);


esp_http_client_set_header(
    client,
    "Content-Type",
    "application/json"
);
  
esp_http_client_set_post_field(
    client,
    json,
    strlen(json)
);

esp_err_t err = esp_http_client_perform(client); // trimitere backend

if (err == ESP_OK)
{
    printf("Eveniment trimis cu succes!\n");
}
else
{
    printf("Eroare la trimitere: %s\n", esp_err_to_name(err));
}

esp_http_client_cleanup(client);
}


void http_client_send_status(void){


char json[128];
system_state_t state = system_state_get();
snprintf(
    json,
    sizeof(json),
    "{"
    "\"deviceId\":1,"
    "\"lidOpen\":%s,"
    "\"lensCasePresent\":%s,"
    "\"alarmActive\":%s,"
    "\"wifiConnected\":%s,"
    "\"batteryLevel\":%u"
    "}",
    state.lid_open ? "true" : "false",
    state.lens_case_present ? "true" : "false",
    state.alarm_active ? "true" : "false",
    state.wifi_connected ? "true" : "false",
    state.battery_level
);


esp_http_client_config_t config =
{
    .url = "http://192.168.1.129:8080/api/status"
};

esp_http_client_handle_t client =
    esp_http_client_init(&config);

esp_http_client_set_method(
    client,
    HTTP_METHOD_POST
);


esp_http_client_set_header(
    client,
    "Content-Type",
    "application/json"
);
  printf("Sending status: %s\n", json);
esp_http_client_set_post_field(
    client,
    json,
    strlen(json)
);

esp_err_t err = esp_http_client_perform(client); // trimitere backend

if (err == ESP_OK)
{
    printf("Eveniment trimis cu succes!\n");
}
else
{
    printf("Eroare la trimitere: %s\n", esp_err_to_name(err));
}

esp_http_client_cleanup(client);
}