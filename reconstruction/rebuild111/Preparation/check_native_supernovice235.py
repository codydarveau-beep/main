"""Execute released first-job final branches with real production VM/adapters."""
from pathlib import Path
import os,json,subprocess
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
world=(S/'campaign_world200.h').read_text();(V/'actual_job_guard228.inc').write_text('/* Exact production guard. */\n'+next(l for l in world.splitlines()if l.startswith('static int campaign_job_guard200('))+'\n')
with (V/'native-supernovice235.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_native_supernovice235.c'),'-lm','-lz','-o',str(V/'native-supernovice235_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'native-supernovice235_asan'),str(R.parent/'packet194/released-scripts.bin')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Native-Supernovice-Checks235.json').write_text(json.dumps(dict(passed=True,scope='Actual accepted Novice story intent, earned opening proof, permanent role/family commitment and scene advancement without granting a job early. Later original Super Novice NPC open/chronology/full dispatcher/VM and native quest materials/repeat behavior execute; missing supplies preserve resources. Intermediate story progress and native quest prerequisites are explicit fixtures, not full native quest journey or target playtesting.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS native first-job quest finalization and campaign proof; host only.')
