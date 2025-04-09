
#include "hal_cpu.h"

void __disable_irq(void)
{
	__asm volatile ("cpsid i" : : : "memory");
}