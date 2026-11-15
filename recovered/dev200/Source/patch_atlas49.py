# MIT. User-requested exact neighboring texture clone; no repaint or generated artwork.
# Also bake equipped-item alpha once into unused atlas cells, keeping GPU allocation1MiB.
from pathlib import Path
import re,zlib
from PIL import Image,ImageDraw
r=Path(__file__).resolve().parent;b=r.parent.parent/'test48/Source';s=(b/'skin_assets.c').read_text();data=bytes(map(int,re.search(r'skin_image\[\]=\{(.*?)\};',s,re.S)[1].split(',')));original=Image.frombytes('RGBA',(512,512),zlib.decompress(data),'raw','BGRA');im=Image.new('RGBA',(512,640));im.paste(original,(0,0));before=im.copy();defs=(b/'skin_data.h').read_text();rects=[tuple(map(int,re.findall(r'\d+',v)))for v in re.findall(r'\{\d+,\d+,\d+,\d+\}',defs)];x,y,w,h=rects[9]
# Cover the six bright middle-finger pixels with the adjacent finger's texture.
for yy in range(6,12):im.putpixel((x+12,y+yy),before.getpixel((x+10,y+yy)))
reserved=[(0,0,256,128),(0,160,256,96),(384,144,120,36),(480,184,32,32),(0,256,512,8),(288,144,96,72)];mask=Image.new('1',(512,640));draw=ImageDraw.Draw(mask)
for xx,yy,ww,hh in rects+reserved:draw.rectangle((max(0,xx-1),max(0,yy-1),min(511,xx+ww),min(639,yy+hh)),fill=1)
text=(b/'window_draw.h').read_text();body=re.search(r'itemIcons\[ITEM_COUNT\]=\{([^}]+)',text)[1];macros={a:int(v)for a,v in re.findall(r'#define (\w+) (\d+)',defs)};ids=[]
for value in body.split(','):
 for name,val in macros.items():value=value.replace(name,str(val))
 assert re.fullmatch('[0-9+ ]+',value);ids.append(eval(value,{'__builtins__':{}}))
assert len(ids)==115
itemblock=(b/'inventory.h').read_text().split('static const ItemDef')[1].split('\n};')[0];import json
entries=[json.loads('['+m[1]+']')for m in re.finditer(r'\{([^{}]+)\}',itemblock)];assert len(entries)==115
new=[]
for id,entry in zip(ids,entries):
 if len(entry)<8 or not entry[7]:new.append(id);continue
 xx,yy,ww,hh=rects[id];icon=im.crop((xx,yy,xx+ww,yy+hh));icon.putalpha(icon.getchannel('A').point(lambda a:a//2));spot=None
 for yy in range(512,640-hh-2):
  for xx in range(512-ww-2):
   if not mask.crop((xx,yy,xx+ww+2,yy+hh+2)).getbbox():spot=(xx,yy);break
  if spot:break
 assert spot,'No free atlas cell after '+str(len(rects));xx,yy=spot;im.paste(icon,(xx+1,yy+1));draw.rectangle((xx,yy,xx+ww+1,yy+hh+1),fill=1);new.append(len(rects));rects.append((xx+1,yy+1,ww,hh))
# Every old runtime pixel except the six requested clone pixels remains exact.
for xx,yy,ww,hh in rects[:len(ids)]+reserved:
 if(xx,yy,ww,hh)==(x,y,w,h):continue
 assert im.crop((xx,yy,xx+ww,yy+hh)).tobytes()==before.crop((xx,yy,xx+ww,yy+hh)).tobytes()
expected=before.copy()
for yy in range(6,12):expected.putpixel((x+12,y+yy),before.getpixel((x+10,y+yy)))
assert im.crop((0,0,512,512)).tobytes()==expected.crop((0,0,512,512)).tobytes()
cp=zlib.compress(im.tobytes('raw','BGRA'),9);(r/'skin_assets.c').write_text('/* Test49: exact hand texture clone and equipped-item half-alpha cells. */\nconst unsigned int skin_image_raw=1310720,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%len(cp)+','.join(map(str,cp))+'\n};\n');head='\n'.join(v for v in defs.splitlines()if v.startswith('#define'));(r/'skin_data.h').write_text(head+'\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join('{%d,%d,%d,%d}'%q for q in rects)+'\n};\nstatic const unsigned short itemDim49[115]={'+','.join(map(str,new))+'};\n');im.crop((x,y,x+w,y+h)).save(r.parent/'FirstAid49.png');print('PASS hand clone and',sum(a!=b for a,b in zip(ids,new)),'half-alpha equipment icons; original atlas regions retained')
