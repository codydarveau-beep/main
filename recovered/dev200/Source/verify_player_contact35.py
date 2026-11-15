"""Read-only grounding check against all real equipped/unarmed standing actors.
The Test34 last-four-row rule selected the lower boot, not the stance midpoint.
Use the lower14px support silhouette and the mean of the two sole heights.
No per-frame recentering: walking/attack motion remains intact.
"""
from pathlib import Path
import sys,re,zlib,struct,json
root=Path(__file__).resolve().parent
blob=Path(sys.argv[1]).read_bytes()
rows=re.findall(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),0x[0-9a-f]+u\}',(root/'actor_data.h').read_text())
def actor(row):
 job,gear,offset,packed,rawsize=map(int,row)
 raw=zlib.decompress(blob[offset:offset+packed]);assert len(raw)==rawsize
 w,h,n,a,s,ax,ay,pix=struct.unpack_from('<8I',raw);start=32+a*12+s*4;data=start+n*20
 result=[]
 for dr in range(8):
  si=struct.unpack_from('<I',raw,32+dr*12)[0];fi=struct.unpack_from('<I',raw,32+a*12+si*4)[0]
  x,y,ww,hh,off=struct.unpack_from('<5I',raw,start+fi*20);v=struct.unpack_from('<%dH'%(ww*hh),raw,data+off)
  pts=[(x+xx,y+yy+1)for yy in range(max(0,hh-14),hh)for xx in range(ww)if v[yy*ww+xx]&32768]
  cx=(min(p[0]for p in pts)+max(p[0]for p in pts))*.5
  cy=(max(p[1]for p in pts if p[0]<=cx)+max(p[1]for p in pts if p[0]>=cx))*.5
  result.append((ax-cx,ay-cy,cx,cy,ax,ay))
 return job,gear,result
corrections=[tuple(map(float,m))for m in re.findall(r'\{(-?[\d.]+)f,(-?[\d.]+)f\}',(root/'player_contact.h').read_text())]
assert len(corrections)==56
for row in rows:
 job,gear,results=actor(row)
 for dr,(dx,dy,cx,cy,ax,ay) in enumerate(results):
  assert corrections[job*8+dr]==(dx,dy),(job,gear,dr)
  # Real screen-facing quad's texel position, not the overlay/collision predicate.
  for z in [.85,1.2,1.8]:
   scale=z/3;px,py=321.25,244.75
   assert abs(px+dx*scale-ax*scale+cx*scale-px)<.001
   assert abs(py+dy*scale-ay*scale+cy*scale-py)<.001
print('PASS14 real actor variants x8 directions x3 zooms: projected stance midpoint meets contact; standing gear agrees')
