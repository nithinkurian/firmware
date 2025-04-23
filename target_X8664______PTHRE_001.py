import os
from Environments import *

env = get_x86_64_env()

env.Append(OS_NAME='x86_pthread')
env.Append(BOARD_NAME='x86_64')
env.Append(TARGET_NAME='X8664______PTHRE_001')
env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${TARGET_NAME}'+'/firmware.map')
env.Append(CPPPATH=['include','bsp/include', 'os/include'])

source = SConscript('#src/common/common_source.py', exports='env')
source.append(SConscript('bsp/'+env["BOARD_NAME"]+'/'+env["BOARD_NAME"]+'.py', exports='env'))
source.append(SConscript('os/'+env["OS_NAME"]+'/'+env["OS_NAME"]+'.py', exports='env'))

firmware = env.Program('firmware.elf',source)
env.SideEffect('firmware.map', firmware)