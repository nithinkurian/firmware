targets = []
#<XXXXX><XXX><X><X> :<Board><Number><Type><OS>
targets.append('STM32H743N_CUSTR_001')#STM32 H743 Nucleo Normal Custom RTOS
targets.append('STM32H743N_CUSTR_001S')#STM32 H743 Nucleo Semi hosting Custom RTOS
targets.append('X8664______PTHRE_001S')#x86_64 pthread
targets.append('STM32H743N_FREER_001S')#STM32 H743 Nucleo Semi hosting Custom FreeRTOS

for target in targets:
	print(target)
	SConscript('target_'+target+'.py', variant_dir='build/scons/'+target+'/',src_dir='src', duplicate=False)