"""Normal actual battle/support integration checks; no target playtest claims."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-cast201.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_skills201.c'),'-lm','-lz','-o',str(V/'companion-cast201_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-cast201_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Cast-Checks201.json').write_text(json.dumps(dict(passed=True,scope='Actual initial support and cast callers: learned ranks follow own job level, failed support save preserves resources, cast initiation/interruption does not debit SP, failed completion does not hit or spend, successful completion charges ally only. Remaining career AI/effects are not certified.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
print('PASS actual companion learning, support and cast payment integration; host only.')
