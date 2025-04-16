import os
from Environments import *

env = get_x86_64_env()

env.Append(BOARD_NAME='x86_64')
env.Append(TARGET_NAME='X8664001N')
env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${TARGET_NAME}'+'/firmware.map')

env.Append(CPPPATH=['include','bsp/include'])

source = SConscript('#common_source.py', exports='env')
source.append('bsp/'+'${BOARD_NAME}'+'/semihosting.c')

firmware = env.Program('firmware.elf',source)
env.SideEffect('firmware.map', firmware)