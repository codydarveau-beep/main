"""MIT. Re-run every actual HUD case after the autosave-menu addition."""
from pathlib import Path
import subprocess,textwrap,sys
root=Path(__file__).resolve().parent;source=(root/'validate50.py').read_text();a=source.index(' cases=');b=source.index('\n peak=0',a);scope={};exec(textwrap.dedent(source[a:b]),scope);cases=scope['cases'];assert len(cases)==1642
exe=Path(sys.argv[1])if len(sys.argv)>1 else Path('/tmp/ui50b_final');peak=0
for args in cases:
 run=subprocess.run([str(exe),*args],check=True,capture_output=True,text=True);quads=0
 for line in run.stdout.splitlines():
  fields=line.split()
  if fields and fields[0]=='Q':
   x,y,w,h,*uv=map(float,fields[1:]);assert min(x,y)>=0 and x+w<=640.1 and y+h<=480.1,(args,line);quads+=1
  elif fields and fields[0]=='F':
   x,y,w,h,c=map(int,fields[1:]);assert min(x,y)>=0 and x+w<=640 and y+h<=480,(args,line)
 peak=max(peak,quads);assert quads<=1536
print('PASS50b all1642 actual HUD cases, all seven slider positions, pause/performance coexistence, screen bounds; peak',peak,'/1536quads.')
