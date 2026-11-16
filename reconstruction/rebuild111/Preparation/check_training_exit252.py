"""Focused restoration check; course progress and OnInit are explicit fixtures."""
from pathlib import Path
import json,os,subprocess
R=Path(__file__).resolve().parent.parent;V=R/'Validation';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with(V/'training-exit252.log').open('w')as f:
 subprocess.run(['cc','-O0','-g','-fsanitize=address,undefined','-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-I'+str(R/'Source'),str(V/'test_training_exit252.c'),'-lm','-lz','-o',str(V/'training-exit252_asan')],stdout=f,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'training-exit252_asan'),str(R.parent/'packet194/released-scripts.bin')],stdout=f,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Training-Exit-Checks252.json').write_text(json.dumps(dict(passed=True,confirmedCause='Whole-script destination closure hides Hanson at initial campaign state',fixProvenance='Reconstructed targeted opening admission and exact native graduation destination redirect; native script unchanged',checks=['Actual Hanson npc_game_open and full native VM/dispatcher','Native graduation reaches campaign map0','Player remains Novice'],limitations=['Completed course flags, carrying capacity and OnInit completion are explicit fixtures','No full natural training journey, initialization/reachability or Xbox visual test in this fixture'],additionalRestorationReviewPassesCompleted=0),indent=2)+'\n')
