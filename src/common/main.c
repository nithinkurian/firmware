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

taskhandle_t task1_handler;
taskhandle_t task2_handler;
taskhandle_t task3_handler;
taskhandle_t task4_handler;

void task1_function(void* parameters); //This is task1
void task2_function(void* parameters); //This is task2
void task3_function(void* parameters); //This is task3
void task4_function(void* parameters); //This is task4

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

	printf(BOLD_DARK_GRAY"Initialized\n");
	printf("%s Initializing\n",get_rtos_name());

	task1_handler = create_task(task1_function,760, 2);
	task2_handler = create_task(task2_function,760, 2);
	task3_handler = create_task(task3_function,760, 2);
	task4_handler = create_task(task4_function,760, 2);
	
	
	run_scheduler();

}

void task1_function(void* parameters)
{
	uint32_t previous_wake_time = get_rtos_tick_count();
	while(1)
	{
		printf(BOLD_YELLOW"task1 ON\n\r");
		turn_on_led(YELLOW);
		rtos_delay_until_ms(&previous_wake_time,1000);
		printf(YELLOW_COLOUR"task1 OFF\n\r");	
		turn_off_led(YELLOW);
		rtos_delay_until_ms(&previous_wake_time,1000);
	}
}

void task2_function(void* parameters)
{
	uint32_t previous_wake_time = get_rtos_tick_count();
	while(1)
	{
		printf(BOLD_BLUE"task2 ON\n\r");
		turn_on_led(BLUE);
		rtos_delay_until_ms(&previous_wake_time,2000);
		printf(BLUE_COLOUR"task2 OFF\n\r");	
		turn_off_led(BLUE);
		rtos_delay_until_ms(&previous_wake_time,2000);
	}
}

void task3_function(void* parameters)
{
	uint32_t previous_wake_time = get_rtos_tick_count();
	while(1)
	{
		printf(BOLD_RED"task3 ON\n\r");
		turn_on_led(RED);
		rtos_delay_until_ms(&previous_wake_time,4000);
		printf(RED_COLOUR"task3 OFF\n\r");	
		turn_off_led(RED);
		rtos_delay_until_ms(&previous_wake_time,4000);
	}
}

void task4_function(void* parameters)
{
	uint32_t previous_wake_time = get_rtos_tick_count();
	while(1)
	{
		printf(BOLD_GREEN"task4 ON\n\r");
		rtos_delay_until_ms(&previous_wake_time,8000);
		printf(GREEN_COLOUR"task4 OFF\n\r");
		rtos_delay_until_ms(&previous_wake_time,8000);
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
