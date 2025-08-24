import os
from Environments import *

env = get_x86_64_env()

env.Append(OS_NAME='x86_pthread')
env.Append(BOARD_NAME='x86_64')
env.Append(TARGET_NAME='X8664______PTHRE_001')
env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${TARGET_NAME}'+'/firmware.map')

firmware = env.Program('firmware.elf',[],	
	LIBS=['common','bsp','os'],
	LIBPATH=['#build/scons/libs/common/'+'${BOARD_NAME}',
			'#build/scons/libs/bsp/'+'${BOARD_NAME}',
			'#build/scons/libs/os/'+'${OS_NAME}'])
env.Depends(firmware, '#build/scons/libs/common/'+'${BOARD_NAME}'+'/libcommon.a')
env.Depends(firmware, '#build/scons/libs/bsp/'+'${BOARD_NAME}'+'/libbsp.a')
env.Depends(firmware, '#build/scons/libs/os/'+'${OS_NAME}'+'/libos.a')
env.SideEffect('firmware.map', firmware)