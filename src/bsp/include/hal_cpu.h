#ifndef HALCPU_H
#define HALCPU_H

#include <stdint.h>

void __disable_irq(void);
void init_systick_timer(uint32_t tick_hz);
uint64_t get_tick_count(void);
void delay_tick(uint32_t tick_delay);

 #endif // HALCPU_H