"""Repeat normal acceptance after the additional-review upload-order correction."""
from pathlib import Path
import subprocess,sys
R=Path(__file__).resolve().parent.parent;V=R/'Validation'
for command,log in [('run_full_candidate240.py','full-candidate-result240.log'),('check_normal_release244.py','normal-complete244.log')]:
 with(V/log).open('w')as out:
  subprocess.run([sys.executable,str(R/'Preparation'/command)],cwd=R,stdout=out,stderr=subprocess.STDOUT,check=True)
print('PASS corrected-source full normal checks. Final two additional review confirmations and packaging still pending.')
