#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Determine repository root (REPO_ROOT): prefer git, otherwise search upward for SConstruct or .git
if command -v git >/dev/null 2>&1; then
    REPO_ROOT=$(git -C "$SCRIPT_DIR" rev-parse --show-toplevel 2>/dev/null || true)
else
    REPO_ROOT=""
fi
if [[ -z "${REPO_ROOT:-}" ]]; then
    cur="$SCRIPT_DIR"
    while [[ "$cur" != "/" && -n "$cur" ]]; do
        if [[ -f "$cur/SConstruct" || -d "$cur/.git" ]]; then
            REPO_ROOT="$cur"
            break
        fi
        cur="$(dirname "$cur")"
    done
fi
# Fallback: parent of script (closest reasonable default)
if [[ -z "${REPO_ROOT:-}" ]]; then
    REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
fi
PYTHON="${PYTHON:-python3}"
SCONS="${SCONS:-tools/scons/scons-local-4.9.1/scons.py}"
ARM_GCC_PATH="${ARM_GCC_PATH:-tools/gcc-arm-none-eabi-10.3-2021.10/bin/}"
ARM_GCC_GDB="${ARM_GCC_GDB:-${ARM_GCC_PATH}arm-none-eabi-gdb}"

command_exists() { command -v "$1" >/dev/null 2>&1; }

die() { echo "ERROR: $*" >&2; exit 1; }

usage() {
    cat <<EOF
Usage: $(basename "$0") <action> [args]

Actions:
  openocd                - run openocd with board/st_nucleo_h743zi.cfg
  load <build_id>        - run arm-none-eabi-gdb with flash.gdb
  loadsemi <build_id>    - run arm-none-eabi-gdb with flash_semi.gdb
  debug <build_id>       - debug firmware (arm gdb or host gdb for x86)
  debugsemi <build_id>   - debug semi-hosting firmware
  run <build_id>         - run host ELF
  analyzer               - run logic analyzer AppImage
EOF
}

if [[ $# -lt 1 ]]; then
    usage
    exit 0
fi

action="$1"; shift || true
case "$action" in
    openocd)
        command_exists openocd || die "openocd not found"
    openocd -f "${REPO_ROOT}/board/st_nucleo_h743zi.cfg"
        ;;
    load)
        build_id="${1:-}"
        [[ -n "$build_id" ]] || die "load requires a build id"
        command_exists "${ARM_GCC_GDB##*/}" || die "arm-none-eabi-gdb not found"
    "${ARM_GCC_GDB}" --command="${SCRIPT_DIR}/${build_id}/flash.gdb"
        ;;
    loadsemi)
        build_id="${1:-}"
        [[ -n "$build_id" ]] || die "loadsemi requires a build id"
        command_exists "${ARM_GCC_GDB##*/}" || die "arm-none-eabi-gdb not found"
    "${ARM_GCC_GDB}" --command="${SCRIPT_DIR}/${build_id}/flash_semi.gdb"
        ;;
    debug)
        build_id="${1:-}"
        [[ -n "$build_id" ]] || die "debug requires a build id"
        if [[ "$build_id" == "X8664______PTHRE_001" ]]; then
            command_exists gdb || die "gdb not found"
            gdb -tui "${SCRIPT_DIR}/${build_id}/firmware.elf"
        else
            command_exists "${ARM_GCC_GDB##*/}" || die "arm-none-eabi-gdb not found"
            "${ARM_GCC_GDB}" --command="${SCRIPT_DIR}/${build_id}/debug.gdb" -tui "${SCRIPT_DIR}/${build_id}/firmware.elf"
        fi
        ;;
    debugsemi)
        build_id="${1:-}"
        [[ -n "$build_id" ]] || die "debugsemi requires a build id"
        command_exists "${ARM_GCC_GDB##*/}" || die "arm-none-eabi-gdb not found"
    "${ARM_GCC_GDB}" --command="${SCRIPT_DIR}/${build_id}/debug_semi.gdb" -tui "${SCRIPT_DIR}/${build_id}/firmware_semi.elf"
        ;;
    run)
        build_id="${1:-}"
        [[ -n "$build_id" ]] || die "run requires a build id"
    elf="${SCRIPT_DIR}/${build_id}/firmware.elf"
        [[ -f "$elf" ]] || die "ELF not found: $elf"
        if [[ ! -x "$elf" ]]; then
            echo "Warning: $elf is not executable; attempting to run anyway"
        fi
        "$elf"
        ;;
    analyzer)
    app="${REPO_ROOT}/tools/logic_analyzer/Logic-2.4.29-linux-x64.AppImage"
        [[ -x "$app" ]] || die "Logic analyzer not found or not executable: $app"
        "$app"
        ;;
    -h|--help|help)
        usage
        ;;
    *)
        echo "Unknown action: $action" >&2
        usage
        exit 2
        ;;
esac
