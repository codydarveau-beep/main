"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-elemental-integration211.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_elemental211.c'),'-lm','-lz','-o',str(V/'companion-elemental211_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-elemental211_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Elemental-Integration-Checks211.json').write_text(json.dumps(dict(passed=True,scope='Actual Edda and Kaede candidate ticks across all three authored careers: original learned element/cost choices, own-DEX casting, complete real hit series, single durable SP payment, unchanged player SP/progression, interrupted casts and failed persistence. Native choice/impact comparisons are separate; full roster activation and target playtests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Edda and Kaede candidate integration; host only.')
