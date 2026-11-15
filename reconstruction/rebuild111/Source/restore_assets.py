"""MIT. Restore generated C arrays from the preserved packed assets.
No original client archives or third-party Python libraries required.
"""
from pathlib import Path
import json,hashlib,sys,zlib
root=Path(__file__).resolve().parent.parent
index=json.loads((root/'Packed/index.json').read_text());data=(root/'Packed/world.bin').read_bytes();output=Path(sys.argv[1]) if len(sys.argv)>1 else root/'Source/town_assets.c'
with output.open('w') as f:
 f.write('/* Generated from supplied game assets; original ownership retained. */\n')
 for row in index:
  name=row['name'];cp=data[row['offset']:row['offset']+row['size']];assert len(cp)==row['size'] and hashlib.sha256(cp).hexdigest()==row['sha256'];raw=zlib.decompress(cp);assert len(raw)==row['raw']
  f.write('const unsigned int %s_raw=%d,%s_size=%d;\nconst unsigned char %s[]={\n'%(name,len(raw),name,len(cp),name))
  for i in range(0,len(cp),32):f.write(','.join(map(str,cp[i:i+32]))+',\n')
  f.write('};\n')
print('Restored generated asset source:',output)
