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
  target,life,damage=struct.unpack('<3I',cpu.mem_read(esp+4,12));assert target<3 and life==123+target;ctx['damage'][target]+=damage
 elif at==0xa3fc0:
  target=cpu.reg_read(UC_X86_REG_EDX);assert target<3;values=struct.unpack('<3I',cpu.mem_read(esp+4,12));ctx['push'][target*3:target*3+3]=values;ctx['mask']|=1<<target
 elif at==0x114370:assert cpu.reg_read(UC_X86_REG_ECX) in [386,388,390,392];ctx['cues']+=1
 elif at==0x94440:pass
 else:raise AssertionError(hex(at))
 cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0x94070,0x95200,0xf3500,0xa3870,0xa3fc0,0x95650,0x114370,0x94440,0x137420]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_taekwon_adapter221.c'),'-lm','-lz','-o',str(V/'companion_taekwon221.so')],check=True);lib=ctypes.CDLL(str(V/'companion_taekwon221.so'));U=ctypes.c_uint;lib.impact221.argtypes=[U]*12+[U*35];rng=random.Random(221);cases=0;coverage={};armed=pushes=0
for k in range(2400):
 identity=rng.choice([16,17]);jl=rng.choice([1,2,20,50]);skill=rng.choice([1,1,386,388,390,392]);rank=0 if skill==1 else rng.randrange(1,8);points=rng.choice([0,1,10,30,100]);strength=rng.randrange(1,151);agility=rng.randrange(1,151);dex=rng.randrange(1,151);luck=rng.randrange(1,151);kind=rng.randrange(655);seed=rng.randrange(2**32);scenario=rng.choice([0,0,0,0,0,1,2,4,8,16,32,64,128,256,512,2048]);out=(U*35)();lib.impact221(identity,jl,skill,rank,points,strength,agility,dex,luck,kind,seed,scenario,out)
 m=bytearray(244)
 for off,val in [(0,identity),(4,3),(16,90),(20,100),(24,points),(48,jl),(56,43 if identity==16 else 44),(60,1),(112,0),(124,123),(128,skill),(132,rank),(136,skill)]:struct.pack_into('<I',m,off,val)
 m[80]=strength;m[81]=agility;m[84]=dex;m[85]=luck
 for off,f in [(164,100.),(168,100.),(200,10.),(160,11. if scenario&256 else 0.)]:struct.pack_into('<f',m,off,f)
 u.mem_write(0x3000000,bytes(m));u.mem_write(0xbef648,bytes(664*3))
 for i in range(3):
  mob=bytearray(664);x=125. if i==0 and scenario&2 else 121. if i==0 and scenario&2048 else 112. if i==0 else 116. if i==1 else 121.;struct.pack_into('<2f',mob,400,x,108. if i==1 else 100.);struct.pack_into('<3I',mob,572,124 if i==0 and scenario&4 else 123+i,kind,100000);struct.pack_into('<I',mob,592,0 if i==0 and scenario&8 else 1)
  if i==1:
   if scenario&32:struct.pack_into('<f',mob,508,2.)
   if scenario&64:struct.pack_into('<f',mob,524,2.)
   if scenario&128:struct.pack_into('<I',mob,548,1);struct.pack_into('<I',mob,568,3)
  u.mem_write(0xbef648+i*664,bytes(mob))
 u.mem_write(0xbe3080,struct.pack('<2f',100.,100.));u.mem_write(0xbe3098,struct.pack('<f',9. if scenario&16 else 10.));u.mem_write(0xbe30c0,struct.pack('<I',100));u.mem_write(0xbe30b8,struct.pack('<I',77));u.mem_write(0xc25dc8,struct.pack('<I',seed));u.mem_write(0xd42501+identity,bytes([not bool(scenario&512)]));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);ctx.update(scenario=scenario,damage=[0,0,0],cues=0,flee=out[33],push=[0]*9,mask=0);u.emu_start(0x111490,0x1000000,count=300000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
 expected=[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [24,128,64,76,60]]+[struct.unpack('<I',u.mem_read(0xc25dc8,4))[0]]+[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [68,160,124,200,192,72]]+ctx['damage']+[struct.unpack('<I',u.mem_read(0xbef8ac+i*664,4))[0]for i in range(3)]+ctx['push']+[ctx['mask'],ctx['cues']]+[100000]*3+[77,struct.unpack('<I',u.mem_read(0x3000000+212,4))[0]];actual=list(out)[:33]+[out[34]];assert actual==expected,(k,identity,jl,skill,rank,points,kind,scenario,[(i,a,b)for i,(a,b)in enumerate(zip(actual,expected))if a!=b]);cases+=1;armed+=out[6]!=0;pushes+=out[27]!=0
 if sum(ctx['damage']):coverage[skill]=coverage.get(skill,0)+1
assert all(coverage.get(skill,0)>0 for skill in [1,386,388,390,392])and armed and pushes,(coverage,armed,pushes)
(V/'Companion-Taekwon-Impact-Checks221.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,damageCoverage=coverage,stanceArmCases=armed,knockbackCases=pushes,scope='Original Daro/Haneul complete physical/stance resolver, actual native target eligibility, learning/proc/window and native element/defense/statuses; all original kick-family ratios and three-mob area boundaries, primary exclusion and exact secondary knockback requests. Exact cache, one-time own-SP payment, RNG, preparation, pending life and timing agree. Native persistence/line/flee/final HP and collision/knockback are explicit recording boundaries; actual battle and real movement/durable failure tests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original Daro/Haneul native stance preparation, kick areas/statuses and knockback requests; host only.')
