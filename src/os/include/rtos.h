#ifndef RTOS_H_
#define RTOS_H_

#include <stdint.h>
#include <stdbool.h>

typedef void * taskhandle_t;

char * get_rtos_name();
taskhandle_t create_task(void (*task_handler)(void*),uint16_t stack_size, uint8_t priority);
void run_scheduler();
void rtos_delay_tick(uint32_t tick_count);
void rtos_delay_ms(uint32_t ms);
void rtos_delay_until_ms(uint32_t *previous_wake_time,uint32_t ms);
uint32_t get_rtos_tick_count();
void notify_task_setbit(taskhandle_t dest_task,uint32_t bit);
bool notify_task_wait(uint32_t block_time_ms,uint32_t * notification_value);

#endif /* RTOS_H_ */
