"""Read-only verification of the supplied ten effect bitmap payloads."""
import sys,zipfile,io,csv,hashlib,json
from PIL import Image
with zipfile.ZipFile(sys.argv[1])as z:
 rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 assert len(rows)==10
 for row in rows:
  b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256'];assert len(b)==int(row['bytes']);Image.open(io.BytesIO(b)).verify()
 print('PASS all10 supplied textures, SHA256/byte counts/image decode')
