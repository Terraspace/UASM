#!/usr/bin/env python3
"""ELF64 PIC object and Linux loader checks. Requires Python 3, plus cc for --runtime."""
import argparse, pathlib, struct, subprocess, tempfile, os
ap=argparse.ArgumentParser();ap.add_argument('--asm',required=True);ap.add_argument('--runtime',action='store_true');a=ap.parse_args()
assembler=str(pathlib.Path(a.asm).resolve());root=pathlib.Path(__file__).resolve().parents[1]
def run(args,**kw):
 return subprocess.run([str(x) for x in args],check=True,capture_output=True,text=True,**kw).stdout
def elf(path):
 b=path.read_bytes(); assert b[:6]==b'\x7fELF\x02\x01'
 off=struct.unpack_from('<Q',b,40)[0];size,num,strings=struct.unpack_from('<HHH',b,58)
 sh=[struct.unpack_from('<IIQQQQIIQQ',b,off+i*size) for i in range(num)]
 def data(h):return b[h[4]:h[4]+h[5]]
 def string(buf,n):return buf[n:buf.index(0,n)].decode()
 names=data(sh[strings]);sections={string(names,h[0]):data(h) for h in sh}
 table=next(h for h in sh if h[1]==2);st=data(sh[table[6]]);symbols=[]
 for i in range(0,table[5],24):
  n,info,other,idx,value,sz=struct.unpack_from('<IBBHQQ',data(table),i)
  symbols.append((string(st,n),info,other,idx,value))
 rel=[]
 for h in sh:
  if h[1]==4:
   for i in range(0,h[5],24):
    pos,info,add=struct.unpack_from('<QQq',data(h),i);rel.append((pos,info&0xffffffff,symbols[info>>32][0],add))
 return sections,{s[0]:s[1:] for s in symbols},rel
with tempfile.TemporaryDirectory(prefix='uasm-pic-') as d:
 d=pathlib.Path(d)
 def assemble(name):
  out=d/(name+'.o');run([assembler,'-q','-elf64','-Fo'+str(out),root/'src/elf64_pic_calls'/(name+'.asm')]);return out
 calls=assemble('calls');sec,sym,rel=elf(calls)
 assert rel==[(1,4,'imported',-4),(6,4,'imported',-1),(11,2,'hidden_import',-4),(16,4,'exported',-4),(36,4,'imported',-4),(65,4,'exported',-4),(70,4,'exported',-4)],rel
 assert sym['hidden_fn'][1]==2 and sym['protected_fn'][1]==3 and sym['exported'][1]==0
 # Three resolved local calls, independently calculated displacements.
 assert sec['.text'][20:35]==bytes.fromhex('e8 15 00 00 00 e8 16 00 00 00 e8 17 00 00 00')
 _,_,rel=elf(assemble('late_public'));assert rel==[(1,4,'later',-4),(6,4,'later',-4)],rel
 _,sym,_=elf(assemble('visibility'))
 assert [sym[n][1] for n in ['default_data','hidden_data','protected_data']]==[0,2,3]
 _,sym,rel=elf(assemble('cross_section'))
 assert [(kind,name,add) for _,kind,name,add in rel]==[(4,'optional',-4),(4,'public_fn',-4),(2,'hidden_fn',-4),(2,'private_fn',-4)]
 assert sym['optional'][0]>>4==2
 _,sym,rel=elf(assemble('forward_proto'));assert not rel
 assert sym['hidden_proc'][1]==2 and sym['protected_proc'][1]==3
 runtime=assemble('runtime');_,sym,rel=elf(runtime)
 assert sym['imported'][0]&15==2
 assert [(t,n,add) for _,t,n,add in rel]==[(4,'exported',-4),(4,'supplied',-4),(4,'imported',-4)]
 print('PIC object checks passed: relocation types/addends, direct branches, visibility, forward PUBLIC and PROTO type')
 if a.runtime:
  def source(name,text):
   p=d/name;p.write_text(text);return p
  supplied=source('supplied.c','int supplied(void){return 14;}')
  imported=source('imported.c','int imported(void){return 15;}')
  override=source('override.c','int exported(void){return 91;} int protected_fn(void){return 92;} int hidden_fn(void){return 93;}')
  main=source('main.c',r'''#include <stdlib.h>
extern int call_exported(void),call_hidden(void),call_protected(void),call_supplied(void),call_imported(void);
int main(void){int expected=getenv("EXPECT_OVERRIDE")?91:11;return !(call_exported()==expected && call_hidden()==12 && call_protected()==13 && call_supplied()==14 && call_imported()==15);}
''')
  cc=os.environ.get('CC','cc')
  run([cc,'-fPIC','-c',supplied,'-o',d/'supplied.o'])
  run([cc,'-shared','-fPIC',imported,'-o',d/'libimported.so'])
  run([cc,'-shared','-fPIC',override,'-o',d/'liboverride.so'])
  # Independent GNU assembler oracle for unresolved CALL/JMP PLT32 addends.
  reference=source('reference.s','.text\ncall imported@PLT\ncall imported@PLT+3\njmp imported@PLT\n')
  run([cc,'-c',reference,'-o',d/'reference.o'])
  _,_,rr=elf(d/'reference.o');assert [(t,n,add) for _,t,n,add in rr]==[(4,'imported',-4),(4,'imported',-1),(4,'imported',-4)]
  for linker in ['bfd','lld']:
   probe=subprocess.run([cc,'-fuse-ld='+linker,'-Wl,--version'],capture_output=True)
   if probe.returncode:print('SKIP optional linker',linker);continue
   flags=['-fuse-ld='+linker,'-Wl,-z,text,-z,noexecstack','-Wl,-rpath,$ORIGIN','-L'+str(d)]
   run([cc,*flags,'-shared',runtime,d/'supplied.o','-limported','-o',d/'libtest.so'])
   run([cc,*flags,'-fPIE','-pie',main,'-ltest','-o',d/'test'])
   run([d/'test']);env=dict(os.environ,LD_PRELOAD=str(d/'liboverride.so'),EXPECT_OVERRIDE='1');run([d/'test'],env=env)
   env['LD_BIND_NOW']='1';run([d/'test'],env=env)
   dynamic=run(['readelf','-dW',d/'libtest.so']);assert 'TEXTREL' not in dynamic
   # The same PLT-capable object binds directly when linked into a PIE.
   run([cc,*flags,'-fPIE','-pie',main,runtime,d/'supplied.o','-limported','-o',d/'direct'])
   run([d/'direct']);run([d/'direct'],env=dict(os.environ,LD_PRELOAD=str(d/'liboverride.so')))
   print(linker+': PIE/SO calls, INVOKE, local binding, interposition, hidden/protected, eager/lazy binding passed')
