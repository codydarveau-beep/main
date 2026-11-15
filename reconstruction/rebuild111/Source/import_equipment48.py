# GPL-3.0-or-later. Expand job permissions from supplied pre-renewal item DB.
from pathlib import Path
import re,json
r=Path(__file__).resolve().parent;src=(r.parent.parent/'asset-library/Test48-followup/server/db/pre-re/item_db.conf').read_text();db={int(m[1]):m[2]for m in re.finditer(r'(?ms)^\{\s*Id:\s*(\d+)\s*(.*?)^\},?\s*$',src)};jobs=['Novice','Swordsman','Magician','Acolyte','Thief','Archer','Merchant','Knight','Wizard','Wizard','Sage','Crusader']
p=r/'inventory.h';s=p.read_text();a=s.index('static const ItemDef');b=s.index('\n};',a)
def patch(m):
 vals=json.loads('['+m[1]+']')
 if len(vals)<14 or not vals[7]:return m[0]
 block=db[vals[0]];j=re.search(r'(?s)\bJob:\s*\{(.*?)\}',block)
 mask=sum(1<<i for i,n in enumerate(jobs)if not j or(re.search(r'\bAll:\s*true',j[1])and not re.search(r'\b'+n+r':\s*false',j[1]))or re.search(r'\b'+n+r':\s*true',j[1]));vals[8]=mask
 return '{'+','.join(json.dumps(v,ensure_ascii=False)for v in vals)+'}'
s=s[:a]+re.sub(r'\{([^{}]+)\}',patch,s[a:b])+s[b:];p.write_text(s)
p=r/'equipment46.json';entries=json.loads(p.read_text())
for e in entries:
 j=re.search(r'(?s)\bJob:\s*\{(.*?)\}',db[e['id']]);e['jobs']=sum(1<<i for i,n in enumerate(jobs)if not j or(re.search(r'\bAll:\s*true',j[1])and not re.search(r'\b'+n+r':\s*false',j[1]))or re.search(r'\b'+n+r':\s*true',j[1]))
p.write_text(json.dumps(entries,indent=2));print('PASS exact source permissions expanded to12 jobs')
