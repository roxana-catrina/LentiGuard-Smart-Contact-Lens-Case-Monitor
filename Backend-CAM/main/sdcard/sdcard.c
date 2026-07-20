#include "sdcard.h"

#include <stdio.h>

#include "esp_log.h"
#include "esp_vfs_fat.h"

#include "driver/sdmmc_host.h"
#include "driver/sdmmc_defs.h"

#include "sdmmc_cmd.h"


#include "driver/gpio.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"  

#include <stdbool.h>
#include "esp_camera.h"


#include "img_converters.h"
#include "esp_jpeg_enc.h"
#include "img_converters.h"
static const char *TAG = "SDCARD";

void sdcard_init(void)
{
sdmmc_host_t host = SDMMC_HOST_DEFAULT();
sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();


esp_vfs_fat_mount_config_t mount_config = {
    .format_if_mount_failed = false,
    .max_files = 5,
    .allocation_unit_size = 16 * 1024
};
 sdmmc_card_t *card;
 esp_err_t ret = esp_vfs_fat_sdmmc_mount(
    "/sdcard",
    &host,
    &slot_config,
    &mount_config,
    &card
);
if (ret != ESP_OK)
{
    ESP_LOGE(TAG, "Failed to mount SD card");
    return;
}
ESP_LOGI(TAG, "SD card mounted successfully!");
sdmmc_card_print_info(stdout, card);
}

void sdcard_write_test_file(void)
{
FILE *file = fopen("/sdcard/test.txt", "w");

if (file == NULL)
{
    ESP_LOGE(TAG, "Nu pot crea fisierul!");
    return;
}

fprintf(file, "Salut din ESP32-CAM!\n");
fprintf(file, "Acesta este primul fisier salvat pe card.\n");

fclose(file);

ESP_LOGI(TAG, "Fisierul test.txt a fost salvat.");
}



bool sdcard_save_jpg(camera_fb_t *fb, const char *filename)
{
    jpeg_enc_config_t cfg = DEFAULT_JPEG_ENC_CONFIG();

    cfg.width = fb->width;
    cfg.height = fb->height;
    cfg.src_type = JPEG_PIXEL_FORMAT_RGB565_BE;
    cfg.subsampling = JPEG_SUBSAMPLE_420;
    cfg.quality = 60;
    cfg.rotate = JPEG_ROTATE_0D;

    jpeg_enc_handle_t enc = NULL;

    jpeg_error_t ret = jpeg_enc_open(&cfg, &enc);

    if (ret != JPEG_ERR_OK)
    {
        ESP_LOGE(TAG, "Encoder open failed");
        return false;
    }

    int outbuf_size = 80 * 1024;

    uint8_t *outbuf = calloc(1, outbuf_size);

    if (outbuf == NULL)
    {
        ESP_LOGE(TAG, "Cannot allocate JPEG buffer");
        jpeg_enc_close(enc);
        return false;
    }

    int out_len = 0;

    ret = jpeg_enc_process(
            enc,
            fb->buf,
            fb->len,
            outbuf,
            outbuf_size,
            &out_len);

    if (ret != JPEG_ERR_OK)
    {
        ESP_LOGE(TAG, "JPEG encode failed");

        free(outbuf);
        jpeg_enc_close(enc);

        return false;
    }

    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        ESP_LOGE(TAG, "Cannot create file");

        free(outbuf);
        jpeg_enc_close(enc);

        return false;
    }

    fwrite(outbuf, 1, out_len, file);

    fclose(file);

    free(outbuf);

    jpeg_enc_close(enc);

    ESP_LOGI(TAG, "JPEG saved! Size = %d", out_len);

    return true;
}