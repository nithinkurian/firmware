import os
from Environments import *

source = []
source.append('x86_pthread.c')

env = get_x86_64_env()
env.Append(CPPPATH=['#src/bsp/include','#src/os/include','#src/include'])
source_obj = env.Object(source)
env.Library('os',source_obj)