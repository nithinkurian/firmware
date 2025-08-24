#!/bin/bash

PYTHON="python3"
SCONS="tools/scons/scons-local-4.9.1/scons.py"
BUILD="./build"

arguments=()

for argument in $@
do
	echo "$argument"
	if [[ "$argument" = "clean" ]]; then
		$PYTHON $SCONS -Qc
		exit 0
	elif [[ "$1" = "tree" ]]; then
		tree -I tools/ -I reference_project
		exit 0
	elif [[ "$1" = "treebuild" ]]; then
		tree build -I tools/ -I reference_project -I docs
		exit 0
	elif [[ "$1" = "openocd" ]]; then
		openocd -f board/st_nucleo_h743zi.cfg
		exit 0
	elif [[ "$1" = "load" ]]; then
		arm-none-eabi-gdb --command=build/scons/$2/flash.gdb
		exit 0
	elif [[ "$1" = "loadsemi" ]]; then
		arm-none-eabi-gdb --command=build/scons/$2/flash_semi.gdb
		exit 0
	elif [[ "$1" = "debug" ]]; then
		if [[ "$2" = "X8664______PTHRE_001" ]]; then
			gdb -tui build/scons/$2/firmware.elf
		else
			arm-none-eabi-gdb --command=build/scons/$2/debug.gdb -tui build/scons/$2/firmware.elf
		fi
		exit 0
	elif [[ "$1" = "debugsemi" ]]; then
		arm-none-eabi-gdb --command=build/scons/$2/debug_semi.gdb -tui build/scons/$2/firmware_semi.elf
		exit 0
	elif [[ "$1" = "run" ]]; then
		./build/scons/$2/firmware.elf 
		exit 0
	elif [[ "$1" = "analyzer" ]]; then
		tools/logic_analyzer/Logic-2.4.29-linux-x64.AppImage
		exit 0
	else
		arguments+=($argument)
	fi
done


$PYTHON $SCONS -Q ${arguments[@]}

