# SPDX-License-Identifier: MIT. Converts the supplied offline RO expansion collection.
from pathlib import Path
import zipfile,csv,io,re,hashlib,struct,zlib,json,sys,wave,audioop
import ro_sprite_bake as bake
root=Path(__file__).resolve().parent.parent;out=root/'EncounterAssets';out.mkdir(exist_ok=True)
z=zipfile.ZipFile(sys.argv[1]);assets={}
for r in csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))):
 b=z.read(r['payload']);assert hashlib.sha256(b).hexdigest()==r['sha256'];assets[r['virtual_path'].lower()]=b
bake.assets=assets;bake.root=root;bake.out=out
ids=[1002,1063,1008,1113,1048,1051,1080,1079,1052,1031,1088,1084,1167,1107,1047,1049,1009,1081]
names=['poring','lunatic','pupa','drops','thief_bug_egg','thief_bug','green_plant','blue_plant','rocker','poporing','vocal','black_mushroom','savage_babe','desert_wolf_b','pecopeco_egg','picky','condor','yellow_plant']
text=assets['server/db/pre-re/mob_db.conf'].decode('utf-8-sig');text=re.sub(r'/\*.*?\*/','',text,flags=re.S)
blobs=[];specs=[];report={'monsters':[],'spawns':[],'sounds':[]}
for id,name in zip(ids,names):
 b=re.search(r'\{\s*Id:\s*'+str(id)+r'\b.*?\n\},',text,re.S)[0]
 def num(k,default=0):
  m=re.search(r'\b'+k+r':\s*(\d+)',b);return int(m[1]) if m else default
 def drop(k):return num(k)
 display=re.search(r'\bName:\s*"([^"]+)"',b)[1];atk=[int(v) for v in re.search(r'Attack:\s*\[(\d+),\s*(\d+)\]',b).groups()]
 mode=re.search(r'Mode:\s*\{(.*?)\}',b,re.S);mode=mode[1] if mode else ''
 flags=sum(v for k,v in [('CanMove',1),('CanAttack',2),('Aggressive',4),('Assist',8),('Plant',16)] if re.search(r'\b'+k+r':\s*true',mode))
 spec=[display,num('Hp'),*atk,num('Exp'),num('JExp'),num('AttackDelay')/1000,8000/max(1,num('MoveSpeed',1000)) if flags&1 else 0,max(.1,num('AttackMotion')/1000),drop('Jellopy'),id,flags,num('Def'),num('ViewRange',10)*8,num('ChaseRange',12)*8,drop('Clover'),drop('Apple')]
 specs.append(spec);report['monsters'].append({'id':id,'name':display,'flags':flags,'stats':spec[1:]})
 prefix=next('data\\sprite\\'+folder+'\\'+name for folder in ['몬스터','npc'] if 'data\\sprite\\'+folder+'\\'+name+'.spr' in assets)
 # Immobile objects often have fewer than 40 actions; repeat idle for unavailable groups.
 acts,delays=bake.act(assets[prefix+'.act']);bake.fallback_actions=len(acts)
 raw=bake.bake(name,prefix,None,[0,1,2,3,4],86);blobs.append(raw)
with (root/'Source/encounter_assets.c').open('w') as f:
 f.write('/* Generated from user-supplied RO assets; original ownership retained. */\n')
 for i,raw in enumerate(blobs):
  p=zlib.compress(raw,9);f.write(f'const unsigned int enemy{i}_raw={len(raw)},enemy{i}_size={len(p)};\nconst unsigned char enemy{i}[]={{\n');
  for at in range(0,len(p),32):f.write(','.join(map(str,p[at:at+32]))+',\n')
  f.write('};\n')
with (root/'Source/encounter_data.h').open('w') as f:
 f.write('/* SPDX-License-Identifier: MIT. Generated pre-renewal monster/spawn definitions. */\n#define MOB_SPEC_COUNT 18\n#define MOB_COUNT 193 /* Last slot reserved for the developer target. */\n#define RENDER_MOBS 32\n#define SPRITE_SLOT_COUNT (RENDER_MOBS+2)\n#define MERCHANT_SPRITE (MOB_SPEC_COUNT+1)\n')
 f.write('typedef struct {const char*name;int hp,amin,amax,exp,jexp;float delay,speed,motion;int dropChance,id,flags,defense,view,chase,cloverChance,appleChance;} MobSpec;\nstatic const MobSpec mobSpecs[MOB_SPEC_COUNT]={\n')
 for row in specs:f.write('{'+','.join(json.dumps(x) if isinstance(x,str) else str(x) for x in row)+'},\n')
 f.write('};\ntypedef struct {unsigned map,kind,count;int x,y,rx,ry,delay,variance;} SpawnDef;\nstatic const SpawnDef spawnDefs[]={\n')
 maps=['prt_fild08','prt_fild05','prontera','izlude','prt_fild06','prt_fild07','prt_fild09']
 for line in assets['server/npc/pre-re/mobs/fields/prontera.txt'].decode('utf-8-sig').splitlines():
  if not line or line.lstrip().startswith('//'):continue
  cols=line.split('\t');loc=cols[0].split(',')
  if loc[0] not in maps or len(cols)<4 or cols[1]!='monster':continue
  vals=list(map(int,cols[3].split(',')[:4]));id,count,delay,variance=vals;assert id in ids
  row=[maps.index(loc[0]),ids.index(id),count,*map(int,loc[1:5]),delay,variance]
  f.write('{'+','.join(map(str,row))+'},\n');report['spawns'].append({'source':line,'definition':row})
 f.write('};\n#define SPAWN_DEF_COUNT (sizeof(spawnDefs)/sizeof(spawnDefs[0]))\n')
with (root/'Source/enemy_blobs.h').open('w') as f:
 for i in range(len(ids)):f.write(f'extern const unsigned char enemy{i}[];extern const unsigned int enemy{i}_raw,enemy{i}_size;\n')
 f.write('static const unsigned char*enemyData[MOB_SPEC_COUNT]={'+','.join('enemy'+str(i) for i in range(len(ids)))+'};\n')
 f.write('static unsigned enemyRaw[MOB_SPEC_COUNT],enemySize[MOB_SPEC_COUNT];\nstatic void enemy_blob_init(void){\n')
 for i in range(len(ids)):f.write(f'enemyRaw[{i}]=enemy{i}_raw;enemySize[{i}]=enemy{i}_size;\n')
 f.write('}\n')
# Fixed, short, 48 kHz mono signed PCM clips. No decoder or streaming needed for SFX.
paths=['data\\wav\\_hit_sword.wav','data\\wav\\effect\\warp.wav']
paths += ['data\\wav\\'+n+'_die.wav' for n in names]
sounds=[]
for path in paths:
 if path not in assets:
  sounds.append(b'');report['sounds'].append({'path':path,'missing':True});continue
 with wave.open(io.BytesIO(assets[path]),'rb') as w:
  data=w.readframes(min(w.getnframes(),w.getframerate()*3));width=w.getsampwidth();channels=w.getnchannels();rate=w.getframerate()
 if width==1:data=audioop.bias(data,1,-128)
 if channels==2:data=audioop.tomono(data,width,.5,.5)
 elif channels!=1:raise ValueError('unsupported channels')
 if width!=2:data=audioop.lin2lin(data,width,2)
 data=audioop.ratecv(data,2,1,rate,48000,None)[0];data=audioop.mul(data,2,.35)
 sounds.append(data);report['sounds'].append({'path':path,'bytes':len(data)})
with (root/'Source/sound_assets.c').open('w') as f:
 f.write('/* Generated supplied WAV clips, 48 kHz mono PCM16. */\n')
 for i,b in enumerate(sounds):
  vals=struct.unpack('<'+'h'*(len(b)//2),b);f.write(f'const short sound{i}[]={{'+','.join(map(str,vals or [0]))+'};\n')
 f.write('const short*soundData[]={'+','.join('sound'+str(i) for i in range(len(sounds)))+'};\nconst unsigned soundLengths[]={'+','.join(str(len(b)//2) for b in sounds)+'};\n')
(root/'ENCOUNTER-CONVERSION-REPORT.json').write_text(json.dumps(report,indent=2));print('Finished',sum(map(len,blobs)),'sprite bytes;',sum(map(len,sounds)),'PCM bytes')
