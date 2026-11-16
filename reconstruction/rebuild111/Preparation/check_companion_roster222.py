"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-roster-integration222.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_roster222.c'),'-lm','-lz','-o',str(V/'companion-roster222_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-roster222_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Roster-Integration-Checks222.json').write_text(json.dumps(dict(passed=True,scope='Actual mixed three-companion backend parties across all nineteen characters, every three-person combination, three career stages and cyclic slot order. Actual AI, repeated impacts and shared fields run together; player resources/control ownership stay separate, live/saved vitals and career EXP agree, reserve records remain byte-identical and removing/reselecting grants no HP/SP. This is bounded host integration, not a complete campaign/target runtime proof or GPU/64MB acceptance',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS mixed full-roster backend candidate integration; host only.')
