"""Preserve original raised walk surfaces and original minimap art for streamed maps."""
from pathlib import Path
import io,json,struct
import numpy as np
from PIL import Image

def derive(assets,name,out,minimap):
 gb=assets['data/'+name+'.gat'];gw,gh=struct.unpack_from('<II',gb,6)
 gat=np.frombuffer(gb,offset=14,dtype=[('z','<f4',(4,)),('kind','<i4')],count=gw*gh)
 heights=-1.6*gat['z'].reshape(gh,gw,4);walk=np.isin(gat['kind'].reshape(gh,gw),[0,3])
 b=(out/'geometry.bin').read_bytes();w,h,n=struct.unpack_from('<III',b);assert (gw,gh)==(2*w,2*h)
 v=np.frombuffer(b,dtype='<f4',offset=12+(w*h+1)*4,count=w*h*4).reshape(h,w,4)
 ys,xs=np.indices((gh,gw));c=v[ys//2,xs//2];ground=[]
 for dx,dy in [(0,0),(1,0),(0,1),(1,1)]:
  fx=(xs%2+dx)/2;fy=(ys%2+dy)/2
  ground.append(np.where(fx>fy,c[:,:,0]+(c[:,:,1]-c[:,:,0])*fx+(c[:,:,3]-c[:,:,1])*fy,c[:,:,0]+(c[:,:,3]-c[:,:,2])*fx+(c[:,:,2]-c[:,:,0])*fy))
 delta=heights-np.stack(ground,2);selected=np.flatnonzero(walk&(delta.max(2)>6))
 quant=np.rint(heights.reshape(-1,4)[selected]*16)
 if len(quant):assert np.isfinite(quant).all() and quant.min()>=-32768 and quant.max()<=32767
 surfaces=b''.join(struct.pack('<I4h',int(cell),*map(int,z)) for cell,z in zip(selected,quant))
 # Prop occupancy is appended separately by the solid-section conversion stage.
 (out/'surfaces.bin').write_bytes(struct.pack('<II',gw,gh)+walk.astype('uint8').tobytes()+struct.pack('<I',len(selected))+surfaces)
 if minimap and minimap in assets:
  mini=Image.open(io.BytesIO(assets[minimap])).convert('RGB');ar=np.array(mini);pink=(ar[:,:,0]>230)&(ar[:,:,1]<30)&(ar[:,:,2]>230);ar[pink]=[234,240,245];mini=Image.fromarray(ar);source='original'
 else:
  ar=np.full((gh,gw,3),[234,240,245],dtype=np.uint8);ar[walk]=[150,165,177];mini=Image.fromarray(ar);source='source-walk-grid'
 if gw*72>=gh*96:ww=96;hh=max(1,gh*96//gw)
 else:hh=72;ww=max(1,gw*72//gh)
 canvas=Image.new('RGBA',(96,72),(234,240,245,255));canvas.paste(mini.resize((ww,hh),Image.Resampling.LANCZOS),((96-ww)//2,(72-hh)//2));(out/'minimap.bin').write_bytes(canvas.tobytes('raw','BGRA'))
 report={'map':name,'surface_cells':len(selected),'walkable_cells':int(walk.sum()),'minimap_source':source,'collision_bytes_before_props':12+gw*gh+12*len(selected)}
 (out/'SURFACES51.json').write_text(json.dumps(report,indent=2));return report
