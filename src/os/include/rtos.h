#ifndef RTOS_H_
#define RTOS_H_

#include <stdint.h>

void create_task(void (*task_handler)(void*),uint16_t stack_size, uint8_t priority);
void run_scheduler();
void rtos_delay(uint32_t tick_count);

#endif /* RTOS_H_ */
