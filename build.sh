#!/bin/bash

PYTHON="python3"
SCONS="tools/scons/scons-local-4.9.1/scons.py"
BUILD="./build"

if [[ "$1" = "clean" ]]; then
$PYTHON $SCONS -Qc
elif [[ "$1" = "tree" ]]; then
tree -I tools/ -I reference_project
elif [[ "$1" = "treebuild" ]]; then
tree build -I tools/ -I reference_project -I docs
elif [[ "$1" = "openocd" ]]; then
openocd -f board/st_nucleo_h743zi.cfg
elif [[ "$1" = "load" ]]; then
arm-none-eabi-gdb --command=flash_scons.gdb
elif [[ "$1" = "loadsemi" ]]; then
arm-none-eabi-gdb --command=flash_scons_semi.gdb
elif [[ "$1" = "semihosting" ]]; then
#Semihost enabled firmware will run only when semihosting is enabled from gdb client
#semi hosting prints will appear in gdb server
arm-none-eabi-gdb --command=semi_hosting_enable.gdb
elif [[ "$1" = "run" ]]; then
./build/scons/x86_64/firmware_x86.elf 
else
$PYTHON $SCONS -Q
fi
