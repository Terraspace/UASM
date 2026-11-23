#!/usr/bin/env python3
"""Check actual linker/loader behaviour, not just successful assembly."""
from pathlib import Path
import subprocess

def run(*args):
    return subprocess.check_output(args, text=True)

output = run('./build/console')
assert 'PASS:' in output, output
print(output, end='')
for name in ['console', 'libuasm_sample.so']:
    file = 'build/' + name
    assert 'DYN (Shared object file)' in run('readelf', '-hW', file) or 'DYN (Position-Independent Executable file)' in run('readelf', '-hW', file)
    dynamic = run('readelf', '-dW', file)
    relocations = run('readelf', '-rW', file)
    assert 'TEXTREL' not in dynamic
    assert 'R_X86_64_COPY' not in relocations
    stack = next(line for line in run('readelf', '-lW', file).splitlines() if 'GNU_STACK' in line)
    assert 'RWE' not in stack, stack
    sections = run('readelf', '-SW', file)
    for section in ['.debug_info', '.debug_line', '.debug_frame']:
        assert section in sections, (file, section)
relocations = run('readelf', '-rW', 'build/console')
assert 'R_X86_64_JUMP_SLOT' in relocations and 'sample_add' in relocations
assert 'R_X86_64_GLOB_DAT' in relocations and 'sample_model' in relocations
assert '$ORIGIN' in run('readelf', '-dW', 'build/console')
assert 'libuasm_sample.so' in run('readelf', '-dW', 'build/console')
print('PASS: PIE/SO, PLT/GOT, $ORIGIN, DWARF sections, non-executable stack; no TEXTREL/COPY')
