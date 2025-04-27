
#include "rtos.h"
#include "hal_cpu.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h> 
#include <limits.h>
#include <stdint.h>
#include <queue.h>

char * get_rtos_name()
{
	return "FreeRTOS";
}

void run_scheduler()
{
	vTaskStartScheduler();
}

taskhandle_t create_task(void (*task_handler)(void*),uint16_t stack_size, uint8_t priority)
{
	TaskHandle_t task_handle;
	BaseType_t status;

	status = xTaskCreate(task_handler, "", stack_size, "", priority, &task_handle);
	configASSERT(status == pdPASS);
	return task_handle;
}


void rtos_delay_tick(uint32_t tick_count)
{
	vTaskDelay(tick_count);
}

void rtos_delay_ms(uint32_t ms)
{
	vTaskDelay(pdMS_TO_TICKS(ms));
}

void rtos_delay_until_ms(uint32_t *previous_wake_time,uint32_t ms)
{
	vTaskDelayUntil(previous_wake_time, pdMS_TO_TICKS(ms));
}

uint32_t get_rtos_tick_count()
{
	return xTaskGetTickCount();
}

void notify_task_setbit(taskhandle_t dest_task,uint32_t bit)
{
	xTaskNotify(dest_task, bit, eSetBits);
}


bool notify_task_wait(uint32_t block_time_ms,uint32_t * notification_value)
{
	TickType_t max_block_time = pdMS_TO_TICKS( block_time_ms );
	BaseType_t xResult = xTaskNotifyWait( pdFALSE,          /* Don't clear bits on entry. */
                                 ULONG_MAX,        /* Clear all bits on exit. */
                                 notification_value, /* Stores the notified value. */
                                 max_block_time );
	return (xResult == pdPASS);
}

queuehandle_t create_queue(const uint32_t queue_length,const uint32_t item_size)
{
	QueueHandle_t q_handle = xQueueCreate(queue_length,item_size);
	configASSERT(q_handle != pdPASS);
	return q_handle;
}

bool send_to_queue(queuehandle_t handle,void * data, uint32_t ms)
{
	if( xQueueSend(handle, data, pdMS_TO_TICKS(ms)) == pdPASS )
	{
	    return true;
	}
	else
	{
	    return false;
	}
}

bool receive_from_queue(queuehandle_t handle,void * data, uint32_t ms)
{
	return (xQueueReceive(handle,data,pdMS_TO_TICKS(ms)) == pdTRUE);
}