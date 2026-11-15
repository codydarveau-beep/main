"""MIT. Read-only, hash-checked extraction of matching actors/world from a Test45 ISO.
Usage: python stage_base_assets38.py /path/to/MyRO-Current.iso
Refuses to replace an existing different asset; never edits the ISO.
"""
from pathlib import Path
import hashlib,struct,sys
root=Path(__file__).resolve().parent.parent
b=Path(sys.argv[1]).read_bytes()
assert b[65536:65556]==b'MICROSOFT*XBOX*MEDIA'
sector,size=struct.unpack_from('<II',b,65556)
expected={'world.bin': ('Packed', '804de47f3a46c8278ca6cc77aecc223042b1758a7dfba3ade906ebb02ee07972'), 'actors.bin': ('Actors', 'de0b0d58fb3cf0ba91f05d550f03d4a17dc61922b65d47aa023656d593e8b658'), 'enemies.bin': ('Enemies', '7a3eccee8f6cd000b83d505898461841334f60e88681438ad1bbaa17a92c21c3'), 'effects.bin': ('Effects', '25a14c952e1a39913eb9a500594768c08d90a920f29c28f7053930fdebf2fe17')}
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
