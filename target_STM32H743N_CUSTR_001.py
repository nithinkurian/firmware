import os
from Environments import *

env = get_stm32_env()

env.Append(OS_NAME='custom_rtos')
env.Append(BOARD_NAME='stm32h743_nucleo')
env.Append(TARGET_NAME='STM32H743N_CUSTR_001')
env.Append(SEMI_HOSTING=False)
env.Append(LINKFLAGS='--specs=nano.specs')
env.Append(LINKFLAGS='-T src/bsp/'+'${BOARD_NAME}'+'/stm32_ls.ld')
env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${TARGET_NAME}'+'/firmware.map')
env.Append(CPPPATH=['include','bsp/include', 'os/include'])

source = SConscript('#src/common/common_source.py', exports='env')
source.append(SConscript('bsp/'+env["BOARD_NAME"]+'/'+env["BOARD_NAME"]+'.py', exports='env'))
source.append(SConscript('os/'+env["OS_NAME"]+'/'+env["OS_NAME"]+'.py', exports='env'))

firmware = env.Program('firmware.elf',source)
env.SideEffect('firmware.map', firmware)

env.Command(target='firmware.list',source='firmware.elf', action=['arm-none-eabi-objdump -h -S $SOURCE > $TARGET'])