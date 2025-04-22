
#include "rtos.h"
#include "hal_cpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stddef.h>

extern void task1_handler(void* parameters); //This is task1
extern void task2_handler(void* parameters); //This is task2
extern void task3_handler(void* parameters); //This is task3
extern void task4_handler(void* parameters); //This is task4
extern void idle_task(void* parameters); //Idle task
uint64_t get_tick_count(void);

#define MAX_TASKS			5
 #define TICK_HZ                1000U

typedef struct
{
	void (*task_handler)(void* parameters);
}TCB_t;
TCB_t user_tasks[MAX_TASKS];

uint32_t current_task = 1;


pthread_t threads[MAX_TASKS];
int thread_args[MAX_TASKS] = {0,1,2,3,4};
int i, result;
extern uint32_t tick_in_hz;

// Function executed by the thread
void *thread_function(void *arg) {
    int thread_id = *(int*)arg;
    //printf("Thread %d: Hello from thread!\n", thread_id);
    user_tasks[thread_id].task_handler(NULL);
    pthread_exit(NULL);
}

void rtos_init()
{
	user_tasks[0].task_handler = idle_task;
	user_tasks[1].task_handler = task1_handler;
	user_tasks[2].task_handler = task2_handler;
	user_tasks[3].task_handler = task3_handler;
	user_tasks[4].task_handler = task4_handler;


    //Initialize systick
    init_systick_timer(TICK_HZ);

    // Create threads
    for(int i =0; i < MAX_TASKS; i++)
    {
        result = pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
        if (result != 0) {
            perror("Thread creation failed");
            exit(1);
        }
    }
}

void run_scheduler()
{
	// Wait for threads to finish
    for(int i =0; i < MAX_TASKS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: All threads completed.\n");
}



uint64_t get_tick_count(void)
{
    return time(0)*tick_in_hz;;
}


void rtos_delay(uint32_t tick_count)
{
	//disable interrupt
	disable_interrupt();

	uint64_t initial_tick = get_tick_count();
	while(initial_tick+ tick_count>get_tick_count());

	//enable interrupt
	enable_interrupt();
}