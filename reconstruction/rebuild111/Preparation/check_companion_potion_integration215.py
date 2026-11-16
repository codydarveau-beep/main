"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-potion-integration215.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_potion215.c'),'-lm','-lz','-o',str(V/'companion-potion215_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-potion215_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Potion-Integration-Checks215.json').write_text(json.dumps(dict(passed=True,scope='Actual Maya candidate ticks in both careers: original Red Potion use, own SP/rank-one fee and learned research, player/ally/self healing with preserved career progression; exact inventory and record snapshots for denied, failed-commit and corrupt-save cases; original approach and real basic combat fallback. Native target/choice/impact comparisons are separate; full roster activation and target playtests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Maya support and physical candidate integration; host only.')
