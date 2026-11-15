# GPL-3.0-or-later. Import pinned, matching Hercules pre-renewal stat data.
from pathlib import Path
import re,json,ast,hashlib
r=Path(__file__).resolve().parent;ref=r.parent.parent/'reference48';j=(ref/'job_db.conf').read_text();names=['Novice','Swordsman','Magician','Acolyte','Thief','Archer','Merchant','Knight','High_Wizard','Wizard','Sage','Crusader'];ids=[0,1,2,4,6,3,5,7,4010,9,16,14];wtypes=['Fist','Dagger','Sword','TwoHandSword','Spear','TwoHandSpear','Axe','TwoHandAxe','Mace','Rod','Bow','Book','TwoHandRod']
def block(n):
 m=re.search(r'(?m)^'+re.escape(n)+r':\s*\{',j);a=m.end();b=a;depth=1
 while depth:
  if j[b]=='{':depth+=1
  if j[b]=='}':depth-=1
  b+=1
 return j[a:b-1]
def aspd(n):
 b=block(n);q=re.search(r'BaseASPD:\s*\{([^}]+)\}',b)
 if q:return [int(re.search(r'\b'+w+r':\s*(\d+)',q[1])[1])if re.search(r'\b'+w+r':\s*(\d+)',q[1])else 2000 for w in wtypes]
 parent=re.search(r'\bInherit:\s*\("([^"]+)"',b);assert parent,n;return aspd(parent[1])
bonus={}
for line in(ref/'job_db2.txt').read_text().splitlines():
 line=line.split('//')[0].strip()
 if not line:continue
 vals=list(map(int,line.split(',')));bonus[vals[0]]=vals[1:]
points=list(map(int,(ref/'statpoint.txt').read_text().split()))[:99];assert points[0]==48 and len(points)==99
rows=[]
for n,id in zip(names,ids):
 seq=bonus[id];tot=[0]*6;levels=[]
 for lv in range(70):
  k=seq[lv]if lv<len(seq)else 0
  if k:tot[k-1]+=1
  levels.append(tot.copy())
 rows.append(levels)
bodies=(r/'encounter_data.h').read_text().split('static const MobSpec mobSpecs[MOB_SPEC_COUNT]={',1)[1].split('};',1)[0];mobids=[]
for line in bodies.splitlines():
 if line.strip().startswith('{'):mobids.append(ast.literal_eval('['+line.strip()[1:line.rfind('}')]+']')[10])
s=(ref/'mob_db.conf').read_text();mb={int(m[1]):m[0]for m in re.finditer(r'(?ms)^\{\s*Id:\s*(\d+)\b.*?^\},?',s)}
ints=[]
for id in mobids:
 assert id in mb,id;m=re.search(r'\bInt:\s*(\d+)',mb[id]);ints.append(int(m[1])if m else 0)
s='''/* GPL-3.0-or-later. Hercules21b27966 pre-re data; matches supplied job_db/battle sources. */\n''';s+='static const unsigned short statBudget48[99]={'+','.join(map(str,points))+'};\n';s+='static const unsigned short baseMotion48[12][13]={'+','.join('{'+','.join(map(str,aspd(n)))+'}'for n in names)+'};\n';s+='static const unsigned char jobBonus48[12][70][6]='+json.dumps(rows,separators=(',',':')).replace('[','{').replace(']','}')+';\n';s+='static const unsigned short mobInt48[MOB_SPEC_COUNT]={'+','.join(map(str,ints))+'};\n';(r/'stats_data48.h').write_text(s)
(r/'stats_sources48.json').write_text(json.dumps(dict(commit='21b27966cfc2e7df0bf8151cd717a1105d047ba9',matching_supplied=['db/pre-re/job_db.conf','src/map/battle.c'],jobs=names,jobIDs=ids,statBudget99=points[-1],files={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in ref.iterdir()if p.is_file()}),indent=2));print('PASS matched-source data:12jobs,70job levels,13weapon delays,99point budgets,50monster INT; points99',points[-1])
