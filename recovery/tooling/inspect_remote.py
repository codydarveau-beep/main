import json,zipfile,hashlib
from pathlib import Path
b=Path('/workspace/work/recovery'); files=json.load(open(b/'remote-verified.json'));out=[]; docs=[]
for x in files:
 if not x['path'].endswith('.zip'):continue
 with zipfile.ZipFile(x['location']) as z:
  names=z.namelist();a={'path':x['path'],'crcFailure':z.testzip(),'entries':[{'name':i.filename,'bytes':i.file_size,'crc32':format(i.CRC,'08x')} for i in z.infolist()]};a['sourceFiles']=sum('/Source/' in n or n.startswith('Source/') for n in names);out.append(a)
  for n in names:
   if any(t in n.lower() for t in ['recover','rebuild','start-here','build-notes','source-reference']) and n.lower().endswith(('.txt','.md','.json','.sh')):
    docs.append({'archive':x['path'],'path':n,'content':z.read(n).decode('utf-8','replace')})
json.dump(out,open(b/'remote-archives.json','w'));json.dump(docs,open(b/'archive-recovery-instructions.json','w'),indent=2)
print('remote zips',len(out),'CRC failures',sum(bool(x['crcFailure']) for x in out));print('with Source',[(x['path'],x['sourceFiles']) for x in out if x['sourceFiles']][-15:]);print('instruction docs',len(docs))
for x in files:
 if x['path'].endswith('.sha256'):
  expected=Path(x['location']).read_text().split()[0];pkg=x['path'][:-7];match=next((y for y in files if y['path']==pkg),None)
  if match:
   h=hashlib.sha256(Path(match['location']).read_bytes()).hexdigest()
   if h!=expected:print('SHA256 MISMATCH',pkg)
print('sidecar verification complete')
