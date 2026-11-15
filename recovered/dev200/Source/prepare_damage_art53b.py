"""MIT. Original combat SPR artwork, fixed 256KiB texture, no per-event allocation."""
from pathlib import Path
import json,zlib,hashlib
import numpy as np
from PIL import Image
from bake_enemies51 import spr51
s=Path('/workspace/myro/test53b/Source')
source=s.parent.parent/'asset-library/Test52d-damage-art/data/sprite/이팩트'
numbers,_=spr51((source/'숫자.spr').read_bytes());msg,_=spr51((source/'msg.spr').read_bytes())
colors=[(1,1,1),(.9,.9,.15),(1,0,0),(0,1,0),(.13,.19,.75)]
inputs=[(n,c)for c in colors for n in numbers[:10]]
inputs.extend([(msg[0],(1,1,1)),(msg[0],(1,0,0)),(msg[1],(1,1,1)),(msg[1],(1,0,0)),(msg[3],(.66,.66,.66)),(msg[5],(1,1,1)),(msg[4],(1,1,1))])
inputs.append((Image.open(s.parent/'Preparation/gold-coin53.png').convert('RGBA'),(1,1,1)))
frames=[]
for image,color in inputs:
 for alpha in [1,.8,.6,.4,.2,.067]:
  a=np.array(image).astype('f4');a[:,:,:3]*=np.array(color);a[:,:,3]*=alpha;frames.append(Image.fromarray(np.rint(a).astype('u1'),'RGBA'))
atlas=Image.new('RGBA',(512,256));occupied=np.zeros((256,512),dtype='u1');rects=[None]*len(frames)
for index in sorted(range(len(frames)),key=lambda i:frames[i].height,reverse=True):
 im=frames[index];w,h=im.width+2,im.height+2;integral=np.pad(occupied.astype('i4'),((1,0),(1,0))).cumsum(0).cumsum(1);free=integral[h:,w:]-integral[:-h,w:]-integral[h:,:-w]+integral[:-h,:-w];ys,xs=np.where(free==0)
 assert len(xs),(index,im.size)
 x,y=int(xs[0])+1,int(ys[0])+1;occupied[y-1:y+h-1,x-1:x+w-1]=1;atlas.paste(im,(x,y));rects[index]=(x,y,im.width,im.height)
a=np.array(atlas,dtype='u2');raw=(((a[:,:,3]>>4)<<12)|((a[:,:,0]>>4)<<8)|((a[:,:,1]>>4)<<4)|(a[:,:,2]>>4)).astype('<u2').tobytes();cp=zlib.compress(raw,9)
(s/'damage_art53.h').write_text('/* Original client SPR artwork; six baked alpha levels, no runtime rasterisation. */\n#define DAMAGE_FADE_LEVELS53 6\nstatic const unsigned short damageGlyphs53[][4]={'+','.join('{%d,%d,%d,%d}'%r for r in rects)+'};\nstatic const unsigned damageImageRaw53=%d,damageImageSize53=%d;\nstatic const unsigned char damageImage53[]={\n'%(len(raw),len(cp))+','.join(map(str,cp))+'\n};\n')
atlas.save(s.parent/'Validation/damage-source-atlas52d.png')
(s.parent/'Validation/damage-art52d.json').write_text(json.dumps(dict(files={p.name:hashlib.sha256(p.read_bytes()).hexdigest()for p in source.iterdir()},glyphs=len(rects),textureBytes=len(raw),textureFormat='ARGB4444',digitDimensions=[list(i.size)for i in numbers[:10]],originalNumberActScale=[1,1]),indent=2)+'\n')
print('PASS original damage art:',len(rects),'glyphs; fixed',len(raw),'GPU bytes;',len(cp),'compressed bytes')
