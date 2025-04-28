
#include "rtos.h"
#include "queue.h"
#include <stddef.h>

semaphore_handle_t create_binary_semaphore()
{
   return create_queue(1,1);
}

semaphore_handle_t create_counting_semaphore(uint32_t max_count,uint32_t initial_count)
{
    semaphore_handle_t handle = create_queue(max_count,1);
    for(int i=0;i<initial_count;i++)
    {
        give_semaphore(handle);
    }
   return handle;
}

bool take_semaphore(semaphore_handle_t handle,uint32_t ms)
{
    uint8_t data;
    return receive_from_queue(handle,&data, ms);
}

bool give_semaphore(semaphore_handle_t handle)
{
    uint8_t data;
    return send_to_queue(handle,&data, 10);
}