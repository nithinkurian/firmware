#ifndef HAL_USART_H
#define HAL_USART_H


#include <stdint.h>
//#include <stdbool.h>


void hal_usart_init(void);
void hal_usart3_transmit(uint8_t *buffer,uint16_t length);

 #endif // HAL_USART_H