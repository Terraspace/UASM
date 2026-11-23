#!/usr/bin/env python3
"""Live DWARF type/location and System V homing checks; called by check.py."""
import pathlib, shutil, struct, subprocess, sys
here=pathlib.Path(__file__).resolve().parent
root=here.parents[2]
out=root/'regress/results/dwarf-live';out.mkdir(parents=True,exist_ok=True)
asm=str(pathlib.Path(sys.argv[1]).resolve())
source=root/'regress/src/systemv/sysvhome.asm'
def run(args, **kw): return subprocess.run(args,cwd=out,check=True,text=True,**kw)
run([asm,'-q','-elf64','-Zi','-Fo=variables.o',str(source)])
run(['gcc','-no-pie','-Wl,-z,noexecstack','variables.o','-o','dwarf-variables'])
run([str(out/'dwarf-variables')])
verifier=next((shutil.which(n) for n in ['llvm-dwarfdump','llvm-dwarfdump-23','llvm-dwarfdump-18'] if shutil.which(n)),None)
if verifier:
 for f in ['variables.o','dwarf-variables']:run([verifier,'--verify',f])
# Debug metadata must not change generated machine code.
run([asm,'-q','-elf64','-Fo=variables-nodebug.o',str(source)])
for source_obj,output in [('variables.o','debug.text'),('variables-nodebug.o','plain.text')]:
 run(['objcopy','-O','binary','--only-section=.text',source_obj,output])
assert (out/'debug.text').read_bytes()==(out/'plain.text').read_bytes()
# Direct-register-only procedures must have identical machine code in both modes.
data=(out/'variables.o').read_bytes();off=struct.unpack_from('<Q',data,40)[0]
stride,count,names=struct.unpack_from('<HHH',data,58)
sections=[struct.unpack_from('<IIQQQQIIQQ',data,off+i*stride) for i in range(count)]
functions={}
for section in sections:
 if section[1]!=2:continue
 strings=sections[section[6]];strings=data[strings[4]:strings[4]+strings[5]]
 for pos in range(section[4],section[4]+section[5],section[9]):
  name,info,other,index,value,size=struct.unpack_from('<IBBHQQ',data,pos)
  name=strings[name:].split(b'\0',1)[0].decode()
  if name in ['Unused0','Unused1']:
   code=sections[index];functions[name]=data[code[4]+value:code[4]+value+9]
assert functions['Unused0']==functions['Unused1']==bytes.fromhex('55 48 8b ec 48 8b c7 5d c3')
script=r'''
python
import gdb,traceback
checks=0
try:
 def eq(expr,want):
  global checks
  got=gdb.parse_and_eval(expr)
  assert not got.is_optimized_out,expr
  got=float(got) if isinstance(want,float) else (int(str(got),0) if got.type.sizeof>8 else int(got))
  assert got==want,(expr,got,want)
  checks+=1
 def stop(where,first=False):
  gdb.execute('tbreak '+where)
  gdb.execute('run' if first else 'continue')
 gdb.execute('set pagination off')
 stop('Params0Ready',True)
 for mode in [0,1]:
  if mode:
   stop('*Params1')
   eq('arg_i',42);eq('arg_d',3.25)
   assert gdb.parse_and_eval('local_i').is_optimized_out
   gdb.execute('stepi');eq('arg_i',42)
   stop('Params1Ready')
  for expr,want in [('arg_i',42),('arg_d',3.25),('arg_f',1.5),('arg_s',-9),('stackarg',1234),
    ('arg_ptr->count',123),('arg_ptr->ratio',6.5),('local_i',-42),('local_d',3.25),
    ('local_ptr->count',123),('local_arr[0]',-11),('local_arr[1]',22),('local_arr[2]',-33),
    ('local_node.count',321),('local_node.link->count',123),('local_node.values[2]',6),
    ('unused',0 if mode else 77),('extra',0 if mode else 88),('more',0 if mode else 99)]:eq(expr,want)
 for expr,want in [('GlobalScalar',-7),('GlobalDouble',3.25),('GlobalArray[0]',-1),
   ('GlobalArray[2]',-3),('GlobalPointer->count',123),('(**DoublePointer).ratio',6.5),
   ('NodeInstance.values[2]',3),('GlobalChoice.number',6.5),('GlobalFlags.lowbits',3),
   ('GlobalFlags.middlebits',5),('GlobalFlags.highbits',7)]:eq(expr,want)
 gdb.execute('ptype Node');gdb.execute('ptype SignedCount')
 # NOP and XOR precede the generated epilogue; its stack locations are unavailable.
 gdb.execute('stepi');gdb.execute('stepi')
 assert gdb.parse_and_eval('local_i').is_optimized_out
 stop('VectorReady')
 eq('vec',0x112233445566778899aabbccddeeff00);eq('local_vec',0x112233445566778899aabbccddeeff00)
 stop('HomeLeafReady');eq('input_value',42);eq('leaf_value',43)
 stop('FloatStackReady');eq('a8',3.25)
 gdb.execute('continue');eq('$_exitcode',0)
 print('DWARF variables/SYSVHOME: %d value checks PASS; frame lifetime and unused-register checks PASS'%checks)
except Exception:
 traceback.print_exc();gdb.execute('quit 1')
end
'''
(out/'variables.gdb').write_text(script)
run(['gdb','-q','-batch','-x',str(out/'variables.gdb'),str(out/'dwarf-variables')])
print('Interactive: gdb '+str(out/'dwarf-variables'))
