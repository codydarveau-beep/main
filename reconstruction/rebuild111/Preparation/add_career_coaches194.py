from pathlib import Path
import re,json
R=Path(__file__).resolve().parent.parent;S=R/'Source';p=S/'world_data.h';s=p.read_text();m=re.search(r'(static const WorldGate worldGates\[\]=\{)(.*?)(\};)',s,re.S);assert m
count=len(re.findall(r'\{[^{}]+\}',m[2]));rows=[(2,1148,1380,20,20,126,1204,940),(126,1204,940,20,20,2,1148,1380),(2,1204,1380,20,20,406,300,548),(406,300,548,20,20,2,1204,1380),(2,1260,1380,20,20,406,1108,1340),(406,1108,1340,20,20,2,1260,1380),(126,1324,940,20,20,108,284,2844),(108,284,2844,20,20,126,1300,940)]
body=m[2].rstrip().rstrip(',')+','+','.join('{'+','.join(map(str,r))+'}'for r in rows)
s=s[:m.start()]+m[1]+body+m[3]+s[m.end():];s+='\n#define CAREER_GATE_START194 %du\n'%count;p.write_text(s)
p=S/'world_gate_state64.h';s=p.read_text().replace('static int world_gate_enabled64(unsigned gate){return','static int(*worldCareerGateAvailable194)(unsigned);\nstatic int world_gate_enabled64(unsigned gate){if(gate>=CAREER_GATE_START194&&(!worldCareerGateAvailable194||!worldCareerGateAvailable194(gate)))return 0;return',1);p.write_text(s)
p=S/'campaign_admission_runtime194.h';s=p.read_text();needle='static void campaign_admission_install194(void){';assert needle in s
s=s.replace(needle,'''static int campaign_career_gate194(unsigned gate){
 if(gate<CAREER_GATE_START194)return 1;if(gate>=WORLD_GATE_COUNT)return 0;Campaign200 c;
 if(campaign_load200(questPins65,&c)!=1||c.cursor<1)return 0;
 return gate<CAREER_GATE_START194+6||career_pilgrimage194(questPins65);
}
'''+needle,1);s=s.replace('campaign_admission_reset194();npcTravelAdmission194=','campaign_admission_reset194();worldCareerGateAvailable194=campaign_career_gate194;npcTravelAdmission194=',1);p.write_text(s)
(R/'Preparation/Career-Coaches194.json').write_text(json.dumps({'firstGateIndex':count,'rows':rows,'source':'Retained packet section 7; original gate indices unchanged','visibility':'cursor >= 1; last two also require native pilgrimage proof'},indent=2)+'\n')
print('Appended eight retained coach passages without changing any original gate index')
