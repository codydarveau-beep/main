"""MIT. Read-only icon and Hercules fire-trait extraction for Test26.
Usage: python convert_skills26.py HUD-Assets.zip /path/to/hercules/db/pre-re
"""
from pathlib import Path
import re,zlib,zipfile,csv,io,hashlib,sys,json
from PIL import Image
r=Path(__file__).resolve().parent;p=r/'skin_assets.c';t=p.read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',t,re.S)[1])));im=Image.frombytes('RGBA',(512,256),zlib.decompress(cp),'raw','BGRA')
rects=[(i*26,148,24,24)for i in range(5)];report=[]
with zipfile.ZipFile(sys.argv[1])as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 for name,(x,y,w,h)in zip(['mg_firewall.bmp','ac_shower.bmp','al_angelus.bmp','tf_miss.bmp','sm_sword.bmp'],rects):
  row=next(row for row in rows if row['virtual_path'].lower().endswith('\\'+name));b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];icon=Image.open(io.BytesIO(b)).convert('RGBA');icon.putdata([(rr,gg,bb,0 if rr>245 and gg<12 and bb>245 else aa)for rr,gg,bb,aa in icon.getdata()]);im.paste(icon.resize((w,h),Image.Resampling.LANCZOS),(x,y));report.append(dict(icon=name,sha256=row['sha256'],rect=[x,y,w,h]))
raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9);p.write_text('/* Original client artwork; no atlas size increase. */\nconst unsigned int skin_image_raw=%d,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%(len(raw),len(cp))+','.join(map(str,cp))+'\n};\n')
p=r/'skin_data.h';old=re.findall(r'\{\d+,\d+,\d+,\d+\}',p.read_text())[:48];assert len(old)==48;p.write_text('/* Stable icon indices, Test26 additions 48..52. */\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join(old+['{%d,%d,%d,%d}'%v for v in rects])+'\n};\n')
db=Path(sys.argv[2]);text=(db/'mob_db.conf').read_text();entries={int(m[1]):m[2]for m in re.finditer(r'^\{\s*\n\s*Id:\s*(\d+)([\s\S]*?)(?=^\},)',text,re.M)}
a=(db/'attr_fix.conf').read_text();rates={}
for m in re.finditer(r'^(Ele_\w+):\s*\{([\s\S]*?)(?=^\})',a,re.M):
 for lv in re.finditer(r'Lv(\d):\s*\{([^}]*)\}',m[2]):rates[m[1],int(lv[1])]={k:int(v)for k,v in re.findall(r'(Ele_\w+):\s*(-?\d+)',lv[2])}
ids=list(map(int,re.findall(r'\{"[^"]+",[^\n]*?,(\d{4}),\d+,\d+,\d+,\d+,\d+,\d+\}',(r/'encounter_data.h').read_text())));assert len(ids)==18
traits=[]
for id in ids:
 t=entries[id];m=re.search(r'Element:\s*\("(Ele_\w+)",\s*(\d)\)',t);el,lv=(m[1],int(m[2]))if m else('Ele_Neutral',1);race=re.search(r'Race:\s*"(\w+)"',t);race=race[1]if race else'RC_Formless';traits.append(dict(id=id,fire=rates[el,max(1,lv)]['Ele_Fire'],noPush=int(el in ['Ele_Fire','Ele_Undead']or race=='RC_Undead'),immune=int(bool(re.search(r'NoKnockback:\s*true',t)))))
with(r/'mob_flame_traits.h').open('w')as f:
 f.write('/* Source-derived Hercules pre-re fire/knockback data, GPL3+. */\n')
 for name,key in [('mobFlameRate','fire'),('mobFlameNoPush','noPush'),('mobKnockImmune','immune')]:f.write('static const short '+name+'[MOB_SPEC_COUNT]={'+','.join(str(t[key])for t in traits)+'};\n')
report=dict(icons=report,traits=traits,sourceSHA256={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in [db/'skill_db.conf',db/'skill_tree.conf',db/'attr_fix.conf',db/'mob_db.conf']})
(r.parent/'SKILLS26-SOURCE-REPORT.json').write_text(json.dumps(report,indent=2));print('PASS five verified client icons; unchanged 512x256 atlas; 18 source-derived fire/knockback traits')
