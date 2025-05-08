
#include "hal_gpio.h"
#include "stm32h743xx.h"
#include "stm32h743xx_gpio_driver.h"

static void hal_set_gpio_port_b_reg(uint32_t value);

static void hal_set_gpio_port_b_reg(uint32_t value)
{
	GPIOB->BSRR= value;
}

void hal_gpio_set_pin(uint16_t value)
{
	hal_set_gpio_port_b_reg(1 << value);
}

void hal_gpio_clear_pin(uint16_t value)
{
	hal_set_gpio_port_b_reg((1 << value) << 16);
}

void hal_gpio_init(void)
{
	//GPIO Port B clock enable
	GPIOB_PERI_CLK_EN();

	/*Configure GPIO pin Output Level */
	hal_gpio_clear_pin(0);
	hal_gpio_clear_pin(7);
	hal_gpio_clear_pin(14);

	/* Configure IO Direction mode (Input, Output, Alternate or Analog) */
	GPIOB->MODER = (1 << (0 * 2U)) | (1 << (7 * 2U)) | (1 << (14 * 2U));
}