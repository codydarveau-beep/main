"""Build bounded current-map, native-large minimaps from original client artwork."""
from pathlib import Path
import re,zlib,json,hashlib,struct
import numpy as np
from PIL import Image
R=Path('/workspace/myro/dev200');S=R/'Source';s=(S/'world_data.h').read_text()
names=json.loads('['+re.search(r'mapNames\[\]=\{([^}]+)',s)[1]+']')
widths=list(map(int,re.search(r'mapWidths\[\]=\{([^}]+)',s)[1].split(',')));heights=list(map(int,re.search(r'mapHeights\[\]=\{([^}]+)',s)[1].split(',')))
old=[tuple(map(int,m))for m in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',re.search(r'minimapBlobs45\[WORLD_MAP_COUNT\]=\{(.+?)\};',s,re.S)[1])]
index={}
for p in Path('/workspace/myro/asset-library').rglob('*.bmp'):
 if p.parent.name.casefold()=='map':index.setdefault(p.stem.casefold(),[]).append(p)
blob=bytearray();entries=[];report=[];fallbacks=[]
with (R/'Packed/world.bin').open('rb')as world:
 for i,name in enumerate(names):
  paths=index.get(name.casefold(),[])
  if paths:
   paths.sort(key=lambda p:(max([int(n)for n in re.findall(r'\d+',str(p.relative_to('/workspace/myro/asset-library')).split('/')[0])],default=0),str(p)))
   path=paths[-1];im=Image.open(path).convert('RGB');a=np.array(im);pink=(a[:,:,0]>230)&(a[:,:,1]<30)&(a[:,:,2]>230);a[pink]=[234,240,245];im=Image.fromarray(a)
   gw,gh=widths[i]*2,heights[i]*2
   if gw*108>=gh*144:w,h=144,max(1,gh*144//gw)
   else:w,h=max(1,gw*108//gh),108
   canvas=Image.new('RGB',(144,108),(234,240,245));canvas.paste(im.resize((w,h),Image.Resampling.LANCZOS),((144-w)//2,(108-h)//2));source=str(path);source_size=im.size
  else:
   off,packed,raw,crc=old[i];world.seek(off);cp=world.read(packed);assert zlib.crc32(cp)==crc;data=zlib.decompress(cp);assert len(data)==raw
   canvas=Image.frombytes('RGBA',(96,72),data,'raw','BGRA').convert('RGB').resize((144,108),Image.Resampling.NEAREST);source='existing 96x72 fallback';source_size=(96,72);fallbacks.append(name)
  a=np.asarray(canvas,dtype=np.uint16);pixels=(0x8000|((a[:,:,0]>>3)<<10)|((a[:,:,1]>>3)<<5)|(a[:,:,2]>>3)).astype('<u2');raw=pixels.tobytes();cp=zlib.compress(raw,9);entries.append((len(blob),len(cp),len(raw),zlib.crc32(raw)));blob+=cp;report.append({'id':i,'map':name,'source':source,'sourceSize':source_size,'packed':len(cp)})
  if name in ['prontera','lighthalzen','gl_knt01']:canvas.save(R/'Validation'/('minimap-native-'+name+'200.png'))
assert len(entries)==494
(R/'Interface').mkdir(exist_ok=True);(R/'Interface/minimaps.bin').write_bytes(blob)
(S/'minimap_data200.h').write_text('/* Generated original minimap art, 144x108 A1R5G5B5. */\n#define MINIMAP_FILE_BYTES200 %du\n#define MINIMAP_W200 144u\n#define MINIMAP_H200 108u\nstatic const WorldBlob minimapBlobs200[WORLD_MAP_COUNT]={\n'%len(blob)+',\n'.join('{%du,%du,%du,%du}'%e for e in entries)+'\n};\n')
(R/'Preparation/Minimap-Assets200.json').write_text(json.dumps({'width':144,'height':108,'fileBytes':len(blob),'fileSHA256':hashlib.sha256(blob).hexdigest(),'currentMapTextureBytes':65536,'nativeArtCount':494-len(fallbacks),'fallbackMaps':fallbacks,'maps':report},indent=2)+'\n')
print('Built',len(blob),'bytes; native original art:',494-len(fallbacks),'fallbacks:',len(fallbacks))
