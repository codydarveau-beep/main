"""Bake complete original 2D actions into independently compressed sparse frames.
Metadata stays small and frames can be cached without expanding whole species.
"""
from pathlib import Path
from concurrent.futures import ProcessPoolExecutor
import csv,hashlib,json,math,struct,time,zlib
import numpy as np
from PIL import Image
import ro_sprite_bake as ro
from world_assets51 import WorldAssets51
ROOT=Path(__file__).resolve().parent.parent;LIB=ROOT.parent/'asset-library/Test51-world-maps'

def spr51(b):
 r=ro.Reader(b);assert r.take(4)==b'SP\x01\x02';count,rgba=r.unpack('HH');palette=np.frombuffer(b[-1024:],np.uint8).reshape(256,4).copy();palette[:,3]=255;palette[0,3]=0;images=[]
 for _ in range(count):
  w,h,n=r.unpack('HHH');enc=r.take(n);raw=bytearray();i=0
  while i<len(enc):
   v=enc[i];i+=1
   if v:raw.append(v)
   else:n=enc[i];i+=1;raw.extend(bytes(n if n else 2))
  assert len(raw)==w*h;images.append(Image.fromarray(palette[np.frombuffer(raw,np.uint8).reshape(h,w)],'RGBA'))
 for _ in range(rgba):
  w,h=r.unpack('HH');a=np.frombuffer(r.take(w*h*4),np.uint8).reshape(h,w,4);images.append(Image.fromarray(a[::-1,:,::-1].copy(),'RGBA'))
 assert r.p==len(b)-1024;return images,count

def act51(b):
 r=ro.Reader(b);assert r.take(2)==b'AC';minor,major,n=r.unpack('BBH');v=major*10+minor;r.take(10);actions=[]
 for _ in range(n):
  frames=[]
  for _ in range(r.one('I')):
   r.take(32);layers=[]
   for _ in range(r.one('I')):
    x,y,index,mirror=r.unpack('4i');color=r.unpack('4B');xs=r.one('f');ys=r.one('f')if v>23 else xs;angle,kind=r.unpack('ii')
    if v>=25:r.take(8)
    layers.append((x,y,index,mirror,color,xs,ys,angle,kind))
   sound=r.one('i');anchors=[r.unpack('4i')for _ in range(r.one('I'))]if v>=23 else[];frames.append((layers,sound))
  actions.append(frames)
 ns=r.one('I');sounds=[r.take(40).split(b'\0')[0].decode('cp949')for _ in range(ns)];delays=[r.one('f')*25 for _ in range(n)]if v>=22 else[150]*n
 assert r.p==len(b);return actions,delays,sounds

def transformed(images,indexed,layer):
 x,y,index,mirror,color,xs,ys,angle,kind=layer
 if index<0:return None
 if kind:index+=indexed
 assert index<len(images),(index,len(images),kind)
 image=images[index].copy()
 if mirror:image=image.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
 if xs<0:image=image.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
 if ys<0:image=image.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
 if xs!=1 or ys!=1:image=image.resize((max(1,round(image.width*abs(xs))),max(1,round(image.height*abs(ys)))),Image.Resampling.NEAREST)
 if angle:image=image.rotate(-angle,expand=True)
 if color!=(255,255,255,255):image=Image.fromarray((np.array(image,dtype=np.uint16)*np.array(color,dtype=np.uint16)//255).astype(np.uint8),'RGBA')
 left=round(x-image.width/2);top=round(y-image.height/2);box=image.getbbox()
 if not box:return None
 return image.crop(box),left+box[0],top+box[1]

def bake(prefix):
 key=hashlib.sha256(prefix.encode()).hexdigest()[:16];out=ROOT/'CreatureAssets51'/key;out.mkdir(parents=True,exist_ok=True)
 if(out/'REPORT.json').exists():return json.loads((out/'REPORT.json').read_text())
 start=time.monotonic();a=WorldAssets51(LIB/'Asset-Index.json',8*1024*1024);images,indexed=spr51(a[prefix+'.spr']);acts,delays,sounds=act51(a[prefix+'.act']);frames=[];lookup={};sequence=[];meta=[];source=[];lo=np.array([0,0]);hi=np.array([1,87]);partial=False
 for group in range(5):
  for direction in range(8):
   action=group*8+direction
   if action>=len(acts):action=direction%len(acts)
   begin=len(sequence)
   poses=acts[action]or[([], -1)]
   for layers,sound in poses:
    parts=[p for layer in layers if(p:=transformed(images,indexed,layer))is not None]
    if parts:
     x=min(p[1]for p in parts);y=min(p[2]for p in parts);right=max(p[1]+p[0].width for p in parts);bottom=max(p[2]+p[0].height for p in parts);canvas=Image.new('RGBA',(right-x,bottom-y))
     for im,px,py in parts:canvas.alpha_composite(im,(px-x,py-y))
     box=canvas.getbbox()
     if box:canvas=canvas.crop(box);x+=box[0];y+=box[1]
     else:canvas=Image.new('RGBA',(1,1));x=y=0
    else:canvas=Image.new('RGBA',(1,1));x=y=0
    data=canvas.tobytes();signature=(x,y,canvas.size,hashlib.sha256(data).digest());index=lookup.get(signature)
    if index is None:
     index=len(frames);lookup[signature]=index;frames.append((x,y,canvas));lo=np.minimum(lo,[x,y]);hi=np.maximum(hi,[x+canvas.width,y+canvas.height]);alpha=np.array(canvas.getchannel('A'));partial|=bool(((alpha>0)&(alpha<255)).any())
    sequence.append(index);source.append((group,direction,sound))
   meta.append((begin,len(sequence)-begin,max(20,round(delays[action]))))
 lo-=2;hi+=2;width=1<<(int(hi[0]-lo[0])-1).bit_length();height=1<<(int(hi[1]-lo[1])-1).bit_length();width=max(128,width);height=max(128,height)
 assert width<=1024 and height<=1024,(prefix,width,height)
 assert len(frames)<=8192 and len(sequence)<=32768,(prefix,len(frames),len(sequence))
 directory=[];blocks=[];payload=bytearray();pixelbytes=0
 for x,y,im in frames:
  ar=np.array(im,dtype=np.uint16)
  if partial:v=((ar[:,:,3]>>4)<<12)|((ar[:,:,0]>>4)<<8)|((ar[:,:,1]>>4)<<4)|(ar[:,:,2]>>4)
  else:v=((ar[:,:,3]>=128).astype(np.uint16)<<15)|((ar[:,:,0]>>3)<<10)|((ar[:,:,1]>>3)<<5)|(ar[:,:,2]>>3)
  raw=v.astype('<u2').tobytes();cp=zlib.compress(raw,6);directory.append((x-int(lo[0]),y-int(lo[1]),im.width,im.height,pixelbytes));pixelbytes+=len(raw);blocks.append((len(payload),len(cp),len(raw),zlib.crc32(cp)));payload.extend(cp)
 metadata=struct.pack('<8I',width,height,len(frames),len(meta),len(sequence),-int(lo[0]),86-int(lo[1]),pixelbytes|(0xc0000000 if partial else 0x80000000))
 metadata+=b''.join(struct.pack('<3I',*m)for m in meta)+np.asarray(sequence,dtype='<u4').tobytes()+b''.join(struct.pack('<5I',*d)for d in directory)+b''.join(struct.pack('<4I',*d)for d in blocks)
 packed=zlib.compress(metadata,6);(out/'meta.z').write_bytes(packed);(out/'frames.bin').write_bytes(payload)
 report=dict(prefix=prefix,key=key,width=width,height=height,frames=len(frames),sequence=len(sequence),metadata_raw=len(metadata),metadata_packed=len(packed),metadata_crc=zlib.crc32(packed),frame_bytes=len(payload),virtual_pixel_bytes=pixelbytes,alpha4444=partial,sounds=sounds,death_sounds=list(dict.fromkeys(sounds[s]for group,dir,s in source if group==4 and 0<=s<len(sounds))),seconds=round(time.monotonic()-start,3),sprSHA=hashlib.sha256(a[prefix+'.spr']).hexdigest(),actSHA=hashlib.sha256(a[prefix+'.act']).hexdigest())
 (out/'REPORT.json').write_text(json.dumps(report,indent=2,ensure_ascii=False));return report

def main():
 # Preserve all original50 species byte-for-byte; prepare only new source bodies.
 oldtext=(ROOT.parent/'test50c/Source/encounter_data.h').read_text();section=oldtext[oldtext.index('mobSpecs'):oldtext.index('typedef struct {unsigned map')];oldids={json.loads('['+r+']')[10]for r in __import__('re').findall(r'\{([^{}]+)\}',section)if r.startswith('"')}
 prefixes=sorted({r[2].replace('\\','/').lower()for r in csv.reader((ROOT.parent/'asset-request51/World-Maps/Monster-Requests.tsv').open(encoding='utf-8-sig'),delimiter='\t')if int(r[1])not in oldids})
 reports=[]
 with ProcessPoolExecutor(max_workers=4)as pool:
  for r in pool.map(bake,prefixes):reports.append(r);print(len(reports),len(prefixes),r['prefix'],r['width'],r['height'],r['frames'],flush=True)
 (ROOT/'ENEMY-ART51.json').write_text(json.dumps(reports,indent=2,ensure_ascii=False));print('PASS',len(reports),'original bodies, full source actions')
if __name__=='__main__':main()
