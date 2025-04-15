import os
env = Environment(ENV={'PATH': os.environ['PATH']})
#env.Execute(Mkdir('build/scons/'))
env.VariantDir('build/scons/', '.', duplicate=0)
target = 'stm32h743_nucleo'
env['CC'] = 'arm-none-eabi-gcc'
env.Append(CFLAGS='-c')
env.Append(CFLAGS='-mcpu=cortex-m7')
env.Append(CFLAGS='-mthumb')
env.Append(CFLAGS='-mfloat-abi=soft')
env.Append(CFLAGS='-std=gnu11')
env.Append(CFLAGS='-Wall')
env.Append(CFLAGS='-O0')
env.Append(CFLAGS='-g3')
env.Append(CFLAGS='-ggdb')

env.Append(LINKFLAGS='-mcpu=cortex-m7')
env.Append(LINKFLAGS='-mthumb')
env.Append(LINKFLAGS='-mfloat-abi=soft')
env.Append(LINKFLAGS='--specs=rdimon.specs')
env.Append(LINKFLAGS='-T src/bsp/'+target+'/stm32_ls.ld')
env.Append(LINKFLAGS='-Wl,-Map=build/scons/'+target+'/firmware.map')

env.Append(CPPPATH=['include','bsp/include'])

source_files = []
source_files.append('main.c')
source_files.append('led.c')
source_files.append('delay.c')

hal_source_files = []
hal_source_files.append('bsp/'+target+'/stm32_startup.c')
hal_source_files.append('bsp/'+target+'/hal_gpio.c')
hal_source_files.append('bsp/'+target+'/hal_cpu.c')

env.Program('firmware_semi.elf',source_files + hal_source_files)