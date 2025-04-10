
#include "hal_gpio.h"
#include <stdio.h>


#define WHITE           "\x1b[0;30m"
#define RED             "\x1b[0;31m"
#define GREEN           "\x1b[0;32m"
#define YELLOW          "\x1b[0;33m"
#define BLUE            "\x1b[0;34m"
#define PURPLE          "\x1b[0;35m"
#define TEAL            "\x1b[0;36m"
#define DARK_GRAY       "\x1b[0;37m"
#define LIGHT_GRAY      "\x1b[0;38m"
#define BOLD_WHITE      "\x1b[1;30m"
#define BOLD_RED        "\x1b[1;31m"
#define BOLD_GREEN      "\x1b[1;32m"
#define BOLD_YELLOW     "\x1b[1;33m"
#define BOLD_BLUE       "\x1b[1;34m"
#define BOLD_PURPLE     "\x1b[1;35m"
#define BOLD_TEAL       "\x1b[1;36m"
#define BOLD_DARK_GRAY  "\x1b[1;37m"
#define BOLD_LIGHT_GRAY "\x1b[1;38m"

void gpio_set_pin(uint16_t value)
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

void gpio_clear_pin(uint16_t value)
{
	switch(value)
	{		
		case 0:
			printf(YELLOW"YELLOW OFF\n\r");
			break;
		case 7:
			printf(BLUE"BLUE OFF\n\r");
			break;
		case 14:
			printf(RED"RED OFF\n\r");
			break;
	}
}

void gpio_init(void)
{
	//empty
}
