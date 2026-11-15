"""MIT. Stage original second-class/companion icons in appended atlas rows.

All 512x640 existing pixels and rectangle indices are protected, including fonts,
damage/miss digits, hold buttons, the edited First Aid hand and equipped fades.
"""
from pathlib import Path
import hashlib
import json
import re
import zlib
from PIL import Image
from asset_index50 import paths, key50

r = Path(__file__).resolve().parent
out = r.parent/'ClassAssets50'
out.mkdir(exist_ok=True)
base = r.parent.parent/'test49/Source'
s = (base/'skin_assets.c').read_text()
cp = bytes(map(int,re.findall(r'\d+',re.search(r'skin_image\[\]=\{(.*?)\};',s,re.S)[1])))
original = Image.frombytes('RGBA',(512,640),zlib.decompress(cp),'raw','BGRA')
atlas = Image.new('RGBA',(512,1024))
atlas.paste(original,(0,0))
defs = (base/'skin_data.h').read_text()
old_rects = [tuple(map(int,re.findall(r'\d+',v))) for v in re.findall(r'\{\d+,\d+,\d+,\d+\}',defs)]
rects = old_rects.copy()
catalog = json.loads((out/'catalog50.json').read_text())
report = []


def put(key, runtime_id, kind, dim=False):
    name = key.lower()
    if key == 'BA_FROSTJOKER':
        name = 'ba_frostjoke'  # Verified original client spelling, not a repaint.
    path = paths[key50('data/texture/유저인터페이스/item/'+name+'.bmp')]
    icon = Image.open(path).convert('RGBA')
    data = list(icon.getdata())
    icon.putdata([(rr,gg,bb,0 if (rr,gg,bb)==(255,0,255) else aa) for rr,gg,bb,aa in data])
    icon = icon.resize((20,20),Image.Resampling.LANCZOS)
    if dim:
        icon.putalpha(icon.getchannel("A").point(lambda a:a//2))
    ordinal = len(report)
    x,y = 1+(ordinal%23)*22,641+(ordinal//23)*22
    assert x+20<512 and y+20<1024
    atlas.paste(icon,(x,y))
    index = len(rects)
    rects.append((x,y,20,20))
    report.append(dict(key=key,kind=kind,id=runtime_id,rect=index,
                       resource=str(path),sourceSHA256=hashlib.sha256(path.read_bytes()).hexdigest()))
    return index


player = [put(row['key'],row['id'],'player') for row in catalog['skills'] if row['id']>=127]
companions = [put(row['key'],row['sourceID'],'homunculus') for row in catalog['companions']]
assert len(player)==127 and len(companions)==16 and len(report)==143
# Items use the source ID-to-resource table, including the nested Potion Pitcher
# Orange Potion requirement. No source art is repainted or substituted.
item_rows=json.loads((r/'items50.json').read_text())['items']
table=(r.parent.parent/'asset-library/Test46-followup/data/idnum2itemresnametable.txt').read_text(encoding='cp949')
names={int(q[0]):q[1]for line in table.splitlines()if len(q:=line.split('#'))>=2 and q[0].isdigit()}
item_icons=[put(names[row['id']],row['index'],'item')for row in item_rows[115:]]
old_dim=list(map(int,re.search(r'itemDim49\[115\]=\{([^}]+)',defs)[1].split(',')))
item_dim=old_dim+[put(names[row['id']],row['index'],'equipped-item',True)if row['wtype']else item_icons[n]for n,row in enumerate(item_rows[115:])]
assert len(item_dim)==len(item_rows)==255
assert atlas.crop((0,0,512,640)).tobytes()==original.tobytes()
assert rects[:len(old_rects)]==old_rects
new_defs = re.sub(r'(static const unsigned short skinRects\[\]\[4\]=\{).*?(\n\};)',
                  lambda m:m[1]+'\n'+',\n'.join('{%d,%d,%d,%d}'%v for v in rects)+m[2],defs,flags=re.S)
new_defs=re.sub(r'itemDim49\[115\]=\{[^}]+}', 'itemDim49[%d]={'%len(item_rows)+','.join(map(str,item_dim))+'}',new_defs)
new_defs += 'static const unsigned short classItemIcons50[%d]={'%len(item_icons)+','.join(map(str,item_icons))+'};\n'
new_defs += '\n#define SKIN50_H 1024\nstatic const unsigned short classSkillIcons50[127]={' + ','.join(map(str,player))+'};\n'
new_defs += 'static const unsigned short homunSkillIcons50[16]={' + ','.join(map(str,companions))+'};\n'
(out/'skin_data50.h').write_text(new_defs)
raw = atlas.tobytes('raw','BGRA')
packed = zlib.compress(raw,9)
(out/'skin_assets50.c').write_text('/* MIT. Prepared original icons; all Test49 pixels/indices retained. */\n'
    +'const unsigned int skin_image_raw=%d,skin_image_size=%d;\n'%(len(raw),len(packed))
    +'const unsigned char skin_image[]={'+','.join(map(str,packed))+'};\n')
atlas.save(out/'icons50.png')
(out/'icons50.json').write_text(json.dumps(dict(width=512,height=1024,rawBytes=len(raw),
    gpuIncreaseBytes=len(raw)-512*640*4,protectedTop640SHA256=hashlib.sha256(original.tobytes()).hexdigest(),
    icons=report,status='activated in Test50; original Test49 pixels protected'),indent=2)+'\n')
print('PASS50',len(report),'original player/companion/item/equipped icons; exact protected512x640 pixels and333 old rectangles; integer512x1024 atlas,768KiB increase.')
