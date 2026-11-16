from pathlib import Path
import json,hashlib,shutil
R=Path(__file__).resolve().parent.parent;D=R.parent/'release111';S=D/'Source';S.mkdir(exist_ok=True);V=R/'Validation'
n=json.loads((V/'Normal-Complete-Checks244.json').read_text());assert n['passed']
for name in ['Additional-Review-Pass1-245.json','Additional-Review-Pass2-247.json']:
 d=json.loads((V/name).read_text());assert d['passed']and d['sourceDigest']==n['sourceDigest']
for name,h in n['sourceFiles'].items():assert hashlib.sha256((R/name).read_bytes()).hexdigest()==h,name
for p in (R/'Source').rglob('*'):
 if p.is_file()and(p.suffix in ['.h','.c','.s','.inc','.inl','.vp']or p.name=='Makefile'):
  q=S/p.relative_to(R/'Source');q.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(p,q)
p=S/'pause_draw.h';s=p.read_text();assert s.count('MyRO 1.11.0 DEV')==1;p.write_text(s.replace('MyRO 1.11.0 DEV','MyRO 1.11.0'))
p=S/'Makefile';s=p.read_text();s=s.replace('XBE_TITLE = MyRO\\ v1.11.0\\ RECOVERY','XBE_TITLE = MyRO\\ v1.11.0');p.write_text(s)
changes={}
for p in S.rglob('*'):
 if p.is_file():
  old=R/'Source'/p.relative_to(S)
  if p.read_bytes()!=old.read_bytes():changes[str(p.relative_to(S))]=dict(original=hashlib.sha256(old.read_bytes()).hexdigest(),release=hashlib.sha256(p.read_bytes()).hexdigest())
assert set(changes)=={'Makefile','pause_draw.h'}
(V/'Release-Source-Labels250.json').write_text(json.dumps(dict(sourceDigest=n['sourceDigest'],changes=changes,scope='Separate native release build; only certificate title and pause version label change. Reviewed private source/artifacts remain preserved.'),indent=2)+'\n')
