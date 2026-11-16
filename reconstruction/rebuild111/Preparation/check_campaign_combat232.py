"""Functional authored encounters with real combat and explicit host calibration."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation'
world=(S/'campaign_world200.h').read_text()
for prefix,name in [('static void campaign_party_bind200(', 'actual_party_bind223.inc'),('static void campaign_killed200(', 'actual_campaign_killed226.inc')]:
 (V/name).write_text('/* Exact production chapter/party bridge. */\n'+next(l for l in world.splitlines() if l.startswith(prefix))+'\n')
env=os.environ.copy();env.update(MYRO_WORLD_PATH=str(R/'XboxFiles/world.bin'),MYRO_CHAPTER1_PATH=str(R/'Recovered195/chapter1.bin'),MYRO_CAMPAIGN_ACTOR_PATH=str(R/'Recovered195/campaign.bin'),MYRO_CAMPAIGN_PORTRAIT_PATH=str(R/'Recovered195/storyportraits.bin'),MYRO_NPCFX_PATH=str(R/'Recovered195/npcfx.bin'),ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'campaign-combat232.log').open('w') as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_campaign_combat232.c'),'-lm','-lz','-o',str(V/'campaign-combat232_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'campaign-combat232_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Campaign-Combat-Checks232.json').write_text(json.dumps(dict(passed=True,scenes=36,roles=1,replyVariants=1,scope='Actual scene traversal with production per-frame party binding, modal locks, all recruited companions and own independent EXP from real AI combat/damage/reward callback, chapter rewards and idempotency. Authored scene enemies retain actual HP, defenses and AI; player/companion damage and production reward/death callbacks execute. Qualified level/stat and continuously replenished player HP/SP are explicit host calibration fixtures, not balance acceptance. Native first-job completion remains a prerequisite fixture here, with actual final-quest branches tested separately in Native-First-Jobs-Checks231.json. GPU/raster/allocations host-recorded. Promotion boundary checks remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
print('PASS complete candidate chapter/companion reward bridge; host only.')
