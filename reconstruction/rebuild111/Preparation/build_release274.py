"""Stage reviewed corrective Source; only public version labels differ."""
from pathlib import Path
import json,hashlib,shutil
R=Path(__file__).resolve().parent.parent;D=R.parent/'release1111';S=D/'Source';V=R/'Validation';S.mkdir(parents=True,exist_ok=True);(D/'XboxFiles').mkdir(exist_ok=True)
n=json.loads((V/'Normal-Complete-Checks244.json').read_text());assert n['passed']and n['normalReleaseWideChecksComplete']
p=json.loads((V/'Restoration-Normal-Checks270.json').read_text());assert p['passed']and p['sourceFiles']==n['sourceFiles']
for name in ['Restoration-Review-Pass1-271.json','Restoration-Review-Pass2-272.json']:
 d=json.loads((V/name).read_text());assert d['passed']and d['sourceDigest']==n['sourceDigest']and d['normalCompletedBeforeReview']
for name,h in n['sourceFiles'].items():assert hashlib.sha256((R/name).read_bytes()).hexdigest()==h,name
for p in(R/'Source').rglob('*'):
 if p.is_file()and(p.suffix in ['.h','.c','.s','.inc','.inl','.vp']or p.name=='Makefile'):
  q=S/p.relative_to(R/'Source');q.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(p,q)
p=S/'pause_draw.h';s=p.read_text();assert s.count('MyRO 1.11.0 DEV')==1;p.write_text(s.replace('MyRO 1.11.0 DEV','MyRO 1.11.1'))
p=S/'Makefile';s=p.read_text();assert 'XBE_TITLE = MyRO\\ v1.11.0\\ RECOVERY'in s;p.write_text(s.replace('XBE_TITLE = MyRO\\ v1.11.0\\ RECOVERY','XBE_TITLE = MyRO\\ v1.11.1'))
changes={}
for p in S.rglob('*'):
 if p.is_file():
  old=R/'Source'/p.relative_to(S)
  if p.read_bytes()!=old.read_bytes():changes[str(p.relative_to(S))]=dict(original=hashlib.sha256(old.read_bytes()).hexdigest(),release=hashlib.sha256(p.read_bytes()).hexdigest())
assert set(changes)=={'Makefile','pause_draw.h'}
(V/'Release-Source-Labels274.json').write_text(json.dumps(dict(sourceDigest=n['sourceDigest'],version='1.11.1',changes=changes,scope='Separate native corrective build; only title/pause version labels change. Reviewed private Source remains unchanged.'),indent=2)+'\n')
print('PASS reviewed corrective Source staged with public1.11.1 labels; native build and packaging validation still required.')
