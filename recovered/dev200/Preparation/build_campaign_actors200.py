"""Prepare source player bodies/heads as bounded, single-pose scene actors."""
from pathlib import Path
import ast,sys,json,struct,zlib,hashlib,math
import numpy as np
from PIL import Image
R=Path('/workspace/myro/dev200');S=R/'Source';sys.path.insert(0,str(S))
from asset_index50 import paths,key50
import ro_sprite_bake as ro
ns=dict(ro=ro,np=np,Image=Image,struct=struct,math=math)
for name,functions in [('convert_classic49.py',['sprites']),('convert_equipped_actors.py',['act'])]:
 tree=ast.parse((S/name).read_text());code=ast.Module(body=[n for n in tree.body if isinstance(n,ast.FunctionDef)and n.name in functions],type_ignores=[]);ns['Reader']=ro.Reader;exec(compile(code,name,'exec'),ns)
payload=bytearray();frames=[];actions=[];report=[];contacts=[]
plan=[('Nera','초보자','여',3),('Roan','검사','남',2),('Yuufa','성직자','여',1),('Driver','상인','남',2),('Judia','헌터','여',4),('Maya','연금술사','여',6),('Veyr','세이지','남',7)]
for actor,(name,body,sex,hair)in enumerate(plan):
 stem=key50(f'data/sprite/인간족/몸통/{sex}/{body}_{sex}');head=key50(f'data/sprite/인간족/머리통/{sex}/{hair}_{sex}')
 sources=[paths[k+ext]for k in [stem,head]for ext in ['.spr','.act']];bodyimages,ni=ns['sprites'](sources[0].read_bytes());bodyacts,delays=ns['act'](sources[1].read_bytes())
 headData=sources[2].read_bytes();colour={'Roan':7,'Yuufa':2,'Driver':7,'Judia':1,'Maya':1,'Veyr':7}.get(name)
 if colour is not None:
  palette=paths[key50(f'data/palette/머리/머리{hair}_{sex}_{colour}.pal')];pal=palette.read_bytes();assert len(pal)==1024;headData=headData[:-1024]+pal;sources.append(palette)
 headimages,hni=ns['sprites'](headData);headacts,_=ns['act'](sources[3].read_bytes());originBase=108 if actor>=4 else 96;ro.originY=originBase;actorContact=[];sheet=Image.new('RGBA',(1024,256),(42,49,42,255))
 weaponimages=weaponacts=None
 if name in ('Roan','Judia'):
  weapon=key50('data/sprite/인간족/검사/검사_남_검'if name=='Roan'else'data/sprite/인간족/헌터/헌터_여_활');sources.extend(paths[weapon+ext]for ext in ['.spr','.act']);weaponimages,wni=ns['sprites'](paths[weapon+'.spr'].read_bytes());weaponacts,_=ns['act'](paths[weapon+'.act'].read_bytes())
 for group,sourceGroup in enumerate([0,1,10 if name in ('Roan','Judia') else 5,6,8,4]):
  ro.originY=128
  for direction in range(8):
   ai=sourceGroup*8+direction;first=len(frames)
   for fi,(layers,anchors)in enumerate(bodyacts[ai][:1]if group==0 else bodyacts[ai]):
    # Idle keeps a stable head pose; walking follows source attachment anchors.
    im=Image.new('RGBA',(128,256))
    def draw_body():
     for x,y,idx,mirror,col,xs,ys,angle,typ in layers:
      if idx>=0:ro.drawlayer(im,bodyimages,(x,y,idx+(ni if typ else 0),mirror,col,xs,ys,angle,0))
    def draw_weapon():
     if weaponacts and group==2:
      wl,_=weaponacts[ai][min(fi,len(weaponacts[ai])-1)]
      for x,y,idx,mirror,col,xs,ys,angle,typ in wl:
       if idx>=0:ro.drawlayer(im,weaponimages,(x,y,idx+(wni if typ else 0),mirror,col,xs,ys,angle,0))
    if direction in (3,4,5):draw_weapon();draw_body()
    else:draw_body();draw_weapon()
    hl,ha=headacts[ai][0 if group==0 else min(fi,len(headacts[ai])-1)];ox=oy=0
    if anchors and ha:ox=anchors[0][0]-ha[0][0];oy=anchors[0][1]-ha[0][1]
    for x,y,idx,mirror,col,xs,ys,angle,typ in hl:
     if idx>=0:ro.drawlayer(im,headimages,(x,y,idx+(hni if typ else 0),mirror,col,xs,ys,angle,0),ox,oy)
    # Preserve ACT world offsets while packing every complete pose into the
    # same128-square texture. Anchor compensation cancels any packing shift.
    box=im.getbbox();assert box and box[0]>0 and box[2]<128 and box[1]>0 and box[3]<256,(name,group,direction,fi,box)
    low,high=1-box[1],127-box[3];assert low<=high,(name,group,direction,fi,'pose taller than126pixels',box)
    shift=max(low,min(originBase-128,high));anchorY=90+128+shift-originBase;assert 0<anchorY<128
    packedImage=Image.new('RGBA',(128,128));packedImage.alpha_composite(im,(0,shift));im=packedImage;box=im.getbbox();assert box[0]>0 and box[1]>0 and box[2]<128 and box[3]<128
    x,y,xx,yy=box;a=np.array(im.crop(box),dtype=np.uint32);v=(((a[:,:,3]>=128).astype(np.uint32)<<15)|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3)).astype('<u2');raw=struct.pack('<8I',128,128,1,40,1,64,anchorY,v.nbytes|0x80000000)+struct.pack('<3I',0,1,100)*40+struct.pack('<I',0)+struct.pack('<5I',x,y,xx-x,yy-y,0)+v.tobytes();cp=zlib.compress(raw,9);frames.append((len(payload),len(cp),len(raw),zlib.crc32(cp)));payload+=cp
    if fi==0 and group<2:
     sheet.alpha_composite(im,(direction*128,group*128))
     if group==0:
      ys,xs=np.where(np.asarray(im)[:,:,3]>=128);low=ys>=ys.max()-13;xs,ys=xs[low],ys[low];fx=(xs.min()+xs.max())*.5;fy=((ys[xs<=fx]+1).max()+(ys[xs>=fx]+1).max())*.5;actorContact.append([float(64-fx),float(anchorY-fy)])
   actions.append((first,len(frames)-first,max(20,round(delays[ai]))))
 contacts.append(actorContact)
 sheet.save(R/'Validation'/('campaign-'+name.lower()+'200.png'));report.append({'name':name,'body':stem,'head':head,'hairColour':colour,'sourceAttackGroup':10 if name in ('Roan','Judia')else 5,'sources':{str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in sources}})
(R/'Campaign/actors.bin').write_bytes(payload)
reviewPath=R/'Preparation/Opening-Staging200.json';reviewed=json.loads(reviewPath.read_text())if reviewPath.exists()else {}
header=['/* Generated original player bodies + heads, one displayed pose per actor. */',
 '#ifndef MYRO_CAMPAIGN_ACTOR_DATA200_H','#define MYRO_CAMPAIGN_ACTOR_DATA200_H',
 f'#define CAMPAIGN_ACTOR_COUNT200 {len(plan)}u','#define CAMPAIGN_ACTIONS_PER_ACTOR200 48u','#define CAMPAIGN_OPENING_READY200 '+('1u'if reviewed.get('hostStagingReviewed')and reviewed.get('actorPackSHA256')==hashlib.sha256(payload).hexdigest()else '0u'),f'#define CAMPAIGN_FRAME_COUNT200 {len(frames)}u',f'#define CAMPAIGN_ACTOR_BYTES200 {len(payload)}u',
 'static const struct{unsigned offset,packed,raw,crc;}campaignFrames200[]={'+','.join('{%du,%du,%du,%du}'%r for r in frames)+'};',
 'static const struct{unsigned first,count,ms;}campaignActions200[]={'+','.join('{%du,%du,%du}'%r for r in actions)+'};',
 f'static const float campaignContact200[{len(plan)}][8][2]='+str(contacts).replace('[','{').replace(']','}')+';','#endif']
(S/'campaign_actor_data200.h').write_text(chr(10).join(header)+chr(10))
(R/'Preparation/Campaign-Actors200.json').write_text(json.dumps({'bytes':len(payload),'frames':len(frames),'maxPoseRaw':max(r[2]for r in frames),'actors':report},indent=2,ensure_ascii=False)+'\n')
print('Prepared',len(frames),'source poses;',len(payload),'compressed bytes; max pose raw',max(r[2]for r in frames))
