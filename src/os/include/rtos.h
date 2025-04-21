#ifndef RTOS_H_
#define RTOS_H_

#include <stdint.h>

void rtos_init();
void run_scheduler();
void rtos_delay(uint32_t tick_count);
void unblock_tasks(void);

#endif /* RTOS_H_ */
