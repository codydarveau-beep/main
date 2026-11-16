"""Faithful original Willow ACT death layers, shared atlas instead of clipped bakes."""
from pathlib import Path
import sys,struct,zlib,json,hashlib
import numpy as np
from PIL import Image
R=Path(__file__).resolve().parent.parent;S=R/'Source';sys.path.insert(0,str(S));import ro_sprite_bake as ro
assets=Path('/workspace/myro/asset-library/Payon43-return/data/sprite/몬스터');out=['/* Original source SPR/ACT death layers; reconstructed restoration259. */'];reports=[]
for species,name in enumerate(['wilow','elder_wilow']):
 acts,delays=ro.act((assets/(name+'.act')).read_bytes());images=ro.spr((assets/(name+'.spr')).read_bytes());atlas=Image.new('RGBA',(512,1024));cells={};x=y=1;rowh=0;poses=[];layers=[]
 for direction in range(8):
  action=[]
  for parts,_ in acts[32+direction]:
   first=len(layers)
   for lx,ly,index,mirror,color,sx,sy,angle,typ in parts:
    if index<0 or not color[3]:continue
    assert typ==0 and sx>0 and sy>0
    assert color[:3]==(255,255,255)
    key=index,color[:3],color[3]>>4
    if key not in cells:
     im=images[index];w,h=im.size
     if x+w+1>512:x=1;y+=rowh+2;rowh=0
     assert y+h+1<=1024
     ar=np.asarray(im,dtype=np.uint16);ar=(ar*np.array(color,np.uint16)//255).astype(np.uint8);atlas.paste(Image.fromarray(ar,'RGBA'),(x,y));cells[key]=(x,y,w,h);x+=w+2;rowh=max(rowh,h)
    u,v,w,h=cells[key];layers.append((lx,ly,sx,sy,angle,mirror,u,v,w,h))
   action.append((first,len(layers)-first))
  poses.append(action)
 height=y+rowh+1;atlas=atlas.crop((0,0,512,height));a=np.asarray(atlas,dtype=np.uint32);q=((a[:,:,3]>>4)<<12)|((a[:,:,0]>>4)<<8)|((a[:,:,1]>>4)<<4)|(a[:,:,2]>>4);pixels=q.astype('<u2').tobytes();packed=zlib.compress(pixels,9)
 out.append('static const unsigned char willowAtlas259_%d[]={%s};'%(species,','.join(map(str,packed))))
 def cf(v):
  v=format(v,'.9g');return v+('f'if'.'in v or'e'in v else'.0f')
 out.append('static const WillowLayer259 willowLayers259_%d[]={%s};'%(species,','.join('{%d,%d,%s,%s,%d,%d,%d,%d,%d,%d}'%(lx,ly,cf(sx),cf(sy),angle,mirror,u,v,w,h)for lx,ly,sx,sy,angle,mirror,u,v,w,h in layers)))
 out.append('static const WillowPose259 willowPoses259_%d[8][22]={%s};'%(species,','.join('{'+','.join('{%d,%d}'%v for v in action)+(''if len(action)==22 else ',{0,0}')+'}'for action in poses)))
 reports.append(dict(species=species,name=name,atlasHeight=height,atlasGPUBytes=len(pixels),packedBytes=len(packed),sourceFrames=len(poses[0]),milliseconds=round(delays[32]),layers=len(layers),cells=len(cells),sourceSPR_SHA256=hashlib.sha256((assets/(name+'.spr')).read_bytes()).hexdigest(),sourceACT_SHA256=hashlib.sha256((assets/(name+'.act')).read_bytes()).hexdigest()))
out.append('static const WillowArt259 willowArt259[2]={'+','.join('{willowAtlas259_%d,%d,%d,%d,%d,willowLayers259_%d,willowPoses259_%d}'%(i,r['packedBytes'],r['atlasHeight'],r['sourceFrames'],r['milliseconds'],i,i)for i,r in enumerate(reports))+'};')
(S/'willow_art259.h').write_text('\n'.join(out)+'\n');(R/'Validation/Willow-Layers259.json').write_text(json.dumps(dict(reconstructed=True,source='original retained SPR/ACT',species=reports,totalGPUBytes=sum(r['atlasGPUBytes']for r in reports),allocationIndependentOfEnemyCount=True,neitherClippedNorResizedSourceArt=True,normalSpritePackUnchanged=True,XboxVisualAnd64MBStressPending=True),indent=2)+'\n');print(reports)
