"""MIT. Read-only, hash-checked extraction of matching actors/world from a Test47 ISO.
Usage: python stage_base_assets46.py /path/to/MyRO-Current.iso
Refuses to replace an existing different asset; never edits the ISO.
"""
from pathlib import Path
import hashlib,struct,sys
root=Path(__file__).resolve().parent.parent
b=Path(sys.argv[1]).read_bytes()
assert b[65536:65556]==b'MICROSOFT*XBOX*MEDIA'
sector,size=struct.unpack_from('<II',b,65556)
expected={'world.bin': ('Packed', '42aafbd049085d103a14284d1ce9d6153090c9d9329758bdbea47a6eb4c0902f'), 'actors.bin': ('Actors', '582d03867110ddb304683d25f7a649b3e6ec6038e3686baa04331e888faa13e1'), 'enemies.bin': ('Enemies', 'e067b5586c659be81c3d455eb732f3f97747981af3a061fbd6529b7dae2078b1'), 'effects.bin': ('Effects', '25a14c952e1a39913eb9a500594768c08d90a920f29c28f7053930fdebf2fe17')}
found=set()
def visit(offset):
 assert offset+14<=size
 left,right,start,length,attr,n=struct.unpack_from('<HHIIBB',b,sector*2048+offset)
 assert offset+14+n<=size
 name=b[sector*2048+offset+14:sector*2048+offset+14+n].decode('ascii')
 if left:visit(left*4)
 if name in expected:
  directory,sha=expected[name];data=b[start*2048:start*2048+length]
  assert hashlib.sha256(data).hexdigest()==sha
  dest=root/directory/name;dest.parent.mkdir(exist_ok=True)
  if dest.exists():assert dest.read_bytes()==data,'Existing different asset: '+str(dest)
  else:dest.write_bytes(data)
  found.add(name);print('Verified/staged',dest)
 if right:visit(right*4)
visit(0);assert found==set(expected)
