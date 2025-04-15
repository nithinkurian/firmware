
#include "hal_cpu.h"


void delay_tick(uint32_t tick_delay)
{
	uint64_t initial_tick = get_tick_count();
	while(initial_tick+ tick_delay>get_tick_count());
}