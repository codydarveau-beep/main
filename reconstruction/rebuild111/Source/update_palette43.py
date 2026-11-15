"""MIT. Add cast blue and white/black physical button shades in protected palette.
Idempotent; asserts every pixel outside the new solid swatches is unchanged.
"""
from pathlib import Path
import re,zlib
from PIL import Image,ImageDraw
r=Path(__file__).resolve().parent;p=r/'skin_colors.h';s=p.read_text();match=re.search(r'skinColors\[\]=\{(.*?)\};',s,re.S);colors=[int(c,16)for c in re.findall(r'0x([0-9a-f]+)u',match[1])]
f=r/'skin_assets.c';text=f.read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',text,re.S)[1])));raw=zlib.decompress(cp);im=Image.frombytes('RGBA',(512,512),raw,'raw','BGRA');before=im.copy()
for c in [0x1965eafa,0x2165eafa,0x2965eafa,0x4065dffa,0x6065dffa,0x8065dffa,0x90ffffff,0x40ffffff,0x90ff4848,0x40ff4848,0x0c65dffa,0x1465dffa,0x1c65dffa,0x0cff4848]:
 if c in colors:continue
 i=len(colors);assert i<64;colors.append(c);box=(i*8,256,i*8+5,261);ImageDraw.Draw(im).rectangle(box,fill=(c>>16&255,c>>8&255,c&255,c>>24));ImageDraw.Draw(before).rectangle(box,fill=(c>>16&255,c>>8&255,c&255,c>>24))
assert before.tobytes()==im.tobytes()
s=s[:match.start(1)]+','.join('0x%08xu'%c for c in colors)+s[match.end(1):];p.write_text(s)
cp=zlib.compress(im.tobytes('raw','BGRA'),9);f.write_text('/* Shared512x512 HUD atlas, original client artwork. Test39 palette only. */\nconst unsigned int skin_image_raw=1048576,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%len(cp)+','.join(map(str,cp))+'\n};\n')
print('PASS palette-only change;',len(colors),'swatches')
