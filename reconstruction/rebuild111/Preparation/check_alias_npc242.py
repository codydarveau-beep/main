"""Actual native NPC lifecycle/render selection across custom environment aliases."""
from pathlib import Path
import subprocess,os,json,sys
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with(V/'alias-npc242.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_alias_npc242.c'),'-lm','-lz','-o',str(V/'alias-npc242_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'alias-npc242_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Alias-NPC-Checks242.json').write_text(json.dumps(dict(passed=True,scope='Actual native NPC map bind, ordinary-map return, near/touch/creature-touch and sprite selection for both empty campaign aliases; correct reset of prior presentation, touch occupancy and minimap markers. Existing 495 map spans, including previously recovered career-safe relocations, remain unchanged and two empty alias spans add no native NPC/script copies. World geometry/scene placements are unchanged and validated separately. Host only.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS empty-alias native NPC transition/selection safety; host only.')
