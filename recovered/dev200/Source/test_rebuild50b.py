"""MIT. Compare a clean release rebuild against the frozen native build."""
from pathlib import Path
import hashlib,struct
r=Path(__file__).resolve().parent.parent.parent
frozen=r/'test50b/XboxFiles';rebuilt=r/'release50b/XboxFiles'
a=bytearray((frozen/'default.xbe').read_bytes());b=bytearray((rebuilt/'default.xbe').read_bytes());assert len(a)==len(b)
changes=[i for i in range(len(a))if a[i]!=b[i]]
allowed={i for pos in [0x114,0x148,0x17c]for i in range(pos,pos+4)};assert set(changes)<=allowed,changes[:40]
for pos in [0x114,0x148,0x17c]:a[pos:pos+4]=b'\0'*4;b[pos:pos+4]=b'\0'*4
assert a==b
for name in ['world.bin','actors.bin','effects.bin','enemies.bin','music.bin','systems.bin']:assert (frozen/name).read_bytes()==(rebuilt/name).read_bytes(),name
assert struct.unpack_from('<I',a,0x130)[0]==131072
print('PASS50b clean matching source rebuild: all native code/data and six disc packs byte-identical; only allowed XBE header timestamps differ.128KiB stack retained.')
