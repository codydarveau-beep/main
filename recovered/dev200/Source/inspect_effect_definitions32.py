"""Read/verify supplied STR batch and list embedded NUL-terminated image names.
The strings are dependency candidates, not a complete semantic STR parser.
python inspect_effect_definitions32.py input.zip output.json
"""
import csv,hashlib,io,json,re,sys,zipfile
out=[]
with zipfile.ZipFile(sys.argv[1])as z:
 report=json.loads(z.read('Report.json'));rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))))
 assert report['complete'] and report['collected']==len(rows)==311
 for row in rows:
  b=z.read(row['payload']);assert hashlib.sha256(b).hexdigest()==row['sha256']
  assert b.startswith(b'STRM'),row['virtual_path']
  candidates=[]
  for chunk in re.findall(rb'[^\x00]{1,255}\x00',b):
   part=chunk[:-1]
   if re.search(rb'\.(bmp|tga|png|jpg)$',part,re.I):
    # Leading binary bytes can adjoin a printable filename; retain only its tail.
    tail=re.search(rb'[\x20-\x7e\x80-\xff]+\.(?:bmp|tga|png|jpg)$',part,re.I)
    if tail:
     try:name=tail[0].decode('cp949')
     except UnicodeDecodeError:name=tail[0].decode('latin1')
     candidates.append(name)
  out.append(dict(path=row['virtual_path'],sha256=row['sha256'],bytes=len(b),image_candidates=sorted(set(candidates))))
open(sys.argv[2],'w',encoding='utf-8').write(json.dumps(dict(report=report,definitions=out,note='Image strings are dependency candidates; original STR rendering is not yet implemented.'),indent=2,ensure_ascii=False))
print('PASS311 STR headers/checksums; dependency candidates indexed')
