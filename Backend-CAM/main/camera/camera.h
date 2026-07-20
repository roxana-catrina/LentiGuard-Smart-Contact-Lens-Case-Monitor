void camera_init(void);
#include "esp_camera.h"
camera_fb_t *camera_capture(void);

void camera_release(camera_fb_t *fb);