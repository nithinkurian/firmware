import sys

all_targets = []
#<XXXXX><XXX><X><X> :<Board><Number><Type><OS>
all_targets.append('STM32H743N_CUSTR_001')#STM32 H743 Nucleo  Custom RTOS
all_targets.append('STM32H743N_FREER_001')#STM32 H743 Nucleo  FreeRTOS
all_targets.append('X8664______PTHRE_001')#x86_64 pthread

for target in all_targets:
	Alias(target, 'build/scons/'+target+'/')


for target in all_targets:
	print(target)
	SConscript('target_'+target+'.py', variant_dir='build/scons/'+target+'/',src_dir='src', duplicate=False)