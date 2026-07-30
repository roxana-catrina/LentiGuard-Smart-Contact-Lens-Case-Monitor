
#include <stdbool.h>
#include <stdint.h>
typedef struct
{
    bool lid_open;

    bool lens_case_present;

    bool alarm_active;


    bool wifi_connected;
    uint8_t battery_level ;

} system_state_t;



void system_state_init(void);


void system_state_set_lid_open(bool state);


void system_state_set_lens_case_present(bool state);


void system_state_set_alarm_active(bool state);


void system_state_set_wifi_connected(bool state);


system_state_t system_state_get(void);



// problema cu race condition, foloseste mutex pentru a proteja accesul la g_system_state in task-uri