"""Compare full original area-cast construction and debit preflight to live C."""
from pathlib import Path
import sys,struct,ctypes,json,subprocess,random
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 row=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(row[1],x[row[3]:row[3]+row[4]])
u.mem_map(0x2000000,0x10000);u.mem_map(0x3000000,4096);u.mem_map(0x1000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000;ctx={}
def hook(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];result=1
 if at==0x137420:
  ptr,value,n=struct.unpack('<3I',cpu.mem_read(esp+4,12));cpu.mem_write(ptr,bytes([value&255])*n);result=ptr
 elif at==0x95650:
  result=not(ctx['scenario']&1)
  if result:cpu.mem_write(cpu.reg_read(UC_X86_REG_ECX)+20,struct.pack('<2I',cpu.reg_read(UC_X86_REG_EDX),struct.unpack('<I',cpu.mem_read(esp+4,4))[0]))
 elif at==0xca050:result=cpu.reg_read(UC_X86_REG_ECX)==0 and not(ctx['scenario']&16)
 elif at in [0x95200,0x94070]:result=not(ctx['scenario']&4)
 cpu.reg_write(UC_X86_REG_EAX,int(result));cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0x137420,0x95650,0xca050,0x95200,0x94070,0xa5c30]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_wizard_cast_adapter205.c'),'-lm','-lz','-o',str(V/'companion_wizard_cast205.so')],check=True);lib=ctypes.CDLL(str(V/'companion_wizard_cast205.so'));U=ctypes.c_uint;B=ctypes.c_ubyte;lib.cast205.argtypes=[U]*6+[U*3,B*6160];rng=random.Random(205);cases=0
for skill in [77,80]:
 for k in range(180):
  rank=rng.randrange(0,11);points=rng.choice([0,1,10,50,500]);intelligence=rng.randrange(1,151);seed=rng.randrange(2**32);scenario=rng.choice([0,0,0,1,2,4,8,16]);ctx['scenario']=scenario;m=bytearray(244)
  for off,val in [(0,2),(4,3),(16,20),(20,100),(24,points),(48,50),(56,9),(128,skill),(132,rank),(136,skill)]:struct.pack_into('<I',m,off,val)
  m[83]=intelligence
  for off,val in [(148,400. if scenario&8 else 160.),(152,100.),(164,100.),(168,100.),(200,10.)]:struct.pack_into('<f',m,off,val)
  u.mem_write(0x3000000,bytes(m));u.mem_write(0xc26070,bytes(6160*3))
  if scenario&2:
   for i in range(3):u.mem_write(0xc26070+i*6160+84,struct.pack('<I',1))
  u.mem_write(0xbef648,bytes(664));u.mem_write(0xbef7d8,struct.pack('<2f',160.,100.));u.mem_write(0xbef884,struct.pack('<3I',123,0,100000));u.mem_write(0xbe3098,struct.pack('<f',10.));u.mem_write(0xc25dc8,struct.pack('<I',seed));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);u.emu_start(0x111490,0x1000000,count=200000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
  expected=[struct.unpack('<I',u.mem_read(0x3000000+off,4))[0]for off in [24,128]]+[struct.unpack('<I',u.mem_read(0xc25dc8,4))[0]];out=(U*3)();field=(B*6160)();lib.cast205(skill,rank,points,intelligence,seed,scenario,out,field);assert list(out)==expected,(skill,rank,points,intelligence,scenario,list(out),expected);native=bytes(u.mem_read(0xc26070,6160));assert bytes(field)==native,(skill,rank,scenario,[(i,field[i],native[i])for i in range(6160)if field[i]!=native[i]][:12]);cases+=1
(V/'Companion-Wizard-Cast-Checks205.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,fieldBytes=6160,scope='Original complete field record, own power RNG, single SP debit, failed allocation, blocked/range/target/capacity preflight. Native target-validity and line hooks are explicit fixture inputs; cosmetic audio is muted.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original companion wizard area creation and resource preflight; host only.')
