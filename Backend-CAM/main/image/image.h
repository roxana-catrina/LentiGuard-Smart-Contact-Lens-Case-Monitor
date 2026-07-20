#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include "esp_camera.h"

uint8_t *image_rgb565_to_rgb888(camera_fb_t *fb);

#endif