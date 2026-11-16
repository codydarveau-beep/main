"""Compare original Judia basic/Double Strafe resolver with production impact step."""
from pathlib import Path
import sys,struct,ctypes,json,random,subprocess
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x10000);u.mem_map(0x3000000,4096);u.mem_map(0x1000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000;ctx={}
def hook(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];result=1
 if at==0x137420:
  dest,value,count=struct.unpack('<3I',cpu.mem_read(esp+4,12));cpu.mem_write(dest,bytes([value&255])*count);result=dest
 elif at==0xca050:
  target=cpu.reg_read(UC_X86_REG_ECX);result=int(target<3 and not(target==0 and ctx['scenario']&8) and not(target==1 and ctx['scenario']&256))
 elif at in [0x94070,0x95200]:result=0 if ctx['scenario']&1 else 1
 elif at==0x95650:
  ptr=cpu.reg_read(UC_X86_REG_ECX);hp=cpu.reg_read(UC_X86_REG_EDX);points=struct.unpack('<I',cpu.mem_read(esp+4,4))[0];cpu.mem_write(ptr+20,struct.pack('<2I',hp,points))
 elif at==0x114370:assert cpu.reg_read(UC_X86_REG_ECX)==230;ctx['cues']+=1
 else:raise AssertionError(hex(at))
 cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0xca050,0x94070,0x95200,0x95650,0x114370,0x137420]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_blacksmith_adapter217.c'),'-lm','-lz','-o',str(V/'companion_blacksmith217.so')],check=True);lib=ctypes.CDLL(str(V/'companion_blacksmith217.so'));U=ctypes.c_uint;lib.hammer217.argtypes=[U]*7+[U*12];rng=random.Random(217);cases=0;stuns=0
for k in range(1200):
 job=rng.choice([19,31]);jl=rng.choice([1,2,20,50] if job<21 else [1,2,20,50,70]);rank=rng.randrange(1,6);points=rng.choice([0,1,10,30,100]);kind=rng.randrange(600);seed=rng.randrange(2**32);scenario=rng.choice([0,0,0,1,2,4,8,16,32,64,128,256]);out=(U*12)();lib.hammer217(job,jl,rank,points,kind,seed,scenario,out)
 m=bytearray(244)
 for off,val in [(0,11),(4,3),(16,90),(20,100),(24,points),(48,jl),(56,job),(60,1),(112,0),(124,123),(128,230),(132,rank),(136,230)]:struct.pack_into('<I',m,off,val)
 for off,f in [(164,100.),(168,100.),(200,10.)]:struct.pack_into('<f',m,off,f)
 u.mem_write(0x3000000,bytes(m));u.mem_write(0xbef648,bytes(664*3))
 for i in range(3):
  mob=bytearray(664);struct.pack_into('<2f',mob,400,181. if i==0 and scenario&2 else 164. if i==0 else 180. if i==1 else 185.,100.);struct.pack_into('<3I',mob,572,124 if i==0 and scenario&4 else 123,kind,100000)
  if i==1:
   if scenario&32:struct.pack_into('<f',mob,508,2.)
   if scenario&64:struct.pack_into('<f',mob,612,2.5)
   if scenario&128:struct.pack_into('<f',mob,524,2.)
   if scenario&256:struct.pack_into('<I',mob,548,1);struct.pack_into('<I',mob,568,3)
  u.mem_write(0xbef648+i*664,bytes(mob))
 u.mem_write(0xbe3098,struct.pack('<f',9. if scenario&16 else 10.));u.mem_write(0xbe30c0,struct.pack('<I',100));u.mem_write(0xbe30b8,struct.pack('<I',77));u.mem_write(0xc25dc8,struct.pack('<I',seed));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);ctx.update(scenario=scenario,cues=0);u.emu_start(0x111490,0x1000000,count=300000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
 expected=[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [24,128,64]]+[struct.unpack('<I',u.mem_read(0xc25dc8,4))[0]]+[struct.unpack('<I',u.mem_read(0xbef8ac+i*664,4))[0]for i in range(3)]+[ctx['cues']]+[100000]*3+[77];assert list(out)==expected,(k,job,jl,rank,points,kind,scenario,list(out),expected);cases+=1;stuns+=out[4]!=0
assert stuns>0
(V/'Companion-Blacksmith-Impact-Checks217.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,stunCases=stuns,scope='Original complete Dagna Hammer Fall impact and real native stun resistance/RNG/duration compared to production real status helper, both careers and three-enemy clusters at native 20-unit boundary, boss/training/frozen/stone/pre-existing stun cases, deferred own-SP payment and serial/range/line/time/resource rejection. Native persistence and validity/line are explicit fixtures; actual battle/durable failure integration remains separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original Dagna area stun, statuses and deferred payment; host only.')
