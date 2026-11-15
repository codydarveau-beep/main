"""Validate standing-player foot calibration directly against actors.bin.
Usage: python verify_player_contact34.py ../Actors/actors.bin
No game assets are changed.
"""
from pathlib import Path
import sys,re,zlib,struct
r=Path(__file__).resolve().parent;b=Path(sys.argv[1]).read_bytes()
rows=re.findall(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),0x[0-9a-f]+u\}',(r/'actor_data.h').read_text())
corrections=[tuple(map(float,m))for m in re.findall(r'\{(-?[\d.]+)f,(-?[\d.]+)f\}',(r/'player_contact.h').read_text())]
assert len(corrections)==56
for job in range(7):
 j,g,offset,packed,rawsize=next(tuple(map(int,row))for row in rows if int(row[0])==job and int(row[1])==0)
 raw=zlib.decompress(b[offset:offset+packed]);assert len(raw)==rawsize
 w,h,n,a,s,ax,ay,pix=struct.unpack_from('<8I',raw);seq=struct.unpack_from('<%dI'%s,raw,32+a*12);start=32+a*12+s*4;data=start+n*20
 for dr in range(8):
  fi=seq[struct.unpack_from('<I',raw,32+dr*12)[0]];x,y,ww,hh,off=struct.unpack_from('<5I',raw,start+fi*20);v=struct.unpack_from('<%dH'%(ww*hh),raw,data+off)
  pts=[x+xx for yy in range(max(0,hh-4),hh)for xx in range(ww)if v[yy*ww+xx]&32768];fx=(min(pts)+max(pts))*.5;fy=y+hh;dx,dy=corrections[job*8+dr]
  for scale in [.85/3,1.2/3,1.8/3]:assert abs((320+dx*scale-ax*scale+fx*scale)-320)<.001 and abs((245+dy*scale-ay*scale+fy*scale)-245)<.001
print('PASS all7 first-job/novice bodies x8 directions x3 zooms: visible standing feet meet world contact')
