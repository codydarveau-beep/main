"""MIT. Stage all six verified Test50 disc packs without altering the ISO.
Usage: python3 stage_base_assets50.py /path/to/MyRO-Current.iso
The Test50 updater produces this input. Existing different packs are preserved.
"""
from pathlib import Path
import hashlib,json,struct,sys
root=Path(__file__).resolve().parent.parent
meta=json.loads((root/'Source/stage_assets50.json').read_text())
b=Path(sys.argv[1]).read_bytes();assert b[65536:65556]==b'MICROSOFT*XBOX*MEDIA','Not an Xbox ISO'
sector,size=struct.unpack_from('<II',b,65556);found={};visited=set()
def visit(offset):
 assert offset not in visited and 0<=offset<=size-14,'Invalid directory';visited.add(offset)
 pos=sector*2048+offset;left,right,start,length,attr,n=struct.unpack_from('<HHIIBB',b,pos);assert offset+14+n<=size
 name=b[pos+14:pos+14+n].decode('ascii');assert start*2048+length<=len(b)
 if left:visit(left*4)
 if name in meta:
  data=b[start*2048:start*2048+length];q=meta[name]
  assert len(data)==q['bytes'] and hashlib.sha256(data).hexdigest()==q['sha256'],'Use the matching Test50 ISO: '+name
  found[name]=(q['directory'],data)
 if right:visit(right*4)
visit(0);assert set(found)==set(meta),'Missing Test50 packs'
for name,(directory,data)in found.items():
 dest=root/directory/name
 assert not dest.exists() or dest.read_bytes()==data,'Existing different pack: '+str(dest)
for name,(directory,data)in found.items():
 dest=root/directory/name;dest.parent.mkdir(exist_ok=True)
 if not dest.exists():dest.write_bytes(data)
 print('Verified/staged',name,len(data),'bytes')
