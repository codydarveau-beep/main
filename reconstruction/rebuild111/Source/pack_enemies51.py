"""Append independently compressed creature poses to the accepted enemy pack."""
from pathlib import Path
import json,re,struct,zlib,hashlib
import numpy as np
from PIL import Image
R=Path(__file__).resolve().parent;ROOT=R.parent;BASE=ROOT.parent/'test50f';cat=json.loads((ROOT/'CATALOG51.json').read_text());reports={r['prefix']:r for r in json.loads((ROOT/'ENEMY-ART51.json').read_text())['bodies']} if isinstance(json.loads((ROOT/'ENEMY-ART51.json').read_text()),dict) else {r['prefix']:r for r in json.loads((ROOT/'ENEMY-ART51.json').read_text())}
rows=[];seen={};target=ROOT/'Enemies/enemies.bin';tmp=target.with_suffix('.pending')
with tmp.open('wb')as f:
 prefix=(BASE/'Enemies/enemies.bin').read_bytes();f.write(prefix)
 for id in cat['ids'][50:]:
  stem=cat['requests'][str(id)]
  if stem.startswith('guardian'):rows.append([0]*7);continue
  if stem not in seen:
   r=reports[stem];d=ROOT/'CreatureAssets51'/r['key'];m=(d/'meta.z').read_bytes();frames=(d/'frames.bin').read_bytes();row=[f.tell(),len(m),r['metadata_raw'],zlib.crc32(m),f.tell()+len(m),len(frames),0];f.write(m);f.write(frames);seen[stem]=row
  rows.append(seen[stem])
 guardians=[]
 for bank in (7,8):
  d=ROOT/'GuardianAssets51';m=json.loads((d/f'{bank}-model.json').read_text());atlas=Image.new('RGBA',(768,512));placements={}
  for i,t in enumerate(m['textures']):
   x=(i%3)*256;y=(i//3)*256;im=Image.frombytes('RGBA',(t['width'],t['height']),(d/(str(bank)+'-'+t['name']+'.rgba')).read_bytes());atlas.paste(im,(x,y));placements[t['index']]=(x,y,t['width'],t['height'])
  a=np.array(atlas,dtype=np.uint16);pixels=((a[:,:,3]>>4)<<12)|((a[:,:,0]>>4)<<8)|((a[:,:,1]>>4)<<4)|(a[:,:,2]>>4);raw=pixels.astype('<u2').tobytes();cp=zlib.compress(raw,6);texture=[f.tell(),len(cp),len(raw),zlib.crc32(cp)];f.write(cp)
  poses=np.frombuffer((d/f'{bank}-poses.bin').read_bytes(),dtype='<f4').reshape(m['frameCount'],m['vertices'],6).copy();groups=[];frames=[]
  for g in m['groups']:groups.append([g['records'][0]['frame'],g['frames'],round(g['duration']*1000)])
  for pose in poses:
   for tex,(x,y,w,h)in placements.items():
    mask=pose[:,5]==tex;pose[mask,3]=x+pose[mask,3]*w;pose[mask,4]=y+pose[mask,4]*h
   raw=pose[:,:5].copy().tobytes();cp=zlib.compress(raw,6);frames.append([f.tell(),len(cp),len(raw),zlib.crc32(cp)]);f.write(cp)
  guardians.append(dict(bank=bank,texture=texture,vertices=m['vertices'],groups=groups,frames=frames))
 sounds=[];soundseen={}
 for audio in json.loads((ROOT/'DEATH-AUDIO51.json').read_text()):
  if not audio:sounds.append([0]*4);continue
  key=audio['key']
  if key not in soundseen:
   cp=(ROOT/'CreatureAudio51'/(key+'.z')).read_bytes();soundseen[key]=[f.tell(),len(cp),audio['raw'],audio['crc']];f.write(cp)
  sounds.append(soundseen[key])
 total=f.tell()
tmp.replace(target)
h='/* Metadata and independently compressed source crops, bounded runtime cache. */\n#define ENEMY_ANCHOR_BIAS51 80\nstruct EnemyStream51 {unsigned offset,packed,raw,crc,framesOffset,framesBytes,guardian;};\nstatic const EnemyStream51 enemyStreams51[MOB_SPEC_COUNT-50]={\n'+''.join('{'+','.join(map(str,row[:-1]+[7 if id==1829 else 8 if id==1830 else 0]))+'},\n'for id,row in zip(cat['ids'][50:],rows))+'};\n'
(R/'enemy_stream_data51.h').write_text(h)
(R/'guardian_data51.h').write_text('/* Original GR2 material atlases and full source skinned poses. */\n'+''.join('static const unsigned guardianTexture%d[4]={%s};\nstatic const unsigned guardianGroups%d[5][3]={%s};\nstatic const unsigned guardianPoses%d[%d][4]={%s};\n#define GUARDIAN_VERTICES%d %d\n'%(g['bank'],','.join(map(str,g['texture'])),g['bank'],','.join('{'+','.join(map(str,v))+'}'for v in g['groups']),g['bank'],len(g['frames']),','.join('{'+','.join(map(str,v))+'}'for v in g['frames']),g['bank'],g['vertices'])for g in guardians));p=R/'enemy_disc_data44.h';t=(BASE/'Source/enemy_disc_data44.h').read_text();t=re.sub(r'#define ENEMY_FILE_BYTES \d+u?',f'#define ENEMY_FILE_BYTES {total}u',t);p.write_text(t)
(ROOT/'ENEMIES-PACK51.json').write_text(json.dumps(dict(species=len(cat['ids']),bytes=total,preserved_bytes=len(prefix),preserved_sha256=hashlib.sha256(prefix).hexdigest(),unique_bodies=len(seen)),indent=2));print('PASS',len(rows),'new descriptors',total,'bytes')

(R/'death_sound_data51.h').write_text('/* Original optional death cues; lazy bounded PCM cache. */\nstatic const unsigned deathSounds51[MOB_SPEC_COUNT-50][4]={'+','.join('{'+','.join(map(str,row))+'}'for row in sounds)+'};\n')
