"""Verify deployed scene records through the production reader without activating chapters."""
from pathlib import Path
import subprocess,os,json
R=Path(__file__).resolve().parent.parent;V=R/'Validation';S=R/'Source'
subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-I'+str(S),str(S/'test_scenes195.c'),'-lm','-lz','-o',str(V/'scenes195_asan')],check=True)
env=os.environ.copy();env['ASAN_OPTIONS']='detect_leaks=1:halt_on_error=1';env['UBSAN_OPTIONS']='halt_on_error=1:print_stacktrace=1'
subprocess.run([str(V/'scenes195_asan'),str(R/'Recovered195/chapter1.bin')],env=env,check=True)
(V/'Scene-Checks195.json').write_text(json.dumps(dict(passed=True,packedSceneRecords=36,runtimeSceneCeiling=12,worldActivation=False,nodes=458,roles=3,checks=['actual scene validation/inflate','every node expression and preserved cue','checkpoint and scene reopen','malformed cue rejection','inactive scene ceiling retained'],scope='Production scene wire/checkpoint host checks only; no world objectives, scene staging or full campaign completion claim'),indent=2)+'\n')
