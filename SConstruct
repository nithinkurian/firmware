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

# Copy helper run script into each variant_dir so CI and users can call it from build tree
import shutil
import os
# Install a single run.sh into build/scons/run.sh using SCons so it's tracked/cleaned
import SCons.Script
env = DefaultEnvironment() if 'DefaultEnvironment' in globals() else Environment()
run_src = File('run.sh')
run_dst_dir = Dir('build/scons')
# install will place run.sh into build/scons/run.sh
installed = env.Install(run_dst_dir, run_src)
# Ensure installed file is executable (post action so it doesn't create a self-source rule)
try:
	env.AddPostAction(installed, SCons.Script.Chmod('$TARGET', 0o755))
except Exception:
	# Fallback: attempt to create a command that runs after install
	env.Command(None, installed, SCons.Script.Chmod('$TARGET', 0o755))
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



