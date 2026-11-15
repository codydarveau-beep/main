"""Normal retained story marker integration checks with a host draw recorder."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source';env=os.environ.copy();env.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
with (V/'campaign-minimap200.log').open('w')as out:
 subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_campaign_minimap200.c'),'-lm','-lz','-o',str(V/'campaign-minimap200_asan')],stdout=out,stderr=subprocess.STDOUT,check=True)
 subprocess.run([str(V/'campaign-minimap200_asan')],stdout=out,stderr=subprocess.STDOUT,env=env,check=True)
(V/'Campaign-Minimap-Checks200.json').write_text(json.dumps(dict(passed=True,source='Retained196/campaign_minimap194.partial.h',adapters=['recovered trailing-field names','original gate/mask helpers','early single-document count absent from trailing extension'],integration='Called after regional markers; main-story early returns do not hide regional notices.',scope='Host marker recorder and sanitizer checks; GPU presentation and world prop rendering remain separate.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
print('PASS restored retained story minimap markers; host only.')
