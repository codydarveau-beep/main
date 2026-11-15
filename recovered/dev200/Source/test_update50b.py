"""MIT. Run the shipped PowerShell updater on real disc images and failure cases."""
from pathlib import Path
import hashlib,json,os,shutil,subprocess,tempfile
r=Path(__file__).resolve().parent.parent.parent
release=r/'release50b';manifest=json.loads((release/'update.json').read_text());sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
pwsh=r/'pwsh/bin/pwsh';env=os.environ.copy();env.update(XDG_CACHE_HOME=str(r/'pwsh/cache'),XDG_CONFIG_HOME=str(r/'pwsh/config'),XDG_DATA_HOME=str(r/'pwsh/data'))
with tempfile.TemporaryDirectory(prefix='myro-update50-')as td:
 d=Path(td);pack=d/'Update';pack.mkdir()
 for name in ['Update-Test50b.ps1','update.json',*[p['name']for p in manifest['payload']]]:shutil.copy2(release/name,pack/name)
 def run(base,ok=True,text=None):
  result=subprocess.run([str(pwsh),'-NoProfile','-File',str(pack/'Update-Test50b.ps1'),'-BaseIso',str(base)],env=env,text=True,capture_output=True)
  assert (result.returncode==0)==ok,(result.stdout,result.stderr)
  if text:assert text.lower()in result.stdout.lower(),result.stdout
  assert not list(base.parent.glob('*.building'))
  return result
 for version in ['50a']:
  case=d/version;case.mkdir();base=case/'MyRO-Current.iso';shutil.copy2(r/('test'+version)/'Source'/('MyRO-Xbox-Test-'+version+'.iso'),base);old=sha(base)
  run(base,text='SUCCESS');assert sha(base)==manifest['targetSHA256'];backups=list(case.glob('*.before-test50b-*.iso'));assert len(backups)==1 and sha(backups[0])==old
  run(base,text='already');assert len(list(case.glob('*.before-test50b-*.iso')))==1
 # A separately named baseline remains intact; repeat preserves unrelated output.
 case=d/'named';case.mkdir();base=case/'original49.iso';shutil.copy2(r/'test50a/Source/MyRO-Xbox-Test-50a.iso',base);original=sha(base);run(base);assert sha(base)==original and sha(case/'MyRO-Current.iso')==manifest['targetSHA256']
 (case/'MyRO-Current.iso').write_bytes(b'unrelated existing ISO');run(base,False,text='different MyRO-Current.iso');assert (case/'MyRO-Current.iso').read_bytes()==b'unrelated existing ISO'and sha(base)==original
 # Missing/corrupt/truncated payload and modified baseline never replace a file.
 case=d/'faults';case.mkdir();base=case/'MyRO-Current.iso';shutil.copy2(r/'test50a/Source/MyRO-Xbox-Test-50a.iso',base);old=sha(base);part=pack/manifest['payload'][0]['name'];good=part.read_bytes()
 part.unlink();run(base,False);assert sha(base)==old
 part.write_bytes(good[:-1]);run(base,False,text='damaged update part');assert sha(base)==old
 corrupt=bytearray(good);corrupt[0]^=1;part.write_bytes(corrupt);run(base,False,text='damaged update part');assert sha(base)==old
 part.write_bytes(good);changed=bytearray(base.read_bytes());changed[-1]^=1;base.write_bytes(changed);modified=sha(base);run(base,False,text='exact');assert sha(base)==modified
 assert not list(case.glob('*.before-test50b-*.iso'))
 # Exact manifest range integrity is checked before committing a rebuilt image.
 shutil.copy2(r/'test50a/Source/MyRO-Xbox-Test-50a.iso',base);bad=json.loads(json.dumps(manifest));bad['baselines'][0]['operations'][0]['offset']=-1;(pack/'update.json').write_text(json.dumps(bad));run(base,False,text='Invalid patch range');assert sha(base)==old
assert (release/'Apply-Update.cmd').read_bytes().startswith(b'@echo off\r\n')
print('PASS50b actual PowerShell: exact Test50a reconstruction, verified rollback, idempotence, named baseline preservation, unrelated-output protection, missing/truncated/corrupt payloads, wrong baseline and invalid-range cleanup; ASCII CMD.')
