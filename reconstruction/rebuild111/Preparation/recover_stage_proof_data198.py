from pathlib import Path
import struct,json,hashlib
R=Path(__file__).resolve().parent.parent;x=(R.parent/'packet194/released-default.xbe').read_bytes()
s=(R/'Source/campaign_stage_rules198.h').read_text();import re
addresses={int(a,16)for a in re.findall(r'0x[ab][0-9a-f]{5}\b',s)}
early=struct.unpack_from('<3I',x,0x5dcd80+110*4-65536);addresses.update(early)
prompts=struct.unpack_from('<3I',x,0x7472b4+110*4-65536);addresses.update(prompts);addresses.update([0xaa7437,0xa55aca,0xa48c05])
wrong=[0xb514de,0xb50d66,0xb50e90];addresses.update(wrong)
gates=struct.unpack_from('<36I',x,0x5c0738-65536);order=struct.unpack_from('<9I',x,0x748150-65536)
lines=['/* Exact released gates, order and feedback strings; generated. */','#ifndef MYRO_CAMPAIGN_STAGE_PROOF_DATA198_H','#define MYRO_CAMPAIGN_STAGE_PROOF_DATA198_H','static const unsigned campaignStageGates198[36]={'+','.join(str(v)+'u'for v in gates)+'};','static const unsigned campaignStageOrder198[3][3]={'+','.join('{'+','.join(map(str,order[i:i+3]))+'}'for i in range(0,9,3))+'};','static const unsigned campaignStageEarlyMessages198[3]={'+','.join(hex(v)+'u'for v in early)+'};','static const unsigned campaignStageWrongOrder198[3]={'+','.join(hex(v)+'u'for v in wrong)+'};','static const char*campaign_stage_text198(unsigned address){switch(address){']
lines.insert(-1,'static const unsigned campaignStageAnchorPrompts198[3]={'+','.join(hex(v)+'u'for v in prompts)+'};')
for a in sorted(addresses):
 at=a-65536;text=x[at:x.index(b'\0',at)].decode('utf-8');assert len(text)<512;lines.append('case '+hex(a)+'u:return '+json.dumps(text)+';')
lines+=['default:return "";}}','#endif'];(R/'Source/campaign_stage_proof_data198.h').write_text('\n'.join(lines)+'\n')
print('Recovered exact stage gates, route-dependent order and feedback.')
