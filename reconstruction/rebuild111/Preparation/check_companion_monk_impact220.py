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
 elif at in [0x94070,0x95200]:result=0 if ctx['scenario']&1 else 1
 elif at==0x95650:
  ptr=cpu.reg_read(UC_X86_REG_ECX);hp=cpu.reg_read(UC_X86_REG_EDX);points=struct.unpack('<I',cpu.mem_read(esp+4,4))[0];cpu.mem_write(ptr+20,struct.pack('<2I',hp,points))
 elif at==0xa3870:
  target,life,damage=struct.unpack('<3I',cpu.mem_read(esp+4,12));assert target==0 and life==123;ctx['damage']=damage
 elif at==0x114370:assert cpu.reg_read(UC_X86_REG_ECX) in [211];ctx['cues']+=1
 elif at==0x94440:pass
 else:raise AssertionError(hex(at))
 cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0x94070,0x95200,0xf3500,0xa3870,0x95650,0x114370,0x94440,0x137420]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_monk_adapter220.c'),'-lm','-lz','-o',str(V/'companion_monk220.so')],check=True);lib=ctypes.CDLL(str(V/'companion_monk220.so'));U=ctypes.c_uint;lib.impact220.argtypes=[U]*16+[U*20];rng=random.Random(218);cases=0;coverage={}
for k in range(2400):
 job=rng.choice([18,25]);jl=rng.choice([1,2,20,50] if job<21 else [1,2,20,50,70]);skill=rng.choice([1,202,211]);rank=0 if skill==1 else rng.randrange(1,11)if skill==202 else rng.randrange(1,6);points=rng.choice([0,1,10,30,100]);level=rng.randrange(1,100);strength=rng.randrange(1,151);dex=rng.randrange(1,151);luck=rng.randrange(1,151);kind=rng.randrange(655);seed=rng.randrange(2**32);scenario=rng.choice([0,0,0,1,2,4,8,16,32,64]);remaining=1 if skill==1 else rng.randrange(1,4)if skill==202 else rng.randrange(1,5);paid=rng.randrange(2);cached=rng.randrange(1,1000)if paid else 0;remainder=rng.randrange(4)if paid else 0;out=(U*20)();lib.impact220(job,jl,skill,rank,points,level,strength,dex,luck,kind,seed,scenario,remaining,paid,cached,remainder,out)
 m=bytearray(244)
 for off,val in [(0,5),(4,3),(16,level),(20,100),(24,points),(48,jl),(56,job),(60,remaining),(64,paid),(76,cached),(72,remainder),(112,0),(124,123),(128,skill),(132,rank),(136,skill)]:struct.pack_into('<I',m,off,val)
 m[80]=strength;m[84]=dex;m[85]=luck
 for off,f in [(164,100.),(168,100.),(200,10.)]:struct.pack_into('<f',m,off,f)
 mob=bytearray(664);struct.pack_into('<2f',mob,400,125. if scenario&2 else 112.,100.);struct.pack_into('<2f',mob,416,1.,0.);struct.pack_into('<3I',mob,572,124 if scenario&4 else 123,kind,100000);struct.pack_into('<I',mob,592,0 if scenario&8 else 1);struct.pack_into('<2f',mob,620,2.5,.8)
 if scenario&32:struct.pack_into('<f',mob,508,2.)
 if scenario&64:struct.pack_into('<f',mob,524,2.)
 u.mem_write(0x3000000,bytes(m));u.mem_write(0xbef648,bytes(mob));u.mem_write(0xbe3080,struct.pack('<2f',100.,100.));u.mem_write(0xbe3098,struct.pack('<f',9. if scenario&16 else 10.));u.mem_write(0xbe30c0,struct.pack('<I',100));u.mem_write(0xbe30b8,struct.pack('<I',77));u.mem_write(0xc25dc8,struct.pack('<I',seed));u.mem_write(0xd42501+5,bytes([1]));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);ctx.update(scenario=scenario,damage=0,cues=0,flee=out[15]);u.emu_start(0x111490,0x1000000,count=200000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
 expected=[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [24,128,64,76,60]]+[struct.unpack('<I',u.mem_read(0xc25dc8,4))[0],ctx['damage'],ctx['cues']]+[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [200,192]]+list(struct.unpack('<2I',u.mem_read(0xbef7e8,8)))+list(struct.unpack('<2I',u.mem_read(0xbef8b4,8)))+[77]+[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [72,68,160,212]];assert list(out)[:15]+list(out)[16:20]==expected,(k,job,jl,skill,rank,points,kind,scenario,paid,remaining,list(out),expected);cases+=1
 if ctx['damage']:coverage[skill]=coverage.get(skill,0)+1
assert all(coverage.get(skill,0)>0 for skill in [1,202,211]),coverage
(V/'Companion-Monk-Impact-Checks220.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,damageCoverage=coverage,scope='Original Suri full physical resolver in both careers: own Iron Fists/power/ratios, native target eligibility and real element/defense reduction, exact cached split/remainder damage for three/four hits, deferred once-only SP/RNG, no extra Trifecta cue and original 1.2-second same-target follow-up window. Every cache/repeat/timing/combo field agrees. Native persistence/line/enemy flee/final HP application are recording boundaries; live integration and failed storage remain separate',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original Suri complete combo impacts, native defenses/statuses and repeat cache; host only.')
