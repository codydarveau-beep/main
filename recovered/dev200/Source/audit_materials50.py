"""GPL-3.0-or-later. Source-backed solo crafting inputs/results and consumable art."""
from pathlib import Path
import json,re,hashlib
r=Path(__file__).resolve().parent;ref=r.parent.parent/'reference48';db=r.parent.parent/'asset-library/Test48-followup/server/db/pre-re';plan=json.loads((r/'class_plan50.json').read_text())
items={int(i):dict(key=k,name=n) for i,k,n in re.findall(r'(?m)^\{\s*\n\s*Id:\s*(\d+)\s*\n\s*AegisName:\s*"([^"]+)"\s*\n\s*Name:\s*"([^"]+)"',(db/'item_db.conf').read_text())};bykey={v['key']:i for i,v in items.items()};wanted={};recipes=[]
def add(i,why):
 assert i in items,('Unknown source item',i);wanted.setdefault(i,set()).add(why)
ids=set()
sourceSkills=dict(plan['skills']);sourceSkills.update(json.loads((r/'class_skill_audit50.json').read_text())['companionSkills'])
for key,row in sourceSkills.items():
 ids.add(int(re.search(r'Id:\s*(\d+)',row['source'])[1]))
 for section in re.findall(r'\bItems:\s*\{([^{}]+)\}',row['source']):
  for name in re.findall(r'\b([A-Za-z_][\w]*):\s*\d+',section):add(bykey[name],'skill:'+key)
for line in (ref/'test50-produce_db.txt').read_text().splitlines():
 line=line.split('//')[0].strip()
 if not line:continue
 q=list(map(int,line.split(',')))
 if q[2]not in ids:continue
 assert q[1]in [1,2,3,21,22] and len(q[4:])%2==0
 recipes.append(dict(product=q[0],itemLevel=q[1],skill=q[2],rank=q[3],materials=[dict(id=i,amount=a) for i,a in zip(q[4::2],q[5::2])]))
 add(q[0],'recipe:product')
 for i in q[4::2]:add(i,'recipe:material-or-guide')
# Source forging equipment/catalysts and Homunculus evolution/food items.
for i in [612,613,614,615,984,985,998,999,1000,7118,7134]:add(i,'class-tool-catalyst-or-companion-food')
homun=(ref/'test50-homunculus_db.conf').read_text()
for chunk in re.split(r'(?m)^\{',homun)[1:]:
 m=re.search(r'\bId:\s*(\d+)',chunk)
 if m and 6001<=int(m[1])<=6016:
  name=re.search(r'FoodItem:\s*"([^"]+)"',chunk)[1];add(bykey[name],'source-homunculus-food')
for i in [1201,1204,1213,1221,1250,1251,1252,1253,1301,1304,1351,1354,1501,1504,1514,1601,1604,1701,1704,1707,1710,1801,1804,1807,1901,1904,1907,1950,1953,1956]:add(i,'class-weapon')
out=r.parent.parent/'asset-request50/Second-Classes';(out/'Item-Requests50.tsv').write_text('\n'.join(str(i)+'\t'+items[i]['name'] for i in sorted(wanted))+'\n',encoding='utf-8-sig')
report=dict(sourceCommit='21b27966cfc2e7df0bf8151cd717a1105d047ba9',sourceHashes={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in [ref/'test50-produce_db.txt',ref/'test50-homunculus_db.conf',db/'item_db.conf']},recipes=recipes,items={i:dict(**items[i],uses=sorted(why))for i,why in sorted(wanted.items())},status='source audit; mechanics pending')
(r/'class_materials_audit50.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n');print('PASS50',len(recipes),'eligible source recipes;',len(wanted),'exact item IDs for skill reagents/crafting/guides/weapons/companion food; no later class recipes.')
