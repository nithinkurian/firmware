#include "software_timer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "rtos.h"
#include <stddef.h>
#include "task_scheduler.h"
#include <limits.h>

typedef struct
{
    uint32_t period;
    uint32_t expiry_time;
    bool auto_reload;
    bool using;
    void (*callback)( timerhandle_t timer_handle );
} TimerCB_t;


#define MAX_TIMERS 2

uint8_t used_timer_count = 0;

TimerCB_t user_timer[MAX_TIMERS];

bool timer_modified = false;


timerhandle_t create_and_start_software_timer(uint32_t ms,bool auto_reload,void callback( timerhandle_t timer_handle ))
{
    if(used_timer_count<MAX_TIMERS)
    {
        for(uint8_t index = 0; index < MAX_TIMERS; index++ )
        {
            TimerCB_t * timer_tcb = &user_timer[index];
            if((timer_tcb != NULL) &&
                (timer_tcb->using == false) && 
                (callback!=NULL) && (ms != 0))
            {
                uint32_t initial_tick = get_rtos_tick_count();
                timer_tcb->period = tick_in_hz*ms/1000;
                timer_tcb->expiry_time = timer_tcb->period + initial_tick;
                timer_tcb->auto_reload = auto_reload;
                timer_tcb->callback = callback;
                timer_tcb->using = true;
                timer_modified = true;
                return timer_tcb;
            }
        }
    }
    else
    {
        printf("Increase MAX_TIMERS\n");
        while(1);
    }
    return NULL;
} 


uint32_t next_expiry = UINT32_MAX;
uint8_t next_expiry_index = 0xFF;

void update_next_expiry()
{
    uint32_t local_expiry = UINT32_MAX;
    uint8_t local_expiry_index = 0xFF;

    for(uint8_t index = 0; index < MAX_TIMERS; index++ )
    {
        TimerCB_t * timer_tcb = &user_timer[index];
        if( (timer_tcb != NULL) &&
            (timer_tcb->using == true) && 
            (timer_tcb->callback!=NULL) && 
            (timer_tcb->period != 0) &&
            (timer_tcb->expiry_time != 0))
        {
            if(timer_tcb->expiry_time < local_expiry)
            {
                local_expiry = timer_tcb->expiry_time;
                local_expiry_index = index;
            }
        }
    }
    next_expiry = local_expiry;
    next_expiry_index = local_expiry_index;

}

void timer_manager(void* parameters)
{
    printf("Timer manager is running.....\n");
    while(1)
    {
        if(timer_modified)
        {
            update_next_expiry();
            timer_modified = false;
        }
        if(get_rtos_tick_count()>next_expiry)
        {
            TimerCB_t * timer_tcb = &user_timer[next_expiry_index];
            if( (timer_tcb != NULL) &&                
            (timer_tcb->callback!=NULL) && 
            (timer_tcb->using == true) && 
            (timer_tcb->period != 0) &&
            (timer_tcb->expiry_time != 0))
            {
                timer_tcb->callback(timer_tcb);
                if(timer_tcb->auto_reload)
                {
                    timer_tcb->expiry_time += timer_tcb->period;
                }
                else
                {
                    timer_tcb->period = 0;
                    timer_tcb->expiry_time = 0;
                    timer_tcb->auto_reload = false;
                    timer_tcb->callback = NULL;
                    timer_tcb->using = false;
                }
                timer_modified = true;
            }
        }
        rtos_delay_ms(1);
    }
}