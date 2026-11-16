from pathlib import Path
import json,re,zlib,hashlib
from PIL import Image
R=Path(__file__).resolve().parent.parent;D=R/'Restoration252';x=(R.parent/'packet194/released-default.xbe').read_bytes();source=(R/'Source/skin_assets.c').read_text();m=re.search(r'skin_image\[\]\s*=\s*\{([^}]+)\}',source);old=zlib.decompress(bytes(map(int,m[1].split(','))));rows=[]
Image.frombytes('RGBA',(512,2048),old,'raw','BGRA').crop((0,1904,224,1920)).save(D/'buttons-source253.png')
for match in re.finditer(b'\x78[\x01\x5e\x9c\xda]',x):
 at=match.start()
 try:
  data=x[at:at+1000000];z=zlib.decompressobj();raw=z.decompress(data,4194305)
  if not z.eof or len(raw)!=4194304:continue
  packed=len(data)-len(z.unused_data);(D/f'skin-{at:x}.zlib').write_bytes(data[:packed]);Image.frombytes('RGBA',(512,2048),raw,'raw','BGRA').crop((0,1904,224,1920)).save(D/f'buttons-native-{at:x}.png');rows.append(dict(offset=at,packed=packed,rawSHA256=hashlib.sha256(raw).hexdigest(),matchesSource=raw==old,buttonStripMatches=raw[1904*2048:1920*2048]==old[1904*2048:1920*2048]))
 except zlib.error:pass
(R/'Validation/Skin-Inventory253.json').write_text(json.dumps(dict(candidates=rows),indent=2)+'\n');print(rows)
