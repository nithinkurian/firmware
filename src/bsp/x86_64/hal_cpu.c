
#include "hal_cpu.h"
#include <time.h>

#define SYSTICK_TIM_CLK 	1000000
uint32_t tick_in_hz = 0;



void disable_interrupt()
{
}

void enable_interrupt()
{
}

void __disable_irq(void)
{
	//empty
}

void init_systick_timer(uint32_t tick_hz)
{	
	tick_in_hz = tick_hz;
}

void update_tick_count(void)
{
}

uint64_t get_tick_count(void)
{
	return time(0)*tick_in_hz;;
}

void pend_pendsv()
{
}

void init_scheduler_stack(uint32_t sched_top_of_stack)
{
}

/* this function changes SP to PSP */
void switch_sp_to_psp(void)
{
}

uint32_t task_stack_init(uint32_t psp_value, void (*task_handler)(void))
{
	return (uint32_t)psp_value;
}