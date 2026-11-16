"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-blacksmith-integration217.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_blacksmith217.c'),'-lm','-lz','-o',str(V/'companion-blacksmith217_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-blacksmith217_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Blacksmith-Integration-Checks217.json').write_text(json.dumps(dict(passed=True,scope='Actual Dagna ticks in both careers: learned Hammer Fall, native area boundary and real statuses, deferred durable own-SP fee, unchanged enemy HP for stun, preserved career EXP/job/vitals/player resources. Lost/dead/out-of-range/blocked targets, exhausted SP, corrupt record and failed write preserve exact records and resources. Real basic fallback preserves original support/disabled/cooldown/boss/already-stunned behavior. Full world activation and target playtests remain separate',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Dagna area-stun/physical candidate integration; host only.')
