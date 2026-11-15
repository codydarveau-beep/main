"""Pack four supplied original client icons into unused shared atlas cells.
python convert_ui31.py RO-Xbox-HUD-Assets.zip
"""
from pathlib import Path
import re,zlib,zipfile,csv,io,hashlib,sys,json
from PIL import Image
r=Path(__file__).resolve().parent;p=r/'skin_assets.c'
cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',p.read_text(),re.S)[1])))
raw=zlib.decompress(cp);assert len(raw)==512*512*4
im=Image.frombytes('RGBA',(512,512),raw,'raw','BGRA')
rects=[(442,272,24,24),(468,272,24,24),(0,298,24,24),(26,298,24,24)];report=[]
with zipfile.ZipFile(sys.argv[1])as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 for name,rect in zip(['mg_safetywall.bmp','mg_stonecurse.bmp','gemstone_blue.bmp','gemstone_red.bmp'],rects):
  row=next(v for v in rows if v['virtual_path'].lower().endswith('\\'+name));b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];icon=Image.open(io.BytesIO(b)).convert('RGBA');icon.putdata([(rr,gg,bb,0 if rr>245 and gg<12 and bb>245 else aa)for rr,gg,bb,aa in icon.getdata()]);icon=icon.resize((24,24),Image.Resampling.LANCZOS);im.paste(icon,rect[:2]);report.append(dict(icon=name,sha256=row['sha256'],rect=rect))
cp=zlib.compress(im.tobytes('raw','BGRA'),9);p.write_text('/* Original client artwork; shared512px atlas, same allocation. */\nconst unsigned int skin_image_raw=1048576,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%len(cp)+','.join(map(str,cp))+'\n};\n')
p=r/'skin_data.h';old=re.findall(r'\{\d+,\d+,\d+,\d+\}',p.read_text())[:65];assert len(old)==65;p.write_text('/* Stable icon indices. Safety Wall65, Stone Curse66, gems67/68. */\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join(old+['{%d,%d,%d,%d}'%v for v in rects])+'\n};\n')
(r.parent/'ICONS31-REPORT.json').write_text(json.dumps(report,indent=2));print('PASS four original icons; unchanged1MiB atlas')
