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
 if at in [0xca050,0x95200,0x94070]:result=0 if (at==0xca050 and ctx['scenario']&32) or (at!=0xca050 and ctx['scenario']&2) else 1
 elif at==0x95650:
  ptr=cpu.reg_read(UC_X86_REG_ECX);hp=cpu.reg_read(UC_X86_REG_EDX);points=struct.unpack('<I',cpu.mem_read(esp+4,4))[0];result=0 if ctx['scenario']&1 else 1
  if result:cpu.mem_write(ptr+20,struct.pack('<2I',hp,points))
 elif at==0x114540:
  life,damage,magic=struct.unpack('<3I',cpu.mem_read(esp+4,12));assert life==123 and magic==1;ctx['damage']=damage
  if ctx['scenario']&16:cpu.mem_write(0xbef88c,bytes(4))
 cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0xca050,0x95200,0x94070,0x95650,0x114540,0x114370]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_bolt_adapter204.c'),'-lm','-lz','-o',str(V/'companion_bolt204.so')],check=True);lib=ctypes.CDLL(str(V/'companion_bolt204.so'));U=ctypes.c_uint;lib.step204.argtypes=[U]*7+[U*7];rng=random.Random(204);cases=0
for skill in [3,9,21]:
 for k in range(400):
  rank=rng.randrange(1,11);remaining=rng.randrange(1,rank+1);points=rng.choice([0,1,10,50,500]);intelligence=rng.randrange(1,151);seed=rng.randrange(2**32);m=bytearray(244)
  for off,val in [(0,2),(4,3),(16,20),(20,100),(24,points),(48,50),(56,2),(60,remaining),(112,0),(124,123),(128,skill),(132,rank),(136,skill)]:struct.pack_into('<I',m,off,val)
  m[83]=intelligence
  for off,f in [(164,100.),(168,100.),(200,10.)]:struct.pack_into('<f',m,off,f)
  u.mem_write(0x3000000,bytes(m));u.mem_write(0xbef648,bytes(664));u.mem_write(0xbef884,struct.pack('<3I',123,0,100000));u.mem_write(0xbef7d8,struct.pack('<2f',112.,100.));u.mem_write(0xbe3098,struct.pack('<f',10.));u.mem_write(0xc25dc8,struct.pack('<I',seed));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);scenario=rng.choice([0,0,0,1,2,4,8,16,32]);ctx['scenario']=scenario
  if scenario&4:u.mem_write(0xbef7d8,struct.pack('<f',220.))
  if scenario&8:u.mem_write(0xbef884,struct.pack('<I',124))
  ctx['damage']=0;u.emu_start(0x111490,0x1000000,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
  expected=[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [24,128,60]]+[ctx['damage'],struct.unpack('<I',u.mem_read(0xc25dc8,4))[0]]+[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [200,192]]
  out=(U*7)();lib.step204(skill,rank,remaining,points,intelligence,seed,scenario,out);assert list(out)==expected,(skill,rank,remaining,points,intelligence,scenario,list(out),expected);cases+=1
(V/'Companion-Bolt-Impact-Checks204.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,scope='Actual native ordinary bolt impact compared to recovered C step: one SP debit, own INT/RNG, individual repeat rolls and exact repeat timing; failed save, blocked line, range, stale/dead/invalid targets. Final damage application and presentation use explicit recording callbacks here; remaining caster kit and target acceptance remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original ordinary bolt impacts and repeat timing; host only.')
