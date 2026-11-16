"""Execute released first-job final branches with real production VM/adapters."""
from pathlib import Path
import os,json,subprocess
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation';env=os.environ.copy();env['MYRO_WORLD_PATH']=str(R/'XboxFiles/world.bin');env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
world=(S/'campaign_world200.h').read_text();(V/'actual_job_guard228.inc').write_text('/* Exact production guard. */\n'+next(l for l in world.splitlines()if l.startswith('static int campaign_job_guard200('))+'\n')
with (V/'native-ferry237.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_native_ferry237.c'),'-lm','-lz','-o',str(V/'native-ferry237_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'native-ferry237_asan'),str(R.parent/'packet194/released-scripts.bin')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Native-Ferry-Checks237.json').write_text(json.dumps(dict(passed=True,scope='Actual NPC open and unmodified native ferry bytecode/full dispatcher/admission at the authored optional-visit milestone: earlier denial preserves complete character/quest revision, admission charges original fare, real packed collision connects arrival to city portal, and later dungeon/Morroc restrictions remain intact. Qualified traveler and completed NPC OnInit are explicit fixtures. No target playtest.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS native first-job quest finalization and campaign proof; host only.')
