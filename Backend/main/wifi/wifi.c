#include "wifi.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "http_server.h"
#include "ntp/ntp.h"
#include <stdio.h>
#include "system_state.h"
#include "communication/http_client/http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//static const char *TAG = "WIFI";


static void wifi_event_handler(void *arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_data)
{
    if (event_base == WIFI_EVENT &&
        event_id == WIFI_EVENT_STA_START)
    {
        printf("WiFi start\n");

        esp_wifi_connect();
    }


    else if (event_base == WIFI_EVENT &&
             event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        printf("WiFi disconnected\n");
        system_state_set_wifi_connected(false);
        esp_wifi_connect();
    }


    else if (event_base == IP_EVENT &&
             event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;

        printf("IP primit: " IPSTR "\n",
       IP2STR(&event->ip_info.ip));
       system_state_set_wifi_connected(true);
       system_state_t state = system_state_get();
       printf("WIFI STATE AFTER GOT IP: %d\n", state.wifi_connected);
        http_server_start();
         http_client_send_status();
         ntp_init();
         vTaskDelay(pdMS_TO_TICKS(3000));

        ntp_print_current();
         
}
}


void wifi_init(void)
{
    nvs_flash_init();


    esp_netif_init();//pregătește stiva TCP/IP și mecanismele necesare 


    esp_event_loop_create_default(); // pt ca handler sa primeasca evenimnete


    esp_netif_create_default_wifi_sta();



    wifi_init_config_t wifi_config = 
        WIFI_INIT_CONFIG_DEFAULT();


    esp_wifi_init(&wifi_config); // initiere driver wifi cu configuratia implicita



    esp_wifi_set_mode(WIFI_MODE_STA);



    wifi_config_t sta_config = {
        .sta = {
            .ssid = "DIGI-b4Nu",
            .password = "kkMsmgUTj4"
        },
    };


    esp_wifi_set_config(
        WIFI_IF_STA,
        &sta_config
    );



    esp_event_handler_register( //orice eveniment ex: start, stop, disconnect etc
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        wifi_event_handler,
        NULL
    );


    esp_event_handler_register(
        IP_EVENT,
        IP_EVENT_STA_GOT_IP,
        wifi_event_handler,
        NULL
    );



    esp_wifi_start();
   // event_t event;


}
