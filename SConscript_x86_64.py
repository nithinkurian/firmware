import os
from Environments import *

env = get_x86_64_env()

target = 'x86_64'
env.Append(BOARD='x86_64')
env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${BOARD}'+'/firmware.map')

env.Append(CPPPATH=['include','bsp/include'])

source = SConscript('#common_source.py', exports='env')
source.append('bsp/'+'${BOARD}'+'/semihosting.c')

firmware = env.Program('firmware.elf',source)
env.SideEffect('firmware.map', firmware)