"""MIT. Static source-height water. Read-only original GND/RSW assets.
python convert_water.py expansion-collection.zip
Emits compact row-merged wet-cell rectangles; depth buffer clips shorelines.
"""
from pathlib import Path
import csv,io,zipfile,hashlib,struct,math,json
import numpy as np
MAPS=['prt_fild08','prt_fild05','prontera','izlude','prt_fild06','prt_fild07','prt_fild09']
def rectangles(mask):
 active={};out=[]
 for y,row in enumerate(mask):
  spans=[];x=0
  while x<len(row):
   if not row[x]:x+=1;continue
   start=x
   while x<len(row) and row[x]:x+=1
   spans.append((start,x))
  nextactive={}
  for key in spans:
   nextactive[key]=active.pop(key,[key[0]*16,y*16,key[1]*16,(y+1)*16]);nextactive[key][3]=(y+1)*16
  out.extend(active.values());active=nextactive
 out.extend(active.values());return out

def main(path,root):
 assets={}
 with zipfile.ZipFile(path) as z:
  for row in csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))):
   name=row['virtual_path'].lower()
   if any(name=='data\\'+m+ext for m in MAPS for ext in ['.gnd','.rsw']):
    b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];assets[name]=b
 allrect=[];maps=[];reports=[]
 for name in MAPS:
  b=assets['data\\'+name+'.rsw'];assert b[:4]==b'GRSW';v=b[4]*10+b[5];assert 13<=v<=21
  z=-1.6*struct.unpack_from('<f',b,126+(40 if v>=14 else 0))[0];assert math.isfinite(z)
  b=assets['data\\'+name+'.gnd'];assert b[:6]==b'GRGN\x01\x07';w,h,zoom,nt,ln=struct.unpack_from('<IIfII',b,6);p=26+nt*ln
  nl,lx,ly,ls=struct.unpack_from('<4I',b,p);p+=16+nl*lx*ly*ls*4;n=struct.unpack_from('<I',b,p)[0];p+=4+n*40
  cells=np.frombuffer(b,offset=p,count=w*h,dtype=np.dtype([('h','<f4',4),('tiles','<i4',3)]));heights=-1.6*cells['h'];assert np.isfinite(heights).all()
  mask=(heights.min(axis=1)<z-.01).reshape(h,w);rect=rectangles(mask)
  # Exact coverage: no dry cells and no holes introduced by merging.
  coverage=np.zeros_like(mask,dtype=np.uint8)
  for x0,y0,x1,y1 in rect:coverage[y0//16:y1//16,x0//16:x1//16]+=1
  assert np.array_equal(coverage,mask.astype(np.uint8))
  maps.append((len(allrect),len(rect),z));allrect+=rect;reports.append(dict(map=name,height=z,wet_cells=int(mask.sum()),rectangles=len(rect)))
 with (root/'Source/water_data.h').open('w') as f:
  f.write('/* Generated original RSW heights and GND wet-cell coverage. */\nstatic const struct {unsigned start,count;float z;} waterMaps[]={\n')
  for start,count,z in maps:f.write('{%d,%d,%.9gf},\n'%(start,count,z) if z%1 else '{%d,%d,%.1ff},\n'%(start,count,z))
  f.write('};\nstatic const unsigned short waterRects[][4]={\n')
  for rect in allrect:f.write('{%d,%d,%d,%d},\n'%tuple(rect))
  f.write('};\n')
 (root/'WATER-CONVERSION-REPORT.json').write_text(json.dumps(reports,indent=2));print(reports)
if __name__=='__main__':
 import sys
 main(sys.argv[1],Path(__file__).resolve().parent.parent)
