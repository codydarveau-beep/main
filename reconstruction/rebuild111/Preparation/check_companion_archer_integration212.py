"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-archer-integration212.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_archer212.c'),'-lm','-lz','-o',str(V/'companion-archer212_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-archer212_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Archer-Integration-Checks212.json').write_text(json.dumps(dict(passed=True,scope='Actual Judia candidate ticks in both careers: delayed original arrows and complete real double hits, rank-zero support fallback, durable one-time SP payment, unchanged player SP/experience, failed persistence and original native effect ownership/lifetime/room/serial/removal handling with real cylinder animation parameters and recorded GPU boundaries. Native comparisons are separate; full roster activation and target playtests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Judia candidate and native effect integration; host only.')
