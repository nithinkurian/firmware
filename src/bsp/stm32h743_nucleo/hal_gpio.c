
#include "hal_gpio.h"

void set_gpio_port_b_reg(uint32_t value)
{
	uint32_t *GPIO_PortB_Set_Reset = (uint32_t*) 0x58020418UL;
	*GPIO_PortB_Set_Reset = value;
}

void gpio_set_pin(uint16_t value)
{
	set_gpio_port_b_reg(1 << value);
}

void gpio_clear_pin(uint16_t value)
{
	set_gpio_port_b_reg((1 << value) << 16);
}

void gpio_init(void)
{
	//GPIO Port B clock enable
	uint32_t *reg = (uint32_t*) 0x580244E0UL;
	*reg |= 2;

	/*Configure GPIO pin Output Level */
	gpio_clear_pin(0);
	gpio_clear_pin(7);
	gpio_clear_pin(14);

	/* Configure IO Direction mode (Input, Output, Alternate or Analog) */
	uint32_t *GPIO_PortB_Mode = (uint32_t*) 0x58020400UL;
	*GPIO_PortB_Mode = (1 << (0 * 2U)) | (1 << (7 * 2U)) | (1 << (14 * 2U));
}