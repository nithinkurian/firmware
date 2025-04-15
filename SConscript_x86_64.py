import os
env = Environment()
env.VariantDir('build/scons/', '.', duplicate=0)
target = 'x86_64'
env.Append(CFLAGS='-O0')
env.Append(CFLAGS='-g3')
env.Append(CFLAGS='-ggdb')


env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+target+'/firmware.map')

env.Append(CPPPATH=['include','bsp/include'])

source_files = []
source_files.append('main.c')
source_files.append('led.c')
source_files.append('delay.c')

hal_source_files = []
hal_source_files.append('bsp/'+target+'/hal_gpio.c')
hal_source_files.append('bsp/'+target+'/hal_cpu.c')
hal_source_files.append('bsp/'+target+'/semihosting.c')
hal_source_files.append('bsp/'+target+'/hal_processor_faults.c')
hal_source_files.append('bsp/'+target+'/hal_processor_faults_test.c')

firmware = env.Program('firmware.elf',source_files + hal_source_files)
env.SideEffect('firmware.map', firmware)