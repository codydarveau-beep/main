"""GPL-3.0-or-later. Source classic effect geometry textures and tints.
Retains original five packed48 textures exactly. Additional tinting is offline.
"""
from pathlib import Path
from PIL import Image
import numpy as np,zlib,re,json,hashlib
from asset_index49 import paths
r=Path(__file__).resolve().parent;s=(r/'field_textures48.h').read_text();out=s[:s.index('static const struct')];out=out[:out.index('static const unsigned char fieldTexPacked48_5')] if 'static const unsigned char fieldTexPacked48_5' in out else out
sides=[64,64,64,64,128];report=[]
for name,tint in [('ring_white.tga',(.7,1,.7)),('guardk.tga',(.91,1,.9)),('stone.bmp',(1,1,1)),('alpha_down.tga',(.5,.1,.5)),('ring_white.tga',(1,1,1)),('ring_blue.tga',(.3,.3,1))]:
 i=len(sides)
 p=paths['data\\texture\\effect\\'+name];im=Image.open(p).convert('RGBA').resize((128,128)if name=='stone.bmp'else(64,64),Image.Resampling.LANCZOS);a=np.array(im);sha=hashlib.sha256(p.read_bytes()).hexdigest()
 a[(a[:,:,0]>245)&(a[:,:,1]<12)&(a[:,:,2]>245)]=0
 for c,k in enumerate(tint):a[:,:,c]=(a[:,:,c]*k).astype('uint8')
 side=a.shape[0];raw=Image.fromarray(a).tobytes('raw','BGRA');cp=zlib.compress(raw,9);out+='static const unsigned char fieldTexPacked48_%d[]={%s};\n'%(i,','.join(map(str,cp)));sides.append(side);report.append(dict(index=i,name=name,sourceSha256=sha,side=side,tint=tint))
out+='#define FIELD_TEXTURE_COUNT50 %d\n'%len(sides)
out+='static const struct {const unsigned char*p;unsigned packed,side;}fieldTexDefs48[]={'+','.join('{fieldTexPacked48_%d,sizeof(fieldTexPacked48_%d),%d}'%(i,i,side)for i,side in enumerate(sides))+'};\n';(r/'field_textures48.h').write_text(out);(r/'classic_textures49.json').write_text(json.dumps(report,indent=2)+'\n');print('PASS original five textures retained; Heal,Guard,stone and original Safety texture appended')
