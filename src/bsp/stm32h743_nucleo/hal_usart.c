
#include "hal_gpio.h"
#include "stm32h743xx.h"
#include "stm32h743xx_gpio_driver.h"
#include "stm32h743xx_usart_driver.h"
#include <stddef.h>
#include <string.h>




USART_Handle_t usart3_handle;

void hal_usart_init(void)
{
    GPIO_Handle_t gpio_handle;
    gpio_handle.pGPIOx = GPIOD;
    
    gpio_handle.gpio_pin_config.gpio_pin_mode = GPIO_MODE_ALTFN;
    gpio_handle.gpio_pin_config.gpio_pin_pupd_control = GPIO_PIN_NO_PUPD;
    gpio_handle.gpio_pin_config.gpio_pin_speed = GPIO_OP_SPEED_HIGH;
    gpio_handle.gpio_pin_config.gpio_pin_op_type = GPIO_OP_TYPE_PP;
    gpio_handle.gpio_pin_config.gpio_pin_alt_fun_mode = GPIO_ALT_FN_7;

    gpio_handle.gpio_pin_config.gpio_pin_number = 8;
    gpio_init(&gpio_handle);
    gpio_handle.gpio_pin_config.gpio_pin_number = 9;
    gpio_init(&gpio_handle);

    usart3_handle.pUSARTx = USART3;

    usart3_handle.usart_config.usart_mode = USART_MODE_TXRX;
    usart3_handle.usart_config.usart_baud_rate = USART_STD_BAUD_115200;
    usart3_handle.usart_config.usart_parity_control = USART_PARITY_DISABLE;
    usart3_handle.usart_config.usart_word_length = USART_8_BIT_DATA;
    usart3_handle.usart_config.usart_stop_bit_count = USART_1_STOP_BIT;
    usart3_handle.usart_config.usart_hw_flow_control = USART_HW_FLOW_CTRL_NONE;
    usart_init(&usart3_handle);

}

void hal_usart3_transmit(uint8_t *buffer,uint16_t length)
{
    usart_send_data(&usart3_handle,buffer,length);
}