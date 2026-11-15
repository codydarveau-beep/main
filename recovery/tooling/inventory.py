import os,json,hashlib,zipfile,collections,time
from pathlib import Path
base=Path('/workspace/work/recovery'); rows=json.load(open(base/'initial-files.json'))
def sha(p):
 h=hashlib.sha256()
 with open(p,'rb') as f:
  for b in iter(lambda:f.read(4*1024*1024),b''):h.update(b)
 return h.hexdigest()
selected=[]
for x in rows:
 p=x['path']; ext=Path(p).suffix.lower()
 if not x['symlink'] and (('/Source/' in p and ext not in ['.o','.a','.exe','.xbe','.bin','.iso','.elf']) or (p.startswith('/workspace/myro/') and ext in ['.md','.txt','.json','.py','.sh','.ps1','.cmd','.conf','.yml'])):selected.append(x)
with zipfile.ZipFile(base/'source-and-recovery-backup.zip','w',zipfile.ZIP_DEFLATED,compresslevel=6) as z:
 for x in selected:z.write(x['path'],x['path'].removeprefix('/workspace/'))
print('backed up',len(selected),'files',flush=True)
archives=[]
for x in rows:
 p=x['path']
 if not p.lower().endswith('.zip') or x['symlink']:continue
 a={'path':p,'bytes':x['bytes'],'sha256':sha(p)}
 try:
  with zipfile.ZipFile(p) as z:
   a['entries']=[{'name':i.filename,'bytes':i.file_size,'crc32':format(i.CRC,'08x')} for i in z.infolist()]
   a['crcFailure']=z.testzip()
 except Exception as e:a['error']=str(e)
 archives.append(a)
json.dump(archives,open(base/'local-archives.json','w'))
json.dump({'backupSHA256':sha(base/'source-and-recovery-backup.zip'),'selectedFiles':len(selected),'archives':len(archives),'archiveErrors':[a['path'] for a in archives if a.get('error') or a.get('crcFailure')]},open(base/'backup-receipt.json','w'),indent=2)
print((base/'backup-receipt.json').read_text(),flush=True)
