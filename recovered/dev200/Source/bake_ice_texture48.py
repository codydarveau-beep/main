# Original client texture; no synthetic replacement or resampling.
from pathlib import Path
from PIL import Image
import zlib,hashlib,json
r=Path(__file__).resolve().parent;p=r.parent.parent/'asset-library/Test45-return/data/texture/effect/ice.tga';im=Image.open(p).convert('RGBA');assert im.size==(128,128);raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9);(r/'ice_texture48.h').write_text('/* Original RO ice.tga; byte-exact decoded BGRA128x128. */\nstatic const unsigned char iceTexturePacked48[]={'+','.join(map(str,cp))+'};\n');(r/'ice_source48.json').write_text(json.dumps(dict(textureSHA256=hashlib.sha256(p.read_bytes()).hexdigest(),decodedSHA256=hashlib.sha256(raw).hexdigest(),reference='MrAntares/roBrowserLegacy 2dc0d1538edbb2a35f06b184552d8579d27b6639: EffectTable EF_ICEWALL74, QuadHorn vertices/UVs and shader'),indent=2));print('PASS original Ice Wall texture',len(cp),'packed,65536resident')
