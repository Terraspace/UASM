"""Validate vector saves against decoded machine code, not assembler listings.
Run with Python 3 and llvm-objdump; no AVX-512 execution required.
"""
import argparse,re,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--objdump',default='llvm-objdump');p.add_argument('objects',nargs='+');a=p.parse_args()
functions=pairs=0
for file in a.objects:
 text=subprocess.check_output([a.objdump,'-d','--no-show-raw-insn','--x86-asm-syntax=intel',file],text=True)
 sections=re.split(r'^[0-9a-f]+ <([^>]+)>:\s*$',text,flags=re.M)
 for j in range(1,len(sections),2):
  name,body=sections[j:j+2]
  if not name.startswith('Use_'):continue
  regs={'rsp':0,'rbp':None};saves={};loads={};low=0
  def addr(expr):
   m=re.fullmatch(r'(rsp|rbp)(?: ([+-]) (0x[0-9a-f]+|\d+))?',expr)
   assert m,(name,expr)
   off=int(m[3],0) if m[3] else 0
   return regs[m[1]]+(-off if m[2]=='-' else off)
  for line in body.splitlines():
   m=re.match(r'\s*[0-9a-f]+:\s+(\w+)\s*(.*)',line)
   if not m:continue
   op,arg=m.groups()
   if op=='push':regs['rsp']-=8
   elif op=='pop':regs['rsp']+=8
   elif op in ('sub','add') and arg.startswith('rsp, '):regs['rsp']+=int(arg[5:],0)*(1 if op=='add' else -1)
   elif op=='mov' and arg in ('rbp, rsp','rsp, rbp'):
    dst,src=arg.split(', ');regs[dst]=regs[src]
   elif op=='lea' and arg.startswith(('rbp, [','rsp, [')):regs[arg[:3]]=addr(arg[6:-1])
   low=min(low,regs['rsp'])
   m=re.fullmatch(r'(xmmword|ymmword|zmmword) ptr \[([^]]+)\], ([xyz]mm\d+)',arg)
   if m and op.startswith(('mov','vmov')):
    width={'xmmword':16,'ymmword':32,'zmmword':64}[m[1]];off=addr(m[2]);reg=m[3]
    assert regs['rsp']<=off and off+width<=0,(name,'save outside frame',reg,off,width,regs)
    if op in ('movdqa','vmovdqa','vmovdqa64'):assert (8+off)%16==0,(name,'unaligned XMM save')
    assert reg not in saves;(saves)[reg]=(off,width)
   m=re.fullmatch(r'([xyz]mm\d+), (xmmword|ymmword|zmmword) ptr \[([^]]+)\]',arg)
   if m and op.startswith(('mov','vmov')):loads[m[1]]=(addr(m[3]),{'xmmword':16,'ymmword':32,'zmmword':64}[m[2]])
  assert regs['rsp']==0,(name,'unbalanced stack',regs)
  assert saves==loads,(name,saves,loads)
  assert len(saves)==6,(name,saves)
  ranges=sorted((off,off+width,reg) for reg,(off,width) in saves.items())
  for x,y in zip(ranges,ranges[1:]):assert x[1]<=y[0],(name,'overlap',x,y)
  functions+=1;pairs+=len(saves)
assert functions
print(f'PASS: {functions} frames, {pairs} matched vector save/restore slots, alignment and stack balance')
