import os
from Environments import *

source = []
source.append('custom_rtos.c')

env = get_stm32_env()
env.Append(CPPPATH=['#src/os/include','#src/bsp/include','#src/include'])
source_obj = env.Object(source)
env.Library('os',source_obj)