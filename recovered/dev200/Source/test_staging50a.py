"""MIT. Actual pack staging from50 and50a, idempotence and wrong-input safety."""
from pathlib import Path
import hashlib,json,shutil,subprocess,tempfile
r=Path(__file__).resolve().parent.parent.parent;s=r/'test50a/Source'
meta=json.loads((s/'stage_assets50.json').read_text());sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
with tempfile.TemporaryDirectory(prefix='myro-stage50a-')as td:
 d=Path(td);src=d/'Source';src.mkdir()
 for name in ['stage_base_assets50.py','stage_assets50.json']:shutil.copy2(s/name,src/name)
 def run(iso,ok=True):
  result=subprocess.run(['python3',str(src/'stage_base_assets50.py'),str(iso)],capture_output=True,text=True);assert (result.returncode==0)==ok,result.stderr
 for version in ['50','50a']:
  run(r/('test'+version)/'Source'/('MyRO-Xbox-Test-'+version+'.iso'))
  for name,q in meta.items():
   dest=d/q['directory']/name;assert dest.stat().st_size==q['bytes']and sha(dest)==q['sha256']
 first=next(iter(meta));dest=d/meta[first]['directory']/first;dest.write_bytes(b'preserve different pack');run(s/'MyRO-Xbox-Test-50a.iso',False);assert dest.read_bytes()==b'preserve different pack'
 run(r/'test49/Source/MyRO-Xbox-Test-49.iso',False);assert dest.read_bytes()==b'preserve different pack'
print('PASS50a all six packs stage from50/50a; idempotence, prior-version rejection and conflicting-destination preservation.')
