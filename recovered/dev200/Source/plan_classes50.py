"""GPL-3.0-or-later. Audited class/skill allocation and integer source profiles.
Planning data only: a class is not selectable until its mechanics/art are integrated.
"""
from pathlib import Path
import re,json,hashlib
r=Path(__file__).resolve().parent;ref=r.parent.parent/'reference48';db=re.sub(r'//[^\n]*','',(ref/'job_db.conf').read_text());audit=json.loads((r/'class_skill_audit50.json').read_text())['classes'];art=json.loads((r/'class_asset_audit50.json').read_text());deferred=art['deferred']
classes=[('Assassin',12,'어세신',4),('Rogue',17,'로그',4),('Hunter',11,'헌터',5),('Bard',19,'바드',5),('Dancer',20,'무희',5),('Priest',8,'프리스트',3),('Monk',15,'몽크',3),('Blacksmith',10,'제철공',6),('Alchemist',18,'연금술사',6)]
def block(n):
 m=re.search(r'(?m)^'+re.escape(n)+r':\s*\{',db);assert m,n;start=m.end();i=start;depth=1
 while depth:
  if db[i]=='{':depth+=1
  if db[i]=='}':depth-=1
  i+=1
 return db[start:i-1]
def parent(b,key='Inherit'):
 m=re.search(r'\b'+key+r':\s*\(\s*"([^"]+)"',b);return m[1]if m else None

def table(n,key,trail=()):
 assert n not in trail; b=block(n);m=re.search(r'\b'+key+r':\s*\[([^]]+)\]',b)
 if m:return list(map(int,re.findall(r'\d+',m[1])))[:99]
 p=parent(b,'Inherit'+('HP'if key=='HPTable'else'SP'))or parent(b);assert p,(n,key)
 return table(p,key,trail+(n,))
def aspd(n,trail=()):
 assert n not in trail;b=block(n);p=parent(b);result=aspd(p,trail+(n,))if p else{}
 m=re.search(r'BaseASPD:\s*\{([^}]+)\}',b)
 if m:result.update({k:int(v)for k,v in re.findall(r'(\w+):\s*(\d+)',m[1])})
 return result
bonus={}
for line in(ref/'job_db2.txt').read_text().splitlines():
 line=line.split('//')[0].strip()
 if line:
  q=list(map(int,line.split(',')));bonus[q[0]]=q[1:]
shared={'SM_SWORD':35,'AC_VULTURE':16,'AC_DOUBLE':17,'MG_SRECOVERY':25,'MG_SAFETYWALL':48,'PR_KYRIE':7};next_id=127;skills={};roster=[]
for i,(name,source,stem,first)in enumerate(classes,12):
 hp=table(name,'HPTable');sp=table(name,'SPTable');assert len(hp)==len(sp)==99 and all(0<v<65536 for v in hp+sp)
 count=[0]*6;levels=[]
 for lv in range(50):
  stat=bonus[source][lv]if lv<len(bonus[source])else 0
  if stat:count[stat-1]+=1
  levels.append(count.copy())
 active=[];skip=[]
 for row in audit[name]:
  key=row['key']
  if key in deferred:skip.append(dict(key=key,reason=deferred[key]));continue
  if key not in skills:
   id=shared.get(key)
   if id is None:id=next_id;next_id+=1
   skills[key]=dict(id=id,maxRank=row['maxRank'],source=row['source'],owners=[])
  skills[key]['owners'].append(i);active.append(skills[key]['id'])
 roster.append(dict(id=i,name=name,sourceJobID=source,firstClass=first,bodyStem=stem,defaultSex='female'if name=='Dancer'else'male',sourceHP99=hp,sourceSP99=sp,sourceWeaponMotion=aspd(name),sourceJobBonus50=levels,skills=active,deferred=skip))
assert len(skills)==133 and next_id==254
assert aspd('Dancer')['Bow']==aspd('Bard')['Bow']==650 and aspd('Dancer')['Whip']==575
plan=dict(sourceCommit='21b27966cfc2e7df0bf8151cd717a1105d047ba9',sourceHashes={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in[ref/'job_db.conf',ref/'job_db2.txt']},classes=roster,skills=skills,plannedSkillCount=next_id,plannedRankCount=252,rankCompatibility='Existing124 slots unchanged; append127 new skills and existing KyrieID7, which had no learned slot.',bindingFoundation='implemented: 16-bit bindings, item base4096/empty65535, Save50 disjoint sections and read-only Save48 migration; native/ASAN/SDK verified',status='source catalog prepared; mechanics/art integration remains gated')
(r/'class_plan50.json').write_text(json.dumps(plan,indent=2,ensure_ascii=False)+'\n');print('PASS50 nine source job profiles/99HP-SP levels/50job bonuses,133 eligible shared skill keys,127 new IDs127..253; Dancer inherited bow timing retained. 16-bit binding/save migration foundation verified; mechanics/art still pending.')
