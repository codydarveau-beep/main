"""Recover authored weapons and compare physical power with native 0x114870."""
from pathlib import Path
import struct,json,sys,subprocess,ctypes,random
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();base=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-base+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);u.mem_map(0x3000000,4096);u.mem_map(0x1000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000
weapons=struct.unpack_from('<19I',x,0x5e59a0-65536)
(R/'Source/companion_weapons202.h').write_text('/* Exact original authored companion weapons. */\n#ifndef MYRO_COMPANION_WEAPONS202_H\n#define MYRO_COMPANION_WEAPONS202_H\nstatic const unsigned partyWeapons202[19]={'+','.join(map(str,weapons))+'};\n#endif\n')
(V/'companion_power_adapter202.c').write_text('#include "companion_power202.h"\nunsigned power202(unsigned id,unsigned s,unsigned d,unsigned l){return party_power_values202(id,s,d,l);}\n')
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_power_adapter202.c'),'-lm','-lz','-o',str(V/'companion_power202.so')],check=True);lib=ctypes.CDLL(str(V/'companion_power202.so'));lib.power202.argtypes=[ctypes.c_uint]*4;rng=random.Random(202);cases=0
for identity in range(19):
 for k in range(100):
  stats=[rng.randrange(1,151)for _ in range(6)];buff=rng.randrange(0,11);active=k%2;raw=bytearray(244);struct.pack_into('<I',raw,0,identity);raw[80:86]=bytes(stats);raw[86]=buff;struct.pack_into('<f',raw,88,20. if active else 0.);u.mem_write(0x3000000,bytes(raw));u.mem_write(sp,struct.pack('<If',0x1000000,10.));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);u.emu_start(0x114870,0x1000000,count=10000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
  actual=lib.power202(identity,stats[0]+buff*active,stats[4]+buff*active,stats[5]);expected=u.reg_read(UC_X86_REG_EAX);assert actual==expected,(identity,stats,buff,active,actual,expected);cases+=1
(V/'Companion-Power-Checks202.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,authoredWeapons=list(weapons),scope='Original per-person weapon and melee/ranged physical power, including active Blessing. Full career choices, modifiers and hit/effect resolution remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original companion weapons and physical power; host native-code comparison only.')
