#ifndef TIME_H
#define TIME_H

#include <stdbool.h>

void ntp_init(void);

bool ntp_get_current(
    int *hour,
    int *minute,
    int *second
);

void ntp_print_current(void);

#endif