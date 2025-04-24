import os
from Environments import *

source = []
source.append('croutine.c')
source.append('event_groups.c')
source.append('list.c')
source.append('queue.c')
source.append('stream_buffer.c')
source.append('tasks.c')
source.append('timers.c')
source.append('portable/MemMang/heap_4.c')
source.append('portable/GCC/ARM_CM7/r0p1/port.c')

source.append('freertos.c')
source.append('freertos_hook.c')

env = get_stm32_env()
#env.Append(CPPPATH=['#src/include','#src/bsp/include', '#src/os/include', 'os/${OS_NAME}/include', 'os/${OS_NAME}/portable/GCC/ARM_CM7/r0p1', 'os/${OS_NAME}'])
env.Append(CPPPATH=['include','.','portable/GCC/ARM_CM7/r0p1','#src/bsp/include','#src/os/include'])
source_obj = env.Object(source)
env.Library('os',source_obj)