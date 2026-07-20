

void sdcard_init(void);
void sdcard_write_test_file(void);
#include "esp_camera.h"
bool sdcard_save_bmp(camera_fb_t *fb,
                     const char *filename);
bool sdcard_save_jpg(camera_fb_t *fb, const char *filename);


