# MIT. Preserve baseline species IDs; append source-defined route and dungeon species.
from pathlib import Path
import re,struct,zlib,json,collections
import ro_sprite_bake as bake
r=Path(__file__).resolve().parent;root=r.parent;lib=root.parent/'asset-library';base=root.parent/'test42/Source'
assets={}
for folder in ['Payon43-return','Payon43-supplement','Payon43-skeletons']:
 for p in (lib/folder/'data').rglob('*'):
  if p.is_file():assets[str(p.relative_to(lib/folder)).replace('/','\\').lower()]=p.read_bytes()
text=(lib/'Payon43-return/server/db/pre-re/mob_db.conf').read_text();blocks={int(m[1]):m[0]for m in re.finditer(r'(?ms)^\{\s*Id:\s*(\d+)\b.*?^\},?',text)}
old=[1002,1063,1008,1113,1048,1051,1080,1079,1052,1031,1088,1084,1167,1107,1047,1049,1009,1081];ids=old+sorted(set(blocks)-set(old));new=ids[len(old):];bake.assets=assets;bake.root=root;bake.out=root/'EncounterAssets';bake.out.mkdir(exist_ok=True)
def num(b,k,d=0):
 m=re.search(r'\b'+k+r':\s*(\d+)',b);return int(m[1])if m else d
def row(b):
 name=re.search(r'\bName:\s*"([^"]+)"',b)[1];atk=list(map(int,re.search(r'Attack:\s*\[(\d+),\s*(\d+)\]',b).groups()));modeMatch=re.search(r'Mode:\s*\{(.*?)\}',b,re.S);mode=modeMatch[1]if modeMatch else '';flags=sum(v for k,v in [('CanMove',1),('CanAttack',2),('Aggressive',4),('Assist',8),('Plant',16)]if re.search(r'\b'+k+r':\s*true',mode));return [name,num(b,'Hp'),*atk,num(b,'Exp'),num(b,'JExp'),num(b,'AttackDelay')/1000,8000/max(1,num(b,'MoveSpeed',1000))if flags&1 else 0,max(.1,num(b,'AttackMotion')/1000),num(b,'Jellopy'),num(b,'Id'),flags,num(b,'Def'),num(b,'ViewRange',10)*8,num(b,'ChaseRange',12)*8,num(b,'Clover'),num(b,'Apple')]
s=(base/'encounter_data.h').read_text();specPos=s.index('};',s.index('static const MobSpec'));s=s[:specPos]+''.join('{'+','.join(json.dumps(v)for v in row(blocks[id]))+'},\n'for id in new)+s[specPos:];s=s.replace('#define MOB_SPEC_COUNT 18','#define MOB_SPEC_COUNT '+str(len(ids)))
names=['prt_fild08','prt_fild05','prontera','izlude','prt_fild06','prt_fild07','prt_fild09','moc_fild01','moc_fild02','moc_fild03','pay_fild01','payon','pay_arche']+['pay_dun0'+str(i)for i in range(5)];spawns=[];pops=collections.Counter()
for line in (lib/'Payon43-return/server/npc/pre-re/mobs/selected-payon.txt').read_text().splitlines():
 m=re.match(r'(\w+),(\d+),(\d+),(\d+),(\d+)\s+(?:monster|boss_monster)\s+[^\t]+\t(\d+),(\d+),(\d+),(\d+)',line)
 if not m:continue
 name,x,y,rx,ry,id,n,delay,var=m.groups();id=int(id)
 if name not in names or id not in ids:continue
 v=[names.index(name),ids.index(id),int(n),*map(int,[x,y,rx,ry,delay,var])];spawns.append(v);pops[names.index(name)]+=int(n)
# Replace baseline-map spawns only when the returned exact map has a source row.
a=s.index('static const SpawnDef spawnDefs[]={');b=s.index('};',a);oldsp=[list(map(int,m.groups()))for m in re.finditer(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),(\d+),(\d+),(\d+),(\d+)\}',s[a:b])];returned={v[0]for v in spawns};spawns=oldsp+ [v for v in spawns if v[0]>=7];pops=collections.Counter()
for v in spawns:pops[v[0]]+=v[2]
s=s[:a]+'static const SpawnDef spawnDefs[]={\n'+''.join('{'+','.join(map(str,v))+'},\n'for v in spawns)+s[b:];cap=max(pops.values())+1;s=re.sub(r'#define MOB_COUNT \d+', '#define MOB_COUNT '+str(cap),s);(r/'encounter_data.h').write_text(s)
f=(base/'encounter_assets.c').read_text();declarations=(base/'enemy_blobs.h').read_text();at=declarations.index('static const unsigned char*enemyData');declarations=declarations[:at]
for idx,id in enumerate(new,len(old)):
 b=blocks[id];stem=re.search(r'SpriteName:\s*"([^"]+)"',b)[1].lower();stem={'archer_skeleton':'skel_archer','soldier_skeleton':'skel_soldier','whisper_':'whisper'}.get(stem,stem);prefix=next('data\\sprite\\'+d+'\\'+stem for d in ['몬스터','npc']if 'data\\sprite\\'+d+'\\'+stem+'.spr'in assets)
 out=bake.out/(stem+'.bin');raw=out.read_bytes()if out.exists()else bake.bake(stem,prefix,None,[0,1,2,3,4],86);cp=zlib.compress(raw,9);f+=f'const unsigned int enemy{idx}_raw={len(raw)},enemy{idx}_size={len(cp)};\nconst unsigned char enemy{idx}[]={{'+','.join(map(str,cp))+'};\n';declarations+=f'extern const unsigned char enemy{idx}[];extern const unsigned int enemy{idx}_raw,enemy{idx}_size;\n'
declarations+='static const unsigned char*enemyData[MOB_SPEC_COUNT]={'+','.join('enemy'+str(i)for i in range(len(ids)))+'};\nstatic unsigned enemyRaw[MOB_SPEC_COUNT],enemySize[MOB_SPEC_COUNT];\nstatic void enemy_blob_init(void){\n'+''.join(f'enemyRaw[{i}]=enemy{i}_raw;enemySize[{i}]=enemy{i}_size;\n'for i in range(len(ids)))+'}\n';(r/'enemy_blobs.h').write_text(declarations);(r/'encounter_assets.c').write_text(f)
# Extend source-based defensive/status traits; element tier scaling remains prototype.
for fn in ['mob_accuracy_traits.h','mob_acolyte_traits.h','mob_control_traits.h','mob_flame_traits.h','mob_sand_traits.h','mob_stun_traits.h','class_mob_traits.h']:
 s=(base/fn).read_text()
 def extra(m):
  key=m[1];vals=[]
  for id in new:
   b=blocks[id];ele=re.search(r'Element:\s*\("Ele_(\w+)",\s*(\d+)\)',b);element=ele[1]if ele else'Neutral';boss=bool(re.search(r'\b(?:Boss|StatusImmune|Mvp):\s*true',b));undead='RC_Undead'in b or element=='Undead';demon='RC_Demon'in b
   rates={'mobWaterRate':{'Water':25,'Fire':150,'Earth':100,'Wind':50,'Undead':100,'Ghost':100},'mobWindRate':{'Water':175,'Fire':100,'Earth':50,'Wind':25},'mobFlameRate':{'Water':50,'Fire':25,'Earth':150,'Wind':100,'Undead':125},'mobSandRate':{'Water':100,'Fire':50,'Earth':100,'Wind':150}}
   v=rates.get(key,{}).get(element,100)if key in rates else {'mobSourceAgi':num(b,'Agi'),'mobSourceDex':num(b,'Dex'),'mobStatusLuk':num(b,'Luk'),'mobSourceLevel':num(b,'Lv'),'mobStunVit':num(b,'Vit'),'mobFreezeMdef':num(b,'Mdef'),'mobBaneTarget':int(undead or demon),'mobSignumTarget':int(undead or demon),'mobFreezeImmune':int(boss or undead),'mobFlameNoPush':int(boss or not('CanMove: true'in b)),'mobKnockImmune':int(boss),'mobProtectedRace':int(undead or demon),'mobPoisonImmune':int(boss or undead or element=='Poison')}.get(key,0);vals.append(str(v))
  return m[0][:-2]+','+','.join(vals)+'};'
 s=re.sub(r'\b(mob\w+)\[MOB_SPEC_COUNT\]=\{[^}]*\};',extra,s);(r/fn).write_text(s)
s=(base/'mob_utility_traits.h').read_text();pos=s.index('};',s.index('mobUtility'));s=s[:pos]+''.join('{%d,%d,%d,0,{0},{0}},\n'%(num(blocks[id],'Dex'),int('Detector: true'in blocks[id]),int(bool(re.search(r'\b(?:Boss|StatusImmune):\s*true',blocks[id]))))for id in new)+s[pos:];(r/'mob_utility_traits.h').write_text(s)
# Preserve existing PCM indexes, silent optional death samples for new species.
s=(base/'sound_assets.c').read_text();m=re.search(r'const short\*soundData\[\]=\{([^}]+)\}',s);s=s[:m.end(1)]+',soundEmpty43'*(len(new))+s[m.end(1):];s='static const short soundEmpty43[1]={0};\n'+s;m=re.search(r'const unsigned soundLengths\[\]=\{([^}]+)\}',s);s=s[:m.end(1)]+',0'*len(new)+s[m.end(1):];(r/'sound_assets.c').write_text(s)
(root/'MOBS43.json').write_text(json.dumps({'ids':ids,'new_ids':new,'spawns':spawns,'populations':dict(pops),'capacity':cap},indent=2));print('DONE species',len(ids),'capacity',cap,'populations',dict(pops))
