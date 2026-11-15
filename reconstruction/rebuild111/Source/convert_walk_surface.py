"""MIT. Sparse authentic walk-surface fixes and disconnected warp markers.
Regenerates small headers only; never changes map geometry or source archives.
"""
from pathlib import Path
import csv,io,json,zipfile,struct,zlib,hashlib,re,sys
import numpy as np
ROOT=Path(__file__).resolve().parent.parent
MAPS=['prt_fild08','prt_fild05','prontera','izlude','prt_fild06','prt_fild07','prt_fild09']
def main(archive):
 idx={r['name']:r for r in json.loads((ROOT/'Packed/index.json').read_text())};blob=(ROOT/'Packed/world.bin').read_bytes();allrows=[];offsets=[0];report=[];pending=set()
 with zipfile.ZipFile(archive) as z:
  rows={r['virtual_path'].lower():r for r in csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig')))}
  def read(row):
   b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];return b
  for k,name in enumerate(MAPS):
   b=read(rows['data\\'+name+'.gat']);assert b[:6]==b'GRAT\1\2';gw,gh=struct.unpack_from('<II',b,6);a=np.frombuffer(b,offset=14,dtype=[('z','<f4',(4,)),('kind','<i4')],count=gw*gh)
   r=idx[f'town{k}_3'];g=zlib.decompress(blob[r['offset']:r['offset']+r['size']]);w,h,n=struct.unpack_from('<III',g);assert (gw,gh)==(w*2,h*2);v=np.frombuffer(g,dtype='<f4',offset=12+(w*h+1)*4,count=w*h*4).reshape(h,w,4)
   ys,xs=np.indices((gh,gw));fx=(xs%2+.5)/2;fy=(ys%2+.5)/2;c=v[ys//2,xs//2];ground=np.where(fx>fy,c[:,:,0]+(c[:,:,1]-c[:,:,0])*fx+(c[:,:,3]-c[:,:,1])*fy,c[:,:,0]+(c[:,:,3]-c[:,:,2])*fx+(c[:,:,2]-c[:,:,0])*fy)
   gat=-1.6*a['z'].mean(axis=1).reshape(gh,gw);walk=np.isin(a['kind'].reshape(gh,gw),[0,3]);sel=walk&(gat-ground>6)
   count=0
   for cell in np.flatnonzero(sel):
    corner=-1.6*a['z'][cell];assert np.isfinite(corner).all();q=np.rint(corner*16).astype(np.int64);assert (q>=-32768).all() and(q<=32767).all();allrows.append((int(cell),*map(int,q)));count+=1
   offsets.append(len(allrows));report.append({'map':name,'surface_cells':count,'max_delta':float((gat-ground)[walk].max())})
  for key,row in rows.items():
   if not key.startswith('server/npc/') or '/warps/' not in key:continue
   for line in read(row).decode('cp949',errors='replace').splitlines():
    if line.lstrip().startswith('//'):continue
    m=re.match(r'\s*(\w+),(\d+),(\d+),\d+\s+warp\s+\S+\s+(\d+),(\d+),(\w+),(\d+),(\d+)',line)
    if not m:continue
    src,x,y,rx,ry,dst,dx,dy=m.groups()
    if src not in MAPS or(dst in MAPS and dst!=src):continue
    pending.add((MAPS.index(src),int(x)*8+4,int(y)*8+4,dst))
 with (ROOT/'Source/walk_surface_data.h').open('w') as f:
  f.write('/* Generated from user-supplied GAT; original content ownership retained. */\ntypedef struct {unsigned cell;short z[4];} WalkSurface;\nstatic const unsigned surfaceOffsets[]={'+','.join(map(str,offsets))+'};\nstatic const WalkSurface surfaceCells[]={\n')
  for cell,*q in allrows:f.write('{%d,{%s}},\n'%(cell,','.join(map(str,q))))
  f.write('};\n')
 with(ROOT/'Source/pending_warps.h').open('w') as f:
  f.write('/* Explicit source warps whose destination is not connected in this build. */\ntypedef struct{unsigned map;float x,y;const char*destination;} PendingWarp;\nstatic const PendingWarp pendingWarps[]={\n')
  for k,x,y,dst in sorted(pending):f.write('{%d,%d,%d,"%s"},\n'%(k,x,y,dst))
  f.write('};\n#define PENDING_WARP_COUNT (sizeof(pendingWarps)/sizeof(pendingWarps[0]))\n')
 (ROOT/'WALK-SURFACE-REPORT.json').write_text(json.dumps({'maps':report,'table_bytes':len(allrows)*12+len(offsets)*4,'pending_warps':len(pending)},indent=2));print(report,'bytes',len(allrows)*12,'pending',len(pending))
if __name__=='__main__':main(sys.argv[1])
