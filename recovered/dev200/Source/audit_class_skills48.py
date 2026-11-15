# GPL-3.0-or-later. Preserve the supplied class trees and skill parameters for implementation review.
from pathlib import Path
import re,json,hashlib
r=Path(__file__).resolve().parent;root=r.parent.parent/'asset-library/Test48-followup/server/db/pre-re';tree=(root/'skill_tree.conf').read_text();db=(root/'skill_db.conf').read_text()
def block(text,start):
 a=text.index('{',start);depth=1;b=a+1
 while depth:
  if text[b]=='{':depth+=1
  elif text[b]=='}':depth-=1
  b+=1
 return text[a+1:b-1],b
entries={}
for m in re.finditer(r'(?m)^\{\s*\n\s*Id:\s*(\d+)',db):
 b,_=block(db,m.start());name=re.search(r'\bName:\s*"([^"]+)"',b);entries[name[1]]=b
result={}
for job in ['Wizard','Sage','Crusader','High_Wizard']:
 m=re.search(r'(?m)^'+job+r':\s*\{',tree);b,_=block(tree,m.start());m=re.search(r'\bskills:\s*\{',b);s,_=block(b,m.start());rows=[];pos=0
 while True:
  m=re.search(r'(?m)^\s*([A-Z][A-Z0-9_]+):\s*(\d+|\{)',s[pos:])
  if not m:break
  name=m[1];at=pos+m.start();end=pos+m.end()
  if m[2]=='{':sub,end=block(s,at);maxrank=int(re.search(r'MaxLevel:\s*(\d+)',sub)[1]);needs={k:int(v)for k,v in re.findall(r'([A-Z][A-Z0-9_]+):\s*(\d+)',sub)}
  else:maxrank=int(m[2]);needs={}
  raw=entries.get(name);assert raw,name
  rows.append(dict(key=name,maxRank=maxrank,prerequisites=needs,source=raw.strip(),implementation='pending review'))
  pos=end
 result[job]=rows
out=dict(source='User-supplied Hercules pre-renewal DB',sha256={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in [root/'skill_db.conf',root/'skill_tree.conf']},classes=result)
(r/'class_skill_audit48.json').write_text(json.dumps(out,indent=2,ensure_ascii=False));print({k:len(v)for k,v in result.items()})
