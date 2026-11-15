"""MIT. Reproduce cart wheel-contact constants from generated artwork headers.
Run after convert_art40.py; no client files or network access needed.
"""
from pathlib import Path
import struct,re,zlib,json
r=Path(__file__).resolve().parent;s=(r/'art_assets40.h').read_text();packed=bytes(map(int,re.findall(r'\d+',re.search(r'art39Packed\[\]=\{(.*?)\};',s,re.S)[1])));m=json.loads((r/'art-manifest40.json').read_text());rows=[]
for clip in m['clips'][10:15]:
 b=zlib.decompress(packed[clip['offset']:clip['offset']+clip['packed']]);w,h,n,a,ns,ax,ay,pb=struct.unpack_from('<8I',b);seqoff=32+a*12;diroff=seqoff+ns*4;pixeloff=diroff+n*20;contacts=[]
 for d in range(8):
  start=struct.unpack_from('<I',b,32+d*12)[0];fi=struct.unpack_from('<I',b,seqoff+start*4)[0];x,y,ww,hh,off=struct.unpack_from('<5I',b,diroff+fi*20);pts=[]
  for yy in range(hh):
   for xx in range(ww):
    v=struct.unpack_from('<H',b,pixeloff+off+(yy*ww+xx)*2)[0]
    if v&0x8000:pts.append((x+xx,y+yy))
  bottom=max(y for x,y in pts)+1;feet=[x for x,y in pts if y>=bottom-4];contacts.append(((min(feet)+max(feet))*.5,bottom))
 rows.append(contacts)
(r/'cart_contact40.h').write_text('/* Generated ground-contact midpoint from lowest4 opaque pixel rows of each style/direction. */\nstatic const float cartContact40[5][8][2]={\n'+',\n'.join('{'+','.join('{%.1ff,%.1ff}'%p for p in row)+'}'for row in rows)+'\n};\n')
print('PASS40 five styles x eight direction ground contacts generated from actual opaque pixels')
