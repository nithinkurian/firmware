#ifndef STM32H743XX_GPIO_DRIVER_H
#define STM32H743XX_GPIO_DRIVER_H

#include <stdint.h>
#include "stm32h743xx.h"


/*
 * Configuration structure for GPIO
 */
typedef struct
{
    uint8_t gpio_pin_number;        //Possible values from @GPIO_PIN_NUMBERS
    uint8_t gpio_pin_mode;          //Possible values from @GPIO_PIN_MODES
    uint8_t gpio_pin_speed;         //Possible values from @GPIO_PIN_SPEEDS
    uint8_t gpio_pin_pupd_control;  //Possible values from @GPIO_PIN_PULL_UP_DOWN_SETTINGS
    uint8_t gpio_pin_op_type;       //Possible values from @GPIO_PIN_OUTPUT_TYPES
    uint8_t gpio_pin_alt_fun_mode;  //Possible values from @GPIO_PIN_ALTERNATE_FUNCTIONS
} GPIO_PinConfig_t;

/*
 * GPIO pin handle
 */
typedef struct
{
    GPIO_RegDef_t *pGPIOx;
    GPIO_PinConfig_t gpio_pin_config;
} GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin possible pin modes
 */
#define GPIO_NUMBER_0           0
#define GPIO_NUMBER_1           1
#define GPIO_NUMBER_2           2
#define GPIO_NUMBER_3           3
#define GPIO_NUMBER_4           4
#define GPIO_NUMBER_5           5
#define GPIO_NUMBER_6           6
#define GPIO_NUMBER_7           7
#define GPIO_NUMBER_8           8
#define GPIO_NUMBER_9           9
#define GPIO_NUMBER_10          10
#define GPIO_NUMBER_11          11
#define GPIO_NUMBER_12          12
#define GPIO_NUMBER_13          13
#define GPIO_NUMBER_14          14
#define GPIO_NUMBER_15          15

/*
 * @GPIO_PIN_MODES
 * GPIO pin possible pin modes
 */
#define GPIO_MODE_IN 	        0
#define GPIO_MODE_OUT	        1
#define GPIO_MODE_ALTFN	   	    2
#define GPIO_MODE_ANALOG        3 //RESET STATE
#define GPIO_MODE_IT_FT         4
#define GPIO_MODE_IT_RT         5
#define GPIO_MODE_IT_RFT        6

/*
 * @GPIO_PIN_SPEEDS
 * GPIO pin possible output speeds
 */
#define GPIO_OP_SPEED_LOW       0
#define GPIO_OP_SPEED_MEDIUM    1
#define GPIO_OP_SPEED_FAST      2
#define GPIO_OP_SPEED_HIGH      3

/*
 * @GPIO_PIN_PULL_UP_DOWN_SETTINGS
 * GPIO pin possible push up pull down settings
 */
#define GPIO_PIN_NO_PUPD        0
#define GPIO_PIN_PU             1
#define GPIO_PIN_PD             2

/*
 * @GPIO_PIN_OUTPUT_TYPES
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP         0 //RESET STATE
#define GPIO_OP_TYPE_OD         1

/*
 * @GPIO_PIN_ALTERNATE_FUNCTIONS
 * GPIO pin possible pin modes
 */
#define GPIO_ALT_FN_0           0
#define GPIO_ALT_FN_1           1
#define GPIO_ALT_FN_2           2
#define GPIO_ALT_FN_3           3
#define GPIO_ALT_FN_4           4
#define GPIO_ALT_FN_5           5
#define GPIO_ALT_FN_6           6
#define GPIO_ALT_FN_7           7
#define GPIO_ALT_FN_8           8
#define GPIO_ALT_FN_9           9
#define GPIO_ALT_FN_10          10
#define GPIO_ALT_FN_11          11
#define GPIO_ALT_FN_12          12
#define GPIO_ALT_FN_13          13
#define GPIO_ALT_FN_14          14
#define GPIO_ALT_FN_15          15

/*****************************GPIO APIs******************************/

/*
 * peripheral clock setup
 */
void gpio_peri_clk_control(GPIO_RegDef_t *p_gpiox, uint8_t en_or_di);

/*
 * Init and deinit
 */
void gpio_init(GPIO_Handle_t *handle);
void gpio_deinit(GPIO_RegDef_t *p_gpiox);

/*
 * read write
 */
uint8_t gpio_pin_read(GPIO_RegDef_t *p_gpiox,uint8_t pin_number);
uint16_t gpio_port_read(GPIO_RegDef_t *p_gpiox);
void gpio_pin_write(GPIO_RegDef_t *p_gpiox,uint8_t pin_number,uint8_t pin_value);
void gpio_port_write(GPIO_RegDef_t *p_gpiox,uint16_t port_value);
void gpio_pin_toggle(GPIO_RegDef_t *p_gpiox,uint8_t pin_number);

/*
 * interrupt
 */
void gpio_irq_interrupt_config(uint8_t irq_number,uint8_t en_or_di);
void gpio_irq_priorityconfig(uint8_t irq_number,uint32_t irq_priority);
void gpio_irq_handling(uint8_t pin_number);


#endif // STM32H743XX_GPIO_DRIVER_H
