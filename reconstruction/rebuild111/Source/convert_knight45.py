# MIT. Original male Knight two-handed body/head/weapon layers, all directional frames.
from pathlib import Path
import struct,zlib,re,csv,hashlib,json
import numpy as np
from PIL import Image
import ro_sprite_bake as ro
r=Path(__file__).resolve().parent;lib=r.parent.parent/'asset-library';assets={}
for folder in ['Classes43-return','Test45-return']:
 for p in (lib/folder/'data').rglob('*'):
  if p.is_file():assets[str(p.relative_to(lib/folder)).replace('/','\\').lower()]=p.read_bytes()
a=lib/'Next-Assets-Test37'
for row in csv.DictReader((a/'Assets.csv').open(encoding='utf-8-sig')):
 b=(a/row['payload']).read_bytes();assert hashlib.sha256(b).hexdigest()==row['sha256'];assets[row['virtual_path'].lower()]=b
ro.originY=100;body='data\\sprite\\인간족\\몸통\\남\\기사_남';weapon='data\\sprite\\인간족\\기사\\기사_남_양손검';head='data\\sprite\\인간족\\머리통\\남\\1_남';images=ro.spr(assets[body+'.spr']);weapons=ro.spr(assets[weapon+'.spr']);heads=ro.spr(assets[head+'.spr']);acts,delays=ro.act(assets[body+'.act']);wa,_=ro.act(assets[weapon+'.act']);ha,_=ro.act(assets[head+'.act']);frames=[];lookup={};sequence=[];meta=[];visible=[0]*8;preview=[]
for group,source in enumerate([0,1,10,6,8,2,4,4]):
 for direction in range(8):
  ai=source*8+direction;start=len(sequence)
  for fi,(layers,anchors)in enumerate(acts[ai]):
   canvas=Image.new('RGBA',(128,128));wl=wa[ai][min(fi,len(wa[ai])-1)][0]if group in[2,6,7]else[]
   def wd():
    for l in wl:ro.drawlayer(canvas,weapons,l)
   def bd():
    for l in layers:ro.drawlayer(canvas,images,l)
   if direction in [3,4,5]:wd();bd()
   else:bd();wd()
   hl,ah=ha[ai][min(fi,len(ha[ai])-1)];ox=oy=0
   if anchors and ah:ox=anchors[0][0]-ah[0][0];oy=anchors[0][1]-ah[0][1]
   for l in hl:ro.drawlayer(canvas,heads,l,ox,oy)
   if group==2:
    visible[direction]+=any(l[2]>=0 for l in wl)
    if direction in[0,2,4,6]:preview.append(canvas.copy())
   data=canvas.tobytes()
   if data not in lookup:lookup[data]=len(frames);frames.append(canvas)
   sequence.append(lookup[data])
  meta.append((start,len(sequence)-start,max(20,int(delays[ai]))))
assert all(visible);pix=bytearray();directory=[]
for im in frames:
 box=im.getbbox()
 if box:
  x,y,x1,y1=box;a=np.array(im.crop(box),np.uint32);v=((a[:,:,3]>=128).astype(np.uint32)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3);directory.append((x,y,x1-x,y1-y,len(pix)));pix+=v.astype('<u2').tobytes()
 else:directory.append((0,0,0,0,len(pix)))
raw=struct.pack('<8I',128,128,len(frames),len(meta),len(sequence),64,110,len(pix)|0x80000000)+b''.join(struct.pack('<3I',*x)for x in meta)+struct.pack('<%dI'%len(sequence),*sequence)+b''.join(struct.pack('<5I',*x)for x in directory)+pix;cp=zlib.compress(raw,9);file=r.parent/'Actors/actors.bin';old=file.read_bytes();file.write_bytes(old+cp);p=r/'actor_data.h';s=p.read_text().replace('ACTOR_FILE_BYTES '+str(len(old)),'ACTOR_FILE_BYTES '+str(len(old)+len(cp))).replace('ACTOR_VARIANTS 17','ACTOR_VARIANTS 18');s=s.replace('\n};',',\n{7,3,%d,%d,%d,0x%08xu}\n};'%(len(old),len(cp),len(raw),zlib.crc32(cp)));p.write_text(s)
sheet=Image.new('RGBA',(128*9,128*4),(45,60,50,255))
for i,im in enumerate(preview):sheet.alpha_composite(im,(i%9*128,i//9*128))
sheet.save(r.parent/'Knight-Sword45.png');(r/'knight45.json').write_text(json.dumps({'source_attack_group':10,'weapon_frames_each_direction':visible,'raw_bytes':len(raw),'packed_bytes':len(cp)},indent=2));print(visible,len(raw),len(cp))
