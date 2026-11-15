# MIT. Converts supplied RO SPR/ACT assets into deduplicated combat frames.
from pathlib import Path
import zipfile,csv,io,hashlib,struct,zlib,json,sys
import numpy as np
from PIL import Image
root=Path(__file__).resolve().parent.parent
out=root/'BuildAssets';out.mkdir(exist_ok=True)
assets={}
for name in sys.argv[1:]:
 with zipfile.ZipFile(name) as z:
  for r in csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))):
   b=z.read(r['payload']);assert hashlib.sha256(b).hexdigest()==r['sha256'];assets[r['virtual_path'].lower()]=b
class Reader:
 def __init__(self,b):self.b=b;self.p=0
 def take(self,n):
  b=self.b[self.p:self.p+n];assert len(b)==n;self.p+=n;return b
 def unpack(self,f):return struct.unpack('<'+f,self.take(struct.calcsize('<'+f)))
 def one(self,f):return self.unpack(f)[0]
def spr(b):
 r=Reader(b);assert r.take(4)==b'SP\x01\x02';n,rgba=r.unpack('HH');assert rgba==0
 pal=np.frombuffer(b[-1024:],np.uint8).reshape(256,4).copy();pal[:,3]=255;pal[0,3]=0;images=[]
 for _ in range(n):
  iw,ih,sz=r.unpack('HHH');enc=r.take(sz);raw=[];j=0
  while j<len(enc):
   c=enc[j];j+=1
   if c:raw.append(c)
   else:
    count=enc[j];j+=1;raw.extend([0]*(count if count else 2))
  assert len(raw)==iw*ih
  images.append(Image.fromarray(pal[np.array(raw).reshape(ih,iw)],'RGBA'))
 assert r.p==len(b)-1024
 return images
def act(b):
 r=Reader(b);assert r.take(2)==b'AC';minor,major,n=r.unpack('BBH');v=major*10+minor;r.take(10);actions=[]
 for _ in range(n):
  frames=[]
  for __ in range(r.one('I')):
   r.take(32);layers=[]
   for ___ in range(r.one('I')):
    x,y,idx,mirror=r.unpack('4i');col=r.unpack('4B');xs=r.one('f');ys=r.one('f') if v>23 else xs;angle,typ=r.unpack('ii')
    if v>=25:r.take(8)
    layers.append((x,y,idx,mirror,col,xs,ys,angle,typ))
   sound=r.one('i');anchors=[]
   for ___ in range(r.one('i')):
    unused,x,y,unused2=r.unpack('4i');anchors.append((x,y))
   frames.append((layers,anchors))
  actions.append(frames)
 ns=r.one('i');r.take(ns*40);delays=[r.one('f')*25 for _ in range(n)];assert r.p==len(b)
 return actions,delays

def drawlayer(canvas,images,layer,ox=0,oy=0):
 x,y,idx,mirror,col,xs,ys,angle,typ=layer
 if idx<0:return
 assert typ==0 and idx<len(images)
 im=images[idx].copy()
 if mirror:im=im.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
 if xs!=1 or ys!=1:im=im.resize((max(1,round(im.width*abs(xs))),max(1,round(im.height*abs(ys)))),Image.Resampling.NEAREST)
 if angle:im=im.rotate(-angle,expand=True)
 ar=np.array(im).astype(np.uint16);ar=(ar*np.array(col,np.uint16)//255).astype(np.uint8);im=Image.fromarray(ar,'RGBA')
 canvas.alpha_composite(im,(round(64+x+ox-im.width/2),round(80+y+oy-im.height/2)))

def bake(name,body,head,actions,anchor):
 images=spr(assets[body+'.spr']);acts,delays=act(assets[body+'.act'])
 if head:heads=spr(assets[head+'.spr']);hacts,hdelays=act(assets[head+'.act'])
 frames=[];lookup={};sequence=[];meta=[];preview=[]
 for group in actions:
  for direction in range(8):
   ai=group*8+direction;assert ai<len(acts);start=len(sequence)
   for fi,(layers,anchors) in enumerate(acts[ai]):
    canvas=Image.new('RGBA',(128,128))
    for layer in layers:drawlayer(canvas,images,layer)
    if head:
     hl,hanchors=hacts[ai][min(fi,len(hacts[ai])-1)];ox=oy=0
     if anchors and hanchors:ox=anchors[0][0]-hanchors[0][0];oy=anchors[0][1]-hanchors[0][1]
     for layer in hl:drawlayer(canvas,heads,layer,ox,oy)
    data=canvas.tobytes();index=lookup.get(data)
    if index is None:index=len(frames);lookup[data]=index;frames.append(data)
    sequence.append(index)
    if fi==0 and direction==0:preview.append(canvas)
   meta.append((start,len(sequence)-start,max(20,int(delays[ai]))))
 # Sparse frame storage preserves the original 128x128 canvas/anchors.
 directory=[];pixels=bytearray()
 for data in frames:
  im=Image.frombytes('RGBA',(128,128),data);bbox=im.getbbox()
  if not bbox:directory.append((0,0,0,0,len(pixels)));continue
  x0,y0,x1,y1=bbox;a=np.array(im.crop(bbox),dtype=np.uint32);argb=(a[:,:,3]<<24)|(a[:,:,0]<<16)|(a[:,:,1]<<8)|a[:,:,2]
  directory.append((x0,y0,x1-x0,y1-y0,len(pixels)));pixels+=argb.astype('<u4').tobytes()
 raw=bytearray(struct.pack('<8I',128,128,len(frames),len(meta),len(sequence),64,anchor,len(pixels)))
 for m in meta:raw+=struct.pack('<III',*m)
 raw+=np.array(sequence,dtype='<u4').tobytes()
 for entry in directory:raw+=struct.pack('<5I',*entry)
 raw+=pixels
 (out/(name+'.bin')).write_bytes(raw)
 im=Image.new('RGBA',(128*len(preview),128),(45,65,50,255))
 for i,frame in enumerate(preview):im.alpha_composite(frame,(i*128,0))
 im.save(root/(name+'-preview.png'))
 print(name,'unique',len(frames),'sequence',len(sequence),'RAM MB',round(len(raw)/1048576,2),flush=True)
 return raw

body='data\\sprite\\인간족\\몸통\\남\\초보자_남';head='data\\sprite\\인간족\\머리통\\남\\1_남'
blobs=[bake('player',body,head,[0,1,5,6,8],90),bake('poring','data\\sprite\\몬스터\\poring',None,[0,1,2,3,4],86),bake('lunatic','data\\sprite\\몬스터\\lunatic',None,[0,1,2,3,4],89)]
with (root/'Source/combat_assets.c').open('w') as f:
 f.write('/* Generated user-supplied assets. Original ownership retained. */\n')
 for i,raw in enumerate(blobs):
  packed=zlib.compress(raw,9);f.write('const unsigned int combat%d_raw=%d, combat%d_size=%d;\nconst unsigned char combat%d[]={\n'%(i,len(raw),i,len(packed),i))
  for at in range(0,len(packed),32):f.write(','.join(str(v) for v in packed[at:at+32])+',\n')
  f.write('};\n')
