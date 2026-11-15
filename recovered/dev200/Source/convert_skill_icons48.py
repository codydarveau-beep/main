# MIT. Original client skill/reagent icons; protect all existing runtime atlas regions.
from pathlib import Path
import json,re,zlib
from PIL import Image,ImageDraw
r=Path(__file__).resolve().parent;base=r.parent.parent/'test47a/Source';lib=r.parent.parent/'asset-library';paths={}
for folder in lib.iterdir():
 if folder.is_dir():
  for p in(folder/'data').rglob('*'):
   if p.is_file():paths[str(p.relative_to(folder)).replace('/','\\').lower()]=p
text=(base/'skin_assets.c').read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',text,re.S)[1])));im=Image.frombytes('RGBA',(512,512),zlib.decompress(cp),'raw','BGRA');original=im.copy();defs=(base/'skin_data.h').read_text();rects=[tuple(map(int,re.findall(r'\d+',v)))for v in re.findall(r'\{\d+,\d+,\d+,\d+\}',defs)];oldrects=rects.copy();reserved=[(0,0,256,128),(0,160,256,96),(384,144,120,36),(480,184,32,32),(0,256,512,8),(288,144,96,72)];mask=Image.new('1',(512,512));draw=ImageDraw.Draw(mask)
for x,y,w,h in oldrects+reserved:draw.rectangle((max(0,x-1),max(0,y-1),min(511,x+w),min(511,y+h)),fill=1)
def put(key):
 p=paths[key.lower()];icon=Image.open(p).convert('RGBA');pixels=icon.load()
 for y in range(icon.height):
  for x in range(icon.width):
   rr,g,b,a=pixels[x,y]
   if rr==255 and g==0 and b==255:pixels[x,y]=(rr,g,b,0)
 icon=icon.resize((20,20),Image.Resampling.LANCZOS);found=None
 for y in range(128,491):
  for x in range(491):
   if not mask.crop((x,y,x+22,y+22)).getbbox():found=x,y;break
  if found:break
 assert found,'Atlas capacity exhausted'
 x,y=found;im.paste(icon,(x+1,y+1));draw.rectangle((x,y,x+21,y+21),fill=1);rects.append((x+1,y+1,20,20))
rows=json.loads((r/'new_class_skills48.json').read_text());skillbase=len(rects)
for q in rows:put('data\\texture\\유저인터페이스\\item\\'+q['key'].lower()+'.bmp')
materialbase=len(rects);ids=[715,904,946,947,990,991,992,993,7006,7433,12114,12115,12116,12117];t=paths['data\\idnum2itemresnametable.txt'].read_bytes().decode('cp949',errors='replace');names={int(m[1]):m[2]for m in re.finditer(r'(?m)^(\d+)#([^#\r\n]+)#',t)}
for id in ids:put('data\\texture\\유저인터페이스\\item\\'+names[id]+'.bmp')
bookicon=len(rects);put("data\\texture\\유저인터페이스\\item\\북.bmp")
for x,y,w,h in oldrects+reserved:assert im.crop((x,y,x+w,y+h)).tobytes()==original.crop((x,y,x+w,y+h)).tobytes()
cp=zlib.compress(im.tobytes('raw','BGRA'),9);(r/'skin_assets.c').write_text('/* Original client UI; all47a runtime regions byte-identical. */\nconst unsigned int skin_image_raw=1048576,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%len(cp)+','.join(map(str,cp))+'\n};\n');(r/'skin_data.h').write_text('#define SKIN46_SLOT 108\n#define SKIN48_SKILL_BASE %d\n#define SKIN48_MATERIAL_BASE %d\n#define SKIN48_BOOK %d\nstatic const unsigned short skinRects[][4]={\n'%(skillbase,materialbase,bookicon)+',\n'.join('{%d,%d,%d,%d}'%q for q in rects)+'\n};\n');print('PASS38skill+14materialoriginalicons, unchanged1MiB512atlas; ALLoriginalfont/damage/icon/palette/minimap pixels preserved')
