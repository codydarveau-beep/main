"""Bake accepted Test47 body-height solid cross-sections for each new map.
Terrain and source GAT cells remain intact; only closed opaque model volumes
contribute extra 2-unit prop occupancy. Source portal routes take priority.
"""
from pathlib import Path
import csv,json,re,struct,time
from concurrent.futures import ProcessPoolExecutor
import numpy as np
from prop_routes46 import protect_routes46
ROOT=Path(__file__).resolve().parent.parent
LIB=ROOT.parent/'asset-library/Test51-map-inventory/metadata'

def map_names51():
 old=re.findall(r'"([^"]+)"',re.search(r'mapNames\[\]=\{(.*?)\}',(ROOT.parent/'test50c/Source/world_data.h').read_text())[1])
 new=[r[1] for r in csv.reader((ROOT.parent/'asset-library/Test51-world-maps/Map-Requests.tsv').open(encoding='utf-8-sig'),delimiter='\t')]
 return list(dict.fromkeys(old+new))

def source_gates51(names):
 ids={n:i for i,n in enumerate(names)};gates=[];seen=set()
 # Original 18-map gates contain previously accepted endpoint corrections.
 text=(ROOT.parent/'test50c/Source/world_data.h').read_text();prior=re.search(r'worldGates\[\]=\{(.*?)\};',text,re.S)[1]
 for row in re.findall(r'\{([^{}]+)\}',prior):
  v=tuple(map(int,row.split(',')));gates.append(v);seen.add(v)
 for row in csv.DictReader((LIB/'Warp-Records.csv').open(encoding='utf-8-sig')):
  src,dst=row['source_map'],row['destination_map']
  if src not in ids or dst not in ids:continue
  if ids[src]<18 and ids[dst]<18:continue
  value=(ids[src],int(row['x'])*8+4,int(row['y'])*8+4,max(1,int(row['width']))*8+8,max(1,int(row['height']))*8+8,ids[dst],int(row['destination_x'])*8+4,int(row['destination_y'])*8+4)
  if value not in seen:gates.append(value);seen.add(value)
 return gates

def bake(args):
 name,mapid,gates=args;out=ROOT/'WorldAssets'/name
 if (out/'CLEARANCE51.json').exists():return json.loads((out/'CLEARANCE51.json').read_text())
 started=time.monotonic();geometry=(out/'geometry.bin').read_bytes();mw,mh,n=struct.unpack_from('<III',geometry)
 height=np.frombuffer(geometry,dtype='<f4',offset=12+(mw*mh+1)*4,count=mw*mh*4).reshape(mh,mw,4)
 collision=(out/'surfaces.bin').read_bytes();gw,gh=struct.unpack_from('<II',collision);walk=np.frombuffer(collision,dtype='u1',offset=8,count=gw*gh).reshape(gh,gw)
 ns=struct.unpack_from('<I',collision,8+gw*gh)[0];special={struct.unpack_from('<I',collision,12+gw*gh+i*12)[0]for i in range(ns)}
 def ground(xyz):
  xx=xyz[:,0]/16;yy=xyz[:,1]/16;ix=np.clip(xx.astype(int),0,mw-1);iy=np.clip(yy.astype(int),0,mh-1);fx=xx-ix;fy=yy-iy;h=height[iy,ix]
  return np.where(fx>fy,h[:,0]+(h[:,1]-h[:,0])*fx+(h[:,3]-h[:,1])*fy,h[:,0]+(h[:,3]-h[:,2])*fx+(h[:,2]-h[:,0])*fy)
 raw=(out/'SceneryAssets/mesh.bin').read_bytes();sv=np.frombuffer(raw,dtype='<f4',offset=4).reshape(-1,5)
 meta=(out/'SceneryAssets/instances.bin').read_bytes();nm,n0,n1=struct.unpack_from('<III',meta);models=np.frombuffer(meta,dtype='<u4',offset=12,count=nm*2).reshape(nm,2)
 atlas=(out/'SceneryAssets/atlas.bin').read_bytes();aw,ah=struct.unpack_from('<II',atlas);ap=np.frombuffer(atlas,dtype='<u2',offset=8).reshape(ah,aw)
 occupied={};sections=0
 for i in range(n0+n1):
  q=struct.unpack_from('<I18f',meta,12+nm*8+i*76);mid=q[0];mat=np.array(q[1:13]).reshape(3,4);st,ct=models[mid];v=sv[st:st+ct];xyz=v[:,:3]@mat[:,:3].T+mat[:,3]
  if np.ptp(xyz[:,2])<24:continue
  d=(xyz[:,2]-ground(xyz)-32).reshape(-1,3);t=xyz.reshape(-1,3,3);uv=v[:,3:].reshape(-1,3,2);segments=[]
  # Batch all triangle/edge intersections; each non-degenerate slice has two.
  crossing=np.zeros((len(t),3),bool);points=np.zeros((len(t),3,2));texcoords=np.zeros((len(t),3,2))
  for edge,(a,b) in enumerate(((0,1),(1,2),(2,0))):
   mask=((d[:,a]<0)!=(d[:,b]<0))&(np.abs(d[:,a]-d[:,b])>=1e-7);crossing[:,edge]=mask
   f=np.divide(d[:,a],d[:,a]-d[:,b],out=np.zeros(len(t)),where=mask)
   points[:,edge]=t[:,a,:2]+(t[:,b,:2]-t[:,a,:2])*f[:,None];texcoords[:,edge]=uv[:,a]+(uv[:,b]-uv[:,a])*f[:,None]
  selected=np.flatnonzero(crossing.sum(1)==2)
  if not len(selected):continue
  idx=np.argsort(~crossing[selected],axis=1,kind='stable')[:,:2];p=points[selected[:,None],idx];u=texcoords[selected[:,None],idx]
  opaque=np.ones(len(p),bool)
  for f in (.2,.5,.8):
   sample=u[:,0]*(1-f)+u[:,1]*f;tx=np.clip(sample[:,0].astype(int),0,aw-1);ty=np.clip(sample[:,1].astype(int),0,ah-1);opaque&=(ap[ty,tx]&32768)!=0
  p=p[opaque&(np.linalg.norm(p[:,1]-p[:,0],axis=1)>1e-5)]
  if not len(p):continue
  sections+=1;a=p[:,0];b=p[:,1];lo=np.floor(p.min(axis=(0,1))/2).astype(int);hi=np.ceil(p.max(axis=(0,1))/2).astype(int)
  for sy in range(max(0,lo[1]-1),min(gh*4,hi[1]+2)):
   y=sy*2+1;cross=(a[:,1]>y)!=(b[:,1]>y)
   xs=np.sort(a[cross,0]+(b[cross,0]-a[cross,0])*(y-a[cross,1])/(b[cross,1]-a[cross,1]))
   if len(xs)%2:continue
   for x0,x1 in xs.reshape(-1,2):
    for sx in range(max(0,int(np.ceil((x0-1)/2))),min(gw*4-1,int(np.floor((x1-1)/2)))+1):
     cx,cy=sx//4,sy//4;cell=cy*gw+cx
     if walk[cy,cx] and cell not in special:occupied[cell]=occupied.get(cell,0)|(1<<((sy%4)*4+sx%4))
 gate_text=''.join('{'+','.join(map(str,g))+'}' for g in gates if g[0]==mapid)
 protected=protect_routes46(occupied,walk,(out/'spawn.bin').read_bytes(),gate_text,mapid)
 payload=struct.pack('<I',len(occupied))+b''.join(struct.pack('<IHH',cell,bits,0) for cell,bits in sorted(occupied.items()))
 (out/'collision.bin').write_bytes(collision+payload)
 report=dict(map=name,mapid=mapid,solid_sections=sections,prop_cells=len(occupied),protected_route_cells=protected,extra_ram=len(payload),seconds=round(time.monotonic()-started,3),removed_terrain_triangles=0)
 (out/'CLEARANCE51.json').write_text(json.dumps(report,indent=2));return report

def main():
 names=map_names51();gates=source_gates51(names);(ROOT/'WORLD-GATES51.json').write_text(json.dumps(gates))
 todo=[(n,i,gates)for i,n in enumerate(names)if i>=18]
 reports=[]
 with ProcessPoolExecutor(max_workers=4)as pool:
  for r in pool.map(bake,todo):
   reports.append(r);print(len(reports),len(todo),r['map'],r['prop_cells'],r['seconds'],flush=True)
 (ROOT/'CLEARANCE51.json').write_text(json.dumps(reports,indent=2));print('PASS',len(reports),'maps, original terrain intact')
if __name__=='__main__':main()
