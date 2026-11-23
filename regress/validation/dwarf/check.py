#!/usr/bin/env python3
"""Build and validate ELF64 DWARF line/function output on Linux.
Usage: python3 regress/validation/dwarf/check.py /absolute/path/to/uasm
Requires gcc, readelf, GDB (with Python); uses llvm-dwarfdump if available.
Artifacts remain in regress/results/dwarf-live for interactive debugging.
"""
import pathlib, shutil, struct, subprocess, sys
src = pathlib.Path(__file__).resolve().parent
out = src.parents[1] / 'results' / 'dwarf-live'
out.mkdir(parents=True, exist_ok=True)
asm = str(pathlib.Path(sys.argv[1]).resolve())
def run(args, **kw):
    return subprocess.run(args, cwd=out, check=True, text=True, **kw)
# Explicit CodeView 8 is invalid for ELF64, in either argument order.
for options in (['-elf64', '-Zi8'], ['-Zi8', '-elf64']):
    rejected = out/'rejected.o'
    if rejected.exists(): rejected.unlink()
    result = subprocess.run([asm, '-q', *options, '-Fo='+str(rejected), str(src/'dwarf_other.asm')], cwd=out, text=True, capture_output=True)
    assert result.returncode != 0
    assert 'CodeView 8 (-Zi8) with ELF64 output' in result.stdout + result.stderr
    assert not rejected.exists()
for name in ('dwarf_lines', 'dwarf_other'):
    run([asm, '-q', '-elf64', '-Zi', '-I'+str(src), '-Fo='+name+'.o', str(src/(name+'.asm'))])
# Compare code with debug disabled and check real ELF section flags.
def elf_sections(path):
    data = path.read_bytes()
    off = struct.unpack_from('<Q', data, 40)[0]
    stride, count, names = struct.unpack_from('<HHH', data, 58)
    headers = [struct.unpack_from('<IIQQQQIIQQ', data, off+i*stride) for i in range(count)]
    h = headers[names]; strings = data[h[4]:h[4]+h[5]]
    return {strings[h[0]:].split(b'\0',1)[0].decode(): (h[1], h[2], data[h[4]:h[4]+h[5]]) for h in headers}
run([asm, '-q', '-elf64', '-I'+str(src), '-Fo=plain.o', str(src/'dwarf_lines.asm')])
plain = elf_sections(out/'plain.o'); debug = elf_sections(out/'dwarf_lines.o')
assert not any(n.startswith('.debug_') for n in plain)
for name, value in debug.items():
    if name.startswith('.debug_'): assert value[0:2] == (1, 0), (name, value[0:2])
    if value[1] & 4: assert value == plain[name], name
run(['gcc', '-no-pie', '-Wl,-z,noexecstack', 'dwarf_lines.o', 'dwarf_other.o', '-o', 'dwarf-lines'])
run([str(out/'dwarf-lines')])
verifier = next((shutil.which(n) for n in ('llvm-dwarfdump', 'llvm-dwarfdump-23', 'llvm-dwarfdump-18') if shutil.which(n)), None)
if verifier:
    for name in ('dwarf_lines.o', 'dwarf_other.o', 'dwarf-lines'):
        run([verifier, '--verify', name])
with (out/'decoded-lines.txt').open('w') as f:
    run(['readelf', '--debug-dump=decodedline', 'dwarf-lines'], stdout=f)
# The unlinked object must carry address relocations and non-allocated debug data.
sections = run(['readelf', '-SW', 'dwarf_lines.o'], capture_output=True).stdout
for name in ('.debug_info', '.debug_line', '.debug_ranges', '.debug_abbrev'):
    assert name in sections
relocs = run(['readelf', '-rW', 'dwarf_lines.o'], capture_output=True).stdout
assert '.rela.debug_info' in relocs and '.rela.debug_line' in relocs
assert 'R_X86_64_64' in relocs and 'R_X86_64_32' in relocs
checks = r'''
python
import gdb, pathlib, traceback
try:
    def at(file, text):
        sal = gdb.selected_frame().find_sal()
        assert sal.symtab and pathlib.Path(sal.symtab.fullname()).name == file, sal
        lines = pathlib.Path(sal.symtab.fullname()).read_text().splitlines()
        assert lines[sal.line-1].strip() == text, (sal.line, lines[sal.line-1])
    gdb.execute('set pagination off')
    gdb.execute('tbreak AddValues')
    gdb.execute('run')
    at('dwarf_lines.asm', 'mov eax,edi')
    gdb.execute('next')
    at('dwarf_lines.asm', 'add eax,esi')
    assert int(gdb.parse_and_eval('$eax')) == 20
    gdb.execute('next')
    at('dwarf_lines.asm', 'ret')
    assert int(gdb.parse_and_eval('$eax')) == 42
    gdb.execute('tbreak IncludedValue')
    gdb.execute('continue')
    at('dwarf_lines.inc', 'mov eax,7')
    gdb.execute('tbreak ColdValue')
    gdb.execute('continue')
    at('dwarf_lines.asm', 'mov eax,9')
    gdb.execute('tbreak OtherValue')
    gdb.execute('continue')
    at('dwarf_other.asm', 'mov eax,11')
    gdb.execute('continue')
    assert int(gdb.parse_and_eval('$_exitcode')) == 0
    print('DWARF: source stepping, include files, multiple sections/CUs and execution PASS')
except Exception:
    traceback.print_exc()
    gdb.execute('quit 1')
end
'''
(out/'check.gdb').write_text(checks)
run(['gdb', '-q', '-batch', '-x', str(out/'check.gdb'), str(out/'dwarf-lines')])
print('Interactive check: gdb '+str(out/'dwarf-lines'))

run([sys.executable, str(src/'check_variables.py'), asm])

run([sys.executable, str(src/'check_unwind.py'), asm])
