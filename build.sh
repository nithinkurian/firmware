#!/bin/bash

PYTHON="python3"
SCONS="tools/scons/scons-local-4.9.1/scons.py"
BUILD="./build"

if [[ "$1" = "clean" ]]; then
$PYTHON $SCONS -Qc
elif [[ "$1" = "tree" ]]; then
tree -I tools/
elif [[ "$1" = "openocd" ]]; then
openocd -f board/st_nucleo_h743zi.cfg
elif [[ "$1" = "load" ]]; then
arm-none-eabi-gdb --command=flash_scons.gdb
else
$PYTHON $SCONS -Q
fi