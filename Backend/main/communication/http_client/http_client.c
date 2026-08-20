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

bool http_client_get_alarms(
    alarm_t alarms[],
    int max_alarms,
    int *alarm_count
)
{
    char response[1024] = {0};

    *alarm_count = 0;

    alarm_response_t alarm_response = {
        .buffer = response,
        .buffer_size = sizeof(response),
        .data_len = 0
    };

    esp_http_client_config_t config = {
        .url = "http://192.168.1.128:8080/api/alarm/1",
        .event_handler = alarm_http_event_handler,
        .user_data = &alarm_response
    };

    esp_http_client_handle_t client =
        esp_http_client_init(&config);

    if (client == NULL)
    {
        printf("Failed to create HTTP client\n");
        return false;
    }

    esp_http_client_set_method(
        client,
        HTTP_METHOD_GET
    );

    printf("GETTING ALARMS FROM BACKEND\n");

    esp_err_t err =
        esp_http_client_perform(client);

    if (err != ESP_OK)
    {
        printf(
            "GET ALARMS ERROR: %s\n",
            esp_err_to_name(err)
        );

        esp_http_client_cleanup(client);
        return false;
    }

    int status =
        esp_http_client_get_status_code(client);

    printf(
        "ALARM RESPONSE STATUS: %d\n",
        status
    );

    if (status != 200)
    {
        printf("Unexpected HTTP status\n");

        esp_http_client_cleanup(client);
        return false;
    }

    printf(
        "ALARM RESPONSE LENGTH: %d\n",
        alarm_response.data_len
    );

    printf(
        "ALARM RESPONSE: %s\n",
        response
    );

    esp_http_client_cleanup(client);

    if (alarm_response.data_len == 0)
    {
        printf("Alarm response is empty\n");
        return false;
    }

    /*
     * =========================
     * PARSE JSON ARRAY
     * =========================
     */

    cJSON *root =
        cJSON_Parse(response);

    if (root == NULL)
    {
        printf(
            "Failed to parse alarms JSON\n"
        );

        return false;
    }

    if (!cJSON_IsArray(root))
    {
        printf(
            "Alarm response is not an array\n"
        );

        cJSON_Delete(root);
        return false;
    }

    int array_size =
        cJSON_GetArraySize(root);

    printf(
        "NUMBER OF ALARMS: %d\n",
        array_size
    );

    for (int i = 0;
         i < array_size && *alarm_count < max_alarms;
         i++)
    {
        cJSON *alarm_json =
            cJSON_GetArrayItem(root, i);

        if (!cJSON_IsObject(alarm_json))
        {
            continue;
        }

        cJSON *id =
            cJSON_GetObjectItem(
                alarm_json,
                "id"
            );

        cJSON *alarmTime =
            cJSON_GetObjectItem(
                alarm_json,
                "alarmTime"
            );

        cJSON *enabledJson =
            cJSON_GetObjectItem(
                alarm_json,
                "enabled"
            );

        if (!cJSON_IsNumber(id) ||
            !cJSON_IsString(alarmTime) ||
            !cJSON_IsBool(enabledJson))
        {
            printf(
                "Invalid alarm at index %d\n",
                i
            );

            continue;
        }

        int hour;
        int minute;

        if (sscanf(
                alarmTime->valuestring,
                "%d:%d",
                &hour,
                &minute
            ) != 2)
        {
            printf(
                "Invalid alarm time: %s\n",
                alarmTime->valuestring
            );

            continue;
        }

        alarms[*alarm_count].id =
            id->valueint;

        alarms[*alarm_count].hour =
            hour;

        alarms[*alarm_count].minute =
            minute;

        alarms[*alarm_count].enabled =
            cJSON_IsTrue(enabledJson);

        printf(
            "ALARM %d: id=%d time=%02d:%02d enabled=%d\n",
            *alarm_count,
            alarms[*alarm_count].id,
            alarms[*alarm_count].hour,
            alarms[*alarm_count].minute,
            alarms[*alarm_count].enabled
        );

        (*alarm_count)++;
    }

    cJSON_Delete(root);

    printf(
        "TOTAL ALARMS LOADED: %d\n",
        *alarm_count
    );

    return true;
}


bool http_client_delete_alarm(int alarm_id)
{
    char url[128];

    snprintf(
        url,
        sizeof(url),
        "http://192.168.1.128:8080/api/alarm/%d",
        alarm_id
    );

    printf(
        "DELETING ALARM ID: %d\n",
        alarm_id
    );

    esp_http_client_config_t config = {
        .url = url
    };

    esp_http_client_handle_t client =
        esp_http_client_init(&config);

    if (client == NULL)
    {
        printf(
            "FAILED TO CREATE DELETE CLIENT\n"
        );

        return false;
    }

    esp_http_client_set_method(
        client,
        HTTP_METHOD_DELETE
    );

    esp_err_t err =
        esp_http_client_perform(client);

    if (err != ESP_OK)
    {
        printf(
            "DELETE ALARM ERROR: %s\n",
            esp_err_to_name(err)
        );

        esp_http_client_cleanup(client);

        return false;
    }

    int status =
        esp_http_client_get_status_code(client);

    printf(
        "DELETE ALARM STATUS: %d\n",
        status
    );

    esp_http_client_cleanup(client);

    if (status >= 200 && status < 300)
    {
        printf(
            "ALARM ID %d DELETED\n",
            alarm_id
        );

        return true;
    }

    printf(
        "FAILED TO DELETE ALARM ID %d\n",
        alarm_id
    );

    return false;
}