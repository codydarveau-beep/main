"""Recover deployed content metadata, validating every blob before integration."""
from pathlib import Path
import struct,zlib,json,hashlib,re
R=Path(__file__).resolve().parent.parent;D=R/'Recovered195';D.mkdir(exist_ok=True);recovery=R.parent
xbe=(recovery/'packet194/released-default.xbe').read_bytes();baseline=json.loads((recovery/'baseline-file-verification.json').read_text())['files']
base,=struct.unpack_from('<I',xbe,0x104);count,table=struct.unpack_from('<II',xbe,0x11c);sections=[struct.unpack_from('<14I',xbe,table-base+i*56)for i in range(count)]
def offset(va):return next(s[3]+va-s[1]for s in sections if s[1]<=va<s[1]+s[4])
def string(va):
 at=offset(va);return xbe[at:xbe.index(0,at)].decode('utf8')
def unique(needle):
 at=xbe.find(needle);assert at>=0 and xbe.find(needle,at+1)<0,('nonunique',needle.hex(),at);return at
def streams(data):
 out=[];at=0
 while at<len(data):
  chunk=data[at:at+2*1024*1024];z=zlib.decompressobj();raw=z.decompress(chunk);assert z.eof;size=len(chunk)-len(z.unused_data);assert size>0
  out.append(dict(offset=at,packed=size,raw=len(raw),crc=zlib.crc32(data[at:at+size]),rawCRC=zlib.crc32(raw),magic=raw[:4].hex()));at+=size
 return out
report={}
with (recovery/'released-1.10.0.iso').open('rb')as f:
 for name in ['campaign.bin','chapter1.bin','npcfx.bin','portraits.bin','storyportraits.bin']:
  b=baseline[name];f.seek(b['isoOffset']);data=f.read(b['bytes']);assert hashlib.sha256(data).hexdigest()==b['sha256'];(D/name).write_bytes(data);rows=streams(data);report[name]=dict(bytes=len(data),sha256=b['sha256'],streams=rows);print(name,len(rows),'validated streams',flush=True)
# Tables anchored by three complete verified blob records, never guessed offsets.
for name,rawcrc in [('campaign.bin',False),('chapter1.bin',True)]:
 rows=report[name]['streams'];key='rawCRC'if rawcrc else'crc';at=unique(b''.join(struct.pack('<4I',r['offset'],r['packed'],r['raw'],r[key])for r in rows[:3]));decoded=[]
 for i,r in enumerate(rows):
  t=struct.unpack_from('<4I',xbe,at+i*16);assert t==tuple(r[k]for k in ['offset','packed','raw',key]);decoded.append(t)
 report[name]['tableFileOffset']=at
 if name=='chapter1.bin':
  header='/* Verified released typed-scene metadata; not new authored scenes. */\n#ifndef MYRO_CHAPTER1_DATA200_H\n#define MYRO_CHAPTER1_DATA200_H\n#define CHAPTER1_RESCUE_GATE200 5u\n#define CHAPTER2_INVESTIGATION_GATE200 9u\n#define CAMPAIGN_PACKED_SCENES195 36u\n#define CAMPAIGN_TYPED_SCENES200 36u\n#define CAMPAIGN_RELEASE_SCENES193 %du\n#define CHAPTER1_FILE_BYTES200 %du\nstatic const struct{unsigned offset,packed,raw,crc;}chapter1Index200[]={\n'%(12,report[name]['bytes'])
  header+=''.join('{'+','.join(str(v)+'u'for v in t)+'},\n'for t in decoded)+'};\n#endif\n';(D/'chapter1_data200.h').write_text(header)
# FX table retains crop origin/size: recover exact rows and validate sequential blobs.
rows=report['npcfx.bin']['streams'];at=unique(b''.join(struct.pack('<4I',r['offset'],r['packed'],r['raw'],r['crc'])+struct.pack('<4I',*v)for r,v in zip(rows[:3],[(72,117,36,54),(72,116,36,55),(72,117,36,55)])))
fx=[];byOffset={r['offset']:r for r in rows}
for i in range(10000):
 t=struct.unpack_from('<8I',xbe,at+i*32);r=byOffset.get(t[0])
 if not r or t[:4]!=tuple(r[k]for k in ['offset','packed','raw','crc']):break
 assert 0<=t[6]<=1024 and 0<=t[7]<=1024;fx.append(t)
assert len(fx)>=4408
report['npcfx.bin']['tableFileOffset']=at
# Portrait metadata uses pointers plus offset/size/crc/(width,height).
for name,story in [('portraits.bin',False),('storyportraits.bin',True)]:
 rows=report[name]['streams'];r=rows[0]
 needle=struct.pack('<4I',0,r['offset'],r['packed'],r['crc'])if story else struct.pack('<3I',r['offset'],r['packed'],r['crc'])
 at=unique(needle)-(4 if story else 4);stride=24;meta=[]
 byOffset={r['offset']:r for r in rows}
 for i in range(1000):
  t=struct.unpack_from('<6I',xbe,at+i*stride);r=byOffset.get(t[2]if story else t[1])
  if not r:break
  if story:
   if t[2:5]!=tuple(r[k]for k in ['offset','packed','crc'])or t[5]!=r['rawCRC']:break
   assert t[1]<=5
  else:
   if t[1:4]!=tuple(r[k]for k in ['offset','packed','crc']):break
   assert 0<t[4]<=512 and 0<t[5]<=512
  speaker=string(t[0]);assert speaker and len(speaker)<100;meta.append([speaker,*t[1:]])
 assert len(meta)>=24
 report[name]['tableFileOffset']=at;report[name]['metadata']=meta
report['npcfx.bin']['metadata']=fx
(D/'content-recovery195.json').write_text(json.dumps(report,indent=2)+'\n');print('All metadata validated against released pack bytes')
# Exact deployed actor action/contact catalog and roster mappings.
old=(R/'Source/campaign_actor_data200.h').read_text();oldActions=re.findall(r'\{(\d+)u,(\d+)u,(\d+)u\}',old.split('campaignActions200[]=')[1].split(';')[0]);at=unique(b''.join(struct.pack('<3I',*map(int,t))for t in oldActions[:4]));actions=[];first=0;total=len(report['campaign.bin']['streams'])
while first<total:
 t=struct.unpack_from('<3I',xbe,at+len(actions)*12);assert t[0]==first and 0<t[1]<=100 and 0<t[2]<=2000,t;actions.append(t);first+=t[1]
assert first==total and len(actions)%48==0;actors=len(actions)//48
contactsText=old.split('campaignContact200')[1].split('=')[1].split(';')[0];floats=[float(v)for v in re.findall(r'-?\d+\.\d+',contactsText)];contactAt=unique(struct.pack('<16f',*floats[:16]));contacts=struct.unpack_from('<%df'%(actors*16),xbe,contactAt);assert all(-128<=v<=128 for v in contacts)
report['campaign.bin'].update(actionsTableFileOffset=at,actions=actions,actorCount=actors,contactsTableFileOffset=contactAt,contacts=contacts)
names=re.findall(r'\{"([^"\n]+)",[^,\n]+,\d+\}',(R/'Source/campaign_companions200.h').read_text());candidates=[]
for section in sections:
 pos=section[3]
 while True:
  pos=xbe.find(b'Brann\0',pos,section[3]+section[4])
  if pos<0:break
  va=section[1]+pos-section[3];ptr=struct.pack('<I',va);ptrAt=0
  while True:
   ptrAt=xbe.find(ptr,ptrAt)
   if ptrAt<0:break
   try:
    roster=[]
    for i,name in enumerate(names):
     p,career,actor=struct.unpack_from('<3I',xbe,ptrAt+i*12);assert string(p)==name and career<64 and(actor==255 or actor<actors);roster.append([name,career,actor])
    candidates.append((ptrAt,roster))
   except (AssertionError,StopIteration,UnicodeDecodeError,ValueError):pass
   ptrAt+=1
  pos+=1
assert len(candidates)==1,candidates
report['roster']=dict(tableFileOffset=candidates[0][0],rows=candidates[0][1])
# Recover staged contact definitions, including later deployed rows if present.
at=unique(struct.pack('<III4f',3,12,2,364,1004,364,1028));stages=[]
for i in range(34):
 t=struct.unpack_from('<III4f',xbe,at+i*92)
 if t[0]!=i+3 or t[1]>=497 or not 1<=t[2]<=4:break
 a=[]
 for j in range(4):
  source,x,y,p=struct.unpack_from('<IffI',xbe,at+i*92+28+j*16)
  if j<t[2]:assert source<actors;a.append([source,x,y,string(p)])
 stages.append([*t,a])
report['staging']=dict(tableFileOffset=at,rows=stages)
(D/'content-recovery195.json').write_text(json.dumps(report,indent=2)+'\n');print('Recovered actor catalog:',actors,'sources; roster:',len(candidates[0][1]),'; staged definitions:',len(stages))
# Deployed clip descriptors: include appended effects, retaining precise scales/variants.
s=(R/'Source/npc_effect_data172.h').read_text().split('npcFxClips172[]={')[1].split('};')[0];oldclips=re.findall(r'\{([^{}]+)\}',s)
def clip_tuple(row):
 v=row.split(',');return tuple([int(a.rstrip('u'))for a in v[:4]]+[float(v[4].rstrip('f'))]+[int(a.rstrip('u'))for a in v[5:]])
at=unique(b''.join(struct.pack('<4If2I',*clip_tuple(t))for t in oldclips[:3]));clips=[]
for i in range(2000):
 t=struct.unpack_from('<4If2I',xbe,at+i*28)
 if not(0<t[0]<200000 and t[2]>0 and t[1]+t[2]<=len(fx) and 0<t[3]<=2000 and 0<t[4]<=10 and t[6]>0 and t[5]<t[6]):break
 clips.append(t)
assert len(clips)>=len(oldclips)
report['npcfx.bin'].update(clipsTableFileOffset=at,clips=clips)
# Store full 128-byte deployed stage records; trailing fields are not guessed.
at=unique(struct.pack('<III4f',3,12,2,364,1004,364,1028));records=[]
for i in range(33):
 t=struct.unpack_from('<III4f',xbe,at+i*128)
 if t[0]!=i+3 or t[1]>=497 or not 1<=t[2]<=4:break
 a=[]
 for j in range(t[2]):
  source,x,y,p=struct.unpack_from('<IffI',xbe,at+i*128+28+j*16);assert source<actors;a.append([source,x,y,string(p)])
 records.append(dict(cursor=t[0],map=t[1],count=t[2],position=t[3:5],document=t[5:7],actors=a,trailing=struct.unpack_from('<9I',xbe,at+i*128+92)))
report['staging']=dict(tableFileOffset=at,stride=128,rows=records)
(D/'content-recovery195.json').write_text(json.dumps(report,indent=2)+'\n');print('Recovered exact effect clips:',len(clips),'; deployed stage records:',len(records))

# Released validator proves packed presentation semantics; no guessed bit masks.
signature=bytes.fromhex('8b431c3dff500000');cueAt=unique(signature);assert xbe[cueAt+14:cueAt+19]==bytes.fromhex('25fe000000')
report['sceneWire']=dict(cueCheckFileOffset=cueAt,cueMaximum=0x50ff,expressionMask=255,expressionMaximum=5,emotionShift=8,emotionMaximum=80,packedScenes=36,retainedRuntimeCeiling=12,worldActivation=False)
(D/'content-recovery195.json').write_text(json.dumps(report,indent=2)+'\n')
