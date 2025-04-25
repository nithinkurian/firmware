import os
from Environments import *

env_list = []
env_normal = get_stm32_env()
env_normal.Append(SEMI_HOSTING=False)
env_list.append(env_normal)

env_semi = get_stm32_env()
env_semi.Append(SEMI_HOSTING=True)
env_list.append(env_semi)

for env in env_list:
	env.Append(OS_NAME='custom_rtos')
	env.Append(BOARD_NAME='stm32h743_nucleo')
	env.Append(TARGET_NAME='STM32H743N_CUSTR_001')
	env.Append(LINKFLAGS='-T src/bsp/'+'${BOARD_NAME}'+'/stm32_ls.ld')
	env.Append(CPPPATH=['include','bsp/include', 'os/include'])
	if env['SEMI_HOSTING'] == True:
		env.Append(LINKFLAGS='--specs=rdimon.specs')
		env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${TARGET_NAME}'+'/firmware_semi.map')
		source = []
		firmware = env.Program('firmware_semi.elf',source,
			LIBS=['common','bsp','os'],
			LIBPATH=['#build/scons/libs/common/'+'${BOARD_NAME}',
					'#build/scons/libs/bsp/'+'${BOARD_NAME}',
					'#build/scons/libs/os/'+'${OS_NAME}'])
		
		env.SideEffect('firmware_semi.map', firmware)

		env.Command(target='firmware_semi.list',source='firmware_semi.elf', action=['arm-none-eabi-objdump -h -S $SOURCE > $TARGET'])

		conf_dict = {'##Firmware##': '''build/scons/${TARGET_NAME}/firmware_semi.elf
monitor arm semihosting enable'''}
		env.Substfile('flash_semi.gdb','flash_template.gdb', SUBST_DICT = conf_dict)

		conf_dict = {'##Firmware##': '''build/scons/${TARGET_NAME}/firmware_semi.elf
monitor arm semihosting enable'''}
		env_semi.Substfile('debug_semi.gdb','debug_template.gdb', SUBST_DICT = conf_dict)
	else:

		env.Append(LINKFLAGS='--specs=nano.specs')
		env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${TARGET_NAME}'+'/firmware.map')
		source = 'bsp/'+'${BOARD_NAME}'+'/syscalls.c'
		firmware = env.Program('firmware.elf',source,	
			LIBS=['common','bsp','os'],
			LIBPATH=['#build/scons/libs/common/'+'${BOARD_NAME}',
					'#build/scons/libs/bsp/'+'${BOARD_NAME}',
					'#build/scons/libs/os/'+'${OS_NAME}'])
		
		env.SideEffect('firmware.map', firmware)

		env.Command(target='firmware.list',source='firmware.elf', action=['arm-none-eabi-objdump -h -S $SOURCE > $TARGET'])

		conf_dict = {'##Firmware##': '''build/scons/${TARGET_NAME}/firmware.elf'''}
		env.Substfile('flash.gdb', 'flash_template.gdb',SUBST_DICT = conf_dict)

		conf_dict = {'##Firmware##': '''build/scons/${TARGET_NAME}/firmware.elf'''}
		env_semi.Substfile('debug.gdb','debug_template.gdb', SUBST_DICT = conf_dict)

	env.Depends(firmware, '#src/bsp/'+'${BOARD_NAME}'+'/stm32_ls.ld')
	env.Depends(firmware, '#build/scons/libs/common/'+'${BOARD_NAME}'+'/libcommon.a')
	env.Depends(firmware, '#build/scons/libs/bsp/'+'${BOARD_NAME}'+'/libbsp.a')
	env.Depends(firmware, '#build/scons/libs/os/'+'${OS_NAME}'+'/libos.a')



