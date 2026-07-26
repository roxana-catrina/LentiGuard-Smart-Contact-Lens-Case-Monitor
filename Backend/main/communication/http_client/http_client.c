#include "http_client.h"
#include <stdio.h>
#include "esp_http_client.h"


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

