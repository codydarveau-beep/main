"""MIT. Prepare authentic nine-job bodies/weapon actions, preserving shipped49 pack.
The result is staged under ClassAssets50 until gameplay/class registry integration.
"""
from pathlib import Path
import struct,zlib,json,re,hashlib
import numpy as np
from PIL import Image
import ro_sprite_bake as ro
from asset_index50 import paths
r=Path(__file__).resolve().parent;out=r.parent/'ActorAssets52';out.mkdir(exist_ok=True)
ns={'struct':struct,'Reader':ro.Reader};src=(r/'convert_equipped_actors.py').read_text();exec(src[src.index('def act('):src.index("head='data")],ns);act=ns['act']
plan=dict(classes=json.loads((r.parent/'Preparation/Actor-Roster52.json').read_text()));base=r.parent.parent/'test51';original=(base/'Actors/actors.bin').read_bytes();packed=bytearray(original)
meta=[tuple(int(x.rstrip('u'),0)for x in v)for v in re.findall(r'\{(\d+),(\d+),(\d+),(\d+),(\d+),((?:0x[0-9a-f]+u)|(?:\d+))\}',(base/'Source/actor_data.h').read_text())]
assert len(meta)==100;report=[];contacts=[]
terms={3:['양손검','1116'],4:['창','1401'],5:['양손창','1410'],1:['단검'],2:['검'],6:['도끼'],7:['양손도끼'],8:['클럽','1504'],9:['롯드'],10:['활'],11:['책'],13:['너클','1801','1804'],14:['악기'],15:['채찍'],16:['카타르_카타르','카타르']}
# Original client WeaponAction table values; ATTACK1/2/3 map to sheets5/10/11.
styles={'Assassin':{1:1,2:1,6:1,16:2},'Rogue':{1:1,2:1,10:2},'Hunter':{1:1,10:2},'Bard':{1:1,10:2,14:1},'Dancer':{1:0,10:2,15:1},'Priest':{8:1,9:1,11:2},'Monk':{8:1,9:1,13:2},'Blacksmith':{1:1,2:2,6:2,7:2,8:2},'Alchemist':{1:1,2:2,6:2,7:2,8:2}}
styles.update({'Knight':{1:1,2:1,3:1,4:2,5:2},'Crusader':{1:1,2:1,3:1,4:2,5:2},'Sage':{1:1,9:2,11:2}})
sheet={0:5,1:10,2:11};opaque=lambda im:np.array(im)[:,:,3]>=128
for q in plan['classes']:
 job=q['id'];actor=q['actor'];stem=q['bodyStem'];sex='여'if q['defaultSex']=='female'else'남'
 body='data\\sprite\\인간족\\몸통\\'+sex+'\\'+stem+'_'+sex;head='data\\sprite\\인간족\\머리통\\'+sex+'\\1_'+sex
 images=ro.spr(paths[body+'.spr'].read_bytes());ba,delays=act(paths[body+'.act'].read_bytes());heads=ro.spr(paths[head+'.spr'].read_bytes());ha,_=act(paths[head+'.act'].read_bytes())
 wpstem=q['weaponStem'];prefix='data\\sprite\\인간족\\'+wpstem+'\\'+wpstem+'_'+sex+'_';variants=[(0,0,None,0)]
 # Mounted Lord Knight uses the original mounted Knight weapon folder.
 available=styles[q['style']]
 if q['actor']>=40 and not any(prefix+term+'.spr'in paths for term in terms[1]):available={}
 for typ,style in available.items():
  suffix=next((term for term in terms[typ]if prefix+term+'.spr'in paths),None)
  if suffix is None and typ==7:suffix=next((x for x in ['1354','1357','1355']if prefix+x+'.spr'in paths),None)
  assert suffix is not None,(q['name'],typ,'original weapon pose absent')
  variants.append((1 if typ==1 else 2 if typ==10 else 3 if typ==3 else 100+typ,typ,prefix+suffix,style))
 if q['style']=='Assassin':
  for gear,suffix in [(201,'단검_단검'),(202,'검_검'),(203,'도끼_도끼'),(204,'단검_검'),(205,'단검_도끼'),(206,'검_도끼')]:
   assert prefix+suffix+'.spr'in paths
   variants.append((gear,17,prefix+suffix,2))
 for gear,typ,wp,style in variants:
  wi=ro.spr(paths[wp+'.spr'].read_bytes())if wp else None;wa,_=act(paths[wp+'.act'].read_bytes())if wp else (None,None)
  attack=sheet[style];groups=[0,1,attack,6,8,2,4,12];frames=[];lookup={};seq=[];actions=[];visible=[0]*8;previews=[];contact=[]
  ro.originY=100
  for group,source in enumerate(groups):
   for direction in range(8):
    ai=source*8+direction;start=len(seq);poses=ba[ai]
    # Source getAttackSlice: Monk knuckle/unarmed normal attacks use first five frames.
    if q['style']=='Monk'and group==2 and typ in [0,13]:poses=poses[:5]
    for fi,(layers,anchors)in enumerate(poses):
     canvas=Image.new('RGBA',(128,128));wl=wa[ai][min(fi,len(wa[ai])-1)][0]if wp else []
     def wd():
      for l in wl:ro.drawlayer(canvas,wi,l)
     def bd():
      for l in layers:ro.drawlayer(canvas,images,l)
     if direction in [3,4,5]:wd();bd()
     else:bd();wd()
     hl,ah=ha[ai][min(fi,len(ha[ai])-1)];ox=oy=0
     if anchors and ah:ox=anchors[0][0]-ah[0][0];oy=anchors[0][1]-ah[0][1]
     for l in hl:ro.drawlayer(canvas,heads,l,ox,oy)
     if group==2:visible[direction]+=any(l[2]>=0 for l in wl)
     if fi==0 and group==0:
      if not gear:
       ys,xs=np.where(opaque(canvas));mask=ys>=ys.max()-13;xs=xs[mask];ys=ys[mask];fx=(xs.min()+xs.max())/2;fy=((ys[xs<=fx]+1).max()+(ys[xs>=fx]+1).max())/2;contact.append([float(64-fx),float(110-fy)])
      previews.append(canvas.copy())
     data=canvas.tobytes()
     if data not in lookup:lookup[data]=len(frames);frames.append(canvas)
     seq.append(lookup[data])
    actions.append((start,len(seq)-start,max(20,int(delays[ai]))))
  if wp and not(q['style']=='Dancer'and typ==1 and style==0 or q['style']=='Monk'and typ==13):assert all(visible),(q['name'],typ,visible)
  pixels=bytearray();directory=[]
  for im in frames:
   box=im.getbbox()
   if not box:directory.append((0,0,0,0,len(pixels)));continue
   x,y,xx,yy=box;a=np.array(im.crop(box),dtype=np.uint32);v=((a[:,:,3]>=128).astype(np.uint32)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3);directory.append((x,y,xx-x,yy-y,len(pixels)));pixels+=v.astype('<u2').tobytes()
  assert len(frames)<=1024 and len(seq)<=8192
  raw=bytearray(struct.pack('<8I',128,128,len(frames),64,len(seq),64,110,len(pixels)|0x80000000))
  for a in actions:raw+=struct.pack('<3I',*a)
  raw+=np.array(seq,dtype='<u4').tobytes()
  for a in directory:raw+=struct.pack('<5I',*a)
  raw+=pixels;assert len(raw)<=4*1024*1024,(q['name'],gear,len(raw),len(frames))
  cp=zlib.compress(raw,9);meta.append((actor,gear,len(packed),len(cp),len(raw),zlib.crc32(cp)));packed+=cp
  entry=dict(job=job,actor=actor,name=q['name'],gear=gear,wtype=typ,weapon=wp,sourceAttackSheet=attack,visibleDirections=visible,raw=len(raw),packed=len(cp),frames=len(frames),sourceBodySHA256=hashlib.sha256(paths[body+'.spr'].read_bytes()).hexdigest());report.append(entry)
  if not gear:
   contacts.append(dict(actor=actor,job=job,name=q['name'],contact=contact));(out/(q['name']+'.bin')).write_bytes(raw)
   preview=Image.new('RGBA',(128*8,128),(40,48,40,255))
   for i,im in enumerate(previews):preview.alpha_composite(im,(128*i,0))
   preview.save(out/(q['name']+'.png'))
  print(q['name'],gear,'sheet',attack,len(cp),flush=True)
assert packed[:len(original)]==original
(out/'actors52.bin').write_bytes(packed);(out/'actors52.json').write_text(json.dumps(report,indent=2)+'\n')
(out/'actor_data52.h').write_text('/* Prepared original second-class poses; loaded one selected variant at a time. */\n#define ACTOR_FILE_BYTES %d\n#define ACTOR_VARIANTS %d\ntypedef struct {unsigned job,gear,offset,packed,raw,crc;} ActorBlob;\nstatic const ActorBlob actorBlobs[ACTOR_VARIANTS]={\n'%(len(packed),len(meta))+''.join('{%d,%d,%d,%d,%d,0x%08xu},\n'%v for v in meta)+'};\n')
(out/'contacts52.json').write_text(json.dumps(contacts,indent=2)+'\n')
print('PASS52 prepared',len(report),'new authentic body/weapon/dual-wield/mounted variants, original51 prefix unchanged, pack',len(packed),'not activated yet.')
