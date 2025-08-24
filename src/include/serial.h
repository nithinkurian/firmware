#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

void serial_init();
void serial_transmit(uint8_t *buffer,uint16_t length);

#endif // SERIAL_H