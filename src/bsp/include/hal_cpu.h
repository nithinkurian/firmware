#ifndef HALCPU_H
#define HALCPU_H

#include <stdint.h>

void __disable_irq(void);
void init_systick_timer(uint32_t tick_hz);
void delay_tick(uint32_t tick_delay);
void disable_interrupt();
void enable_interrupt();
uint32_t task_stack_init(uint32_t psp_value, void (*task_handler)(void* parameters));

 #endif // HALCPU_H