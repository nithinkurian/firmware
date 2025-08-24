#include "hal_usart.h"
#include <stdio.h>
#include "print_colour.h"

void hal_usart_init(void)
{

}


void hal_usart3_transmit(uint8_t *buffer,uint16_t length)
{
    printf(BOLD_YELLOW"%s\n\r",buffer);
}