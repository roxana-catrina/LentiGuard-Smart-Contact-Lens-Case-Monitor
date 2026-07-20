#include <stdio.h>
#include "camera.h"

#include "sdcard.h"
void app_main(void)
{
 printf("Salut! ESP32-CAM functioneaza!\n");

 camera_init(); sdcard_init();
 //sdcard_write_test_file();
 camera_fb_t *fb = camera_capture();
 if(fb==NULL)
 {
    printf("Eroare la capturarea imaginii!\n");
    return;
 }
else sdcard_save_jpg(fb, "/sdcard/photo.jpg");

camera_release(fb);

 
}