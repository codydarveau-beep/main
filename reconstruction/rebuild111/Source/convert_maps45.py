# MIT. Append current-map collision surfaces and streamed original minimaps; retain44 prefix.
from pathlib import Path
import struct,zlib,re,json
import numpy as np
from PIL import Image
import convert_scenery as scenery45
r=Path(__file__).resolve().parent;root=r.parent;lib=root.parent/'asset-library';base=root.parent/'test44';s=(base/'Source/world_data.h').read_text();blob=(base/'Packed/world.bin').read_bytes();rows=[list(map(int,x))for x in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',s[:s.index('static void world_blob_init')])];assert len(rows)==126;maps=re.search(r'mapNames\[\]=\{(.*?)\}',s)[1];names=re.findall('"(.*?)"',maps);wb=bytearray(blob);report=[];minis=[]
surf=(base/'Source/walk_surface_data.h').read_text();offs=list(map(int,re.search(r'surfaceOffsets\[\]=\{(.*?)\}',surf)[1].split(',')));old=[(int(k),list(map(int,z.split(','))))for k,z in re.findall(r'\{(\d+),\{(.*?)\}\}',surf)]
for k,name in enumerate(names):
 files=[lib/'Test45-return/data'/ (name+'.gat'),lib/'Izlude-Bridge44-return/payload/000000.gat',lib/'Payon43-return/data'/(name+'.gat')];path=files[0]if k<7 and k!=3 else files[1]if k==3 else files[2];b=path.read_bytes();assert b[:6]==b'GRAT\1\2';gw,gh=struct.unpack_from('<II',b,6);gat=np.frombuffer(b,offset=14,dtype=[('z','<f4',(4,)),('kind','<i4')],count=gw*gh);heights=-1.6*gat['z'].reshape(gh,gw,4);walk=np.isin(gat['kind'].reshape(gh,gw),[0,3]);off,sz,raw,crc=rows[k*7+3];g=zlib.decompress(blob[off:off+sz]);w,h,n=struct.unpack_from('<III',g);assert(gw,gh)==(2*w,2*h);v=np.frombuffer(g,dtype='<f4',offset=12+(w*h+1)*4,count=w*h*4).reshape(h,w,4);ys,xs=np.indices((gh,gw));c=v[ys//2,xs//2];ground=[]
 for dx,dy in [(0,0),(1,0),(0,1),(1,1)]:
  fx=(xs%2+dx)/2;fy=(ys%2+dy)/2;ground.append(np.where(fx>fy,c[:,:,0]+(c[:,:,1]-c[:,:,0])*fx+(c[:,:,3]-c[:,:,1])*fy,c[:,:,0]+(c[:,:,3]-c[:,:,2])*fx+(c[:,:,2]-c[:,:,0])*fy))
 delta=heights-np.stack(ground,2);sel=walk&(delta.max(2)>6);cells={int(i):list(map(int,np.rint(heights.reshape(-1,4)[i]*16)))for i in np.flatnonzero(sel)}
 if k<7:
  cells.update(dict(old[offs[k]:offs[k+1]]))
 if k==3:cells=dict(old[offs[3]:offs[4]]) # Accepted Izlude44 bytes/logic untouched.
 for q in cells.values():assert all(-32768<=z<=32767 for z in q)
 source_walk45=walk.copy();prop45=[]
 if k>=13:
  rsw=(lib/'Payon43-return/data'/(name+'.rsw')).read_bytes()
  for model,values in scenery45.world(rsw):
   if '버섯'not in model and'화로'not in model:continue
   cx=int((values[0]*1.6+gw*4)/8);cy=int((values[2]*1.6+gh*4)/8)
   if 0<=cx<gw and 0<=cy<gh and walk[cy,cx]:walk[cy,cx]=False;cells.pop(cy*gw+cx,None);prop45.append([model,cx,cy])
 off,sz,_,_=rows[k*7+1];prior=zlib.decompress(blob[off:off+sz]);assert prior==struct.pack('<II',gw,gh)+source_walk45.astype('uint8').tobytes()
 data=struct.pack('<II',gw,gh)+walk.astype('uint8').tobytes()+struct.pack('<I',len(cells))+b''.join(struct.pack('<I4h',key,*q)for key,q in sorted(cells.items()));cp=zlib.compress(data,9);rows[k*7+1]=[len(wb),len(cp),len(data),zlib.crc32(cp)];wb+=cp
 mini=Image.open(lib/'Test45-return/data/texture/유저인터페이스/map'/(name+'.bmp')).convert('RGB');ar=np.array(mini);pink=(ar[:,:,0]>230)&(ar[:,:,1]<30)&(ar[:,:,2]>230);ar[pink]=[234,240,245];mini=Image.fromarray(ar)
 if gw*72>=gh*96:ww=96;hh=max(1,gh*96//gw)
 else:hh=72;ww=max(1,gw*72//gh)
 out=Image.new('RGBA',(96,72),(234,240,245,255));out.paste(mini.resize((ww,hh),Image.Resampling.LANCZOS),((96-ww)//2,(72-hh)//2));data=out.tobytes('raw','BGRA');cp=zlib.compress(data,9);minis.append([len(wb),len(cp),len(data),zlib.crc32(cp)]);wb+=cp
 report.append({'map':name,'surface_cells':len(cells),'solid_prop_exceptions':prop45,'source_walk_cells':int(walk.sum()),'mini_raw_bytes':len(data),'max_corner_raise':float(delta[walk].max()),'izlude44_preserved':k==3})
(root/'Packed/world.bin').write_bytes(wb);s=(r/'world_data.h').read_text();a=s.index('static const WorldBlob worldBlobs');b=s.index('static void world_blob_init',a);s=s[:a]+'static const WorldBlob worldBlobs[18][7]={\n'+',\n'.join('{'+','.join('{'+','.join(map(str,z))+'}'for z in rows[i*7:(i+1)*7])+'}'for i in range(18))+'};\nstatic const WorldBlob minimapBlobs45[18]={'+','.join('{'+','.join(map(str,z))+'}'for z in minis)+'};\n'+s[b:];s=re.sub(r'WORLD_FILE_BYTES \d+','WORLD_FILE_BYTES '+str(len(wb)),s);(r/'world_data.h').write_text(s);(r/'maps45.json').write_text(json.dumps(report,indent=2));print(json.dumps(report,indent=1));print('worldpack',len(wb),'prefix',len(blob),'total sparse cells',sum(x['surface_cells']for x in report))
