#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

# Configuration with sensible defaults; can be overridden via environment
PYTHON="${PYTHON:-python3}"
SCONS="${SCONS:-tools/scons/scons-local-4.9.1/scons.py}"
ARM_GCC_PATH="${ARM_GCC_PATH:-tools/gcc-arm-none-eabi-10.3-2021.10/bin/}"
ARM_GCC_GDB="${ARM_GCC_GDB:-${ARM_GCC_PATH}arm-none-eabi-gdb}"

arguments=()

command_exists() { command -v "$1" >/dev/null 2>&1; }
die() { echo "ERROR: $*" >&2; exit 1; }

usage() {
	cat <<'EOF'
Usage: build.sh [command] [args...]

Commands:
  clean                 - run scons clean
  tree                  - show workspace tree (excludes tools/reference_project)
  treebuild             - show build tree
  openocd               - run openocd with board config
  load <target_id>      - load flash using arm-none-eabi-gdb
  loadsemi <target_id>  - load semi-hosting flash
  debug <target_id>     - debug firmware (uses gdb for x86 target)
  debugsemi <target_id> - debug semi-hosting firmware
  run <target_id>       - run built ELF on host (x86 targets)
  analyzer              - run logic analyzer appimage
  help                  - show this message

Environment variables:
  PYTHON, SCONS, ARM_GCC_PATH, ARM_GCC_GDB
EOF
}

# Resolve arm-none-eabi-gdb: prefer given path, fall back to PATH
if [[ -n "${ARM_GCC_GDB:-}" && -x "$ARM_GCC_GDB" ]]; then
	: # use as-is
else
	if command_exists arm-none-eabi-gdb; then
		ARM_GCC_GDB="$(command -v arm-none-eabi-gdb)"
	else
		ARM_GCC_GDB=""
	fi
fi

# Runtime flags with defaults
VERBOSE=${VERBOSE:-0}
DRY_RUN=${DRY_RUN:-0}

# Parse options (short and long) using getopt. Supported options:
# -h|--help, -c|--clean, -v|--verbose, -n|--dry-run, -t|--toolchain <path>, -g|--gdb <path>
if command -v getopt >/dev/null 2>&1; then
	PARSED=$(getopt -o hcvnt:g: -l help,clean,verbose,dry-run,toolchain:,gdb: -- "$@") || {
		usage
		exit 2
	}
	eval set -- "$PARSED"
	while true; do
		case "$1" in
			-h|--help)
				usage
				exit 0
				;;
			-c|--clean)
				"$PYTHON" "$SCONS" -Qc
				exit 0
				;;
			-b|--build)
				# Run scons with no extra targets (build default)
				"$PYTHON" "$SCONS" -Q
				exit 0
				;;
			-v|--verbose)
				VERBOSE=1; shift
				;;
			-n|--dry-run)
				DRY_RUN=1; shift
				;;
			-t|--toolchain)
				ARM_GCC_PATH="$2"
				# also update default gdb path when toolchain path changed
				ARM_GCC_GDB="${ARM_GCC_PATH%/}/arm-none-eabi-gdb"
				shift 2
				;;
			-g|--gdb)
				ARM_GCC_GDB="$2"
				shift 2
				;;
			--)
				shift; break
				;;
			*)
				break
				;;
		esac
	done
fi


while [[ $# -gt 0 ]]; do
	case "$1" in
		clean)
			"$PYTHON" "$SCONS" -Qc
			exit 0
			;;
		tree)
			command_exists tree || die "'tree' command not found; install it or run 'ls' instead"
			tree -I tools/ -I reference_project
			exit 0
			;;
		treebuild)
			command_exists tree || die "'tree' command not found; install it or run 'ls' instead"
			tree build -I tools/ -I reference_project -I docs
			exit 0
			;;
		openocd)
			command_exists openocd || die "openocd not found"
			openocd -f board/st_nucleo_h743zi.cfg
			exit 0
			;;
		load)
			shift
			target_id="${1:-}"
			[[ -n "$target_id" ]] || die "load requires a target id"
			[[ -n "$ARM_GCC_GDB" ]] || die "arm-none-eabi-gdb not found; set ARM_GCC_GDB or install gcc-arm-none-eabi"
			"$ARM_GCC_GDB" --command="build/scons/$target_id/flash.gdb"
			exit 0
			;;
		loadsemi)
			shift
			target_id="${1:-}"
			[[ -n "$target_id" ]] || die "loadsemi requires a target id"
			[[ -n "$ARM_GCC_GDB" ]] || die "arm-none-eabi-gdb not found; set ARM_GCC_GDB or install gcc-arm-none-eabi"
			"$ARM_GCC_GDB" --command="build/scons/$target_id/flash_semi.gdb"
			exit 0
			;;
		debug)
			shift
			target_id="${1:-}"
			[[ -n "$target_id" ]] || die "debug requires a target id"
			if [[ "$target_id" = "X8664______PTHRE_001" ]]; then
				command_exists gdb || die "gdb not found"
				gdb -tui "build/scons/$target_id/firmware.elf"
			else
				[[ -n "$ARM_GCC_GDB" ]] || die "arm-none-eabi-gdb not found; set ARM_GCC_GDB or install gcc-arm-none-eabi"
				"$ARM_GCC_GDB" --command="build/scons/$target_id/debug.gdb" -tui "build/scons/$target_id/firmware.elf"
			fi
			exit 0
			;;
		debugsemi)
			shift
			target_id="${1:-}"
			[[ -n "$target_id" ]] || die "debugsemi requires a target id"
			[[ -n "$ARM_GCC_GDB" ]] || die "arm-none-eabi-gdb not found; set ARM_GCC_GDB or install gcc-arm-none-eabi"
			"$ARM_GCC_GDB" --command="build/scons/$target_id/debug_semi.gdb" -tui "build/scons/$target_id/firmware_semi.elf"
			exit 0
			;;
		run)
			shift
			target_id="${1:-}"
			[[ -n "$target_id" ]] || die "run requires a target id"
			elf="build/scons/$target_id/firmware.elf"
			[[ -f "$elf" ]] || die "ELF not found: $elf"
			if [[ ! -x "$elf" ]]; then
				echo "Warning: $elf is not executable; attempting to run anyway"
			fi
			"$elf"
			exit 0
			;;
		analyzer)
			app="tools/logic_analyzer/Logic-2.4.29-linux-x64.AppImage"
			[[ -x "$app" ]] || die "Logic analyzer not found or not executable: $app"
			"$app"
			exit 0
			;;
		-h|--help|help)
			usage
			exit 0
			;;
		*)
			arguments+=("$1")
			shift
			;;
	esac
done

# Default: pass remaining arguments to scons
"$PYTHON" "$SCONS" -Q "${arguments[@]:-}"

