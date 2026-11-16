"""Normal real world binding/commit checks for the native-verified career paths."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation'
world=(S/'campaign_world200.h').read_text();(V/'actual_party_bind223.inc').write_text('/* Exact production binding. */\n'+next(l for l in world.splitlines()if l.startswith('static void campaign_party_bind200('))+'\n')
env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-promotions227.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_promotions227.c'),'-lm','-lz','-o',str(V/'companion-promotions227_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-promotions227_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Promotions-Checks227.json').write_text(json.dumps(dict(passed=True,scope='Actual extracted per-frame world binding and promotion commits for every authored career path at story/job readiness boundaries, living/dead reserves, independent growth and settings. Allocation-failed promotion transactions preserve the entire record and retry; subsequent binding/reserve selection never repeats resource restoration. Eligibility arithmetic separately compared against original native code in Companion-Path-Checks200.json. Fixture story/job levels are explicit; natural campaign growth checked separately.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS complete career promotion world transactions; host only.')
