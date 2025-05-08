#include "stm32h743xx_gpio_driver.h"

/*****************************GPIO APIs******************************/

/********************************************************************
 * @fn          - gpio_peri_clk_control
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
void gpio_peri_clk_control(GPIO_RegDef_t *p_gpiox, uint8_t en_or_di)
{
    if(en_or_di == ENABLE)
    {
        if(p_gpiox == GPIOA)
        {
            GPIOA_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOB)
        {
            GPIOB_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOC)
        {
            GPIOC_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOD)
        {
            GPIOD_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOE)
        {
            GPIOE_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOF)
        {
            GPIOF_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOG)
        {
            GPIOG_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOH)
        {
            GPIOH_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOI)
        {
            GPIOI_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOJ)
        {
            GPIOJ_PERI_CLK_EN();
        }
        else if(p_gpiox == GPIOK)
        {
            GPIOK_PERI_CLK_EN();
        }
    }
    else
    {
        if(p_gpiox == GPIOA)
        {
            GPIOA_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOB)
        {
            GPIOB_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOC)
        {
            GPIOC_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOD)
        {
            GPIOD_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOE)
        {
            GPIOE_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOF)
        {
            GPIOF_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOG)
        {
            GPIOG_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOH)
        {
            GPIOH_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOI)
        {
            GPIOI_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOJ)
        {
            GPIOJ_PERI_CLK_DI();
        }
        else if(p_gpiox == GPIOK)
        {
            GPIOK_PERI_CLK_DI();
        }
    }
}

/*
 * Init and deinit
 */

/********************************************************************
 * @fn          - 
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
void gpio_init(GPIO_Handle_t *handle)
{
    //configure mode
    if(handle->gpio_pin_config.gpio_pin_mode <= GPIO_MODE_ANALOG)
    {
        //Non interrupt modes
        WRITE_REG(handle->pGPIOx->MODER,2*handle->gpio_pin_config.gpio_pin_number,handle->gpio_pin_config.gpio_pin_mode,0x3);
    }
    else
    {
        //Interrupt modes
    }

    //configure speed
    WRITE_REG(handle->pGPIOx->OSPEEDR,2*handle->gpio_pin_config.gpio_pin_number,handle->gpio_pin_config.gpio_pin_speed,0x3);

    //configure pull up pull down settings
    WRITE_REG(handle->pGPIOx->PUPDR,2*handle->gpio_pin_config.gpio_pin_number,handle->gpio_pin_config.gpio_pin_pupd_control,0x3);

    //output type
    SET_BITS(handle->pGPIOx->PUPDR,handle->gpio_pin_config.gpio_pin_number,handle->gpio_pin_config.gpio_pin_op_type,0x1);

    //alternate function mode
    if(handle->gpio_pin_config.gpio_pin_mode == GPIO_MODE_ALTFN)
    { 
        uint8_t index,offset;
        index = handle->gpio_pin_config.gpio_pin_number/8;
        offset = 4 * (handle->gpio_pin_config.gpio_pin_number%8);
        WRITE_REG(handle->pGPIOx->AFR[index],offset,handle->gpio_pin_config.gpio_pin_alt_fun_mode,0x3);
    }

}

/********************************************************************
 * @fn          - 
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
void gpio_deinit(GPIO_RegDef_t *p_gpiox)
{    
    if(p_gpiox == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(p_gpiox == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(p_gpiox == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(p_gpiox == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(p_gpiox == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if(p_gpiox == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if(p_gpiox == GPIOG)
    {
        GPIOG_REG_RESET();
    }
    else if(p_gpiox == GPIOH)
    {
        GPIOH_REG_RESET();
    }
    else if(p_gpiox == GPIOI)
    {
        GPIOI_REG_RESET();
    }
    else if(p_gpiox == GPIOJ)
    {
        GPIOJ_REG_RESET();
    }
    else if(p_gpiox == GPIOK)
    {
        GPIOK_REG_RESET();
    }
}

/*
 * read write
 */

/********************************************************************
 * @fn          - 
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
uint8_t gpio_pin_read(GPIO_RegDef_t *p_gpiox,uint8_t pin_number)
{
    uint8_t value;
    value = (uint8_t) ((p_gpiox->IDR >> pin_number) & 0x00000001);
    return value;
}

/********************************************************************
 * @fn          - 
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
uint16_t gpio_port_read(GPIO_RegDef_t *p_gpiox)
{
    uint16_t value;
    value = (uint16_t) (p_gpiox->IDR);
    return value;
}

/********************************************************************
 * @fn          - 
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
void gpio_pin_write(GPIO_RegDef_t *p_gpiox,uint8_t pin_number,uint8_t pin_value)
{
    if(pin_value == GPIO_PIN_SET)
    {
        SET_BIT(p_gpiox->ODR,pin_number);
    }
    else
    {
        CLEAR_BIT(p_gpiox->ODR,pin_number);
    }
}

/********************************************************************
 * @fn          - 
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
void gpio_port_write(GPIO_RegDef_t *p_gpiox,uint16_t port_value)
{
    p_gpiox->ODR = port_value;
}

/********************************************************************
 * @fn          - 
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
void gpio_pin_toggle(GPIO_RegDef_t *p_gpiox,uint8_t pin_number)
{
    p_gpiox->ODR ^= (1 << pin_number );
}

/*
 * interrupt
 */

/********************************************************************
 * @fn          - 
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
void gpio_irq_config(uint8_t irq_number,uint8_t irq_priority,uint8_t en_or_di)
{
    
}

/********************************************************************
 * @fn          - 
 * 
 * @brief       -
 * 
 * @param[in]   -
 * @param[in]   -
 * 
 * 
 * @return      -
 * 
 * @note        -
 * 
 */
void gpio_irq_handling(uint8_t pin_number)
{
    
}