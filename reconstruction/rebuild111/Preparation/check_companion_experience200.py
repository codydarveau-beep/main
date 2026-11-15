"""Compare actual original active-party EXP awards with recovered C arithmetic."""
from pathlib import Path
import sys,struct,json,subprocess,ctypes,zlib,random,hashlib
R=Path(__file__).resolve().parent.parent;sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-b+i*56)for i in range(n)]
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for s in ss:u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);u.mem_map(0x3000000,0x20000);u.mem_map(0x1000000,4096);sp=0x2008000;u.reg_write(UC_X86_REG_CR4,0x200);ctx={}
def hook(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP)
 if at==0x92ae0:cpu.mem_write(cpu.reg_read(UC_X86_REG_EDX),ctx['raw']);cpu.reg_write(UC_X86_REG_EAX,1)
 elif at==0x91ff0:
  high,index,kind,lo,hi,ptr,n=struct.unpack('<7I',cpu.mem_read(esp+4,28));assert(high,index,kind,n)==(0xeca20000,0,2,1280);ctx['raw']=bytes.fromhex(bytes(cpu.mem_read(ptr,n)).decode());cpu.reg_write(UC_X86_REG_EAX,1)
 elif at==0x13d320:
  seed,ptr,n=struct.unpack('<3I',cpu.mem_read(esp+4,12));cpu.reg_write(UC_X86_REG_EAX,zlib.crc32(bytes(cpu.mem_read(ptr,n)),seed))
 elif at==0x74540:raise AssertionError('Unexpected failed native growth commit')
 else:raise AssertionError(hex(at))
 ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in[0x92ae0,0x91ff0,0x13d320,0x74540]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(R/'Validation/companion_exp_adapter200.c'),'-lm','-lz','-o',str(R/'Validation/companion_exp200.so')],check=True);lib=ctypes.CDLL(str(R/'Validation/companion_exp200.so'));U=ctypes.c_uint;lib.companion_gain200.argtypes=[ctypes.c_void_p,U,ctypes.c_int,ctypes.c_int,U,U]
initial=struct.unpack_from('<19I',x,0x2a7984-65536);final=[7,11,9,10,17,18,12,13,14,15,16,19,20];promoted=struct.unpack_from('<13I',x,0x5e593c-65536);rng=random.Random(200);cases=0
for identity in range(19):
 for job in{initial[identity],final[identity]if identity<13 else initial[identity],promoted[identity]if identity<13 else initial[identity]}:
  for level in[1,49,89,90,99,150,249,250]:
   for amount in[0,1,12345,2000000000]:
    jobLevel=rng.choice([1,2,49,50,69,70,99]);exp=rng.randrange(100000);jobExp=rng.randrange(10000);baseRate=rng.choice([0,10,300,1000]);jobRate=rng.choice([0,10,300]);hp,sp0=12,8
    raw=bytearray(640);raw[:4]=b'RPV3';raw[4]=1;struct.pack_into('<I',raw,8,1<<identity);struct.pack_into('<8I',raw,16+identity*32,level,exp,jobLevel,jobExp,job,hp,sp0,0);struct.pack_into('<I',raw,636,zlib.crc32(raw[:636]));ctx['raw']=bytes(raw)
    member=bytearray(244);struct.pack_into('<11I',member,0,identity,3,0,0,level,hp,sp0,100,100,1,1);struct.pack_into('<4I',member,44,exp,jobLevel,jobExp,job);struct.pack_into('<2f',member,164,100,100);u.mem_write(0xd2f8b0,bytes(member));u.mem_write(0xd2fb8c,struct.pack('<I',1));u.mem_write(0xd424d4,struct.pack('<I',0x12345));u.mem_write(0xbde5e0+0xdfcc,struct.pack('<I',3));u.mem_write(0xbda14c,struct.pack('<2I',baseRate,jobRate));u.mem_write(sp,struct.pack('<II2fI',0x1000000,amount//2,100.,100.,0));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0xbde5e0);u.reg_write(UC_X86_REG_EDX,amount);u.emu_start(0x92470,0x1000000,count=1000000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000 and u.reg_read(UC_X86_REG_EAX)==1
    out=ctypes.create_string_buffer(bytes(raw),640);lib.companion_gain200(out,identity,amount,amount//2,baseRate,jobRate);assert out.raw==ctx['raw'],(identity,job,level,jobLevel,amount,baseRate,jobRate,struct.unpack_from('<8I',out.raw,16+identity*32),struct.unpack_from('<8I',ctx['raw'],16+identity*32));cases+=1
 print('Independent EXP growth checked',identity+1,'/19',flush=True)
(R/'Validation/Companion-Experience-Checks200.json').write_text(json.dumps(dict(passed=True,cases=cases,personalities=19,sourceSHA256=hashlib.sha256((R/'Source/companion_experience200.h').read_bytes()).hexdigest(),scope='Full original active-member EXP function with durable-state adapters versus C; own level/job curves, rate settings, caps and level-up resources. Eligibility and actual battle/formation persistence require separate runtime checks.',runtimeCallersIntegrated=False,originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original independent companion base/job EXP and level progression; host CPU reference only.')
