
#include "hal_gpio.h"
#include <stdio.h>
#include "print_colour.h"


void hal_gpio_set_pin(uint16_t value)
{
	switch(value)
	{		
		case 0:
			printf(BOLD_YELLOW"YELLOW ON\n\r");
			break;
		case 7:
			printf(BOLD_BLUE"BLUE ON\n\r");
			break;
		case 14:
			printf(BOLD_RED"RED ON\n\r");
			break;
	}
}

void hal_gpio_clear_pin(uint16_t value)
{
	switch(value)
	{		
		case 0:
			printf(YELLOW_COLOUR"YELLOW OFF\n\r");
			break;
		case 7:
			printf(BLUE_COLOUR"BLUE OFF\n\r");
			break;
		case 14:
			printf(RED_COLOUR"RED OFF\n\r");
			break;
	}
}

void hal_gpio_init(void)
{
	//empty
}
