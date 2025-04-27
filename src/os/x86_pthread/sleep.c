#include "sleep.h"
#include <stdlib.h>
#include <pthread.h>


int sleep_ms(long ms) 
{
    struct timespec req, rem;

    if (ms > 999) {
        req.tv_sec = (int)(ms / 1000);
        req.tv_nsec = (ms % 1000) * 1000000L;
    } else {
        req.tv_sec = 0;
        req.tv_nsec = ms * 1000000L;
    }

    return nanosleep(&req, &rem);
}