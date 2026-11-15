import json,hashlib,os,urllib.request,concurrent.futures
from pathlib import Path
base=Path('/workspace/work/recovery'); tree=json.load(open(base/'remote-tree.json'))['tree']; dest=base/'remote-originals'; dest.mkdir(exist_ok=True)
def task(x):
 p=x['path']; local=Path('/workspace/main')/p; target=dest/p
 def blob(path):
  h=hashlib.sha1();h.update(('blob '+str(path.stat().st_size)+'\0').encode())
  with path.open('rb') as f:
   for b in iter(lambda:f.read(4194304),b''):h.update(b)
  return h.hexdigest()
 if local.is_file() and blob(local)==x['sha']: return {'path':p,'location':str(local),'gitBlobVerified':True,'downloaded':False}
 target.parent.mkdir(parents=True,exist_ok=True)
 urllib.request.urlretrieve('https://raw.githubusercontent.com/codydarveau-beep/main/9aeac8c16ddccbe3b4a8a2f359a30402b897ada4/'+p,target)
 if blob(target)!=x['sha']:raise ValueError('blob mismatch '+p)
 return {'path':p,'location':str(target),'gitBlobVerified':True,'downloaded':True}
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool: out=list(pool.map(task,[x for x in tree if x['type']=='blob']))
json.dump(out,open(base/'remote-verified.json','w'),indent=2)
print('verified',len(out),'downloaded',sum(x['downloaded'] for x in out),flush=True)
