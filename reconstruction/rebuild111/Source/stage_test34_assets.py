"""MIT. Read-only, hash-checked extraction of unchanged actors/world from Test34 ISO.
Usage: python stage_test34_assets.py /path/to/MyRO-34.iso
Refuses to replace an existing different asset; never edits the ISO.
"""
from pathlib import Path
import hashlib,struct,sys
root=Path(__file__).resolve().parent.parent
b=Path(sys.argv[1]).read_bytes()
assert hashlib.sha256(b).hexdigest()=='5c0dd53a674ab78a9333677edde3aae3f8a20c72399d1c346033c779621a44dd','Not the exact Test34 ISO'
assert b[65536:65556]==b'MICROSOFT*XBOX*MEDIA'
sector,size=struct.unpack_from('<II',b,65556)
expected={'actors.bin':('Actors','fadf7d21a9a41f36fdd39d6e17e716c7c5290ddec9bed1a7ea7d47c00b1f5be5'),'world.bin':('Packed','16db02f46c7ea7821fb22cb0421a65c6903492f5ed9330987bc280c548081c96')}
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
