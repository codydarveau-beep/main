"""Normal actual initial-mage candidate checks; full career activation remains guarded."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-mage204.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_mage204.c'),'-lm','-lz','-o',str(V/'companion-mage204_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-mage204_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Mage-Checks204.json').write_text(json.dumps(dict(passed=True,scope='Actual initial mage candidate tick and real combat impacts: own learned choice, interrupted casting, complete repeated bolt chain, single SP debit, stale target and failed-save preservation. Promoted area/status kits, defensive monster spells and world selection remain unfinished/guarded.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
print('PASS actual initial mage candidate integration; full roster activation remains guarded; host only.')
