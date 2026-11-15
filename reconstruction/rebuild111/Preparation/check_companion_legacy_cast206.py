"""Compare native first-pair Holy Light fee callers, including promoted healer records."""
from pathlib import Path
import sys,struct,subprocess,ctypes,json,random
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 row=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(row[1],x[row[3]:row[3]+row[4]])
u.mem_map(0x2000000,0x10000);u.mem_map(0x3000000,4096);u.mem_map(0x1000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000
# Resolve actual fee and own power; final damage/presentation are recorded elsewhere.
def hook(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0]
 if at==0x95650:cpu.mem_write(cpu.reg_read(UC_X86_REG_ECX)+20,struct.pack('<2I',cpu.reg_read(UC_X86_REG_EDX),struct.unpack('<I',cpu.mem_read(esp+4,4))[0]))
 cpu.reg_write(UC_X86_REG_EAX,1);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0xca050,0x94070,0x95200,0x95650,0x114540,0x114370]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_legacy_cast_adapter206.c'),'-lm','-lz','-o',str(V/'companion_legacy_cast206.so')],check=True);lib=ctypes.CDLL(str(V/'companion_legacy_cast206.so'));U=ctypes.c_uint;lib.legacy206.argtypes=[U]*4+[U*4];rng=random.Random(206);cases=0
for job,jl in [(3,2),(3,50),(17,1),(17,50),(24,1),(24,50),(24,70)]:
 for points in [0,10,12,14,15,50,500]:
  seed=rng.randrange(2**32);m=bytearray(244)
  for off,val in [(0,4),(4,3),(16,20),(20,100),(24,points),(48,jl),(56,job),(124,123),(128,51),(132,1),(136,51)]:struct.pack_into('<I',m,off,val)
  m[83]=30
  for off,val in [(164,100.),(168,100.),(200,10.)]:struct.pack_into('<f',m,off,val)
  u.mem_write(0x3000000,bytes(m));u.mem_write(0xbef648,bytes(664));u.mem_write(0xbef884,struct.pack('<3I',123,0,100000));u.mem_write(0xbef7d8,struct.pack('<2f',112.,100.));u.mem_write(0xbe3098,struct.pack('<f',10.));u.mem_write(0xbe30b8,struct.pack('<I',77));u.mem_write(0xc25dc8,struct.pack('<I',seed));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);u.emu_start(0x111490,0x1000000,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000;expected=[struct.unpack('<I',u.mem_read(at,4))[0]for at in [0x3000018,0x3000080,0xc25dc8,0xbe30b8]];out=(U*4)();lib.legacy206(job,jl,points,seed,out);assert list(out)==expected,(job,jl,points,list(out),expected);cases+=1
# Execute the original inline starting-technique rank floor, with real native learning.
def memset206(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret,dest,value,count=struct.unpack('<4I',cpu.mem_read(esp,16));cpu.mem_write(dest,bytes([value&255])*count);cpu.reg_write(UC_X86_REG_EAX,dest);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
u.hook_add(UC_HOOK_CODE,memset206,begin=0x137420,end=0x137420)
lib.basic206.argtypes=[U]*3;rankCases=0
for identity,jobs in [(1,[1,11,22]),(4,[3,17,24])]:
 for job in jobs:
  for jl in [0,1,2,10,49,50,70,100]:
   m=bytearray(244);struct.pack_into('<I',m,0,identity);struct.pack_into('<I',m,48,jl);struct.pack_into('<I',m,56,job);u.mem_write(0x3000000,bytes(m));u.mem_write(sp+0x90,struct.pack('<I',identity));u.mem_write(sp+0xf0,struct.pack('<I',0x3000000));u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0x30971,0x309a0,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x309a0;expected=u.reg_read(UC_X86_REG_EBX);assert lib.basic206(identity,job,jl)==expected,(identity,job,jl,expected);rankCases+=1
(V/'Companion-Legacy-Cast-Checks206.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,startingTechniqueComparisons=rankCases,scope='Actual original first-pair Holy Light impact caller across starting/promoted jobs, including learned Meditation, exact SP boundary and unchanged player SP. Generic caster-cost helper remains separate from this original fixed-fee caller.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original first-pair cast caller fees across promotions; host only.')
