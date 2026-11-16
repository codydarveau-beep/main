"""Released campaign record/native career guard and legacy sandbox compatibility.
Independent Python wire fixtures; actual native record reader and guard execute.
"""
from pathlib import Path
import sys,struct,json,ctypes,subprocess,zlib,random
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
world=(S/'campaign_world200.h').read_text();(V/'actual_job_guard228.inc').write_text('/* Exact production career guard. */\n'+next(l for l in world.splitlines() if l.startswith('static int campaign_job_guard200('))+'\n')
subprocess.run(['cc','-O1','-shared','-fPIC','-I'+str(S),str(V/'campaign_save_adapter228.c'),'-lm','-lz','-o',str(V/'campaign_save228.so')],check=True)
lib=ctypes.CDLL(str(V/'campaign_save228.so'));U=ctypes.c_uint;lib.save228.argtypes=[ctypes.c_void_p,U,U,U*5]
x=(R.parent/'packet194/released-default.xbe').read_bytes();base=struct.unpack_from('<I',x,0x104)[0];n,table=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 sec=struct.unpack_from('<14I',x,table-base+i*56);u.mem_write(sec[1],x[sec[3]:sec[3]+sec[4]])
u.mem_map(0x2000000,0x20000);u.mem_map(0x3000000,0x30000);u.mem_map(0x1000000,4096);u.reg_write(UC_X86_REG_CR4,0x200);sp=0x2008000
# A denied job may print its original notice; only that display boundary is recorded.
def notice(cpu,at,size,data):
 esp=cpu.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_EAX,0);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
u.hook_add(UC_HOOK_CODE,notice,begin=0x74540,end=0x74540)
def wire(cursor,route,lineage,objectives,checkpoint=0):
 b=bytearray(64);b[:4]=b'ROC2';b[4]=1;b[8:12]=bytes([cursor,route,lineage,checkpoint]);struct.pack_into('<II',b,12,(1<<19)-1,objectives);b[20:28]=b'Recovery';struct.pack_into('<I',b,60,zlib.crc32(b[:60]));return bytes(b.hex(),'ascii')
def install(text):
 u.mem_write(0x3000000,struct.pack('<5I',0x3001000,int(bool(text)),1,len(text),1));u.mem_write(0x3001000,struct.pack('<QIIqII',0xeca20000f219bc61,0,2,0,0x3002000,len(text)));u.mem_write(0x3002000,text+b'\0');u.mem_write(0xd34020,struct.pack('<I',0x3000000))
fixtures=[b'']
for cursor in [0,1,2,12,15,27,35,36]:
 for lineage in [0,1,2,3,4,5,6,40,41,42,43]:
  route=0 if not lineage else 1
  for flags in [0,1,0x80000000,0x80000001,0xffffffff]:fixtures.append(wire(cursor,route,lineage,flags))
# Correctly checksummed malformed fields and actual CRC/length corruption.
fixtures.extend([wire(37,1,1,0),wire(36,0,0,0x80000000),b'0'*128,b'G'*128,wire(36,1,1,0x80000000)[:-2]])
cases=sandbox=0
for text in fixtures:
 install(text);u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,0x3000000);u.reg_write(UC_X86_REG_EDX,0x3010000);u.emu_start(0x919b0,0x1000000,count=200000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000;expected=u.reg_read(UC_X86_REG_EAX);loaded=struct.unpack('<6I',u.mem_read(0x3010000,24)) if expected==1 else None;legacy=bool(loaded and loaded[0]==36 and loaded[4]&0x80000000)
 for job in [0,1,2,3,4,5,6,7,8,11,17,22,33,40,41,42,43,44,45]:
  out=(U*5)();lib.save228(text,len(text),job,out);assert out[0]==expected,(text,out[0],expected);assert out[1]==out[2]==out[4]==legacy,(text,list(out),loaded)
  u.mem_write(sp,struct.pack('<3I',0x1000000,0x3020000,job));u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0x67b60,0x1000000,count=500000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000;allowed=u.reg_read(UC_X86_REG_EAX);assert out[3]==allowed,(text,job,list(out),allowed);cases+=1;sandbox+=legacy
(V/'Campaign-Save-Checks228.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,legacySandboxCases=sandbox,scope='Independent ROC2 wire fixtures through the actual original native record reader and native career guard, against production load/predicate/guard. Native display notice is the sole emulation recording boundary. Covers malformed/absent/corrupt records, Super Novice high-bit distinction, canonical legacy sandbox, read-only sparse-state roundtrip, sandbox objective warning and no campaign reward backpay. Full bundled character/alternating disk-save compatibility and real FATX saves remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original campaign save reader, native job guard and legacy sandbox preservation; host CPU only.')
