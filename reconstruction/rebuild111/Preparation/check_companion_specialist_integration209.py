"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-specialist-integration209.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_specialist209.c'),'-lm','-lz','-o',str(V/'companion-specialist209_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-specialist209_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Specialist-Integration-Checks209.json').write_text(json.dumps(dict(passed=True,scope='Actual production impact resolver: Ninja series, Soul Linker priming and follow-up series, durable one-time SP payment, player SP unchanged, failed saves and stale serial preserve resources. AI decision integration, full roster activation and target playtests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual specialist impact integration; choices remain separate; host only.')
