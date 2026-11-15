from pathlib import Path
import re,struct,zlib,json,collections,math
B=Path('/workspace/myro/dev200');s=(B/'Source/world_data.h').read_text();m=re.search(r'worldBlobs\[WORLD_MAP_COUNT\]\[7\]=\{(.*?)\};',s,re.S);rows=[tuple(map(int,x))for x in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',m[1])];assert len(rows)==494*7
with (B/'Packed/world.bin').open('rb')as f:
 at,n,raw,crc=rows[1];f.seek(at);packed=f.read(n);assert zlib.crc32(packed)==crc;data=zlib.decompress(packed);assert len(data)==raw
w,h=struct.unpack_from('<II',data);walk=data[8:8+w*h];surfaces=struct.unpack_from('<I',data,8+w*h)[0];at=12+w*h+surfaces*12;propcount=struct.unpack_from('<I',data,at)[0];props={struct.unpack_from('<I',data,at+4+i*8)[0]for i in range(propcount)}
# Native positions use8 units per collision cell. Avoid all prop subcells conservatively.
def clear(x,y):return 0<=x<w and 0<=y<h and walk[y*w+x]==1 and y*w+x not in props
reference=(1364,3028);cx,cy=1460//8,2804//8
assert all(clear(cx+dx,cy+dy)for dy in range(-3,4)for dx in range(-3,4))
start=(reference[0]//8,reference[1]//8);q=collections.deque([start]);seen={start};found=False
while q:
 x,y=q.popleft()
 if(x,y)==(cx,cy):found=True;break
 for dx,dy in [(1,0),(-1,0),(0,1),(0,-1)]:
  p=x+dx,y+dy
  if p not in seen and clear(*p):seen.add(p);q.append(p)
assert found
proof=dict(map='prt_fild08',mapID=0,reference='Existing Prontera gate',gate=list(reference),candidateCenter=[cx*8+4,cy*8+4],clearAreaCells=[7,7],reachableOnCollisionGrid=True,avoidsSolidPropRecords=True,validationRemaining=['Rendered scenery/camera review','Height/slope and exact actor radius checks','NPC and gate interaction clearance','Real controller playthrough'],activated=False)
(B/'Preparation/Opening-Placement200.json').write_text(json.dumps(proof,indent=2));print(json.dumps(proof,indent=2))
