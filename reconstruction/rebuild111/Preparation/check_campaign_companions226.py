"""Normal complete chapter/roster integration; explicit isolated combat arenas."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation'
world=(S/'campaign_world200.h').read_text()
for prefix,name in [('static void campaign_party_bind200(', 'actual_party_bind223.inc'),('static void campaign_killed200(', 'actual_campaign_killed226.inc')]:
 (V/name).write_text('/* Exact production chapter/party bridge. */\n'+next(l for l in world.splitlines() if l.startswith(prefix))+'\n')
env=os.environ.copy();env.update(MYRO_WORLD_PATH=str(R/'XboxFiles/world.bin'),MYRO_CHAPTER1_PATH=str(R/'Recovered195/chapter1.bin'),MYRO_CAMPAIGN_ACTOR_PATH=str(R/'Recovered195/campaign.bin'),MYRO_CAMPAIGN_PORTRAIT_PATH=str(R/'Recovered195/storyportraits.bin'),MYRO_NPCFX_PATH=str(R/'Recovered195/npcfx.bin'),ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'campaign-companions226.log').open('w') as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_campaign_companions226.c'),'-lm','-lz','-o',str(V/'campaign-companions226_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'campaign-companions226_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Campaign-Companions-Checks226.json').write_text(json.dumps(dict(passed=True,scenes=36,roles=3,replyVariants=2,scope='Actual scene traversal with production per-frame party binding, modal locks, all recruited companions and own independent EXP from real AI combat/damage/reward callback, chapter rewards and idempotency. Between-scene ordinary native-spec enemy arenas explicitly synthesized. Native first-job completion and scene-specific enemy-death proofs remain base-suite fixtures. GPU/raster/allocations host-recorded. Promotion boundary checks remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
print('PASS complete candidate chapter/companion reward bridge; host only.')
