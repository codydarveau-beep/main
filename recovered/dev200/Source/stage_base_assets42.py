"""MIT. Read-only, hash-checked extraction of unchanged actors/world from a verified Test37, Test36, Test35 or Test34 ISO.
Usage: python stage_base_assets38.py /path/to/MyRO-Current.iso
Refuses to replace an existing different asset; never edits the ISO.
"""
from pathlib import Path
import hashlib,struct,sys
root=Path(__file__).resolve().parent.parent
b=Path(sys.argv[1]).read_bytes()
assert hashlib.sha256(b).hexdigest() in {'0c808b6a4a958983185fe7f94ee9b77fc593950d9118e6bf5c73835b69500727','24e06f24f0491539e82382feeff79aec880333ebd700ff8dd9456e6166306d26','6fb3f47c9f841f24e1223d3ff6b4b77d635daffc5d7876ad4820391dbfc6b704','03e0687daf667abe166ae9e85b663b077fb09711f04fd8a00d6d511ab0aabd4f','6c4b9c7ad163de826c0961cf9903b68dd5e2bc06ffc62202646524873fa127d1','f9eedc05a42468c6de9bd980ccf95bd8c09d1ac3635ec759baf0bb36215e7d8a','5c0dd53a674ab78a9333677edde3aae3f8a20c72399d1c346033c779621a44dd','bdc608cb19dac7e47e7d2becfaff383f2f83a0c827e5bc4794bafd7e79c44e7d'},'Not a verified Test34/Test35/Test36/Test37 ISO'
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
