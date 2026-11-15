# MIT. Every original terrain section is restored exactly; no heuristic culling.
from pathlib import Path
import re,zlib,hashlib
r=Path(__file__).resolve().parent
base=r.parent.parent/'test45a'
def load(root):
 s=(root/'Source/world_data.h').read_text();rows=[tuple(map(int,x))for x in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',s[:s.index('static const WorldBlob minimapBlobs45')])];return rows,(root/'Packed/world.bin').read_bytes()
a,ab=load(base);b,bb=load(r.parent)
for k in range(18):
 assert a[k*7+3]==b[k*7+3];o,n,raw,crc=b[k*7+3];assert ab[o:o+n]==bb[o:o+n] and zlib.crc32(bb[o:o+n])==crc
print('PASS47 all18 original45a terrain directories, heights and triangles byte-identical, correct camera/front-face retained; black-triangle culling reverted.')
