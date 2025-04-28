
#include "rtos.h"
#include "hal_cpu.h"
#include <stddef.h>
#include <stdio.h>
#include "task_scheduler.h"
#include "notification.h"
#include "queue.h"
#include "software_timer.h"



static void idle_task(void* parameters); //Idle task


__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_tasks_stack(void);
void switch_sp_to_psp(void);
__attribute__((naked)) void switch_sp_to_psp(void);
void pend_pendsv();
uint32_t task_stack_init(uint32_t psp_value, void (*task_handler)(void* parameters));
void update_global_tick_count(void);
uint32_t get_tick_count(void);
void init_idle_task_stack(void);
void init_timer_manager_stack(void);
void unblock_tasks(void);


TCB_t user_tasks[MAX_TASKS];
uint32_t g_tick_count = 0;
uint32_t current_task = 1;
uint32_t next_task_start = FIRST_STACK_START;
uint8_t idle_task_index = 0;
uint8_t timer_manager_index = 1;
uint8_t next_task_index = 2;
uint32_t tick_in_hz = 0;


void idle_task(void* parameters)
{
	while(1);
}

char * get_rtos_name()
{
	return "CustomRTOS";
}

void run_scheduler()
{
	tick_in_hz = TICK_HZ;
	init_systick_timer(TICK_HZ);
	init_idle_task_stack();
	init_timer_manager_stack();
	init_scheduler_stack(SCHED_STACK_START);
	switch_sp_to_psp();
	if(user_tasks[1].task_handler == NULL)
	{
		printf("First task is not created, please create first task\n");
		while(1);
	}
	user_tasks[1].task_handler(NULL);
}

taskhandle_t create_task(void (*task_handler)(void*),uint16_t stack_size, uint8_t priority)
{
	//disable interrupt
	disable_interrupt();
	if(next_task_index >= MAX_TASKS)
	{
		printf("TCB are not available, please increase MAX_TASKS\n");
		while(1);
	}
	TCB_t * next_task = &user_tasks[next_task_index];
	next_task->task_handler = task_handler;
	next_task->psp_value = next_task_start;
	next_task->current_state = TASK_READY_STATE;
	next_task->psp_value=task_stack_init(next_task->psp_value,next_task->task_handler);

	next_task_start -= stack_size;
	next_task_index++;

	//enable interrupt
	enable_interrupt();
	return next_task;
}

void init_idle_task_stack(void)
{
	//disable interrupt
	disable_interrupt();
	user_tasks[idle_task_index].psp_value = IDLE_STACK_START;
	user_tasks[idle_task_index].task_handler = idle_task;
	user_tasks[idle_task_index].current_state = TASK_READY_STATE;
	user_tasks[idle_task_index].psp_value=task_stack_init(user_tasks[idle_task_index].psp_value,user_tasks[idle_task_index].task_handler);

	//enable interrupt
	enable_interrupt();
}

void init_timer_manager_stack(void)
{

	//disable interrupt
	disable_interrupt();
	user_tasks[timer_manager_index].psp_value = TIMER_STACK_START;
	user_tasks[timer_manager_index].task_handler = timer_manager;
	user_tasks[timer_manager_index].current_state = TASK_READY_STATE;
	user_tasks[timer_manager_index].psp_value=task_stack_init(user_tasks[timer_manager_index].psp_value,user_tasks[timer_manager_index].task_handler);

	//enable interrupt
	enable_interrupt();
}


void rtos_delay_tick(uint32_t tick_count)
{
	//disable interrupt
	disable_interrupt();

	if(current_task)
	{
		user_tasks[current_task].block_count = get_rtos_tick_count() + tick_count;
		user_tasks[current_task].current_state = TASK_BLOCKED_STATE;
		schedule();
	}

	//enable interrupt
	enable_interrupt();
}

void rtos_delay_ms(uint32_t ms)
{
    uint32_t tick_count = tick_in_hz*ms/1000;
    rtos_delay_tick(tick_count);
}

void rtos_delay_until_ms(uint32_t *previous_wake_time,uint32_t ms)
{
    //disable interrupt
	disable_interrupt();

	if(current_task)
	{
		user_tasks[current_task].block_count = (*previous_wake_time) + tick_in_hz*ms/1000;
		user_tasks[current_task].current_state = TASK_BLOCKED_STATE;
		*previous_wake_time = user_tasks[current_task].block_count;
		schedule();
	}

	//enable interrupt
	enable_interrupt();
}

void rtos_delay_until_absolute(uint32_t absolute_time)
{
    //disable interrupt
	disable_interrupt();

	if(current_task)
	{
		user_tasks[current_task].block_count = absolute_time;
		user_tasks[current_task].current_state = TASK_BLOCKED_STATE;
		schedule();
	}

	//enable interrupt
	enable_interrupt();
}

uint32_t get_rtos_tick_count()
{
    return get_tick_count();
}

void unblock_tasks(void)
{
	if(timer_modified)
	{
		if(user_tasks[timer_manager_index].current_state != TASK_READY_STATE)
		{
			user_tasks[timer_manager_index].current_state = TASK_READY_STATE;
		}
	}
	for(int i =1; i < next_task_index; i++)
	{
		if(user_tasks[i].current_state != TASK_READY_STATE)
		{
			if(user_tasks[i].block_count == get_rtos_tick_count())
			{
				user_tasks[i].current_state = TASK_READY_STATE;
			}
			else if(user_tasks[i].notification_status == NOTIFICATION_PRESENT)
			{
				user_tasks[i].current_state = TASK_READY_STATE;
			}
            else if(user_tasks[i].currently_waiting_queue != (uint32_t)NULL)
            {
                if(user_tasks[i].queue_waiting_state == WAITING_ON_FULL_QUEUE)
                {
                    if(!is_queue_full((queuehandle_t)user_tasks[i].currently_waiting_queue))
                    {
                        user_tasks[i].current_state = TASK_READY_STATE;
                    }
                }
                else if(user_tasks[i].queue_waiting_state == WAITING_ON_EMPTY_QUEUE)
                {
                    if(!is_queue_empty((queuehandle_t)user_tasks[i].currently_waiting_queue))
                    {
                        user_tasks[i].current_state = TASK_READY_STATE;
                    }
                }
            }

		}
	}
}

int32_t get_psp_value(void)
{
	return user_tasks[current_task].psp_value;
}

/* this function changes SP to PSP */
__attribute__((naked)) void switch_sp_to_psp(void)
{
	//get the value of psp of current task;
	__asm volatile("PUSH {LR}");//Preserve LR which connects back to main()
	__asm volatile("BL get_psp_value");//load current task (task1) psp value to R0
	__asm volatile("MSR PSP,R0");//Initialise PSR
	__asm volatile("POP {LR}");//Pops back LR

	// change SP to PSP using CONTROL register.
	__asm volatile("MOV R0,#0X02");
	__asm volatile("MSR CONTROL,R0");
	__asm volatile("BX LR");

}

void save_psp_value(uint32_t current_psp_value)
{
	 user_tasks[current_task].psp_value = current_psp_value;
}

void update_next_task(void)
{
	int state =  TASK_BLOCKED_STATE;
	for(int i = 0; i < next_task_index; i++)
	{
		current_task++;
		current_task %= next_task_index;
		state = user_tasks[current_task].current_state;
		if( (state == TASK_READY_STATE) && (current_task != 0))
			break;
	}
	if(state != TASK_READY_STATE)
	{
		current_task = 0;
	}
}

void schedule(void)
{
	pend_pendsv();
}

void update_global_tick_count(void)
{
	g_tick_count++;
}

uint32_t get_tick_count(void)
{
	return g_tick_count;
}

void SysTick_Handler(void)
{
	update_global_tick_count();
	unblock_tasks();
	pend_pendsv();
}

__attribute__ ((naked)) void PendSV_Handler(void)
{
	/* Save the context of current task */

	//1. Get current running task's PSP value
	__asm volatile("MRS R0, PSP");
	//2 Using that PSP value store SF2 (R4 to R11)
	__asm volatile("STMDB R0!,{R4-R11}");

	//Preserve LR
	__asm volatile("PUSH {LR}");

	//3. Save the current value of PSP
	__asm volatile("BL save_psp_value");

	/*Retrieve the context of next task */

	//1. Decide next task to run
	__asm volatile("BL update_next_task");
	//2. get its past PSP value
	__asm volatile("BL get_psp_value");
	//3. Using that PSP value retrieve SF2(R4 to R11)
	__asm volatile("LDMIA R0!,{R4-R11}");
	//4. Update PSP and exit
	__asm volatile("MSR PSP, R0");

	//Loads LR
	__asm volatile("POP {LR}");

	//Switches to thread/user mode
	__asm volatile("BX LR");
}

TCB_t * get_current_task_tcb()
{
    return &user_tasks[current_task];
}