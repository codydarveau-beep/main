# SPDX-License-Identifier: MIT. Adapted sparse RO SPR/ACT converter.
from pathlib import Path
import struct,zlib,json
import numpy as np
from PIL import Image
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
 canvas.alpha_composite(im,(round(64+x+ox-im.width/2),round(originY+y+oy-im.height/2)))

def bake(name,body,head,actions,anchor):
 global originY
 originY=100 if name in ("Knight","HighWizard","Wizard","Sage","Crusader") else 160
 canvasH=128 if name in ("Knight","HighWizard","Wizard","Sage","Crusader") else 256
 anchor+=originY-80
 images=spr(assets[body+'.spr']);acts,delays=act(assets[body+'.act'])
 if head:heads=spr(assets[head+'.spr']);hacts,hdelays=act(assets[head+'.act'])
 frames=[];lookup={};sequence=[];meta=[];preview=[]
 for group in actions:
  for direction in range(8):
   ai=group*8+direction;ai=ai if ai<len(acts) else direction%len(acts);start=len(sequence)
   for fi,(layers,anchors) in enumerate(acts[ai]):
    if fi not in [round(k*(len(acts[ai])-1)/max(1,min(3,len(acts[ai])-1))) for k in range(min(4,len(acts[ai])))]:continue
    canvas=Image.new('RGBA',(128,canvasH))
    for layer in layers:drawlayer(canvas,images,layer)
    if head:
     hl,hanchors=hacts[ai][min(fi,len(hacts[ai])-1)];ox=oy=0
     if anchors and hanchors:ox=anchors[0][0]-hanchors[0][0];oy=anchors[0][1]-hanchors[0][1]
     for layer in hl:drawlayer(canvas,heads,layer,ox,oy)
    data=canvas.tobytes();index=lookup.get(data)
    if index is None:index=len(frames);lookup[data]=index;frames.append(data)
    sequence.append(index)
    if fi==0 and direction==0:preview.append(canvas)
   meta.append((start,len(sequence)-start,max(20,int(delays[ai]*len(acts[ai])/(len(sequence)-start)))))
 # Sparse frame storage preserves the original 128x128 canvas/anchors.
 directory=[];pixels=bytearray()
 for data in frames:
  im=Image.frombytes('RGBA',(128,canvasH),data);bbox=im.getbbox()
  if not bbox:directory.append((0,0,0,0,len(pixels)));continue
  x0,y0,x1,y1=bbox;a=np.array(im.crop(bbox),dtype=np.uint32);argb=((a[:,:,3]>=128).astype(np.uint32)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3)
  directory.append((x0,y0,x1-x0,y1-y0,len(pixels)));pixels+=argb.astype('<u2').tobytes()
 raw=bytearray(struct.pack('<8I',128,canvasH,len(frames),len(meta),len(sequence),64,anchor,len(pixels)|0x80000000))
 for m in meta:raw+=struct.pack('<III',*m)
 raw+=np.array(sequence,dtype='<u4').tobytes()
 for entry in directory:raw+=struct.pack('<5I',*entry)
 raw+=pixels
 (out/(name+'.bin')).write_bytes(raw)
 im=Image.new('RGBA',(128*len(preview),canvasH),(45,65,50,255))
 for i,frame in enumerate(preview):im.alpha_composite(frame,(i*128,0))
 im.save(root/(name+'-preview.png'))
 print(name,'unique',len(frames),'sequence',len(sequence),'RAM MB',round(len(raw)/1048576,2),flush=True)
 return raw

