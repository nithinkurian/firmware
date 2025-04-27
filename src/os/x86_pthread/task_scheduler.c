
#include "rtos.h"
#include "hal_cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include "task_scheduler.h"
#include "sleep.h"
#include "software_timer.h"

extern uint32_t tick_in_hz;


TCB_t user_tasks[MAX_TASKS];
uint8_t current_task = 1;


pthread_t threads[MAX_TASKS],timer_thread;
int thread_args[MAX_TASKS] = {0,1,2,3,4,5,6,7}, timer_thread_args;
int i, result;
extern uint32_t tick_in_hz;

uint8_t next_task_index = 1;

void idle_task(void* parameters); //Idle task
TCB_t * get_current_task_tcb();
void print_queue(queuehandle_t handle);
bool is_queue_empty(queuehandle_t handle);
bool is_queue_full(queuehandle_t handle);

// Function executed by the thread
void *thread_function(void *arg) {
    int thread_id = *(int*)arg;
    int pthread_id = pthread_self();
    //printf("Thread %d:pthread_id %d: Hello from thread!\n", thread_id,pthread_id);
    user_tasks[thread_id].thread_id=pthread_id;
    user_tasks[thread_id].task_handler(NULL);
    pthread_exit(NULL);
}

void *timer_thread_function(void *arg) {
    int thread_id = *(int*)arg;
    timer_manager(NULL);
    pthread_exit(NULL);
}

void idle_task(void* parameters)
{
    while(1)
    {
        sleep_ms(100);
    }
}

char * get_rtos_name()
{
    return "x86Pthread";
}

taskhandle_t create_task(void (*task_handler)(void*),uint16_t stack_size, uint8_t priority)
{
    if(next_task_index >= MAX_TASKS)
    {
        printf("TCB are not available, please increase MAX_TASKS\n");
        while(1);
    }

    user_tasks[next_task_index].task_handler = task_handler;
    next_task_index++;
    return &user_tasks[next_task_index-1];
}

void run_scheduler()
{

    //Initialize systick
    init_systick_timer(TICK_HZ);

    user_tasks[0].task_handler = idle_task;

    for(int i=0;i<next_task_index;i++)
    {
        result = pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
        if (result != 0) {
            perror("Thread creation failed\n");
            exit(1);
        }
    }

    result = pthread_create(&timer_thread, NULL, timer_thread_function, &timer_thread_args);
    if (result != 0) {
        perror("Timer Thread creation failed\n");
        exit(1);
    }
    

	// Wait for threads to finish
    for(int i =0; i < next_task_index; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: All threads completed.\n");
}



uint32_t get_tick_count(void)
{
    return time(0)*tick_in_hz;;
}


void rtos_delay_tick(uint32_t tick_count)
{
	//disable interrupt
	disable_interrupt();

	uint32_t initial_tick = get_tick_count();
	while(initial_tick+ tick_count>get_tick_count())
    {
        sleep_ms(1);
    }

	//enable interrupt
	enable_interrupt();
}

void rtos_delay_ms(uint32_t ms)
{
    uint32_t tick_count = tick_in_hz*ms/1000;
    rtos_delay_tick(tick_count);
}

void rtos_delay_until_ms(uint32_t *previous_wake_time,uint32_t ms)
{
    //disable interrupt
    disable_interrupt();

    uint32_t initial_tick = *previous_wake_time;
    while(initial_tick+ tick_in_hz*ms/1000>get_tick_count())
    {
        sleep_ms(1);
    }
    *previous_wake_time = initial_tick+ tick_in_hz*ms/1000;
    //enable interrupt
    enable_interrupt();
}

uint32_t get_rtos_tick_count()
{
    return get_tick_count();
}

TCB_t * get_current_task_tcb()
{
    int pthread_id = pthread_self();

    for(int i =0; i < next_task_index; i++)
    {
        if(pthread_id == user_tasks[i].thread_id)
        {
            return &user_tasks[i];
        }
    }
    return NULL;
}