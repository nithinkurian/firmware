#include "led.h"
#include "hal_gpio.h"

void led_init()
{
	gpio_init();
}

void turn_on_led(led_t led)
{
	switch(led)
	{
	case YELLOW:
		gpio_set_pin(0);
		break;
	case BLUE:
		gpio_set_pin(7);
		break;
	case RED:
		gpio_set_pin(14);
		break;

	}
}



void turn_off_led(led_t led)
{
	switch(led)
	{
	case YELLOW:
		gpio_clear_pin(0);
		break;
	case BLUE:
		gpio_clear_pin(7);
		break;
	case RED:
		gpio_clear_pin(14);
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

		