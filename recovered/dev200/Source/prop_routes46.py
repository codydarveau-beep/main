# MIT. Source GAT portal routes take priority over additional decorative clearance.
import struct,re
from collections import deque
def protect_routes46(occupied,walk,camp,gates,k):
 h,w=walk.shape;sx,sy=struct.unpack('<ff',camp);start=int(sy/8)*w+int(sx/8);parent=[-1]*(w*h);parent[start]=start;q=deque([start]);flat=walk.ravel()
 while q:
  a=q.popleft();x,y=a%w,a//w
  for b in ([a-1]if x>1 else [])+([a+1]if x<w-2 else [])+([a-w]if y>1 else [])+([a+w]if y<h-2 else []):
   if parent[b]<0 and flat[b]:parent[b]=a;q.append(b)
 protected={start}
 for line in re.findall(r'\{([^{}]+)\}',gates):
  v=list(map(float,line.split(',')))
  if int(v[0])!=k:continue
  _,gx,gy,rx,ry,*_=v;targets=[]
  for y in range(max(1,int((gy-ry)/8)),min(h-1,int((gy+ry)/8)+1)):
   for x in range(max(1,int((gx-rx)/8)),min(w-1,int((gx+rx)/8)+1)):
    a=y*w+x
    if parent[a]>=0:targets.append(((x*8+4-gx)**2+(y*8+4-gy)**2,a))
  if not targets:continue
  a=min(targets)[1]
  while a not in protected:protected.add(a);a=parent[a]
 for a in protected:occupied.pop(a,None)
 return len(protected)
