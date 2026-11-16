from pathlib import Path
import hashlib,json,re,zlib
R=Path(__file__).resolve().parent.parent;D=R/'Restoration252';D.mkdir(exist_ok=True);x=(R.parent/'packet194/released-default.xbe').read_bytes();rows=[]
for match in re.finditer(b'\x78[\x01\x5e\x9c\xda]',x):
 at=match.start()
 try:
  z=zlib.decompressobj();raw=z.decompress(x[at:at+1000000],1048577)
  if not z.eof or len(raw)!=614400:continue
  packed=1000000-len(z.unused_data)if len(x)-at>=1000000 else len(x)-at-len(z.unused_data)
  p=D/f'released-ui-{at:08x}.zlib';p.write_bytes(x[at:at+packed]);rows.append(dict(offset=at,packed=packed,raw=len(raw),rawSHA256=hashlib.sha256(raw).hexdigest(),path=str(p.relative_to(R))))
 except zlib.error:pass
(R/'Validation/Embedded-UI-Inventory252.json').write_text(json.dumps(dict(source='exact released 1.10.0 executable',candidates=rows,scope='Lossless embedded640x480 RGB565 screen inventory; screen identity not assumed from byte size'),indent=2)+'\n');print('Recovered full-screen candidates:',len(rows))
