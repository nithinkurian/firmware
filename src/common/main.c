#include <stdint.h>
#include "hal_cpu.h"
#include "led.h"
#include <stdio.h>
#include "print_colour.h"
#include "hal_processor_faults.h"
#include "hal_processor_faults_test.h" //just for testing
#include "rtos.h"
#include <string.h>


#define TASK_1_ON    	0x01
#define TASK_1_OFF   	0x02
#define RECEIVED_DATA	0x04

#define TASK_1_DELAY 1000

//Semi hosting init function
extern void initialise_monitor_handles(void);

taskhandle_t task1_handler;
taskhandle_t notification_receive_task_handler;
taskhandle_t send_handler;
taskhandle_t receive_handler;
queuehandle_t queue_data_handler;

void task1_function(void* parameters); //This is task1
void receive_task(void* parameters); //This is receive
void notification_receive_task( void *pvParameter );

void timer_callback( timerhandle_t timer_handle );

#if defined(X86_64)
#define U32_PRINT	"d"
#else
#define U32_PRINT	"ld"
#endif


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

	printf(BOLD_DARK_GRAY"%"U32_PRINT": Initialized\n",get_rtos_tick_count());
	printf("%"U32_PRINT": %s Initializing\n",get_rtos_tick_count(),get_rtos_name());

	task1_handler   = create_task(task1_function,760, 2);
	notification_receive_task_handler = create_task(notification_receive_task,760, 2);
	receive_handler = create_task(receive_task,760, 2);
	queue_data_handler = create_queue(80,sizeof(char));
	
	run_scheduler();

}

void timer_callback( timerhandle_t timer_handle )
{
	uint8_t index = 0;
	char data[] = "Welcome to queue";
	#if defined(X86_64)
	printf(BOLD_PURPLE"%"U32_PRINT": Timer : Sending Data, length %ld : %s \n",get_rtos_tick_count(),strlen(data),data);
	#else
	printf(BOLD_PURPLE"%"U32_PRINT": Timer : Sending Data, length %d : %s \n",get_rtos_tick_count(),strlen(data),data);
	#endif
	do
	{
		if(!send_to_queue(queue_data_handler,&data[index], 0))
		{
			printf(BOLD_PURPLE"%"U32_PRINT": Sending to data queue failed @ index: %d\n",get_rtos_tick_count(),index);
			break;
		}
	}		
	while(data[index++]!='\0');
}

void task1_function(void* parameters)
{

	create_and_start_software_timer(4000,true,timer_callback);

	uint32_t previous_wake_time = get_rtos_tick_count();
	while(1)
	{
		turn_on_led(YELLOW);
		notify_task_setbit(notification_receive_task_handler,TASK_1_ON);
		rtos_delay_until_ms(&previous_wake_time,TASK_1_DELAY);
		turn_off_led(YELLOW);
		notify_task_setbit(notification_receive_task_handler,TASK_1_OFF);
		rtos_delay_until_ms(&previous_wake_time,TASK_1_DELAY);
	}
}

void receive_task(void* parameters) //This is receive
{

	char data[80];
	while(1)
	{
		memset(data,0,sizeof(data));
		uint8_t index = 0;
		while(1)
		{
			if(!receive_from_queue(queue_data_handler,&data[index], 20000))
			{
				data[index++]='\0';
				break;
			}
			if(data[index]=='\0')
			{
				printf(BOLD_TEAL"%"U32_PRINT": Received data length %d : %s \n",get_rtos_tick_count(),index,data);
				notify_task_setbit(notification_receive_task_handler,RECEIVED_DATA);
				break;
			}
			index++;
		}
	}
	
}


void notification_receive_task( void *pvParameter )
{
	bool red_state = false, blue_state = false;
	printf(TEAL_COLOUR"%"U32_PRINT": notification_receive_task\n\r",get_rtos_tick_count());
   for( ;; )
   {
      uint32_t notification_value = 0;
      if(notify_task_wait(20000,&notification_value))
      {

			
      	//printf("%x \n\r",notification_value);
      	/* A notification was received. See which bits were set. */
         if( ( notification_value & TASK_1_ON ) != 0 )
         {
         	toggle_led(RED,&red_state);
            printf(BOLD_YELLOW"%"U32_PRINT": Notification : TASK_1_ON\n\r",get_rtos_tick_count());
         }
         
         /* A notification was received. See which bits were set. */
         if( ( notification_value & TASK_1_OFF ) != 0 )
         {
         	toggle_led(RED,&red_state);
            printf(YELLOW_COLOUR"%"U32_PRINT": Notification : TASK_1_OFF\n\r",get_rtos_tick_count());
         }

      	/* A notification was received. See which bits were set. */
         if( ( notification_value & RECEIVED_DATA ) != 0 )
         {
         	toggle_led(BLUE,&blue_state);
            printf(BOLD_BLUE"%"U32_PRINT": Notification : RECEIVED_DATA\n\r",get_rtos_tick_count());
         }
         
      }
      else
      {
      	printf(TEAL_COLOUR"%"U32_PRINT" no notification\n\r",get_rtos_tick_count());
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
