"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-pip-integration214.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_pip214.c'),'-lm','-lz','-o',str(V/'companion-pip214_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-pip214_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Pip-Integration-Checks214.json').write_text(json.dumps(dict(passed=True,scope='Actual Pip candidate ticks: own learned Heal/Bash and original priorities, real player/ally/self recovery with durable recipient/caster resources, one SP payment and unchanged player SP/experience, original rank/range and failed-save preservation, real physical fallback. Native target/choice/impact comparisons are separate; full roster activation and target playtests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Pip support and physical candidate integration; host only.')
