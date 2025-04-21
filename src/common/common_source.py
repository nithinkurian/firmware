Import('env')
common_source = []
common_source.append('common/main.c')
common_source.append('common/led.c')

Return('common_source') 