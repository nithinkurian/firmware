
#include "hal_cpu.h"
#include <time.h>

#define SYSTICK_TIM_CLK 	1000000
uint32_t tick_in_hz = 0;

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