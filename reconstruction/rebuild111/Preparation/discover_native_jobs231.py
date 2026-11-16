"""Locate actual released job-changing scripts for gameplay context checks."""
from pathlib import Path
import re,json,struct
R=Path(__file__).resolve().parent.parent
s=(R/'Source/npc_registry_data55.h').read_text();f=dict((n,int(i))for n,i in re.findall(r'\{"([^"]+)",(\d+)u\}',s[s.index('npcFunctions55[]'):]))
p=json.loads((R.parent/'packet194/released-program-index.json').read_text());wire=(R.parent/'packet194/released-scripts.bin').read_bytes();jobnames={n for n,i in f.items() if i==4};jobs={i['id'] for i in p if 'jobchange' in i['calls']};related=[]
for row in p:
 raw=wire[row['offset']:row['offset']+row['bytes']];nc,ns,nl,nf=struct.unpack_from('<4I',raw,16);pool=raw[40+nc*12+(nl+nf)*8:];code=[struct.unpack_from('<III',raw,40+i*12)for i in range(nc)];texts={pool[a:pool.index(0,a)].decode(errors='replace')for op,a,b in code if op==2}
 if texts&jobnames:related.append(row['id']);jobs.add(row['id'])
maps=json.loads((R.parent/'packet194/RecoveredMetadata/released-map-names.json').read_text());policy=json.loads((R/'Preparation/Map-Policy194.json').read_text())['maps'];deps=json.loads((R/'Preparation/NPC-Dependencies194.json').read_text())['programs'];output=[]
for l in s.splitlines():
 if not l.startswith('{'):continue
 a=l.split(',',12)
 if len(a)!=13 or not a[1].isdigit() or int(a[1])not in jobs:continue
 mid=int(a[2]);program=int(a[1]);name=a[12].split(',')[0].strip('"');refs=deps[program-1]['references'];output.append(dict(npc=int(a[0][1:])-1,name=name,program=program,map=mid,mapName=maps[mid] if mid<len(maps) else 'helper',mapMinimum=policy[mid]['minimumCursor'] if mid<len(maps) else None,dependencies=refs))
(R/'Validation/native-job-paths231.json').write_text(json.dumps(dict(programs=sorted(jobs),npcs=output,scope='Discovery for actual NPC/path integration, not a quest playthrough acceptance'),indent=2)+'\n')
print('Native job helper:',jobnames,'direct/helper programs',len(jobs),'NPCs',len(output));print([(r['name'],r['mapName'],r['mapMinimum'])for r in output if r['map']<495])
