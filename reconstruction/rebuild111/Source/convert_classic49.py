"""MIT. Append returned original classic art; retain clips 0..40 byte-for-byte.
RGBA SPR pixels use source ABGR order and inverted rows. ACT 2.1 has no anchors.
Source parser reference: roBrowserLegacy 2dc0d153, Sprite.js/Action.js.
Run after convert_smite49.py and convert_meteor49.py; this pass is idempotent.
"""
from pathlib import Path
import struct,zlib,json,math,re,hashlib
import numpy as np
from PIL import Image
import ro_sprite_bake as ro
from asset_index49 import paths
r=Path(__file__).resolve().parent
ns=dict(struct=struct,math=math,np=np,Image=Image)
s=(r/'convert_art41.py').read_text();exec(s[s.index('def parse_str('):s.index('records=[]')],ns)
table=(r/'art_assets45.h').read_text().split('static const Art39Blob art39Blobs')[1].split('};')[0]
records=[dict(offset=int(a),packed=int(b),raw=int(c),scale=float(d)) for a,b,c,d in re.findall(r'\{(\d+),(\d+),(\d+),([\d.e+-]+)f\}',table)][:41]
assert len(records)==41
cut=records[-1]['offset']+records[-1]['packed'];payload=bytearray((r.parent/'Effects/effects.bin').read_bytes()[:cut]);prefix=bytes(payload);report=[]
preview=r.parent/'ArtPreviews';preview.mkdir(exist_ok=True)
def read(key):
 p=paths[key.lower()];b=p.read_bytes();report_sources[key]=hashlib.sha256(b).hexdigest();return b
report_sources={}
def emit(name,frames,ms,scale=.5,anchor=192):
 raw=ns['sparse'](frames,[(0,len(frames),ms)]*40,list(range(len(frames))),anchor);cp=zlib.compress(raw,9)
 report.append(dict(name=name,clip=len(records),frames=len(frames),raw=len(raw),packed=len(cp),scale=scale));records.append(dict(offset=len(payload),packed=len(cp),raw=len(raw),scale=scale));payload.extend(cp)
 sheet=Image.new('RGB',(128*8,256),(24,30,24))
 for i in range(8):
  f=frames[round(i*(len(frames)-1)/7)];sheet.paste(f.convert('RGB'),(128*i,0))
 sheet.save(preview/('classic49-'+name+'.png'));print(report[-1],flush=True)
# Complete original Safety Wall STR. Same sampling/source blend as existing accepted clips.
fps,end,layers=ns['parse_str'](read('data\\texture\\effect\\safetywall.str'))
poses=[[(names,ns['sample'](keys,t)) for names,keys in layers] for t in range(0,end,4)]
points=[p for pose in poses for names,a in pose if names and a and a[27]>0 for p in ns['coords'](a)]
scale=min(.5,60/max(1,max(abs(x-320)for x,y in points)),184/max(1,320-min(y for x,y in points)),56/max(1,max(y for x,y in points)-320))
textures={}
for names,_ in layers:
 for n in names:
  im=Image.open(__import__('io').BytesIO(read('data\\texture\\effect\\'+n))).convert('RGBA');a=np.array(im);a[(a[:,:,0]>245)&(a[:,:,1]<12)&(a[:,:,2]>245)]=0;textures[n]=Image.fromarray(a)
frames=[]
for pose in poses:
 canvas=np.zeros((256,128,3),np.float32)
 for names,a in pose:
  if not names or a is None or a[27]<=0:continue
  assert (a[28],a[29])in[(5,7),(2,1)],a[28:30]
  assert a[4:12]==[0,0,1,1,0,0,1,1]
  im=textures[names[int(max(0,a[20]))%len(names)]];pts=[((x-320)*scale+64,(y-320)*scale+192)for x,y in ns['coords'](a)]
  p0=np.array(pts[0]);basis=np.array([np.array(pts[1])-p0,np.array(pts[3])-p0]).T
  if abs(np.linalg.det(basis))<1e-6:continue
  mat=np.diag([im.width,im.height])@np.linalg.inv(basis);off=-mat@p0;coeff=tuple([*mat[0],off[0],*mat[1],off[1]])
  rgba=np.array(im.transform((128,256),Image.Transform.AFFINE,coeff,Image.Resampling.BILINEAR),dtype=np.float32);rgb=rgba[:,:,:3]*(rgba[:,:,3:4]/255);rgb*=np.clip(a[24:27],0,255)/255
  if(a[28],a[29])==(2,1):canvas[rgba[:,:,3]>0]=rgb[rgba[:,:,3]>0]
  else:canvas+=rgb*min(255,max(0,a[27]))/255
 frames.append(Image.fromarray(np.clip(canvas,0,255).astype('uint8')))
emit('safetywall',frames,67,scale)
def sprites(b):
 q=ro.Reader(b);assert q.take(4)==b'SP\x01\x02';ni,nr=q.unpack('HH');out=[]
 if ni:
  pal=np.frombuffer(b[-1024:],np.uint8).reshape(256,4).copy();pal[:,3]=255;pal[0,3]=0
 for i in range(ni):
  w,h,size=q.unpack('HHH');enc=q.take(size);raw=[];j=0
  while j<len(enc):
   c=enc[j];j+=1
   if c:raw.append(c)
   else:count=enc[j];j+=1;raw.extend([0]*(count if count else 2))
  assert len(raw)==w*h;out.append(Image.fromarray(pal[np.array(raw).reshape(h,w)],'RGBA'))
 for i in range(nr):
  w,h=q.unpack('HH');a=np.frombuffer(q.take(w*h*4),np.uint8).reshape(h,w,4);out.append(Image.fromarray(a[::-1,:,[3,2,1,0]].copy(),'RGBA'))
 assert len(b)-q.p in (0,1024), (q.p,len(b))
 return out,ni

def actions(b):
 q=ro.Reader(b);assert q.take(2)==b'AC';minor,major,n=q.unpack('BBH');v=major*10+minor;assert 20<=v<=25;q.take(10);out=[]
 for _ in range(n):
  frames=[]
  for _ in range(q.one('I')):
   q.take(32);layers=[]
   for _ in range(q.one('I')):
    x,y,idx,mirror=q.unpack('4i');col=q.unpack('4B');xs=q.one('f');ys=q.one('f')if v>23 else xs;angle,typ=q.unpack('ii')
    if v>=25:q.take(8)
    layers.append((x,y,idx,mirror,col,xs,ys,angle,typ))
   q.one('i')
   if v>=23:
    for _ in range(q.one('I')):q.take(16)
   frames.append(layers)
  out.append(frames)
 nsound=q.one('I');q.take(nsound*40);delays=[q.one('f')*25 for _ in range(n)] if v>=22 else [150]*n;assert q.p==len(b)
 return out,delays
ro.originY=192
for name in ['sight','particle1','waterball']:
 stem='data\\sprite\\이팩트\\'+name;images,ni=sprites(read(stem+'.spr'));acts,delays=actions(read(stem+'.act'));frames=[]
 for layers in acts[0]:
  im=Image.new('RGBA',(128,256))
  for layer in layers:
   x,y,idx,mirror,col,xs,ys,angle,typ=layer
   if idx<0:continue
   idx+=ni if typ==1 else 0;ro.drawlayer(im,images,(x*.5,y*.5,idx,mirror,col,xs*.5,ys*.5,angle,0))
  a=np.array(im).astype(np.uint16);a[:,:,:3]=a[:,:,:3]*a[:,:,3:4]//255;frames.append(Image.fromarray(a[:,:,:3].astype('uint8')))
 emit(name,frames,max(1,round(delays[0])))
for name in ['pok3.tga','lens1.tga','shield_boomerang.bmp','water_out_a.bmp','water_out_b.bmp','water_out_c.bmp']:
 im=Image.open(__import__('io').BytesIO(read('data\\texture\\effect\\'+name))).convert('RGBA');a=np.array(im);a[(a[:,:,0]>245)&(a[:,:,1]<12)&(a[:,:,2]>245)]=0;im=Image.fromarray(a);im.thumbnail((64,64),Image.Resampling.LANCZOS);f=Image.new('RGBA',(128,256));f.alpha_composite(im,(64-im.width//2,192-im.height//2));a=np.array(f).astype(np.uint16);a[:,:,:3]=a[:,:,:3]*a[:,:,3:4]//255
 emit(name.split('.')[0],[Image.fromarray(a[:,:,:3].astype('uint8'))],250)
assert payload[:cut]==prefix
out='/* Generated Test49 original classic effect art; clips0..40 retained. */\n#define ART39_COUNT %d\ntypedef struct {unsigned offset,packed,raw;float scale;} Art39Blob;\nstatic const Art39Blob art39Blobs[ART39_COUNT]={\n'%len(records)
out+=''.join('{%d,%d,%d,%.9gf},\n'%(x['offset'],x['packed'],x['raw'],x['scale'])for x in records)+'};\n#ifdef MYRO_HOST\nstatic const unsigned char art39Packed[]={'+','.join(map(str,payload))+'};\n#endif\n#define ART_FILE_BYTES45 %d\n'%len(payload)
out+='static const unsigned art45Crc[ART39_COUNT]={'+','.join(str(zlib.crc32(payload[x['offset']:x['offset']+x['packed']]))+'u'for x in records)+'};\n';out=out.replace(',1f}',',1.0f}')
(r/'art_assets45.h').write_text(out);(r.parent/'Effects/effects.bin').write_bytes(payload);(r/'classic_art49.json').write_text(json.dumps(dict(clips=report,sources=report_sources),indent=2)+'\n')
print('PASS unchanged41-clip prefix; original classic art imported')
