Import('env')
common_source = []
common_source.append('main.c')
common_source.append('led.c')
common_source.append('delay.c')

common_source.append('bsp/'+'${BOARD}'+'/hal_gpio.c')
common_source.append('bsp/'+'${BOARD}'+'/hal_cpu.c')
common_source.append('bsp/'+'${BOARD}'+'/hal_processor_faults.c')
common_source.append('bsp/'+'${BOARD}'+'/hal_processor_faults_test.c')

Return('common_source') 