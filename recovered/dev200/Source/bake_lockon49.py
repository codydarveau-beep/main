"""MIT. Lossless original lockon128.tga -> native BGRA; no custom redraw.
Requires the exact original resource returned by Original-Casting collector.
"""
from pathlib import Path
from PIL import Image
import zlib,json,hashlib
from asset_index49 import paths
r=Path(__file__).resolve().parent;p=paths.get('data\\texture\\effect\\lockon128.tga')
if p is None:raise SystemExit('Original lockon128.tga not returned yet; no substitute generated.')
im=Image.open(p).convert('RGBA');assert im.size==(128,128);raw=im.tobytes('raw','BGRA');cp=zlib.compress(raw,9)
(r/'lockon_asset49.h').write_text('/* Original target marker, lossless BGRA. */\n#define LOCKON49_AVAILABLE 1\nstatic const unsigned char lockonPacked49[]={'+','.join(map(str,cp))+'};\n')
(r/'lockon49.json').write_text(json.dumps(dict(sourceSha256=hashlib.sha256(p.read_bytes()).hexdigest(),rawSha256=hashlib.sha256(raw).hexdigest(),width=128,height=128,source='roBrowserLegacy2dc0d153 LockOnTarget.js/.vs/.fs'),indent=2)+'\n')
print('PASS original128x128 lock-on texture converted without redrawing; alpha preserved')
