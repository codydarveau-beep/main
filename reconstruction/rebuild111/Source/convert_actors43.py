# MIT. Append Knight / HighWizard sparse body+head variants, one resident at runtime.
from pathlib import Path
import csv,hashlib,struct,zlib,re,json
import ro_sprite_bake as bake
r=Path(__file__).resolve().parent;root=r.parent;lib=root.parent/'asset-library';assets={}
for name in ['Classes43-return']:
 for p in (lib/name/'data').rglob('*'):
  if p.is_file():assets[str(p.relative_to(lib/name)).replace('/','\\').lower()]=p.read_bytes()
folder=lib/'Next-Assets-Test37'
for row in csv.DictReader((folder/'Assets.csv').open(encoding='utf-8-sig')):
 b=(folder/row['payload']).read_bytes();assert hashlib.sha256(b).hexdigest()==row['sha256'];assets[row['virtual_path'].lower()]=b
bake.assets=assets;bake.root=root;bake.out=root/'ClassAssets';bake.out.mkdir(exist_ok=True)
data=bytearray((root.parent/'test42/Actors/actors.bin').read_bytes());rows=[]
for job,name,stem in [(7,'Knight','기사_남'),(8,'HighWizard','하이위저드_남')]:
 raw=bake.bake(name,'data\\sprite\\인간족\\몸통\\남\\'+stem,'data\\sprite\\인간족\\머리통\\남\\1_남',[0,1,5,6,8,2,4],90);cp=zlib.compress(raw,9);rows.append([job,0,len(data),len(cp),len(raw),zlib.crc32(cp)]);data+=cp
(root/'Actors/actors.bin').write_bytes(data);s=(root.parent/'test42/Source/actor_data.h').read_text().replace('ACTOR_FILE_BYTES 1856646','ACTOR_FILE_BYTES '+str(len(data))).replace('ACTOR_VARIANTS 14','ACTOR_VARIANTS 16');pos=s.index('\n};');s=s[:pos]+',\n'+',\n'.join('{'+','.join(map(str,row))+'}'for row in rows)+s[pos:];(r/'actor_data.h').write_text(s);print('Actors',len(data))
