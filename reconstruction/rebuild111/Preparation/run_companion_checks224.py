"""Refresh normal full-roster checks; never creates a backup or starts extra reviews."""
from pathlib import Path
import hashlib,json,subprocess,sys

R=Path(__file__).resolve().parent.parent
V=R/'Validation'
def sources():
    return [{'path':str(p.relative_to(R)),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()}
            for p in sorted((R/'Source').rglob('*'))
            if p.is_file() and (p.suffix in ['.c','.h','.inc','.s'] or p.name=='Makefile')]
before=sources()
commands=['run_checks194.py']+[p.name for p in sorted((R/'Preparation').glob('check_companion_*.py'))]
results=[]
with (V/'companion-release224.log').open('w')as log:
    for command in commands:
        log.write('\nNORMAL HOST CHECK: '+command+'\n');log.flush()
        result=subprocess.run([sys.executable,str(R/'Preparation'/command)],cwd=R,stdout=log,stderr=subprocess.STDOUT)
        results.append({'command':command,'passed':result.returncode==0})
        print(('PASS 'if result.returncode==0 else'FAIL ')+command,flush=True)
        if result.returncode:
            break
passed=len(results)==len(commands) and all(row['passed']for row in results)
assert sources()==before,'Source changed during normal companion checks; do not accept mixed-source evidence.'
report=dict(passed=passed,phase='normal full-roster release integration',commands=results,
    sourceFiles=before,sourceDigest=hashlib.sha256(json.dumps(before,sort_keys=True).encode()).hexdigest(),
    scope='Fresh actual sanitizer integration and independent original-native comparisons for all restored companion careers, persistence/growth/learning, mixed parties, roster/controller and production world binding, plus travel/policy/guild integration regression.',
    limitations='Bounded host/native CPU checks; full chapter/travel/native-job/save context, GPU/64MB/target acceptance and final packaging remain separate.',
    normalReleaseWideChecksComplete=False,additionalReviewPassesStarted=False,additionalReviewPassesCompleted=0,
    packagingValidated=False,originalXboxPlaytested=False,xemuPlaytested=False)
(V/'Companion-Release-Checks224.json').write_text(json.dumps(report,indent=2)+'\n')
if not passed:
    raise SystemExit(1)
with (V/'companion-release-native224.log').open('w')as log:
    subprocess.run([sys.executable,str(R/'Preparation/check_native194.py')],cwd=R,stdout=log,stderr=subprocess.STDOUT,check=True)
subprocess.run([sys.executable,str(R/'Preparation/summarize_normal_checks194.py')],cwd=R,check=True)
print('PASS refreshed normal companion checks; no backup, review pass, packaging or target-playtest claim.')
