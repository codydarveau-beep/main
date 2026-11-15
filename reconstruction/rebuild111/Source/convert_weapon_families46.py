"""MIT. Append supported original male weapon-family poses; one selected variant is loaded."""
from pathlib import Path
import sys,struct,zlib,json,re,csv
import numpy as np
from PIL import Image
import ro_sprite_bake as ro
s=Path(__file__).resolve().parent;lib=s.parent.parent/'asset-library';assets={}
for folder in ['Classes43-return','Test45-return','Test46-equipment-art']:
 for p in (lib/folder/'data/sprite').rglob('*'):
  if p.is_file()and p.suffix in ['.spr','.act']:assets[str(p.relative_to(lib/folder)).replace('/','\\').lower()]=p.read_bytes()
a=lib/'Next-Assets-Test37'
for row in csv.DictReader((a/'Assets.csv').open(encoding='utf-8-sig')):
 if row['virtual_path'].endswith(('.spr','.act')):assets[row['virtual_path'].lower()]=(a/row['payload']).read_bytes()
# Parser supports original weapon ACT2.1 without anchor/delay blocks.
t=(s/'convert_equipped_actors.py').read_text();ns={'struct':struct,'Reader':ro.Reader};exec(t[t.index('def act('):t.index("head='data")],ns);act=ns['act'];ro.originY=100
stems=['초보자','검사','마법사','성직자','도둑','궁수','상인','기사','하이위저드'];terms={2:'검',4:'창',5:'양손창',6:'도끼',7:'양손도끼',8:'1504',9:'롯드'};items=json.loads((s/'equipment46.json').read_text());bodyhead='data\\sprite\\인간족\\머리통\\남\\1_남';heads=ro.spr(assets[bodyhead+'.spr']);ha,_=act(assets[bodyhead+'.act']);old=(s.parent.parent/'test45a/Actors/actors.bin').read_bytes();payload=bytearray(old);meta=[tuple(int(x.rstrip('u'),0)for x in v)for v in re.findall(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),((?:0x[0-9a-f]+u)|(?:\d+))\}',(s.parent.parent/'test45a/Source/actor_data.h').read_text())];report=[]
for job in range(9):
 ro.originY=80 if job<7 else 100
 stem=stems[job];body='data\\sprite\\인간족\\몸통\\남\\'+stem+'_남'
 if body+'.spr'not in assets:continue
 images=ro.spr(assets[body+'.spr']);ba,delays=act(assets[body+'.act'])
 for typ,term in terms.items():
  if not any(e['wtype']==typ and e['jobs']&(1<<job)for e in items):continue
  ws=stems[2]if job==8 else stem;weapon='data\\sprite\\인간족\\'+ws+'\\'+ws+'_남_'+term
  if weapon+'.spr'not in assets:report.append({'job':job,'type':typ,'deferred':'matching original weapon resource absent'});continue
  weapons=ro.spr(assets[weapon+'.spr']);wa,_=act(assets[weapon+'.act']);groups=[0,1,11 if typ in [4,5]else 10,6,8,2,4,4];frames=[];lookup={};seq=[];actions=[];visible=[0]*8
  if max(groups)*8+7>=min(len(ba),len(wa),len(ha)):report.append({'job':job,'type':typ,'deferred':'unsupported original action layout'});continue
  for group,source in enumerate(groups):
   for direction in range(8):
    ai=source*8+direction;start=len(seq)
    for fi,(layers,anchors)in enumerate(ba[ai]):
     canvas=Image.new('RGBA',(128,128));wl=wa[ai][min(fi,len(wa[ai])-1)][0]if group in [2,6,7]else[]
     def wd():
      for l in wl:ro.drawlayer(canvas,weapons,l)
     def bd():
      for l in layers:ro.drawlayer(canvas,images,l)
     if direction in[3,4,5]:wd();bd()
     else:bd();wd()
     hl,ah=ha[ai][min(fi,len(ha[ai])-1)];ox=oy=0
     if anchors and ah:ox=anchors[0][0]-ah[0][0];oy=anchors[0][1]-ah[0][1]
     for l in hl:ro.drawlayer(canvas,heads,l,ox,oy)
     if group==2:visible[direction]+=any(l[2]>=0 for l in wl)
     data=canvas.tobytes()
     if data not in lookup:lookup[data]=len(frames);frames.append(canvas)
     seq.append(lookup[data])
    actions.append((start,len(seq)-start,max(20,int(delays[ai]))))
  if not all(visible):report.append({'job':job,'type':typ,'deferred':'no visible matching attack weapon in every direction'});continue
  pixels=bytearray();directory=[]
  for im in frames:
   box=im.getbbox()
   if not box:directory.append((0,0,0,0,len(pixels)));continue
   x,y,xx,yy=box;a=np.array(im.crop(box),dtype=np.uint32);argb=((a[:,:,3]>=128).astype(np.uint32)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3);directory.append((x,y,xx-x,yy-y,len(pixels)));pixels+=argb.astype('<u2').tobytes()
  raw=bytearray(struct.pack('<8I',128,128,len(frames),64,len(seq),64,90 if job<7 else 110,len(pixels)|0x80000000))
  for a in actions:raw+=struct.pack('<3I',*a)
  raw+=np.array(seq,dtype='<u4').tobytes()
  for a in directory:raw+=struct.pack('<5I',*a)
  raw+=pixels;cp=zlib.compress(raw,9);meta.append((job,100+typ,len(payload),len(cp),len(raw),zlib.crc32(cp)));payload+=cp;report.append(dict(job=job,type=typ,raw=len(raw),visible=visible,weapon=weapon));print(job,typ,len(cp),flush=True)
(s.parent/'Actors/actors.bin').write_bytes(payload);(s/'actor_data.h').write_text('/* Original weapon-family variants: decoded one selected variant at a time. */\n#define ACTOR_FILE_BYTES %d\n#define ACTOR_VARIANTS %d\ntypedef struct {unsigned job,gear,offset,packed,raw,crc;} ActorBlob;\nstatic const ActorBlob actorBlobs[ACTOR_VARIANTS]={\n'%(len(payload),len(meta))+''.join('{%d,%d,%d,%d,%d,0x%08xu},\n'%v for v in meta)+'};\n');(s/'weapon_families46.json').write_text(json.dumps(report,indent=2));print('PASS variants',len(meta),'pack',len(payload))
