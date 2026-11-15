"""MIT. Current Test37 host suite; historical test files are retained separately.
Run: python validate37.py [--sanitize] [--ui-only]. Native build and emulator tests are separate.
"""
from pathlib import Path
import subprocess, tempfile, sys, math, os
root=Path(__file__).resolve().parent
sanitize='--sanitize' in sys.argv
flags=['-O1','-g']+(['-fsanitize=address,undefined']if sanitize else [])
with tempfile.TemporaryDirectory(prefix='myro37-') as tmp:
 out=Path(tmp)
 tests=[('test_acolyte37',[]),('test_expansion36',[]),('test_mechanics37',[]),('test_batch37',[]),('test_cast37',[]),('test_services36',[]),('test_save35',[]),('test_inventory',[]),('test_shop',[]),('test_contact34',[]),('test_projection',[]),('test_sprite_projection35',[]),('test_atlas34',['skin_assets.c']),('test_hud_batch',[])]
 if '--ui-only' in sys.argv:tests=[]
 for name,extra in tests:
  exe=out/name
  subprocess.run(['gcc',*flags,str(root/(name+'.c')),*[str(root/e)for e in extra],'-lm','-lz','-o',str(exe)],check=True)
  args=[str(exe)]+([str(root.parent/'Actors/actors.bin')]if name=='test_sprite_projection35' else [])
  subprocess.run(args,check=True)
 if '--ui-only' not in sys.argv:
  subprocess.run([sys.executable,str(root/'verify_player_contact35.py'),str(root.parent/'Actors/actors.bin')],check=True)
  subprocess.run([sys.executable,str(root/'test_hud_backend.py')],check=True)
 exe=out/'ui'
 subprocess.run(['gcc',*flags,str(root/'test_ui37.c'),str(root/'ui_assets.c'),str(root/'skin_assets.c'),'-lm','-lz','-o',str(exe)],check=True)
 cases=[['assign',str(i)]for i in range(14)]+[['cart',str(i)]for i in range(36)]+[['skills',str(i)]for i in range(1,7)]+[['craft'],['appraise'],['styles'],['equip']]+[['roll',str(i*math.pi/64)]for i in range(65)]
 cases += [['inventory',str(i)]for i in range(18)]+[['cast',str(v)]for v in [.1,2.5,5]]+[['services',str(i),str(c)]for i in range(8)for c in range(2)]+[['servicecart',str(i)]for i in range(36)]+[['shop',str(i),str(selling)]for i in range(18)for selling in range(2)]
 cases += [['feedback',str(i),'63']for i in range(64)]+[['feedback','63',str(i)]for i in range(69)]+[['windows',str(w),str(i)]for w in range(4)for i in range(6)]
 peak=0
 for args in cases:
  r=subprocess.run([str(exe),*args],check=True,capture_output=True,text=True)
  count=0;selected=False;thumb=False;panels=[];slots=[]
  for line in r.stdout.splitlines():
   a=line.split()
   if a[0]=='Q':
    x,y,w,h,u,v,uw,vh=map(float,a[1:]);assert x>=0 and y>=0 and x+w<=640.1 and y+h<=480.1,(args,line)
   elif a[0]=='F':
    x,y,w,h,c=map(int,a[1:]);assert x>=0 and y>=0 and x+w<=640 and y+h<=480,(args,line)
    if args[0]=='roll' and 195<=x<=445 and 10<=w<=40:assert y+h<=477,(args,line)
    if args[0]=='windows' and 160<=x<=475 and y>=400 and w<=40:assert y+h<=477,(args,line)
    if args[0]=='inventory' and (w,h,c)==(4,67,0xff8fd1ff):
     first=max(0,int(args[1])//4-2);assert x==581 and y==139+45*first//2,(args,line);thumb=True
    if args[0]=='assign':
     n=int(args[1]);xx=202+(n%6+1)*34 if n<12 else 168 if n==12 else 446;yy=403+n//6*36 if n<12 else 424;ww=32 if n<12 else 26
     if (x,y,w,h,c)==(xx,yy,ww,2,0xffffda45):selected=True
    if c==0xffeaf0f5 and w>=100 and h>=20:panels.append((x,y,w,h))
    if args[0]=='assign' and c==0xffeaf0f5 and w==h==30:slots.append((x,y,w,h))
   count+=1
  if args[0]=='assign':assert selected,args
  if args[0]=='inventory':assert thumb,args
  if args[0] in ['feedback','windows']:
   for i,a in enumerate(panels):
    for b in panels[i+1:]:assert a[0]+a[2]<=b[0] or b[0]+b[2]<=a[0] or a[1]+a[3]<=b[1] or b[1]+b[3]<=a[1],(args,a,b)
  if args[0]=='feedback':
   central=[p for p in panels if p[0]>=200 and p[0]+p[2]<=435 and p[1]>=100]
   for a in central:assert a[1]+a[3]<=425,(args,a)
   for a,b in zip(sorted(central,key=lambda p:p[1]),sorted(central,key=lambda p:p[1])[1:]):assert a[1]+a[3]+6<=b[1],(args,a,b)
  if args[0]=='assign':assert len(slots)==14,args
  # Native palette fills also consume one quad, as the recorder does.
  peak=max(peak,count)
 print(f'PASS {len(cases)} actual UI cases: all assignments/cart rows/job ends, inventory, services, all69 skill labels, feedback combinations and open windows; nonoverlapping panels and full-roll bounds; peak {peak} quads of1536')
print('PASS Test37 '+('UI-only' if '--ui-only' in sys.argv else 'host')+' validation complete; native compile and xemu/hardware remain separate checks')
