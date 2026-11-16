"""Compare original shared healing target helper with production support priorities."""
from pathlib import Path
import sys,struct,ctypes,json,random,subprocess
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x10000);u.mem_map(0x3000000,4096);u.mem_map(0x1000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000;ctx={}
blocked214=0
def hook214(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_EAX,0 if blocked214 else 1);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
u.hook_add(UC_HOOK_CODE,hook214,begin=0x95200,end=0x95200)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_heal_target_adapter214.c'),'-lm','-lz','-o',str(V/'companion_heal_target214.so')],check=True);lib=ctypes.CDLL(str(V/'companion_heal_target214.so'));U=ctypes.c_uint;lib.target214.restype=U;lib.target214.argtypes=[U]*4+[U*24];rng=random.Random(214);cases=0;coverage={}
for i in range(1800):
 preference=rng.randrange(3);hp=rng.choice([0,1,49,50,74,75,89,90,99,100]);maxhp=rng.choice([0,100]);blocked214=rng.randrange(2);rows=(U*24)();u.mem_write(0xd2f8b0,bytes(244*3))
 for j,identity in enumerate([4,13,1]):
  mapid=rng.choice([3,3,4]);initialized=rng.randrange(2);health=rng.choice([0,1,49,50,74,75,89,90,99,100]);maximum=rng.choice([0,100]);xx=100. if j==1 else rng.choice([100.,112.,292.,293.,400.]);yy=100.;m=bytearray(244)
  for off,val in [(0,identity),(4,mapid),(20,health),(28,maximum),(40,initialized)]:struct.pack_into('<I',m,off,val)
  struct.pack_into('<2f',m,164,xx,yy);u.mem_write(0xd2f8b0+j*244,bytes(m));vals=[identity,mapid,initialized,health,maximum,struct.unpack('<I',struct.pack('<f',xx))[0],struct.unpack('<I',struct.pack('<f',yy))[0],0]
  for k,value in enumerate(vals):rows[j*8+k]=value
 u.mem_write(0xd2fb8c,struct.pack('<I',3));u.mem_write(0xbec5ac,struct.pack('<I',3));u.mem_write(0xbe3080,struct.pack('<2f',100.,100.));u.mem_write(0xbe30b0,struct.pack('<2I',hp,maxhp));u.mem_write(0xd424ee+13,bytes([preference]));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0xd2f8b0+244);u.emu_start(0x1135e0,0x1000000,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000;expected=u.reg_read(UC_X86_REG_EAX);actual=lib.target214(preference,hp,maxhp,blocked214,rows);assert actual==expected,(i,preference,hp,maxhp,blocked214,list(rows),actual,expected);coverage[actual]=coverage.get(actual,0)+1;cases+=1
assert all(coverage.get(target,0)>0 for target in [0xfffffffe,0xffffffff,1,4,13]),coverage
(V/'Companion-Heal-Target-Checks214.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,targetCoverage=coverage,scope='Actual original shared support target helper: player/active ally/self priorities, preference thresholds and integer ratio ties, alive/initialized/map/full-HP filters, exact distance boundary and blocked-line fixture. Cast/payment behavior remains separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original companion healing target priorities; host only.')
