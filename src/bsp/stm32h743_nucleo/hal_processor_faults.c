
#include "hal_cpu.h"
#include <stdio.h>


void enable_processor_faults(void)
{
	uint32_t *pSHCSR = (uint32_t*)0xE000ED24;

	*pSHCSR |= ( 1 << 16); //mem manage
	*pSHCSR |= ( 1 << 17); //bus fault
	*pSHCSR |= ( 1 << 18); //usage fault
}

//2. implement the fault handlers
void HardFault_Handler(void)
{
	printf("Exception : Hardfault\n");
	while(1);
}


void MemManage_Handler(void)
{
	printf("Exception : MemManage\n");
	//Need to implement these
	while(1);
}

void BusFault_Handler(void)
{
	printf("Exception : BusFault\n");
	//Need to implement these
	while(1);
}

__attribute__ ((naked)) void UsageFault_Handler(void)
{
	//here we extracted the value of MSP which happens to be the
	//base address of the stack frame(thread mode) which got saved during the exception entry
	//from thread mode to handler mode
	__asm ("MRS r0,MSP");
	__asm ("B UsageFault_Handler_c");
}

void UsageFault_Handler_c(uint32_t *pBaseStackFrame)
{
	uint16_t *pUFSR = (uint16_t *)0xE000ED2A; // Half word access
	printf("Exception : UsageFault\n");
	printf("UFSR = %u\n",(*pUFSR) & 0xFFFF);
	if(*pUFSR == 1)
	{
		printf("Undefined instruction UsageFault\n");
	}
	else if(*pUFSR == 2)
	{
		printf("Invalid state UsageFault\n");
	}
	printf("pBaseStackFrame = %p\n",pBaseStackFrame);
	printf("Value of R0 = %lx\n", pBaseStackFrame[0]);
	printf("Value of R1 = %lx\n", pBaseStackFrame[1]);
	printf("Value of R2 = %lx\n", pBaseStackFrame[2]);
	printf("Value of R3 = %lx\n", pBaseStackFrame[3]);
	printf("Value of R12 = %lx\n", pBaseStackFrame[4]);
	printf("Value of LR = %lx\n", pBaseStackFrame[5]);
	printf("Value of PC = %lx\n", pBaseStackFrame[6]);
	printf("Value of XPSR = %lx\n", pBaseStackFrame[7]);
	while(1);
}