
#include "hal_cpu.h"
#include "rtos.h"
#include "stm32h743xx.h"



#define DUMMY_XPSP			0x01000000U

#define INTERRUPT_DISABLE()  do{__asm volatile ("MOV R0,#0x1"); asm volatile("MSR PRIMASK,R0"); } while(0)

#define INTERRUPT_ENABLE()  do{__asm volatile ("MOV R0,#0x0"); asm volatile("MSR PRIMASK,R0"); } while(0)

uint32_t SystemCoreClock = HSI_CLK;


void disable_interrupt()
{
	INTERRUPT_DISABLE();
}

void enable_interrupt()
{
	INTERRUPT_ENABLE();
}

void __disable_irq(void)
{
	__asm volatile ("cpsid i" : : : "memory");
}

void init_systick_timer(uint32_t tick_hz)
{
	//Systick timer is 24bit
	uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz) - 1;

	//Clear the value of SRVR
    SYSTICK->RVR &= ~(0x00FFFFFF);

	//load the value in to SVR
	SYSTICK->RVR |= count_value;

	//do some settings
	SYSTICK->CSR |= (1 << 1); // Enables SysTick exception request.
	SYSTICK->CSR |= (1 << 2); // Indicates the clock source to	Processor clock (Internal)

	//start systick
	SYSTICK->CSR |= (1 << 0); // Enables the counter
}

__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack)
{
	__asm  volatile("MSR MSP,%0": : "r" (sched_top_of_stack) : );
	__asm  volatile("BX LR");
}

void pend_pendsv()
{
	//pend the pendsv exception
	SCB->ICSR |= (1 << 28);
}

uint32_t task_stack_init(uint32_t psp_value, void (*task_handler)(void* parameters))
{
	uint32_t *pPSP;
	pPSP = (uint32_t *)psp_value;

	pPSP--;//XPSR
	*pPSP = DUMMY_XPSP;//0x00100000

	pPSP--;//PC
	*pPSP = (uint32_t) task_handler;

	pPSP--;//LR
	*pPSP = 0xFFFFFFFD;

	for(int j=0; j < 13; j++)
	{
		pPSP--;
		*pPSP = 0;
	}
	return (uint32_t)pPSP;
}