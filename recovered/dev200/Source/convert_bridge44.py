# MIT. Add only omitted raised Izlude collision cells; other maps/cells unchanged.
from pathlib import Path
import csv,hashlib,re,struct,zlib,sys,json
import numpy as np
r=Path(__file__).resolve().parent;a=Path(sys.argv[1]);rows=list(csv.DictReader((a/'Assets.csv').open(encoding='utf-8-sig')))
row=next(x for x in rows if x['virtual_path'].lower()=='data\\izlude.gat');b=(a/row['payload']).read_bytes();assert hashlib.sha256(b).hexdigest()==row['sha256'];assert b[:6]==b'GRAT\1\2';gw,gh=struct.unpack_from('<II',b,6);ga=np.frombuffer(b,offset=14,dtype=[('z','<f4',(4,)),('kind','<i4')],count=gw*gh);source=-1.6*ga['z'].reshape(gh,gw,4);walk=np.isin(ga['kind'].reshape(gh,gw),[0,3]);blob=(r.parent/'Packed/world.bin').read_bytes();g=zlib.decompress(blob[11569911:11868831]);w,h,n=struct.unpack_from('<III',g);assert(gw,gh)==(2*w,2*h);v=np.frombuffer(g,dtype='<f4',offset=12+(w*h+1)*4,count=w*h*4).reshape(h,w,4);ys,xs=np.indices((gh,gw));c=v[ys//2,xs//2];ground=[]
for dx,dy in [(0,0),(1,0),(0,1),(1,1)]:
 fx=(xs%2+dx)/2;fy=(ys%2+dy)/2;ground.append(np.where(fx>fy,c[:,:,0]+(c[:,:,1]-c[:,:,0])*fx+(c[:,:,3]-c[:,:,1])*fy,c[:,:,0]+(c[:,:,3]-c[:,:,2])*fx+(c[:,:,2]-c[:,:,0])*fy))
sel=walk&((source-np.stack(ground,axis=2)).max(2)>6)
p=r/'walk_surface_data.h';s=p.read_text();offsets=list(map(int,re.search(r'surfaceOffsets\[\]=\{(.*?)\}',s)[1].split(',')));entries=[(int(k),list(map(int,z.split(','))))for k,z in re.findall(r'\{(\d+),\{(.*?)\}\}',s)];by_map=[entries[offsets[i]:offsets[i+1]]for i in range(7)];before=dict(by_map[3]);iz=dict(before)
for key in np.flatnonzero(sel):iz[int(key)]=list(map(int,np.rint(source.reshape(-1,4)[key]*16)))
by_map[3]=sorted(iz.items());offsets=[0]
for x in by_map:offsets.append(offsets[-1]+len(x))
p.write_text('/* Source GAT raised surfaces; Test44 adds omitted Izlude ramp corners. */\ntypedef struct {unsigned cell;short z[4];} WalkSurface;\nstatic const unsigned surfaceOffsets[]={'+','.join(map(str,offsets))+'};\nstatic const WalkSurface surfaceCells[]={\n'+''.join('{%d,{%s}},\n'%(k,','.join(map(str,z)))for m in by_map for k,z in m)+'};\n')
new=sorted(set(iz)-set(before));report={'source_sha256':row['sha256'],'map':'izlude','previous_cells':len(before),'current_cells':len(iz),'added_cells':len(new),'added_coordinates':[[k%gw,k//gw]for k in new],'rule':'walkable source cell with any corner over six units above rendered ground; retain previous raised cells','other_maps_unchanged':True};(r/'bridge44.json').write_text(json.dumps(report,indent=2)+'\n');print(report)
