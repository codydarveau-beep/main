"""Encode approved eight-view cabinet art into bounded native ARGB1555 frames.
Only technical slicing/resizing/texture encoding; originals are never changed.
"""
from pathlib import Path
import json,hashlib,zlib,struct,shutil,math
from PIL import Image
import numpy as np
from scipy.ndimage import label,find_objects
R=Path(__file__).resolve().parent.parent;D=R/'Guild/Directional197';D.mkdir(parents=True,exist_ok=True)
files=['exec-2da50094-49e3-4337-932f-7a9efb4758c0.png','exec-68239fa5-8f01-43b4-9baf-d84fc8a7f07a.png','exec-d8aac340-cd3a-4c19-bd7c-5fb515050857.png','exec-b1e482e0-3e92-4997-9560-1c1a4cb153df.png','exec-15eac072-1f54-44d9-8a9a-0d529a8a4d08.png','exec-459e92a8-2557-4a3d-9a66-2532998c2a3c.png'];names=['pong','patrol','snake','breaker','puzzle','maze'];frames=[];sources=[];contact=Image.new('RGBA',(8*64,6*96))
with (D/'views.bin').open('wb')as bank:
 for game,(name,file)in enumerate(zip(names,files)):
  source=Path('/workspace/generated_images')/file;target=D/(name+'.png')
  if source.exists():shutil.copy2(source,target)
  im=Image.open(target).convert('RGBA');sources.append(dict(cabinet=name,path=target.name,sha256=hashlib.sha256(target.read_bytes()).hexdigest(),generatedSource=str(source),provenance='New eight-view art generated with image_gen from recovered guildhall atlas; Pong face approved by user; original PNG unchanged'))
  components,n=label(np.asarray(im.getchannel('A'))>=128);areas=np.bincount(components.ravel());ids=sorted(range(1,len(areas)),key=lambda i:areas[i],reverse=True)[:8];regions=find_objects(components);assert len(ids)==8 and min(areas[i]for i in ids)>10000
  boxes=[(regions[i-1][1].start,regions[i-1][0].start,regions[i-1][1].stop,regions[i-1][0].stop)for i in ids];boxes.sort(key=lambda b:(b[1]+b[3])/2);boxes=sorted(boxes[:4],key=lambda b:b[0])+sorted(boxes[4:],key=lambda b:b[0])
  for view,bbox in enumerate(boxes):
   sprite=im.crop(bbox);scale=min(60/sprite.width,90/sprite.height);sprite=sprite.resize((max(1,round(sprite.width*scale)),max(1,round(sprite.height*scale))),Image.Resampling.LANCZOS);tile=Image.new('RGBA',(64,96));tile.paste(sprite,((64-sprite.width)//2,94-sprite.height));raw=bytearray()
   for red,green,blue,alpha in tile.getdata():raw+=struct.pack('<H',0 if alpha<128 else 0x8000|((red>>3)<<10)|((green>>3)<<5)|(blue>>3))
   packed=zlib.compress(bytes(raw),9);frames.append(dict(game=game,view=view,offset=bank.tell(),packed=len(packed),raw=len(raw),crc=zlib.crc32(packed),rawCRC=zlib.crc32(raw),sourceCellBox=bbox));bank.write(packed)
   # Preview the ACTUAL one-bit-alpha packed frame, not the high-resolution draft.
   pixels=[((v>>10&31)*255//31,(v>>5&31)*255//31,(v&31)*255//31,255 if v&0x8000 else 0)for v, in struct.iter_unpack('<H',raw)];tile.putdata(pixels);contact.paste(tile,(view*64,game*96))
contact.save(D/'encoded-preview.png')
h='/* Newly authored eight-view cabinets. One native frame per cabinet is resident. */\n#ifndef MYRO_GUILD_VIEWS197_H\n#define MYRO_GUILD_VIEWS197_H\n#define GUILD_VIEWS_BYTES197 %du\n#define GUILD_VIEW_RAW197 12288u\n#define GUILD_VIEW_COUNT197 48u\nstatic const struct{unsigned offset,packed,raw,crc,rawCRC;}guildViews197[]={\n'%(D/'views.bin').stat().st_size
h+=''.join('{'+','.join(str(f[k])+'u'for k in ['offset','packed','raw','crc','rawCRC'])+'},\n'for f in frames)+'};\n#endif\n';(R/'Source/guild_views_data197.h').write_text(h)
(D/'manifest.json').write_text(json.dumps(dict(sources=sources,frames=frames,bankSHA256=hashlib.sha256((D/'views.bin').read_bytes()).hexdigest(),frameSize=[64,96],floorAnchor=[32,94],cameraViews=['front','front-right','right','back-right','back','back-left','left','front-left'],newArt=True,allAnglesResident=False),indent=2)+'\n')
print('Encoded complete eight-direction cabinet bank; original PNG sources preserved.')
