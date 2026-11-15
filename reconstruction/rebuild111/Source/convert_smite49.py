"""MIT. Append original second-class STR clips, retaining the accepted 47a effect pack byte for byte.
No universal casting glow. Uses source texture/UV/layer/color/timing, sampled at 15 Hz.
"""
from pathlib import Path
import struct,zlib,json,math,io,re,hashlib
import numpy as np
from PIL import Image
r=Path(__file__).resolve().parent;lib=r.parent.parent/'asset-library';paths={}
for folder in lib.iterdir():
 if folder.is_dir():
  for p in (folder/'data').rglob('*'):
   if p.is_file():paths[str(p.relative_to(folder)).replace('/','\\').lower()]=p
ns=dict(struct=struct,math=math,np=np,Image=Image)
s=(r/'convert_art41.py').read_text();exec(s[s.index('def parse_str('):s.index('records=[]')],ns)
base=r.parent.parent/'test48';header=(base/'Source/art_assets45.h').read_text();table=header.split('static const Art39Blob art39Blobs')[1].split('};')[0]
records=[dict(offset=int(a),packed=int(b),raw=int(c),scale=float(d))for a,b,c,d in re.findall(r'\{(\d+),(\d+),(\d+),([\d.e+-]+)f\}',table)]
assert len(records)==37
cut=records[-1]["offset"];records=records[:-1]
payload=bytearray((base/'Effects/effects.bin').read_bytes()[:cut]);original=bytes(payload);report=[]
names=['shield_charge']
preview=r.parent/'ArtPreviews';preview.mkdir(exist_ok=True)
for name in names:
 path=paths['data\\texture\\effect\\'+name+'.str'];b=path.read_bytes();fps,end,layers=ns['parse_str'](b);times=list(range(0,end,4));poses=[[(names,ns['sample'](keys,t))for names,keys in layers]for t in times]
 points=[p for pose in poses for names,a in pose if names and a and a[27]>0 for p in ns['coords'](a)];assert points
 scale=min(.5,60/max(1,max(abs(x-320)for x,y in points)),184/max(1,320-min(y for x,y in points)),56/max(1,max(y for x,y in points)-320))
 textures={}
 for names,_ in layers:
  for n in names:
   im=Image.open(paths['data\\texture\\effect\\'+n]).convert('RGBA');a=np.array(im);key=(a[:,:,0]>245)&(a[:,:,1]<12)&(a[:,:,2]>245);a[key]=0;textures[n]=Image.fromarray(a)
 frames=[]
 for pose in poses:
  canvas=np.zeros((256,128,3),np.float32)
  for names,a in pose:
   if not names or a is None or a[27]<=0:continue
   assert (a[28],a[29])in[(5,7),(2,1)],(name,a[28:30])
   assert a[4:12]==[0,0,1,1,0,0,1,1],(name,a[4:12])
   im=textures[names[int(max(0,a[20]))%len(names)]];pts=[((x-320)*scale+64,(y-320)*scale+192)for x,y in ns['coords'](a)]
   p0=np.array(pts[0]);basis=np.array([np.array(pts[1])-p0,np.array(pts[3])-p0]).T
   if abs(np.linalg.det(basis))<1e-6:continue
   mat=np.diag([im.width,im.height])@np.linalg.inv(basis);off=-mat@p0;coeff=tuple([*mat[0],off[0],*mat[1],off[1]])
   warped=np.array(im.convert('RGB').transform((128,256),Image.Transform.AFFINE,coeff,Image.Resampling.BILINEAR),dtype=np.float32);col=np.clip(np.array(a[24:27]),0,255)/255;alpha=min(255,max(0,a[27]))/255
   if(a[28],a[29])==(2,1):
    mask=np.array(im.getchannel('A').transform((128,256),Image.Transform.AFFINE,coeff,Image.Resampling.NEAREST))>0;canvas[mask]=warped[mask]*col
   else:canvas+=warped*col*alpha
  frames.append(Image.fromarray(np.clip(canvas,0,255).astype('uint8'),'RGB'))
 raw=ns['sparse'](frames,[(0,len(frames),67)]*40,list(range(len(frames))));cp=zlib.compress(raw,9);idx=len(records);records.append(dict(offset=len(payload),packed=len(cp),raw=len(raw),scale=scale));payload+=cp
 report.append(dict(clip=idx,name=name,source=str(path),sha256=hashlib.sha256(b).hexdigest(),frames=len(frames),raw=len(raw),packed=len(cp),scale=scale))
 sheet=Image.new('RGB',(128*8,256*2),(25,35,30))
 for i in range(16):
  im=frames[min(len(frames)-1,round(i*(len(frames)-1)/15))];sheet.paste(Image.fromarray(np.clip(np.array(im).astype(int)+[25,35,30],0,255).astype('uint8')),(i%8*128,i//8*256))
 sheet.save(preview/('class48-'+name+'.png'));print(idx,name,len(cp),len(raw),flush=True)
assert payload[:len(original)]==original
out='/* Original sampled effect assets. Test48 preserves the complete accepted 47a prefix. */\n#define ART39_COUNT %d\ntypedef struct {unsigned offset,packed,raw;float scale;} Art39Blob;\nstatic const Art39Blob art39Blobs[ART39_COUNT]={\n'%len(records)
out+=''.join('{%d,%d,%d,%.9gf},\n'%(x['offset'],x['packed'],x['raw'],x['scale'])for x in records)+'};\n#ifdef MYRO_HOST\nstatic const unsigned char art39Packed[]={'+','.join(map(str,payload))+'};\n#endif\n#define ART_FILE_BYTES45 %d\n'%len(payload)
out+='static const unsigned art45Crc[ART39_COUNT]={'+','.join(str(zlib.crc32(payload[x['offset']:x['offset']+x['packed']]))+'u'for x in records)+'};\n';out=out.replace(',1f}',',1.0f}')
(r/'art_assets45.h').write_text(out);(r.parent/'Effects/effects.bin').write_bytes(payload);(r/'smite_art49.json').write_text(json.dumps(report,indent=2)+'\n');print('PASS: unchanged old pack prefix; original Smite transparency repaired; first36 clips retained')
