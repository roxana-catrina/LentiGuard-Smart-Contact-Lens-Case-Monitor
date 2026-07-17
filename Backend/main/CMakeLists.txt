idf_component_register(SRCS "tasks/tasks/leds/task_led.c" 
                            "tasks/tasks/sensors/reed/task_reed.c"
                            "system/system_state.c"
                            "main.c"
                    INCLUDE_DIRS "."
                                "tasks/tasks/leds"
                                "tasks/tasks/sensors/reed"
                                "system")
