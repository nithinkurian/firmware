#include "led.h"
#include "hal_gpio.h"

void led_init()
{
	hal_gpio_init();
}

void turn_on_led(led_t led)
{
	switch(led)
	{
	case YELLOW:
		hal_gpio_set_pin(PORT_B,0);
		break;
	case BLUE:
		hal_gpio_set_pin(PORT_B,7);
		break;
	case RED:
		hal_gpio_set_pin(PORT_B,14);
		break;

	}
}



void turn_off_led(led_t led)
{
	switch(led)
	{
	case YELLOW:
		hal_gpio_clear_pin(PORT_B,0);
		break;
	case BLUE:
		hal_gpio_clear_pin(PORT_B,7);
		break;
	case RED:
		hal_gpio_clear_pin(PORT_B,14);
		break;
	}
}

void toggle_led(led_t led,bool * current_state)
{
	if(*current_state)
	{
		turn_off_led(led);
		*current_state = false;
	}
	else
	{
		turn_on_led(led);
		*current_state = true;
	}
}

		