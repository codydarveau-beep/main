"""MIT. Dedicated nonoverlapping glyph/damage/icon areas,512x512 shared texture."""
from pathlib import Path
import re,zlib,json,hashlib
from PIL import Image,ImageDraw
r=Path(__file__).resolve().parent
def read(p):
 s=p.read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',s,re.S)[1])));raw=zlib.decompress(cp);return Image.frombytes('RGBA',(512,len(raw)//2048),raw,'raw','BGRA')
im=read(r/'skin_assets.c');out=Image.new('RGBA',(512,512));out.paste(im,(0,0));base=read(r.parent.parent/'Xbox-Test-27/Source/skin_assets.c') if False else read(Path('Xbox-Test-27/Source/skin_assets.c'))
rects=[tuple(map(int,re.findall(r'\d+',v)))for v in re.findall(r'\{\d+,\d+,\d+,\d+\}',(r/'skin_data.h').read_text())];icons=[im.crop((x,y,x+w,y+h))for x,y,w,h in rects[48:]]
# Recover precisely the accepted damage digits and critical burst, unchanged.
for box in [(384,144,504,180),(480,184,512,216)]:out.paste(base.crop(box),box[:2])
for i,icon in enumerate(icons):x=i*26;y=272;out.paste(icon,(x,y));rects[48+i]=(x,y,24,24)
colors=list(map(lambda x:int(x,16),re.findall(r'0xff[0-9a-fA-F]{6}',(r/'skin_colors.h').read_text())));colors.append(0xffa96f6f)
for i,c in enumerate(colors):x=(i%64)*8;y=256+(i//64)*8;ImageDraw.Draw(out).rectangle((x,y,x+5,y+5),fill=((c>>16)&255,(c>>8)&255,c&255,c>>24))
(r/'skin_colors.h').write_text('/* Protected solid-color row y256. */\nstatic const unsigned skinColors[]={'+','.join(hex(c)+'u'for c in colors)+'};\n')
raw=out.tobytes('raw','BGRA');cp=zlib.compress(raw,9);(r/'skin_assets.c').write_text('/* Original client art. Font,damage,minimap and icons have disjoint regions. */\nconst unsigned int skin_image_raw=%d,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%(len(raw),len(cp))+','.join(map(str,cp))+'\n};\n');(r/'skin_data.h').write_text('/* Stable icon indices. */\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join('{%d,%d,%d,%d}'%v for v in rects)+'\n};\n')
(r.parent/'ATLAS29-REPORT.json').write_text(json.dumps(dict(width=512,height=512,extraResidentBytes=512*256*4,damageSourceSHA256=hashlib.sha256(base.crop((384,144,504,180)).tobytes()).hexdigest(),criticalSourceSHA256=hashlib.sha256(base.crop((480,184,512,216)).tobytes()).hexdigest(),icons={str(i):v for i,v in enumerate(rects)}),indent=2))
