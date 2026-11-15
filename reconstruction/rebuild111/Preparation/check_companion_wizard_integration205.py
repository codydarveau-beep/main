"""Normal live mage area integration, ownership and player-field regression."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-wizard-integration205.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_wizard205.c'),'-lm','-lz','-o',str(V/'companion-wizard205_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-wizard205_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Wizard-Integration-Checks205.json').write_text(json.dumps(dict(passed=True,scope='Actual promoted mage candidate selection, casts, shared fields and impacts: thresholds/preferences, own resources, freeze/ownership/aggro, failed capacity/target/save preflight and unchanged player-owned fields. Full roster/world activation and target playtests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual promoted mage candidate shared-field integration; host only.')
