"""MIT. Slightly stronger glyph coverage, same 11px outlines and advances.
Run once against Test22 skin_assets.c. No texture size change. UI info/Stats
now use native pixel size rather than resizing these glyphs fractionally.
"""
from pathlib import Path
import re,zlib,numpy as np
p=Path(__file__).with_name('skin_assets.c');s=p.read_text();match=re.search(r'const unsigned char skin_image\[\]=\{(.*?)\};',s,re.S);assert match
packed=bytes(map(int,re.findall(r'\d+',match[1])));a=np.frombuffer(zlib.decompress(packed),dtype='<u4').copy().reshape(256,512)
for y in [0,160]:
 part=a[y:y+96,:256];alpha=part>>24;alpha=np.minimum(255,(alpha*116+50)//100);part[:]=(part&0xffffff)|(alpha<<24)
raw=a.tobytes();cp=zlib.compress(raw,9);s=re.sub(r'skin_image_size=\d+',f'skin_image_size={len(cp)}',s);s=s[:s.index('const unsigned char skin_image')]+ 'const unsigned char skin_image[]={\n'+','.join(map(str,cp))+'\n};\n';p.write_text(s)
print('Native font contrast adjusted; atlas remains',len(raw),'bytes')
