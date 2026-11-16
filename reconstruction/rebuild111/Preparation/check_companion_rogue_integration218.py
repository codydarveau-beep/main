"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-rogue-integration218.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_rogue218.c'),'-lm','-lz','-o',str(V/'companion-rogue218_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-rogue218_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Rogue-Integration-Checks218.json').write_text(json.dumps(dict(passed=True,scope='Actual Kest ticks across all three authored careers: rear-only Back Stab and Envenom, real damage/facing, learned Double Attack with cached fully reduced damage, one deferred saved own-SP payment and preserved growth/player resources. Complete durable-record/RNG/resource preservation under lost/dead/out-of-range/blocked targets, exhausted SP, corrupt records and allocation failures. Basic disabled/support behavior and pause checked. World activation and target playtests remain separate',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Kest physical candidate integration; host only.')
