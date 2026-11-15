"""Compare actual original impact-element branch, not inferred skill labels."""
from pathlib import Path
import sys,struct,subprocess,ctypes,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,4096);u.mem_map(0x3000000,4096)
(V/'companion_element_adapter204.c').write_text('#include "companion_element204.h"\nunsigned element204(unsigned s,unsigned m){return party_impact_element204(s,m);}\n');subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_element_adapter204.c'),'-o',str(V/'companion_element204.so')],check=True);lib=ctypes.CDLL(str(V/'companion_element204.so'));lib.element204.argtypes=[ctypes.c_uint,ctypes.c_uint];cases=0
for skill in range(446):
 for magic in [0,1]:
  u.mem_write(0x3000088,struct.pack('<I',skill));u.mem_write(0x2000830,struct.pack('<I',magic));u.reg_write(UC_X86_REG_ESP,0x2000800);u.reg_write(UC_X86_REG_ESI,0x3000000);u.emu_start(0x114636,0x11469f,count=1000);assert u.reg_read(UC_X86_REG_EIP)==0x11469f;assert lib.element204(skill,magic)==u.reg_read(UC_X86_REG_EDX),(skill,magic);cases+=1
(V/'Companion-Element-Checks204.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,runtimeImpactCallerIntegrated=True,scope='Original per-skill magical/physical impact element selection; complete career targeting, statuses and repeated-hit casting remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original companion impact elements; host native-code comparison only.')
