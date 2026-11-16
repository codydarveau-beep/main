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
 elif at==0xf3500:result=ctx['flee']
 elif at in [0xca050,0x94070,0x95200]:result=0 if (at==0xca050 and ctx['scenario']&8) or (at in [0x94070,0x95200] and ctx['scenario']&1) else 1
 elif at==0x95650:
  ptr=cpu.reg_read(UC_X86_REG_ECX);hp=cpu.reg_read(UC_X86_REG_EDX);points=struct.unpack('<I',cpu.mem_read(esp+4,4))[0];cpu.mem_write(ptr+20,struct.pack('<2I',hp,points))
 elif at==0xa36d0:result=100
 elif at==0xcedf0:result=0
 elif at==0xa3870:
  target,life,damage=struct.unpack('<3I',cpu.mem_read(esp+4,12));assert target==0 and life==123;ctx['damage']=damage
 elif at==0x114370:ctx['cues']+=1
 cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0xca050,0x94070,0x95200,0xf3500,0xa36d0,0xcedf0,0xa3870,0x95650,0x114370,0x94440,0x137420]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_blacksmith_adapter217.c'),'-lm','-lz','-o',str(V/'companion_blacksmith217.so')],check=True);lib=ctypes.CDLL(str(V/'companion_blacksmith217.so'));U=ctypes.c_uint;lib.basic217.argtypes=[U]*12+[U*8];rng=random.Random(216);cases=0;coverage={}
for k in range(1600):
 identity=11;job=rng.choice([19,31]);jl=rng.choice([1,2,20,50] if job<21 else [1,2,20,50,70]);skill=1;rank=0;points=rng.choice([0,1,10,30,100]);level=rng.randrange(1,100);strength=rng.randrange(1,151);dex=rng.randrange(1,151);luck=rng.randrange(1,151);seed=rng.randrange(2**32);scenario=rng.choice([0,0,0,1,2,4,8,16]);out=(U*8)();lib.basic217(identity,job,jl,skill,rank,points,level,strength,dex,luck,seed,scenario,out)
 m=bytearray(244)
 for off,val in [(0,identity),(4,3),(16,level),(20,100),(24,points),(48,jl),(56,job),(60,1),(112,0),(124,123),(128,skill),(132,rank),(136,skill)]:struct.pack_into('<I',m,off,val)
 m[80]=strength;m[84]=dex;m[85]=luck
 for off,f in [(164,100.),(168,100.),(200,10.)]:struct.pack_into('<f',m,off,f)
 u.mem_write(0x3000000,bytes(m));u.mem_write(0xbef648,bytes(664));u.mem_write(0xbef884,struct.pack('<3I',124 if scenario&4 else 123,0,100000));u.mem_write(0xbef7d8,struct.pack('<2f',125. if scenario&2 else 112.,100.));u.mem_write(0xbe3098,struct.pack('<f',9. if scenario&16 else 10.));u.mem_write(0xbe30b8,struct.pack('<I',77));u.mem_write(0xc25dc8,struct.pack('<I',seed));u.mem_write(0x427d40,bytes(2));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);ctx.update(scenario=scenario,damage=0,cues=0,flee=out[6]);u.emu_start(0x111490,0x1000000,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
 expected=[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [24,128,64]]+[ctx['damage'],struct.unpack('<I',u.mem_read(0xc25dc8,4))[0],ctx['cues']];assert list(out)[:6]==expected,(k,identity,job,jl,skill,rank,points,scenario,list(out),expected);assert out[7]==77;cases+=1
 if ctx['damage']:coverage[skill]=coverage.get(skill,0)+1
assert all(coverage.get(skill,0)>0 for skill in [1]),coverage
(V/'Companion-Blacksmith-Basic-Checks217.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,damageCoverage=coverage,scope='Original complete Dagna basic impact family in both careers, own weapon/stats/power, exact own-SP impact payment and hit RNG/miss, absence of invented skill cues and range/line/serial/time/resource rejection. Native persistence is a callback fixture here; native element/defense are identity fixtures to compare pre-defense power against production hit callback. Real defense/durable actual candidate ticks are separate; no target playtest.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original Dagna basic impacts and deferred own-SP payment; host only.')
