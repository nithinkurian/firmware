
#include "rtos.h"
#include "hal_cpu.h"
#include <stdio.h>
#include "notification.h"
#include "task_scheduler.h"


void notify_task_setbit(taskhandle_t dest_task,uint32_t bit)
{

    //disable interrupt
	disable_interrupt();

    TCB_t * dest_task_tcb = dest_task;
    dest_task_tcb->notification_value |= bit;

    if(dest_task_tcb->notification_status == WAITING_FOR_NOTIFICATION)
    {
    	dest_task_tcb->notification_status = NOTIFICATION_PRESENT;
    	schedule();
    }
    else
    {
    	dest_task_tcb->notification_status = NOTIFICATION_PRESENT;
    }

	//enable interrupt
	enable_interrupt();
}

bool notify_task_wait(uint32_t block_time_ms,uint32_t * notification_value)
{
	//disable interrupt
	disable_interrupt();

    TCB_t * current_task_tcb = get_current_task_tcb();
    if(current_task_tcb == NULL)
    {

		//enable interrupt
		enable_interrupt();
        return false;
    }

    if(current_task_tcb->notification_status != NOTIFICATION_PRESENT)
    {
	    current_task_tcb->notification_status = WAITING_FOR_NOTIFICATION;
	    rtos_delay_ms(block_time_ms);
    }

    if(current_task_tcb->notification_status == NOTIFICATION_PRESENT)
    {
        *notification_value = current_task_tcb->notification_value;
        current_task_tcb->notification_value = 0;
        current_task_tcb->notification_status = NO_NOTIFICATION;
        //enable interrupt
		enable_interrupt();
        return true;
    }
    else
    {
	    current_task_tcb->notification_status = NO_NOTIFICATION;
	    //enable interrupt
		enable_interrupt();
	    return false;
    }

}