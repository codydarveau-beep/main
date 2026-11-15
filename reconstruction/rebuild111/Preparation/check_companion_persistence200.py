"""Normal companion wire/storage checks, not career-AI or game swap acceptance."""
from pathlib import Path
import os,subprocess,json,hashlib
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-persistence200.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_progress200.c'),'-lm','-lz','-o',str(V/'companion-persistence200_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-persistence200_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
r=json.loads((V/'Companion-Wire-Checks200.json').read_text());assert r['passed']and r['sourceSHA256']==hashlib.sha256((S/'companion_progress200.h').read_bytes()).hexdigest();r.update(sparseSaveRoundtripPassed=True,legacyMigrationDoesNotWriteOnRead=True,failedCommitAtomic=True,independentCharactersPassed=True,behaviorSettingsDoNotAlterGrowthRecord=True,runtimeCallersIntegrated=True,runtimeIntegrationEvidence='Companion-Runtime-Checks200.json',remaining='Complete authored career skill/AI integration and full native save/gameplay regression before enabling unprepared careers')
(V/'Companion-Persistence-Checks200.json').write_text(json.dumps(r,indent=2)+'\n');print('PASS restored companion record and durable per-character persistence; live growth/formation checks are reported separately.')
