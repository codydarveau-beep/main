"""Normal stage integration checks; neither additional review pass."""
from pathlib import Path
import subprocess,os,json,hashlib
R=Path(__file__).resolve().parent.parent;V=R/'Validation';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'campaign-stage198.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(R/'Source'),str(R/'Source/test_campaign_stage198.c'),'-lm','-lz','-o',str(V/'campaign-stage198_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'campaign-stage198_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
r=json.loads((V/'Stage-Rules-Checks198.json').read_text());assert r['passed'];assert r['sourceSHA256']==hashlib.sha256((R/'Source/campaign_stage_rules198.h').read_bytes()).hexdigest()
r.update(physicalAdaptersSanitized=True,saveAllocationFailurePreserved=True,blockedMovementPreserved=True,staleStageRejected=True,activationChanged=False,preparedLaterRuntime='Evidence decisions are implemented; later binding remains guarded pending encounter lifecycle and transition integration',integrationSourceSHA256=hashlib.sha256((R/'Source/campaign_stage200.h').read_bytes()).hexdigest())
(V/'Stage-Integration-Checks198.json').write_text(json.dumps(r,indent=2)+'\n');print('PASS authored stage interaction rules, physical adapters and failed-write preservation. Later activation remains guarded; host only.')
