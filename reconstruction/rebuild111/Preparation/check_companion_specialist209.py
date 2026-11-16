"""Compare actual original bolt resolver with the recovered C impact step."""
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
 elif at in [0xca050,0x95200,0x94070]:result=0 if (at==0xca050 and ctx['scenario']&32) or (at!=0xca050 and ctx['scenario']&2) else 1
 elif at==0x95650:
  ptr=cpu.reg_read(UC_X86_REG_ECX);hp=cpu.reg_read(UC_X86_REG_EDX);points=struct.unpack('<I',cpu.mem_read(esp+4,4))[0];result=0 if ctx['scenario']&1 else 1
  if result:cpu.mem_write(ptr+20,struct.pack('<2I',hp,points))
 elif at==0x114540:
  life,damage,magic=struct.unpack('<3I',cpu.mem_read(esp+4,12));assert life==123 and magic==1;ctx['damage']=damage
  if ctx['scenario']&16:cpu.mem_write(0xbef88c,bytes(4))
 elif at==0xa3fc0:ctx['after']=1
 elif at==0xa9340:ctx['after']=2
 cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0xca050,0x95200,0x94070,0x95650,0x114540,0x114370,0xa3fc0,0xa9340,0x137420]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_specialist_adapter209.c'),'-lm','-lz','-o',str(V/'companion_specialist209.so')],check=True);lib=ctypes.CDLL(str(V/'companion_specialist209.so'));U=ctypes.c_uint;lib.step209.argtypes=[U]*12+[U*11];rng=random.Random(209);cases=0;payments={}
for skill in [352,355,358,438,439,440]:
 for k in range(300):
  rank=rng.randrange(1,11);remaining=rng.randrange(1,rank+1);paid=rng.randrange(2);points=rng.choice([0,1,10,50,500]);intelligence=rng.randrange(1,151);level=rng.choice([20,69,70,79,80,89,90,99]);jl=rng.choice([1,10,50,70]);kind=rng.randrange(100);primed=rng.randrange(2);seed=rng.randrange(2**32);scenario=rng.choice([0,0,0,1,2,4,8,16,32]);identity=14 if skill<438 else 18;job=41 if skill<438 else 45;m=bytearray(244)
  for off,val in [(0,identity),(4,3),(16,level),(20,100),(24,points),(48,jl),(56,job),(60,remaining),(64,paid),(112,0),(124,123),(128,skill),(132,rank),(136,skill)]:struct.pack_into('<I',m,off,val)
  m[83]=intelligence
  for off,f in [(156,11. if primed else 0.),(164,100.),(168,100.),(200,10.)]:struct.pack_into('<f',m,off,f)
  u.mem_write(0x3000000,bytes(m));u.mem_write(0xbef648,bytes(664));u.mem_write(0xbef884,struct.pack('<3I',124 if scenario&8 else 123,kind,100000));u.mem_write(0xbef7d8,struct.pack('<2f',300. if scenario&4 else 112.,100.));u.mem_write(0xbe3098,struct.pack('<f',10.));u.mem_write(0xbe30b8,struct.pack('<I',77));u.mem_write(0xc25dc8,struct.pack('<I',seed));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);ctx.update(scenario=scenario,damage=0,after=0);u.emu_start(0x111490,0x1000000,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
  expected=[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [24,128,60,64,156,200,192]]+[struct.unpack('<I',u.mem_read(0xc25dc8,4))[0],ctx['damage'],ctx['after'],struct.unpack('<I',u.mem_read(0xbe30b8,4))[0]];out=(U*11)();lib.step209(skill,rank,remaining,paid,points,intelligence,level,jl,kind,primed,seed,scenario,out);assert list(out)==expected,(skill,rank,remaining,paid,level,jl,scenario,list(out),expected);cases+=1
  if not paid and out[3] and out[0]<points:payments[job]=payments.get(job,0)+1
assert all(payments.get(job,0)>0 for job in [41,45]),payments
(V/'Companion-Specialist-Impact-Checks209.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,successfulPaymentsByAuthoredJob=payments,scope='Actual native Ninja/Soul Linker impact compared to production targeted step: learned caster costs/passives, one debit, own INT/level, size ratios, Esma priming/consumption, RNG and repeated-hit scheduling, rejected save/line/range/stale/invalid targets. Final hit, status/knockback requests and sound are explicit recording boundaries; actual battle choices and status acceptance remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original targeted specialist impacts; host only.')
