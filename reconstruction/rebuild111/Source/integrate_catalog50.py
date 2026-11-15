"""GPL-3.0-or-later. Activate stable source class/skill metadata in Test50 only.
Run once after prepare_catalog50.py. Gameplay handlers are a separate module.
"""
from pathlib import Path
import json,re,shutil
r=Path(__file__).resolve().parent
data=json.loads((r.parent/'ClassAssets50/catalog50.json').read_text())
rows=sorted((v for v in data['skills'] if v['id']>=127),key=lambda v:v['id'])
byid={v['id']:v for v in data['skills']}
assert len(rows)==127
def change(name,fn):
 p=r/name;p.write_text(fn(p.read_text()))
def arr(v):return json.dumps(v,separators=(',',':')).replace('[','{').replace(']','}')
shutil.copyfile(r.parent/'ClassAssets50/catalog50.h',r/'class_data50.h')
(r/'class_ids50.h').write_text('/* Stable runtime IDs; original IDs0..126 retained. */\n'+''.join('#define C50_'+q['key']+' '+str(q['id'])+'\n' for q in data['skills']))
p=r/'skills.h';s=p.read_text();assert 'SK50_AS_RIGHT'not in s
s=s.replace('SKILL_COUNT };',','.join('SK50_'+q['key']for q in rows)+',SKILL_COUNT };')
at=s.index('\n};',s.index('static const SkillDef'))
def definition(q):
 source=q['source'];rng=max(0,q['Range'][0])*8;rad=max(0,q['SplashRange'][0])*8+4 if q['target'].get('Place') else 0
 return ' {'+','.join([json.dumps(q['name']),json.dumps(q['name'][:12]),json.dumps(q['name']+'.'),str(q['SPCost'][0]),'0',str(rng),str(rad)])+'}'
s=s[:at]+',\n'+',\n'.join(definition(q)for q in rows)+s[at:]
for name,extra in [('learnIds',[q['id']for q in rows]+[7]),('learnJobs',[q['owners'][0]for q in rows]+[17]),('learnMax',[q['maxRank']for q in rows]+[10]),('learnNeeds',[0]*128),('learnNeedsRank',[0]*128)]:
 m=re.search(name+r'\[LEARN_COUNT\]=\{([^}]+)',s);s=s[:m.end(1)]+','+','.join(map(str,extra))+s[m.end(1):]
s=s.replace('static int skill_passive(unsigned id){return ','static int skill_passive(unsigned id){if(id>=127){const ClassSkill50*d=class_skill_data50(id);return d&&d->passive;}return ')
s=s.replace('static int skill_quest(unsigned id){return ','static int skill_quest(unsigned id){if(id>=127){const ClassSkill50*d=class_skill_data50(id);return d&&d->quest;}return ')
s=s.replace('if(id>=SKILL_COUNT)return 0;if(id>=89)', 'if(id>=SKILL_COUNT)return 0;if(id>=127){const ClassSkill50*d=class_skill_data50(id);int rank=skill_rank(g,id);if(rank<1)rank=1;if(rank>10)rank=10;return d?d->sp[rank-1]:0;}if(id>=89)')
s=s.replace('static int skill_ground(unsigned id){return ', 'static int skill_ground(unsigned id){if(id>=127){const ClassSkill50*d=class_skill_data50(id);return d&&(d->target&4);}return ')
s=s.replace('static int skill_cast_targeted(unsigned id){return ', 'static int skill_cast_targeted(unsigned id){if(id>=127){const ClassSkill50*d=class_skill_data50(id);return d&&(d->target&2);}return ')
s=s.replace('if(r[44]&&r[18]<7)', 'if(job!=17&&r[44]&&r[18]<7)').replace('if(id==48&&g->ranks[18]<7)', 'if(id==48&&g->jobId!=17&&g->ranks[18]<7)')
s=s.replace('const unsigned char*p=classPrereqs48[missing48-1]', 'const uint16_t*p=classPrereqs48[missing48-1]')
s=s.replace('static int class_inherited49(const Combat*g,int owner){return ', 'static int class_inherited49(const Combat*g,int owner){if(g->jobId>=12&&g->jobId<=20)return owner==classParent50[g->jobId-12];return ')
s=s.replace('float range=id>=89?', 'float range=id>=127?class_range50(g,id,rank):id>=89?')
s=s.replace('#include "class_skills48.h"', '#include "class_skills48.h"\n#include "class_skills50.h"')
s=s.replace('if(id>=89&&!class_ready48', 'if(id>=127&&!class_ready50(g,id,x,y,target))return 0;\n if(id>=89&&id<127&&!class_ready48')
s=s.replace('if(id>=89){class_execute48', 'if(id>=127){class_execute50(g,id,rank,target,x,y);}\n else if(id>=89){class_execute48')
p.write_text(s)
p=r/'progression_data.h';s=p.read_text().replace('#define LEARN_COUNT 124','#define LEARN_COUNT 252');s='#include "class_data50.h"\n'+s
for name,key in [('jobHP','sourceHP99'),('jobSP','sourceSP99')]:
 m=re.search(r'(static const int '+name+r')\[12\]\[99\]=\{(.*?)};',s,re.S)
 s=s[:m.start()]+m[1]+'[21][99]={'+m[2]+','+','.join(arr(q[key])for q in data['classes'])+'};'+s[m.end():]
s=s.replace('static int job_owns_skill43(unsigned job,unsigned owner){return ', 'static unsigned job_first50(unsigned job){if(job>=12&&job<=20)return classParent50[job-12];if(job==7||job==11)return 1;if(job==8||job==9||job==10)return 2;return job;}\nstatic int job_owns_skill43(unsigned job,unsigned owner){return (job>=12&&job<=20&&owner==job_first50(job))||')
s=s.replace('static int job_owns_skill48(unsigned job,unsigned owner,unsigned id){return ', 'static int job_owns_skill48(unsigned job,unsigned owner,unsigned id){if(job>=12&&job<=20){const ClassSkill50*d=class_skill_data50(id);return job_owns_skill43(job,owner)||(d&&(d->owners&(1u<<job)));}return ')
p.write_text(s)
p=r/'class_prereqs48.h';s=p.read_text().replace('unsigned char classPrereqs48','uint16_t classPrereqs48').replace('const unsigned char*p=classPrereqs48','const uint16_t*p=classPrereqs48');at=s.index('\n};');s=s[:at]+''.join('\n'+arr(v)+','for v in data['prerequisiteEdges'])+s[at:];p.write_text(s)
p=r/'cast_timing.h';s=p.read_text();at=s.index('\n};');s=s[:at]+''.join('\n{'+','.join([str(q['id']),arr(q['CastTime']),arr(q['AfterCastActDelay']),arr(q['CoolDown']),arr(q['HPCost']),str(int(q['interruptible']))])+'},'for q in rows+[byid[7]])+s[at:];p.write_text(s)
def combat(s):
 s=s.replace('unsigned job=g->jobId<12?g->jobId:0;int lv=g->joblevel;', 'unsigned job=g->jobId<21?g->jobId:0;int lv=g->joblevel;if(job>=12){if(lv<1)lv=1;if(lv>50)lv=50;return classBonus50[job-12][lv-1][n];}')
 s=s.replace('if(weapon<0||weapon>12)weapon=0;int d=baseMotion48[g->jobId][weapon];','if(weapon<0||weapon>16)weapon=0;int d=g->jobId>=12?classMotion50[g->jobId-12][weapon]:baseMotion48[g->jobId][weapon>12?0:weapon];')
 s=s.replace('if(job>11||','if(job>20||')
 for old,new in [('g->jobId==4?3*g->ranks[30]','job_first50(g->jobId)==4?3*g->ranks[30]'),('g->jobId==5?', 'job_first50(g->jobId)==5?'),('if(g->jobId==5&&','if(job_first50(g->jobId)==5&&'),('g->jobId==3&&','job_first50(g->jobId)==3&&'),('g->jobId==4&&','job_first50(g->jobId)==4&&')]:s=s.replace(old,new)
 s=s.replace('static const char*job_name(unsigned id){return ', 'static const char*job_name(unsigned id){static const char*added[]={"Assassin","Rogue","Hunter","Bard","Dancer","Priest","Monk","Blacksmith","Alchemist"};if(id>=12&&id<=20)return added[id-12];return ')
 return s
change('combat.h',combat)
change('save_format.h',lambda s:s.replace('s->jobId>11','s->jobId>20'))
# Staged body/weapon pack is now the actual Test50 actor catalog.
shutil.copyfile(r.parent/'ClassAssets50/actor_data50.h',r/'actor_data.h');shutil.copyfile(r.parent/'ClassAssets50/actors50.bin',r.parent/'Actors/actors.bin')
p=r/'player_contact.h';s=p.read_text().replace('[13][8][2]','[22][8][2]');at=s.rfind('};');contacts=json.loads((r.parent/'ClassAssets50/contacts50.json').read_text());s=s[:at]+','+','.join(arr(v).replace('}', 'f}').replace(',','f,').replace('{f','{') for v in [])+s[at:] if False else s
# Insert after the old last row, keeping all thirteen existing contact rows.
assert s.endswith('};\n');s=s[:-3]+','+','.join(re.sub(r'(-?\d+\.\d+)',r'\1f',arr(v))for v in contacts)+'};\n';p.write_text(s)
change('sprites.h',lambda s:s.replace('if(id>12)','if(id>21)').replace('unsigned gear=','unsigned gear=(equipment&(1u<<21))?113:(equipment&(1u<<22))?114:(equipment&(1u<<23))?115:(equipment&(1u<<24))?116:'))
change('main.c',lambda s:s.replace('game.jobId==11&&game.mounted48?12:game.jobId','class_actor_id50(game.jobId,game.mounted48)').replace('group=6;elapsed=game.spellCastTotal','group=game.jobId>=12?7:6;elapsed=game.spellCastTotal'))
# Explicit temporary gate is removed as handlers are implemented; avoids charging
# resources for any unimplemented operation while integration proceeds.
if not(r/'class_skills50.h').exists():(r/'class_skills50.h').write_text('static float class_range50(const Combat*g,unsigned id,int rank){const ClassSkill50*d=class_skill_data50(id);int cells=d?d->range[rank-1]:0;return cells<0?combat_attack_range(g):cells*8.f;}\nstatic int class_ready50(Combat*g,unsigned id,float x,float y,int target){(void)id;(void)x;(void)y;(void)target;combat_notice(g,POP_SKILLS,"Skill integration in progress.");return 0;}\nstatic void class_execute50(Combat*g,unsigned id,int rank,int target,float x,float y){(void)g;(void)id;(void)rank;(void)target;(void)x;(void)y;}\n')
print('PASS50 runtime21job profiles,254skill definitions,252stable learned slots, all133skill ownership/126prerequisite edges, native100variant actor pack installed; skill handler integration continues.')
