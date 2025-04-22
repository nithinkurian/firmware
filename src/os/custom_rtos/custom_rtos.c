
#include "rtos.h"
#include "hal_cpu.h"
#include <stddef.h>

extern void task1_handler(void* parameters); //This is task1
extern void task2_handler(void* parameters); //This is task2
extern void task3_handler(void* parameters); //This is task3
extern void task4_handler(void* parameters); //This is task4
extern void idle_task(void* parameters); //Idle task

#define MAX_TASKS			5

/* Stack memory calculations */
#define SIZE_TASK_STACK		1024U
#define SIZE_SCHED_STACK	1024U

#define SRAM_START			0x20000000U
#define SIZE_SRAM			( (128) * (1024))
#define SRAM_END			( (SRAM_START) + (SIZE_SRAM))

#define T1_STACK_START		SRAM_END
#define T2_STACK_START		( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START		( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START		( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START	( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START	( (SRAM_END) - (5 * SIZE_TASK_STACK) )

#define TASK_READY_STATE 	0x00
#define TASK_BLOCKED_STATE 	0xFF

#define TICK_HZ				1000U


typedef struct
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t current_state;
	void (*task_handler)(void* parameters);
}TCB_t;


__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_tasks_stack(void);
void switch_sp_to_psp(void);
__attribute__((naked)) void switch_sp_to_psp(void);
void pend_pendsv();
void schedule(void);
uint32_t task_stack_init(uint32_t psp_value, void (*task_handler)(void* parameters));
void update_global_tick_count(void);
uint64_t get_tick_count(void);


TCB_t user_tasks[MAX_TASKS];
uint64_t g_tick_count = 0;
uint32_t current_task = 1;

void rtos_init()
{
	//Initialize systick
	init_systick_timer(TICK_HZ);
	init_tasks_stack();	
}

void run_scheduler()
{
	init_scheduler_stack(SCHED_STACK_START);
	switch_sp_to_psp();
	task1_handler(NULL);
}

void init_tasks_stack(void)
{
	user_tasks[0].current_state = TASK_READY_STATE;
	user_tasks[1].current_state = TASK_READY_STATE;
	user_tasks[2].current_state = TASK_READY_STATE;
	user_tasks[3].current_state = TASK_READY_STATE;
	user_tasks[4].current_state = TASK_READY_STATE;

	user_tasks[0].psp_value = IDLE_STACK_START;
	user_tasks[1].psp_value = T1_STACK_START;
	user_tasks[2].psp_value = T2_STACK_START;
	user_tasks[3].psp_value = T3_STACK_START;
	user_tasks[4].psp_value = T4_STACK_START;

	user_tasks[0].task_handler = idle_task;
	user_tasks[1].task_handler = task1_handler;
	user_tasks[2].task_handler = task2_handler;
	user_tasks[3].task_handler = task3_handler;
	user_tasks[4].task_handler = task4_handler;

	
	for(int i =0; i < MAX_TASKS; i++)
	{

		user_tasks[i].psp_value=task_stack_init(user_tasks[i].psp_value,user_tasks[i].task_handler);
	}
}


void rtos_delay(uint32_t tick_count)
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

void unblock_tasks(void)
{
	for(int i =1; i < MAX_TASKS; i++)
	{
		if(user_tasks[i].current_state != TASK_READY_STATE)
		{
			if(user_tasks[i].block_count == get_tick_count())
			{
				user_tasks[i].current_state = TASK_READY_STATE;
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
	for(int i = 0; i < MAX_TASKS; i++)
	{
		current_task++;
		current_task %= MAX_TASKS;
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

uint64_t get_tick_count(void)
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