"""MIT. Precompose original first-job body/head/weapon actions into disc-loaded sparse frames.
Usage: python convert_equipped_actors.py WeaponAssets.zip JobAssets.zip
Original resources retain their owners' rights. Only current catalog gear is baked.
"""
from pathlib import Path
import sys,zipfile,csv,io,hashlib,struct,zlib,json,os,time,math
import numpy as np
from PIL import Image
ROOT=Path(__file__).resolve().parent.parent
assets={}
for path in sys.argv[1:]:
 with zipfile.ZipFile(path) as z:
  for r in csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))):
   b=z.read(r['payload']);assert hashlib.sha256(b).hexdigest()==r['sha256'];assets[r['virtual_path'].lower()]=b
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
STEMS=['초보자','검사','마법사','성직자','도둑','궁수','상인'];out=ROOT/'Actors';out.mkdir(exist_ok=True);packed=bytearray();records=[];previews=[]
def bake(job,gear):
 stem=STEMS[job];body='data\\sprite\\인간족\\몸통\\남\\'+stem+'_남';images=spr(assets[body+'.spr']);acts,delays=act(assets[body+'.act']);weapon=None;wp=None
 if gear:
  wp='data\\sprite\\인간족\\'+stem+'\\'+stem+'_남_'+('활' if gear==2 else '단검');weapon=spr(assets[wp+'.spr']);wacts,_=act(assets[wp+'.act'])
 attack=10 if gear==2 else (11 if job in (2,5,6) else 10) if gear==1 else 5;groups=[0,1,attack,6,8,2,4,4];frames=[];lookup={};seq=[];meta=[];preview=[];weaponFrames=0;visibleByDir=[0]*8
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
for job in range(7):
 bake(job,0)
 if job!=3:bake(job,1)
 if job==5:bake(job,2)
(out/'actors.bin').write_bytes(packed);(out/'index.json').write_text(json.dumps(records,indent=2))
header='''/* Generated original body/head/weapon composites. Only current variant decoded. */
#define ACTOR_FILE_BYTES %d
#define ACTOR_VARIANTS %d
typedef struct {unsigned job,gear,offset,packed,raw,crc;} ActorBlob;
static const ActorBlob actorBlobs[ACTOR_VARIANTS]={\n'''%(len(packed),len(records))
header+=',\n'.join('{%d,%d,%d,%d,%d,0x%08xu}'%(a['job'],a['gear'],a['offset'],a['packed'],a['raw'],a['crc']) for a in records)+'\n};\n'
p=ROOT/'Source/actor_data.h';p.write_text(header);os.utime(p,(time.time()+21600,)*2)
print('Actors disc pack:',len(records),'variants;',len(packed),'bytes')
