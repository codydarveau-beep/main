# GPL-3.0-or-later. Preserve all source prerequisite edges, scoped by current class.
from pathlib import Path
import json
r=Path(__file__).resolve().parent;j=json.loads((r/'class_skill_audit48.json').read_text())['classes'];mapping={'WZ_ESTIMATION':83,'WZ_EARTHSPIKE':81,'WZ_HEAVENDRIVE':4,'AL_CURE':50,'AL_DP':11,'AL_DEMONBANE':42,'AL_HEAL':10,'SM_ENDURE':28,'MG_FIREBOLT':3,'MG_COLDBOLT':9,'MG_LIGHTNINGBOLT':21,'MG_STONECURSE':49,'MG_FIREWALL':31,'MG_FROSTDIVER':29,'MG_NAPALMBEAT':22,'MG_SIGHT':36,'MG_THUNDERSTORM':30}
for file in ['second-skills43.json','new_class_skills48.json']:
 for q in json.loads((r/file).read_text()):mapping[q['key']]=q['id']
rows=[]
for name,job in [('Wizard',9),('Sage',10),('Crusader',11)]:
 for q in j[name]:
  id=mapping[q['key']]
  if id in [122,123]:continue
  for key,rank in q['prerequisites'].items():rows.append((job,id,mapping[key],rank))
out='/* Source Hercules pre-renewal class trees; every prerequisite edge, class-scoped. */\nstatic const unsigned char classPrereqs48[][4]={\n'+''.join('{%d,%d,%d,%d},\n'%x for x in rows)+'};\n'
out+='''static int class_has_tree48(unsigned job,unsigned id){if(job==8)job=9;for(unsigned i=0;i<sizeof(classPrereqs48)/sizeof(*classPrereqs48);i++)if(classPrereqs48[i][0]==job&&classPrereqs48[i][1]==id)return 1;return 0;}
static int class_missing_prereq48(unsigned job,unsigned id,const unsigned char*r){if(job==8)job=9;for(unsigned i=0;i<sizeof(classPrereqs48)/sizeof(*classPrereqs48);i++){const unsigned char*p=classPrereqs48[i];if(p[0]==job&&p[1]==id&&r[skill_rank_index(p[2])]<p[3])return i+1;}return 0;}
static int class_valid_prereqs48(unsigned job,const unsigned char*r){for(unsigned i=0;i<LEARN_COUNT;i++)if(r[i]&&class_missing_prereq48(job,learnIds[i],r))return 0;return 1;}
'''
(r/'class_prereqs48.h').write_text(out);print('Imported',len(rows),'source prerequisite edges')
