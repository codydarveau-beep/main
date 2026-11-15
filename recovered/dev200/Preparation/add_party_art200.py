"""Original party widgets into verified unused HUD pixels; atlas size unchanged."""
from pathlib import Path
import sys,re,zlib,hashlib,json
import numpy as np
from PIL import Image
R=Path('/workspace/myro/dev200');sys.path.insert(0,str(R/'Source'));from asset_index50 import paths,key50
p=R/'Source/skin_assets.c';s=p.read_text();m=re.search(r'skin_image\[\]=\{([^}]+)\}',s);raw=zlib.decompress(bytes(map(int,m[1].split(','))));a=np.frombuffer(raw,dtype=np.uint8).reshape(2048,512,4).copy();before=a.copy();assert not np.any(a[2016:2048,416:512])
root='data/texture/유저인터페이스/renewalparty/';sources=[]
for name,x,y in [('icon_jobs_1.bmp',416,2016),('icon_jobs_4.bmp',442,2016),('ico_partycrown.bmp',469,2016),('bg_partymember.bmp',469,2028)]:
 path=paths[key50(root+name)];im=np.array(Image.open(path).convert('RGBA'));pink=(im[:,:,0]>240)&(im[:,:,1]<20)&(im[:,:,2]>240);im[pink]=0;h,w=im.shape[:2];a[y:y+h,x:x+w]=im[:,:,[2,1,0,3]]; sources.append(dict(name=name,path=str(path),sha256=hashlib.sha256(path.read_bytes()).hexdigest(),rect=[x,y,w,h]))
mask=np.any(a!=before,axis=2);assert not np.any(mask[:2016])and not np.any(mask[:,:416]);cp=zlib.compress(a.tobytes(),9);s=s[:m.start(1)]+','.join(map(str,cp))+s[m.end(1):];s=re.sub(r'skin_image_size=\d+',f'skin_image_size={len(cp)}',s);p.write_text(s);(R/'Source/party_art200.h').write_text('/* Original party UI widgets, existing atlas; no extra GPU allocation. */\n#define PARTY_SWORD_X200 416\n#define PARTY_ACO_X200 442\n#define PARTY_ART_Y200 2016\n#define PARTY_CROWN_X200 469\n#define PARTY_BG_X200 469\n#define PARTY_BG_Y200 2028\n')
(R/'Preparation/Party-Art200.json').write_text(json.dumps(dict(atlasBytes=len(raw),extraGPUBytes=0,sources=sources,changedPixels=int(mask.sum())),indent=2,ensure_ascii=False)+'\n');Image.fromarray(a[2016:2048,416:512][:,:,[2,1,0,3]]).resize((576,192),Image.Resampling.NEAREST).save(R/'Validation/party-atlas200.png');print('Added four original party widgets; atlas allocation unchanged; touched',mask.sum(),'previously empty pixels.')
