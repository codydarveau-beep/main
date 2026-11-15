# GPL-3.0-or-later. Original effect textures and source shader transparency thresholds.
from pathlib import Path
from PIL import Image
import zlib,hashlib,json
import numpy as np
r=Path(__file__).resolve().parent;lib=r.parent.parent/'asset-library';names=['ring_red.tga','ring_blue.tga','ring_yellow.tga','ring_black.tga','aaa copy.bmp'];out='/* Original textures, lossless BGRA; roBrowser source shader thresholds are applied at upload. */\n';rows=[]
for i,name in enumerate(names):
 p=list(lib.glob('*/data/texture/effect/'+name))[-1];im=Image.open(p).convert('RGBA');assert im.size==((128,128)if i==4 else(64,64));raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9);out+='static const unsigned char fieldTexPacked48_%d[]={%s};\n'%(i,','.join(map(str,cp)));rows.append(dict(name=name,sha256=hashlib.sha256(p.read_bytes()).hexdigest(),raw=len(raw)))
out+='static const struct {const unsigned char*p;unsigned packed,side;}fieldTexDefs48[]={'+','.join('{fieldTexPacked48_%d,sizeof(fieldTexPacked48_%d),%d}'%(i,i,128 if i==4 else 64)for i in range(5))+'};\n'
(r/'field_textures48.h').write_text(out);(r/'field_textures48.json').write_text(json.dumps(rows,indent=2)+'\n')
