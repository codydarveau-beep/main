"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-melee-integration213.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_melee213.c'),'-lm','-lz','-o',str(V/'companion-melee213_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-melee213_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Melee-Integration-Checks213.json').write_text(json.dumps(dict(passed=True,scope='Actual Brann and Iruga candidate ticks in all four authored careers: own learned Bash/Envenom, real hit/poison resolution and original native Bash effect, durable one-time SP payment, unchanged player SP/experience, support/basic and insufficient-SP fallback, paused and failed-save preservation. Native branch/status comparisons are separate; full roster activation and target playtests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Brann and Iruga candidate integration; host only.')
