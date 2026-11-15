"""MIT. Add returned original window backgrounds/slot art to unused atlas cells."""
from pathlib import Path
import re,zlib,json,sys
from PIL import Image,ImageDraw
s=Path(__file__).resolve().parent;r=Path(sys.argv[1]);p=s/'skin_assets.c';t=p.read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',t,re.S)[1])));im=Image.frombytes('RGBA',(512,512),zlib.decompress(cp),'raw','BGRA');rects=[tuple(map(int,re.findall(r'\d+',v)))for v in re.findall(r'\{\d+,\d+,\d+,\d+\}',(s/'skin_data.h').read_text())]
# Fixed existing atlas allocations, including font, minimap and palette.
occupied=Image.new('1',(512,512));d=ImageDraw.Draw(occupied)
for x,y,w,h in rects+[(0,0,256,128),(0,160,256,96),(384,144,120,36),(480,184,32,32),(0,256,512,8),(288,144,96,72)]:d.rectangle((max(0,x-1),max(0,y-1),min(511,x+w),min(511,y+h)),fill=1)
records=[];definitions=[]
for name,size,tag in [('itemwin_mid.bmp',(32,32),'SLOT')]:
 found=None
 for y in range(128,512-size[1]):
  for x in range(0,512-size[0]):
   if not occupied.crop((x,y,x+size[0]+2,y+size[1]+2)).getbbox():found=x,y;break
  if found:break
 if not found:raise RuntimeError('No atlas space: '+name)
 x,y=found;icon=Image.open(r/'data/texture/유저인터페이스/basic_interface'/name).convert('RGBA').resize(size,Image.Resampling.LANCZOS);im.paste(icon,(x,y));d.rectangle((x,y,x+size[0]+1,y+size[1]+1),fill=1);definitions.append('#define SKIN46_'+tag+' '+str(len(rects)));rects.append((x,y,*size));records.append(dict(name=name,rect=rects[-1]))
# White panel color already exists in the shared palette; no allocation growth.
cp=zlib.compress(im.tobytes('raw','BGRA'),9);p.write_text('/* Original client atlas: Test46 window fragments, unchanged1MiB allocation. */\nconst unsigned int skin_image_raw=1048576,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%len(cp)+','.join(map(str,cp))+'\n};\n');(s/'skin_data.h').write_text('/* Stable shared icon indices; original UI additions. */\n'+'\n'.join(definitions)+'\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join('{%d,%d,%d,%d}'%v for v in rects)+'\n};\n');(s/'skin46.json').write_text(json.dumps(records,indent=2));print(records)
