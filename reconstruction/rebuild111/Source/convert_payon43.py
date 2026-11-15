# MIT. Appends source-defined Payon route resources; keeps baseline bytes intact.
from pathlib import Path
import sys,struct,zlib,json,re,glob,importlib,hashlib
import convert_world as cw
ROOT=Path(__file__).resolve().parent.parent
INPUT=ROOT.parent/'asset-library/Payon43-return'
NEW=['moc_fild01','moc_fild02','moc_fild03','pay_fild01','payon','pay_arche']+['pay_dun0'+str(i)for i in range(5)]
LABEL=['Morroc Border','Sograt Desert 2','Sograt Desert 3','Payon Forest','Payon','Archer Village']+['Payon Cave '+str(i+1)for i in range(5)]
cw.MAPS+=NEW;cw.LABELS+=LABEL
assets={str(p.relative_to(INPUT)).replace('/','\\').lower():p.read_bytes()for p in (INPUT/'data').rglob('*')if p.is_file()}
paths=sorted(glob.glob('/workspace/attachments/*/RO-Payon-Assets43-20261021-001107-f6b503-part*.zip'))
base=(ROOT.parent/'test42/Source/world_data.h').read_text();raw=(ROOT.parent/'test42/Packed/world.bin').read_bytes();data=bytearray(raw);rows=[];reports=[]
for name in NEW:
 out=ROOT/'WorldAssets'/name;out.mkdir(parents=True,exist_ok=True);(out/'Source').mkdir(exist_ok=True)
 if not (out/'geometry.bin').exists():rep=cw.ground(assets,name,out);(out/'terrain-report.json').write_text(json.dumps(rep))
 else:rep=json.loads((out/'terrain-report.json').read_text())
 if not (out/'SceneryAssets/instances.bin').exists():cw.convert_scenery.convert(paths,out,map_names=[name],texture_limit=128)
 row=[]
 for p in [out/n for n in ['atlas.bin','walk.bin','spawn.bin','geometry.bin']]+[out/'SceneryAssets'/n for n in ['atlas.bin','mesh.bin','instances.bin']]:
  b=p.read_bytes();cp=zlib.compress(b,9);row.append([len(data),len(cp),len(b),zlib.crc32(cp)]);data+=cp
 rep['sections']=row;rep['resident_raw']=sum(x[2]for x in row);reports.append(rep);rows.append(row);print('APPENDED',name,len(data),rep['resident_raw'],flush=True)
(ROOT/'Packed/world.bin').write_bytes(data)
s=base.replace('#define WORLD_MAP_COUNT 7','#define WORLD_MAP_COUNT 18').replace('#define WORLD_FILE_BYTES 22896465','#define WORLD_FILE_BYTES '+str(len(data))).replace('worldBlobs[7][7]','worldBlobs[18][7]')
a=s.index('static const WorldBlob');b=s.index('static void world_blob_init',a);table=s[a:b];table=table.rstrip().removesuffix('};')+',\n'+',\n'.join('{'+','.join('{'+','.join(map(str,x))+'}'for x in row)+'}'for row in rows)+'};\n';s=s[:a]+table+s[b:]
for key,extra in [('mapLabels',LABEL),('mapNames',NEW),('mapWidths',[x['width']for x in reports]),('mapHeights',[x['height']for x in reports])]:
 m=re.search(key+r'\[\]=\{([^}]+)\}',s);s=s[:m.end(1)]+','+','.join(json.dumps(x)for x in extra)+s[m.end(1):]
warps=(INPUT/'server/npc/pre-re/warps/selected-payon.txt').read_text();gates=[]
for line in warps.splitlines():
 m=re.match(r'\s*(\w+),(\d+),(\d+),\d+\s+warp\s+\S+\s+(\d+),(\d+),(\w+),(\d+),(\d+)',line)
 if not m:continue
 src,x,y,rx,ry,dst,dx,dy=m.groups()
 if src not in cw.MAPS or dst not in cw.MAPS or src==dst:continue
 row=[cw.MAPS.index(src),int(x)*8+4,int(y)*8+4,max(1,int(rx))*8+8,max(1,int(ry))*8+8,cw.MAPS.index(dst),int(dx)*8+4,int(dy)*8+4]
 line='{'+','.join(map(str,row))+'},';
 if line not in s and line not in gates:gates.append(line)
# The fifth-floor script chooses one of four authenticated destinations at runtime.
gates.append('{%d,%d,%d,24,24,%d,1612,1636},'%(cw.MAPS.index('pay_dun03'),127*8+4,62*8+4,cw.MAPS.index('pay_dun04')))
pos=s.index('};',s.index('static const WorldGate worldGates'));s=s[:pos]+'\n'.join(gates)+'\n'+s[pos:];(ROOT/'Source/world_data.h').write_text(s)
(ROOT/'PAYON-CONVERSION43.json').write_text(json.dumps({'maps':reports,'new_gates':gates,'baseline_bytes':len(raw),'world_bytes':len(data),'world_sha256':hashlib.sha256(data).hexdigest()},indent=2))
print('PASS prefix preserved',len(raw),'worldbytes',len(data))
