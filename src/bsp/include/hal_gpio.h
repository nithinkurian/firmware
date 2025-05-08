#ifndef HAL_GPIO_H
#define HAL_GPIO_H


#include <stdint.h>
#include <stdbool.h>

#define PORT_A  0
#define PORT_B  1
#define PORT_C  2
#define PORT_D  3
#define PORT_E  4
#define PORT_F  5
#define PORT_G  6
#define PORT_H  7
#define PORT_I  8
#define PORT_J  9
#define PORT_K  10

void hal_gpio_set_pin(uint8_t port_number,uint16_t pin_number);
void hal_gpio_clear_pin(uint8_t port_number,uint16_t pin_number);
bool hal_gpio_pin_read(uint8_t port_number,uint16_t pin_number);
void hal_gpio_init(void);

 #endif // HAL_GPIO_H