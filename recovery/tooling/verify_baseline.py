import mmap,struct,json,hashlib
from pathlib import Path
b=Path('/workspace/work/recovery');r=json.load(open(b/'remote-verified.json'));manifest=json.load(open(next(x['location'] for x in r if x['path']=='release1.10.0.json')))
with (b/'released-1.10.0.iso').open('rb') as f,mmap.mmap(f.fileno(),0,access=mmap.ACCESS_READ) as data:
 assert data[65536:65556]==b'MICROSOFT*XBOX*MEDIA';sector,size=struct.unpack_from('<II',data,65556);files={};seen=set()
 def visit(offset):
  assert offset not in seen and 0<=offset<=size-14;seen.add(offset);p=sector*2048+offset;left,right,start,length,attr,n=struct.unpack_from('<HHIIBB',data,p);name=data[p+14:p+14+n].decode('ascii')
  if left:visit(left*4)
  h=hashlib.sha256();begin=start*2048
  for i in range(0,length,4194304):h.update(data[begin+i:begin+min(length,i+4194304)])
  files[name]={'bytes':length,'sha256':h.hexdigest(),'isoOffset':begin}
  if right:visit(right*4)
 visit(0)
 assert set(files)==set(manifest['files'])
 for name,q in manifest['files'].items():assert all(files[name][k]==q[k] for k in ['bytes','sha256']),name
json.dump({'verifiedFiles':len(files),'files':files},open(b/'baseline-file-verification.json','w'),indent=2)
print('all',len(files),'released files match manifest')
