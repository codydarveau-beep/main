"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-gunner-integration219.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_gunner219.c'),'-lm','-lz','-o',str(V/'companion-gunner219_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-gunner219_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Gunner-Integration-Checks219.json').write_text(json.dumps(dict(passed=True,scope='Actual Corin ranged battle: complete five-hit Rapid Shower and learned Chain Action/basic behavior, real defense/hit application with original cached series damage, one deferred durable own-SP payment, own growth/player-resource preservation, cancelled/interrupted target handling and exact record/RNG preservation under failed writes/corrupt records/line/range/resource denial. Disabled/support/basic and pause checked. Full roster activation and target playtests remain separate',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Corin ranged candidate integration; host only.')
