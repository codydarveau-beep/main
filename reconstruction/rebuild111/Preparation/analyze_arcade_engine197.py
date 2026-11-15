"""Identify bounded original arcade control-flow for faithful native restoration."""
from pathlib import Path
import struct,sys,json,collections
sys.path.insert(0,str(Path(__file__).resolve().parents[2]/'emulation-libs'))
from capstone import Cs,CS_ARCH_X86,CS_MODE_32,CS_GRP_JUMP,CS_GRP_RET
from capstone.x86 import X86_OP_IMM,X86_OP_MEM
R=Path(__file__).resolve().parent.parent;x=(R.parent/'packet194/released-default.xbe').read_bytes();md=Cs(CS_ARCH_X86,CS_MODE_32);md.detail=True
base=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-base+i*56)for i in range(n)]
def off(v):return next(s[3]+v-s[1]for s in ss if s[1]<=v<s[1]+s[4])
def word(v):return struct.unpack_from('<I',x,off(v))[0]
def walk(start,stops):
 queue=[start];ins={};calls=set();absolute=set();tables={}
 while queue:
  at=queue.pop()
  while at not in ins and at not in stops:
   i=next(md.disasm(x[off(at):off(at)+15],at));ins[at]=dict(address=at,mnemonic=i.mnemonic,operands=i.op_str,bytes=i.bytes.hex())
   for op in i.operands:
    if op.type==X86_OP_MEM and not op.mem.base:
     absolute.add(op.mem.disp&0xffffffff)
   if i.mnemonic=='call':
    assert i.operands[0].type==X86_OP_IMM,i.op_str;calls.add(i.operands[0].imm)
   if i.group(CS_GRP_RET):break
   if i.group(CS_GRP_JUMP):
    op=i.operands[0]
    if op.type==X86_OP_IMM:queue.append(op.imm)
    else:
     assert i.mnemonic=='jmp'and op.type==X86_OP_MEM and op.mem.disp in [0x1c00f4,0x1c1e98],(hex(at),i.op_str)
     targets=[word(op.mem.disp+j*4)for j in range(6 if op.mem.disp==0x1c00f4 else 5)];tables[hex(op.mem.disp)]=targets;queue+=targets
    if i.mnemonic=='jmp':break
   at+=i.size
 return dict(start=start,stops=stops,instructions=[ins[a]for a in sorted(ins)],calls=sorted(calls),absolute=sorted(absolute),tables=tables)
report={name:walk(start,stops)for name,start,stops in [('input',0x1d343,[0x1e44d,0x1f941]),('tick',0x1e44d,[0x1f941]),('reset',0xcc5a0,[]),('shot',0xccc90,[]),('abs',0x132bc0,[]),('fabsf',0x1369e0,[]),('fmaxf',0x136bf0,[]),('fminf',0x136dc0,[]),('memmove',0x1373d0,[]),('memset',0x137420,[]),('sinf',0x1377c0,[]),('classify',0x132b30,[]),('mathhelper',0x1466f0,[])]}
(R/'Preparation/Arcade-Control-Flow197.json').write_text(json.dumps(report,indent=2)+'\n')
for name,r in report.items():print(name,len(r['instructions']),'instructions; callees',[hex(v)for v in r['calls']],'foreign data',[hex(v)for v in r['absolute']if not(0xd478f0<=v<0xd48000 or 0x749e00<=v<0x74b000 or v in [0x1c00f4,0x1c1e98])])
