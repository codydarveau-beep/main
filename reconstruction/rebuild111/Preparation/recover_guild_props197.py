"""Recover original prop plans by replaying the pure deployed placement block.
This is host CPU emulation of a bounded data generator, not Xbox playtesting.
"""
from pathlib import Path
import sys,struct,json,zlib,hashlib
sys.path.insert(0,str(Path(__file__).resolve().parents[2]/'emulation-libs'))
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32
from unicorn.x86_const import *
R=Path(__file__).resolve().parent.parent;x=(R.parent/'packet194/released-default.xbe').read_bytes();b=struct.unpack_from('<I',x,0x104)[0];n,t=struct.unpack_from('<II',x,0x11c);ss=[struct.unpack_from('<14I',x,t-b+i*56)for i in range(n)]
u=Uc(UC_ARCH_X86,UC_MODE_32);u.mem_map(0x10000,0xe60000)
for s in ss:u.mem_write(s[1],x[s[3]:s[3]+s[4]])
u.mem_map(0x2000000,0x10000);sp=0x2008000;u.reg_write(UC_X86_REG_CR4,0x200)
def props(mask,style):
 u.mem_write(0xe281fc,bytes(48*24));u.mem_write(sp+0xa4,struct.pack('<II',mask,style));u.reg_write(UC_X86_REG_ESP,sp);u.emu_start(0x7695f,0x76f8d,count=20000);assert u.reg_read(UC_X86_REG_EIP)==0x76f8d
 count=struct.unpack('<I',u.mem_read(0xd424bc,4))[0];assert count<=48
 raw=bytes(u.mem_read(0xe281fc,count*24));return raw
base=props(0,0);assert len(base)==48
pool=[];groups=[]
for style in range(4):
 g=[]
 for bit in range(12):
  mask=1<<bit if bit<6 else 32|(1<<bit);raw=props(mask,style);assert raw.startswith(base);extra=raw[len(base):];records=[struct.unpack_from('<I4fI',extra,i)for i in range(0,len(extra),24)];first=len(pool);pool+=records;g.append([first,len(records)])
 groups.append(g)
baseRows=[struct.unpack_from('<I4fI',base,i)for i in range(0,len(base),24)]
projects=json.loads((R/'Preparation/Guild-Recovery194.json').read_text())['projects'];valid=[]
for mask in range(4096):
 if any(mask&(1<<i)and(mask&p['requires'])!=p['requires']for i,p in enumerate(projects)):continue
 for style in range(4):
  if style and not(mask&2):continue
  if style==2 and not(mask&8):continue
  if style==3 and not(mask&4):continue
  expected=props(mask,style);made=base
  for bit in range(12):
   if mask&(1<<bit)and(bit<6 or mask&32):
    start,count=groups[style][bit];made+=b''.join(struct.pack('<I4fI',*row)for row in pool[start:start+count])
  assert expected==made,(mask,style,len(expected),len(made));valid.append([mask,style,len(expected)//24,zlib.crc32(expected)])
# Original asset actually contains both atlas and model mesh, not just artwork.
p=(R/'Guild/guildhall.bin').read_bytes();z=zlib.decompressobj();atlas=z.decompress(p);packedAtlas=len(p)-len(z.unused_data);mesh=zlib.decompress(z.unused_data);assert len(atlas)==131072 and len(mesh)==11760 and zlib.crc32(mesh)==0x63f549e8
ranges=[struct.unpack('<II',u.mem_read(0x6ebe64+i*8,8))for i in range(11)];bounds=[struct.unpack('<6f',u.mem_read(0x5b8f6c+i*24,24))for i in range(11)];assert all(first+count<=588 and count%3==0 for first,count in ranges)
def rowC(row):return '{'+str(row[0])+'u,'+','.join(repr(float(v))+'f'for v in row[1:5])+','+str(row[5])+'u}'
h='/* Exact deployed original furnishing placements and model metadata. */\n#ifndef MYRO_GUILD_PROPS_DATA197_H\n#define MYRO_GUILD_PROPS_DATA197_H\nstatic const GuildProp194 guildPropBase197[]={'+','.join(rowC(r)for r in baseRows)+'};\nstatic const GuildProp194 guildPropPool197[]={\n'+',\n'.join(rowC(r)for r in pool)+'};\nstatic const unsigned short guildPropGroups197[4][12][2]={'+','.join('{'+','.join('{%d,%d}'%tuple(g)for g in gs)+'}'for gs in groups)+'};\n'
h+='static const struct{unsigned first,count;float bounds[6];}guildModels197[]={'+','.join('{%du,%du,{'%tuple(rc)+','.join(repr(v)+'f'for v in bo)+'}}'for rc,bo in zip(ranges,bounds))+'};\n#define GUILD_ATLAS_PACKED197 %du\n#define GUILD_MESH_PACKED197 %du\n#define GUILD_MESH_RAW197 11760u\n#define GUILD_ATLAS_RAW_CRC197 %du\n#define GUILD_MESH_RAW_CRC197 %du\n#endif\n'%(packedAtlas,len(z.unused_data),zlib.crc32(atlas),zlib.crc32(mesh));(R/'Source/guild_props_data197.h').write_text(h)
f='static const unsigned guildPropFixtures197[][4]={'+','.join('{'+','.join(str(v)+'u'for v in r)+'}'for r in valid)+'};\n';(R/'Validation/guild_prop_fixtures197.h').write_text(f)
report=dict(provenance='Exact released pure placement block replayed on host; not Xbox/Xemu execution',entryVA=0x7695f,exitVA=0x76f8d,propArrayVA=0xe281fc,records=pool,base=baseRows,groups=groups,validPlans=len(valid),allPlanBytesMatch=True,modelRanges=ranges,modelBounds=bounds,atlasPacked=packedAtlas,meshPacked=len(z.unused_data),meshRaw=len(mesh),meshCRC=zlib.crc32(mesh),cabinetPlacements=[list(r)for r in [struct.unpack_from('<I4fI',props(4095,0),i)for i in range(0,len(props(4095,0)),24)]if r[0]>=5],collisionConstants={hex(a):list(struct.unpack('<4f',u.mem_read(a,16)))for a in [0x74ad10,0x74ad00,0x74ad04]})
(R/'Preparation/Guild-Props-Recovery197.json').write_text(json.dumps(report,indent=2)+'\n');print('Recovered original furnishing generator outputs for',len(valid),'valid floor plans, and exact original model mesh/ranges.')
