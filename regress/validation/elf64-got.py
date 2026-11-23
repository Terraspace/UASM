#!/usr/bin/env python3
"""GOT independent encoding/relocation oracle and Linux runtime checks."""
import argparse,pathlib,struct,subprocess,tempfile,os
ap=argparse.ArgumentParser();ap.add_argument('--asm',required=True);ap.add_argument('--clang');ap.add_argument('--runtime',action='store_true');a=ap.parse_args()
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

with tempfile.TemporaryDirectory(prefix='uasm-got-') as d:
 d=pathlib.Path(d)
 def assemble(name):
  out=d/(name+'.o');run([assembler,'-q','-elf64','-Fo'+str(out),root/'src/elf64_got'/(name+'.asm')]);return out
 for name in ['forms','widths']:
  obj=assemble(name);sec,sym,rel=elf(obj)
  ref=root/'validation'/('elf64-got-'+name+'.s');out=d/(name+'-ref.o')
  if a.clang:run([a.clang,'-target','x86_64-linux-gnu','-c','-Wa,-mrelax-relocations=no','-o',out,ref])
  else:run(['as','--64','-mrelax-relocations=no','-o',out,ref])
  rs,_,rr=elf(out)
  assert sec['.text']==rs['.text'],name+' machine code differs from independent assembler'
  assert rel==rr,(name,rel,rr)
  assert all(t==9 and add==-4 for _,t,_,add in rel),rel
  print(name+': code and GOTPCREL relocations match independent assembler')
 _,_,rel=elf(assemble('local_addresses'));assert [t for _,t,_,_ in rel]==[9,2,2,2,2,9,9,2],rel
 assert all(add==-4 for _,_,_,add in rel)
 runtime=assemble('runtime')
 if a.runtime:
  def source(name,text):
   p=d/name;p.write_text(text);return p
  provider=source('provider.c',"int counter=123,values[2]={17,19}; double real_value=3.25; int imported_fn(void){return 77;} int consume(int*p){return *p;} int (*callback)(void)=imported_fn;")
  override=source('override.c',"int counter=321,local_counter=91; int imported_fn(void){return 88;}")
  main=source('main.c',r"""#include <stdlib.h>
#include <assert.h>
extern int counter,values[],imported_fn(void);
extern int call_pointer(void),tail_pointer(void);
extern int get_counter(void),get_second(void),get_local(void),check_flags(void),check_regs(void),call_consume(void);
extern void set_counter(int),bump_counter(void),adc_counter(void);
extern double get_real(void);
extern int *get_pointer(void),*get_offset(void);
extern int (*get_function(void))(void);
int main(void){int over=getenv("EXPECT_OVERRIDE")!=0;
assert(get_counter()==(over?321:123));assert(get_local()==(over?91:31));
assert(get_second()==19);assert(get_real()==3.25);
assert(get_pointer()==&counter);assert(get_offset()==values+1);
assert(get_function()==imported_fn);assert(get_function()()==(over?88:77));
assert(call_pointer()==(over?88:77));assert(tail_pointer()==(over?88:77));
assert(check_flags()==1);assert(check_regs()==1);
set_counter(456);assert(counter==456);bump_counter();assert(counter==457);
adc_counter();assert(counter==458);assert(call_consume()==458);return 0;}
""")
  cc=os.environ.get('CC','cc');flags=['-Wl,-z,text,-z,noexecstack','-Wl,-rpath,$ORIGIN','-L'+str(d)]
  run([cc,'-shared','-fPIC',provider,'-o',d/'libprovider.so'])
  run([cc,'-shared','-fPIC',override,'-o',d/'liboverride.so'])
  run([cc,*flags,'-shared',runtime,'-lprovider','-o',d/'libgot.so'])
  run([cc,*flags,'-fPIC','-pie',main,'-lgot','-lprovider','-o',d/'test'])
  run([d/'test']);env=dict(os.environ,LD_PRELOAD=str(d/'liboverride.so'),EXPECT_OVERRIDE='1');run([d/'test'],env=env)
  env['LD_BIND_NOW']='1';run([d/'test'],env=env)
  for file in ['libgot.so','test']:
   assert 'TEXTREL' not in run(['readelf','-dW',d/file])
   assert 'R_X86_64_COPY' not in run(['readelf','-rW',d/file])
  print('Linux GOT runtime passed: loads/stores, SIMD, offsets, flags, register preservation, INVOKE ADDR, pointers and data/function interposition; no TEXTREL/COPY')
