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

hal_source_files = []
hal_source_files.append('bsp/'+target+'/hal_gpio.c')
hal_source_files.append('bsp/'+target+'/hal_cpu.c')
env.Program('firmware_x86.elf',source_files + hal_source_files)