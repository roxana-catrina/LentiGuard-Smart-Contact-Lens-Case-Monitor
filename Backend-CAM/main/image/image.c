#include "image.h"

#include <stdlib.h>
#include <stdint.h>

uint8_t *image_rgb565_to_rgb888(camera_fb_t *fb)
{
    if (fb == NULL)
    {
        return NULL;
    }

    int pixels = fb->width * fb->height;

    uint8_t *rgb888 = malloc(pixels * 3);

    if (rgb888 == NULL)
    {
        return NULL;
    }

    uint16_t *rgb565 = (uint16_t *)fb->buf;

    for (int i = 0; i < pixels; i++)
    {
        uint16_t pixel = rgb565[i];

        uint8_t r = (pixel >> 11) & 0x1F;
        uint8_t g = (pixel >> 5) & 0x3F;
        uint8_t b = pixel & 0x1F;

        rgb888[i * 3 + 0] = (r << 3) | (r >> 2);
        rgb888[i * 3 + 1] = (g << 2) | (g >> 4);
        rgb888[i * 3 + 2] = (b << 3) | (b >> 2);
    }

    return rgb888;
}