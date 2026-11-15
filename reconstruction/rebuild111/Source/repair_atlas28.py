"""MIT. Relocate icons48..60 away from white-font glyphs; preserve icon IDs."""
from pathlib import Path
import re,zlib,json,zipfile,csv,io,hashlib
from PIL import Image
r=Path(__file__).resolve().parent;p=r/'skin_assets.c';s=p.read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',s,re.S)[1])));im=Image.frombytes('RGBA',(512,256),zlib.decompress(cp),'raw','BGRA');rects=[tuple(map(int,re.findall(r'\d+',v)))for v in re.findall(r'\{\d+,\d+,\d+,\d+\}',(r/'skin_data.h').read_text())];assert len(rects)==61
icons=[]
with zipfile.ZipFile('assets26/RO-Xbox-HUD-Assets-20261019-074541-1734d7.zip')as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 for name in ['mg_firewall.bmp','ac_shower.bmp','al_angelus.bmp','tf_miss.bmp','sm_sword.bmp','mg_sight.bmp','tf_steal.bmp','tf_hiding.bmp','ac_concentration.bmp','al_ruwach.bmp','al_decagi.bmp','al_demonbane.bmp','al_crucis.bmp']:
  row=next(v for v in rows if v['virtual_path'].lower().endswith('\\'+name));b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];icon=Image.open(io.BytesIO(b)).convert('RGBA');icon.putdata([(rr,gg,bb,0 if rr>245 and gg<12 and bb>245 else aa)for rr,gg,bb,aa in icon.getdata()]);icons.append(icon.resize((24,24),Image.Resampling.LANCZOS))
white=im.crop((0,0,256,96));white.putdata([(255,255,255,a)for rr,gg,bb,a in white.getdata()]);im.paste(white,(0,160))
for i,icon in enumerate(icons):
 x=min(488,386+(i%5)*26);y=144 if i<5 else 170 if i<10 else 194;im.paste(icon,(x,y));rects[48+i]=(x,y,24,24)
raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9);p.write_text('/* Original client art, stable atlas dimensions, non-overlapping glyph region. */\nconst unsigned int skin_image_raw=%d,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%(len(raw),len(cp))+','.join(map(str,cp))+'\n};\n');(r/'skin_data.h').write_text('/* Stable indices; all glyphs and minimap protected. */\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join('{%d,%d,%d,%d}'%v for v in rects)+'\n};\n')
p=r.parent/'SKILLS28-SOURCE-REPORT.json';d=json.loads(p.read_text());d['atlasRelocation']={str(i):v for i,v in enumerate(rects)if i>=48};p.write_text(json.dumps(d,indent=2))
