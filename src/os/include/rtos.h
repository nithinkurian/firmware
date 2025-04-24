#ifndef RTOS_H_
#define RTOS_H_

#include <stdint.h>

char * get_rtos_name();
void create_task(void (*task_handler)(void*),uint16_t stack_size, uint8_t priority);
void run_scheduler();
void rtos_delay_tick(uint32_t tick_count);
void rtos_delay_ms(uint32_t ms);

#endif /* RTOS_H_ */
