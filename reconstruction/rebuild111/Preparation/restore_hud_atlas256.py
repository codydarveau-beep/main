from pathlib import Path
import hashlib,json,re,struct,zlib
R=Path(__file__).resolve().parent.parent;D=R/'Restoration252';nativePacked=(D/'skin-8fc4c8.zlib').read_bytes();raw=bytearray(zlib.decompress(nativePacked));assert len(raw)==512*2048*4
flat=(R.parent/'decompiler203/native-flat203.bin').read_bytes();s=(R/'Source/skin_data.h').read_text();a=s.index('skinRects');rects=[tuple(map(int,m))for m in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',s[a:s.index('};',a)])];table=struct.pack('<'+'H'*len(rects)*4,*[v for r in rects for v in r]);at=flat.find(table);assert at>=0 and len(rects)==801
colors=[int(x,16)for x in re.findall(r'0x([0-9a-fA-F]+)',(R/'Source/skin_colors.h').read_text())];overlay=[]
for i,color in enumerate(colors):
 # Compass initialization owns these verified blank cells at runtime.
 if 95 <= i <= 99:
  x=(i%64)*8;y=256+(i//64)*8
  assert all(struct.unpack_from('<I',raw,((y+dy)*512+x+dx)*4)[0]==0 for dy in range(8)for dx in range(8)),i
  continue
 x=(i%64)*8;y=256+(i//64)*8;current=struct.unpack_from('<I',raw,((y+3)*512+x+3)*4)[0]
 if current==color:continue
 assert all(struct.unpack_from('<I',raw,((y+dy)*512+x+dx)*4)[0]==0 for dy in range(8)for dx in range(8)),i
 for dy in range(8):
  for dx in range(8):struct.pack_into('<I',raw,((y+dy)*512+x+dx)*4,color)
 overlay.append(i)
# Recovery-added solid colors occupy previously unused palette cells only.
packed=zlib.compress(raw,9);p=R/'Source/skin_assets.c';source=p.read_text();source,n=re.subn(r'(skin_image_size=)\d+',lambda m:m[1]+str(len(packed)),source);assert n==1;source,n=re.subn(r'(const unsigned char skin_image\[\]\s*=\s*\{)[^}]+(\};)',lambda m:m[1]+','.join(map(str,packed))+m[2],source);assert n==1;p.write_text(source)
(R/'Validation/HUD-Atlas-Restoration256.json').write_text(json.dumps(dict(passed=True,source='exact released1.10.0 embedded HUD atlas',sourceOffset='0x8fc4c8',nativeRawSHA256=hashlib.sha256(zlib.decompress(nativePacked)).hexdigest(),metadataRects=len(rects),nativeRectTableVA=hex(at+65536),existingColorPalettePreserved=True,blankPaletteCellsAdded=overlay,runtimeCompassPaletteCells=list(range(95,100)),scope='All released artwork pixels retained. Recovery-added solid-color palette entries filled only in verified blank cells so campaign/guild/preview additions remain supported. No redraw or inferred replacement art.',XboxVisualVerification=False),indent=2)+'\n');print('PASS released HUD atlas restored with exact rectangle-layout proof and blank-cell compatibility palette.')
