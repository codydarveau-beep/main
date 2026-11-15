# MIT. Bake original STR layers, including fade/UV transforms, at bounded15Hz.
from pathlib import Path
import struct,zlib,json,math,io,re
import numpy as np
from PIL import Image
r=Path(__file__).resolve().parent;assets={}
for folder in ['Test45-return','Test45-supplement']:
 for p in (r.parent.parent/'asset-library'/folder/'data').rglob('*'):
  if p.is_file():assets[str(p.relative_to(r.parent.parent/'asset-library'/folder)).replace('/','\\').lower()]=p.read_bytes()
ns={'struct':struct,'math':math,'np':np,'Image':Image};source=(r/'convert_art41.py').read_text();exec(source[source.index('def parse_str'):source.index('records=[];payload=bytearray()')].replace('0<n<=32','0<n<=64'),ns)
old=(r/'art_assets41.h').read_text();matches=re.findall(r'\{(\d+),(\d+),(\d+),([0-9.e+-]+)f\}',old);records=[{'offset':int(a),'packed':int(b),'raw':int(c),'scale':float(d)}for a,b,c,d in matches];payload=bytearray(map(int,re.findall(r'\d+',re.search(r'art39Packed\[\]=\{(.*?)\};',old,re.S)[1])));pre=r.parent/'Effects45';pre.mkdir(exist_ok=True)
for name in ['firepillar','firepillarbomb','stormgust','quagmire','earthhit','bowling']:
 fps,end,layers=ns['parse_str'](assets['data\\texture\\effect\\'+name+'.str']);stride=8 if name=='stormgust'else 4;times=list(range(0,end,stride));poses=[[(names,ns['sample'](keys,t))for names,keys in layers]for t in times];points=[p for pose in poses for names,a in pose if names and a and a[27]>0 for p in ns['coords'](a)];scale=min(.5,60/max(1,max(abs(x-320)for x,y in points)),184/max(1,320-min(y for x,y in points)),56/max(1,max(y for x,y in points)-320));textures={n:Image.open(io.BytesIO(assets['data\\texture\\effect\\'+n])).convert('RGBA')for names,_ in layers for n in names};frames=[]
 for pose in poses:
  canvas=np.zeros((256,128,3),np.float32)
  for names,a in pose:
   if not names or a is None or a[27]<=0:continue
   assert (a[28],a[29])==(5,7),(name,a[28:30]);im=textures[names[int(max(0,a[20]))%len(names)]];pts=[((x-320)*scale+64,(y-320)*scale+192)for x,y in ns['coords'](a)];p0=np.array(pts[0]);basis=np.array([np.array(pts[1])-p0,np.array(pts[3])-p0]).T
   if abs(np.linalg.det(basis))<1e-6:continue
   inv=np.linalg.inv(basis);assert a[4:12]==[0,0,1,1,0,0,1,1],(name,a[4:12]);uv=np.array([[0,0],[1,0],[0,1]])*[im.width,im.height];mat=np.array([uv[1]-uv[0],uv[2]-uv[0]]).T@inv;off=uv[0]-mat@p0;warped=im.transform((128,256),Image.Transform.AFFINE,tuple([*mat[0],off[0],*mat[1],off[1]]),Image.Resampling.BILINEAR);ar=np.array(warped,dtype=np.float32);col=np.clip(np.array(a[24:27]),0,255)/255;alpha=min(255,max(0,a[27]))/255;canvas+=ar[:,:,:3]*col*(ar[:,:,3:4]/255)*alpha
  frames.append(Image.fromarray(np.clip(canvas,0,255).astype('uint8'),'RGB'))
 raw=ns['sparse'](frames,[(0,len(frames),int(stride*1000/60))]*40,list(range(len(frames))));cp=zlib.compress(raw,9);records.append({'name':name,'offset':len(payload),'packed':len(cp),'raw':len(raw),'scale':scale});payload+=cp
 sheet=Image.new('RGB',(128*8,256),(25,35,30))
 for i in range(8):sheet.paste(frames[min(len(frames)-1,round(i*(len(frames)-1)/7))],(i*128,0))
 sheet.save(pre/(name+'.png'));print(name,len(raw),len(cp),scale,flush=True)
# Flight uses the actual original lightning-ball texture; no substituted impact ring.
for name,tex in [('jupitel_ball','thunder_ball_a.bmp')]:
 im=Image.open(io.BytesIO(assets['data\\texture\\effect\\'+tex])).convert('RGBA');frames=[]
 for i in range(12):
  canvas=Image.new('RGB',(128,256));size=(32,32)if name=='jupitel_ball'else(36,70);layer=im.resize(size,Image.Resampling.LANCZOS);a=np.array(layer);a[:,:,0:3]=(a[:,:,0:3].astype('uint16')*a[:,:,3:4]//255).astype('uint8');layer=Image.fromarray(a).convert('RGB');canvas.paste(layer,(64-size[0]//2,192-size[1]));frames.append(canvas)
 raw=ns['sparse'](frames,[(0,len(frames),40)]*40,list(range(len(frames))));cp=zlib.compress(raw,9);records.append({'name':name,'offset':len(payload),'packed':len(cp),'raw':len(raw),'scale':.5});payload+=cp;print(name,len(raw),len(cp))
(r/'art_assets45.h').write_text('/* Original sampled effect assets, bounded containers. */\n#define ART39_COUNT %d\ntypedef struct {unsigned offset,packed,raw;float scale;} Art39Blob;\nstatic const Art39Blob art39Blobs[ART39_COUNT]={\n'%len(records)+',\n'.join('{%d,%d,%d,%.9gf}'%(x['offset'],x['packed'],x['raw'],x['scale'])for x in records).replace(',1f}',',1.0f}')+'\n};\nstatic const unsigned char art39Packed[]={\n'+','.join(map(str,payload))+'\n};\n');(r/'effects45.json').write_text(json.dumps(records,indent=2));print('total decoded',sum(x['raw']for x in records),'packed',len(payload))
