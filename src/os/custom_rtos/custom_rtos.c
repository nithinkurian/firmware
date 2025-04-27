
#include "rtos.h"
#include "hal_cpu.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "print_colour.h"



void idle_task(void* parameters); //Idle task

#define MAX_TASKS			8

/* Stack memory calculations */
#define SIZE_TASK_STACK		1024U
#define SIZE_SCHED_STACK	1024U

#define SRAM_START			0x20000000U
#define SIZE_SRAM			( (128) * (1024))
#define SRAM_END			( (SRAM_START) + (SIZE_SRAM))

#define SCHED_STACK_START	SRAM_END
#define IDLE_STACK_START	( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define FIRST_STACK_START	( (SRAM_END) - (2 * SIZE_TASK_STACK) )

#define TASK_READY_STATE 	0x00
#define TASK_BLOCKED_STATE 	0xFF

#define TICK_HZ				1000U

#define NO_NOTIFICATION     		0
#define WAITING_FOR_NOTIFICATION	1
#define NOTIFICATION_PRESENT		2

#define NOT_WAITING_ON_QUEUE        0
#define WAITING_ON_EMPTY_QUEUE      1
#define WAITING_ON_FULL_QUEUE       2


typedef struct
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t current_state;
	uint32_t notification_value;
    uint8_t notification_status;
    uint8_t queue_waiting_state;
    uint32_t currently_waiting_queue;
	void (*task_handler)(void* parameters);
}TCB_t;

// Defining the Queue structure
typedef struct {
    void *queue_buffer;
    uint16_t queue_length;
    uint16_t item_size;
    int front;
    int back;
} QCB_t;


__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_tasks_stack(void);
void switch_sp_to_psp(void);
__attribute__((naked)) void switch_sp_to_psp(void);
void pend_pendsv();
void schedule(void);
uint32_t task_stack_init(uint32_t psp_value, void (*task_handler)(void* parameters));
void update_global_tick_count(void);
uint32_t get_tick_count(void);
void init_idle_task_stack(void);
void unblock_tasks(void);
TCB_t * get_current_task_tcb();
void print_queue(queuehandle_t handle);
bool is_queue_empty(queuehandle_t handle);
bool is_queue_full(queuehandle_t handle);


TCB_t user_tasks[MAX_TASKS];
uint32_t g_tick_count = 0;
uint32_t current_task = 1;
uint32_t next_task_start = FIRST_STACK_START;
uint8_t next_task_index = 1;
uint32_t tick_in_hz = 0;

#define MAX_QUEUES           2
QCB_t user_queue[MAX_QUEUES];
uint8_t next_queue = 0;


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
	user_tasks[0].psp_value = IDLE_STACK_START;
	user_tasks[0].task_handler = idle_task;
	user_tasks[0].current_state = TASK_READY_STATE;
	user_tasks[0].psp_value=task_stack_init(user_tasks[0].psp_value,user_tasks[0].task_handler);

	//enable interrupt
	enable_interrupt();
}


void rtos_delay_tick(uint32_t tick_count)
{
	//disable interrupt
	disable_interrupt();

	if(current_task)
	{
		user_tasks[current_task].block_count = get_tick_count() + tick_count;
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

uint32_t get_rtos_tick_count()
{
    return get_tick_count();
}

void unblock_tasks(void)
{
	for(int i =1; i < next_task_index; i++)
	{
		if(user_tasks[i].current_state != TASK_READY_STATE)
		{
			if(user_tasks[i].block_count == get_tick_count())
			{
				user_tasks[i].current_state = TASK_READY_STATE;
			}
			else if(user_tasks[i].notification_status == NOTIFICATION_PRESENT)
			{
				user_tasks[i].current_state = TASK_READY_STATE;
			}
            else if(user_tasks[i].currently_waiting_queue != NULL)
            {
                if(user_tasks[i].queue_waiting_state == WAITING_ON_FULL_QUEUE)
                {
                    if(!is_queue_full(user_tasks[i].currently_waiting_queue))
                    {
                        user_tasks[i].current_state = TASK_READY_STATE;
                    }
                }
                else if(user_tasks[i].queue_waiting_state == WAITING_ON_EMPTY_QUEUE)
                {
                    if(!is_queue_empty(user_tasks[i].currently_waiting_queue))
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

bool is_queue_empty(queuehandle_t handle)
{
    QCB_t * queue_handle = (QCB_t *)handle;
    return (queue_handle->back == -1);
}

bool is_queue_full(queuehandle_t handle)
{
    QCB_t * queue_handle = (QCB_t *)handle;
    return (queue_handle->back == queue_handle->front);
}

queuehandle_t create_queue(const uint32_t queue_length,const uint32_t item_size)
{
    if(next_queue >= MAX_QUEUES)
    {
        printf("QCB are not available, please increase MAX_QUEUES\n");
        while(1);
    }

    QCB_t * q_handle = &user_queue[next_queue];

    if(q_handle == NULL)
    {
        return NULL;
    }

    q_handle->queue_length = queue_length;
    q_handle->item_size =item_size;
    q_handle->front = 0;
    q_handle->back = -1;
    q_handle->queue_buffer=malloc(queue_length*item_size);

    if(q_handle->queue_buffer == NULL)
    {
        printf("Queue buffer allocation failed\n");
        while(1);
    }

    next_queue++;
    return q_handle;
}



void print_queue(queuehandle_t handle)
{
    QCB_t * q_handle = (QCB_t *)handle;
    printf(RED_COLOUR"q_handle->queue_length %d \n"
    "q_handle->item_size %d \n"
    "q_handle->front %d \n"
    "q_handle->back %d \n"
    "q_handle->queue_buffer %d \n"
        ,q_handle->queue_length
        ,q_handle->item_size
        ,q_handle->front
        ,q_handle->back
        ,(uint32_t) q_handle->queue_buffer
        );
}

bool send_to_queue(queuehandle_t handle,void * data, uint32_t ms)
{
    QCB_t * queue_handle = (QCB_t *)handle;
    if(is_queue_full(queue_handle))
    {
        TCB_t * current_task_tcb = get_current_task_tcb();
        if(current_task_tcb == NULL)
        {
            printf("current_task_tcb is null\n");
            return false;
        }

        current_task_tcb->queue_waiting_state = WAITING_ON_FULL_QUEUE;
        current_task_tcb->currently_waiting_queue = queue_handle;

        rtos_delay_ms(ms);

        current_task_tcb->queue_waiting_state = NOT_WAITING_ON_QUEUE;
        current_task_tcb->currently_waiting_queue = NULL;
    }

    if(is_queue_full(queue_handle))
    {
        return false;
    }

    if(data == NULL)
    {
        printf("Queue data pointer is null\n");
        while(1);
    }

    memcpy(&(queue_handle->queue_buffer[queue_handle->front++]),data, queue_handle->item_size);
    if(queue_handle->front == queue_handle->queue_length)
    {
        queue_handle->front = 0;
    }

    if(queue_handle->back == -1)
    {
        queue_handle->back = 0;
    }

    return true;
}

bool receive_from_queue(queuehandle_t handle,void * data, uint32_t ms)
{
    QCB_t * queue_handle = (QCB_t *)handle;
    if(is_queue_empty(queue_handle))
    {

        TCB_t * current_task_tcb = get_current_task_tcb();
        if(current_task_tcb == NULL)
        {
            printf("current_task_tcb is null\n");
            return false;
        }

        current_task_tcb->queue_waiting_state = WAITING_ON_EMPTY_QUEUE;
        current_task_tcb->currently_waiting_queue = queue_handle;

        rtos_delay_ms(ms);

        current_task_tcb->queue_waiting_state = NOT_WAITING_ON_QUEUE;
        current_task_tcb->currently_waiting_queue = NULL;
    }

    if(is_queue_empty(queue_handle))
    {
        return false;
    }

    if(data == NULL)
    {
        printf(BOLD_TEAL"Queue data pointer is null\n");
        while(1);
    }

    //print_queue(queue_handle);
    memcpy(data,&(queue_handle->queue_buffer[queue_handle->back++]), queue_handle->item_size);

    if(queue_handle->back == queue_handle->queue_length)
    {
        queue_handle->back = 0;
    }

    if(queue_handle->back == queue_handle->front)
    {
        queue_handle->front = 0;
        queue_handle->back = -1;
    }

    //print_queue(queue_handle);
    return true;
}
