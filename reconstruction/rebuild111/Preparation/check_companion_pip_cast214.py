"""Compare original Pip healing caller with production support initialization."""
from pathlib import Path
import sys,struct,ctypes,json,random,subprocess
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x10000);u.mem_map(0x3000000,4096);u.mem_map(0x1000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000;ctx={}
ctx={}
def hook214(cpu,at,size,user):
 if at==0x111490:ctx['resolved']=1;cpu.emu_stop();return
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];result=1
 if at==0x95200:result=0 if ctx['blocked'] else 1
 elif at==0x137420:
  dest,value,count=struct.unpack('<3I',cpu.mem_read(esp+4,12));cpu.mem_write(dest,bytes([value&255])*count);result=dest
 elif at==0x95650:
  result=0 if ctx['failed'] else 1
  if result:cpu.mem_write(cpu.reg_read(UC_X86_REG_ECX)+20,struct.pack('<2I',cpu.reg_read(UC_X86_REG_EDX),struct.unpack('<I',cpu.mem_read(esp+4,4))[0]))
 cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0x95200,0x95650,0x137420,0x111490]:u.hook_add(UC_HOOK_CODE,hook214,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_pip_adapter214.c'),'-lm','-lz','-o',str(V/'companion_pip214.so')],check=True);lib=ctypes.CDLL(str(V/'companion_pip214.so'));U=ctypes.c_uint;lib.pip214.argtypes=[U]*9+[U*14];rng=random.Random(1414);cases=0;coverage={}
for i in range(1200):
 jl=rng.choice([1,2,10,20,49,50,70,99]);points=rng.choice([0,1,10,12,30,50,100,500]);preference=rng.randrange(3);enabled=rng.randrange(2);cooling=rng.randrange(2);distance=rng.choice([0,32,63,64,65,72,80]);recipient=rng.randrange(4);blocked=rng.randrange(2);failed=rng.randrange(2);m=bytearray(244)
 for off,val in [(0,13),(4,3),(16,90),(20,1 if recipient==2 else 100),(24,points),(28,100),(36,1234),(40,1),(48,jl),(56,40)]:struct.pack_into('<I',m,off,val)
 for off,f in [(164,100.+distance),(168,100.),(212,11. if cooling else 0.)]:struct.pack_into('<f',m,off,f)
 a=bytearray(244)
 for off,val in [(0,4),(4,3),(20,1 if recipient==1 else 100),(28,100),(36,123),(40,1)]:struct.pack_into('<I',a,off,val)
 struct.pack_into('<2f',a,164,100.,100.);u.mem_write(0xd2f8b0,bytes(m+a));u.mem_write(0xd2fb8c,struct.pack('<I',2));u.mem_write(0xbec5ac,struct.pack('<I',3));u.mem_write(0xbe3080,struct.pack('<2f',100.,100.));u.mem_write(0xbe3098,struct.pack('<f',10.));u.mem_write(0xbe30b0,struct.pack('<3I',1 if recipient==0 else 1000,1000,77));u.mem_write(0xd424ee+13,bytes([preference]));u.mem_write(0xd42501+13,bytes([enabled]));u.mem_write(sp,bytes(0x3400))
 for off,val in [(0x40,0),(0x70,0xd2f8b0+20),(0x90,13),(0xa0,0xd2f8b0+8),(0xf0,0xd2f8b0),(0x100,0xd2f8b0+164),(0xd0,0xd2f8b0+168),(0x160,0xd2f8b0+12)]:u.mem_write(sp+off,struct.pack('<I',val))
 ctx.update(blocked=blocked,failed=failed,resolved=0);u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0x3298c,0x333c3,count=100000);assert u.reg_read(UC_X86_REG_EIP) in [0x333c3,0x111490];expected=[struct.unpack('<I',u.mem_read(0xd2f8b0+off,4))[0]for off in [24,128,132,116,124,136,188,192,196,200,204,212]]+[ctx['resolved'],77];out=(U*14)();lib.pip214(jl,points,preference,enabled,cooling,distance,recipient,blocked,failed,out);assert list(out)==expected,(jl,points,preference,enabled,cooling,distance,recipient,blocked,failed,list(out),expected);coverage[ctx['resolved']]=coverage.get(ctx['resolved'],0)+1;cases+=1
assert len(coverage)==2,coverage
(V/'Companion-Pip-Cast-Checks214.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,choiceCoverage=coverage,scope='Actual original Pip support branch with real native learning/target selection versus production helper: original raw Heal cost, learned-rank gating, player/ally/self/full-HP targets, range64/cooldown/preferences/line, failed save, exact timing/target life capture and unchanged player SP. Resolution is explicitly recorded at the caller boundary; actual Heal and physical integration remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original Pip support choice/payment/initiation; host only.')
