"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-performer-integration216.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_performer216.c'),'-lm','-lz','-o',str(V/'companion-performer216_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-performer216_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Performer-Integration-Checks216.json').write_text(json.dumps(dict(passed=True,scope='Actual Oren/Lale ticks in all four authored careers: original learned ranged skills and basic fallback, native projectiles, real physical damage with actual enemy defenses, deferred one-time durable own-SP payment and preserved career EXP/job/vitals/player resources. Lost/dead/out-of-range targets, exhausted SP, corrupt record and rejected write preserve resources and exact durable bytes; pause/peaceful modes preserve attacks. Native caller/impact references are separate; full roster activation and target playtests remain separate',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Oren/Lale ranged candidate integration; host only.')
