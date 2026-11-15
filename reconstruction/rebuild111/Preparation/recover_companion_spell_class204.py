"""Recover original spell classification from the native interruption decision."""
from pathlib import Path
import sys,struct,subprocess,ctypes,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x3000000,4096)
def stop(cpu,at,size,user):cpu.emu_stop()
for at in [0x3031e,0x3033a]:u.hook_add(UC_HOOK_CODE,stop,begin=at,end=at)
def original(skill):
 u.mem_write(0x3000080,struct.pack('<I',skill));u.reg_write(UC_X86_REG_ESI,0x3000000);u.emu_start(0x302d2,0x3033b,count=1000);at=u.reg_read(UC_X86_REG_EIP);assert at in [0x3031e,0x3033a];return at==0x3033a
skills=[i for i in range(446)if original(i)];p=R/'Source/companion_spell_class204.h';p.write_text('/* Exact original companion spell family used for interruption and casting poses. */\n#ifndef MYRO_COMPANION_SPELL_CLASS204_H\n#define MYRO_COMPANION_SPELL_CLASS204_H\nstatic int party_caster_spell194(unsigned skill){switch(skill){'+''.join('case '+str(i)+':'for i in skills)+'return 1;default:return 0;}}\n#endif\n')
(V/'companion_spell_class_adapter204.c').write_text('#include "companion_spell_class204.h"\nint spell204(unsigned s){return party_caster_spell194(s);}\n');subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_spell_class_adapter204.c'),'-o',str(V/'companion_spell_class204.so')],check=True);lib=ctypes.CDLL(str(V/'companion_spell_class204.so'));lib.spell204.argtypes=[ctypes.c_uint]
for skill in range(446):assert bool(lib.spell204(skill))==original(skill)
(V/'Companion-Spell-Class-Checks204.json').write_text(json.dumps(dict(passed=True,nativeComparisons=446,spellIDs=skills,scope='Actual original interruption-family branch; shared by candidate casting pose selection. Full effect and career activation checks remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original companion spell family classification; host native-code comparison only.')
