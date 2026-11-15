"""MIT. Reproducible bounded STR/SPR/ACT bake from hash-verified collector folders.
python convert_art39.py old-textures.zip returned37-folder returned39-folder body-folder
STR delta keys are sampled at15Hz; original image/color/UV/rotation preserved.
Black-background effects use premultiplied additive RGB1555. Not a full RO renderer.
"""
from pathlib import Path
import sys,csv,io,zipfile,hashlib,struct,zlib,json,math
import numpy as np
from PIL import Image
import ro_sprite_bake as ro
root=Path(__file__).resolve().parent;assets={}
for arg in sys.argv[1:]:
 p=Path(arg)
 if p.is_dir(): rows=csv.DictReader((p/'Assets.csv').open(encoding='utf-8-sig'));read=lambda n:(p/n).read_bytes()
 else:
  z=zipfile.ZipFile(p);rows=csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig')));read=z.read
 for row in rows:
  b=read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];assets[row['virtual_path'].replace('\\\\','\\').lower()]=b
 if not p.is_dir():z.close()
def parse_str(b):
 assert b[:4]==b'STRM';ver,fps,end,n=struct.unpack_from('<4I',b,4);assert ver==148 and fps==60 and 0<n<=32 and 0<end<600
 p=36;layers=[]
 for _ in range(n):
  t=struct.unpack_from('<I',b,p)[0];p+=4;assert t<=32
  names=[b[p+j*128:p+(j+1)*128].split(b'\0')[0].decode('cp949').lower() for j in range(t)];p+=t*128
  k=struct.unpack_from('<I',b,p)[0];p+=4;assert k<1000
  keys=[list(struct.unpack_from('<ii2f8f8ffiff4f3i',b,p+j*124)) for j in range(k)];p+=k*124
  assert all(a[1] in (0,1) and all(math.isfinite(v) for v in a) for a in keys)
  layers.append((names,keys))
 assert p==len(b)
 return fps,end,layers
def sample(keys,t):
 bases=[a for a in keys if a[1]==0 and a[0]<=t]
 if not bases:return None
 a=list(bases[-1]);delta=next((x for x in keys if x[1]==1 and x[0]==a[0]),None)
 elapsed=t-a[0]
 if delta:
  for i in list(range(2,21))+[23,24,25,26,27]:a[i]+=delta[i]*elapsed
 if a[21]==3:a[20]+=elapsed*a[22]
 return a
def coords(a):
 angle=a[23]*math.tau/1024;co,si=math.cos(angle),math.sin(angle)
 return [(a[2]+a[12+i]*co-a[16+i]*si,a[3]+a[12+i]*si+a[16+i]*co) for i in range(4)]
def sparse(frames,meta,seq,anchor=192):
 unique=[];lookup={};sequence=[]
 for im in frames:
  data=im.tobytes()
  if data not in lookup:lookup[data]=len(unique);unique.append(im)
  sequence.append(lookup[data])
 pixels=bytearray();directory=[]
 for im in unique:
  box=im.convert('RGB').getbbox()
  if box:
   x,y,x1,y1=box;ar=np.array(im.crop(box),dtype=np.uint32);v=0x8000|((ar[:,:,0]>>3)<<10)|((ar[:,:,1]>>3)<<5)|(ar[:,:,2]>>3)
   if im.mode=='RGBA':v=((ar[:,:,3]>=128).astype(np.uint32)<<15)|(v&0x7fff)
   directory.append((x,y,x1-x,y1-y,len(pixels)));pixels.extend(v.astype('<u2').tobytes())
  else:directory.append((0,0,0,0,len(pixels)))
 seq=[sequence[i] for i in seq]
 raw=struct.pack('<8I',128,frames[0].height,len(unique),len(meta),len(seq),64,anchor,len(pixels)|0x80000000)
 raw+=b''.join(struct.pack('<3I',*m) for m in meta)+struct.pack('<%dI'%len(seq),*seq)+b''.join(struct.pack('<5I',*d) for d in directory)+pixels
 return raw
records=[];payload=bytearray();previews=root.parent/'ArtPreviews';previews.mkdir(exist_ok=True)
def emit(name,raw,scale=1):
 cp=zlib.compress(raw,9);records.append(dict(name=name,offset=len(payload),packed=len(cp),raw=len(raw),scale=scale,sha256=hashlib.sha256(raw).hexdigest()));payload.extend(cp)
 print(name,'raw',len(raw),'packed',len(cp),'scale',scale,flush=True)
for name in ['energycoat','cure','freeze','holyhit','firewall','firehit','windhit','thunderstorm','stonecurse','cartrevolution']:
 fps,end,layers=parse_str(assets['data\\texture\\effect\\'+name+'.str']);times=list(range(0,end,4));poses=[[(names,sample(keys,t)) for names,keys in layers] for t in times]
 points=[p for pose in poses for names,a in pose if names and a and a[27]>0 for p in coords(a)]
 scale=min(.5,60/max(1,max(abs(x-320) for x,y in points)),184/max(1,320-min(y for x,y in points)),56/max(1,max(y for x,y in points)-320))
 textures={n:Image.open(io.BytesIO(assets['data\\texture\\effect\\'+n])).convert('RGB') for names,_ in layers for n in names}
 frames=[]
 for pose in poses:
  canvas=np.zeros((256,128,3),np.float32)
  for names,a in pose:
   if not names or a is None or a[27]<=0:continue
   assert (a[28],a[29])==(5,7),(name,a[28:30])
   im=textures[names[int(max(0,a[20]))%len(names)]];pts=coords(a);pts=[((x-320)*scale+64,(y-320)*scale+192) for x,y in pts]
   # Affine parallelogram mapping; all supplied STR UVs are rectangular.
   p0=np.array(pts[0]);basis=np.array([np.array(pts[1])-p0,np.array(pts[3])-p0]).T
   if abs(np.linalg.det(basis))<1e-6:continue
   inv=np.linalg.inv(basis);assert a[4:12]==[0,0,1,1,0,0,1,1], 'Unsupported cropped STR texture coordinates'
   uv=np.array([[0,0],[1,0],[0,1]],float)*[im.width,im.height]
   texbasis=np.array([uv[1]-uv[0],uv[2]-uv[0]]).T;mat=texbasis@inv;off=uv[0]-mat@p0
   warped=im.transform((128,256),Image.Transform.AFFINE,tuple([*mat[0],off[0],*mat[1],off[1]]),Image.Resampling.BILINEAR)
   col=np.clip(np.array(a[24:27]),0,255)/255;alpha=min(255,max(0,a[27]))/255
   canvas+=np.array(warped,dtype=np.float32)*col*alpha
  frames.append(Image.fromarray(np.clip(canvas,0,255).astype(np.uint8),'RGB'))
 raw=sparse(frames,[(0,len(frames),67)]*40,list(range(len(frames))))
 emit(name,raw,scale)
 sheet=Image.new('RGB',(128*8,256*2),(25,35,30))
 for i in range(16):
  im=frames[min(len(frames)-1,round(i*(len(frames)-1)/15))];sheet.paste(Image.fromarray(np.clip(np.array(im).astype(int)+[25,35,30],0,255).astype('uint8')),(i%8*128,i//8*256))
 sheet.save(previews/(name+'.png'))
# Original carts: preserve ACT direction/frame timing; bounded idle/walk groups.
ro.originY=80
for style in range(5):
 stem='data\\sprite\\이팩트\\손수레'+(str(style) if style else '')
 images=ro.spr(assets[stem+'.spr']);acts,delays=ro.act(assets[stem+'.act']);frames=[];meta=[];seq=[]
 for group in range(5):
  for direction in range(8):
   ai=(8+direction if group==1 and len(acts)>=16 else direction)%len(acts);start=len(seq)
   for layers,anchors in acts[ai]:
    im=Image.new('RGBA',(128,128))
    for layer in layers:ro.drawlayer(im,images,layer)
    seq.append(len(frames));frames.append(im)
   meta.append((start,len(seq)-start,max(20,int(delays[ai]))))
 raw=sparse(frames,meta,seq,90);emit('cart'+str(style),raw)
 sheet=Image.new('RGBA',(128*8,128),(35,45,35,255))
 for d in range(8):sheet.alpha_composite(frames[meta[d][0]],(d*128,0))
 sheet.save(previews/('cart%d.png'%style))
assert sum(r['raw'] for r in records)<6*1024*1024
(root/'art_assets39.h').write_text('/* Generated bounded original artwork. MIT converter; resource owners retain rights. */\n#define ART39_COUNT %d\ntypedef struct {unsigned offset,packed,raw;float scale;} Art39Blob;\nstatic const Art39Blob art39Blobs[ART39_COUNT]={\n'%len(records)+',\n'.join('{%d,%d,%d,%.9gf}'%(r['offset'],r['packed'],r['raw'],r['scale']) for r in records).replace(',1f}',',1.0f}')+'\n};\nstatic const unsigned char art39Packed[]={\n'+','.join(str(x) for x in payload)+'\n};\n')
(root/'art-manifest39.json').write_text(json.dumps(dict(clips=records,rawBytes=sum(r['raw'] for r in records),packedBytes=len(payload),effectFPS=15,effectBlend='premultiplied additive RGB1555',sources={n:hashlib.sha256(b).hexdigest() for n,b in assets.items()}),indent=2)+'\n')
print('TOTAL',sum(r['raw'] for r in records),len(payload))
