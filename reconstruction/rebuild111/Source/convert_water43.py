# MIT. Append source-height water coverage for the eleven expansion maps.
from pathlib import Path
import re,struct,json
import numpy as np
from convert_water import rectangles
r=Path(__file__).resolve().parent;lib=r.parent.parent/'asset-library/Payon43-return/data';maps=json.loads((r.parent/'PAYON-CONVERSION43.json').read_text())['maps'];s=(r.parent.parent/'test42/Source/water_data.h').read_text();m=re.search(r'waterRects\[\]\[4\]=\{(.*?)\};',s,re.S);offset=len(re.findall(r'\{',m[1]));rows=[];rs=[]
for item in maps:
 name=item['map'];b=(lib/(name+'.rsw')).read_bytes();v=b[4]*10+b[5];z=-1.6*struct.unpack_from('<f',b,126+(40 if v>=14 else 0))[0];b=(lib/(name+'.gnd')).read_bytes();w,h,zoom,nt,ln=struct.unpack_from('<IIfII',b,6);p=26+nt*ln;nl,lx,ly,ls=struct.unpack_from('<4I',b,p);p+=16+nl*lx*ly*ls*4;n=struct.unpack_from('<I',b,p)[0];p+=4+n*40;cells=np.frombuffer(b,offset=p,count=w*h,dtype=np.dtype([('h','<f4',4),('tiles','<i4',3)]));mask=(-1.6*cells['h']).min(axis=1).reshape(h,w)<z-.01;rect=rectangles(mask);rows.append('{%d,%d,%.5ff},\n'%(offset+len(rs),len(rect),z));rs+=rect
pos=s.index('};',s.index('waterMaps'));s=s[:pos]+''.join(rows)+s[pos:];pos=s.index('};',s.index('waterRects'));s=s[:pos]+''.join('{'+','.join(map(str,x))+'},\n'for x in rs)+s[pos:];(r/'water_data.h').write_text(s);print('water appended',len(rs),'rectangles')
