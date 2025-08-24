import sys

fw_targets = []
#<XXXXX><XXX><X><X> :<Board><Number><Type><OS>
fw_targets.append('STM32H743N_CUSTR_001')#STM32 H743 Nucleo  Custom RTOS
fw_targets.append('STM32H743N_FREER_001')#STM32 H743 Nucleo  FreeRTOS
fw_targets.append('X8664______PTHRE_001')#x86_64 pthread


for target in fw_targets:
	Alias(target, 'build/scons/'+target+'/')

for target in fw_targets:
	print(target)
	SConscript('target_'+target+'.py', 
		variant_dir='build/scons/'+target+'/',
		src_dir='src', duplicate=False)

Alias('libs', 'build/scons/libs/')

libs = [
	{
	"src_dir":"src/common",
	"lib":"common",
	"lib_type":"x86_64"
	},	
	{
	"src_dir":"src/common",
	"lib":"common",
	"lib_type":"stm32h743_nucleo"
	},	
	{
	"src_dir":"src/bsp/x86_64",
	"lib":"bsp",
	"lib_type":"x86_64"
	},	
	{
	"src_dir":"src/bsp/stm32h743_nucleo",
	"lib":"bsp",
	"lib_type":"stm32h743_nucleo"
	},	
	{
	"src_dir":"src/os/x86_pthread",
	"lib":"os",
	"lib_type":"x86_pthread"
	},
	{
	"src_dir":"src/os/freertos",
	"lib":"os",
	"lib_type":"freertos"
	},	
	{
	"src_dir":"src/os/custom_rtos",
	"lib":"os",
	"lib_type":"custom_rtos"
	}
]

for lib in libs:
	SConscript(lib['src_dir']+'/lib_'+lib['lib']+'_'+lib['lib_type']+'.py', 
		variant_dir='build/scons/libs/'+lib['lib']+'/'+lib['lib_type'],
		src_dir=lib['src_dir'], duplicate=False)



