#include <stdint.h>
#include "hal_cpu.h"
#include "led.h"
#include <stdio.h>
#include "print_colour.h"
#include "hal_processor_faults.h"
#include "hal_processor_faults_test.h" //just for testing
#include "rtos.h"


#define TASK_1_ON    0x01
#define TASK_1_OFF   0x10
#define TASK_2_ON    0x02
#define TASK_2_OFF   0x20
#define TASK_3_ON    0x04
#define TASK_3_OFF   0x40
#define TASK_4_ON    0x08
#define TASK_4_OFF   0x80

#define TASK_1_DELAY 1000
#define TASK_2_DELAY 2 * TASK_1_DELAY
#define TASK_3_DELAY 2 * TASK_2_DELAY
#define TASK_4_DELAY 2 * TASK_3_DELAY
#define TASK_5_DELAY 2 * TASK_4_DELAY

//Semi hosting init function
extern void initialise_monitor_handles(void);

taskhandle_t task1_handler;
taskhandle_t task2_handler;
taskhandle_t task3_handler;
taskhandle_t task4_handler;
taskhandle_t notification_receive_task_handler;

void task1_function(void* parameters); //This is task1
void task2_function(void* parameters); //This is task2
void task3_function(void* parameters); //This is task3
void task4_function(void* parameters); //This is task4
void notification_receive_task( void *pvParameter );


taskhandle_t send_handler;
taskhandle_t receive_handler;

void send_task(void* parameters); //This is send
void receive_task(void* parameters); //This is receive

int main(void)
{
	//Semi hosting init function
	initialise_monitor_handles();

	//enabling processor faults
	enable_processor_faults();

	//enable one by one for testing
	//generate_undefined_instruction_usagefault();
	//generate_invalid_state_usagefault();
	//generate_divide_by_zero_usagefault();

	//Initialize LED
	led_init();

	printf(BOLD_DARK_GRAY"Initialized\n");
	printf("%s Initializing\n",get_rtos_name());

	task1_handler   = create_task(task1_function,760, 2);
	task2_handler   = create_task(task2_function,760, 2);
	task3_handler   = create_task(task3_function,760, 2);
	task4_handler   = create_task(task4_function,760, 2);
	notification_receive_task_handler = create_task(notification_receive_task,760, 2);
	send_handler    = create_task(send_task,760, 2);
	receive_handler = create_task(receive_task,760, 2);
	
	
	run_scheduler();

}

void task1_function(void* parameters)
{
	uint32_t previous_wake_time = get_rtos_tick_count();
	while(1)
	{
#if 0
	 	char data[80];
	 	char * p = data;
	 	printf("Enter data\n");
    	scanf("%s", p);
    	printf("data %s \n",data);
#endif
		printf(BOLD_YELLOW"task1 ON\n\r");
		turn_on_led(YELLOW);
		notify_task_setbit(notification_receive_task_handler,TASK_1_ON);
		rtos_delay_until_ms(&previous_wake_time,TASK_1_DELAY);
		printf(YELLOW_COLOUR"task1 OFF\n\r");	
		turn_off_led(YELLOW);
		notify_task_setbit(notification_receive_task_handler,TASK_1_OFF);
		rtos_delay_until_ms(&previous_wake_time,TASK_1_DELAY);
	}
}

void task2_function(void* parameters)
{
	uint32_t previous_wake_time = get_rtos_tick_count();
	while(1)
	{
		printf(BOLD_BLUE"task2 ON\n\r");
		turn_on_led(BLUE);
		notify_task_setbit(notification_receive_task_handler,TASK_2_ON);
		rtos_delay_until_ms(&previous_wake_time,TASK_2_DELAY);
		printf(BLUE_COLOUR"task2 OFF\n\r");	
		turn_off_led(BLUE);
		notify_task_setbit(notification_receive_task_handler,TASK_2_OFF);
		rtos_delay_until_ms(&previous_wake_time,TASK_2_DELAY);
	}
}

void task3_function(void* parameters)
{
	uint32_t previous_wake_time = get_rtos_tick_count();
	while(1)
	{
		printf(BOLD_RED"task3 ON\n\r");
		turn_on_led(RED);
		notify_task_setbit(notification_receive_task_handler,TASK_3_ON);
		rtos_delay_until_ms(&previous_wake_time,TASK_3_DELAY);
		printf(RED_COLOUR"task3 OFF\n\r");	
		turn_off_led(RED);
		notify_task_setbit(notification_receive_task_handler,TASK_3_OFF);
		rtos_delay_until_ms(&previous_wake_time,TASK_3_DELAY);
	}
}

void task4_function(void* parameters)
{
	uint32_t previous_wake_time = get_rtos_tick_count();
	while(1)
	{
		printf(BOLD_GREEN"task4 ON\n\r");
		notify_task_setbit(notification_receive_task_handler,TASK_4_ON);
		rtos_delay_until_ms(&previous_wake_time,TASK_4_DELAY);
		printf(GREEN_COLOUR"task4 OFF\n\r");
		notify_task_setbit(notification_receive_task_handler,TASK_4_OFF);
		rtos_delay_until_ms(&previous_wake_time,TASK_4_DELAY);
	}
}

void send_task(void* parameters) //This is send
{
	while(1);
}

void receive_task(void* parameters) //This is receive
{
	while(1);
}


void notification_receive_task( void *pvParameter )
{
	printf(TEAL_COLOUR"notification_receive_task\n\r");
   for( ;; )
   {
      uint32_t notification_value = 0;
      if(notify_task_wait(TASK_5_DELAY,&notification_value))
      {
      	//printf("%x \n\r",notification_value);
      	/* A notification was received. See which bits were set. */
         if( ( notification_value & TASK_1_ON ) != 0 )
         {
            printf(BOLD_YELLOW"Notification : TASK_1_ON\n\r");
         }
         
         /* A notification was received. See which bits were set. */
         if( ( notification_value & TASK_1_OFF ) != 0 )
         {
            printf(YELLOW_COLOUR"Notification : TASK_1_OFF\n\r");
         }

      	/* A notification was received. See which bits were set. */
         if( ( notification_value & TASK_2_ON ) != 0 )
         {
            printf(BOLD_BLUE"Notification : TASK_2_ON\n\r");
         }
         
         /* A notification was received. See which bits were set. */
         if( ( notification_value & TASK_2_OFF ) != 0 )
         {
            printf(BLUE_COLOUR"Notification : TASK_2_OFF\n\r");
         }

         if( ( notification_value & TASK_3_ON ) != 0 )
         {
            printf(BOLD_RED"Notification : TASK_3_ON\n\r");
         }

      	/* A notification was received. See which bits were set. */
         if( ( notification_value & TASK_3_OFF ) != 0 )
         {
            printf(RED_COLOUR"Notification : TASK_3_OFF\n\r");
         }

         /* A notification was received. See which bits were set. */
         if( ( notification_value & TASK_4_ON ) != 0 )
         {
            printf(BOLD_GREEN"Notification : TASK_4_ON\n\r");
         }

         if( ( notification_value & TASK_4_OFF ) != 0 )
         {
            printf(GREEN_COLOUR"Notification : TASK_4_OFF\n\r");
         }
      }
      else
      {
      	printf(TEAL_COLOUR"no notification\n\r");
      }
   }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
