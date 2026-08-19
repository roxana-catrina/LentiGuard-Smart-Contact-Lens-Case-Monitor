#include "time.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "esp_sntp.h"

void ntp_init(void)
{
    printf("Initializing NTP...\n");

    /*
     * Fusul orar al României:
     *
     * EET  = UTC+2
     * EEST = UTC+3 vara
     *
     * Trecerea ora de vara/iarna este gestionata automat.
     */
    setenv(
        "TZ",
        "EET-2EEST,M3.5.0/3,M10.5.0/4",
        1
    );

    tzset();

    /*
     * Folosim SNTP in modul POLL.
     */
    esp_sntp_setoperatingmode(
        ESP_SNTP_OPMODE_POLL
    );

    /*
     * Server NTP.
     */
    esp_sntp_setservername(
        0,
        "pool.ntp.org"
    );

    /*
     * Pornim SNTP.
     */
    esp_sntp_init();

    printf("NTP started\n");
}


bool ntp_get_current(
    int *hour,
    int *minute,
    int *second
)
{
    time_t now;

    struct tm timeinfo;

    /*
     * Obtinem timpul curent.
     */
    time(&now);

    /*
     * Convertim timpul UTC in timpul local
     * folosind fusul orar setat mai sus.
     */
    localtime_r(
        &now,
        &timeinfo
    );

    /*
     * Daca anul este inca 1970,
     * NTP nu s-a sincronizat.
     */
    if (timeinfo.tm_year < (2020 - 1900))
    {
        return false;
    }

    *hour = timeinfo.tm_hour;
    *minute = timeinfo.tm_min;
    *second = timeinfo.tm_sec;

    return true;
}


void 
ntp_print_current(void)
{
    int hour;
    int minute;
    int second;

    if (ntp_get_current(
            &hour,
            &minute,
            &second))
    {
        printf(
            "CURRENT TIME: %02d:%02d:%02d\n",
            hour,
            minute,
            second
        );
    }
    else
    {
        printf(
            "TIME NOT SYNCHRONIZED\n"
        );
    }
}