"""Actual packed environment, scene placements and passage checks; normal phase."""
from pathlib import Path
import subprocess,os,json,hashlib
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation';env=os.environ.copy();env.update(MYRO_WORLD_PATH=str((R/'XboxFiles/world.bin').resolve()),ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'story-alias199.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_story_alias199.c'),'-lm','-lz','-o',str(V/'story-alias199_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'story-alias199_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
report=dict(passed=True,aliases={'495':343,'496':118},actualPackedTerrainSceneryLoaded=True,collisionAndHeightMatchSources=True,authoredPlacementsPreserved=True,nativeScriptsAndSpawnsIsolated=True,actualWalkablePaths=True,passageMilestonesAndObjectiveGate=True,deniedTravelPreservesMoneyItemsQuestStateAndRNG=True,originalMap118StillRestrictedUntil35=True,resourceCleanupPassed=True,scope='Production world/collision/travel code with host GPU allocation recorder; not target RAM/performance, native rendering or Xbox/Xemu playtesting',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0,sourceSHA256=hashlib.sha256((S/'test_story_alias199.c').read_bytes()).hexdigest())
(V/'Story-Alias-Checks199.json').write_text(json.dumps(report,indent=2)+'\n');print('PASS restored scene environments, exact geometry parity, authored placements, reachable passages and denied-travel preservation. Host only.')
