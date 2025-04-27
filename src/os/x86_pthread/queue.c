
#include "rtos.h"
#include <stdio.h>
#include <stdlib.h>
#include "print_colour.h"
#include "queue.h"
#include <string.h>
#include "task_scheduler.h"
#include "sleep.h"

extern uint32_t tick_in_hz;


QCB_t user_queue[MAX_QUEUES];
uint8_t next_queue = 0;

void print_queue(queuehandle_t handle);

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
    "q_handle->queue_buffer %ld \n"
        ,q_handle->queue_length
        ,q_handle->item_size
        ,q_handle->front
        ,q_handle->back
        ,(uint64_t) q_handle->queue_buffer
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

    memcpy(queue_handle->queue_buffer+queue_handle->front*queue_handle->item_size,data, queue_handle->item_size);
    queue_handle->front++;
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
    memcpy(data,queue_handle->queue_buffer+queue_handle->back*queue_handle->item_size, queue_handle->item_size);
    queue_handle->back++;

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