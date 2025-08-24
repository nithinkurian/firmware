#include "serial.h"
#include "hal_usart.h"

void serial_init()
{
	hal_usart_init();
}

void serial_transmit(uint8_t *buffer,uint16_t length)
{
	hal_usart3_transmit(buffer,length);
}