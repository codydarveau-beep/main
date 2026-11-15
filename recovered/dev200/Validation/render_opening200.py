"""Host reference staging render. Actual packed mesh/atlas and source actor poses.
Affine camera/depth equations match projection.h; this is not an Xbox screenshot.
"""
from pathlib import Path
import sys,struct,json,math,re,zlib
import numpy as np
from PIL import Image,ImageDraw
DX=float(sys.argv[1])if len(sys.argv)>1 else 0;DY=float(sys.argv[2])if len(sys.argv)>2 else 0
R=Path('/workspace/myro/dev200');sys.path.insert(0,str(R/'Preparation'));import audit_opening_height200 as world

def atlas(section,rgb=False):
 b=world.load(section);w,h=struct.unpack_from('<II',b);v=np.frombuffer(b,dtype='<u2',offset=8).reshape(h,w).astype(np.uint32)
 if rgb:out=np.stack([((v>>11)&31)*255//31,((v>>5)&63)*255//63,(v&31)*255//31,np.where(((v>>11)>=29)&(((v>>5)&63)<5)&((v&31)>=29),0,255)],axis=-1)
 else:out=np.stack([((v>>10)&31)*255//31,((v>>5)&31)*255//31,(v&31)*255//31,(v>>15)*255],axis=-1)
 return out.astype(np.uint8)
groundTex=atlas(0,True);sceneTex=atlas(4);b=world.load(3);w,h,n=struct.unpack_from('<III',b);ground=np.frombuffer(b,dtype='<f4',offset=12+(w*h+1)*4+w*h*16).reshape(-1,5);b=world.load(5);scenery=np.frombuffer(b,dtype='<f4',offset=4).reshape(-1,5);b=world.load(6);models,n0,n1=struct.unpack_from('<III',b);model=np.frombuffer(b,dtype='<u4',offset=12,count=models*2).reshape(-1,2);instances=[]
for i in range(n0):
 at=12+models*8+i*76;idx=struct.unpack_from('<I',b,at)[0];mat=np.frombuffer(b,dtype='<f4',offset=at+4,count=12).reshape(3,4);bounds=np.frombuffer(b,dtype='<f4',offset=at+52,count=6)
 if bounds[0]<1600 and bounds[3]>1100 and bounds[1]<3100 and bounds[4]>2600:
  start,count=model[idx];v=scenery[start:start+count].copy();v[:,:3]=v[:,:3]@mat[:,:3].T+mat[:,3];instances.append(v)
scenery=np.concatenate(instances)
header=(R/'Source/campaign_actor_data200.h').read_text();first=header.split('campaignFrames200[]={')[1].split('};')[0];frames=[tuple(map(int,v))for v in re.findall(r'\{(\d+)u,(\d+)u,(\d+)u,(\d+)u\}',first)];first=header.split('campaignActions200[]={')[1].split('};')[0];actions=[tuple(map(int,v))for v in re.findall(r'\{(\d+)u,(\d+)u,(\d+)u\}',first)];contacts=json.loads(re.split(r'campaignContact200\[\d+\]\[8\]\[2\]=',header)[1].split(';')[0].replace('{','[').replace('}',']'));actorbin=(R/'Campaign/actors.bin').read_bytes();positions=[(1452,2820),(1436,2788),(1476,2820),(1468,2780)];positions=[(x+DX,y+DY)for x,y in positions];names=['Nera','Roan','Yuufa','Driver']

def camera(yaw,zoom):
 co,si=math.cos(yaw),math.sin(yaw);ct,sn=math.cos(.825),math.sin(.825);x,y=1460+DX,2804+DY;z=world.height(x,y)
 return np.array([[zoom*co,zoom*si,0,320-zoom*(co*x+si*y)],[zoom*ct*si,-zoom*ct*co,-zoom*sn,245-zoom*ct*(si*x-co*y)+zoom*sn*z],[-2048*sn*si,2048*sn*co,-2048*ct,8388608+2048*sn*si*x-2048*sn*co*y+2048*ct*z]])
def triangles(v,tex,m,img,depth):
 p=np.concatenate([v[:,:3]@m[:,:3].T+m[:,3],v[:,3:]],axis=1).reshape(-1,3,5);lo=p[:,:,:2].min(1);hi=p[:,:,:2].max(1);p=p[(lo[:,0]<640)&(hi[:,0]>=0)&(lo[:,1]<480)&(hi[:,1]>=0)]
 for t in p:
  x0=max(0,int(math.floor(t[:,0].min())));x1=min(640,int(math.ceil(t[:,0].max())));y0=max(0,int(math.floor(t[:,1].min())));y1=min(480,int(math.ceil(t[:,1].max())))
  if x0>=x1 or y0>=y1:continue
  a,b,c=t;den=(b[1]-c[1])*(a[0]-c[0])+(c[0]-b[0])*(a[1]-c[1])
  if abs(den)<1e-7:continue
  yy,xx=np.mgrid[y0:y1,x0:x1];xx=xx+.5;yy=yy+.5;u=((b[1]-c[1])*(xx-c[0])+(c[0]-b[0])*(yy-c[1]))/den;v=((c[1]-a[1])*(xx-c[0])+(a[0]-c[0])*(yy-c[1]))/den;w=1-u-v;z=u*a[2]+v*b[2]+w*c[2];tx=np.clip((u*a[3]+v*b[3]+w*c[3]).astype(int),0,tex.shape[1]-1);ty=np.clip((u*a[4]+v*b[4]+w*c[4]).astype(int),0,tex.shape[0]-1);col=tex[ty,tx];mask=(u>=0)&(v>=0)&(w>=0)&(z<=depth[y0:y1,x0:x1])&(col[:,:,3]>=128);img[y0:y1,x0:x1][mask]=col[mask];depth[y0:y1,x0:x1][mask]=z[mask]
 return len(p)
for yawIndex in range(8):
 yaw=yawIndex*math.pi/4;zoom=2.5;m=camera(yaw,zoom);img=np.zeros((480,640,4),dtype=np.uint8);img[:,:,3]=255;depth=np.full((480,640),np.inf);ng=triangles(ground,groundTex,m,img,depth);ns=triangles(scenery,sceneTex,m,img,depth);labels=[]
 for i,(x,y)in enumerate(positions):
  fx,fy=1468+DX-x,2780+DY-y
  if i==3:fx,fy=0,-1
  sx=math.cos(yaw)*fx+math.sin(yaw)*fy;sy=math.sin(yaw)*fx-math.cos(yaw)*fy;direction=(int(math.floor(math.atan2(-sx,sy)*4/math.pi+.5))+8)%8;idx=actions[i*48+direction][0];at,packed,raw,crc=frames[idx];cp=actorbin[at:at+packed];assert zlib.crc32(cp)==crc;b=zlib.decompress(cp);assert len(b)==raw;cx,cy,cw,ch,_=struct.unpack_from('<5I',b,516);v=np.frombuffer(b,dtype='<u2',offset=536).reshape(ch,cw).astype(np.uint32);color=np.stack([((v>>10)&31)*255//31,((v>>5)&31)*255//31,(v&31)*255//31,(v>>15)*255],axis=-1).astype(np.uint8);pose=np.zeros((128,128,4),np.uint8);pose[cy:cy+ch,cx:cx+cw]=color;scale=zoom/3;pose=np.array(Image.fromarray(pose).resize((round(128*scale),round(128*scale)),Image.Resampling.NEAREST));p=m[:,:3]@np.array([x,y,world.height(x,y)])+m[:,3];left=round(p[0]+contacts[i][direction][0]*scale-64*scale);top=round(p[1]+contacts[i][direction][1]*scale-90*scale);h,w=pose.shape[:2];assert left>=0 and top>=0 and left+w<=640 and top+h<=480;yy=np.arange(top,top+h)[:,None]+.5;z=p[2]-256+(yy-p[1])*(m[2,2]/m[1,2]);mask=(pose[:,:,3]>=128)&(z<=depth[top:top+h,left:left+w]);img[top:top+h,left:left+w][mask]=pose[mask];labels.append((left+32,top-10,names[i]));assert mask.sum()>100,(names[i],yawIndex,'scenery obscures staging',DX,DY)
 im=Image.fromarray(img);d=ImageDraw.Draw(im);d.rectangle((0,0,640,18),fill='black');d.text((4,3),f'HOST staging reference, yaw {yawIndex*45}; native packed ground/scenery/actor art',fill='white');
 for x,y,name in labels:d.text((x,y),name,fill='white',stroke_width=1,stroke_fill='black')
 im.save(R/'Validation'/f'opening-stage-{yawIndex}200.png');print('Rendered yaw',yawIndex*45,ng,'ground triangles',ns,'scenery triangles')
