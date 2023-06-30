#!/usr/bin/env bash

OUT_FILE=ctx.c

GCC=gcc
FLAGS="-E -P -dD -undef"
INCLUDES="-Iinclude -Iinclude/constants -Iinclude/nitro -Iinclude-mw -Ifiles -Iarm9/lib/NitroSDK/include -Iarm9/lib/MSL_C/include -Iarm9/lib/libnns/include -Iarm9/overlays/21/include -Iarm9/overlays/52/include -Iarm9/overlays/59/include -include global.h"
DEFINES="-DDIAMOND"


generate-ctx () {
    # Remove any line containing a predefined macro. If not removed, mwccarm
    # generates compiler warnings.
    grep "^#include " "$1" | $GCC $FLAGS $INCLUDES $DEFINES  -x c - | sed '/__STDC__\|__STDC_VERSION__\|__STDC_VERSION__\|__STDC_HOSTED__/d' > $OUT_FILE
}

usage () {
    echo "Generate a context file for decomp.me."
    echo "Usage: $0 [-h] [FILEPATH]"
    echo ""
    echo "Arguments:"
    echo "  FILEPATH      Source file used to generate ctx.c"
    echo ""
    echo "Options:"
    echo "  -h            Show this message and exit"
}

while [[ $# -gt 0 ]]; do
  key="$1"
  case $key in
  -h)
    usage
    exit 0
    ;;
  *)
    generate-ctx "$1"
    exit 0
    ;;
  esac
done