#ifndef LED_H
#define LED_H

#include <stdint.h>

typedef enum
{
	YELLOW,
	BLUE,
	RED
} led_t;

void led_init();
void turn_on_led(led_t led);
void turn_off_led(led_t led);

#endif // LED_H