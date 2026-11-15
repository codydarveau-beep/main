"""MIT. Restore full original terrain and bake body-level solid mesh cross-sections.
Reads immutable45a pack. Keeps the Test46 prefix, atlas and every accepted GAT height.
Only opaque geometry 32 units above the walk surface contributes; raised
walk surfaces are excluded so stairs/bridges retain their accepted traversal.
Sparse 2-unit occupancy is streamed in the existing current-map collision blob.
"""
from pathlib import Path
import struct,zlib,re,json
import numpy as np
from prop_routes46 import protect_routes46
root=Path(__file__).resolve().parent; base=root.parent.parent/'test45a'; src=(base/'Source/world_data.h').read_text(); data=(base/'Packed/world.bin').read_bytes(); rows=[list(map(int,x)) for x in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',src[:src.index('static const WorldBlob minimapBlobs45')])];assert len(rows)==126
out=bytearray((root.parent.parent/'test46/Packed/world.bin').read_bytes()); report=[]
def unpack(k,j):
 a,n,r,c=rows[k*7+j];v=zlib.decompress(data[a:a+n]);assert len(v)==r;return v
def append(k,j,b):
 v=zlib.compress(b,9);rows[k*7+j]=[len(out),len(v),len(b),zlib.crc32(v)];out.extend(v)
for k in range(18):
 tex=unpack(k,0);tw,th=struct.unpack_from('<II',tex);pixels=np.frombuffer(tex,dtype='<u2',offset=8).reshape(th,tw)
 mesh=unpack(k,3);mw,mh,n=struct.unpack_from('<III',mesh);starts=np.frombuffer(mesh,dtype='<u4',offset=12,count=mw*mh+1);offset=12+(mw*mh+1)*4;heights=np.frombuffer(mesh,dtype='<f4',offset=offset,count=mw*mh*4).reshape(mh,mw,4);vo=offset+mw*mh*16;verts=np.frombuffer(mesh,dtype='<f4',offset=vo).reshape(n,5);tri=verts.reshape(-1,3,5)
 # Test47 restores every original triangle; no terrain culling.
 keep=np.ones(len(tri),bool)
 collision=unpack(k,1);gw,gh=struct.unpack_from('<II',collision);walk=np.frombuffer(collision,dtype='u1',offset=8,count=gw*gh).reshape(gh,gw);ns=struct.unpack_from('<I',collision,8+gw*gh)[0];special=set(struct.unpack_from('<I',collision,12+gw*gh+i*12)[0] for i in range(ns))
 def ground(x,y):
  ix=min(max(int(x/16),0),mw-1);iy=min(max(int(y/16),0),mh-1);fx=x/16-ix;fy=y/16-iy;h=heights[iy,ix];return h[0]+(h[1]-h[0])*fx+(h[3]-h[1])*fy if fx>fy else h[0]+(h[3]-h[2])*fx+(h[2]-h[0])*fy
 sc=unpack(k,5);sv=np.frombuffer(sc,dtype='<f4',offset=4).reshape(-1,5);meta=unpack(k,6);nm,n0,n1=struct.unpack_from('<III',meta);models=np.frombuffer(meta,dtype='<u4',offset=12,count=nm*2).reshape(nm,2);atlas=unpack(k,4);aw,ah=struct.unpack_from('<II',atlas);ap=np.frombuffer(atlas,dtype='<u2',offset=8).reshape(ah,aw);occupied={};sections=0
 for ii in range(n0+n1):
  q=struct.unpack_from('<I18f',meta,12+nm*8+ii*76);mid=q[0];mat=np.array(q[1:13]).reshape(3,4);st,ct=models[mid];v=sv[st:st+ct];xyz=v[:,:3]@mat[:,:3].T+mat[:,3];
  if xyz[:,2].max()-xyz[:,2].min()<24:continue
  seg=[]
  for ids in range(0,len(v),3):
   t=xyz[ids:ids+3];uv=v[ids:ids+3,3:];d=np.array([a[2]-ground(a[0],a[1])-32 for a in t]);hit=[]
   for a,b in [(0,1),(1,2),(2,0)]:
    if (d[a]<0)==(d[b]<0) or abs(d[a]-d[b])<1e-7:continue
    f=d[a]/(d[a]-d[b]);hit.append((t[a]+(t[b]-t[a])*f,uv[a]+(uv[b]-uv[a])*f))
   if len(hit)!=2:continue
   # Cutout foliage and transparent texture margins are not solid geometry.
   if any(not(ap[min(ah-1,max(0,int((hit[0][1]*(1-f)+hit[1][1]*f)[1]))),min(aw-1,max(0,int((hit[0][1]*(1-f)+hit[1][1]*f)[0])))]&32768) for f in [.2,.5,.8]):continue
   a,b=hit[0][0][:2],hit[1][0][:2]
   if np.linalg.norm(b-a)>1e-5:seg.append((a,b))
  if not seg:continue
  extent=np.ptp(np.array([a for edge in seg for a in edge]),axis=0)
  # Opaque closed bases include stalls/architecture, not only small props.
  sections+=1;lo=np.floor(np.min([a for e in seg for a in e],axis=0)/2).astype(int);hi=np.ceil(np.max([a for e in seg for a in e],axis=0)/2).astype(int)
  # Scan-convert closed solid sections only. Flat foliage/wall cutouts are not volumes.
  for sy in range(max(0,lo[1]-1),min(gh*4,hi[1]+2)):
   y=sy*2+1;cross=[];edges=set()
   for a,b in seg:
    if (a[1]>y)!=(b[1]>y):cross.append(a[0]+(b[0]-a[0])*(y-a[1])/(b[1]-a[1]))
   cross.sort()
   if len(cross)%2==0:
    for a,b in zip(cross[::2],cross[1::2]):edges.update(range(int(np.ceil((a-1)/2)),int(np.floor((b-1)/2))+1))
   for sx in edges:
    if sx<0 or sx>=gw*4:continue
    cx,cy=sx//4,sy//4;cell=cy*gw+cx
    if not walk[cy,cx] or cell in special:continue
    occupied[cell]=occupied.get(cell,0)|(1<<((sy%4)*4+sx%4))
 gates=re.search(r'worldGates\[\]=\{(.*?)\};',src,re.S)[1]
 protected=protect_routes46(occupied,walk,unpack(k,2),gates,k)
 payload=struct.pack('<I',len(occupied))+b''.join(struct.pack('<IHH',c,b,0) for c,b in sorted(occupied.items()));append(k,1,collision+payload)
 report.append(dict(map=k,removed_black_triangles=int((~keep).sum()),solid_sections=sections,sparse_cells=len(occupied),extra_ram=len(payload),protected_route_cells=protected))
 print(report[-1],flush=True)
(root.parent/'Packed/world.bin').write_bytes(out);s=(root/'world_data.h').read_text();a=s.index('static const WorldBlob worldBlobs');b=s.index('static const WorldBlob minimapBlobs45',a);s=s[:a]+'static const WorldBlob worldBlobs[18][7]={\n'+',\n'.join('{'+','.join('{'+','.join(map(str,z))+'}' for z in rows[i*7:i*7+7])+'}' for i in range(18))+'};\n'+s[b:];s=re.sub(r'WORLD_FILE_BYTES \d+','WORLD_FILE_BYTES '+str(len(out)),s);(root/'world_data.h').write_text(s);(root/'clearance46.json').write_text(json.dumps(report,indent=2));print('world bytes',len(out))
