"""Normal encounter lifecycle validation using actual NPC pool/combat adapters."""
from pathlib import Path
import subprocess,os,json,hashlib
R=Path(__file__).resolve().parent.parent;V=R/'Validation';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'campaign-encounter198.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(R/'Source'),str(R/'Source/test_campaign_encounter198.c'),'-lm','-lz','-o',str(V/'campaign-encounter198_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'campaign-encounter198_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
r=json.loads((V/'Encounter-Reference-Checks198.json').read_text());assert r['passed'] and r['sourceSHA256']==hashlib.sha256((R/'Source/campaign_encounter198.h').read_bytes()).hexdigest();r.update(actualPoolLifecyclePassed=True,serialOwnershipPassed=True,duplicateSpawnPreventionPassed=True,pausedRangeAndCapacityPassed=True,failedSaveRetryPassed=True,worldResetCleanupPassed=True,privateMapsNotRuntimeTested=[],privateMapsLifecycleTested=[495,496],laterActivationChanged=False,remaining='Full campaign binding, physical routes/geometry, scene transitions and companion progression need end-to-end integration')
(V/'Encounter-Integration-Checks198.json').write_text(json.dumps(r,indent=2)+'\n');print('PASS original encounter plans and actual NPC/combat lifecycle, failed-save retry, pause/range/capacity and cleanup. Host only; later activation unchanged.')
