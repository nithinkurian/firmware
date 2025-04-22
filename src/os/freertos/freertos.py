Import('env')
source = []

source.append('os/${OS_NAME}/croutine.c')
source.append('os/${OS_NAME}/event_groups.c')
source.append('os/${OS_NAME}/list.c')
source.append('os/${OS_NAME}/queue.c')
source.append('os/${OS_NAME}/stream_buffer.c')
source.append('os/${OS_NAME}/tasks.c')
source.append('os/${OS_NAME}/timers.c')
source.append('os/${OS_NAME}/portable/MemMang/heap_4.c')
source.append('os/${OS_NAME}/portable/GCC/ARM_CM7/r0p1/port.c')

source.append('os/${OS_NAME}/${OS_NAME}.c')

Return('source') 