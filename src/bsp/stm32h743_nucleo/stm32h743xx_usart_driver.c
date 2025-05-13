#include "stm32h743xx_usart_driver.h"
#include <stdio.h>

/*****************************USART APIs******************************/

/********************************************************************
 * @fn          - usart_peri_clk_control
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
void usart_peri_clk_control(USART_RegDef_t *p_usartx, uint8_t en_or_di)
{
    if(en_or_di == ENABLE)
    {
        if(p_usartx == USART1)
        {
            USART1_PERI_CLK_EN();
        }
        else if(p_usartx == USART2)
        {
            USART2_PERI_CLK_EN();
        }
        else if(p_usartx == USART3)
        {
            USART3_PERI_CLK_EN();
        }
        else if(p_usartx == UART4)
        {
            UART4_PERI_CLK_EN();
        }
        else if(p_usartx == UART5)
        {
            UART5_PERI_CLK_EN();
        }
        else if(p_usartx == USART6)
        {
            USART6_PERI_CLK_EN();
        }
        else if(p_usartx == UART7)
        {
            UART7_PERI_CLK_EN();
        }
        else if(p_usartx == UART8)
        {
            UART8_PERI_CLK_EN();
        }
    }
    else
    {
        if(p_usartx == USART1)
        {
            USART1_PERI_CLK_DI();
        }
        else if(p_usartx == USART2)
        {
            USART2_PERI_CLK_DI();
        }
        else if(p_usartx == USART3)
        {
            USART3_PERI_CLK_DI();
        }
        else if(p_usartx == UART4)
        {
            UART4_PERI_CLK_DI();
        }
        else if(p_usartx == UART5)
        {
            UART5_PERI_CLK_DI();
        }
        else if(p_usartx == USART6)
        {
            USART6_PERI_CLK_DI();
        }
        else if(p_usartx == UART7)
        {
            UART7_PERI_CLK_DI();
        }
        else if(p_usartx == UART8)
        {
            UART8_PERI_CLK_DI();
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
void usart_init(USART_Handle_t *p_handle)
{
    //enable USART peripheral clock
    usart_peri_clk_control(p_handle->pUSARTx, ENABLE);

    //Clear USART enable, this should be cleared to change USART registers
    CLEAR_BIT(p_handle->pUSARTx->CR1,0);

    if(p_handle->usart_config.usart_mode == USART_MODE_TX_ONLY)
    {
        //set Transmitter enable
        SET_BIT(p_handle->pUSARTx->CR1,3);
        //clear Receiver enable
        CLEAR_BIT(p_handle->pUSARTx->CR1,2);
    }
    else if (p_handle->usart_config.usart_mode == USART_MODE_RX_ONLY)
    {
        //clear Transmitter enable
        CLEAR_BIT(p_handle->pUSARTx->CR1,3);
        //set Receiver enable
        SET_BIT(p_handle->pUSARTx->CR1,2);
    }
    else if (p_handle->usart_config.usart_mode == USART_MODE_TXRX)
    {
        //set Transmitter enable
        SET_BIT(p_handle->pUSARTx->CR1,3);
        //set Receiver enable
        SET_BIT(p_handle->pUSARTx->CR1,2);
    }

    if(p_handle->usart_config.usart_word_length == USART_7_BIT_DATA)
    {
        //set M1[1:0]= 10
        WRITE_REG(p_handle->pUSARTx->CR1,28,1,1);//M1
        WRITE_REG(p_handle->pUSARTx->CR1,12,0,1);//M0
    }
    else if (p_handle->usart_config.usart_word_length == USART_8_BIT_DATA)
    {
        //set M1[1:0]= 00
        WRITE_REG(p_handle->pUSARTx->CR1,28,0,1);//M1
        WRITE_REG(p_handle->pUSARTx->CR1,12,0,1);//M0
    }
    else if (p_handle->usart_config.usart_word_length == USART_9_BIT_DATA)
    {
        //set M1[1:0]= 01
        WRITE_REG(p_handle->pUSARTx->CR1,28,0,1);//M1
        WRITE_REG(p_handle->pUSARTx->CR1,12,1,1);//M0
    }

    if(p_handle->usart_config.usart_parity_control == USART_PARITY_DISABLE)
    {
        //clear parity control
        CLEAR_BIT(p_handle->pUSARTx->CR1,10);
    }
    else if (p_handle->usart_config.usart_parity_control == USART_PARITY_EN_ODD)
    {
        //set parity control
        SET_BIT(p_handle->pUSARTx->CR1,10);
        //set odd parity
        SET_BIT(p_handle->pUSARTx->CR1,11);
    }
    else if (p_handle->usart_config.usart_parity_control == USART_PARITY_EN_EVEN)
    {
        //set parity control
        SET_BIT(p_handle->pUSARTx->CR1,10);
        //set even parity
        CLEAR_BIT(p_handle->pUSARTx->CR1,11);
    }

    //set stop bits
    WRITE_REG(p_handle->pUSARTx->CR2,12,p_handle->usart_config.usart_stop_bit_count,2);

    if(p_handle->usart_config.usart_hw_flow_control == USART_HW_FLOW_CTRL_NONE)
    {
        //Disable RTS
        WRITE_REG(p_handle->pUSARTx->CR3,8,0,1);//RTSE
        //Disable CTS
        WRITE_REG(p_handle->pUSARTx->CR3,9,0,1);//CTSE
    }
    else if(p_handle->usart_config.usart_hw_flow_control == USART_HW_FLOW_CTRL_CTS)
    {
        //Disable RTS
        WRITE_REG(p_handle->pUSARTx->CR3,8,0,1);//RTSE
        //Enable CTS
        WRITE_REG(p_handle->pUSARTx->CR3,9,1,1);//CTSE
    }
    else if(p_handle->usart_config.usart_hw_flow_control == USART_HW_FLOW_CTRL_RTS)
    {
        //Enable RTS
        WRITE_REG(p_handle->pUSARTx->CR3,8,1,1);//RTSE
        //Disable CTS
        WRITE_REG(p_handle->pUSARTx->CR3,9,0,1);//CTSE
    }
    else if(p_handle->usart_config.usart_hw_flow_control == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        //Enable RTS
        WRITE_REG(p_handle->pUSARTx->CR3,8,1,1);//RTSE
        //Enable CTS
        WRITE_REG(p_handle->pUSARTx->CR3,9,1,1);//CTSE
    }

    //Sets Baudrate with oversampling by 16
    //Need to implement API for RCC get value usart_ker_ckpres for usart_ker_ck
    WRITE_REG(p_handle->pUSARTx->BRR,0,USART_KER_CLK_PRES/p_handle->usart_config.usart_baud_rate,0xFFFF);


    //Set USART enable
    SET_BIT(p_handle->pUSARTx->CR1,0);

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
void usart_deinit(USART_RegDef_t *p_usartx)
{
    if(p_usartx == USART1)
    {
        USART1_REG_RESET();
    }
    else if(p_usartx == USART2)
    {
        USART2_REG_RESET();
    }
    else if(p_usartx == USART3)
    {
        USART3_REG_RESET();
    }
    else if(p_usartx == UART4)
    {
        UART4_REG_RESET();
    }
    else if(p_usartx == UART5)
    {
        UART5_REG_RESET();
    }
    else if(p_usartx == USART6)
    {
        USART6_REG_RESET();
    }
    else if(p_usartx == UART7)
    {
        UART7_REG_RESET();
    }
    else if(p_usartx == UART8)
    {
        UART8_REG_RESET();
    }
}

/*
 * read write
 */

void usart_receive_data(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_receive_data_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_receive_data_fifo(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_receive_data_fifo_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_receive_data_dma(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_receive_data_dma_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_send_data(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{
    uint16_t index = 0;
    while(index<length)
    {
        p_handle->pUSARTx->TDR = buffer[index++];
        while(!READ_BIT(p_handle->pUSARTx->ISR,7));
    }
    
}

void usart_send_data_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_send_data_fifo(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_send_data_fifo_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_send_data_dma(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

}

void usart_send_data_dma_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length)
{

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
void usart_irq_interrupt_config(uint8_t irq_number,uint8_t en_or_di)
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
void usart_irq_priorityconfig(uint8_t irq_number,uint32_t irq_priority)
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
void usart_irq_handling(uint8_t pin_number)
{
}

/*
 * Other Peripheral Control APIs
 */

/*
 * Application callback
 */
