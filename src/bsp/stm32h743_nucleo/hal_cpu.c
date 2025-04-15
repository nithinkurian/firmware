
#include "hal_cpu.h"

#define HSI_CLK 			64000000U
#define SYSTICK_TIM_CLK 	HSI_CLK

static void update_tick_count(void);

uint64_t sys_tick_count = 0;

void __disable_irq(void)
{
	__asm volatile ("cpsid i" : : : "memory");
}

void init_systick_timer(uint32_t tick_hz)
{
	//Systick timer is 24bit
	uint32_t *pSYST_CSR = (uint32_t *)0xE000E010;
	uint32_t *pSYST_RVR = (uint32_t *)0xE000E014;
	uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz) - 1;

	//Clear the value of SRVR
    *pSYST_RVR &= ~(0x00FFFFFFFF);

	//load the value in to SVR
	*pSYST_RVR |= count_value;

	//do some settings
	*pSYST_CSR |= (1 << 1); // Enables SysTick exception request.
	*pSYST_CSR |= (1 << 2); // Indicates the clock source to	Processor clock (Internal)

	//start systick
	*pSYST_CSR |= (1 << 0); // Enables the counter
}

void SysTick_Handler(void)
{
	update_tick_count();
}

void update_tick_count(void)
{
	sys_tick_count++;
}

uint64_t get_tick_count(void)
{
	return sys_tick_count;
}