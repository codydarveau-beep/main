"""Actual scene transition semantics against independent preserved native code.
Host CPU replay and C execution, not Xbox/Xemu playtesting.
"""
from pathlib import Path
import sys,struct,json,subprocess,ctypes,re,zlib,random,hashlib
R=Path(__file__).resolve().parent.parent;sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-b+i*56)for i in range(n)]
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for s in ss:u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);u.mem_map(0x3000000,0x10000);u.mem_map(0x1000000,4096);sp=0x2008000;u.reg_write(UC_X86_REG_CR4,0x200);ctx={}
def hook(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP)
 if at==0x919b0:cpu.mem_write(cpu.reg_read(UC_X86_REG_EDX),ctx['state']);cpu.reg_write(UC_X86_REG_EAX,1)
 elif at==0x91cc0:
  incoming=bytes(cpu.mem_read(cpu.reg_read(UC_X86_REG_EDX),52));denied=ctx['fail'] and incoming!=ctx['state']
  if not denied:ctx['state']=incoming
  cpu.reg_write(UC_X86_REG_EAX,0 if denied else 1)
 elif at==0x133f30:pass
 else:raise AssertionError(hex(at))
 ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in[0x919b0,0x91cc0,0x133f30]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(R/'Validation/scene_poll_adapter200.c'),'-lm','-lz','-o',str(R/'Validation/scene_poll200.so')],check=True)
lib=ctypes.CDLL(str(R/'Validation/scene_poll200.so'));U=ctypes.c_uint;lib.scene_poll_reference200.argtypes=[ctypes.c_void_p,*([U]*8),U*6]
index=re.findall(r'\{(\d+)u?,(\d+)u?,(\d+)u?,(\d+)u?\}',(R/'Source/chapter1_data200.h').read_text())[:36];packed=(R/'Recovered195/chapter1.bin').read_bytes();cases=[];rng=random.Random(200)
for cursor,row in enumerate(index):
 off,n,raw,crc=map(int,row);data=zlib.decompress(packed[off:off+n]);assert len(data)==raw and zlib.crc32(data)==crc;nodes=struct.unpack_from('<H',data,6)[0];buf=ctypes.create_string_buffer(data)
 for node in range(nodes):
  required=struct.unpack_from('<I',data,16+node*32+24)[0]
  for role in[1,2,3]:
   for objectives in sorted({0,1,required,required|1,0xffffffff,rng.getrandbits(12)}):
    for fail in[0,1]:
     named=(node+role)%2;recruits=0x12 if cursor>=3 else 0;ctx.update(state=struct.pack('<6I',cursor,role,role,recruits,objectives,node)+(b'Recovery'+bytes(20)if named else bytes(28)),fail=fail)
     u.mem_write(0x3000000,data);u.mem_write(0xd42a28,struct.pack('<7I',0x12345,0x3000000,len(data),nodes,16+nodes*32,cursor,1));u.mem_write(sp,struct.pack('<I',0x1000000));u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0xc9bd0,0x1000000,count=200000);assert u.reg_read(UC_X86_REG_EIP)==0x1000000
     c=struct.unpack_from('<6I',ctx['state']);expected=[u.reg_read(UC_X86_REG_EAX),c[0],c[5],c[4],c[3],int(struct.unpack('<I',u.mem_read(0xd42a2c,4))[0]!=0)];out=(U*6)();lib.scene_poll_reference200(buf,len(data),cursor,role,node,objectives,recruits,named,fail,out)
     assert list(out)==expected,(cursor,node,role,hex(objectives),named,fail,list(out),expected)
     cases.append([cursor,node,role,objectives,recruits,named,fail,*expected])
 print('Scene transition records checked',cursor+1,'/36',flush=True)
(R/'Validation/scene_poll_fixtures200.h').write_text('/* Independent released-code scene outcomes. */\nstatic const unsigned scenePollFixtures200[][13]={\n'+''.join('{'+','.join(str(v)+'u'for v in case)+'},\n'for case in cases)+'};\n')
(R/'Validation/Scene-Transition-Checks200.json').write_text(json.dumps(dict(passed=True,cases=len(cases),packedScenes=36,roles=3,failedWritesChecked=True,sourceSHA256=hashlib.sha256((R/'Source/campaign_scene200.h').read_bytes()).hexdigest(),scope='Every authored node through actual C polling versus independent original native scene polling. This does not establish world/actor/camera integration or companion behavior.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS independent original scene transition/state parity; host only.')
