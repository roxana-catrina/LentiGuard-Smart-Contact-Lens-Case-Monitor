#include "camera.h"

#include <stdio.h>

#include "esp_camera.h"
#include "esp_log.h"
static const char *TAG = "SDCARD";
static camera_config_t camera_config_init(void)
{
    camera_config_t config = {

        // Alimentare cameră
        .pin_pwdn  = 32,
        .pin_reset = -1,

        // Ceas cameră
        .pin_xclk = 0,

        // Magistrala SCCB (I2C pentru cameră)
        .pin_sccb_sda = 26,
        .pin_sccb_scl = 27,

        // Date cameră
        .pin_d7 = 35,
        .pin_d6 = 34,
        .pin_d5 = 39,
        .pin_d4 = 36,
        .pin_d3 = 21,
        .pin_d2 = 19,
        .pin_d1 = 18,
        .pin_d0 = 5,

        // Sincronizare
        .pin_vsync = 25,
        .pin_href  = 23,
        .pin_pclk  = 22,

        // LEDC pentru XCLK
        .xclk_freq_hz = 20000000,
        .ledc_timer   = LEDC_TIMER_0,
        .ledc_channel = LEDC_CHANNEL_0,

        // Format imagine
      .pixel_format = PIXFORMAT_RGB565,

        // Rezoluție
       .frame_size = FRAMESIZE_QVGA,
        // Calitate JPEG
        .jpeg_quality = 12,

        // Număr frame buffer-e
        .fb_count = 1,

        // Locație frame buffer
         .fb_location = CAMERA_FB_IN_DRAM,

        // Modul captură
        .grab_mode = CAMERA_GRAB_WHEN_EMPTY
    };

return config;
}


void camera_init(void)
{
    camera_config_t config = camera_config_init();

    esp_err_t err = esp_camera_init(&config);

    if (err != ESP_OK)
    {
        ESP_LOGE("CAMERA", "Camera init failed! Error = 0x%x", err);
        return;
    }

    sensor_t *s = esp_camera_sensor_get();
    ESP_LOGI("CAMERA", "PID = 0x%04X", s->id.PID);

ESP_LOGI("CAMERA", "PIXFORMAT = %d", s->pixformat);

ESP_LOGI("CAMERA", "FRAMESIZE = %d", s->status.framesize);

    ESP_LOGI("CAMERA", "Camera initialized successfully!");
    ESP_LOGI("CAMERA", "Sensor PID: 0x%04X", s->id.PID);
}


camera_fb_t *camera_capture(void)
{
    camera_fb_t *fb = esp_camera_fb_get();

    if (fb == NULL)
    {
        ESP_LOGE("CAMERA", "Capture failed!");
        return NULL;
    }

    ESP_LOGI("CAMERA", "Photo captured!");
    ESP_LOGI("CAMERA", "Width  : %d", fb->width);
    ESP_LOGI("CAMERA", "Height : %d", fb->height);
    ESP_LOGI("CAMERA", "Length : %d bytes", fb->len);
    ESP_LOGI("CAMERA", "Format : %d", fb->format);
    uint16_t *p = (uint16_t *)fb->buf;

ESP_LOGI("CAMERA", "Pixel0 = 0x%04X", p[0]);
ESP_LOGI("CAMERA", "Pixel1 = 0x%04X", p[1]);
ESP_LOGI("CAMERA", "Pixel2 = 0x%04X", p[2]);
ESP_LOGI("CAMERA", "Pixel3 = 0x%04X", p[3]);

    return fb;
}

void camera_release(camera_fb_t *fb){
    esp_camera_fb_return(fb);
}