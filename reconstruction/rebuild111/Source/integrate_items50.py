"""GPL-3.0-or-later. Append source crafting/reagent/weapon items, stable old IDs.
Only parses source scripts for literal healing/base MATK values; never executes.
"""
from pathlib import Path
import re,json
from prepare_catalog50 import levels
r=Path(__file__).resolve().parent
src=(r.parent.parent/'asset-library/Test50-second-classes/server/db/pre-re/item_db.conf').read_text()
db={int(m[1]):m[2]for m in re.finditer(r'(?ms)^\{\s*Id:\s*(\d+)\s*(.*?)^\},?\s*$',src)}
def value(block,key,default=0):
 m=re.search(r'(?m)^\s*'+key+r':\s*("[^\n"]*"|\d+)',block)
 return json.loads(m[1])if m and m[1].startswith('"')else int(m[1])if m else default
bykey={value(b,'AegisName'):i for i,b in db.items()}
catalog=json.loads((r.parent/'ClassAssets50/catalog50.json').read_text());audit=json.loads((r/'class_materials_audit50.json').read_text())
p=r/'inventory.h';s=p.read_text();a=s.index('static const ItemDef');b=s.index('\n};',a)
entries=[json.loads('['+m[1]+']')for m in re.finditer(r'\{([^{}]+)\}',s[a:b])];assert len(entries)>=115
sourceids=[v[0]for v in entries];wanted=set(map(int,audit['items']));wanted.update([1771,1010,1011,756,757,969,714,986,987,988,989,12040])
for v in catalog['skills']:
 for key in v['items']:wanted.add(bykey[key])
newids=sorted(wanted-set(sourceids));assert len(entries)+len(newids)<=256
jobs=['Novice','Swordsman','Magician','Acolyte','Thief','Archer','Merchant','Knight','Wizard','Wizard','Sage','Crusader']+[v['name']for v in catalog['classes']]
wtypes={'W_DAGGER':1,'W_1HSWORD':2,'W_2HSWORD':3,'W_1HSPEAR':4,'W_2HSPEAR':5,'W_1HAXE':6,'W_2HAXE':7,'W_MACE':8,'W_STAFF':9,'W_BOW':10,'W_BOOK':11,'W_2HSTAFF':12,'W_KNUCKLE':13,'W_MUSICAL':14,'W_WHIP':15,'W_KATAR':16}
bits={1:1,2:64,3:32,4:128,5:256,6:512,7:1024,8:2048,9:4096,10:16,11:8192,12:4096,13:1<<21,14:1<<22,15:1<<23,16:1<<24}
def permission(block,wtype):
 j=re.search(r'(?s)\bJob:\s*\{(.*?)\}',block);mask=0
 for i,name in enumerate(jobs):
  # Hercules maps Bard and Dancer onto the same ordinary job permission bit.
  if name=='Dancer':name='Bard'
  if not j or(re.search(r'\bAll:\s*true',j[1])and not re.search(r'\b'+name+r':\s*false',j[1]))or re.search(r'\b'+name+r':\s*true',j[1]):mask|=1<<i
 if wtype==14:mask&=~(1<<16)
 if wtype==15:mask=(mask&~(1<<15))|((1<<16)if(mask&(1<<15))else 0)
 return mask
for e in entries:
 if len(e)>=14 and e[7]and e[0]in db:e[8]=permission(db[e[0]],e[11])
 e.extend([0]*(17-len(e)))
 if e[0]in db:e[16]=value(db[e[0]],'WeaponLv')
def heal(block):
 m=re.search(r'itemheal\s+(rand\(\s*\d+\s*,\s*\d+\s*\)|\d+)\s*,\s*(rand\(\s*\d+\s*,\s*\d+\s*\)|\d+)',block)
 def pair(v):
  n=list(map(int,re.findall(r'\d+',v)));return n if len(n)==2 else n*2
 return (*pair(m[1]),*pair(m[2]))if m else(0,0,0,0)
weights=list(map(int,re.search(r'itemWeights\[ITEM_COUNT\]=\{([^}]+)',s)[1].split(',')))
for id in newids:
 block=db[id];name=value(block,'Name');typ=value(block,'Type','IT_ETC');w=wtypes.get(value(block,'Subtype',''),0);attack=value(block,'Atk');defense=value(block,'Def');hp1,hp2,sp1,sp2=heal(block)
 loc=value(block,'Loc','');slot=0;bit=bits.get(w,0)if typ=='IT_WEAPON'else 0
 if typ=='IT_ARMOR':raise AssertionError(('Unexpected new armour',id))
 matk=re.search(r'bonus bMatkRate,\s*(\d+)',block);matk=int(matk[1])if matk else 0
 description=('ATK %d. '%attack if attack else '')+('Restores HP and SP. 'if hp1 and sp1 else'Restores HP. 'if hp1 else'Restores SP. 'if sp1 else'')+('Two-handed weapon.'if w in [3,5,7,10,12,16]else'Weapon.'if w else'Crafting material or skill reagent.')
 entries.append([id,name,description,hp1,hp2,attack,defense,bit,permission(block,w)if bit else 0,value(block,'EquipLv',1),slot,w,int(w in [3,5,7,10,12,16]),matk,sp1,sp2,value(block,'WeaponLv')]);weights.append(value(block,'Weight'))
old_end=b+3;s=s[:a]+'static const ItemDef itemDefs[ITEM_COUNT]={\n'+',\n'.join('{'+','.join(json.dumps(v,ensure_ascii=False)for v in e)+'}'for e in entries)+'\n};'+s[old_end:]
s=s.replace('unsigned equipBit,jobs,minLevel,slot,wtype,twoHand,matk;', 'unsigned equipBit,jobs,minLevel,slot,wtype,twoHand,matk,spMin,spMax,weaponLv;')
s=re.sub(r'itemWeights\[ITEM_COUNT\]=\{[^}]+}', 'itemWeights[ITEM_COUNT]='+json.dumps(weights).replace('[','{').replace(']','}'),s)
s=s.replace('g->jobId<12','g->jobId<21').replace('base[g->jobId]','base[job_first50(g->jobId)]').replace('g->jobId==6?2000','job_first50(g->jobId)==6?2000').replace('g->cartOwned&&g->jobId==6','g->cartOwned&&job_first50(g->jobId)==6')
p.write_text(s)
(r/'item_count46.h').write_text('/* MIT. Stable expanded catalog within Save50 integer capacities. */\n#define ITEM_COUNT %d\n#define EQUIP_SLOTS46 10\n'%len(entries))
mapping={e[0]:i for i,e in enumerate(entries)}
recipes=[]
for recipe in audit['recipes']:
 key=next(v['id']for v in catalog['skills']if v['sourceID']==recipe['skill'])
 recipes.append(dict(product=mapping[recipe['product']],sourceProduct=recipe['product'],skill=key,rank=recipe['rank'],level=recipe['itemLevel'],materials=[[mapping[v['id']],v['amount']]for v in recipe['materials']]))
req=[]
for skill in catalog['skills']:
 for key,amount in skill['items'].items():req.append([skill['id'],mapping[bykey[key]],*amount])
out=dict(items=[dict(index=i,id=e[0],name=e[1],wtype=e[11]if len(e)>11 else 0,source=db.get(e[0],''))for i,e in enumerate(entries)],recipes=recipes,requirements=req)
(r/'items50.json').write_text(json.dumps(out,indent=2,ensure_ascii=False)+'\n')
h='/* GPL-3.0-or-later. Source item requirements by skill and rank. */\nstatic const unsigned short classItems50[][12]='+json.dumps(req,separators=(',',':')).replace('[','{').replace(']','}')+';\n'
h+='typedef struct {unsigned short product,skill,rank,level,count,materials[10][2];} Recipe50;\nstatic const Recipe50 recipes50[]={\n'
for q in recipes:
 assert len(q['materials'])<=10
 h+='{%d,%d,%d,%d,%d,%s},\n'%(q['product'],q['skill'],q['rank'],q['level'],len(q['materials']),json.dumps(q['materials'],separators=(',',':')).replace('[','{').replace(']','}'))
h+='};\nstatic int item_source50(unsigned source){for(int i=0;i<ITEM_COUNT;i++)if((unsigned)itemDefs[i].id==source)return i;return -1;}\n'
(r/'item_data50.h').write_text(h)
print('PASS50',len(entries),'stable items,',len(newids),'new original gear/reagents/products/materials,79source recipes,',len(req),'nested rank-specific item requirements.')
