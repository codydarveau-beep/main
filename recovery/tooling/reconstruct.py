from pathlib import Path
import json,zipfile,hashlib
b=Path('/workspace/work/recovery');r=json.load(open(b/'remote-verified.json'))
def sha(p):
 h=hashlib.sha256()
 with open(p,'rb') as f:
  for c in iter(lambda:f.read(4194304),b''):h.update(c)
 return h.hexdigest()
original=Path('/workspace/myro/test70/Source/MyRO-Xbox-1.9.0.iso');current=original;receipts=[]
for version in ['1.9.3','1.10.0']:
 p=next(x for x in r if x['path']=='downloads/MyRO-'+version+'-Update.zip')['location']
 with zipfile.ZipFile(p) as z:
  n=next(n for n in z.namelist() if n.endswith('/update.json'));m=json.loads(z.read(n));digest=sha(current);baseline=next(v for v in m['baselines'] if v['bytes']==current.stat().st_size and v['sha256']==digest)
  payloads=[]
  for part in m['payload']:
   raw=z.read(n.rsplit('/',1)[0]+'/'+part['name']);assert len(raw)==part['bytes'] and hashlib.sha256(raw).hexdigest()==part['sha256'];payloads.append(raw)
  target=b/('released-'+version+'.iso')
  with current.open('rb') as f,target.open('wb') as out:
   for op in baseline['operations']:
    if op['source']=='payload':out.write(payloads[op['part']][op['offset']:op['offset']+op['length']])
    else:
     f.seek(op['offset']);left=op['length']
     while left:
      c=f.read(min(4194304,left));assert c;out.write(c);left-=len(c)
  assert target.stat().st_size==m['targetBytes'] and sha(target)==m['targetSHA256']
  receipts.append({'version':version,'baseline':str(current),'baselineSHA256':digest,'target':str(target),'targetBytes':target.stat().st_size,'targetSHA256':m['targetSHA256'],'verified':True})
  print('verified recovered ISO',version,flush=True)
  if current!=original:current.unlink()
  current=target
json.dump(receipts,open(b/'iso-reconstruction-receipt.json','w'),indent=2)
