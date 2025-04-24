import os
from Environments import *

source = []
source.append('hal_gpio.c')
source.append('hal_cpu.c')
source.append('hal_processor_faults.c')
source.append('hal_processor_faults_test.c')
source.append('semihosting.c')

env = get_x86_64_env()
env.Append(CPPPATH=['#src/include','#src/bsp/include','#src/os/include'])
source_obj = env.Object(source)
env.Library('bsp',source_obj)