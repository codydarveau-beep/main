"""MIT. Move byte-identical shipped MP3s to a CRC-checked disc pack.

This changes residency only. No re-encoding, trimming, mapping or gain changes.
"""
from pathlib import Path
import hashlib
import json
import re
import zlib

r = Path(__file__).resolve().parent
source = (r / 'music_assets.c').read_text()
manifest = r / 'music_pack50.json'
if manifest.exists():
    assert hashlib.sha256(source.encode()).hexdigest() == json.loads(manifest.read_text())['sourceSHA256'], 'Encoded music source differs from the verified source'
out = r.parent / 'Music'
out.mkdir(exist_ok=True)
payload = bytearray()
records = []
for i in range(10):
    size = int(re.search(r'const unsigned music%d_size=(\d+)' % i, source)[1])
    values = re.search(r'const unsigned char music%d\[\]=\{(.*?)\};' % i, source, re.S)[1]
    data = bytes(map(int, re.findall(r'\d+', values)))
    assert len(data) == size and 0 < size <= 2*1024*1024
    records.append(dict(track=i, offset=len(payload), bytes=size,
                        crc=zlib.crc32(data), sha256=hashlib.sha256(data).hexdigest()))
    payload.extend(data)
target = out / 'music.bin'
assert not target.exists() or target.read_bytes() == payload, 'Existing music.bin differs; preserve it for inspection'
if not target.exists():
    target.write_bytes(payload)
h = ['/* MIT. Byte-identical Test49 MP3s; one current track plus a transition. */',
     '#ifndef MYRO_MUSIC_PACK50_H', '#define MYRO_MUSIC_PACK50_H',
     '#define MUSIC_FILE_BYTES50 %du' % len(payload),
     'typedef struct {unsigned offset,bytes,crc;} MusicBlob50;',
     'static const MusicBlob50 musicBlobs50[10]={']
h += ['{%du,%du,0x%08xu},' % (v['offset'],v['bytes'],v['crc']) for v in records]
h += ['};', '#endif']
(r / 'music_pack50.h').write_text('\n'.join(h)+'\n')
(r / 'music_pack50.json').write_text(json.dumps(dict(
    source='Frozen Test49 encoded tracks; original bytes retained',
    sourceSHA256=hashlib.sha256(source.encode()).hexdigest(),
    packBytes=len(payload), packSHA256=hashlib.sha256(payload).hexdigest(),
    tracks=records), indent=2)+'\n')
print('PASS50 identical10 MP3s, disc pack', len(payload),
      'bytes; steady encoded residency <=', max(v['bytes'] for v in records))
