# MIT. Derive standing support midpoints for two appended classes; preserve old contacts.
from pathlib import Path
import struct,numpy as np
r=Path(__file__).resolve().parent;rows=[]
for name in ['Wizard','Sage','Crusader','MountedCrusader']:
 b=(r.parent/'ClassAssets'/(name+'.bin')).read_bytes();w,h,n,a,seq,ax,ay,_=struct.unpack_from('<8I',b);startdir=32+a*12+seq*4;pixels=startdir+n*20;row=[]
 for d in range(8):
  start=struct.unpack_from('<I',b,32+d*12)[0];frame=struct.unpack_from('<I',b,32+a*12+start*4)[0];x,y,ww,hh,off=struct.unpack_from('<5I',b,startdir+frame*20);data=np.frombuffer(b,offset=pixels+off,count=ww*hh,dtype='<u2').reshape(hh,ww);ys,xs=np.where((data&0x8000)!=0);mask=ys>=hh-14;xs=xs[mask]+x;ys=ys[mask]+y;fx=(xs.min()+xs.max())/2;fy=((ys[xs<=fx]+1).max()+(ys[xs>=fx]+1).max())/2;row.append([float(ax-fx),float(ay-fy)])
 rows.append(row)
s=(r.parent.parent/'test47a/Source/player_contact.h').read_text().replace('playerContact[9]','playerContact[13]');pos=s.index('};');s=s[:pos]+',\n'+',\n'.join('{'+','.join('{%.1ff,%.1ff}'%tuple(x)for x in row)+'}'for row in rows)+s[pos:];s=s.replace('}},\n,','}},\n');(r/'player_contact.h').write_text(s)
