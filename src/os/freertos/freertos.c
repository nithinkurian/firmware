
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


void rtos_delay(uint32_t tick_count)
{
	//vTaskDelay(pdMS_TO_TICKS(1000));
	vTaskDelay(tick_count);
}