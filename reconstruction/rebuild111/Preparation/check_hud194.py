"""Actual production HUD host recorder + SDK asserting stub; no GPU playtest."""
from pathlib import Path
import subprocess,textwrap,os,json
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation'
exe=V/'hud194_asan';stub=Path('/workspace/myro/toolchain/xbox-nxdk/lib/pdclib/platform/xbox/functions/math/lround.c')
subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-fno-omit-frame-pointer','-fno-builtin-lroundf',str(S/'test_ui42.c'),str(S/'ui_assets.c'),str(S/'skin_assets.c'),str(stub),'-lm','-lz','-o',str(exe)],check=True)
s=(S/'validate50.py').read_text();a=s.index(' cases=');b=s.index('\n peak=0',a);scope={};exec(textwrap.dedent(s[a:b]),scope);cases=scope['cases'];assert len(cases)==1642
# Exercise each legal current settings row, both edit states, in-game/title modes.
rows=[5,7,8,4,8,3,5]
for front in [0,1]:
 for tab in (range(1,5) if front else range(7)):
  for row in range(rows[tab]):
   for edit in [0,1]:cases.append(['settings194',str(tab),str(row),str(edit),str(front)])
cases += [['diagvideo255',str(row),str(edit),str(allow)]for row in range(9)for edit in ([0,1]if row<8 else[0])for allow in [0,1]]
cases += [['windows194',str(w)]for w in range(5)]+[['storage',str(i)]for i in [0,10,254]]
env=os.environ.copy();env['ASAN_OPTIONS']='detect_leaks=1:halt_on_error=1';env['UBSAN_OPTIONS']='halt_on_error=1:print_stacktrace=1'
peak=0
cases.extend([['storyminimap242',str(row),str(large)]for row in range(42)for large in range(2)])
cases.extend([['quest257',str(row),str(detail),str(scroll)]for row in [0,50,500,1500,3000]for detail in [0,1]for scroll in [0,99]])
for index,args in enumerate(cases):
 run=subprocess.run([str(exe),*args],capture_output=True,text=True,env=env)
 if run.returncode:
  (V/'hud-failure194.log').write_text(str(args)+'\n'+run.stderr);raise AssertionError((args,run.stderr[-500:]))
 quads=0
 for line in run.stdout.splitlines():
  f=line.split()
  if f and f[0]in ['Q','F']:
   x,y,w,h=map(float,f[1:5]);assert min(x,y)>=0 and x+w<=640.1 and y+h<=480.1,(args,line)
   if f[0]=='Q':quads+=1
 assert quads<=4096,(args,quads);peak=max(peak,quads)
 if index%250==0:print('HOST HUD cases',index,'/',len(cases),flush=True)
report=dict(passed=True,cases=len(cases),legacyCases=1642,currentSettingsAndWindowCases=len(cases)-1642,peakRecordedQuads=peak,capacity=4096,sanitizers=['address','undefined','leaks'],actualSDKAssertingMathStub=True,scope='Actual UI draw recorder and host platform adapters; not GPU rendering, Xbox/Xemu playtest or hardware RAM proof')
(V/'HUD-Checks194.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report))
