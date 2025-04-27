
#include "rtos.h"
#include "hal_cpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stddef.h>
#include <string.h>
#include "print_colour.h"


typedef struct
{
    void (*task_handler)(void* parameters);
    pthread_t thread_id;
    uint32_t notification_value;
    bool notification_status;
}TCB_t;


// Defining the Queue structure
typedef struct {
    void *queue_buffer;
    uint16_t queue_length;
    uint16_t item_size;
    int front;
    int back;
} QCB_t;

#define TICK_HZ             1000U
#define MAX_TASKS			8
TCB_t user_tasks[MAX_TASKS];
uint8_t current_task = 1;


#define MAX_QUEUES           2
QCB_t user_queue[MAX_QUEUES];
uint8_t next_queue = 0;


pthread_t threads[MAX_TASKS];
int thread_args[MAX_TASKS] = {0,1,2,3,4,5,6,7};
int i, result;
extern uint32_t tick_in_hz;

uint8_t next_task_index = 1;

void idle_task(void* parameters); //Idle task
TCB_t * get_current_task_tcb();
uint32_t get_tick_count(void);
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

int sleep_ms(long ms) {
    struct timespec req, rem;

    if (ms > 999) {
        req.tv_sec = (int)(ms / 1000);
        req.tv_nsec = (ms % 1000) * 1000000L;
    } else {
        req.tv_sec = 0;
        req.tv_nsec = ms * 1000000L;
    }

    return nanosleep(&req, &rem);
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

void notify_task_setbit(taskhandle_t dest_task,uint32_t bit)
{
    TCB_t * dest_task_tcb = dest_task;
    dest_task_tcb->notification_value |= bit;
    dest_task_tcb->notification_status = true;
}

bool notify_task_wait(uint32_t block_time_ms,uint32_t * notification_value)
{
    //disable interrupt
    disable_interrupt();
    uint32_t tick_count = tick_in_hz*block_time_ms/1000;
    uint32_t initial_tick = get_tick_count();
    TCB_t * current_task_tcb = get_current_task_tcb();
    if(current_task_tcb == NULL)
    {
        printf("current_task_tcb is NULL\n");
        while(1);
        return false;
    }
    while(initial_tick+ tick_count>get_tick_count())
    {
        if(current_task_tcb->notification_status != 0)
        {
            *notification_value = current_task_tcb->notification_value;
            current_task_tcb->notification_value = 0;
            current_task_tcb->notification_status = false;

            //enable interrupt
            enable_interrupt();
            return true;
        }
        sleep_ms(1);
    }

    //enable interrupt
    enable_interrupt();
    return false;
}

bool is_queue_empty(queuehandle_t handle)
{
    QCB_t * queue_handle = (QCB_t *)handle;
    return (queue_handle->back == -1);
}

bool is_queue_full(queuehandle_t handle)
{
    QCB_t * queue_handle = (QCB_t *)handle;
    return (queue_handle->back == queue_handle->front);
}

queuehandle_t create_queue(const uint32_t queue_length,const uint32_t item_size)
{
    if(next_queue >= MAX_QUEUES)
    {
        printf("QCB are not available, please increase MAX_QUEUES\n");
        while(1);
    }

    QCB_t * q_handle = &user_queue[next_queue];

    if(q_handle == NULL)
    {
        return NULL;
    }

    q_handle->queue_length = queue_length;
    q_handle->item_size =item_size;
    q_handle->front = 0;
    q_handle->back = -1;
    q_handle->queue_buffer=malloc(queue_length*item_size);

    if(q_handle->queue_buffer == NULL)
    {
        printf("Queue buffer allocation failed\n");
        while(1);
    }

    next_queue++;
    return q_handle;
}



void print_queue(queuehandle_t handle)
{
    QCB_t * q_handle = (QCB_t *)handle;
    printf(RED_COLOUR"q_handle->queue_length %d \n"
    "q_handle->item_size %d \n"
    "q_handle->front %d \n"
    "q_handle->back %d \n"
    "q_handle->queue_buffer %d \n"
        ,q_handle->queue_length
        ,q_handle->item_size
        ,q_handle->front
        ,q_handle->back
        ,(uint32_t) q_handle->queue_buffer
        );
}

bool send_to_queue(queuehandle_t handle,void * data, uint32_t ms)
{
    QCB_t * queue_handle = (QCB_t *)handle;
    if(is_queue_full(queue_handle))
    {
        uint32_t initial_tick = get_tick_count();
        uint32_t tick_count = tick_in_hz*ms/1000;

        while(initial_tick+ tick_count>get_tick_count())
        {
            if(!is_queue_full(queue_handle))
            {
                break;
            }
            sleep_ms(1);
        }
    }

    if(is_queue_full(queue_handle))
    {
        return false;
    }

    if(data == NULL)
    {
        printf("Queue data pointer is null\n");
        while(1);
    }

    memcpy(&(queue_handle->queue_buffer[queue_handle->front++]),data, queue_handle->item_size);
    if(queue_handle->front == queue_handle->queue_length)
    {
        queue_handle->front = 0;
    }

    if(queue_handle->back == -1)
    {
        queue_handle->back = 0;
    }

    return true;
}

bool receive_from_queue(queuehandle_t handle,void * data, uint32_t ms)
{
    QCB_t * queue_handle = (QCB_t *)handle;
    if(is_queue_empty(queue_handle))
    {
        uint32_t initial_tick = get_tick_count();
        uint32_t tick_count = tick_in_hz*ms/1000;

        while(initial_tick+ tick_count>get_tick_count())
        {
            if(!is_queue_empty(queue_handle))
            {
                break;
            }
            sleep_ms(1);
        }
    }

    if(is_queue_empty(queue_handle))
    {
        return false;
    }

    if(data == NULL)
    {
        printf(BOLD_TEAL"Queue data pointer is null\n");
        while(1);
    }

    //print_queue(queue_handle);
    memcpy(data,&(queue_handle->queue_buffer[queue_handle->back++]), queue_handle->item_size);

    if(queue_handle->back == queue_handle->queue_length)
    {
        queue_handle->back = 0;
    }

    if(queue_handle->back == queue_handle->front)
    {
        queue_handle->front = 0;
        queue_handle->back = -1;
    }

    //print_queue(queue_handle);
    return true;
}
