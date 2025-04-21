Import('env')
source = []

source.append('bsp/'+'${BOARD_NAME}'+'/hal_gpio.c')
source.append('bsp/'+'${BOARD_NAME}'+'/hal_cpu.c')
source.append('bsp/'+'${BOARD_NAME}'+'/hal_processor_faults.c')
source.append('bsp/'+'${BOARD_NAME}'+'/hal_processor_faults_test.c')
source.append('bsp/'+'${BOARD_NAME}'+'/stm32_startup.c')
if env['TARGET_NAME'] == 'STH7N001N':
	source.append('bsp/'+'${BOARD_NAME}'+'/syscalls.c')

Return('source') 