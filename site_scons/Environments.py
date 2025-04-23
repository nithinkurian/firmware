import os
from SCons.Environment import Environment

def get_stm32_env():
	env = Environment(ENV={'PATH': os.environ['PATH']}, tools = ['default', 'textfile'])
	env.VariantDir('build/scons/', '.', duplicate=0)
	env['CC'] = 'arm-none-eabi-gcc'
	env.Append(CFLAGS='-c') #no linking
	env.Append(CFLAGS='-mcpu=cortex-m7') #cortex-m7
	env.Append(CFLAGS='-mthumb') #thumb instruction set
	env.Append(CFLAGS='-mfloat-abi=hard') #use hardware floating point
	env.Append(CFLAGS='-std=gnu11') #gnu 11 standard
	env.Append(CFLAGS='-Wall')
	env.Append(CFLAGS='-O0') #no optimization
	env.Append(CFLAGS='-g3')
	env.Append(CFLAGS='-ggdb')



	env.Append(LINKFLAGS='-mcpu=cortex-m7') #cortex-m7
	env.Append(LINKFLAGS='-mthumb') #thumb instruction set
	env.Append(LINKFLAGS='-mfloat-abi=hard') #use hardware floating point
	return env

def get_x86_64_env():
	env = Environment()
	env.VariantDir('build/scons/', '.', duplicate=0)
	env.Append(CFLAGS='-O0')
	env.Append(CFLAGS='-g3')
	env.Append(CFLAGS='-ggdb')
	return env
