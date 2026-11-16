"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
line=next(line for line in (S/'campaign_world200.h').read_text().splitlines() if line.startswith('static void campaign_party_bind200('));(V/'actual_party_bind223.inc').write_text('/* Exact current production world-party binding. */\n'+line+'\n')
with (V/'companion-world-integration223.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_world223.c'),'-lm','-lz','-o',str(V/'companion-world223_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-world223_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-World-Integration-Checks223.json').write_text(json.dumps(dict(passed=True,scope='Actual production menu/controller and extracted exact world-party binding for all nineteen recruited companions: add/reserve and three-member limit, original starting pair, deceased and injured reserve vitals, per-character settings commit/cancel/failed save, native learning and independent levels, repeated live binding during actual mixed combat. Host draw recorder checks layout bounds; full chapter progression/target rasterization and 64MB acceptance remain separate',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual full-roster world/menu candidate integration; host only.')
