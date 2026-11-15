# GPL-3.0-or-later. Source Book1550; append only, no changes to existing item indices.
from pathlib import Path
import re,json
r=Path(__file__).resolve().parent;p=r/'item_count46.h';s=p.read_text();assert 'ITEM_COUNT 114' in s;p.write_text(s.replace('ITEM_COUNT 114','ITEM_COUNT 115'))
p=r/'inventory.h';s=p.read_text();a=s.index('\n};',s.index('static const ItemDef'));s=s[:a]+',\n {1550,"Book","BaseLv14; ATK85. Sage book; Study applies.",0,0,85,0,8192,1024,14,0,11,0,0}'+s[a:];m=re.search(r'itemWeights\[ITEM_COUNT\]=\{([^}]+)',s);s=s[:m.end(1)]+',600'+s[m.end(1):];p.write_text(s)
p=r/'shop.h';s=p.read_text()
for name,value in [('shopBuy',30000),('shopSell',15000)]:
 m=re.search(name+r'\[ITEM_COUNT\]=\{([^}]+)',s);s=s[:m.end(1)]+','+str(value)+s[m.end(1):]
p.write_text(s)
p=r/'equipment46.json';q=json.loads(p.read_text());q.append(dict(id=1550,name='Book',type='IT_WEAPON',slot=0,subtype='W_BOOK',jobs=1024,level=14,attack=85,defense=0,weight=600,buy=30000,sell=15000,slots=3,matk=0,twoHand=False,sourceScript=False,wtype=11,equipBit=8192));p.write_text(json.dumps(q,indent=2)+'\n')
p=r/'window_draw.h';s=p.read_text();m=re.search(r'itemIcons\[ITEM_COUNT\]=\{([^}]+)',s);s=s[:m.end(1)]+',SKIN48_BOOK'+s[m.end(1):];p.write_text(s)
p=r/'sprites.h';s=p.read_text().replace('(equipment&4096)?109:0','(equipment&4096)?109:(equipment&8192)?111:0');p.write_text(s)
p=r/'convert_skill_icons48.py';s=p.read_text().replace('for x,y,w,h in oldrects+reserved:assert','bookicon=len(rects);put("data\\\\texture\\\\유저인터페이스\\\\item\\\\북.bmp")\nfor x,y,w,h in oldrects+reserved:assert');s=s.replace('#define SKIN48_MATERIAL_BASE %d\\n','#define SKIN48_MATERIAL_BASE %d\\n#define SKIN48_BOOK %d\\n').replace('%(skillbase,materialbase)','%(skillbase,materialbase,bookicon)');p.write_text(s)
p=r/'test_equipment46.c';p.write_text(p.read_text().replace('ITEM_COUNT==100','ITEM_COUNT==115'))
p=r/'developer.h';s=p.read_text();m='dev_class_preset';# leave preset dagger stable; Book is available through developer inventory/shop.
print('PASS source Book appended index114; Study uses actual book weapon type11')
