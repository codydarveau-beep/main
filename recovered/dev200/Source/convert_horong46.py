# MIT. Retain source Willow/Elder Willow fade alpha at the same16-bit GPU footprint.
from pathlib import Path
import re,struct,zlib,sys
import numpy as np
from PIL import Image
import ro_sprite_bake as ro
r=Path(__file__).resolve().parent;lib=r.parent.parent/'asset-library';assets={}
for folder in ['Payon43-return','Payon43-supplement']:
 for p in (lib/folder/'data').rglob('*'):
  if p.is_file():assets[str(p.relative_to(lib/folder)).replace('/','\\').lower()]=p.read_bytes()
ro.assets=assets;ro.root=r.parent;ro.out=r.parent/'CreatureAssets46';ro.out.mkdir(exist_ok=True)
s=(r/'ro_sprite_bake.py').read_text();s=s[s.index('def bake('):];s=s.replace('argb=((a[:,:,3]>=128).astype(np.uint32)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3)','argb=((a[:,:,3]>>4)<<12)|((a[:,:,0]>>4)<<8)|((a[:,:,1]>>4)<<4)|(a[:,:,2]>>4)');s=s.replace('len(pixels)|0x80000000','len(pixels)|0xc0000000');s=s.replace("if fi not in [", "if group!=2 and fi not in [");exec(s,ro.__dict__)
rows=[list(map(lambda x:int(x,16)if re.search('[a-f]',x)else int(x),m))for m in []] # parse CRC explicitly below
matches=re.findall(r'\{(\d+),(\d+),(\d+),0x([0-9a-f]+)u\}',(r/'enemy_disc_data44.h').read_text());old=(r.parent/'Enemies/enemies.bin').read_bytes();blobs=[]
for i,(off,sz,raw,crc)in enumerate(matches):
 cp=old[int(off):int(off)+int(sz)]
 if i==38:
  name='horong';data=ro.bake(name,'data\\sprite\\몬스터\\'+name,None,[0,1,2,3,4],86);cp=zlib.compress(data,9);raw=len(data)
 blobs.append((cp,int(raw)))
meta=[];data=bytearray();c='/* Source monster artwork; selected source fades retain4-bit alpha for Test45. */\n'
for i,(b,raw)in enumerate(blobs):
 meta.append((len(data),len(b),raw,zlib.crc32(b)));data+=b;c+=f'const unsigned int enemy{i}_raw={raw},enemy{i}_size={len(b)};\nconst unsigned char enemy{i}[]={{'+','.join(map(str,b))+'};\n'
(r.parent/'Enemies/enemies.bin').write_bytes(data);(r/'encounter_assets.c').write_text(c)
(r/'enemy_disc_data44.h').write_text('/* Per-species disc offsets. */\n#define ENEMY_FILE_BYTES %d\n#define ENEMY_DISC_COUNT 50\ntypedef struct {unsigned offset,packed,raw,crc;} EnemyBlob44;\nstatic const EnemyBlob44 enemyBlobs44[50]={\n'%len(data)+''.join('{%d,%d,%d,0x%08xu},\n'%x for x in meta)+'};\n')
print('monsterpack',len(data))
