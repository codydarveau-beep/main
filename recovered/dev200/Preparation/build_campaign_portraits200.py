"""Encode authored expression-sheet cells as disc-only BGRA dialogue textures.
This is deterministic texture slicing/encoding; creative edits remain in source PNGs.
"""
from pathlib import Path
import json,zlib,hashlib,numpy as np
from PIL import Image
R=Path('/workspace/myro/dev200');D=R/'Preparation/Campaign-Portraits200';payload=bytearray();rows=[];names=['Roan','Yuufa','Judia','Maya'];emotions=['neutral','happy','angry','sad','worried','surprised'];rawBytes=256*256*4
for name in names:
 path=D/(name.lower()+'-expressions.png');im=Image.open(path).convert('RGBA');assert im.size==(1536,1024)
 for expression in range(6):
  x=expression%3*512;y=expression//3*512;tile=im.crop((x,y,x+512,y+512)).resize((256,256),Image.Resampling.LANCZOS);a=np.array(tile);a[a[:,:,3]<8]=0;assert np.count_nonzero(a[:,:,3]>=128)>10000 and np.count_nonzero(a[:,:,3]==0)>10000,(name,expression,'cutout alpha')
  raw=a[:,:,[2,1,0,3]].tobytes();assert len(raw)==rawBytes;cp=zlib.compress(raw,9);rows.append(dict(name=name,expression=expression,emotion=emotions[expression],offset=len(payload),packed=len(cp),crc=zlib.crc32(cp),rawCRC=zlib.crc32(raw),sourceSHA256=hashlib.sha256(path.read_bytes()).hexdigest()));payload.extend(cp)
(R/'Campaign/portraits.bin').write_bytes(payload)
h='/* Authored expression variants from official character references; one texture at a time. */\n#ifndef MYRO_CAMPAIGN_PORTRAIT_DATA200_H\n#define MYRO_CAMPAIGN_PORTRAIT_DATA200_H\n#define CAMPAIGN_PORTRAIT_RAW200 262144u\n#define CAMPAIGN_PORTRAIT_FILE_BYTES200 '+str(len(payload))+'u\nstatic const struct{const char*name;unsigned expression,offset,packed,crc,rawCRC;}campaignPortraits200[]={\n'+''.join('{"'+v['name']+'",'+','.join(str(v[k])+'u'for k in ['expression','offset','packed','crc','rawCRC'])+'},\n'for v in rows)+'};\n#endif\n'
(R/'Source/campaign_portrait_data200.h').write_text(h);(D/'Encoded-Portraits200.json').write_text(json.dumps(dict(bytes=len(payload),rawBytesPerDisplayedTexture=rawBytes,expressions=emotions,rows=rows,generatedArt=True,originalOfficialExpressionSets=False),indent=2)+'\n');print('Encoded',len(rows),'disc-only portraits;',len(payload),'bytes, one256KiB displayed texture.')
