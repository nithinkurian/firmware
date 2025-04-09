
#include "hal_gpio.h"

void set_gpio_port_b_reg(uint32_t value)
{
	//empty
}

void gpio_set_pin(uint16_t value)
{
	set_gpio_port_b_reg(1 << value);
}

void gpio_clear_pin(uint16_t value)
{
	set_gpio_port_b_reg((1 << value) << 16);
}

void GPIO_Init(void)
{
	//empty
}