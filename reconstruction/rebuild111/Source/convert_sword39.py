"""MIT. Compose received Swordsman body/head with original two-handed action layers.
Usage: python convert_sword39.py body-folder weapon-folder
Preserves base actors.bin. Emits one embedded compressed variant.
"""
from pathlib import Path
import sys,csv,hashlib,struct,zlib,json,os,time,math
import numpy as np
from PIL import Image
ROOT=Path(__file__).resolve().parent.parent
assets={}
for arg in sys.argv[1:]:
 p=Path(arg)
 for row in csv.DictReader((p/'Assets.csv').open(encoding='utf-8-sig')):
  b=(p/row['payload']).read_bytes();assert hashlib.sha256(b).hexdigest()==row['sha256'];assets[row['virtual_path'].replace('\\\\','\\').lower()]=b
# Reuse validated SPR/parser layer drawing. Older weapon ACT2.1 needs no anchor/delay blocks.
prefix=(ROOT/'Source/convert_combat_assets.py').read_text().split('class Reader:')[1].split("body='data")[0]
prefix='class Reader:'+prefix
ns={'struct':struct,'np':np,'Image':Image,'assets':assets,'root':ROOT,'out':ROOT/'BuildAssets'};exec(prefix,ns)
spr,drawlayer=ns['spr'],ns['drawlayer'];Reader=ns['Reader']
def act(b):
 r=Reader(b);assert r.take(2)==b'AC';minor,major,n=r.unpack('BBH');v=major*10+minor;assert 20<=v<=25;r.take(10);actions=[]
 for _ in range(n):
  frames=[]
  for __ in range(r.one('I')):
   r.take(32);layers=[]
   for ___ in range(r.one('I')):
    x,y,idx,mirror=r.unpack('4i');col=r.unpack('4B');xs=r.one('f');ys=r.one('f') if v>=24 else xs;angle,typ=r.unpack('ii')
    if v>=25:r.take(8)
    layers.append((x,y,idx,mirror,col,xs,ys,angle,typ))
   sound=r.one('i');anchors=[]
   if v>=23:
    for ___ in range(r.one('i')):
     _,x,y,_=r.unpack('4i');anchors.append((x,y))
   frames.append((layers,anchors))
  actions.append(frames)
 if v>=21:count=r.one('i');r.take(count*40)
 delays=[r.one('f')*25 for _ in range(n)] if v>=22 else [150]*n
 assert r.p==len(b),(v,r.p,len(b))
 return actions,delays
head='data\\sprite\\인간족\\머리통\\남\\1_남';heads=spr(assets[head+'.spr']);hacts,_=act(assets[head+'.act'])
STEMS=['초보자','검사','마법사','성직자','도둑','궁수','상인'];out=ROOT/'Sword39';out.mkdir(exist_ok=True);packed=bytearray();records=[];previews=[]
def bake(job,gear):
 stem=STEMS[job];body='data\\sprite\\인간족\\몸통\\남\\'+stem+'_남';images=spr(assets[body+'.spr']);acts,delays=act(assets[body+'.act']);weapon=None;wp=None
 if gear:
  wp='data\\sprite\\인간족\\'+stem+'\\'+stem+'_남_'+'양손검';weapon=spr(assets[wp+'.spr']);wacts,_=act(assets[wp+'.act'])
 attack=10;groups=[0,1,attack,6,8,2,4,4];frames=[];lookup={};seq=[];meta=[];preview=[];weaponFrames=0;visibleByDir=[0]*8
 for group,source in enumerate(groups):
  for direction in range(8):
   ai=source*8+direction;start=len(seq)
   for fi,(layers,anchors) in enumerate(acts[ai]):
    canvas=Image.new('RGBA',(128,128));wl=[]
    if gear and group in (2,7):
     wf=wacts[ai][min(fi,len(wacts[ai])-1)];wl=wf[0]
     if group==2 and any(x[2]>=0 for x in wl):weaponFrames+=1;visibleByDir[direction]+=1
    def body_draw():
     for layer in layers:drawlayer(canvas,images,layer)
    def weapon_draw():
     for layer in wl:drawlayer(canvas,weapon,layer)
    if direction in (3,4,5):weapon_draw();body_draw()
    else:body_draw();weapon_draw()
    hl,ha=hacts[ai][min(fi,len(hacts[ai])-1)];ox=oy=0
    if anchors and ha:ox=anchors[0][0]-ha[0][0];oy=anchors[0][1]-ha[0][1]
    for layer in hl:drawlayer(canvas,heads,layer,ox,oy)
    data=canvas.tobytes();ix=lookup.get(data)
    if ix is None:ix=len(frames);lookup[data]=ix;frames.append(data)
    seq.append(ix)
    if group==2 and direction in(0,2,4,6):preview.append(canvas.copy())
   meta.append((start,len(seq)-start,max(20,int(delays[ai]))))
 directory=[];pixels=bytearray()
 for data in frames:
  im=Image.frombytes('RGBA',(128,128),data);box=im.getbbox()
  if not box:directory.append((0,0,0,0,len(pixels)));continue
  x,y,x1,y1=box;a=np.array(im.crop(box),dtype=np.uint32);argb=((a[:,:,3]>=128).astype(np.uint32)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3);directory.append((x,y,x1-x,y1-y,len(pixels)));pixels+=argb.astype('<u2').tobytes()
 raw=bytearray(struct.pack('<8I',128,128,len(frames),len(meta),len(seq),64,90,len(pixels)|0x80000000))
 for a in meta:raw+=struct.pack('<3I',*a)
 raw+=np.array(seq,dtype='<u4').tobytes()
 for a in directory:raw+=struct.pack('<5I',*a)
 raw+=pixels;cp=zlib.compress(raw,9);rec={'job':job,'gear':gear,'offset':len(packed),'packed':len(cp),'raw':len(raw),'crc':zlib.crc32(cp),'source_attack_group':attack,'weapon_frames':weaponFrames,'weapon_frames_by_direction':visibleByDir};packed.extend(cp);records.append(rec)
 if gear:
  assert all(visibleByDir),(job,gear,visibleByDir)
  sheet=Image.new('RGBA',(128*9,128*4),(64,78,65,255))
  for i,im in enumerate(preview):
   row=i//len(acts[attack*8]);col=i%len(acts[attack*8]);sheet.alpha_composite(im,(col*128,row*128))
  sheet.save(out/('job%d-gear%d.png'%(job,gear)))
 print('Actor',job,gear,'raw',len(raw),'packed',len(cp),'weapon frames',weaponFrames,flush=True)

bake(1,3)
r=records[0]
(ROOT/'Source/sword_assets39.h').write_text('/* Generated original two-handed composite; see converter/license. */\n#define SWORD39_RAW %d\nstatic const unsigned char sword39Packed[]={\n'%r['raw']+','.join(str(x) for x in packed)+'\n};\n')
(ROOT/'Source/sword-manifest39.json').write_text(json.dumps(r,indent=2)+'\n')
