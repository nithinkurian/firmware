#include <stdint.h>
#include "hal_cpu.h"
#include "led.h"
#include "delay.h"
#include <stdio.h>
#include "print_colour.h"
#include "hal_processor_faults.h"


#define TICK_HZ				1000U

//Semi hosting init function
extern void initialise_monitor_handles(void);

int main(void)
{
	//Semi hosting init function
	initialise_monitor_handles();

	//enabling processor faults
	enable_processor_faults();
	
	//Initialize systick
	init_systick_timer(TICK_HZ);

	//Initialize LED
	led_init();


	printf("Initialized\n");

	while (1)
	{
		printf("loop\n");

		printf(BOLD_YELLOW"YELLOW\n\r");
		turn_on_led(YELLOW);
		delay_tick(1000);

		
		turn_off_led(YELLOW);
		delay_tick(1000);

		printf(BOLD_BLUE"BLUE\n\r");
		turn_on_led(BLUE);
		delay_tick(1000);

		turn_off_led(BLUE);
		delay_tick(1000);

		printf(BOLD_RED"RED\n\r");
		turn_on_led(RED);
		delay_tick(1000);

		turn_off_led(RED);
		delay_tick(1000);
	}
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
