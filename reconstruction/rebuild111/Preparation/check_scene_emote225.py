"""Exact original main-loop scene-emote queue versus production presentation code."""
from pathlib import Path
import sys,struct,ctypes,json,subprocess,re,zlib,random
R=Path(__file__).resolve().parent.parent;V=R/'Validation';sys.path.insert(0,str(R.parent/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
x=(R.parent/'packet194/released-default.xbe').read_bytes();base=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for i in range(n):
 s=struct.unpack_from('<14I',x,t-base+i*56);u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);u.mem_map(0x3000000,0x20000);sp=0x2008000;u.reg_write(UC_X86_REG_CR4,0x200);ctx={}
def hook(cpu,at,size,user):
 esp=cpu.reg_read(UC_X86_REG_ESP)
 if at==0xc9a70:result=ctx['status']
 elif at==0x919b0:cpu.mem_write(cpu.reg_read(UC_X86_REG_EDX),ctx['state']);result=1
 else:raise AssertionError(hex(at))
 ret=struct.unpack('<I',cpu.mem_read(esp,4))[0];cpu.reg_write(UC_X86_REG_EAX,result);cpu.reg_write(UC_X86_REG_ESP,esp+4);cpu.reg_write(UC_X86_REG_EIP,ret)
for at in [0xc9a70,0x919b0]:u.hook_add(UC_HOOK_CODE,hook,begin=at,end=at)
subprocess.run(['cc','-O2','-shared','-fPIC','-I'+str(R/'Source'),str(V/'scene_emote_adapter225.c'),'-lm','-lz','-o',str(V/'scene_emote225.so')],check=True);lib=ctypes.CDLL(str(V/'scene_emote225.so'));U=ctypes.c_uint;B=ctypes.c_ubyte;lib.emote225.argtypes=[ctypes.c_void_p]+[U]*7+[ctypes.c_float,U,B*108]
flat=(R.parent/'decompiler203/native-flat203.bin').read_bytes();names={}
for i in range(19):
 p=struct.unpack_from('<I',flat,0x2a78a0+i*12-65536)[0];names[flat[p-65536:].split(b'\0',1)[0].decode()]=i
rows=re.findall(r'\{(\d+)u?,(\d+)u?,(\d+)u?,(\d+)u?\}',(R/'Source/chapter1_data200.h').read_text())[:36];pack=(R/'Recovered195/chapter1.bin').read_bytes();rng=random.Random(225);cases=emissions=0;cueIDs=set();contexts={}
packets=[]
for cursor,row in enumerate(rows):
 at,n,raw,crc=map(int,row);data=zlib.decompress(pack[at:at+n]);assert len(data)==raw and zlib.crc32(data)==crc;packets.append((cursor,data,False))
# Player support exists in the original presentation resolver even though the
# surviving authored cues target other speakers. Exercise it without editing assets.
cursor,data,_=packets[0];player=bytearray(data);count=struct.unpack_from('<H',player,6)[0];node=next(i for i in range(count)if player[16+i*32]==1);oldPool=struct.unpack_from('<I',player,8)[0];struct.pack_into('<I',player,16+node*32+4,oldPool);struct.pack_into('<I',player,16+node*32+28,6<<8);player.extend(b'Player\0');struct.pack_into('<I',player,8,oldPool+7);packets.append((cursor,bytes(player),True))
for cursor,data,synthetic in packets:
 count=struct.unpack_from('<H',data,6)[0];pool=16+count*32;buf=ctypes.create_string_buffer(data)
 for node in range(count):
  if data[16+node*32]!=1:continue
  word=struct.unpack_from('<I',data,16+node*32+28)[0];speakerAt=struct.unpack_from('<I',data,16+node*32+4)[0];speaker=data[pool+speakerAt:].split(b'\0',1)[0].decode()
  for kind in range(7):
   for variant in range(3 if word>255 else 1):
    status=1 if variant<2 else rng.choice([0,2,3,5]);flags=0 if synthetic and variant==0 else rng.randrange(8);paused=int(variant==1 and rng.randrange(3)==0);dt=rng.choice([0.,.016, .05,4.,4.001]);mapId=rng.choice([3,7,495]);repeat=variant==1;wire=bytearray(108)
    for i in range(4):struct.pack_into('<3I3f',wire,i*24,1 if i%2 else 0,i,mapId if i<3 else mapId+1,rng.choice([0.,3.99,4.,4.001]),float(i),float(i+1))
    nextSlot=rng.randrange(12);struct.pack_into('<3I',wire,96,nextSlot,cursor if repeat else 0xffffffff,node if repeat else 0xffffffff);actual=(B*108).from_buffer_copy(wire);lib.emote225(buf,len(data),cursor,node,mapId,status,kind,flags,dt,paused,actual)
    u.mem_write(0x3000000,data);u.mem_write(0xd42a28,struct.pack('<7I',0x3010000,0x3000000,len(data),count,pool,cursor,1));u.mem_write(0xd34020,struct.pack('<I',0x3010000));u.mem_write(0xbec5ac,struct.pack('<I',mapId));u.mem_write(0xbe3080,struct.pack('<2f',123.25,234.5));u.mem_write(0xbe30b0,struct.pack('<I',0 if flags&4 else 100));u.mem_write(0xd34008,struct.pack('<I',kind in [1,5]));u.mem_write(0xd34018,struct.pack('<2f',1501.25,2803.5));u.mem_write(0xd424cc,struct.pack('<I',kind in [2,4,5]));u.mem_write(0xd424c8,struct.pack('<I',0x3011000));stage=bytearray(128);struct.pack_into('<I',stage,8,1);struct.pack_into('<2fI',stage,32,301.25,407.5,0x3000000+pool+speakerAt);u.mem_write(0x3011000,bytes(stage));u.mem_write(0xd2fb8c,struct.pack('<I',int(kind in [3,4,6]and speaker in names)));member=bytearray(244)
    if speaker in names:
     struct.pack_into('<2I',member,0,names[speaker],mapId+(1 if flags&1 else 0));struct.pack_into('<I',member,20,0 if flags&2 else 100);struct.pack_into('<2f',member,164,501.5,601.25)
    u.mem_write(0xd2f8b0,bytes(member));u.mem_write(0xd880a4,bytes(wire[:96]));u.mem_write(0xd88104,struct.pack('<I',nextSlot));u.mem_write(0xbda944,bytes(wire[100:104]));u.mem_write(0xbda940,bytes(wire[104:108]));u.mem_write(sp,bytes(0x4000));u.mem_write(sp+0x8c,struct.pack('<I',paused));u.mem_write(sp+0xb0,struct.pack('<f',dt));ctx.update(status=status,state=struct.pack('<6I',cursor,1,1,(1<<19)-1,0,node)+bytes(28));u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0x2b75b,0x2bba3,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x2bba3
    expected=bytes(u.mem_read(0xd880a4,96))+bytes(u.mem_read(0xd88104,4))+bytes(u.mem_read(0xbda944,4))+bytes(u.mem_read(0xbda940,4));assert bytes(actual)==expected,(cursor,node,kind,variant,flags,paused,[(i,a,b)for i,(a,b)in enumerate(zip(actual,expected))if a!=b]);cases+=1
    if struct.unpack_from('<I',expected,96)[0]!=nextSlot:emissions+=1;cueIDs.add(word>>8);contexts[kind]=contexts.get(kind,0)+1
assert emissions and len(cueIDs)==9 and all(contexts.get(k,0)for k in [0,1,2,3,4,5,6]),(emissions,cueIDs,contexts)
(V/'Scene-Emote-Checks225.json').write_text(json.dumps(dict(passed=True,nativeComparisons=cases,sceneIntegrationEvidence='Campaign-Sequence-Checks200.json',privateNativeEvidence='Native-Checks194.json',emissions=emissions,cueIDs=sorted(cueIDs),emissionContexts=contexts,scope='Actual original main-loop four-entry emote queue, speaker priority/position, one-shot cursor/node cache, positive one-based cue conversion, paused state, exact float aging/map/strict four-second expiry/ring wrap compared byte-for-byte to production. All surviving dialogue line records and original emote IDs are exercised. Native scene status/state reads and actor contexts are explicit fixtures; no quest writes, SP or currency changes. Actual scene/renderer lifecycle and frame decoding remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS original scene-emote queue and speaker context against production; host only.')
