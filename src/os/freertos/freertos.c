
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

void init_tasks_stack(void);

void rtos_init()
{
	init_tasks_stack();	
}

void run_scheduler()
{
	vTaskStartScheduler();
}


void init_tasks_stack(void)
{

	TaskHandle_t task1_handle;
	TaskHandle_t task2_handle;
	TaskHandle_t task3_handle;
	TaskHandle_t task4_handle;

	BaseType_t status;

	status = xTaskCreate(task1_handler, "Task-1", 200, "Hello world from Task-1", 2, &task1_handle);
	configASSERT(status == pdPASS);

	status = xTaskCreate(task2_handler, "Task-2", 200, "Hello world from Task-1", 2, &task2_handle);
	configASSERT(status == pdPASS);

	status = xTaskCreate(task3_handler, "Task-3", 200, "Hello world from Task-1", 2, &task3_handle);
	configASSERT(status == pdPASS);

	status = xTaskCreate(task4_handler, "Task-4", 200, "Hello world from Task-1", 2, &task4_handle);
	configASSERT(status == pdPASS);

}


void rtos_delay(uint32_t tick_count)
{
	//vTaskDelay(pdMS_TO_TICKS(1000));
	vTaskDelay(tick_count);
}