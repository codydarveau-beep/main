from pathlib import Path
import hashlib,json,os,shutil,subprocess,tempfile,zipfile,mmap
from package_release250 import files,sha
R=Path(__file__).resolve().parent.parent;D=R.parent/'release111';V=R/'Validation';P=D/'MyRO-1.11.0';Z=D/'MyRO-1.11.0-Update.zip'
def pack():
 with zipfile.ZipFile(Z,'w',zipfile.ZIP_DEFLATED,compresslevel=6)as z:
  for p in sorted(P.rglob('*')):
   if p.is_file():z.write(p,'MyRO-1.11.0/'+str(p.relative_to(P)))
 with zipfile.ZipFile(Z)as z:assert z.testzip()is None
pack();checks=[]
with tempfile.TemporaryDirectory(prefix='Actual updater ',dir=D)as temp:
 T=Path(temp)
 with zipfile.ZipFile(Z)as z:z.extractall(T)
 A=T/'MyRO-1.11.0';M=A/'update.json';original=M.read_bytes();m=json.loads(original);baseline=R.parent/'released-1.10.0.iso';accepted=m['baselines'][0];assert len(m['baselines'])==1 and accepted['version']=='1.10.0'
 base=T/'MyRO-Current.iso';os.link(baseline,base)
 def run(input,ok,contains=None):
  p=subprocess.run(['/workspace/myro/pwsh/bin/pwsh','-NoLogo','-NoProfile','-File',str(A/'Update-MyRO1.11.0.ps1'),'-BaseIso',str(input)],capture_output=True,text=True)
  with(V/'actual-updater251.log').open('a')as log:log.write(p.stdout+p.stderr+'\n')
  assert (p.returncode==0)==ok,(p.returncode,p.stdout,p.stderr)
  if contains:assert contains in p.stdout,p.stdout
  assert not list(T.glob('*.building'))
  return p
 run(base,True,'SUCCESS:');assert sha(base)==m['targetSHA256'];backups=list(T.glob('*.before-1.11.0-*.iso'));assert len(backups)==1 and sha(backups[0])==accepted['sha256'];receipt=json.loads((T/'MyRO-1.11.0-receipt.json').read_text(encoding='utf-8-sig'));assert Path(receipt['baseline'])==backups[0]
 with base.open('rb')as f,mmap.mmap(f.fileno(),0,access=mmap.ACCESS_READ)as iso:
  catalog=files(iso);assert set(catalog)==set(m['files'])and len(catalog)==20
  for name,meta in m['files'].items():
   at,n=catalog[name];assert n==meta['bytes']and hashlib.sha256(memoryview(iso)[at:at+n]).hexdigest()==meta['sha256'],name
 checks+=['Actual ZIP extraction and actual PowerShell full reconstruction','Exact ISO hash and all twenty target file hashes','Atomic replacement retains exact baseline rollback image and correct receipt']
 run(base,True,'already contains 1.11.0');checks+=['Idempotent rerun on completed target']
 base.unlink();inp=T/'Released1.10.0.iso';os.link(baseline,inp)
 base.write_bytes(b'existing unrelated output');run(inp,False,'different MyRO-Current.iso');assert base.read_bytes()==b'existing unrelated output';base.unlink();checks+=['Conflicting existing output is preserved']
 part=A/'payload.001.bin';good=part.read_bytes();part.write_bytes(bytes([good[0]^1])+good[1:]);run(inp,False,'damaged update part');part.write_bytes(good);checks+=['Corrupt payload rejection before output creation']
 part.rename(A/'held-payload.bin');run(inp,False,'Missing update data');(A/'held-payload.bin').rename(part);checks+=['Missing payload rejection']
 wrong=T/'Wrong.iso';wrong.write_bytes(b'wrong version or private build');run(wrong,False,'Other versions are not supported');assert wrong.read_bytes()==b'wrong version or private build';checks+=['Wrong baseline rejection']
 with wrong.open('wb')as f:f.truncate(accepted['bytes'])
 run(wrong,False,'Other versions are not supported');checks+=['Same-size altered/unreleased image rejection by full SHA-256'];wrong.unlink()
 bad=json.loads(original);bad['baselines'][0]['operations'].insert(1,dict(source='baseline',offset=accepted['bytes']+1,length=2048));M.write_text(json.dumps(bad));run(inp,False,'Invalid patch range');assert not base.exists();checks+=['Partial-build invalid-range failure cleans temporary file and preserves input']
 bad=json.loads(original);bad['targetSHA256']='0'*64;M.write_text(json.dumps(bad));run(inp,False,'Rebuilt ISO verification failed');assert not base.exists();checks+=['Full write followed by failed target verification cleans output and preserves rollback/input']
 M.write_bytes(original);assert sha(inp)==accepted['sha256']and sha(baseline)==accepted['sha256'];checks+=['Original released ISO remains byte-identical throughout']
 assert(A/'Apply-Update.cmd').read_bytes().startswith(b'@echo off\r\n')
report=dict(passed=True,sourceDigest=json.loads((V/'Normal-Complete-Checks244.json').read_text())['sourceDigest'],baselineVersion='1.10.0',targetVersion='1.11.0',targetSHA256=m['targetSHA256'],targetBytes=m['targetBytes'],checks=checks,powerShellVersion='7.4.6 Linux executing the shipped script with explicit -BaseIso',limitations=['Windows file picker/batch GUI not executed on Linux','Host update validation is not an Xbox/Xemu playtest or FATX/64MB acceptance'],originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=2)
(V/'Patch-Validation251.json').write_text(json.dumps(report,indent=2)+'\n');shutil.copy2(V/'Patch-Validation251.json',P/'Verification/Patch-Validation251.json')
(P/'VERIFICATION-REPORT.txt').write_text('MyRO 1.11.0 verification\n\nNormal release-wide host/native checks passed on the corrected source, followed by both additional reviews. One review found and fixed native actor upload ordering; full checks were repeated before review completion.\n\nThe actual shipped PowerShell updater reconstructed the exact target ISO and all twenty file hashes. Baseline/payload rejection, existing-output protection, rollback/receipt, partial/full failed-write cleanup and baseline preservation passed. Only released 1.10.0 is accepted.\n\nThe complete twelve-chapter runtime, nineteen independent companions, guild construction, all six original arcade engines, eight-angle cabinets and regional dispatches are included. Native quest script data/costs/rewards are preserved.\n\nNo Xbox or Xemu playtest is claimed. Natural progression/balance, original 64MB total residency, frame/audio timing, controller/display and FATX/restart acceptance remain target testing.\n\nDetailed evidence is in Verification and the GitHub recovery source branch. Current save namespace: E:\\MyROStory200\\Save54_1_0. Obsolete test characters are intentionally not migrated.\n')
pack();summary=dict(version='1.11.0',package=Z.name,bytes=Z.stat().st_size,sha256=sha(Z),targetBytes=m['targetBytes'],targetSHA256=m['targetSHA256'],baselines=[{k:b[k]for k in ['version','bytes','sha256']}for b in m['baselines']],files=m['files'],sourceDigest=report['sourceDigest'],normalChecksPassed=True,additionalReviewPassesCompleted=2,packagingValidated=True,originalXboxPlaytested=False,xemuPlaytested=False)
(D/'release1.11.0.json').write_text(json.dumps(summary,indent=2)+'\n');(D/'MyRO-1.11.0-Update.zip.sha256').write_text(summary['sha256']+'  '+Z.name+'\n');print('PASS actual updater reconstruction, inventory, rejection, failed-write cleanup, rollback and input preservation. Final ZIP ready for delivery; no target playtest claim.')
