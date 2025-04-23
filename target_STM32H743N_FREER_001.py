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
	env.Append(OS_NAME='freertos')
	env.Append(BOARD_NAME='stm32h743_nucleo')
	env.Append(TARGET_NAME='STM32H743N_FREER_001')
	env.Append(LINKFLAGS='-T src/bsp/'+'${BOARD_NAME}'+'/stm32_ls.ld')
	env.Append(CPPPATH=['include','bsp/include', 'os/include', 'os/${OS_NAME}/include', 'os/${OS_NAME}/portable/GCC/ARM_CM7/r0p1', 'os/${OS_NAME}'])
	if env['SEMI_HOSTING'] == True:
		env.Append(LINKFLAGS='--specs=rdimon.specs')
		env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${TARGET_NAME}'+'/firmware_semi.map')
	else:
		env.Append(LINKFLAGS='--specs=nano.specs')
		env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+'${TARGET_NAME}'+'/firmware.map')

	source = SConscript('#src/common/common_source.py', exports='env')
	source.append(SConscript('bsp/'+env["BOARD_NAME"]+'/'+env["BOARD_NAME"]+'.py', exports='env'))
	source.append(SConscript('os/'+env["OS_NAME"]+'/'+env["OS_NAME"]+'.py', exports='env'))


	if env['SEMI_HOSTING'] == True:
		firmware = env.Program('firmware_semi.elf',source)
		env.SideEffect('firmware_semi.map', firmware)

		env.Command(target='firmware_semi.list',source='firmware_semi.elf', action=['arm-none-eabi-objdump -h -S $SOURCE > $TARGET'])

		conf_dict = {'##Firmware##': '''build/scons/${TARGET_NAME}/firmware_semi.elf
monitor arm semihosting enable'''}
		env.Substfile('flash_semi.gdb','flash_template.gdb', SUBST_DICT = conf_dict)
	else:
		firmware = env.Program('firmware.elf',source)
		env.SideEffect('firmware.map', firmware)

		env.Command(target='firmware.list',source='firmware.elf', action=['arm-none-eabi-objdump -h -S $SOURCE > $TARGET'])

		conf_dict = {'##Firmware##': '''build/scons/${TARGET_NAME}/firmware.elf'''}
		env.Substfile('flash.gdb', 'flash_template.gdb',SUBST_DICT = conf_dict)
