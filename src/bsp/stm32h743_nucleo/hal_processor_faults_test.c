
#include "hal_cpu.h"
#include <stdio.h>
#include "hal_processor_faults_test.h"


void generate_undefined_instruction_usagefault(void)
{
	//3. lets force the processor to execute some undefined instruction
	uint32_t *pSRAM = (uint32_t*)0x20010000;

	/*This is an undefined instruction value */
	*pSRAM = 0xFFFFFFFF;

   /* This is a function pointer variable */
	void (*some_address) (void);

   /* initialize  the function pointer variable to some address */
	// Undefined instruction UsageFault
	some_address = (void*)((uint32_t)pSRAM+1);


	/* change PC to jump to location 0x20010000 */
	some_address();
}

void generate_invalid_state_usagefault(void)
{
	//3. lets force the processor to execute some undefined instruction
	uint32_t *pSRAM = (uint32_t*)0x20010000;

	/*This is an undefined instruction value */
	*pSRAM = 0xFFFFFFFF;

   /* This is a function pointer variable */
	void (*some_address) (void);

   /* initialize  the function pointer variable to some address */
	/// Invalid state UsageFault
	// Since 0th bit of pSRAM is not set
	// So it says Arm state which is invalid
	some_address = (void*)((uint32_t)pSRAM);


	/* change PC to jump to location 0x20010000 */
	some_address();
}



int generate_divide_by_zero_usagefault(void)
{
	int x = 0;
	return 10/x;
}