"""Restore exact native career attack multipliers, retaining distinct skill cases."""
from pathlib import Path
import struct,json,sys,subprocess,ctypes
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,4096);u.mem_map(0x1000000,4096)
def original(skill,rank):
 u.mem_write(0x2000800,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,0x2000800);u.reg_write(UC_X86_REG_ECX,skill);u.reg_write(UC_X86_REG_EDX,rank);u.emu_start(0x114980,0x1000000,count=1000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000;return u.reg_read(UC_X86_REG_EAX)
rows=[]
for skill in range(445):
 values=[original(skill,r)for r in range(11)]
 if any(v!=100 for v in values):
  a,b=values[0],values[1]-values[0];assert values==[a+b*r for r in range(11)];rows.append((skill,a,b))
p=R/'Source/companion_multipliers203.h';p.write_text('/* Exact original career skill ratios; distinct from Bash and spell hit counts. */\n#ifndef MYRO_COMPANION_MULTIPLIERS203_H\n#define MYRO_COMPANION_MULTIPLIERS203_H\nstatic unsigned party_skill_ratio203(unsigned skill,unsigned rank){\n static const unsigned short cases[][3]={'+','.join('{'+','.join(map(str,row))+'}'for row in rows)+'};\n for(unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);i++)if(cases[i][0]==skill)return cases[i][1]+cases[i][2]*rank;\n return 100;\n}\n#endif\n')
(V/'companion_multipliers_adapter203.c').write_text('#include "companion_multipliers203.h"\nunsigned ratio203(unsigned s,unsigned r){return party_skill_ratio203(s,r);}\n');subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_multipliers_adapter203.c'),'-o',str(V/'companion_multipliers203.so')],check=True);lib=ctypes.CDLL(str(V/'companion_multipliers203.so'));lib.ratio203.argtypes=[ctypes.c_uint,ctypes.c_uint];count=0
for skill in range(446):
 for rank in range(11):
  assert lib.ratio203(skill,rank)==original(skill,rank),(skill,rank);count+=1
(V/'Companion-Multiplier-Checks203.json').write_text(json.dumps(dict(passed=True,nativeVA='0x114980',nativeComparisons=count,authoredCases=rows,runtimeIntegrated=False,scope='Original distinct career skill ratios, including rank zero and unknown skill fallback. This helper is not the full resolver: separate hit counts, elements, costs, statuses and target rules must be integrated before enabling careers.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original career attack multipliers; full resolver integration remains pending, host only.')
