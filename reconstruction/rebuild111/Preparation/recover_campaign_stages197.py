"""Recover both authored stage tables, preserving every field and pointer string.
This is data recovery, not authorization to enable incomplete chapter runtime.
"""
from pathlib import Path
import struct,json,hashlib
R=Path(__file__).resolve().parent.parent;x=(R.parent/'packet194/released-default.xbe').read_bytes()
# Exact instruction references prove the table bounds and 128-byte stride.
assert x[0x2b4ce-0x10000:0x2b4ce-0x10000+10]==bytes.fromhex('bac8075c00be21000000')
assert x[0x2b561-0x10000:0x2b561-0x10000+6]==bytes.fromhex('8d9148185c00')
def string(p):
 assert 0x11000<=p<len(x)+65536
 a=p-65536;b=x.index(b'\0',a);assert b-a<128
 return x[a:b].decode('utf-8')
def table(va,count):
 rows=[]
 for i in range(count):
  at=va-65536+i*128;cursor,mapid,n=struct.unpack_from('<3I',x,at);assert 3<=cursor<36 and mapid<497 and 0<=n<=4
  actors=[]
  for j in range(n):
   actor,xx,yy,p=struct.unpack_from('<IffI',x,at+28+j*16);assert actor<45;actors.append(dict(source=actor,x=xx,y=yy,name=string(p)))
  rows.append(dict(cursor=cursor,map=mapid,count=n,position=struct.unpack_from('<2f',x,at+12),document=struct.unpack_from('<2f',x,at+20),actors=actors,trailing=struct.unpack_from('<9I',x,at+92),recordSHA256=hashlib.sha256(x[at:at+128]).hexdigest()))
 return rows
later=table(0x5c07c8,33);fallback=table(0x5c1848,9)
assert [r['cursor']for r in fallback]==list(range(3,12))
assert set(r['cursor']for r in later)=={9,11,*range(12,36)}
# Runtime lookup reads trailing[7] as required-objective mask and trailing[8]
# as exclusion mask. Other fields remain explicitly raw until their consumers
# have been reconciled; the record storage never invents encounter semantics.
def emit(name,rows):
 out=['static const CampaignStageDefinition200 '+name+'[]={']
 for r in rows:
  actors=['{%du,%sf,%sf,%s}'%(a['source'],repr(a['x']),repr(a['y']),json.dumps(a['name']))for a in r['actors']]
  vals=[str(r[k])+'u'for k in ['cursor','map','count']]+[repr(v)+'f'for v in (*r['position'],*r['document'])]
  out.append(' {'+','.join(vals)+',{'+','.join(actors)+'},{'+','.join(str(v)+'u'for v in r['trailing'])+'}},')
 return '\n'.join(out+['};'])
header='/* Exact authored records from preserved released executable; generated. */\n#ifndef MYRO_CAMPAIGN_STAGE_DATA197_H\n#define MYRO_CAMPAIGN_STAGE_DATA197_H\n'+emit('campaignStages200',fallback)+'\n'+emit('campaignLaterStages197',later)+'\n#endif\n'
(R/'Source/campaign_stage_data197.h').write_text(header)
report=dict(executableSHA256=hashlib.sha256(x).hexdigest(),stride=128,earlier=dict(tableVA='0x5c1848',rows=fallback),later=dict(tableVA='0x5c07c8',rows=later),confirmedConsumers=dict(bindVA='0x2b4c9',requiredObjectiveFieldOffset=120,excludedObjectiveFieldOffset=124),activationChanged=False,scope='Complete records recovered; later runtime interactions/encounters still require integration and checks')
(R/'Preparation/Campaign-Stages-Recovery197.json').write_text(json.dumps(report,indent=2)+'\n')
print('Recovered both complete stage tables with authored positions, actors, raw encounter/objective fields and exact record digests. Activation unchanged.')
