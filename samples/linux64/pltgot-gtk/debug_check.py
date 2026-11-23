# Run inside GDB: gdb -q -batch -ex 'source debug_check.py' --args build/console
import gdb
import os
from pathlib import Path

gui = bool(os.getenv('UASM_DEBUG_GUI'))
gdb.execute('set pagination off')
gdb.execute('set print thread-events off')
gdb.execute('set debuginfod enabled off')
gdb.execute('set confirm off')
gdb.execute('set breakpoint pending on')
gdb.execute('start')
lines = Path('samplelib.asm').read_text().splitlines()
register_line = next(i for i, line in enumerate(lines, 1) if 'DEBUG_REGISTER:' in line)
stop_line = next(i for i, line in enumerate(lines, 1) if 'DEBUG_STOP:' in line)
gdb.Breakpoint('samplelib.asm:' + str(register_line), temporary=True)
gdb.Breakpoint('samplelib.asm:' + str(stop_line), temporary=True)
gdb.execute('continue')
assert gdb.selected_frame().name() == 'sample_adjust'
assert float(gdb.parse_and_eval('value')) == 1.25
gdb.execute('continue')
assert gdb.selected_frame().name() == 'sample_add'
assert float(gdb.parse_and_eval('amount')) == 1.25
assert float(gdb.parse_and_eval('before')) == 0.0
assert float(gdb.parse_and_eval('after')) == 1.25
assert int(gdb.parse_and_eval('state->count')) == 1
assert float(gdb.parse_and_eval('state->total')) == 1.25
assert int(gdb.parse_and_eval('sample_events')) == 1
sal = gdb.selected_frame().find_sal()
assert sal.symtab and sal.line == stop_line
frames = []
frame = gdb.newest_frame()
while frame:
    frames.append(frame.name())
    frame = frame.older()
assert frames[1] == ('on_clicked' if gui else 'apply_value'), frames
assert 'main' in frames, frames
gdb.execute('bt')
gdb.execute('info args')
gdb.execute('info locals')
if not gui:
    caller = gdb.newest_frame().older()
    caller.select()
    assert float(gdb.parse_and_eval('requested')) == 1.25
    assert float(gdb.parse_and_eval('amount')) == 1.25
    caller.older().select()
    assert int(gdb.parse_and_eval('argc')) == 1
    assert int(gdb.parse_and_eval('originalArgc')) == 1
    gdb.newest_frame().select()
gdb.execute('next')
assert gdb.selected_frame().find_sal().symtab
print('PASS: source breakpoint/step, register and homed float parameters, struct pointer, locals, global and cross-SO backtrace')
gdb.execute('continue')
assert int(gdb.parse_and_eval('$_exitcode')) == 0
print('PASS: debugger inferior exited cleanly')
