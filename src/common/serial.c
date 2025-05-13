#include "serial.h"
#include "hal_usart.h"

void serial_init()
{
	hal_usart_init();
}