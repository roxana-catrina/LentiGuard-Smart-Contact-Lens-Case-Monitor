#include "http_server.h"

#include "esp_http_server.h"
#include "esp_log.h"
#include "system/system_state.h"

static const char *TAG = "HTTP_SERVER";


static esp_err_t status_handler(httpd_req_t *req)
{
    system_state_t state = system_state_get();


    char response[200];


    snprintf(response,
             sizeof(response),
             "{"
             "\"lid_open\":%d,"
             "\"lens_case_present\":%d,"
             "\"alarm_active\":%d,"
             "\"wifi_connected\":%d"
             "}",
             state.lid_open,
             state.lens_case_present,
             state.alarm_active,
             state.wifi_connected
    );


    httpd_resp_send(
        req,
        response,
        HTTPD_RESP_USE_STRLEN
    );


    return ESP_OK;
}


void http_server_start(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();


    httpd_handle_t server = NULL;


    if (httpd_start(&server, &config) == ESP_OK)
    {

        httpd_uri_t status_uri = {
            .uri = "/status",
            .method = HTTP_GET,
            .handler = status_handler,
            .user_ctx = NULL
        };


        httpd_register_uri_handler(
            server,
            &status_uri
        );


        ESP_LOGI(TAG, "HTTP server started");
    }
}