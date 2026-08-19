#include "http_client.h"
#include <stdio.h>
#include "esp_http_client.h"
#include "system_state.h"
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "cJSON.h"

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
    .url = "http://192.168.1.128:8080/api/events"
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
    .url = "http://192.168.1.128:8080/api/alarm/events"
};

esp_http_client_handle_t client =
    esp_http_client_init(&config);
printf("HTTP CLIENT CREATED\n");
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
printf("HTTP CLIENT CLEANUP\n");
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
    .url = "http://192.168.1.128:8080/api/status"
};

esp_http_client_handle_t client =
    esp_http_client_init(&config);
printf("HTTP CLIENT CREATED\n");
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
printf("HTTP CLIENT CLEANUP\n");
esp_http_client_cleanup(client);
}


typedef struct {
    char *buffer;
    int buffer_size;
    int data_len;
} alarm_response_t;


static esp_err_t alarm_http_event_handler(
    esp_http_client_event_t *evt)
{
    alarm_response_t *response =
        (alarm_response_t *)evt->user_data;

    if (evt->event_id == HTTP_EVENT_ON_DATA)
    {
        printf(
            "HTTP EVENT DATA: %d bytes\n",
            evt->data_len
        );

        /*
         * Verificăm să avem suficient spațiu în buffer.
         */
        if (response->data_len + evt->data_len
            < response->buffer_size)
        {
            memcpy(
                response->buffer + response->data_len,
                evt->data,
                evt->data_len
            );

            response->data_len += evt->data_len;

            /*
             * Terminator pentru string C.
             */
            response->buffer[
                response->data_len
            ] = '\0';
        }
        else
        {
            printf("Alarm response buffer too small\n");
        }
    }

    return ESP_OK;
}


bool http_client_get_alarm(
    int *hour,
    int *minute,
    bool *enabled
)
{
    char response[256] = {0};

    /*
     * Structura în care vom salva
     * răspunsul primit de la backend.
     */
    alarm_response_t alarm_response = {
        .buffer = response,
        .buffer_size = sizeof(response),
        .data_len = 0
    };

    /*
     * Configurarea clientului HTTP.
     */
    esp_http_client_config_t config = {
        .url = "http://192.168.1.128:8080/api/alarm/1",
        .event_handler = alarm_http_event_handler,
        .user_data = &alarm_response
    };

    esp_http_client_handle_t client =
        esp_http_client_init(&config);

    if (client == NULL)
    {
        printf(
            "Failed to create HTTP client\n"
        );

        return false;
    }

    /*
     * GET request.
     */
    esp_http_client_set_method(
        client,
        HTTP_METHOD_GET
    );

    printf(
        "GETTING ALARM FROM BACKEND\n"
    );

    /*
     * Trimitem request-ul.
     *
     * Răspunsul va fi primit prin
     * alarm_http_event_handler().
     */
    esp_err_t err =
        esp_http_client_perform(client);

    if (err != ESP_OK)
    {
        printf(
            "GET ALARM ERROR: %s\n",
            esp_err_to_name(err)
        );

        esp_http_client_cleanup(client);

        return false;
    }

    /*
     * Verificăm statusul HTTP.
     */
    int status =
        esp_http_client_get_status_code(
            client
        );

    printf(
        "ALARM RESPONSE STATUS: %d\n",
        status
    );

    if (status != 200)
    {
        printf(
            "Unexpected HTTP status\n"
        );

        esp_http_client_cleanup(client);

        return false;
    }

    /*
     * Afișăm ce am primit.
     */
    printf(
        "ALARM RESPONSE LENGTH: %d\n",
        alarm_response.data_len
    );

    printf(
        "ALARM RESPONSE: %s\n",
        response
    );

    esp_http_client_cleanup(client);

    /*
     * Verificăm dacă am primit efectiv body-ul.
     */
    if (alarm_response.data_len == 0)
    {
        printf(
            "Alarm response is empty\n"
        );

        return false;
    }

    /*
     * =========================
     * PARSE JSON
     * =========================
     */

    cJSON *root =
        cJSON_Parse(response);

    if (root == NULL)
    {
        printf(
            "Failed to parse alarm JSON\n"
        );

        return false;
    }

    /*
     * Obținem alarmTime.
     *
     * Exemplu:
     *
     * "alarmTime": "11:30:00"
     */
    cJSON *alarmTime =
        cJSON_GetObjectItem(
            root,
            "alarmTime"
        );

    /*
     * Obținem enabled.
     *
     * Exemplu:
     *
     * "enabled": true
     */
    cJSON *enabledJson =
        cJSON_GetObjectItem(
            root,
            "enabled"
        );

    /*
     * Verificăm tipurile JSON.
     */
    if (!cJSON_IsString(alarmTime) ||
        !cJSON_IsBool(enabledJson))
    {
        printf(
            "Invalid alarm JSON\n"
        );

        cJSON_Delete(root);

        return false;
    }

    printf(
        "ALARM TIME: %s\n",
        alarmTime->valuestring
    );

    printf(
        "ALARM ENABLED: %s\n",
        cJSON_IsTrue(enabledJson)
            ? "true"
            : "false"
    );

    /*
     * =========================
     * PARSE TIME
     * =========================
     *
     * Backend:
     *
     * 11:30:00
     *
     * Noi extragem:
     *
     * hour   = 11
     * minute = 30
     */

    if (sscanf(
            alarmTime->valuestring,
            "%d:%d",
            hour,
            minute
        ) != 2)
    {
        printf(
            "Invalid alarm time: %s\n",
            alarmTime->valuestring
        );

        cJSON_Delete(root);

        return false;
    }

    /*
     * Salvăm enabled.
     */
    *enabled =
        cJSON_IsTrue(enabledJson);

    printf(
        "PARSED ALARM: %02d:%02d enabled=%d\n",
        *hour,
        *minute,
        *enabled
    );

    /*
     * Eliberăm JSON-ul.
     */
    cJSON_Delete(root);

    return true;
}