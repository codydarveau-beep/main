"""MIT. Read-only, hash-checked extraction of matching actors/world from a Test43/Test44 ISO.
Usage: python stage_base_assets38.py /path/to/MyRO-Current.iso
Refuses to replace an existing different asset; never edits the ISO.
"""
from pathlib import Path
import hashlib,struct,sys
root=Path(__file__).resolve().parent.parent
b=Path(sys.argv[1]).read_bytes()
assert b[65536:65556]==b'MICROSOFT*XBOX*MEDIA'
sector,size=struct.unpack_from('<II',b,65556)
expected={'world.bin': ('Packed', '5044852dd681d9586dd51f809393f942cafe11eefd04b1dbac2a96fc031c16e1'), 'actors.bin': ('Actors', '1d52d8831abd8d17d9895c9b7db9b36c4c9e1ce894eddf409f1f4fe7775a3b47'), 'enemies.bin': ('Enemies', 'bef083e051dca02fc006018dd7477ee99ee0f165533a588bfb880d07ef735687')}
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
