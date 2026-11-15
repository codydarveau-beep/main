"""Recover released project costs and wire evidence; no game source is inferred as verbatim."""
from pathlib import Path
import struct,json,hashlib
ROOT=Path(__file__).resolve().parent.parent
data=(ROOT.parent/'packet194/released-default.xbe').read_bytes()
base=struct.unpack_from('<I',data,0x104)[0];count,table=struct.unpack_from('<II',data,0x11c)
sections=[struct.unpack_from('<14I',data,table-base+i*56)for i in range(count)]
def offset(va):return next(s[3]+va-s[1]for s in sections if s[1]<=va<s[1]+s[4])
def string(va):
 at=offset(va);return data[at:data.index(0,at)].decode('utf8')
assert data[offset(0xafe164):offset(0xafe164)+4]==b'RGH1'
assert data[offset(0x98884):offset(0x98884)+5]==b'\xbe\x70\xbc\x19\xf2'
assert data[offset(0x98891):offset(0x98891)+5]==b'\xbe\x00\x00\xa2\xec'
assert data[offset(0xccc5a):offset(0xccc5a)+5]==b'\xba\x70\xbc\x19\xf2'
projects=[]
for i in range(12):
 title,pitch,cursor,requires,a,b,na,nb=struct.unpack_from('<8I',data,offset(0x3a6460)+i*32)
 assert cursor<=36 and requires<4096 and a and b and na and nb
 projects.append(dict(title=string(title),pitch=string(pitch),minimum=cursor,requires=requires,items=[a,b],amounts=[na,nb]))
text='/* MIT. Released project definitions recovered from verified 1.10.0 executable. */\n#ifndef MYRO_GUILD_DATA194_H\n#define MYRO_GUILD_DATA194_H\n'
text+='typedef struct{const char*title,*pitch;unsigned minimum,requires,item[2],amount[2];}GuildProject194;\nstatic const GuildProject194 guildProjects194[]={\n'
for p in projects:
 text+='{'+json.dumps(p['title'])+','+json.dumps(p['pitch'])+','+str(p['minimum'])+','+str(p['requires'])+',{'+','.join(map(str,p['items']))+'},{'+','.join(map(str,p['amounts']))+'}},\n'
text+='};\n#endif\n'
(ROOT/'Source/guild_data194.h').write_text(text)
(ROOT/'Preparation/Guild-Recovery194.json').write_text(json.dumps(dict(
 xbeSHA256=hashlib.sha256(data).hexdigest(),projectTableVA=0x3a6460,
 stateKey='0xeca20000f219bc70',magic='RGH1',wireBytes=56,textBytes=112,
 acceptedOffset=4,completedOffset=8,styleOffset=12,scoresOffset=16,
 scoreCount=6,reservedOffsets=[40,52],crcOffset=52,
 loaderVA=0x98830,storeVA=0xccb50,
 status='Data and wire evidence recovered; C implementation newly reconstructed',projects=projects),indent=2)+'\n')
print('Recovered 12 original project definitions, six score slots and released guild-state wire/key evidence')
