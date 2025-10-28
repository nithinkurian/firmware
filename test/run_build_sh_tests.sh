#!/usr/bin/env bash
set -euo pipefail

echo "Running local checks for build.sh"

SCRIPT="$(dirname "$0")/../build.sh"

echo "1) Shell syntax check"
bash -n "$SCRIPT"
echo "  OK"

if command -v shellcheck >/dev/null 2>&1; then
    echo "2) shellcheck lint"
    shellcheck "$SCRIPT" || (echo "shellcheck failed"; exit 2)
    echo "  OK"
else
    echo "2) shellcheck not installed; skipping shellcheck step"
fi

echo "All checks passed"
