"""Compare original companion field callback, damage and statuses with live C."""
from pathlib import Path
import sys,struct,ctypes,json,subprocess,random
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-b+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x10000);u.mem_map(0x3000000,0x2000);u.mem_map(0x5000000,0x60000);u.mem_map(0x1000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000;g=0x5000000;f=0x3000000
# Cosmetic sound callbacks only; actual native damage, status and RNG code executes.
def quiet(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
u.hook_add(UC_HOOK_CODE,quiet,begin=0x676a0,end=0x676a0)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'companion_wizard_adapter205.c'),'-lm','-lz','-o',str(V/'companion_wizard205.so')],check=True);lib=ctypes.CDLL(str(V/'companion_wizard205.so'));U=ctypes.c_uint;lib.wizard205_step.argtypes=[U]*8+[U*15];rng=random.Random(205);cases=0
for skill in [77,80]:
 for k in range(240):
  rank=rng.randrange(1,11);kind=rng.choice([0,1,2,5,20,100,200,500]);power=rng.randrange(20,2000);seed=rng.randrange(2**32);luk=rng.randrange(1,151);hits=rng.choice([0,1,2,3,249,250]);flags=rng.randrange(32);image=bytearray(0x60000)
  def word(off,val):struct.pack_into('<I',image,off,val)
  def flt(off,val):struct.pack_into('<f',image,off,val)
  word(0x10,50);word(0xdfcc,3);word(0x4ad0,100);flt(0x4ab8,10.);flt(0x4aa0,100.);flt(0x4aa4,100.);word(0x477e8,seed);word(0x112a8,kind);word(0x112ac,100000);word(0x112a4,123);word(0x112b8,1);flt(0x111f8,160.);flt(0x111fc,100.);image[0x11228]=hits
  for bit,off in [(1,0x11130),(2,0x1112c),(4,0x111d0),(8,0x110f4),(16,0x11118)]:
   if flags&bit:flt(off,20.)
  if flags&4:word(0x111d8,3)
  u.mem_write(g,bytes(image));member=bytearray(244);struct.pack_into('<2I',member,0,2,3);struct.pack_into('<I',member,136,3);struct.pack_into('<I',member,16,20);member[85]=luk;u.mem_write(0xd2f8b0,bytes(member));u.mem_write(0xd2fb8c,struct.pack('<I',1));field=bytearray(6160)
  for off,val in [(88,power),(96,skill),(100,rank),(108,3)]:struct.pack_into('<I',field,off,val)
  u.mem_write(f,bytes(field));u.mem_write(sp,struct.pack('<4I',0x1000000,g,f,0));u.reg_write(UC_X86_REG_ESP,sp)
  try:u.emu_start(0x6b630,0x1000000,count=200000)
  except Exception as error:raise AssertionError((skill,kind,hex(u.reg_read(UC_X86_REG_EIP)),str(error)))
  assert u.reg_read(UC_X86_REG_EIP)==0x1000000
  read=lambda off:struct.unpack('<I',u.mem_read(g+off,4))[0]
  expected=[u.reg_read(UC_X86_REG_EAX),read(0x112ac),read(0x11264),read(0x1126c),u.mem_read(g+0x11228,1)[0],read(0x1122c),read(0x11230),read(0x11238),read(0x11064)]
  if expected[8]:event=0x10d64+((expected[8]-1)%16)*48;expected +=[read(event+16),read(event+20)]
  else:expected +=[0,0]
  expected +=[read(0x112b0),read(0x111e8),struct.unpack('<I',u.mem_read(0xd2f938,4))[0],read(0x477e8)]
  out=(U*15)();lib.wizard205_step(skill,rank,kind,power,seed,luk,hits,flags,out);assert list(out)==expected,(skill,rank,kind,power,seed,luk,hits,flags,list(out),expected);cases+=1
(V/'Companion-Wizard-Checks205.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,scope='Actual original companion-owned wizard callback, final native damage, resistances, Lex, blind/freeze counters and durations, ownership/aggro and RNG versus live C. Native sound dispatch is muted in the oracle; target playtesting remains separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original companion field damage and statuses; native CPU reference and host C only.')
