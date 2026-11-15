# GPL-3.0-or-later. Import complete source skill trees for new second classes.
from pathlib import Path
import re,json
r=Path(__file__).resolve().parent;j=json.loads((r/'class_skill_audit48.json').read_text())['classes'];existing={'WZ_ESTIMATION':83,'WZ_EARTHSPIKE':81,'WZ_HEAVENDRIVE':4,'AL_CURE':50,'AL_DP':11,'AL_DEMONBANE':42,'AL_HEAL':10};existing.update({x['key']:x['id']for x in json.loads((r/'second-skills43.json').read_text())});existing.update({'SM_ENDURE':28,'MG_FIREBOLT':3,'MG_COLDBOLT':9,'MG_LIGHTNINGBOLT':21,'MG_STONECURSE':49,'MG_FIREWALL':31,'MG_FROSTDIVER':29,'MG_NAPALMBEAT':22,'MG_SIGHT':36,'MG_THUNDERSTORM':30})
rows=[]
for job,owner in [('Wizard',9),('Sage',10),('Crusader',11)]:
 for q in j[job]:
  if q['key'] in existing:continue
  q=dict(q,id=89+len(rows),owner=owner);rows.append(q);existing[q['key']]=q['id']
assert len(rows)==38 and max(x['id']for x in rows)<128
# Parse rank-value dictionaries with carry-forward semantics for missing ranks.
def vals(b,key):
 m=re.search(r'\b'+key+r':\s*(\{[^}]*\}|\d+)',b)
 if not m:return [0]*10
 if m[1].isdigit():return [int(m[1])]*10
 v={int(a):int(b)for a,b in re.findall(r'Lv(\d+):\s*(\d+)',m[1])};return [v.get(k,0)for k in range(1,11)]
for q in rows:
 raw=q['source'];q['name']=re.search(r'\bDescription:\s*"([^"]+)"',raw)[1];q['sp']=vals(raw,'SPCost');q['cast']=vals(raw,'CastTime');q['delay']=vals(raw,'AfterCastActDelay');q['cooldown']=vals(raw,'CoolDown');q['passive']=not re.search(r'\bSkillType:',raw);q['prerequisites']={k:v for k,v in q['prerequisites'].items()if k in existing};q['needs']=[(existing[k],v)for k,v in q['prerequisites'].items()]
(r/'new_class_skills48.json').write_text(json.dumps(rows,indent=2));print('PASS source audit38 new skill definitions fit89..126; serialization expansion still required before integration')
