
#ifndef TASK_SCHEDULER_H_
#define TASK_SCHEDULER_H_

#include <pthread.h>

#define TICK_HZ             1000U
#define MAX_TASKS			8


typedef struct
{
    void (*task_handler)(void* parameters);
    pthread_t thread_id;
    uint32_t notification_value;
    bool notification_status;
}TCB_t;


TCB_t * get_current_task_tcb();
uint32_t get_tick_count(void);

#endif /* TASK_SCHEDULER_H_ */
