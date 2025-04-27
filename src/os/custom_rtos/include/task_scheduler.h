
#ifndef TASK_SCHEDULER_H_
#define TASK_SCHEDULER_H_

/* Stack memory calculations */
#define SIZE_TASK_STACK		1024U
#define SIZE_SCHED_STACK	1024U

#define SRAM_START			0x20000000U
#define SIZE_SRAM			( (128) * (1024))
#define SRAM_END			( (SRAM_START) + (SIZE_SRAM))

#define SCHED_STACK_START	SRAM_END
#define IDLE_STACK_START	( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define FIRST_STACK_START	( (SRAM_END) - (2 * SIZE_TASK_STACK) )

#define TASK_READY_STATE 	0x00
#define TASK_BLOCKED_STATE 	0xFF

#define TICK_HZ				1000U


typedef struct
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t current_state;
	uint32_t notification_value;
    uint8_t notification_status;
    uint8_t queue_waiting_state;
    uint32_t currently_waiting_queue;
	void (*task_handler)(void* parameters);
}TCB_t;


TCB_t * get_current_task_tcb();
void schedule(void);

#define MAX_TASKS           8

#endif /* TASK_SCHEDULER_H_ */
