#ifndef LED_H
#define LED_H

#include <stdint.h> 
#include <stdbool.h>

typedef enum
{
	YELLOW,
	BLUE,
	RED
} led_t;

void led_init();
void turn_on_led(led_t led);
void turn_off_led(led_t led);
void toggle_led(led_t led,bool * current_state);

#endif // LED_H