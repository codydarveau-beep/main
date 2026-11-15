# MIT. Append authentic second-job bodies; preserve the shipped actor prefix.
from pathlib import Path
import csv,hashlib,zlib,re
import ro_sprite_bake as b
r=Path(__file__).resolve().parent;lib=r.parent.parent/'asset-library';assets={}
for folder in ['Classes43-return','Test46-equipment-art','Test48-classes','Test48-followup','Test48-skill-art']:
 for p in (lib/folder/'data/sprite').rglob('*'):
  if p.is_file():assets[str(p.relative_to(lib/folder)).replace('/','\\').lower()]=p.read_bytes()
a=lib/'Next-Assets-Test37'
for row in csv.DictReader((a/'Assets.csv').open(encoding='utf-8-sig')):
 if row['virtual_path'].endswith(('.spr','.act')):assets[row['virtual_path'].lower()]=(a/row['payload']).read_bytes()
b.assets=assets;b.root=r.parent;b.out=r.parent/'ClassAssets';b.out.mkdir(exist_ok=True)
base=r.parent.parent/'test47a';payload=bytearray((base/'Actors/actors.bin').read_bytes());s=(base/'Source/actor_data.h').read_text();rows=[]
for job,name,stem in [(9,'Wizard','위저드'),(10,'Sage','세이지'),(11,'Crusader','크루세이더'),(12,'MountedCrusader','구페코크루세이더')]:
 raw=b.bake(name,'data\\sprite\\인간족\\몸통\\남\\'+stem+'_남','data\\sprite\\인간족\\머리통\\남\\1_남',[0,1,5,6,8,2,4],90);cp=zlib.compress(raw,9);rows.append((job,0,len(payload),len(cp),len(raw),zlib.crc32(cp)));payload+=cp
s=s.replace('#define ACTOR_FILE_BYTES 4463085','#define ACTOR_FILE_BYTES '+str(len(payload))).replace('#define ACTOR_VARIANTS 31','#define ACTOR_VARIANTS 35');s=s.replace('\n};','\n'+''.join('{%d,%d,%d,%d,%d,0x%08xu},\n'%v for v in rows)+'};');(r/'actor_data.h').write_text(s);(r.parent/'Actors/actors.bin').write_bytes(payload);assert payload[:4463085]==(base/'Actors/actors.bin').read_bytes();print('PASS old actor prefix preserved; 3 authentic bodies appended')
