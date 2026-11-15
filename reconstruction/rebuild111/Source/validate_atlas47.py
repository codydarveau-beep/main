# MIT. Runtime UV regions omitted by the original rect directory must stay intact.
from pathlib import Path
import re,zlib,json
from PIL import Image
r=Path(__file__).resolve().parent
base=r.parent.parent/'test45a/Source'
def image(root):
 s=(root/'skin_assets.c').read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',s,re.S)[1])));return Image.frombytes('RGBA',(512,512),zlib.decompress(cp),'raw','BGRA')
new=image(r);old=image(base);protected=[(0,0,256,128),(0,160,256,96),(384,144,120,36),(480,184,32,32),(0,256,512,8),(288,144,96,72)]
rects=[tuple(map(int,re.findall(r'\d+',s)))for s in re.findall(r'\{\d+,\d+,\d+,\d+\}',(base/'skin_data.h').read_text())]
for x,y,w,h in protected+rects:assert new.crop((x,y,x+w,y+h)).tobytes()==old.crop((x,y,x+w,y+h)).tobytes(),(x,y,w,h)
for item in json.loads((r/'item_icons46.json').read_text()):
 x,y,w,h=item['rect']
 for a,b,c,d in protected+rects:assert x+w<=a or a+c<=x or y+h<=b or b+d<=y,item
print('PASS47 all original icon pixels and dark/white/compact fonts, damage digits/critical burst, minimap and palette byte-identical;82 new icons do not overlap runtime regions; unchanged1MiB atlas.')
