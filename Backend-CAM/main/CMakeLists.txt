idf_component_register(SRCS "main.c"
                        "camera/camera.c"
                        "sdcard/sdcard.c"
                        "image/image.c"
                    INCLUDE_DIRS "."
                    "camera"
                    "sdcard"
                    "image"
                    REQUIRES
                        fatfs
                        sdmmc)