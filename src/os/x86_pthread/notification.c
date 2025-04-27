
#include "rtos.h"
#include "hal_cpu.h"
#include <stdio.h>
#include "task_scheduler.h"
#include "sleep.h"

extern uint32_t tick_in_hz;

void notify_task_setbit(taskhandle_t dest_task,uint32_t bit)
{
    TCB_t * dest_task_tcb = dest_task;
    dest_task_tcb->notification_value |= bit;
    dest_task_tcb->notification_status = true;
}

bool notify_task_wait(uint32_t block_time_ms,uint32_t * notification_value)
{
    //disable interrupt
    disable_interrupt();
    uint32_t tick_count = tick_in_hz*block_time_ms/1000;
    uint32_t initial_tick = get_tick_count();
    TCB_t * current_task_tcb = get_current_task_tcb();
    if(current_task_tcb == NULL)
    {
        printf("current_task_tcb is NULL\n");
        while(1);
        return false;
    }
    while(initial_tick+ tick_count>get_tick_count())
    {
        if(current_task_tcb->notification_status != 0)
        {
            *notification_value = current_task_tcb->notification_value;
            current_task_tcb->notification_value = 0;
            current_task_tcb->notification_status = false;

            //enable interrupt
            enable_interrupt();
            return true;
        }
        sleep_ms(1);
    }

    //enable interrupt
    enable_interrupt();
    return false;
}