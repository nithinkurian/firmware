#!/bin/bash

PYTHON="python3"
SCONS="tools/scons/scons-local-4.9.1/scons.py"
BUILD="./build"

if [[ "$1" = "clean" ]]; then
$PYTHON $SCONS -Qc
elif [[ "$1" = "run" ]]; then
$BUILD/src/main
elif [[ "$1" = "tree" ]]; then
tree -I tools/
else
$PYTHON $SCONS -Q
fi
