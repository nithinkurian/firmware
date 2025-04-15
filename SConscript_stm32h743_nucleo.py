import os
from Environments import *
#from common_source import *

env = get_stm32_env()

env.Append(BOARD='stm32h743_nucleo')
env.Append(LINKFLAGS='--specs=nano.specs')
env.Append(LINKFLAGS='-T src/bsp/'+'${BOARD}'+'/stm32_ls.ld')
env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${BOARD}'+'/firmware.map')

env.Append(CPPPATH=['include','bsp/include'])

source = SConscript('#common_source.py', exports='env')
source.append('bsp/'+'${BOARD}'+'/stm32_startup.c')
source.append('bsp/'+'${BOARD}'+'/syscalls.c')

firmware = env.Program('firmware.elf',source)
env.SideEffect('firmware.map', firmware)
env.Command(target='firmware.list',source='firmware.elf', action=['arm-none-eabi-objdump -h -S $SOURCE > $TARGET'])