# GPL-3.0-or-later. Integrate supplied second-class skill metadata; run once on foundation48.
from pathlib import Path
import re,json,runpy
r=Path(__file__).resolve().parent;rows=json.loads((r/'new_class_skills48.json').read_text());p=r/'skills.h';s=p.read_text();assert 'SK48_WZ_ICEWALL'not in s
s=s.replace('SKILL_COUNT };',','.join('SK48_'+q['key']for q in rows)+',SKILL_COUNT };')
a=s.index('\n};',s.index('static const SkillDef'))
def val(b,k):
 m=re.search(r'\b'+k+r':\s*(\{[^}]*\}|\d+)',b)
 if not m:return [0]*10
 if m[1].isdigit():return [int(m[1])]*10
 d={int(a):int(b)for a,b in re.findall(r'Lv(\d+):\s*(\d+)',m[1])};return [d.get(k,0)for k in range(1,11)]
def rowdef(q):
 raw=q['source'];range=val(raw,'Range')[0]*8;radius=20 if q['id']==89 else 28 if q['id']in[101,102,103]else 44 if q['id']==104 else 24 if q['id']==121 else 0
 return ' {'+','.join(json.dumps(v)for v in [q['name'],q['name'][:12],q['key']+': '+q['name']+'. Source pre-renewal rank and costs.',q['sp'][0],0,range,radius])+'}'
s=s[:a]+('\n'if s[:a].rstrip().endswith(',')else',\n')+',\n'.join(rowdef(q)for q in rows)+s[a:]
for name,vals in [('learnIds',[q['id']for q in rows]),('learnJobs',[q['owner']for q in rows]),('learnMax',[q['maxRank']for q in rows]),('learnNeeds',[0]*38),('learnNeedsRank',[0]*38)]:
 m=re.search(name+r'\[LEARN_COUNT\]=\{([^}]+)',s);s=s[:m.end(1)]+','+','.join(map(str,vals))+s[m.end(1):]
passives=[q['id']for q in rows if q['passive']];ground=[q['id']for q in rows if re.search(r'\bPlace:\s*true',q['source'])];target=[q['id']for q in rows if re.search(r'\bEnemy:\s*true',q['source'])];quest=[q['id']for q in rows if re.search(r'\bQuest:\s*true',q['source'])]
for name,ids in [('skill_passive',passives),('skill_ground',ground),('skill_cast_targeted',target),('skill_quest',quest)]:
 prefix='static int '+name+'(unsigned id){return ';assert prefix in s;s=s.replace(prefix,prefix+''.join('id==%d||'%v for v in ids))
costs='static const unsigned short classCosts48[38][10]='+json.dumps([q['sp']for q in rows]).replace('[','{').replace(']','}')+';\n'
s=s.replace('static int skill_cost(',costs+'static int skill_cost(').replace('if(id>=SKILL_COUNT)return 0;if(id>=69)','if(id>=SKILL_COUNT)return 0;if(id>=89){int rank=skill_rank(g,id);if(rank<1)rank=1;return classCosts48[id-89][rank-1];}if(id>=69)')
p.write_text(s)
p=r/'progression_data.h';s=p.read_text().replace('#define LEARN_COUNT 86','#define LEARN_COUNT 124');s+='\nstatic int job_owns_skill48(unsigned job,unsigned owner,unsigned id){return job_owns_skill43(job,owner)||(job==10&&(id==4||id==81||id==83))||(job==11&&(id==10||id==11||id==42||id==50));}\n';p.write_text(s)
# All rank-table ownership consumers must include the actual skill, not grant another whole class.
for p in r.glob('*.h'):
 s=p.read_text();s=re.sub(r'job_owns_skill43\(([^,()]+),learnJobs\[([^]]+)\]\)',r'job_owns_skill48(\1,learnJobs[\2],learnIds[\2])',s);p.write_text(s)
p=r/'cast_timing.h';s=p.read_text();a=s.index('\n};');extra=[]
for q in rows:
 raw=q['source'];extra.append('{%d,%s,%s,%s,%s,%d},'%(q['id'],*['{'+','.join(map(str,val(raw,k)))+'}'for k in ['CastTime','AfterCastActDelay','CoolDown','HPCost']],bool(re.search(r'InterruptCast:\s*true',raw))))
s=s[:a]+'\n'+'\n'.join(extra)+s[a:];p.write_text(s)
p=r/'save_format.h';s=p.read_text();s=s.replace('save_put(p+4092,save_crc(p,4092));','memcpy(p+2700,s->ranks,LEARN_COUNT);memcpy(p+2840,s->useRanks45,LEARN_COUNT);save_put(p+4092,save_crc(p,4092));');s=s.replace('if(!save_valid(&t))return 0;*s=t;return 1;','memcpy(t.ranks,p+2700,LEARN_COUNT);memcpy(t.useRanks45,p+2840,LEARN_COUNT);if(!save_valid(&t))return 0;*s=t;return 1;');p.write_text(s)
(r/'class_ids48.h').write_text('/* Source skill IDs within existing byte binding namespace. */\n'+''.join('#define C48_'+q['key']+' '+str(q['id'])+'\n'for q in rows))
print('PASS124 learnable skills,127skill definitions, source costs/timings, source class membership, nonoverlapping Save48 ranks')
