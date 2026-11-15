"""Complete the original water table for every prepared ordinary world map.
Preserve old18 rows and rectangles exactly; derive new coverage from source GND/RSW.
"""
from pathlib import Path
import re,json,struct,math,sys
import numpy as np
from convert_water import rectangles
from world_assets51 import WorldAssets51
R=Path(__file__).resolve().parent;ROOT=R.parent;BASE=ROOT.parent/'test51';assets=WorldAssets51(ROOT.parent/'asset-library/Test51-world-maps/Asset-Index.json',8*1024*1024)
s=(BASE/'Source/water_data.h').read_text();a=s.index('};',s.index('waterMaps'));oldmaps=s[s.index('waterMaps'):a];oldrows=re.findall(r'\{(\d+),(\d+),([^{}]+)\}',oldmaps);assert len(oldrows)==18
recttext=re.search(r'waterRects\[\]\[4\]=\{(.*?)\};',s,re.S)[1];oldrects=[list(map(int,x))for x in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',recttext)];offset=len(oldrects);newrows=[];newrects=[];report=[]
world=(BASE/'Source/world_data.h').read_text();names=json.loads('['+re.search(r'mapNames\[\]=\{(.*?)\}',world)[1]+']')
for mid,name in enumerate(names[18:],18):
 b=assets['data/'+name+'.rsw'];assert b[:4]==b'GRSW';v=b[4]*10+b[5];assert 13<=v<=22;z=-1.6*struct.unpack_from('<f',b,126+(40 if v>=14 else 0)+(1 if v>=22 else 0))[0];assert math.isfinite(z)
 b=assets['data/'+name+'.gnd'];assert b[:6]==b'GRGN\x01\x07';w,h,zoom,nt,ln=struct.unpack_from('<IIfII',b,6);p=26+nt*ln;nl,lx,ly,ls=struct.unpack_from('<4I',b,p);p+=16+nl*lx*ly*ls*4;n=struct.unpack_from('<I',b,p)[0];p+=4+n*40
 cells=np.frombuffer(b,offset=p,count=w*h,dtype=np.dtype([('h','<f4',4),('tiles','<i4',3)]));heights=-1.6*cells['h'];assert np.isfinite(heights).all();mask=(heights.min(axis=1)<z-.01).reshape(h,w);rect=rectangles(mask);coverage=np.zeros_like(mask,dtype=np.uint8)
 for x0,y0,x1,y1 in rect:
  assert 0<=x0<x1<=w*16<=65535 and 0<=y0<y1<=h*16<=65535;coverage[y0//16:y1//16,x0//16:x1//16]+=1
 assert np.array_equal(coverage,mask.astype(np.uint8))
 newrows.append('{%d,%d,%.9ef},\n'%(offset+len(newrects),len(rect),z));newrects+=rect;report.append(dict(id=mid,map=name,height=z,wet_cells=int(mask.sum()),rectangles=len(rect)))
end=s.index('};',s.index('waterRects'));s=s[:end]+''.join('{'+','.join(map(str,rect))+'},\n'for rect in newrects)+s[end:];s=s[:a]+''.join(newrows)+s[a:]
s+='''\n#define WATER_MAP_COUNT51A (sizeof(waterMaps)/sizeof(waterMaps[0]))
#define WATER_RECT_COUNT51A (sizeof(waterRects)/sizeof(waterRects[0]))
typedef char WaterMapCoverage51a[(WATER_MAP_COUNT51A==WORLD_MAP_COUNT)?1:-1];
static int water_map_valid51a(unsigned map){if(map>=WATER_MAP_COUNT51A)return 0;unsigned start=waterMaps[map].start,count=waterMaps[map].count;return start<=WATER_RECT_COUNT51A&&count<=WATER_RECT_COUNT51A-start;}
'''
(R/'water_data.h').write_text(s);(ROOT/'WATER-CONVERSION51A.json').write_text(json.dumps(dict(maps=len(names),preserved_maps=18,preserved_rectangles=len(oldrects),new_rectangles=len(newrects),new_maps=report),indent=2));print('PASS',len(names),'source water maps; original18 rows/'+str(len(oldrects))+' rectangles unchanged;',len(newrects),'new rectangles; exact wet-cell coverage')
