#ifndef STM32H743XX_USART_DRIVER_H
#define STM32H743XX_USART_DRIVER_H

#include <stdint.h>
#include "stm32h743xx.h"

#define USART_KER_CLK_PRES HSI_CLK


/*
 * Configuration structure for USART
 */
typedef struct
{
    uint8_t usart_mode;             //Possible values from @USART_MODES
    uint32_t usart_baud_rate;        //Possible values from @USART_BAUD
    uint8_t usart_parity_control;   //Possible values from @USART_PARITYCONTROL
    uint8_t usart_word_length;      //Possible values from @USART_WORDLENGTH
    uint8_t usart_stop_bit_count;   //Possible values from @USART_NOOFSTOPBITS
    uint8_t usart_hw_flow_control;  //Possible values from @USART_HWFLOWCONTROL
} USART_Config_t;

/*
 * USART handle
 */
typedef struct
{
    USART_RegDef_t *pUSARTx;
    USART_Config_t usart_config;
} USART_Handle_t;

/*
 * @USART_MODES
 * USART possible modes
 */
#define USART_MODE_TX_ONLY              0
#define USART_MODE_RX_ONLY              1
#define USART_MODE_TXRX                 2

/*
 *@USART_BAUD
 *Possible options for USART baud rate
 */
#define USART_STD_BAUD_1200                 1200UL
#define USART_STD_BAUD_2400                 2400UL
#define USART_STD_BAUD_9600                 9600UL
#define USART_STD_BAUD_19200                19200UL
#define USART_STD_BAUD_38400                38400UL
#define USART_STD_BAUD_57600                57600UL
#define USART_STD_BAUD_115200               115200UL
#define USART_STD_BAUD_230400               230400UL
#define USART_STD_BAUD_460800               460800UL
#define USART_STD_BAUD_921600               921600UL
#define USART_STD_BAUD_2M                   2000000UL
#define USART_STD_BAUD_3M                   3000000UL
#define USART_STD_BAUD_4M                   4000000UL


/*
 *@USART_PARITYCONTROL
 *Possible options for USART_ParityControl
 */

#define USART_PARITY_EN_ODD   2
#define USART_PARITY_EN_EVEN  1
#define USART_PARITY_DISABLE  0

/*
 *@USART_WORDLENGTH
 *Possible options for USART_WordLength
 */
#define USART_8_BIT_DATA           0
#define USART_9_BIT_DATA           1
#define USART_7_BIT_DATA           2

/*
 *@USART_NOOFSTOPBITS
 *Possible options for USART_NoOfStopBits
 */
#define USART_1_STOP_BIT           0
#define USART_0_5_STOP_BITS        1
#define USART_2_STOP_BITS          2
#define USART_1_5_STOP_BITS        3
/*
 *@USART_HWFLOWCONTROL
 *Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE     0
#define USART_HW_FLOW_CTRL_CTS      1
#define USART_HW_FLOW_CTRL_RTS      2
#define USART_HW_FLOW_CTRL_CTS_RTS  3

/*****************************USART APIs******************************/

/*
 * peripheral clock setup
 */
void usart_peri_clk_control(USART_RegDef_t *p_usartx, uint8_t en_or_di);

/*
 * Init and deinit
 */
void usart_init(USART_Handle_t *p_handle);
void usart_deinit(USART_RegDef_t *p_usartx);

/*
 * read write
 */

void usart_receive_data(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_receive_data_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_receive_data_fifo(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_receive_data_fifo_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_receive_data_dma(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_receive_data_dma_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);

void usart_send_data(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_send_data_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_send_data_fifo(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_send_data_fifo_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_send_data_dma(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);
void usart_send_data_dma_it(USART_Handle_t *p_handle,uint8_t *buffer,uint16_t length);

/*
 * interrupt
 */
void usart_irq_interrupt_config(uint8_t irq_number,uint8_t en_or_di);
void usart_irq_priorityconfig(uint8_t irq_number,uint32_t irq_priority);
void usart_irq_handling(uint8_t pin_number);

/*
 * Other Peripheral Control APIs
 */

/*
 * Application callback
 */


#endif // STM32H743XX_USART_DRIVER_H
