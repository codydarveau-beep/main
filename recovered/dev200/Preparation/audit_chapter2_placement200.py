"""Candidate staging audit against current packed collision/height/prop records.
Does not activate a scene. Render review and native controller acceptance remain separate.
"""
from pathlib import Path
import re,struct,zlib,collections,json,math
R=Path('/workspace/myro/dev200');text=(R/'Source/world_data.h').read_text();part=re.search(r'worldBlobs\[WORLD_MAP_COUNT\]\[7\]=\{(.+?)\};',text,re.S)[1];blobs=[tuple(map(int,v))for v in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',part)];names=re.findall(r'"([^"]+)"',re.search(r'mapNames\[\]=\{([^}]+)',text)[1])
class PackedStage:
 def __init__(self,name):
  self.name=name;self.id=names.index(name);b=self.load(1);self.w,self.h=struct.unpack_from('<II',b);self.walk=b[8:8+self.w*self.h];n=struct.unpack_from('<I',b,8+self.w*self.h)[0];self.surface={}
  for k in range(n):
   cell,*z=struct.unpack_from('<I4h',b,12+self.w*self.h+k*12);self.surface[cell]=[x/16 for x in z]
  at=12+self.w*self.h+n*12;self.props={struct.unpack_from('<I',b,at+4+k*8)[0]for k in range(struct.unpack_from('<I',b,at)[0])};self.geo=self.load(3);self.mw,self.mh,self.nv=struct.unpack_from('<III',self.geo);self.heightStart=12+(self.mw*self.mh+1)*4;self.npcs=[]
  for line in (R/'Source/npc_registry_data55.h').read_text().splitlines():
   m=re.match(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),.*?"([^"]+)"',line)
   if m and int(m[3])==self.id:self.npcs.append((int(m[4]),int(m[5]),m[6],int(m[2])))
 def load(self,section):
  at,n,raw,crc=blobs[self.id*7+section]
  with(R/'Packed/world.bin').open('rb')as f:f.seek(at);cp=f.read(n)
  assert zlib.crc32(cp)==crc;b=zlib.decompress(cp);assert len(b)==raw;return b
 def clear(self,x,y):return 0<=x<self.w and 0<=y<self.h and self.walk[y*self.w+x]==1 and y*self.w+x not in self.props
 def height(self,x,y):
  ix,iy=int(x//8),int(y//8);assert self.clear(ix,iy);cell=iy*self.w+ix
  if cell in self.surface:q=self.surface[cell];u=x/8-ix;v=y/8-iy
  else:ix,iy=int(x//16),int(y//16);q=struct.unpack_from('<4f',self.geo,self.heightStart+(iy*self.mw+ix)*16);u=x/16-ix;v=y/16-iy
  return q[0]+(q[1]-q[0])*u+(q[3]-q[1])*v if u>=v else q[0]+(q[3]-q[2])*u+(q[2]-q[0])*v
 def component(self,x,y):
  seed=(x//8,y//8);assert self.clear(*seed),seed;q=collections.deque([seed]);seen={seed}
  while q:
   a,b=q.popleft()
   for dx,dy in [(1,0),(-1,0),(0,1),(0,-1)]:
    p=a+dx,b+dy
    if p not in seen and self.clear(*p):seen.add(p);q.append(p)
  return seen
 def candidate(self,near,entry,offsets,radius=160):
  reachable=self.component(*entry);candidates=[]
  for cy in range(max(0,(near[1]-radius)//8),min(self.h,(near[1]+radius)//8)):
   for cx in range(max(0,(near[0]-radius)//8),min(self.w,(near[0]+radius)//8)):
    if(cx,cy)not in reachable:continue
    x,y=cx*8+4,cy*8+4;positions=[(x+dx,y+dy)for dx,dy in offsets]
    if not all((a//8,b//8)in reachable and all(self.clear(a//8+dx,b//8+dy)for dx,dy in [(0,0),(1,0),(-1,0),(0,1),(0,-1)])for a,b in positions):continue
    if any(math.hypot(a-nx,b-ny)<40 for a,b in positions for nx,ny,_,_ in self.npcs):continue
    z=[self.height(a,b)for a,b in positions]
    if max(z)-min(z)>4:continue
    candidates.append(((x-near[0])**2+(y-near[1])**2,x,y,z))
  assert candidates,('No clear staging footprint',self.name,near,entry)
  _,x,y,z=min(candidates);return dict(map=self.name,mapID=self.id,entry=list(entry),centre=[x,y],positions=[dict(x=x+dx,y=y+dy,height=h)for(dx,dy),h in zip(offsets,z)],reachableWithoutWarp=True,avoidsPropRecords=True,nativeNpcAndDoorClearance=40,rendered=False,enabled=False)
if __name__=='__main__':
 plans=[('Payon investigation','pay_arche',(340,1004),(652,180),[(-16,0),(16,0),(0,24)],240),('Alberta warehouse','alberta_in',(564,340),(596,356),[(-16,0),(16,0),(0,24)],120),('Alberta inn','alberta_in',(188,1132),(148,1132),[(-16,-16),(16,-16),(-16,16),(16,16)],80)]
 report={}
 for label,name,near,entry,offsets,radius in plans:
  report[label]=PackedStage(name).candidate(near,entry,offsets,radius)
 (R/'Preparation/Chapter2-Placement200.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
