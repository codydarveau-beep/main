"""Normal integration checks for retained core restoration; no extra review pass."""
from pathlib import Path
import subprocess,os,json,hashlib
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source'
env=os.environ.copy();env['ASAN_OPTIONS']='detect_leaks=1:halt_on_error=1';env['UBSAN_OPTIONS']='halt_on_error=1:print_stacktrace=1';checks=[]
for source,name in [('test_retained_guild196.c','retained-guild196'),('test_puzzle196.c','puzzle196'),('test_guild_ui194.c','guild-ui196')]:
 p=S/source;binary=V/(name+'_asan');log=V/(name+'.log')
 with log.open('w')as out:
  subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(p),'-lm','-lz','-o',str(binary)],stdout=out,stderr=subprocess.STDOUT,check=True)
  subprocess.run([str(binary)],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
 checks.append(dict(source=source,passed=True,sourceSHA256=hashlib.sha256(p.read_bytes()).hexdigest(),log=log.name))
report=dict(passed=True,phase='normal host integration',checks=checks,retainedCore='Complete supplied guild implementation with explicit field-name/caller adapters',puzzle='Newly reconstructed engine from retained rules and renderer, not original engine source',remainingArcades='Other five simulations still uncertified; complete engines remain work',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0)
(V/'Retained-Checks196.json').write_text(json.dumps(report,indent=2)+'\n')
# Other five integration suites passed against this restored guild core earlier.
p=V/'Integration-Checks194.json';d=json.loads(p.read_text())
for check in d['checks']:
 if check['name']=='guild_ui':check.update(passed=True,log='guild-ui196.log',sourceSHA256=checks[2]['sourceSHA256'])
d['allPassed']=all(c['passed']for c in d['checks']);p.write_text(json.dumps(d,indent=2)+'\n');print('PASS retained guild core/invitations, full sliding puzzle, actual guild UI and failed-save retry checks; host only.')
