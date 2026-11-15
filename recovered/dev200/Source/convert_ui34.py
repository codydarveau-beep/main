"""Pack eight source icons + two translucent HUD shades; no larger allocation."""
from pathlib import Path
import re,zlib,zipfile,csv,io,hashlib,sys,json
from PIL import Image,ImageDraw
r=Path(__file__).resolve().parent;p=r/'skin_assets.c'
cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',p.read_text(),re.S)[1])))
im=Image.frombytes('RGBA',(512,512),zlib.decompress(cp),'raw','BGRA')
names=['tf_pickstone.bmp','tf_throwstone.bmp','tf_sprinklesand.bmp','ac_chargearrow.bmp','ac_makingarrow.bmp','돌.bmp','화살.bmp','나무뿌리.bmp'];rects=[(260+i*26,298,24,24)for i in range(8)];report=[]
with zipfile.ZipFile(sys.argv[1])as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 for name,rect in zip(names,rects):
  row=next(v for v in rows if v['virtual_path'].lower().endswith('\\'+name));b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];icon=Image.open(io.BytesIO(b)).convert('RGBA');icon.putdata([(rr,gg,bb,0 if rr>245 and gg<12 and bb>245 else aa)for rr,gg,bb,aa in icon.getdata()]);icon=icon.resize((24,24),Image.Resampling.LANCZOS);im.paste(icon,rect[:2]);report.append(dict(icon=name,sha256=row['sha256'],rect=rect))
p=r/'skin_colors.h';base=[int(x,16)for x in re.findall(r'0x([0-9a-fA-F]+)u',p.read_text())][:20];assert len(base)==20
shades=[int(i*96/15+.5)<<24 for i in range(1,16)];colors=base+[0x70000000,0x60000000]+shades
p.write_text('/* Protected shared palette row. */\nstatic const unsigned skinColors[]={'+','.join('0x%08xu'%c for c in colors)+'};\nstatic const unsigned skinDimColors[15]={'+','.join('0x%08xu'%c for c in shades)+'};\n')
for i,c in enumerate(colors):ImageDraw.Draw(im).rectangle((i*8,256,i*8+5,261),fill=(c>>16&255,c>>8&255,c&255,c>>24))
cp=zlib.compress(im.tobytes('raw','BGRA'),9);(r/'skin_assets.c').write_text('/* Shared512x512 HUD atlas, original client artwork. */\nconst unsigned int skin_image_raw=1048576,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%len(cp)+','.join(map(str,cp))+'\n};\n')
p=r/'skin_data.h';old=re.findall(r'\{\d+,\d+,\d+,\d+\}',p.read_text())[:77];assert len(old)==77;p.write_text('/* Stable shared icon indices. */\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join(old+['{%d,%d,%d,%d}'%v for v in rects])+'\n};\n');(r.parent/'ICONS34-REPORT.json').write_text(json.dumps(report,indent=2))
