"""Compare recovered caster choice to the original inline decision block."""
from pathlib import Path
import sys,struct,subprocess,ctypes,json,random
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x10000);u.mem_map(0x3000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000;ctx={}
def hook(cpu,at,size,user):
 if at in [0x35034,0x34902]:cpu.emu_stop();return
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_EAX,ctx['ranks'][[3,9,21].index(cpu.reg_read(UC_X86_REG_EDX))]);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0x35034,0x34902,0x941f0]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
(V/'companion_bolt_choice_adapter204.c').write_text('#include "companion_bolt_choice204.h"\nunsigned choose204(const unsigned*r,const int*e,unsigned sp,unsigned*out){return party_choose_bolt_values204(r,e,sp,out);}\n');subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_bolt_choice_adapter204.c'),'-lm','-lz','-o',str(V/'companion_bolt_choice204.so')],check=True);lib=ctypes.CDLL(str(V/'companion_bolt_choice204.so'));U=ctypes.c_uint;I=ctypes.c_int;lib.choose204.argtypes=[U*3,I*3,U,ctypes.POINTER(U)];rng=random.Random(204);cases=0
for k in range(12000):
 ranks=[rng.choice([0,1,5,10])for _ in range(3)];rates=[rng.choice([-100,-25,0,25,50,100,150,200])for _ in range(3)];points=rng.choice([0,5,10,15,20,50,500]);ctx['ranks']=ranks;u.mem_write(sp,bytes(1024));u.mem_write(sp+0xf0,struct.pack('<I',0x3000000));u.mem_write(sp+0x70,struct.pack('<I',0x3000014));u.mem_write(0x3000018,struct.pack('<I',points));u.mem_write(0xd42503,b'\1');u.mem_write(0xbef82c,struct.pack('<I',1));u.mem_write(0xbef844,bytes(4));u.mem_write(0xbef854,bytes(4))
 for element,rate in zip([3,1,4],rates):u.mem_write(0x429c00+20+element*2,struct.pack('<h',rate))
 u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0x34311,0x35035,count=10000);at=u.reg_read(UC_X86_REG_EIP);assert at in [0x35034,0x34902];expected=struct.unpack('<I',u.mem_read(sp+0x160,4))[0]if at==0x34902 else 0;out=U();actual=lib.choose204((U*3)(*ranks),(I*3)(*rates),points,ctypes.byref(out));assert actual==expected,(ranks,rates,points,actual,expected)
 if actual:assert out.value==struct.unpack('<I',u.mem_read(sp+0x120,4))[0]
 cases+=1
(V/'Companion-Bolt-Choice-Checks204.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,scope='Original learned-bolt choice, immunity/absorption, ties and insufficient-SP decision. Selection helper is not a completed caster kit; cast scheduling, repeated impacts and area/status spells remain integration work.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original elemental caster choices; host native-code comparison only.')
