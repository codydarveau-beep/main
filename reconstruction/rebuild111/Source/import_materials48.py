# GPL-3.0-or-later. Append exact source reagents/converters without moving existing item IDs.
from pathlib import Path
import re,json
r=Path(__file__).resolve().parent;src=(r.parent.parent/'asset-library/Test48-followup/server/db/pre-re/item_db.conf').read_text();db={int(m[1]):m[2]for m in re.finditer(r'(?ms)^\{\s*Id:\s*(\d+)\s*(.*?)^\},?\s*$',src)};ids=[715,904,946,947,990,991,992,993,7006,7433,12114,12115,12116,12117];entries=[]
for iid in ids:
 b=db[iid]
 def num(k,d=0):
  m=re.search(r'(?m)^\s*'+k+r':\s*(\d+)',b);return int(m[1])if m else d
 name=re.search(r'\bName:\s*"([^"]+)"',b)[1];entries.append(dict(id=iid,name=name,weight=num('Weight'),buy=num('Buy'),sell=num('Sell',num('Buy')//2)))
p=r/'item_count46.h';assert '#define ITEM_COUNT 100' in p.read_text();p.write_text(p.read_text().replace('ITEM_COUNT 100','ITEM_COUNT 114'))
p=r/'inventory.h';s=p.read_text();a=s.index('\n};',s.index('static const ItemDef'));s=s[:a]+',\n'+',\n'.join(' {'+','.join(json.dumps(v)for v in [q['id'],q['name'],'Class crafting material or elemental converter.',0,0,0,0,0])+ '}'for q in entries)+s[a:];m=re.search(r'itemWeights\[ITEM_COUNT\]=\{([^}]+)',s);s=s[:m.end(1)]+','+','.join(str(q['weight'])for q in entries)+s[m.end(1):];p.write_text(s)
p=r/'shop.h';s=p.read_text()
for name,k in [('shopBuy','buy'),('shopSell','sell')]:
 m=re.search(name+r'\[ITEM_COUNT\]=\{([^}]+)',s);s=s[:m.end(1)]+','+','.join(str(q[k])for q in entries)+s[m.end(1):]
p.write_text(s)
p=r/'window_draw.h';s=p.read_text();m=re.search(r'itemIcons\[ITEM_COUNT\]=\{([^}]+)',s);assert m;s=s[:m.end(1)]+','+','.join('SKIN48_MATERIAL_BASE+'+str(i)for i in range(14))+s[m.end(1):];s=s.replace('if(id>=69&&id<SKILL_COUNT)return','if(id>=89&&id<127)return SKIN48_SKILL_BASE+id-89;if(id>=69&&id<89)return');p.write_text(s);(r/'materials48.json').write_text(json.dumps(entries,indent=2));print('PASS14 exact source materials,114stableitems, source weights/prices and original icons')
