"""Append source world encounters without renumbering accepted species or maps."""
from pathlib import Path
import ast,csv,json,re,collections,hashlib,struct,zlib
R=Path(__file__).resolve().parent;ROOT=R.parent;BASE=ROOT.parent/'test50f/Source'
def num(b,k,d=0):
 m=re.search(r'\b'+k+r':\s*(-?\d+)',b);return int(m[1])if m else d
def flag(b,k):return bool(re.search(r'\b'+k+r':\s*true',b))
text=(ROOT.parent/'reference48/test50-mob_db.conf').read_text();text=re.sub(r'/\*.*?\*/','',text,flags=re.S)
blocks={int(m[1]):m[0] for m in re.finditer(r'(?ms)^\{\s*Id:\s*(\d+)\b.*?^\},?',text)}
s=(BASE/'encounter_data.h').read_text();a=s.index('static const MobSpec');b=s.index('};',a)
old=[ast.literal_eval('['+x+']') for x in re.findall(r'\{([^{}]+)\}',s[a:b])if x.startswith('"')];ids=[x[10]for x in old]
requests={int(x[1]):x[2].replace('\\','/').lower()for x in csv.reader((ROOT.parent/'asset-request51/World-Maps/Monster-Requests.tsv').open(encoding='utf-8-sig'),delimiter='\t')}
requests.update({1829:"guardian7",1830:"guardian8"})
new=sorted(set(requests)-set(ids));ids+=new;assert len(ids)==494
props=[];spec=[]
races=['Formless','Undead','Brute','Plant','Insect','Fish','Demon','DemiHuman','Angel','Dragon'];eles=['Neutral','Water','Earth','Fire','Wind','Poison','Holy','Dark','Ghost','Undead'];rates=ast.literal_eval(re.search(r'elementRate48\[4\]\[10\]\[10\]=(.*?);',(BASE/'elements48.h').read_text())[1].replace('{','[').replace('}',']'))
for id in ids:
 q=blocks[id];m=re.search(r'Element:\s*\(\s*"Ele_(\w+)",\s*(\d)',q);ele,lv=(eles.index(m[1]),int(m[2]))if m else(0,1);props.append((ele,lv))
 if id not in new:continue
 name=re.search(r'\bName:\s*"([^"]+)"',q)[1];atk=re.search(r'Attack:\s*\[(\d+),\s*(\d+)\]',q);atk=list(map(int,atk.groups()))if atk else[0,0]
 flags=sum(v for k,v in [('CanMove',1),('CanAttack',2),('Aggressive',4),('Assist',8),('Plant',16)]if flag(q,k))
 spec.append([name,num(q,'Hp',1),*atk,num(q,'Exp'),num(q,'JExp'),max(.001,num(q,'AttackDelay',4000)/1000),8000/max(1,num(q,'MoveSpeed',1000))if flags&1 else 0,max(.1,num(q,'AttackMotion',2000)/1000),num(q,'Jellopy'),id,flags,num(q,'Def'),num(q,'ViewRange',1)*8,num(q,'ChaseRange',1)*8,num(q,'Clover'),num(q,'Apple')])
s=s[:b]+''.join('{'+','.join(json.dumps(v)for v in row)+'},\n'for row in spec)+s[b:];s=s.replace('#define MOB_SPEC_COUNT 50','#define MOB_SPEC_COUNT '+str(len(ids)))
world=(R/'world_data.h').read_text();names=json.loads('['+re.search(r'mapNames\[\]=\{(.*?)\}',world)[1]+']');spawn=[]
for row in csv.DictReader((ROOT.parent/'asset-library/Test51-map-inventory/metadata/Spawn-Records.csv').open()):
 if row['map']not in names[18:]:continue
 m=re.match(r'(\w+),(\d+),(\d+),(\d+),(\d+)\s+(?:boss_)?monster\s+[^\t]+\t(\d+),(\d+)(?:,(\d+))?(?:,(\d+))?',row['original_line'])
 assert m,row
 name,x,y,rx,ry,id,count,delay,var=m.groups();assert int(id)in ids
 spawn.append([names.index(name),ids.index(int(id)),int(count),*map(int,[x,y,rx,ry,delay or'0',var or'0'])])
a=s.index('static const SpawnDef');b=s.index('};',a);s=s[:b]+''.join('{'+','.join(map(str,row))+'},\n'for row in spawn)+s[b:]
allspawn=[list(map(int,m.groups()))for m in re.finditer(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),(\d+),(\d+),(\d+),(\d+)\}',s[s.index('static const SpawnDef'):])];pops=collections.Counter()
for row in allspawn:pops[row[0]]+=row[2]
s=re.sub(r'#define MOB_COUNT \d+','#define MOB_COUNT '+str(max(pops.values())+1),s);(R/'encounter_data.h').write_text(s)
# Retain all accepted values; extend derived properties from the same source DB.
keys={
 'mobSourceAgi':lambda q,e,l:num(q,'Agi'),'mobSourceDex':lambda q,e,l:num(q,'Dex'),'mobInt48':lambda q,e,l:num(q,'Int'),'mobStatusLuk':lambda q,e,l:num(q,'Luk'),'mobSourceLevel':lambda q,e,l:num(q,'Lv',1),'mobStunVit':lambda q,e,l:num(q,'Vit'),'mobFreezeMdef':lambda q,e,l:num(q,'Mdef'),'mobDamageMotion49':lambda q,e,l:num(q,'DamageMotion'),
 'mobProtectedRace':lambda q,e,l:1 if'RC_Undead'in q else 6 if'RC_Demon'in q else 0,
 'mobBaneTarget':lambda q,e,l:int('RC_Undead'in q or'RC_Demon'in q or e==9),'mobSignumTarget':lambda q,e,l:int('RC_Undead'in q or'RC_Demon'in q or e==9),
 'mobFreezeImmune':lambda q,e,l:int(flag(q,'Boss')or flag(q,'StatusImmune')or'RC_Undead'in q or e==9),
 'mobPoisonImmune':lambda q,e,l:int(flag(q,'Boss')or flag(q,'StatusImmune')or'RC_Undead'in q or e in(5,9)),
 'mobKnockImmune':lambda q,e,l:int(flag(q,'Boss')or flag(q,'NoKnockback')),
 'mobFlameNoPush':lambda q,e,l:int(flag(q,'Boss')or flag(q,'NoKnockback')or not flag(q,'CanMove')),
 'mobRange43':lambda q,e,l:15 if num(q,'AttackRange',1)<=1 else num(q,'AttackRange',1)*8+6,
}
for key,element in [('mobWaterRate',1),('mobWindRate',4),('mobFlameRate',3),('mobSandRate',2),('mobHolyRate',6)]:keys[key]=lambda q,e,l,element=element:rates[l-1][e][element]
files=['mob_accuracy_traits.h','mob_acolyte_traits.h','mob_control_traits.h','mob_flame_traits.h','mob_sand_traits.h','mob_stun_traits.h','class_mob_traits.h','mob_range43.h','mob_motion49.h','stats_data48.h','mob_utility_traits.h']
for fn in files:
 t=(BASE/fn).read_text()
 for key,func in keys.items():
  pattern=r'\b'+key+r'\[(?:MOB_SPEC_COUNT|50)\]=\{([^{}]*)\}'
  def extend(m):
   vals=[int(x.strip())for x in m[1].split(',')if x.strip()];vals +=[0]*(50-len(vals));assert len(vals)==50
   vals +=[func(blocks[id],*props[ids.index(id)])for id in new]
   return key+'[MOB_SPEC_COUNT]={'+','.join(map(str,vals))+'}'
  t=re.sub(pattern,extend,t)
 # Widen source stat/range types so MVP values cannot wrap at 255.
 t=re.sub(r'unsigned char (mob(?:StatusLuk|SourceLevel|StunVit|Range43))',r'unsigned short \1',t)
 if fn=='mob_utility_traits.h':
  pos=t.index('};',t.index('mobUtility'));t=t[:pos]+''.join('{%d,%d,%d,0,{0},{0}},\n'%(num(blocks[id],'Dex'),flag(blocks[id],'Detector'),flag(blocks[id],'Boss')or flag(blocks[id],'StatusImmune'))for id in new)+t[pos:]
 (R/fn).write_text(t)
t=(BASE/'mob_data50.h').read_text();a=t.index('};');t=t[:a]+','+','.join('{%d,%d,%d}'%(next((i for i,k in enumerate(races)if'RC_'+k+'"'in blocks[id]),0),next((i for i,k in enumerate(['Small','Medium','Large'])if'Size_'+k in blocks[id]),0),num(blocks[id],'Sp'))for id in new)+t[a:];(R/'mob_data50.h').write_text(t.replace('[50][3]','[MOB_SPEC_COUNT][3]'))
t=(BASE/'elements48.h').read_text();t=re.sub(r'mobElement48\[MOB_SPEC_COUNT\]\[2\]=.*?;', 'mobElement48[MOB_SPEC_COUNT][2]='+json.dumps(props).replace('[','{').replace(']','}')+';',t);(R/'elements48.h').write_text(t)
(ROOT/'CATALOG51.json').write_text(json.dumps(dict(ids=ids,new_ids=new,requests=requests,populations={names[k]:v for k,v in pops.items()},capacity=max(pops.values())+1),indent=2,ensure_ascii=False))
print('PASS',len(ids),'species',len(spawn),'new spawn records; population capacity',max(pops.values())+1)
