
#include "hal_gpio.h"
#include "stm32h743xx.h"
#include "stm32h743xx_gpio_driver.h"
#include <stddef.h>

static GPIO_RegDef_t * get_gpio_port_from_number(uint8_t port_number)
{
	switch (port_number) 
	{
	  case PORT_A:
	    return GPIOA;
	    break;
	  case PORT_B:
	    return GPIOB;
	    break;
	  case PORT_C:
	    return GPIOC;
	    break;
	  case PORT_D:
	    return GPIOD;
	    break;
	  case PORT_E:
	    return GPIOE;
	    break;
	  case PORT_F:
	    return GPIOF;
	    break;
	  case PORT_G:
	    return GPIOG;
	    break;
	  case PORT_H:
	    return GPIOH;
	    break;
	  case PORT_I:
	    return GPIOI;
	    break;
	  case PORT_J:
	    return GPIOJ;
	    break;
	  case PORT_K:
	    return GPIOK;
	    break;
	  default:
	    return NULL;
	}
}

void hal_gpio_set_pin(uint8_t port_number,uint16_t pin_number)
{
	gpio_pin_write(get_gpio_port_from_number(port_number),pin_number,GPIO_PIN_SET);
}

void hal_gpio_clear_pin(uint8_t port_number,uint16_t pin_number)
{
	gpio_pin_write(get_gpio_port_from_number(port_number),pin_number,GPIO_PIN_RESET);
}

bool hal_gpio_pin_read(uint8_t port_number,uint16_t pin_number)
{
	return gpio_pin_read(get_gpio_port_from_number(port_number),pin_number);
}


void hal_gpio_init(void)
{
	GPIO_Handle_t gpio_handle;
	gpio_handle.pGPIOx = GPIOB;
	gpio_handle.gpio_pin_config.gpio_pin_number = 0;
	gpio_handle.gpio_pin_config.gpio_pin_mode = GPIO_MODE_OUT;
	gpio_handle.gpio_pin_config.gpio_pin_speed = GPIO_OP_SPEED_FAST;
	gpio_handle.gpio_pin_config.gpio_pin_op_type = GPIO_OP_TYPE_PP;
	gpio_handle.gpio_pin_config.gpio_pin_pupd_control = GPIO_PIN_NO_PUPD;
	gpio_init(&gpio_handle);

	gpio_handle.gpio_pin_config.gpio_pin_number = 7;
	gpio_init(&gpio_handle);

	gpio_handle.gpio_pin_config.gpio_pin_number = 14;
	gpio_init(&gpio_handle);

	/*Configure GPIO pin Output Level */
	hal_gpio_clear_pin(PORT_B,0);
	hal_gpio_clear_pin(PORT_B,7);
	hal_gpio_clear_pin(PORT_B,14);

	//Configuring button as input
	gpio_handle.pGPIOx = GPIOC;
	gpio_handle.gpio_pin_config.gpio_pin_number = 13;
	gpio_handle.gpio_pin_config.gpio_pin_mode = GPIO_MODE_IT_FT;
	gpio_handle.gpio_pin_config.gpio_pin_pupd_control = GPIO_PIN_NO_PUPD;
	gpio_init(&gpio_handle);
	gpio_irq_interrupt_config(IRQ_NO_EXTI15_10,ENABLE);
	gpio_irq_priorityconfig(IRQ_NO_EXTI15_10,NVIC_IRQ_PRIORITY15);

}