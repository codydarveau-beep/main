"""Independent original floor-mask/solid-footprint replay; not hardware testing."""
from pathlib import Path
import sys,struct,zlib,json,re,time
sys.path.insert(0,str(Path(__file__).resolve().parents[2]/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
R=Path(__file__).resolve().parent.parent;x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-b+i*56)for i in range(n)]
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for s in ss:u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x20000);sp=0x2008000;u.mem_map(0x3000000,0x20000);u.reg_write(UC_X86_REG_CR4,0x200)
def skip_visual(uc,address,size,ctx):
 if address in [0x9e440,0x9fea0]:
  esp=uc.reg_read(UC_X86_REG_ESP);ret=struct.unpack('<I',uc.mem_read(esp,4))[0];uc.reg_write(UC_X86_REG_EAX,0);uc.reg_write(UC_X86_REG_ESP,esp+4);uc.reg_write(UC_X86_REG_EIP,ret)
u.hook_add(UC_HOOK_CODE,skip_visual,begin=0x9e440,end=0x9e440);u.hook_add(UC_HOOK_CODE,skip_visual,begin=0x9fea0,end=0x9fea0)
s=(R/'Source/world_data.h').read_text().split('worldBlobs[WORLD_MAP_COUNT][7]=')[1].split(';')[0];rows=[tuple(map(int,t))for t in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',s)];at,n,raw,crc=rows[494*7+1]
with (R/'XboxFiles/world.bin').open('rb')as f:f.seek(at);p=f.read(n)
assert zlib.crc32(p)==crc;data=zlib.decompress(p);width,height=struct.unpack_from('<II',data);floor=data[8:8+width*height];bits=bytearray((len(floor)+7)//8)
for i,v in enumerate(floor):
 if v:bits[i>>3]|=1<<(i&7)
u.mem_write(0x3010000,bytes(bits));u.mem_write(0xd36964,struct.pack('<I',0x3000000));u.mem_write(0xd424b8,struct.pack('<I',0x3010000));u.mem_write(0xd2fbac,struct.pack('<II',height,width))
fixture=(R/'Validation/guild_prop_fixtures197.h').read_text();plans=[tuple(map(int,t))for t in re.findall(r'\{(\d+)u,(\d+)u,(\d+)u,(\d+)u\}',fixture)];crcs=[]
for i,(mask,style,count,propCRC)in enumerate(plans):
 u.mem_write(0x3000000,floor);u.mem_write(sp+0xa4,struct.pack('<II',mask,style));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ESI,len(floor));u.reg_write(UC_X86_REG_EBX,0x3010000);u.emu_start(0x76724,0x7728e,count=10000000);assert u.reg_read(UC_X86_REG_EIP)==0x7728e
 output=bytes(u.mem_read(0x3000000,len(floor)));crcs.append(zlib.crc32(output));assert zlib.crc32(u.mem_read(0xe281fc,count*24))==propCRC
 if i%100==0:print('Original floor reference plans',i,'/',len(plans),flush=True)
(R/'Validation/guild_floor_fixtures197.h').write_text('static const unsigned guildFloorCRCs197[]={'+','.join(str(v)+'u'for v in crcs)+'};\n')
(R/'Validation/Guild-Floor-Reference197.json').write_text(json.dumps(dict(plans=len(plans),entryVA=0x76724,exitVA=0x7728e,originalFloorCRC=zlib.crc32(floor),visualOnlyCallsSkipped=[0x9e440,0x9fea0],scope='Host CPU replay of deployed pure floor/collision logic; no Xbox/Xemu playtest'),indent=2)+'\n');print('Recovered original floor CRCs for all valid plans')
