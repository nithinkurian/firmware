
#include "hal_gpio.h"
#include <stdio.h>

void gpio_set_pin(uint16_t value)
{
	switch(value)
	{		
		case 0:
			printf("YELLOW ON\n\r");
			break;
		case 7:
			printf("BLUE ON\n\r");
			break;
		case 14:
			printf("RED ON\n\r");
			break;
	}
}

void gpio_clear_pin(uint16_t value)
{
	switch(value)
	{		
		case 0:
			printf("YELLOW OFF\n\r");
			break;
		case 7:
			printf("BLUE OFF\n\r");
			break;
		case 14:
			printf("RED OFF\n\r");
			break;
	}
}

void gpio_init(void)
{
	//empty
}