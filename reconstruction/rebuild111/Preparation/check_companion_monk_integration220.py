"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-monk-integration220.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_monk220.c'),'-lm','-lz','-o',str(V/'companion-monk220_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-monk220_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Monk-Integration-Checks220.json').write_text(json.dumps(dict(passed=True,scope='Actual Suri both-career battle sequences through original three-hit Trifecta and same-target four-hit Quadruple follow-up: real cached split/remainder damage, original proc/window/learning, one saved follow-up SP fee and preserved growth/player resources. Failed/corrupt storage and lost/dead/out-of-range/blocked/unaffordable impacts preserve complete records, RNG and resources; failed zero-fee Trifecta cannot arm a combo. Disabled-skill basic behavior checked. World activation and target acceptance remain separate',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Suri combo candidate integration; host only.')
