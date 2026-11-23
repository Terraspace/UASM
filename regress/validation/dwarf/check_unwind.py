#!/usr/bin/env python3
"""Check CFI at every executed instruction, including both return paths."""
import pathlib, subprocess, sys, shutil
here=pathlib.Path(__file__).resolve().parent
out=here.parents[1]/'results/dwarf-live';out.mkdir(parents=True,exist_ok=True)
asm=str(pathlib.Path(sys.argv[1]).resolve())
def run(args,**kw):return subprocess.run(args,cwd=out,check=True,text=True,**kw)
run([asm,'-q','-elf64','-Zi','-Fo=unwind.o',str(here/'dwarf_unwind.asm')])
run(['gcc','-no-pie','-Wl,-z,noexecstack','unwind.o','-o','dwarf-unwind'])
run([str(out/'dwarf-unwind')])
frames=run(['readelf','--debug-dump=frames','unwind.o'],capture_output=True).stdout
assert '.debug_frame' in frames and frames.count(' FDE ')==5
assert 'DW_CFA_remember_state' in frames and 'DW_CFA_restore_state' in frames
(out/'unwind-frames.txt').write_text(frames)
verifier=next((shutil.which(n) for n in ['llvm-dwarfdump-23','llvm-dwarfdump','llvm-dwarfdump-18'] if shutil.which(n)),None)
if verifier:
 for f in ['unwind.o','dwarf-unwind']:run([verifier,'--verify',f])
# GDB must use CFI: NoFrame saves then deliberately destroys the frame pointer.
script=r'''
set pagination off
set confirm off
python
import gdb,traceback
try:
 gdb.execute('break *main')
 gdb.execute('run')
 callers=[]; checks=0; visited=set();returns=0
 def vector_low(frame):
  # GDB maps DWARF 23 to YMM6 on AVX targets. Its XMM alias can remain stale
  # in older frames. Only the 128 bits actually saved by USES XMM6 are valid.
  try: v=frame.read_register('ymm6')['v4_int64']
  except gdb.error: v=frame.read_register('xmm6')['v2_int64']
  return (int(v[0]),int(v[1]))
 regs=['rsp','rbp','rbx','r12','r13','r14','r15']
 while True:
  f=gdb.newest_frame();name=f.name();pc=int(f.pc());visited.add(name)
  older=f
  for caller in reversed(callers):
   older=older.older()
   assert older is not None,(name,hex(pc),'missing caller')
   assert older.name()==caller['name'],(name,hex(pc),older.name(),caller)
   assert int(older.pc())==caller['pc'],(name,hex(pc),'return pc',hex(older.pc()),caller)
   for reg in regs:
    got=int(older.read_register(reg));want=caller[reg]
    assert got==want,(name,hex(pc),caller['name'],reg,hex(got),hex(want))
   if name=='NoFrame' and older==f.older():
    assert vector_low(older)==caller['xmm6'],(hex(pc),'saved vector low bits',vector_low(older),caller['xmm6'])
   checks+=1
  ins=f.architecture().disassemble(pc,count=1)[0]
  text=ins['asm'].strip()
  if text.startswith('ret'):
   returns+=1
   if not callers:break
   callers.pop()
  elif text.startswith('call'):
   saved={reg:int(f.read_register(reg)) for reg in regs}
   saved.update(name=name,pc=pc+ins['length'],xmm6=vector_low(f));callers.append(saved)
  gdb.execute('stepi',to_string=True)
  assert checks<10000,'nonterminating fixture'
 assert visited=={'main','Aliased','Homed','NoFrame','RedLeaf'},visited
 assert returns==6,returns
 gdb.execute('continue',to_string=True)
 assert int(gdb.parse_and_eval('$_exitcode'))==0
 print('DWARF unwind: %d caller-frame checks PASS at every executed instruction; both epilogues, SYSVHOME 0/1, red zone, frameless and stack arguments PASS'%checks)
except Exception:
 traceback.print_exc();gdb.execute('quit 1')
end
'''
(out/'unwind.gdb').write_text(script)
for extra in [[], ['-DPRESERVEFLAGS=1'], ['-Zd']]:
 flags=['-Zd'] if extra==['-Zd'] else ['-Zi']+extra
 run([asm,'-q','-elf64',*flags,'-Fo=unwind.o',str(here/'dwarf_unwind.asm')])
 run(['gcc','-no-pie','-Wl,-z,noexecstack','unwind.o','-o','dwarf-unwind'])
 print('Unwind variant: '+str(flags),flush=True)
 run(['gdb','-q','-batch','-x',str(out/'unwind.gdb'),str(out/'dwarf-unwind')])
