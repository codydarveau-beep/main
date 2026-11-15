"""MIT. Pack only selected original item images into unused shared HUD atlas cells."""
from pathlib import Path
import re,zlib,json,sys
from PIL import Image,ImageDraw
s=Path(__file__).resolve().parent;lib=Path(sys.argv[1]);r=lib/'Test46-equipment-art';table=(lib/'Test46-followup/data/idnum2itemresnametable.txt').read_bytes().decode('cp949');mapping={int(a):b for a,b in re.findall(r'(?m)^\s*(\d+)#([^#\r\n]+)#',table)}
p=s/'skin_assets.c';t=p.read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',t,re.S)[1])));im=Image.frombytes('RGBA',(512,512),zlib.decompress(cp),'raw','BGRA');meta=(s/'skin_data.h').read_text();rects=[tuple(map(int,re.findall(r'\d+',v)))for v in re.findall(r'\{\d+,\d+,\d+,\d+\}',meta)];occupied=Image.new('1',(512,512));d=ImageDraw.Draw(occupied)
for x,y,w,h in rects+[(0,0,256,128),(0,160,256,96),(384,144,120,36),(480,184,32,32),(0,256,512,8),(288,144,96,72)]:d.rectangle((max(0,x-1),max(0,y-1),min(511,x+w),min(511,y+h)),fill=1)
report=[];icons=[]
for item in json.loads((s/'equipment46.json').read_text()):
 name=mapping[item['id']].lower()+'.bmp';path=r/'data/texture/유저인터페이스/item'/name;headpath=r/'data/sprite/악세사리/남'/(('남_'+mapping[item['id']]).lower()+'.spr');assert path.exists()or headpath.exists(),path
 found=None
 for y in range(128,492):
  for x in range(492):
   if not occupied.crop((x,y,x+22,y+22)).getbbox():found=x,y;break
  if found:break
 if not found:raise RuntimeError('Atlas full')
 
 if path.exists():icon=Image.open(path).convert('RGBA')
 else:
  import ro_sprite_bake as ro
  source=next(x for x in ro.spr(headpath.read_bytes())if x.getbbox());source=source.crop(source.getbbox());icon=Image.new('RGBA',(32,32));icon.alpha_composite(source,((32-source.width)//2,(32-source.height)//2))
 icon.putdata([(rr,gg,bb,0 if rr>245 and gg<12 and bb>245 else aa)for rr,gg,bb,aa in icon.getdata()]);icon=icon.resize((20,20),Image.Resampling.LANCZOS);x,y=found;im.paste(icon,(x,y));d.rectangle((x,y,x+21,y+21),fill=1);icons.append(len(rects));rects.append((x,y,20,20));report.append(dict(id=item['id'],name=name,rect=rects[-1]))
cp=zlib.compress(im.tobytes('raw','BGRA'),9);p.write_text('/* Original selected equipment artwork; unchanged512x512 atlas allocation. */\nconst unsigned int skin_image_raw=1048576,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%len(cp)+','.join(map(str,cp))+'\n};\n');defs='\n'.join(x for x in meta.splitlines()if x.startswith('#define'));(s/'skin_data.h').write_text(defs+'\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join('{%d,%d,%d,%d}'%v for v in rects)+'\n};\n');p=s/'window_draw.h';t=p.read_text();m=re.search(r'itemIcons\[ITEM_COUNT\]=\{([^}]+)\}',t);old=list(map(int,m[1].split(',')))[:18];t=t[:m.start(1)]+','.join(map(str,old+icons))+t[m.end(1):];p.write_text(t);(s/'item_icons46.json').write_text(json.dumps(report,indent=2));print('PASS',len(icons),'original item icons, same1MiB GPU atlas');im.save(s.parent/'HUD-Atlas46.png')
