"""MIT. Stage verified Test49 assets from Test48 plus the included replacement effect tail.
Reads the ISO without modifying it; refuses to overwrite different existing assets.
Usage: python3 stage_base_assets49.py /path/to/MyRO-Current.iso
"""
from pathlib import Path
import hashlib,struct,sys,json
s=Path(__file__).resolve().parent;root=s.parent;meta=json.loads((s/'stage_assets49.json').read_text());b=Path(sys.argv[1]).read_bytes();sha=lambda b:hashlib.sha256(b).hexdigest()
assert b[65536:65556]==b'MICROSOFT*XBOX*MEDIA','Not an Xbox ISO';sector,size=struct.unpack_from('<II',b,65556);found={}
def visit(offset):
 assert 0<=offset and offset+14<=size
 left,right,start,length,attr,n=struct.unpack_from('<HHIIBB',b,sector*2048+offset);assert offset+14+n<=size
 name=b[sector*2048+offset+14:sector*2048+offset+14+n].decode('ascii')
 if left:visit(left*4)
 if name in meta:
  q=meta[name];data=b[start*2048:start*2048+length];h=sha(data)
  if h!=q['targetSHA256']:
   assert h==q['baselineSHA256'],'Wrong baseline pack: '+name
   if q.get('patch'):
    extra=(s/q['patch']).read_bytes();assert sha(extra)==q['patchSHA256'];data=data[:q['keepBytes']]+extra
  assert sha(data)==q['targetSHA256'],'Target pack mismatch: '+name;found[name]=(q['directory'],data)
 if right:visit(right*4)
visit(0);assert set(found)==set(meta),'Missing required ISO packs'
# Verify every destination before creating any pack.
for name,(directory,data)in found.items():
 dest=root/directory/name
 if dest.exists():assert dest.read_bytes()==data,'Existing different asset: '+str(dest)
for name,(directory,data)in found.items():
 dest=root/directory/name;dest.parent.mkdir(exist_ok=True)
 if not dest.exists():dest.write_bytes(data)
 print('Verified/staged',dest)
