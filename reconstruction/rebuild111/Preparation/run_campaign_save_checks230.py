"""Normal integration refresh after complete chapters/emotes and save repairs."""
from pathlib import Path
import hashlib,json,subprocess,sys
R=Path(__file__).resolve().parent.parent;V=R/'Validation'
def sources():return {str(p.relative_to(R)):hashlib.sha256(p.read_bytes()).hexdigest()for p in sorted((R/'Source').glob('*')) if p.is_file() and p.suffix in ['.h','.c','.S']}
start=sources();commands=['run_checks194.py','check_companion_runtime200.py','check_companion_world223.py','check_companion_promotions227.py','check_scene_emote225.py','check_campaign_sequence200.py','check_campaign_companions226.py','check_campaign_save228.py','check_campaign_save_bundle229.py','check_native194.py'];results=[]
with (V/'campaign-save-refresh230.log').open('w')as out:
 for command in commands:
  result=subprocess.run([sys.executable,str(R/'Preparation'/command)],cwd=R,stdout=out,stderr=subprocess.STDOUT);results.append(dict(command=command,passed=result.returncode==0));print(('PASS 'if not result.returncode else'FAIL ')+command,flush=True)
  if result.returncode:break
assert sources()==start,'Source changed during the normal refresh'
passed=len(results)==len(commands)and all(r['passed']for r in results)
(V/'Campaign-Save-Refresh230.json').write_text(json.dumps(dict(passed=passed,phase='normal integration',commands=results,sourceFiles=start,scope='Current-source policy/travel/guild/dispatch regression, companion growth/world/promotions, original-native emotes/campaign save/job guard, full scene/live-roster traversal, full persistent-state bundle faults and native compile/stack evidence. Remaining native quest playthrough, platform and package acceptance are separate.',normalReleaseWideChecksComplete=False,additionalReviewPassesStarted=False,additionalReviewPassesCompleted=0,originalXboxPlaytested=False,xemuPlaytested=False,packagingValidated=False),indent=2)+'\n')
if not passed:raise SystemExit(1)
subprocess.run([sys.executable,str(R/'Preparation/summarize_normal_checks194.py')],cwd=R,check=True)
