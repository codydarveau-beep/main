"""MIT. Build bounded-residency maps, scenery, warps and loading images.
Usage: python3 convert_world.py expansion-collection.zip
Requires NumPy/Pillow. Input files are read only; ownership retained.
Map IDs 0/1 remain South/West for importing Test08/09 saves.
"""
from pathlib import Path
import zipfile,csv,io,hashlib,struct,math,zlib,json,re,sys
import numpy as np
from PIL import Image
import convert_scenery
ROOT=Path(__file__).resolve().parent.parent
MAPS=['prt_fild08','prt_fild05','prontera','izlude','prt_fild06','prt_fild07','prt_fild09']
LABELS=['South Field','West Field','Prontera','Izlude','East Field','Southwest Field','Southwest Outskirts']

def ground(assets,name,out,label=None):
 b=assets['data\\'+name+'.gnd'];assert b[:6]==b'GRGN\x01\x07'
 w,h,zoom,nt,ln=struct.unpack_from('<IIfII',b,6);p=26;names=[]
 for _ in range(nt):names.append(b[p:p+ln].split(b'\0')[0].decode('cp949').lower());p+=ln
 nl,lx,ly,ls=struct.unpack_from('<4I',b,p);p+=16+nl*lx*ly*ls*4
 n=struct.unpack_from('<I',b,p)[0];p+=4;tiles=[struct.unpack_from('<8fHH4B',b,p+i*40) for i in range(n)];p+=n*40
 cells=[struct.unpack_from('<4f3i',b,p+i*28) for i in range(w*h)];assert p+w*h*28==len(b)
 slot=260;cols=5;rows=math.ceil(nt/cols);aw=((cols*slot+31)//32)*32;ah=rows*slot
 atlas=Image.new('RGB',(aw,ah),(30,40,25))
 for i,name_tex in enumerate(names):
  im=Image.open(io.BytesIO(assets['data\\texture\\'+name_tex])).convert('RGB').resize((256,256),Image.Resampling.BILINEAR)
  x=i%cols*slot+2;y=i//cols*slot+2;atlas.paste(im,(x,y));atlas.paste(im.crop((0,0,1,256)).resize((2,256)),(x-2,y));atlas.paste(im.crop((255,0,256,256)).resize((2,256)),(x+256,y));atlas.paste(im.crop((0,0,256,1)).resize((256,2)),(x,y-2));atlas.paste(im.crop((0,255,256,256)).resize((256,2)),(x,y+256))
 a=np.array(atlas,dtype=np.uint16);rgb=((a[:,:,0]>>3)<<11)|((a[:,:,1]>>2)<<5)|(a[:,:,2]>>3);(out/'atlas.bin').write_bytes(struct.pack('<II',aw,ah)+rgb.astype('<u2').tobytes())
 verts=[];starts=[];heights=np.array([[-v*1.6 for v in c[:4]] for c in cells],dtype='<f4')
 def face(points,ti,corners=(0,1,3,2)):
  t=tiles[ti];tex=t[8];assert tex<nt;uv=[(tex%cols*slot+2+t[k]*256,tex//cols*slot+2+t[k+4]*256) for k in corners]
  for j in (0,1,2,0,2,3):verts.append((*points[j],*uv[j]))
 for y in range(h):
  for x in range(w):
   i=y*w+x;c=cells[i];ha=heights[i];starts.append(len(verts));x0=x*16;y0=y*16
   if c[4]>=0:face([(x0,y0,ha[0]),(x0+16,y0,ha[1]),(x0+16,y0+16,ha[3]),(x0,y0+16,ha[2])],c[4])
   if c[5]>=0 and y+1<h:
    hb=heights[i+w];face([(x0,y0+16,ha[2]),(x0+16,y0+16,ha[3]),(x0+16,y0+16,hb[1]),(x0,y0+16,hb[0])],c[5])
   if c[6]>=0 and x+1<w:
    hb=heights[i+1];face([(x0+16,y0+16,ha[3]),(x0+16,y0,ha[1]),(x0+16,y0,hb[0]),(x0+16,y0+16,hb[2])],c[6])
 starts.append(len(verts));va=np.array(verts,dtype='<f4');assert np.isfinite(va).all();geometry=struct.pack('<III',w,h,len(verts))+np.array(starts,dtype='<u4').tobytes()+heights.tobytes()+va.tobytes();(out/'geometry.bin').write_bytes(geometry)
 gb=assets['data\\'+name+'.gat'];assert gb[:6]==b'GRAT\x01\x02';ww,wh=struct.unpack_from('<II',gb,6);assert (ww,wh)==(w*2,h*2)
 gat=np.frombuffer(gb,offset=14,dtype=np.dtype([('z','<f4',(4,)),('kind','<i4')]),count=ww*wh);walk=np.isin(gat['kind'],[0,3]).astype(np.uint8).reshape(wh,ww);(out/'walk.bin').write_bytes(struct.pack('<II',ww,wh)+walk.tobytes())
 target={'prt_fild08':(2100,1636),'prt_fild05':(1604,1604),'prontera':(156*8,185*8),'izlude':(125*8,120*8)}.get(name,(w*8,h*8));choices=[]
 for gy in range(4,wh-4):
  for gx in range(4,ww-4):
   if walk[gy-2:gy+3,gx-2:gx+3].all() and np.ptp(heights[(gy//2)*w+gx//2])<8:choices.append((((gx+.5)*8-target[0])**2+((gy+.5)*8-target[1])**2,gx,gy))
 if not choices:
  ys,xs=np.nonzero(walk);assert len(xs),'map has no walkable source cells'
  distances=((xs+.5)*8-target[0])**2+((ys+.5)*8-target[1])**2;nearest=int(np.argmin(distances));choices=[(float(distances[nearest]),int(xs[nearest]),int(ys[nearest]))]
 _,gx,gy=min(choices);sx,sy=(gx+.5)*8,(gy+.5)*8
 # Preserve exact existing safe camps when possible.
 tx,ty=target
 if name in ('prt_fild08','prt_fild05') and walk[int(ty//8),int(tx//8)]:sx,sy=tx,ty
 (out/'spawn.bin').write_bytes(struct.pack('<ff',sx,sy))
 return dict(map=name,label=label if label is not None else LABELS[MAPS.index(name)],width=w,height=h,vertices=len(verts),atlas=[aw,ah],spawn=[sx,sy])

def emit(f,name,raw):
 packed=zlib.compress(raw,9);f.write('const unsigned int %s_raw=%d,%s_size=%d;\nconst unsigned char %s[]={\n'%(name,len(raw),name,len(packed),name))
 for i in range(0,len(packed),32):f.write(','.join(map(str,packed[i:i+32]))+',\n')
 f.write('};\n');return len(packed)

def main(path):
 assets={}
 with zipfile.ZipFile(path) as z:
  for r in csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))):
   b=z.read(r['payload']);assert hashlib.sha256(b).hexdigest()==r['sha256'];assets[r['virtual_path'].lower()]=b
 reports=[];total=0;world=ROOT/'WorldAssets';world.mkdir(exist_ok=True)
 with (ROOT/'Source/town_assets.c').open('w') as f:
  f.write('/* Generated from supplied game assets; original ownership retained. */\n')
  for i,name in enumerate(MAPS):
   out=world/name;out.mkdir(exist_ok=True);(out/'Source').mkdir(exist_ok=True);rep=ground(assets,name,out)
   convert_scenery.convert([path],out,map_names=[name],texture_limit=128)
   # Each pack has four terrain assets followed by three scenery assets.
   blobs=[(out/n).read_bytes() for n in ['atlas.bin','walk.bin','spawn.bin','geometry.bin']]+[(out/'SceneryAssets'/n).read_bytes() for n in ['atlas.bin','mesh.bin','instances.bin']]
   packed=sum(emit(f,'town%d_%d'%(i,j),b) for j,b in enumerate(blobs));total+=packed
   rep['packed']=packed;rep['raw']=sum(map(len,blobs));rep['scenery']=json.loads((out/'SCENERY-CONVERSION-REPORT.json').read_text());reports.append(rep);print('MAP DONE',name,packed,rep['raw'],flush=True)
  loadkey='data\\texture\\유저인터페이스\\loading00.jpg';im=Image.open(io.BytesIO(assets[loadkey])).convert('RGB');im.thumbnail((640,480),Image.Resampling.LANCZOS);canvas=Image.new('RGB',(640,480));canvas.paste(im,((640-im.width)//2,(480-im.height)//2));canvas.save(ROOT/'loading-preview.png');a=np.array(canvas,dtype=np.uint16);rgb=((a[:,:,0]>>3)<<11)|((a[:,:,1]>>2)<<5)|(a[:,:,2]>>3);total+=emit(f,'loading_image',rgb.astype('<u2').tobytes())
 # Explicit source warp endpoints within the selected region, preserving trigger extents.
 warps=[];seen=set()
 for key,b in assets.items():
  if not key.startswith('server/npc/') or '/warps/' not in key:continue
  for line in b.decode('cp949',errors='replace').splitlines():
   if not line.strip() or line.lstrip().startswith('//'):continue
   m=re.match(r'\s*(\w+),(\d+),(\d+),\d+\s+warp\s+\S+\s+(\d+),(\d+),(\w+),(\d+),(\d+)',line)
   if not m:continue
   src,x,y,rx,ry,dst,dx,dy=m.groups()
   if src not in MAPS or dst not in MAPS or src==dst:continue
   v=(MAPS.index(src),int(x),int(y),int(rx),int(ry),MAPS.index(dst),int(dx),int(dy))
   if v not in seen:warps.append(v);seen.add(v)
 with (ROOT/'Source/world_data.h').open('w') as f:
  f.write('/* Generated map metadata and authentic selected-region warp definitions. */\n#define WORLD_MAP_COUNT 7\ntypedef struct {const unsigned char*data;unsigned packed,raw;} WorldBlob;\ntypedef struct {unsigned source;float x,y,rx,ry;unsigned destination;float destX,destY;} WorldGate;\n')
  for i in range(7):
   for j in range(7):f.write('extern const unsigned char town%d_%d[];\nextern const unsigned int town%d_%d_size,town%d_%d_raw;\n'%(i,j,i,j,i,j))
  # sizes are not C constant expressions: initialization filled by init function.
  f.write('static WorldBlob worldBlobs[7][7];\nstatic void world_blob_init(void){\n')
  for i in range(7):
   for j in range(7):f.write('worldBlobs[%d][%d]=(WorldBlob){town%d_%d,town%d_%d_size,town%d_%d_raw};\n'%(i,j,i,j,i,j,i,j))
  f.write('}\nstatic const char*mapLabels[]={'+','.join(json.dumps(x) for x in LABELS)+'};\nstatic const char*mapNames[]={'+','.join(json.dumps(x) for x in MAPS)+'};\nstatic const unsigned mapWidths[]={'+','.join(str(r['width']) for r in reports)+'};\nstatic const unsigned mapHeights[]={'+','.join(str(r['height']) for r in reports)+'};\n')
  f.write('static const WorldGate worldGates[]={\n')
  for src,x,y,rx,ry,dst,dx,dy in warps:f.write('{%d,%d,%d,%d,%d,%d,%d,%d},\n'%(src,x*8+4,y*8+4,max(rx,1)*8+8,max(ry,1)*8+8,dst,dx*8+4,dy*8+4))
  f.write('};\n#define WORLD_GATE_COUNT (sizeof(worldGates)/sizeof(worldGates[0]))\n')
 report={'maps':reports,'embedded_packed_bytes':total,'warps':warps,'scenery_texture_max':128,'loading':loadkey};(ROOT/'WORLD-CONVERSION-REPORT.json').write_text(json.dumps(report,indent=2,ensure_ascii=False));print('TOTAL EMBEDDED',total,'WARPS',len(warps),flush=True)
if __name__=='__main__':main(sys.argv[1])
