import os
from Environments import *


sources = []
sources.append('main.c')
sources.append('led.c')
sources.append('serial.c')

env = get_x86_64_env()
env.Append(CPPPATH=['#src/include','#src/bsp/include','#src/os/include'])
source_obj = env.Object(sources)
env.Library('common',source_obj)