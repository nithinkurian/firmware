import os
from Environments import *

source = []
source.append('task_scheduler.c')
source.append('notification.c')
source.append('queue.c')
source.append('software_timer.c')
source.append('semaphore.c')

env = get_stm32_env()
env.Append(CPPPATH=['#src/os/include','#src/os/custom_rtos/include','#src/bsp/include','#src/include'])
source_obj = env.Object(source)
env.Library('os',source_obj)