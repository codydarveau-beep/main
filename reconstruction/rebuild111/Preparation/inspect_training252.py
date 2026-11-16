from pathlib import Path
import json
r=Path(__file__).resolve().parent.parent;d=json.loads((r.parent/'packet194/released-program-index.json').read_text());print(type(d),list(d)[:8])
if isinstance(d,dict):
 for k,v in d.items():
  if isinstance(v,list):
   print(k,len(v),list(v[0])if v and isinstance(v[0],dict)else'')
   if len(v)>=3875:print(json.dumps(v[3874],indent=2)[:4000])
