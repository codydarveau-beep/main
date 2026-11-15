"""Restore exact authored journal directions from the preserved native table."""
from pathlib import Path
import struct,json,hashlib
R=Path(__file__).resolve().parent.parent;x=(R.parent/'packet194/released-default.xbe').read_bytes()
def string(va):
 at=va-65536;assert 0<=at<len(x);end=x.index(0,at);assert end-at<2048
 return x[at:end].decode('utf-8')
rows=[]
for i in range(36):
 a,b=struct.unpack_from('<2I',x,0x5dd184-65536+i*8);title,objective=string(a),string(b)
 assert title and objective and 'Destination will be supplied' not in objective
 rows.append(dict(cursor=i,title=title,objective=objective,titleVA=hex(a),objectiveVA=hex(b)))
p=R/'Source/campaign_data200.h'
p.write_text('/* Exact authored journal table recovered from preserved native code. */\n#ifndef MYRO_CAMPAIGN_DATA200_H\n#define MYRO_CAMPAIGN_DATA200_H\ntypedef struct{const char*title,*objective;}CampaignQuest200;\nstatic const CampaignQuest200 campaignQuests200[]={\n'+''.join('{'+json.dumps(r['title'],ensure_ascii=True)+','+json.dumps(r['objective'],ensure_ascii=True)+'},\n'for r in rows)+'};\n#include "campaign_objectives200.h"\n#endif\n')
(R/'Preparation/Campaign-Journal-Recovery200.json').write_text(json.dumps(dict(tableVA='0x5dd184',rows=rows,scope='Exact native static journal directions; existing objective-sensitive early guidance remains layered above this table.',sourceSHA256=hashlib.sha256(p.read_bytes()).hexdigest(),activationChanged=False),indent=2)+'\n')
print('Restored exact authored journal directions for all campaign records; activation unchanged.')
