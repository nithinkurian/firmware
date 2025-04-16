targets = []
#<XXXXX><XXX><X> :<Board><Number><Type>
targets.append('STH7N001N')#STM32 H743 Nucleo Normal
targets.append('STH7N001S')#STM32 H743 Nucleo Semi hosting
targets.append('X8664001N')#x86_64
for target in targets:
	print(target)
	SConscript('target_'+target+'.py', variant_dir='build/scons/'+target+'/',src_dir='src', duplicate=False)