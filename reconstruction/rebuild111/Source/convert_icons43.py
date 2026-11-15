# MIT. Append supplied source icons in unused atlas area; retain old icon IDs.
from pathlib import Path
from PIL import Image,ImageDraw
import re,zlib,json
r=Path(__file__).resolve().parent;assets=r.parent.parent/'asset-library/Classes43-return/data/texture';skills=json.loads((r/'second-skills43.json').read_text());p=r/'skin_assets.c';s=p.read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',s,re.S)[1])));im=Image.frombytes('RGBA',(512,512),zlib.decompress(cp),'raw','BGRA');rects=[];report=[]
for i,skill in enumerate(skills):
 candidates=list(assets.rglob(skill['key'].lower()+'.bmp'));x=2+(i%16)*28;y=332+(i//16)*28
 if candidates:
  icon=Image.open(candidates[0]).convert('RGBA').resize((24,24));pixels=icon.load()
  for yy in range(24):
   for xx in range(24):
    rr,gg,bb,aa=pixels[xx,yy]
    if rr>230 and gg<20 and bb>230:pixels[xx,yy]=(rr,gg,bb,0)
 else:
  icon=Image.new('RGBA',(24,24),(30,80,145,255));ImageDraw.Draw(icon).text((2,5),str(skill['id']),fill='white')
 im.paste(icon,(x,y));rects.append([x,y,24,24]);report.append({'id':skill['id'],'file':str(candidates[0])if candidates else 'numbered placeholder'})
cp=zlib.compress(im.tobytes('raw','BGRA'),9);p.write_text('/* Shared HUD atlas; second-job icons appended in unused rows. */\nconst unsigned int skin_image_raw=1048576,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%len(cp)+','.join(map(str,cp))+'\n};\n')
p=r/'skin_data.h';s=p.read_text();a=s.index('};',s.index('skinRects'));s=s[:a]+''.join('{'+','.join(map(str,x))+'},\n'for x in rects)+s[a:];p.write_text(s);(r/'icons43.json').write_text(json.dumps(report,indent=2))
