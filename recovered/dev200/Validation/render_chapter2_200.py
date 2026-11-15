"""Host reference staging: real packed meshes/atlases/poses and projection equations.
No game camera changes; no original-Xbox screenshot claim.
"""
from pathlib import Path
import ast,sys,struct,json,math,re,zlib,hashlib
import numpy as np
from PIL import Image,ImageDraw
R=Path('/workspace/myro/dev200');sys.path.insert(0,str(R/'Preparation'));from audit_chapter2_placement200 import PackedStage
plans=json.loads((R/'Preparation/Chapter2-Placement200.json').read_text());header=(R/'Source/campaign_actor_data200.h').read_text();first=header.split('campaignFrames200[]={')[1].split('};')[0];frames=[tuple(map(int,v))for v in re.findall(r'\{(\d+)u,(\d+)u,(\d+)u,(\d+)u\}',first)];first=header.split('campaignActions200[]={')[1].split('};')[0];actions=[tuple(map(int,v))for v in re.findall(r'\{(\d+)u,(\d+)u,(\d+)u\}',first)];contacts=json.loads(re.split(r'campaignContact200\[\d+\]\[8\]\[2\]=',header)[1].split(';')[0].replace('{','[').replace('}',']'));actorbin=(R/'Campaign/actors.bin').read_bytes()
code=ast.parse((R/'Validation/render_opening200.py').read_text());ns=dict(np=np,math=math,struct=struct);exec(compile(ast.Module(body=[n for n in code.body if isinstance(n,ast.FunctionDef)and n.name in ['atlas','triangles']],type_ignores=[]),'source-staging-render','exec'),ns);triangles=ns['triangles']
actorsByScene={'Payon investigation':[(0,'Nera'),(4,'Judia')],'Alberta warehouse':[(5,'Maya'),(6,'Veyr')],'Alberta inn':[(1,'Roan'),(2,'Yuufa'),(4,'Judia'),(5,'Maya')]};report={};outDir=R/'Validation/Chapter2-Staging200';outDir.mkdir(exist_ok=True)
for label,plan in plans.items():
 world=PackedStage(plan['map']);ns['world']=world;groundTex=ns['atlas'](0,True);sceneTex=ns['atlas'](4);b=world.load(3);w,h,n=struct.unpack_from('<III',b);ground=np.frombuffer(b,dtype='<f4',offset=12+(w*h+1)*4+w*h*16).reshape(-1,5);b=world.load(5);sceneVertices=np.frombuffer(b,dtype='<f4',offset=4).reshape(-1,5);b=world.load(6);models,n0,n1=struct.unpack_from('<III',b);model=np.frombuffer(b,dtype='<u4',offset=12,count=models*2).reshape(-1,2);scenery=[];cx,cy=plan['centre']
 for i in range(n0+n1):
  at=12+models*8+i*76;idx=struct.unpack_from('<I',b,at)[0];mat=np.frombuffer(b,dtype='<f4',offset=at+4,count=12).reshape(3,4);bounds=np.frombuffer(b,dtype='<f4',offset=at+52,count=6)
  if bounds[0]<cx+320 and bounds[3]>cx-320 and bounds[1]<cy+320 and bounds[4]>cy-320:
   start,count=model[idx];v=sceneVertices[start:start+count].copy();v[:,:3]=v[:,:3]@mat[:,:3].T+mat[:,3];scenery.append(v)
 scenery=np.concatenate(scenery)if scenery else np.empty((0,5));angles=[]
 for yawIndex in range(8):
  yaw=yawIndex*math.pi/4;zoom=2.5;co,si=math.cos(yaw),math.sin(yaw);ct,sn=math.cos(.825),math.sin(.825);cz=world.height(cx,cy);m=np.array([[zoom*co,zoom*si,0,320-zoom*(co*cx+si*cy)],[zoom*ct*si,-zoom*ct*co,-zoom*sn,245-zoom*ct*(si*cx-co*cy)+zoom*sn*cz],[-2048*sn*si,2048*sn*co,-2048*ct,8388608+2048*sn*si*cx-2048*sn*co*cy+2048*ct*cz]])
  img=np.zeros((480,640,4),np.uint8);img[:,:,3]=255;depth=np.full((480,640),np.inf);ng=triangles(ground,groundTex,m,img,depth);nscene=triangles(scenery,sceneTex,m,img,depth);visible=[];labels=[]
  for source,(sourceID,name)in enumerate(actorsByScene[label]):
   p=plan['positions'][source];x,y=p['x'],p['y'];fx,fy=cx-x,cy-y;sx=co*fx+si*fy;sy=si*fx-co*fy;direction=(int(math.floor(math.atan2(-sx,sy)*4/math.pi+.5))+8)%8;frame=actions[sourceID*48+direction][0];at,packed,raw,crc=frames[frame];cp=actorbin[at:at+packed];assert zlib.crc32(cp)==crc;b=zlib.decompress(cp);assert len(b)==raw;_,_,_,_,_,anchorX,anchorY,_=struct.unpack_from('<8I',b);ox,oy,cw,ch,_=struct.unpack_from('<5I',b,516);v=np.frombuffer(b,dtype='<u2',offset=536).reshape(ch,cw).astype(np.uint32);color=np.stack([((v>>10)&31)*255//31,((v>>5)&31)*255//31,(v&31)*255//31,(v>>15)*255],axis=-1).astype(np.uint8);pose=np.zeros((128,128,4),np.uint8);pose[oy:oy+ch,ox:ox+cw]=color;scale=zoom/3;pose=np.array(Image.fromarray(pose).resize((round(128*scale),round(128*scale)),Image.Resampling.NEAREST));p=m[:,:3]@np.array([x,y,world.height(x,y)])+m[:,3];left=round(p[0]+contacts[sourceID][direction][0]*scale-anchorX*scale);top=round(p[1]+contacts[sourceID][direction][1]*scale-anchorY*scale);ph,pw=pose.shape[:2];assert left>=0 and top>=0 and left+pw<=640 and top+ph<=480;yy=np.arange(top,top+ph)[:,None]+.5;z=p[2]-256+(yy-p[1])*(m[2,2]/m[1,2]);mask=(pose[:,:,3]>=128)&(z<=depth[top:top+ph,left:left+pw]);img[top:top+ph,left:left+pw][mask]=pose[mask];pixels=int(mask.sum());total=int((pose[:,:,3]>=128).sum());visible.append(dict(name=name,pixels=pixels,total=total));labels.append((left+32,top-12,name))
  im=Image.fromarray(img);d=ImageDraw.Draw(im);d.rectangle((0,0,640,19),fill='black');d.text((4,4),f'HOST reference: {label}; yaw{yawIndex*45}; all nearby scenery',fill='white')
  for x,y,name in labels:d.text((x,y),name,fill='white',stroke_width=1,stroke_fill='black')
  filename=label.lower().replace(' ','-')+f'-{yawIndex}.png';im.save(outDir/filename);angles.append(dict(yaw=yawIndex*45,actors=visible,image=filename,sha256=hashlib.sha256((outDir/filename).read_bytes()).hexdigest()));print(label,yawIndex*45,visible)
 report[label]=dict(map=world.name,mapID=world.id,angles=angles,allActorsVisibleAtLeast80Pixels=all(a['pixels']>=80 for angle in angles for a in angle['actors']),hardwareTested=False)
(R/'Preparation/Chapter2-Staging200.json').write_text(json.dumps(report,indent=2)+'\n')
assert all(p['allActorsVisibleAtLeast80Pixels']for p in report.values()),'Review/reposition occluded staging before enabling scenes.'
