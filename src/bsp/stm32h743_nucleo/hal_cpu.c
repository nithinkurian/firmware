
#include "hal_cpu.h"
#include "rtos.h"


#define HSI_CLK 			64000000U
#define SYSTICK_TIM_CLK 	HSI_CLK
#define DUMMY_XPSP			0x01000000U

#define INTERRUPT_DISABLE()  do{__asm volatile ("MOV R0,#0x1"); asm volatile("MSR PRIMASK,R0"); } while(0)

#define INTERRUPT_ENABLE()  do{__asm volatile ("MOV R0,#0x0"); asm volatile("MSR PRIMASK,R0"); } while(0)


uint64_t g_tick_count = 0;

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

__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack)
{
	__asm  volatile("MSR MSP,%0": : "r" (sched_top_of_stack) : );
	__asm  volatile("BX LR");
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

void pend_pendsv()
{
	uint32_t *pICSR = (uint32_t *)0xE000ED04;
	//pend the pendsv exception
	*pICSR |= (1 << 28);
}



void SysTick_Handler(void)
{
	update_global_tick_count();
	unblock_tasks();
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

uint32_t task_stack_init(uint32_t psp_value, void (*task_handler)(void))
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