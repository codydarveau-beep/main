"""Complete normal acceptance on one Source snapshot; no extra review or packaging."""
from pathlib import Path
import hashlib,json,subprocess,sys
R=Path(__file__).resolve().parent.parent; V=R/'Validation'
def sources():
 return {str(p.relative_to(R)):hashlib.sha256(p.read_bytes()).hexdigest()for p in sorted((R/'Source').rglob('*'))if p.is_file()and(p.suffix in ['.c','.h','.s','.inc']or p.name=='Makefile')}
before=sources(); candidate=json.loads((V/'Full-Candidate-Checks240.json').read_text())
assert candidate['passed']and candidate['normalReleaseWideChecksComplete']and candidate['sourceFiles']==before,'Finish current-source full candidate run first'
with(V/'normal-companion-refresh244.log').open('w')as log:
 result=subprocess.run([sys.executable,str(R/'Preparation/run_companion_checks224.py')],cwd=R,stdout=log,stderr=subprocess.STDOUT)
assert before==sources(),'Source changed during normal release checks'
companion=json.loads((V/'Companion-Release-Checks224.json').read_text())
passed=bool(result.returncode==0 and companion['passed']and{r['path']:r['sha256']for r in companion['sourceFiles']}==before)
r=dict(passed=passed,phase='normal release-wide host/native checks',sourceFiles=before,sourceDigest=hashlib.sha256(json.dumps(before,sort_keys=True).encode()).hexdigest(),candidateEvidence='Full-Candidate-Checks240.json',companionEvidence='Companion-Release-Checks224.json',normalReleaseWideChecksComplete=passed,additionalReviewPassesStarted=False,additionalReviewPassesCompleted=0,packagingValidated=False,originalXboxPlaytested=False,xemuPlaytested=False,limitations=candidate['limitations'])
(V/'Normal-Complete-Checks244.json').write_text(json.dumps(r,indent=2)+'\n')
if not passed:raise SystemExit(1)
subprocess.run([sys.executable,str(R/'Preparation/summarize_normal_checks194.py')],cwd=R,check=True)
print('PASS current-source normal release-wide checks. Two additional reviews and package validation remain; no target playtest claim.')
