"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-taekwon-integration221.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_taekwon221.c'),'-lm','-lz','-o',str(V/'companion-taekwon221_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-taekwon221_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Taekwon-Integration-Checks221.json').write_text(json.dumps(dict(passed=True,scope='Actual Daro/Haneul stance-to-kick sequences: own learned readiness and original window/target restrictions, real area damage and secondary knockback, primary exclusion and splash boundary, one deferred saved own-SP fee and preserved growth/player resources. Complete record/RNG/HP/movement preservation under failed/corrupt storage and invalid range/line/life/dead/resource cases; splash continues after primary death and disabled skills do not arm stances. Full roster/world acceptance and target playtests remain separate',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Daro/Haneul stance/kick candidate integration; host only.')
