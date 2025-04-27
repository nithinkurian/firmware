
#ifndef TASK_SCHEDULER_H_
#define TASK_SCHEDULER_H_

#include <pthread.h>

#define TICK_HZ             1000U
#define MAX_TASKS			5


typedef struct
{
    void (*task_handler)(void* parameters);
    pthread_t thread_id;
    uint32_t notification_value;
    bool notification_status;
}TCB_t;


TCB_t * get_current_task_tcb();
uint32_t get_tick_count(void);

extern uint32_t tick_in_hz;

#endif /* TASK_SCHEDULER_H_ */
