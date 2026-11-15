"""Collision, exact standing heights and interaction-clearance proof for scene1.1."""
from pathlib import Path
import re,json,struct,zlib,math
R=Path('/workspace/myro/dev200');text=(R/'Source/world_data.h').read_text();part=re.search(r'worldBlobs\[WORLD_MAP_COUNT\]\[7\]=\{(.+?)\};',text,re.S)[1];blobs=[tuple(map(int,v))for v in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',part)]
def load(section):
 at,n,raw,crc=blobs[section]
 with(R/'Packed/world.bin').open('rb')as f:f.seek(at);cp=f.read(n)
 assert zlib.crc32(cp)==crc;b=zlib.decompress(cp);assert len(b)==raw;return b
b=load(1);gw,gh=struct.unpack_from('<II',b);walk=b[8:8+gw*gh];n=struct.unpack_from('<I',b,8+gw*gh)[0];surface={}
for k in range(n):
 cell,*z=struct.unpack_from('<I4h',b,12+gw*gh+k*12);surface[cell]=[x/16 for x in z]
at=12+gw*gh+n*12;props={struct.unpack_from('<I',b,at+4+k*8)[0]for k in range(struct.unpack_from('<I',b,at)[0])};geo=load(3);mw,mh,nv=struct.unpack_from('<III',geo);heightStart=12+(mw*mh+1)*4

def height(x,y):
 ix,iy=int(x//8),int(y//8);cell=iy*gw+ix
 assert walk[cell]and cell not in props,(x,y,'blocked')
 if cell in surface:q=surface[cell];u=x/8-ix;v=y/8-iy
 else:
  ix,iy=int(x//16),int(y//16);q=struct.unpack_from('<4f',geo,heightStart+(iy*mw+ix)*16);u=x/16-ix;v=y/16-iy
 return q[0]+(q[1]-q[0])*u+(q[3]-q[1])*v if u>=v else q[0]+(q[3]-q[2])*u+(q[2]-q[0])*v
positions={'Nera':[1452,2820],'Roan':[1436,2788],'Yuufa':[1476,2820],'Driver':[1468,2780],'Safe driver':[1468,2812],'Parcel':[1484,2788],'Poring1':[1436,2780],'Poring2':[1484,2780],'Stalled cart':[1460,2772]}
proof={name:{'x':p[0],'y':p[1],'height':height(*p)}for name,p in positions.items()};path=[[1468,2780+i*2]for i in range(17)];z=[height(*p)for p in path];assert max(abs(a-b)for a,b in zip(z,z[1:]))<4
nearNPC=[]
for line in (R/'Source/npc_registry_data55.h').read_text().splitlines():
 m=re.match(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),',line)
 if m and int(m[3])==0:
  x,y=int(m[4]),int(m[5]);distance=min(math.hypot(x-p[0],y-p[1])for p in positions.values())
  if distance<80:nearNPC.append({'record':int(m[1])-1,'x':x,'y':y,'nearestDistance':round(distance,2)})
assert not nearNPC,nearNPC
result={'map':'prt_fild08','mapID':0,'positions':proof,'escortPath':path,'escortHeightRange':[min(z),max(z)],'maxStepOver2Units':max(abs(a-b)for a,b in zip(z,z[1:])),'nearbyNativeNPCsWithin80Units':nearNPC,'sourceCollisionAndGroundValidated':True,'activated':False,'remaining':['rendered scenery/prop clearance','actual scene actor silhouettes','controller encounter playthrough']};(R/'Preparation/Opening-Heights200.json').write_text(json.dumps(result,indent=2)+'\n');print('PASS9 actor/object/encounter positions and17 escort path samples, exact native standing heights; max escort step',result['maxStepOver2Units'],'and no nearby native NPC interaction conflicts.')
