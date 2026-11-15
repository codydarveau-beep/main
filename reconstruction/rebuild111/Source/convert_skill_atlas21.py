"""MIT. Add eight original skill icons and rebuild padded damage digits.
Usage: python convert_skill_atlas21.py HUD-Assets.zip
Idempotent: atlas remains 512x256, so no additional runtime texture allocation.
"""
from pathlib import Path
import re,zlib,zipfile,csv,io,hashlib,sys,json
from PIL import Image,ImageFont,ImageDraw
s=Path(__file__).resolve().parent;p=s/'skin_assets.c'
cp=bytes(map(int,re.search(r'skin_image\[\]=\{(.*?)\};',p.read_text(),re.S)[1].replace('\n','').strip().strip(',').split(',')))
im=Image.frombytes('RGBA',(512,256),zlib.decompress(cp),'raw','BGRA')
names=['mg_lightningbolt.bmp','mg_napalmbeat.bmp','mg_soulstrike.bmp','mg_fireball.bmp','mg_srecovery.bmp','sm_recovery.bmp','sm_provoke.bmp','sm_endure.bmp'];rects=[(288+26*i,118,24,24)for i in range(7)]+[(256,160,24,24)]
report=[]
with zipfile.ZipFile(sys.argv[1])as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 for name,(x,y,w,h)in zip(names,rects):
  r=next(r for r in rows if r['virtual_path'].lower().endswith('\\'+name));b=z.read(r['payload']);assert hashlib.sha256(b).hexdigest()==r['sha256'];icon=Image.open(io.BytesIO(b)).convert('RGBA').resize((w,h));icon.putdata([(rr,gg,bb,0 if rr>245 and gg<12 and bb>245 else aa)for rr,gg,bb,aa in icon.getdata()]);im.paste(icon,(x,y));report.append({'icon':name,'sha256':r['sha256'],'rect':[x,y,w,h]})
font=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf',14)
for yellow,y in [(False,144),(True,162)]:
 for digit in range(10):
  cell=Image.new('RGBA',(12,18));d=ImageDraw.Draw(cell);c=str(digit);bb=font.getbbox(c,stroke_width=1);x=(12-(bb[2]-bb[0]))//2-bb[0];yy=(18-(bb[3]-bb[1]))//2-bb[1];d.text((x,yy),c,font=font,fill=(255,225,45,255)if yellow else(255,255,255,255),stroke_width=1,stroke_fill=(36,30,20,220));bbox=cell.getbbox();assert bbox[1]>0 and bbox[3]<18,(digit,bbox);im.paste(cell,(384+digit*12,y))
raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9);p.write_text('/* Original client artwork plus padded damage digits. */\nconst unsigned int skin_image_raw=%d,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%(len(raw),len(cp))+''.join(','.join(map(str,cp[i:i+32]))+',\n'for i in range(0,len(cp),32))+'};\n')
p=s/'skin_data.h';old=re.findall(r'\{\d+,\d+,\d+,\d+\}',p.read_text())[:38];assert len(old)==38;p.write_text('/* Original client icon rectangles; added Test21 skills at 38..45. */\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join(old+['{%d,%d,%d,%d}'%r for r in rects])+'\n};\n');im.save(s.parent/'skill-atlas21.png');(s.parent/'SKILL-ICONS-REPORT.json').write_text(json.dumps(report,indent=2));print('PASS eight checksum-verified original icons and padded digits; atlas remains',len(raw),'bytes')
