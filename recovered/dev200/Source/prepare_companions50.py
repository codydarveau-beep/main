"""GPL-3.0-or-later. Pinned classic Homunculus and summoned monster numbers."""
from pathlib import Path
import hashlib,json,re
from prepare_catalog50 import parse_group,levels,carray
r=Path(__file__).resolve().parent;ref=r.parent.parent/'reference48'
text=(ref/'test50-homunculus_db.conf').read_text();clean=re.sub(r'/\*.*?\*/|//[^\n]*','',text,flags=re.S)
hom=[]
for block in re.findall(r'(?ms)^\{.*?^\}',clean):
    v=parse_group(re.sub(r'\((\d+),\s*(\d+)\)',r'{ Min: \1 Max: \2 }',block[1:-1]))
    if 6001<=v['Id']<=6016:hom.append(v)
assert [v['Id'] for v in hom]==list(range(6001,6017))
keys=['Hp','Sp','Str','Agi','Vit','Int','Dex','Luk'];rows=[]
for listed in hom:
    # Original db_search matches a base entry or its EvoId, in file order.
    v=next(q for q in hom if listed["Id"] in (q["Id"],q["EvoId"]))
    food={'Pet_Food':537,'Zargon':912,'Garlet':910,'Scell':911}[v['FoodItem']]
    rows.append('{'+','.join([str(listed['Id']),str(v['EvoId']),str(food),str(v['HungryDelay']),str(v['Aspd']),json.dumps(v['Name']),carray([v['BaseStats'][k] for k in keys]),carray([[v['GrowthStats'][k]['Min'],v['GrowthStats'][k]['Max']] for k in keys]),carray([[v['EvolutionStats'][k]['Min'],v['EvolutionStats'][k]['Max']] for k in keys])])+'}')
out='/* GPL-3.0-or-later. Generated from Hercules 21b27966 prere data. */\n'
out+='typedef struct{unsigned id,evolution,food,hungerMS,motion;const char*name;unsigned base[8],growth[8][2],evo[8][2];} HomunData50;\nstatic const HomunData50 homunData50[16]={\n'+',\n'.join(rows)+'};\n'
exptext=(r.parent.parent/'asset-library/Payon43-return/server/db/pre-re/exp_group_db.conf').read_text();exp=list(map(int,re.findall(r'\d+',re.search(r'Homunculus:\s*\{.*?Exp:\s*\[([^]]+)',exptext,re.S)[1])));assert len(exp)==98
out+='static const unsigned homunEXP50[98]='+carray(exp)+';\n'
tree=[]
for line in (ref/'test50-homun_skill_tree.txt').read_text().splitlines():
    if not re.match(r'60(?:0\d|1[0-6]),',line):continue
    a=list(map(int,line.split('//')[0].strip().split(',')));assert len(a) in [14,15]
    if len(a)==15:del a[3]
    tree.append([a[0],a[1]-8001,a[2],*sum(([a[i]-8001 if a[i] else 65535,a[i+1]] for i in range(3,13,2)),[]),a[13]*100])
out+='static const unsigned homunTree50[][14]='+carray(tree)+';\n'
companions=json.loads((r.parent/'ClassAssets50/catalog50.json').read_text())['companions'];skills=[]
for v in companions:
    d=v['source'];req=d.get('Requirements',{});skills.append('{'+','.join([json.dumps(d['Description']),carray(levels(req.get('SPCost'),5)),carray(levels(d.get('SkillData1'),5)),carray(levels(d.get('SkillData2'),5)),carray(levels(d.get('AfterCastActDelay'),5))])+'}')
out+='typedef struct{const char*name;unsigned sp[5],duration[5],block[5],delay[5];} HomunSkill50;\nstatic const HomunSkill50 homunSkill50[16]={\n'+',\n'.join(skills)+'};\n'
mob=(ref/'test50-mob_db.conf').read_text();blocks={int(m[1]):m[0] for m in re.finditer(r'(?ms)^\{\s*Id:\s*(\d+).*?^\}',mob)};summons=[]
for id in [1589,1579,1575,1555,1590,1142]:
    v=blocks[id]
    def n(key):return int(re.search(r'\b'+key+r':\s*(\d+)',v)[1])
    attack=list(map(int,re.search(r'Attack:\s*\[\s*(\d+),\s*(\d+)',v).groups()))
    summons.append([id,n('Hp'),n('AttackRange')*8,*attack,n('Def'),n('Dex'),n('AttackDelay'),n('MoveSpeed')])
out+='static const unsigned summonData50[6][9]='+carray(summons)+';\n'
(r/'companion_data50.h').write_text(out)
(r/'companion_data50.json').write_text(json.dumps(dict(homunculi=hom,exp=exp,tree=tree,skills=companions,summons=summons,sourceCommit='21b27966cfc2e7df0bf8151cd717a1105d047ba9',inputs={str(p.relative_to(r.parent.parent)):hashlib.sha256(p.read_bytes()).hexdigest() for p in [ref/'test50-homunculus_db.conf',ref/'test50-mob_db.conf',ref/'test50-homun_skill_tree.txt']}),indent=2)+'\n')
print('Prepared16 classic profiles,16 skills,98 EXP levels and6 original summons.')
