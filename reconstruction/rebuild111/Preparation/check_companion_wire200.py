"""RPV3 and RPV2 migration parity against the actual original native reader."""
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
 if at==0x93460:
  high,out,n=struct.unpack('<3I',cpu.mem_read(esp+4,12));assert high==0xeca20000
  if n==len(ctx['raw']):cpu.mem_write(out,ctx['raw']);cpu.reg_write(UC_X86_REG_EAX,1)
  else:cpu.reg_write(UC_X86_REG_EAX,0xffffffff)
 elif at==0x13d320:
  seed,ptr,n=struct.unpack('<3I',cpu.mem_read(esp+4,12));cpu.reg_write(UC_X86_REG_EAX,zlib.crc32(bytes(cpu.mem_read(ptr,n)),seed))
 else:raise AssertionError(hex(at))
 ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in[0x93460,0x13d320]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(R/'Validation/companion_wire_adapter200.c'),'-lz','-o',str(R/'Validation/companion_wire200.so')],check=True)
lib=ctypes.CDLL(str(R/'Validation/companion_wire200.so'));lib.companion_decode200.argtypes=[ctypes.c_void_p,ctypes.c_uint,ctypes.c_void_p];rng=random.Random(200);cases=valid=legacy=0
jobs=struct.unpack_from('<19I',x,0x2a7984-65536);assert jobs==(7,1,2,10,3,18,12,4,14,15,16,19,20,40,41,42,43,44,45)
def seal(b):struct.pack_into('<I',b,len(b)-4,zlib.crc32(b[:-4]));return bytes(b)
def check(raw):
 global cases,valid,legacy
 ctx['raw']=raw;u.mem_write(0x3000000,b'\xa5'*640);u.mem_write(0x3010000,struct.pack('<5I',0x3011000 if raw else 0,int(bool(raw)),1,0,0))
 if raw:u.mem_write(0x3011000,struct.pack('<QIIqII',0xeca20000f219bc63,0,2,0,0x3012000,len(raw)*2))
 u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3010000);u.reg_write(UC_X86_REG_EDX,0x3000000);u.emu_start(0x92ae0,0x1000000,count=200000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
 expected=ctypes.c_int(u.reg_read(UC_X86_REG_EAX)).value;buf=ctypes.create_string_buffer(raw or b'\0');out=ctypes.create_string_buffer(b'\xa5'*640,640);actual=lib.companion_decode200(buf,len(raw),out);assert actual==expected,(len(raw),actual,expected,raw[:20].hex())
 if actual>=0:assert out.raw==bytes(u.mem_read(0x3000000,640));valid+=1;legacy+=len(raw)==256
 else:assert out.raw==b'\xa5'*640
 cases+=1
check(b'')
for version,size in[(2,256),(3,640)]:
 for sample in range(150):
  b=bytearray(size);b[:4]=b'RPV2'if version==2 else b'RPV3';b[4]=1;mask=rng.randrange(1<<19);struct.pack_into('<I',b,8,mask)
  if version==3:struct.pack_into('<I',b,12,rng.randrange(37))
  for i in range(19):
   if mask>>i&1:
    if version==2:struct.pack_into('<3I',b,12+i*12,rng.randrange(1,251),rng.randrange(2000000001),rng.randrange(2000000001))
    else:struct.pack_into('<8I',b,16+i*32,rng.randrange(1,251),rng.randrange(0x80000000),rng.randrange(1,100),rng.randrange(0x80000000),rng.randrange(46),rng.randrange(2000000001),rng.randrange(2000000001),0)
  raw=seal(b);check(raw)
  for at in[0,4,5,8,size-5,rng.randrange(size-4)]:
   corrupt=bytearray(raw);corrupt[at]^=255;check(seal(corrupt));check(bytes(corrupt[:-1]))
(R/'Validation/Companion-Wire-Checks200.json').write_text(json.dumps(dict(passed=True,cases=cases,acceptedCases=valid,legacyMigrations=legacy,wireBytes=640,sourceSHA256=hashlib.sha256((R/'Source/companion_progress200.h').read_bytes()).hexdigest(),scope='Native RPV3 record validation and exact RPV2 migration versus editable C, including rechecksummed malformed fields and truncation. Sparse-state commits, growth awards, promotions and battle/formation callers require further integration.',runtimeCallersIntegrated=False,originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS exact original companion growth-record decoding and legacy migration; host CPU reference only.')
