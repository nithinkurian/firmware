#include <stdint.h>
#include "hal_cpu.h"
#include "led.h"
#include <stdio.h>
#include "print_colour.h"
#include "hal_processor_faults.h"
#include "hal_processor_faults_test.h" //just for testing
#include "rtos.h"




//Semi hosting init function
extern void initialise_monitor_handles(void);

void task1_handler(void* parameters); //This is task1
void task2_handler(void* parameters); //This is task2
void task3_handler(void* parameters); //This is task3
void task4_handler(void* parameters); //This is task4
void idle_task(void* parameters); //Idle task

int main(void)
{
	//Semi hosting init function
	initialise_monitor_handles();

	//enabling processor faults
	enable_processor_faults();

	//enable one by one for testing
	//generate_undefined_instruction_usagefault();
	//generate_invalid_state_usagefault();
	//generate_divide_by_zero_usagefault();

	//Initialize LED
	led_init();
	printf("Initialized\n");

	create_task(task1_handler,760, 2);
	create_task(task2_handler,760, 2);
	create_task(task3_handler,760, 2);
	create_task(task4_handler,760, 2);
	
	run_scheduler();

}

void task1_handler(void* parameters)
{
	while(1)
	{
		printf(BOLD_YELLOW"task1 ON\n\r");
		turn_on_led(YELLOW);
		rtos_delay(1000);	
		printf(YELLOW_COLOUR"task1 OFF\n\r");	
		turn_off_led(YELLOW);
		rtos_delay(1000);
	}
}

void task2_handler(void* parameters)
{
	while(1)
	{
		printf(BOLD_BLUE"task2 ON\n\r");
		turn_on_led(BLUE);
		rtos_delay(2000);
		printf(BLUE_COLOUR"task2 OFF\n\r");	
		turn_off_led(BLUE);
		rtos_delay(2000);
	}
}

void task3_handler(void* parameters)
{
	while(1)
	{
		printf(BOLD_RED"task3 ON\n\r");
		turn_on_led(RED);
		rtos_delay(4000);
		printf(RED_COLOUR"task3 OFF\n\r");	
		turn_off_led(RED);
		rtos_delay(4000);
	}
}

void task4_handler(void* parameters)
{
	while(1)
	{
		printf(BOLD_GREEN"task4 ON\n\r");
		rtos_delay(8000);
		printf(GREEN_COLOUR"task4 OFF\n\r");
		rtos_delay(8000);
	}
}

void idle_task(void* parameters)
{
	while(1);
}




/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
