"""Extract original Kafra display-name -> map branches from released bytecode."""
from pathlib import Path
import json,struct
ROOT=Path(__file__).resolve().parent.parent
P=ROOT.parent/'packet194'
programs=json.loads((P/'released-program-index.json').read_text())
wire=(P/'released-scripts.bin').read_bytes()
maps=json.loads((P/'RecoveredMetadata/released-map-names.json').read_text())
p=programs[843];raw=wire[p['offset']:p['offset']+p['bytes']]
nc,ns,nl,nf=struct.unpack_from('<4I',raw,16)
pool=raw[40+nc*12+(nl+nf)*8:]
def text(at):return pool[at:pool.index(0,at)].decode()
code=[struct.unpack_from('<III',raw,40+i*12)for i in range(nc)]
routes={}
for pc,(op,a,argc)in enumerate(code):
 if op!=12 or text(a)!='warp':continue
 assert argc==3 and code[pc-3][0]==2 and code[pc-2][0]==code[pc-1][0]==1
 name=text(code[pc-3][1]);assert name in maps
 labels=[text(code[i][1])for i in range(max(0,pc-30),pc-3)if code[i][0]==2 and code[i+1][:2]==(9,12)]
 assert labels,pc
 label=labels[-1];mid=maps.index(name)
 assert label not in routes or routes[label]==mid
 routes[label]=mid
assert len(routes)==15 and routes['Morroc']==127
out='/* MIT. Derived from deployed F_KafTele branches; no native script edits. */\n#ifndef MYRO_NPC_TRAVEL_DATA194_H\n#define MYRO_NPC_TRAVEL_DATA194_H\n'
out+='static const struct{const char*label;unsigned map;}npcTravelRoutes194[]={'+','.join('{'+json.dumps(k)+','+str(v)+'u}'for k,v in sorted(routes.items()))+'};\n#endif\n'
(ROOT/'Source/npc_travel_data194.h').write_text(out)
(ROOT/'Preparation/Native-Travel-Routes194.json').write_text(json.dumps(routes,indent=2)+'\n')
print('Extracted',len(routes),'native route labels')
