#include <stdint.h>
#include "hal_cpu.h"
#include "led.h"

void delay();

int main(void)
{

	led_init();

	while (1)
	{
		turn_on_led(YELLOW);
		delay();

		turn_off_led(YELLOW);
		delay();

		turn_on_led(BLUE);
		delay();

		turn_off_led(BLUE);
		delay();

		turn_on_led(RED);
		delay();

		turn_off_led(RED);
		delay();
	}
}

void delay()
{
	uint32_t delay_count = 10000000;
	while (delay_count--);
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
