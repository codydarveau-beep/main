"""Free reproducible host binaries only after normal/review completion, before ISO staging."""
from pathlib import Path
import hashlib,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';n=json.loads((V/'Normal-Complete-Checks244.json').read_text());assert n['passed']
for name in ['Restoration-Review-Pass1-271.json','Restoration-Review-Pass2-272.json']:
 d=json.loads((V/name).read_text());assert d['passed']and d['sourceDigest']==n['sourceDigest']
removed=[]
for p in V.iterdir():
 if not p.is_file()or not(p.name.endswith('_asan')or p.suffix=='.so'):continue
 with p.open('rb')as f:magic=f.read(4)
 if magic!=b'\x7fELF':continue
 removed.append(dict(path=str(p.relative_to(R)),bytes=p.stat().st_size));p.unlink()
(V/'Reproducible-Host-Cleanup273.json').write_text(json.dumps(dict(reason='After normal checks and two extra reviews; space for sequential ISO reconstruction',removed=removed,preserved=['All source and test fixtures','All asset/recovery archives and exact released baseline','Earlier published ZIP','Native reference ELF and input binaries','Logs and JSON evidence']),indent=2)+'\n');print('Removed',len(removed),'reproducible host binaries; bytes',sum(p['bytes']for p in removed))
