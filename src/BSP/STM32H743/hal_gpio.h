#ifndef HAL_GPIO_H
#define HAL_GPIO_H


#include <stdint.h>

void set_gpio_port_b_reg(uint32_t value);
void gpio_set_pin(uint16_t value);
void gpio_clear_pin(uint16_t value);
void GPIO_Init(void);

 #endif // HAL_GPIO_H