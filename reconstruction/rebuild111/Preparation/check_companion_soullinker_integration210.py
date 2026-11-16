"""Normal live targeted specialist impact integration; AI choices remain separate."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'companion-soullinker-integration210.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_companion_soullinker210.c'),'-lm','-lz','-o',str(V/'companion-soullinker210_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'companion-soullinker210_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Companion-Soullinker-Integration-Checks210.json').write_text(json.dumps(dict(passed=True,scope='Actual Miri candidate tick: learned size-based primer and prepared follow-up selection, own-DEX casting, real complete impacts, single saved SP payment, unchanged player SP, interrupted follow-up preserves preparation/SP, and peaceful/skills-disabled/insufficient-SP handling. Native choice comparison is separate; full roster activation and target playtests remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n');print('PASS actual Soul Linker candidate integration; host only.')
