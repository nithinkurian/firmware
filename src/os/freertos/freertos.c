
#include "rtos.h"
#include "hal_cpu.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

extern void task1_handler(void* parameters); //This is task1
extern void task2_handler(void* parameters); //This is task2
extern void task3_handler(void* parameters); //This is task3
extern void task4_handler(void* parameters); //This is task4
extern void idle_task(void* parameters); //Idle task

char * get_rtos_name()
{
	return "FreeRTOS";
}

void run_scheduler()
{
	vTaskStartScheduler();
}

void create_task(void (*task_handler)(void*),uint16_t stack_size, uint8_t priority)
{
	TaskHandle_t task_handle;
	BaseType_t status;

	status = xTaskCreate(task_handler, "", stack_size, "", priority, &task_handle);
	configASSERT(status == pdPASS);
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
