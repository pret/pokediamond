#!/bin/sh
set -e

find arm9 include -not \( -path arm9/lib -prune \) -not \( -path include/nitro -prune \) \( -name "*.c" -or -name "*.cpp" -or -name "*.h" -or -name "*.hpp" \) -exec clang-format -i --verbose {} +
