"""Recover promoted actor selection and compare every roster/job pair to native code."""
from pathlib import Path
import sys,struct,subprocess,ctypes,json
R=Path(__file__).resolve().parent.parent;sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c)
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
rows=[struct.unpack_from('<3I',x,a-65536)for a in range(0x6e6848,0x6e6914,12)]
assert len(rows)==17 and all(a<45 and c<45 and j<46 for a,j,c in rows)
header='/* Exact original base-actor/job to promoted-actor mapping. */\n#ifndef MYRO_COMPANION_ART200_H\n#define MYRO_COMPANION_ART200_H\nstatic unsigned party_actor_source200(unsigned base,unsigned job){\n static const unsigned char variants[][3]={'+','.join('{'+','.join(map(str,row))+'}'for row in rows)+'};\n for(unsigned i=0;i<sizeof(variants)/sizeof(variants[0]);i++)if(variants[i][0]==base&&variants[i][1]==job)return variants[i][2];\n return base;\n}\n#endif\n'
(R/'Source/companion_art200.h').write_text(header)
(R/'Validation/companion_art_adapter200.c').write_text('#include "companion_art200.h"\nunsigned source200(unsigned a,unsigned j){return party_actor_source200(a,j);}\n')
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(R/'Validation/companion_art_adapter200.c'),'-o',str(R/'Validation/companion_art200.so')],check=True)
lib=ctypes.CDLL(str(R/'Validation/companion_art200.so'));lib.source200.argtypes=[ctypes.c_uint,ctypes.c_uint];cases=0
for identity in range(19):
 base=struct.unpack_from('<I',x,0x2a78a8+identity*12-65536)[0]
 for job in range(46):
  u.reg_write(UC_X86_REG_EDI,identity);u.reg_write(UC_X86_REG_EDX,job);u.emu_start(0x3e55d,0x3e589,count=1000)
  assert u.reg_read(UC_X86_REG_EIP)==0x3e589
  assert lib.source200(base,job)==u.reg_read(UC_X86_REG_EAX),(identity,base,job)
  cases+=1
(R/'Validation/Companion-Art-Checks200.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,promotedMappings=rows,runtimeSelectorIntegrated=True,scope='Exact promoted actor selector; source pose decoding separately covered by content/sequence checks. Complete career AI remains pending.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
print('PASS original promoted actor selection across all roster/job pairs; host CPU comparison only.')
