#include <stdint.h>
#include "hal_cpu.h"
#include "led.h"
#include "delay.h"

#define TICK_HZ				1000U

int main(void)
{

	init_systick_timer(TICK_HZ);
	led_init();

	while (1)
	{
		turn_on_led(YELLOW);
		delay_tick(1000);

		turn_off_led(YELLOW);
		delay_tick(1000);

		turn_on_led(BLUE);
		delay_tick(1000);

		turn_off_led(BLUE);
		delay_tick(1000);

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
