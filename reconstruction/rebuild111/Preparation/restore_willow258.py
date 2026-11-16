# SUPERSEDED EXPERIMENT. The full-frame representation is too expensive for64MB.
# Production uses build_willow_layers259.py and an unchanged original pack.
import sys
if '--regenerate-superseded-experiment' not in sys.argv:
 raise SystemExit('Superseded experiment258; use build_willow_layers259.py.')
"""Reconstruct complete Willow death ACTs with uncropped, bounded streamed frames.
The retained source SPR/ACT is authoritative; this is a reconstructed repair,
not a claim to have found the unidentified historical Willow fix.
"""
from pathlib import Path
import hashlib,json,re,struct,sys,zlib,shutil
import numpy as np
from PIL import Image
R=Path(__file__).resolve().parent.parent;D=R/'Restoration252';S=R/'Source'
sys.path.insert(0,str(S));import ro_sprite_bake as ro
base=Path('/workspace/myro/hotfix171/Enemies/enemies.bin')
assets=Path('/workspace/myro/asset-library/Payon43-return/data/sprite/몬스터')
original=(D/'legacy-enemy-streams-before258.h').read_text()
rows=[list(map(int,re.findall(r'\d+',r)))for r in re.findall(r'\{([^{}]+)\}',original)]
assert len(rows)==50
append=bytearray();report=[]
with base.open('rb') as inp:
 for k,name in [(19,'wilow'),(27,'elder_wilow')]:
  off,packed,size,crc,framesoff,framesbytes,guardian=rows[k];inp.seek(off);raw=zlib.decompress(inp.read(packed));w,h,n,actions,seqn,ax,ay,pb=struct.unpack_from('<8I',raw);assert (w,h,actions)==(128,256,40)
  oldmeta=[struct.unpack_from('<3I',raw,32+i*12)for i in range(40)];oldseq=struct.unpack_from('<'+'I'*seqn,raw,512)
  doff=512+seqn*4;directory=[struct.unpack_from('<5I',raw,doff+i*20)for i in range(n)];blocks=[struct.unpack_from('<4I',raw,doff+n*20+i*16)for i in range(n)]
  actfile=assets/(name+'.act');sprfile=assets/(name+'.spr');acts,delays=ro.act(actfile.read_bytes());images=ro.spr(sprfile.read_bytes());ro.originY=512
  # Full source layers use smooth scaling as on the original textured quads.
  # The old nearest-resized 128x256 bake clipped the expanding fade to a box.
  drawsource=Path(ro.__file__).read_text();start=drawsource.index('def drawlayer(');end=drawsource.index('\ndef bake(',start);scope=dict(ro.__dict__);exec(drawsource[start:end].replace('Image.Resampling.NEAREST','Image.Resampling.BILINEAR'),scope);draw=scope['drawlayer']
  death=[];bounds=[448,352,576,608]
  for direction in range(8):
   out=[]
   for layers,_ in acts[32+direction]:
    canvas=Image.new('RGBA',(1024,1024))
    for layer in layers:draw(canvas,images,layer,448,0)
    box=canvas.getbbox();assert box and box[0]>0 and box[1]>0 and box[2]<1024 and box[3]<1024
    bounds=[min(bounds[0],box[0]),min(bounds[1],box[1]),max(bounds[2],box[2]),max(bounds[3],box[3])];out.append(canvas)
   death.append(out)
  left,top,right,bottom=bounds;dx,dy=448-left,352-top;neww,newh=right-left,bottom-top
  assert neww<=1024 and newh<=1024
  newdir=[];newblocks=[];blob=bytearray();lookup={};mapping={};meta=[];sequence=[];maxgpu=0
  def addframe(x,y,ww,hh,cp,rawbytes):
   nonlocal_placeholder=None
   global maxgpu
   key=(x,y,ww,hh,cp)
   if key in lookup:return lookup[key]
   frame=len(newdir);lookup[key]=frame;newdir.append((x,y,ww,hh,0));newblocks.append((len(blob),len(cp),rawbytes,zlib.crc32(cp)));blob.extend(cp);maxgpu=max(maxgpu,(((ww+2)*2+63)&~63)*(hh+2));return frame
  # Preserve every non-death packed pixel and its animation metadata exactly.
  for action in range(32):
   at,count,ms=oldmeta[action];start=len(sequence)
   for old in oldseq[at:at+count]:
    if old not in mapping:
     x,y,ww,hh,_=directory[old];b,sz,r,c=blocks[old];inp.seek(framesoff+b);cp=inp.read(sz);assert zlib.crc32(cp)==c
     mapping[old]=addframe(x+dx,y+dy,ww,hh,cp,r)
    sequence.append(mapping[old])
   meta.append((start,count,ms))
  for direction,frames in enumerate(death):
   start=len(sequence)
   for canvas in frames:
    # Quantize once to the existing 16-bit alpha format, then crop real alpha.
    a=np.asarray(canvas,dtype=np.uint32);q=((a[:,:,3]>>4)<<12)|((a[:,:,0]>>4)<<8)|((a[:,:,1]>>4)<<4)|(a[:,:,2]>>4)
    yy,xx=np.nonzero(q>>12);assert len(xx);x,y,x1,y1=int(xx.min()),int(yy.min()),int(xx.max())+1,int(yy.max())+1
    pixels=q[y:y1,x:x1].astype('<u2').tobytes();sequence.append(addframe(x-left,y-top,x1-x,y1-y,zlib.compress(pixels,9),len(pixels)))
   meta.append((start,len(frames),max(20,round(delays[32+direction]))))
  header=struct.pack('<8I',neww,newh,len(newdir),40,len(sequence),ax+dx,ay+dy,0xc0000000)
  metadata=header+b''.join(struct.pack('<3I',*m)for m in meta)+struct.pack('<'+'I'*len(sequence),*sequence)+b''.join(struct.pack('<5I',*d)for d in newdir)+b''.join(struct.pack('<4I',*b)for b in newblocks)
  cp=zlib.compress(metadata,9);offset=base.stat().st_size+len(append);rows[k]=[offset,len(cp),len(metadata),zlib.crc32(cp),offset+len(cp),len(blob),0];append.extend(cp);append.extend(blob)
  report.append(dict(kind=k,name=name,sourceSPR_SHA256=hashlib.sha256(sprfile.read_bytes()).hexdigest(),sourceACT_SHA256=hashlib.sha256(actfile.read_bytes()).hexdigest(),canvas=[neww,newh],deathFramesByDirection=[len(v)for v in death],sourceDeathMilliseconds=[round(delays[32+i]*len(death[i]))for i in range(8)],maximumGPUCropBytes=maxgpu,nonDeathPackedPixelsAndTimingPreserved=True,packedBytes=len(cp)+len(blob),reconstructed=True))
# Keep the original immutable pack; make a local candidate only.
suffix=D/'willow-stream-append258.bin';suffix.write_bytes(append)
out=R/'XboxFiles/enemies.bin';expected=base.stat().st_size+len(append)
if out.is_symlink():out.unlink()
if not out.exists()or out.stat().st_size!=expected:
 shutil.copyfile(base,out)
 with out.open('ab')as f:f.write(append)
else:
 with out.open('rb')as f:f.seek(base.stat().st_size);assert f.read()==append
(S/'legacy_enemy_streams171.h').write_text('/* Original stream metadata; complete source Willow death reconstruction258. */\nstatic const EnemyStream51 legacyEnemyStreams171[50]={'+','.join('{'+','.join(str(v)+'u'for v in row)+'}'for row in rows)+'};\n')
s=(D/'enemy-disc-data-before258.h').read_text();s,n=re.subn(r'(#define ENEMY_FILE_BYTES )\d+',lambda m:m[1]+str(expected),s);assert n==1;(S/'enemy_disc_data44.h').write_text(s)
(R/'Validation/Willow-Reconstruction258.json').write_text(json.dumps(dict(reconstructed=True,source='retained original SPR/ACT, not an identified historical fix',species=report,appendBytes=len(append),appendSHA256=hashlib.sha256(append).hexdigest(),sourcePackPreserved=str(base),XboxVisualAnd64MBStressPending=True),indent=2)+'\n');print(json.dumps(report))
