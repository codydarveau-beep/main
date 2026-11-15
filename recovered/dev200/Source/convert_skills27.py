"""MIT. Verified original icons and source-derived concealment/loot traits.
Usage: python convert_skills27.py HUD-Assets.zip /path/to/hercules/db/pre-re
"""
from pathlib import Path
import re,zlib,zipfile,csv,io,hashlib,sys,json
from PIL import Image
r=Path(__file__).resolve().parent;p=r/'skin_assets.c';t=p.read_text();cp=bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',t,re.S)[1])));im=Image.frombytes('RGBA',(512,256),zlib.decompress(cp),'raw','BGRA')
rects=[(130,148,24,24),(156,148,24,24),(182,148,24,24),(208,148,24,24),(0,174,24,24)];report=[]
with zipfile.ZipFile(sys.argv[1])as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 for name,(x,y,w,h)in zip(['mg_sight.bmp','tf_steal.bmp','tf_hiding.bmp','ac_concentration.bmp','al_ruwach.bmp'],rects):
  row=next(row for row in rows if row['virtual_path'].lower().endswith('\\'+name));b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];icon=Image.open(io.BytesIO(b)).convert('RGBA');icon.putdata([(rr,gg,bb,0 if rr>245 and gg<12 and bb>245 else aa)for rr,gg,bb,aa in icon.getdata()]);im.paste(icon.resize((w,h),Image.Resampling.LANCZOS),(x,y));report.append(dict(icon=name,sha256=row['sha256'],rect=[x,y,w,h]))
raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9);p.write_text('/* Original client artwork; stable shared atlas size. */\nconst unsigned int skin_image_raw=%d,skin_image_size=%d;\nconst unsigned char skin_image[]={\n'%(len(raw),len(cp))+','.join(map(str,cp))+'\n};\n')
p=r/'skin_data.h';old=re.findall(r'\{\d+,\d+,\d+,\d+\}',p.read_text())[:53];assert len(old)==53;p.write_text('/* Stable icon indices; utility additions 53..57. */\nstatic const unsigned short skinRects[][4]={\n'+',\n'.join(old+['{%d,%d,%d,%d}'%v for v in rects])+'\n};\n')
db=Path(sys.argv[2]);text=(db/'mob_db.conf').read_text();entries={int(m[1]):m[2]for m in re.finditer(r'^\{\s*\n\s*Id:\s*(\d+)([\s\S]*?)(?=^\},)',text,re.M)}
a=(db/'attr_fix.conf').read_text();rates={}
for m in re.finditer(r'^(Ele_\w+):\s*\{([\s\S]*?)(?=^\})',a,re.M):
 for lv in re.finditer(r'Lv(\d):\s*\{([^}]*)\}',m[2]):rates[m[1],int(lv[1])]={k:int(v)for k,v in re.findall(r'(Ele_\w+):\s*(-?\d+)',lv[2])}
ids=list(map(int,re.findall(r'\{"[^"]+",[^\n]*?,(\d{4}),\d+,\d+,\d+,\d+,\d+,\d+\}',(r/'encounter_data.h').read_text())));assert len(ids)==18;traits=[]
for id in ids:
 t=entries[id];m=re.search(r'Element:\s*\("(Ele_\w+)",\s*(\d)\)',t);el,lv=(m[1],int(m[2]))if m else('Ele_Neutral',1);race=re.search(r'Race:\s*"(\w+)"',t);race=race[1]if race else'RC_Formless';dex=re.search(r'Dex:\s*(\d+)',t);dex=int(dex[1])if dex else 1
 drop=re.search(r'Drops:\s*\{([^}]*)\}',t);loot=[]
 if drop:
  for name,chance in re.findall(r'(\w+):\s*(\d+)',drop[1]):
   if name in ['Apple','Jellopy','Clover']:loot.append((['Apple','Jellopy','Clover'].index(name),int(chance)))
 assert len(loot)<=6
 traits.append(dict(id=id,dex=dex,detect=int(race in ['RC_Insect','RC_Demon']or bool(re.search(r'Detector:\s*true',t))),blocked=int(bool(re.search(r'Boss:\s*true',t))),loot=loot,holy=rates[el,max(1,lv)]['Ele_Holy']))
with(r/'mob_utility_traits.h').open('w')as f:
 f.write('/* Hercules pre-re source data, GPL3+; only catalog-supported loot is enabled. */\ntypedef struct {int dex,detect,blocked,count;int item[6],rate[6];} MobUtility;\nstatic const MobUtility mobUtility[MOB_SPEC_COUNT]={\n')
 for t in traits:f.write('{%d,%d,%d,%d,{%s},{%s}},\n'%(t['dex'],t['detect'],t['blocked'],len(t['loot']),','.join(str(x[0])for x in t['loot'])or'0',','.join(str(x[1])for x in t['loot'])or'0'))
 f.write('};\nstatic const short mobHolyRate[MOB_SPEC_COUNT]={'+','.join(str(t['holy'])for t in traits)+'};\n')
(r.parent/'SKILLS27-SOURCE-REPORT.json').write_text(json.dumps(dict(icons=report,traits=traits,sourceSHA256={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in [db/'skill_db.conf',db/'skill_tree.conf',db/'mob_db.conf',db/'attr_fix.conf']}),indent=2));print('PASS five verified icons, stable atlas, 18 detector/DEX/loot/holy source records')
