#!/bin/sh
set -eu
# Run from any directory; optional assembler argument is relative to the caller.
if [ "$#" -gt 0 ]; then assembler=$(realpath "$1"); else assembler=; fi
cd "$(dirname "$0")"
if [ -z "$assembler" ]; then assembler=$(realpath ../../GccUnixR/uasm); fi
mkdir -p results
for name in siblings_noargs siblings_args float_siblings reentrant stack_arguments; do
    "$assembler" -q -elf64 -Zi -Fo"results/$name.o" "../src/nested_callself/$name.asm"
    "${CC:-gcc}" -no-pie -Wl,-z,noexecstack -o "results/$name" "results/$name.o"
    "./results/$name"
    printf 'PASS %s\n' "$name"
done
