"""MIT. Original static RSM 1.x / RSW converter; game assets retain ownership.
Usage: python convert_scenery.py map08-collection.zip field05-source.zip
Outputs one shared cutout atlas, model VBO, instances and embedded C arrays.
No game/server files are modified. Requires Python, NumPy, Pillow.
"""
from pathlib import Path
import zipfile,csv,io,struct,collections,hashlib,math,json,zlib,sys
import numpy as np
from PIL import Image
class AtlasPackingError(ValueError):pass
class Reader:
 def __init__(self,b):self.b=b;self.p=0
 def take(self,n):
  assert 0<=n<=len(self.b)-self.p,'truncated asset'
  out=self.b[self.p:self.p+n];self.p+=n;return out
 def get(self,fmt):return struct.unpack('<'+fmt,self.take(struct.calcsize('<'+fmt)))
 def text(self,n):return self.take(n).split(b'\0')[0].decode('cp949').lower()
 def skip(self,n):self.take(n)
def world(b):
 r=Reader(b);assert r.take(4)==b'GRSW';major,minor=r.get('BB');v=major*10+minor;assert 12<=v<=22
 if v>=22:r.skip(1)
 r.skip(120+(40 if v>=14 else 0));r.skip((4 if v>=13 else 0)+(16 if v>=18 else 0)+(4 if v>=19 else 0));r.skip((32 if v>=15 else 0)+(4 if v>=17 else 0)+(16 if v>=16 else 0));count=r.get('I')[0];assert count<20000;models=[]
 for i in range(count):
  kind=r.get('I')[0]
  if kind==1:
   r.skip(52 if v>=13 else 0);name=r.text(80);r.skip(80);vals=r.get('9f');assert np.isfinite(vals).all();models.append((name,vals))
  elif kind==2:r.skip(108)
  elif kind==3:r.skip(192 if v>=20 else 188)
  elif kind==4:r.skip(116)
  else:raise ValueError('unknown RSW object '+str(kind))
 return models
def translation(v):m=np.eye(4);m[:3,3]=v;return m
def scaling(v):m=np.eye(4);m[:3,:3]=np.diag(v);return m
def rotation(a,axis):
 m=np.eye(4);axis=np.array(axis,float);n=np.linalg.norm(axis)
 if abs(a)<1e-8 or n<1e-8:return m
 x,y,z=axis/n;c=math.cos(a);s=math.sin(a);q=1-c
 m[:3,:3]=[[c+x*x*q,x*y*q-z*s,x*z*q+y*s],[y*x*q+z*s,c+y*y*q,y*z*q-x*s],[z*x*q-y*s,z*y*q+x*s,c+z*z*q]];return m
def quaternion(q):
 x,y,z,w=np.array(q)/np.linalg.norm(q);m=np.eye(4)
 m[:3,:3]=[[1-2*(y*y+z*z),2*(x*y-z*w),2*(x*z+y*w)],[2*(x*y+z*w),1-2*(x*x+z*z),2*(y*z-x*w)],[2*(x*z-y*w),2*(y*z+x*w),1-2*(x*x+y*y)]];return m
def model(b):
 r=Reader(b);assert r.take(4)==b'GRSM';major,minor=r.get('BB');v=major*10+minor;assert 10<=v<=16
 anim,shade=r.get('II');alpha=r.get('B')[0] if v>=14 else 255;assert alpha==255,'partial-opacity model needs separate blending'
 r.skip(16);count=r.get('I')[0];assert count<256;textures=[r.text(40) for _ in range(count)];main=r.text(40);nn=r.get('I')[0];assert 0<nn<256;nodes=[]
 for i in range(nn):
  name,parent=r.text(40),r.text(40);nt=r.get('I')[0];assert nt<=count;tex=list(r.get(str(nt)+'I'));basis=np.array(r.get('9f')).reshape(3,3,order='F');offset=r.get('3f');pos=r.get('3f');angle=r.get('f')[0];axis=r.get('3f');scale=r.get('3f')
  nv=r.get('I')[0];assert nv<65536;verts=np.array(r.get(str(nv*3)+'f')).reshape(nv,3);nu=r.get('I')[0];assert nu<65536;uv=[]
  for j in range(nu):
   if v>=12:r.skip(4)
   uv.append(r.get('2f'))
  nf=r.get('I')[0];assert nf<100000;faces=[]
  for j in range(nf):
   vi=r.get('3H');ti=r.get('3H');tid,pad=r.get('HH');two=r.get('I')[0]
   if v>=12:r.skip(4)
   assert max(vi)<nv and max(ti)<nu and tid<nt
   faces.append((vi,ti,tex[tid]))
  if v>=15:r.skip(r.get('I')[0]*16)
  nr=r.get('I')[0];assert nr<10000;rotkeys=[r.get('I4f') for _ in range(nr)]
  nodes.append(dict(name=name,parent=parent,basis=basis,offset=offset,pos=pos,rot=quaternion(rotkeys[0][1:]) if nr else rotation(angle,axis),scale=scale,verts=verts,uv=np.array(uv),faces=faces))
 if v<15:r.skip(r.get('I')[0]*16)
 nboxes=r.get('I')[0];r.skip(nboxes*(40 if v>=13 else 36));assert r.p==len(b)
 # RSM permits repeated mesh names. Parents resolve to the first named node;
 # transformed vertices must be cached by node identity, never by display name.
 lookup={};cache={}
 for n in nodes:lookup.setdefault(n['name'],n)
 def resolve(n,chain=()):
  key=id(n)
  if key in cache:return cache[key]
  assert key not in chain,'node parent cycle'
  parent=lookup.get(n['parent']);base=resolve(parent,chain+(key,))[0] if parent is not None and parent is not n else np.eye(4)
  node=base@translation(n['pos'])@n['rot']@scaling(n['scale']);own=node@(translation(n['offset']) if nn>1 else np.eye(4));basis=np.eye(4);basis[:3,:3]=n['basis'];own=own@basis
  vv=(own@np.c_[n['verts'],np.ones(len(n['verts']))].T).T[:,:3];cache[key]=(node,vv);return cache[key]
 vv=[resolve(n)[1] for n in nodes];allv=np.concatenate(vv);lo=allv.min(axis=0);hi=allv.max(axis=0);centre=(lo+hi)/2;origin=np.array([centre[0],hi[1],centre[2]])
 result=[]
 for n,p in zip(nodes,vv):
  pp=(p-origin)*1.6;pp=pp[:,[0,2,1]];pp[:,2]*=-1
  for vi,ti,tex in n['faces']:result.append((textures[tex],pp[list(vi)],n['uv'][list(ti)]))
 return result
# Split repeated UVs at integer boundaries, preserving geometry barycentrically.
def clip(poly,axis,value,greater):
 out=[]
 for a,b in zip(poly,poly[1:]+poly[:1]):
  ia=(a[3+axis]>=value) if greater else (a[3+axis]<=value);ib=(b[3+axis]>=value) if greater else (b[3+axis]<=value)
  if ia:out.append(a)
  if ia!=ib:
   t=(value-a[3+axis])/(b[3+axis]-a[3+axis]);out.append(a+(b-a)*t)
 return out
def uv_tiles(points,uv):
 # Bound extreme decorative UV repeats to prevent explosive tessellation.
 if (np.ptp(uv,axis=0)>=32).any():
  uv=(uv-np.floor(uv.min(axis=0)))/np.maximum(1,np.ceil(np.ptp(uv,axis=0)/8))
 poly=[np.r_[p,t] for p,t in zip(points,uv)];low=np.floor(uv.min(axis=0)).astype(int);high=np.ceil(uv.max(axis=0)).astype(int)-1;high=np.maximum(high,low)
 assert (high-low<32).all(),'unreasonable UV repeat extent'
 for iy in range(low[1],high[1]+1):
  for ix in range(low[0],high[0]+1):
   pp=poly
   for axis,edge,great in [(0,ix,True),(0,ix+1,False),(1,iy,True),(1,iy+1,False)]:pp=clip(pp,axis,edge,great) if pp else []
   for j in range(1,len(pp)-1):
    tri=np.array([pp[0],pp[j],pp[j+1]]);tri[:,3:]-=[ix,iy]
    if np.linalg.norm(np.cross(tri[1,:3]-tri[0,:3],tri[2,:3]-tri[0,:3]))>1e-6:yield tri

def convert(paths,root,map_names=None,texture_limit=128,*,assets=None,emit_c=True,preview=True):
 if assets is None:assets={}
 for path in paths:
  with zipfile.ZipFile(path) as z:
   for row in csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))):
    b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];assets[row['virtual_path'].lower()]=b
 map_names=map_names or ['prt_fild08','prt_fild05'];worlds=[world(assets['data\\'+n+'.rsw']) for n in map_names];names=sorted({name for w in worlds for name,v in w if 'data\\model\\'+name in assets and assets['data\\model\\'+name][14]==255})
 models=[model(assets['data\\model\\'+n]) for n in names];textures=sorted({t for m in models for t,p,u in m});images={}
 for name in textures:
  im=Image.open(io.BytesIO(assets['data\\texture\\'+name])).convert('RGBA');a=np.array(im);mask=(a[:,:,0]>230)&(a[:,:,1]<20)&(a[:,:,2]>230);a[mask,3]=0;im=Image.fromarray(a);im.thumbnail((texture_limit,texture_limit),Image.Resampling.LANCZOS);a=np.array(im);mask=a[:,:,3]==0
  # Extend RGB across cutout edges to reduce dark bilinear fringes. Alpha remains zero.
  valid=~mask
  for _ in range(2):
   expanded=valid.copy()
   for dy,dx in [(1,0),(-1,0),(0,1),(0,-1)]:
    source=np.roll(np.roll(valid,dy,0),dx,1);source[:max(dy,0)]=False
    if dy<0:source[dy:]=False
    if dx>0:source[:,:dx]=False
    if dx<0:source[:,dx:]=False
    take=~expanded&source;rgb=np.roll(np.roll(a[:,:,:3],dy,0),dx,1);a[take,:3]=rgb[take];expanded|=take
   valid=expanded
  images[name]=Image.fromarray(a)
 # MaxRects packing: retain full source resolution in the smallest height.
 width=2048
 def pack(height):
  free=[(0,0,width,height)];slots={}
  for name in sorted(textures,key=lambda n:(-images[n].width*images[n].height,-max(images[n].size),n)):
   w,h=images[name].size;rw,rh=w+4,h+4;choices=[]
   for x,y,fw,fh in free:
    if rw<=fw and rh<=fh:choices.append((min(fw-rw,fh-rh),max(fw-rw,fh-rh),y,x))
   if not choices:return None
   _,_,y,x=min(choices);slots[name]=(x+2,y+2,w,h);new=[]
   for fx,fy,fw,fh in free:
    if x>=fx+fw or x+rw<=fx or y>=fy+fh or y+rh<=fy:new.append((fx,fy,fw,fh));continue
    if x>fx:new.append((fx,fy,x-fx,fh))
    if x+rw<fx+fw:new.append((x+rw,fy,fx+fw-x-rw,fh))
    if y>fy:new.append((fx,fy,fw,y-fy))
    if y+rh<fy+fh:new.append((fx,y+rh,fw,fy+fh-y-rh))
   free=[]
   for i,r in enumerate(new):
    if any(i!=j and r[0]>=q[0] and r[1]>=q[1] and r[0]+r[2]<=q[0]+q[2] and r[1]+r[3]<=q[1]+q[3] and (r!=q or j<i) for j,q in enumerate(new)):continue
    free.append(r)
  return slots
 height=1024;slots=pack(height)
 if slots is None:height=2048;slots=pack(height)
 if slots is None:raise AtlasPackingError('scenery atlas exceeds bounded texture capacity')
 atlas=Image.new('RGBA',(width,height))
 for name,(x,y,w,h) in slots.items():
  im=images[name];atlas.paste(im,(x,y));atlas.paste(im.crop((0,0,1,h)).resize((2,h)),(x-2,y));atlas.paste(im.crop((w-1,0,w,h)).resize((2,h)),(x+w,y));atlas.paste(im.crop((0,0,w,1)).resize((w,2)),(x,y-2));atlas.paste(im.crop((0,h-1,w,h)).resize((w,2)),(x,y+h))
 a=np.array(atlas,dtype=np.uint16);pixels=((a[:,:,3]>=128).astype(np.uint16)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3)
 vertices=[];directory=[];bounds=[];uvmin=0;uvmax=1
 for m in models:
  start=len(vertices)
  for tex,points,uv in m:
   uvmin=min(uvmin,float(uv.min()));uvmax=max(uvmax,float(uv.max()));x,y,w,h=slots[tex]
   for tri in uv_tiles(points,uv):
    tri[:,3]=x+(tri[:,3]*.98+.01)*w;tri[:,4]=y+(tri[:,4]*.98+.01)*h;vertices.extend(tri)
  p=np.array(vertices[start:]);assert len(p)>0;directory.append((start,len(vertices)-start));bounds.append((p[:,:3].min(axis=0),p[:,:3].max(axis=0)))
 vertices=np.array(vertices,dtype='<f4');assert np.isfinite(vertices).all();instances=[];reports=[]
 P=np.array([[1,0,0],[0,0,1],[0,-1,0]],float)
 for wi,w in enumerate(worlds):
  rows=[];missing=collections.Counter()
  for name,v in w:
   if name not in names:missing[name]+=1;continue
   mid=names.index(name);rx,ry,rz=np.radians(v[3:6]);R=(rotation(rz,[0,0,1])@rotation(rx,[1,0,0])@rotation(ry,[0,1,0]))[:3,:3];basis=P@R@np.diag(v[6:9])@P.T
   mw,mh=struct.unpack_from('<II',assets['data\\'+map_names[wi]+'.gnd'],6);centre=np.array([v[0]*1.6+mw*8,v[2]*1.6+mh*8,-v[1]*1.6]);matrix=np.c_[basis,centre]
   lo,hi=bounds[mid];corners=np.array([[hi[0] if k&1 else lo[0],hi[1] if k&2 else lo[1],hi[2] if k&4 else lo[2]] for k in range(8)])@basis.T+centre
   bbox=np.r_[corners.min(axis=0),corners.max(axis=0)]
   rows.append(struct.pack('<I18f',mid,*matrix.flatten(),*bbox))
  instances.append(rows);reports.append(dict(map=map_names[wi],total_instances=len(w),rendered_instances=len(rows),missing_models=dict(missing)))
 out=root/'SceneryAssets';out.mkdir(exist_ok=True)
 blobs=[struct.pack('<II',width,height)+pixels.astype('<u2').tobytes(),struct.pack('<I',len(vertices))+vertices.tobytes(),struct.pack('<III',len(models),len(instances[0]),len(instances[1]) if len(instances)>1 else 0)+np.array(directory,dtype='<u4').tobytes()+b''.join(row for group in instances for row in group)]
 for name,b in zip(['atlas.bin','mesh.bin','instances.bin'],blobs):(out/name).write_bytes(b)
 if preview:atlas.save(out/'atlas-preview.png')
 if emit_c:
  with (root/'Source/scenery_assets.c').open('w') as f:
   f.write('/* Generated from user-supplied RO assets; original ownership retained. */\n')
   for i,b in enumerate(blobs):
    packed=zlib.compress(b,9);f.write('const unsigned int scenery%d_raw=%d,scenery%d_size=%d;\nconst unsigned char scenery%d[]={\n'%(i,len(b),i,len(packed),i))
    for at in range(0,len(packed),32):f.write(','.join(map(str,packed[at:at+32]))+',\n')
    f.write('};\n');print('scenery',i,'raw',len(b),'packed',len(packed),flush=True)
 report=dict(atlas=[width,height],textures=len(textures),models=names,vertices=len(vertices),uv_range=[uvmin,uvmax],maps=reports,raw_total=sum(map(len,blobs)))
 (root/'SCENERY-CONVERSION-REPORT.json').write_text(json.dumps(report,indent=2,ensure_ascii=False));print({k:v for k,v in report.items() if k not in ('models','maps')},flush=True)
 return report
if __name__=='__main__':convert(sys.argv[1:],Path(__file__).resolve().parent.parent)
