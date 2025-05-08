#ifndef HAL_GPIO_H
#define HAL_GPIO_H


#include <stdint.h>

void hal_gpio_set_pin(uint16_t value);
void hal_gpio_clear_pin(uint16_t value);
void hal_gpio_init(void);

 #endif // HAL_GPIO_H