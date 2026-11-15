"""Recover exact per-character/per-career learning queues, not generic skill kits."""
from pathlib import Path
import struct,json,hashlib
R=Path(__file__).resolve().parent.parent;x=(R.parent/'packet194/released-default.xbe').read_bytes()
ids=struct.unpack_from('<401H',x,0x2ca702-65536);caps=x[0x2ca570-65536:0x2ca570-65536+401];rows=[]
assert len(set(ids))==401 and max(ids)<444 and max(caps)<=10
for i in range(36):
 at=0x2caa24-65536+i*338;identity,job,start,count=struct.unpack_from('<4B',x,at);queue=struct.unpack_from('<167H',x,at+4)
 assert identity<19 and job<46 and count<=167 and max(queue)<401
 rows.append(dict(identity=identity,job=job,start=start,count=count,queue=queue))
assert len({(r['identity'],r['job'])for r in rows})==36
p=R/'Source/companion_skills_data201.h'
p.write_text('/* Original authored skill queues and rank limits, generated from native tables. */\n#ifndef MYRO_COMPANION_SKILLS_DATA201_H\n#define MYRO_COMPANION_SKILLS_DATA201_H\ntypedef struct{unsigned char id,job,start,count;unsigned short queue[167];}PartySkillPath201;\nstatic const unsigned short partySkillIDs201[401]={'+','.join(map(str,ids))+'};\nstatic const unsigned char partySkillCaps201[401]={'+','.join(map(str,caps))+'};\nstatic const PartySkillPath201 partySkillPaths201[36]={\n'+''.join('{'+','.join(str(r[k])for k in ['identity','job','start','count'])+',{'+','.join(map(str,r['queue']))+'}},\n'for r in rows)+'};\n#endif\n')
(R/'Preparation/Companion-Skills-Recovery201.json').write_text(json.dumps(dict(sourceSHA256=hashlib.sha256(p.read_bytes()).hexdigest(),skillIDsVA='0x2ca702',rankCapsVA='0x2ca570',pathsVA='0x2caa24',stride=338,paths=rows,scope='Exact authored learning data. Career combat choices/effects still require faithful runtime integration.'),indent=2)+'\n')
print('Recovered original companion skill queues for starting and promoted careers.')
