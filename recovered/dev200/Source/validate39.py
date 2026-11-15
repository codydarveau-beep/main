"""MIT. Current Test39 host suite; historical test files are retained separately.
Run: python validate39.py [--sanitize] [--ui-only]. Native build and emulator tests are separate.
"""
from pathlib import Path
import subprocess, tempfile, sys, math, os
root=Path(__file__).resolve().parent
sanitize='--sanitize' in sys.argv
flags=['-O1','-g']+(['-fsanitize=address,undefined']if sanitize else [])
with tempfile.TemporaryDirectory(prefix='myro39-') as tmp:
 out=Path(tmp)
 tests=[('test_acolyte38',[]),('test_expansion38',[]),('test_mechanics37',[]),('test_batch37',[]),('test_cast37',[]),('test_storage38',[]),('test_support_cast38',[]),('test_ui_controls38',[]),('test_art39',[]),('test_art_render39',[]),('test_cast_head38',[]),('test_services36',[]),('test_save38',[]),('test_inventory',[]),('test_shop',[]),('test_contact34',[]),('test_projection',[]),('test_sprite_projection35',[]),('test_atlas34',['skin_assets.c']),('test_hud_batch',[])]
 if '--ui-only' in sys.argv:tests=[]
 for name,extra in tests:
  exe=out/name
  subprocess.run(['gcc',*flags,str(root/(name+'.c')),*[str(root/e)for e in extra],'-lm','-lz','-o',str(exe)],check=True)
  args=[str(exe)]+([str(root.parent/'Actors/actors.bin')]if name in ['test_sprite_projection35','test_cast_head38'] else [])
  subprocess.run(args,check=True)
 if '--ui-only' not in sys.argv:
  subprocess.run([sys.executable,str(root/'verify_player_contact35.py'),str(root.parent/'Actors/actors.bin')],check=True)
  subprocess.run([sys.executable,str(root/'test_hud_backend.py')],check=True)
 exe=out/'ui'
 subprocess.run(['gcc',*flags,str(root/'test_ui39.c'),str(root/'ui_assets.c'),str(root/'skin_assets.c'),'-lm','-lz','-o',str(exe)],check=True)
 cases=[['assign',str(i)]for i in range(14)]+[['cart',str(i)]for i in range(36)]+[['skills',str(i)]for i in range(1,7)]+[['craft'],['appraise'],['styles'],['equip']]+[['roll',str(i*math.pi/64)]for i in range(65)]
 cases += [['inventory',str(i)]for i in range(18)]+[['cast',str(v)]for v in [0,.1,2.5,5]]+[['services',str(i),str(c)]for i in range(9)for c in range(2)]+[['servicecart',str(i)]for i in range(36)]+[['shop',str(i),str(selling)]for i in range(18)for selling in range(2)]
 cases += [['feedback',str(i),'63']for i in range(128)]+[['feedback','63',str(i)]for i in range(69)]+[['windows',str(w),str(i)]for w in range(4)for i in range(6)]
 cases += [['storage',str(i)]for i in range(36)]+[['pause38',str(i),str(v)]for i in range(6)for v in range(2)]+[['windows',str(w),str(i),'1']for w in range(4)for i in range(6)]+[['feedback','63',str(128+i)]for i in range(18)]
 cases += [['preview39',str(i)]for i in range(15)]+[['cast','.0001',str(t)]for t in [.5,1,2,4,5]]
 peak=0
 for args in cases:
  r=subprocess.run([str(exe),*args],check=True,capture_output=True,text=True)
  count=0;selected=False;thumb=False;panels=[];slots=[];casts=[];front=[];rear=[];shadows=[]
  for line in r.stdout.splitlines():
   a=line.split()
   if a[0]=='Q':
    x,y,w,h,u,v,uw,vh=map(float,a[1:]);assert x>=0 and y>=0 and x+w<=640.1 and y+h<=480.1,(args,line)
   elif a[0]=='F':
    x,y,w,h,c=map(int,a[1:]);assert x>=0 and y>=0 and x+w<=640 and y+h<=480,(args,line)
    if args[0]=='roll' and 195<=x<=445 and 10<=w<=40:assert y+h<=479,(args,line)
    if args[0]=='windows' and 160<=x<=475 and y>=400 and w<=40:assert y+h<=479,(args,line)
    if args[0]=='inventory' and (w,h,c)==(4,67,0xff8fd1ff):
     first=max(0,int(args[1])//4-2);assert x==581 and y==139+45*first//2,(args,line);thumb=True
    if args[0]=='assign':
     n=int(args[1]);xx=202+(n%6+1)*34 if n<12 else 170 if n==12 else 448;yy=403+n//6*36 if n<12 else 424;ww=32 if n<12 else 22
     if (x,y,w,h,c)==(xx,yy,ww,2,0xffffda45):selected=True
    if args[0]=='roll':
     if c==0xffeaf0f5 and w==h==30:front.append((x,y,w,h))
     if c==0xffeaf0f5 and w==h==16:rear.append((x,y,w,h))
     if c==0x70000000 and w==h==30:shadows.append((x,y,w,h))
    if c==0xff181818 and (w,h)==(48,6):casts.append((x,y,w,h))
    if c==0xffeaf0f5 and (w>=100 or x==72) and h>=20:panels.append((x,y,w,h))
    if args[0]=='assign' and c==0xffeaf0f5 and w==h==30:slots.append((x,y,w,h))
   count+=1
  if args[0]=='assign':assert selected,args
  if args[0]=='inventory':assert thumb,args
  if args[0] in ['feedback','windows']:
   for i,a in enumerate(panels):
    for b in panels[i+1:]:assert a[0]+a[2]<=b[0] or b[0]+b[2]<=a[0] or a[1]+a[3]<=b[1] or b[1]+b[3]<=a[1],(args,a,b)
  if args[0]=='feedback':
   flags=int(args[1]);compact=bool(flags&32)
   names=[p for p in panels if p[0]==72]
   assert bool(names)==bool(flags&1 and not flags&64),(args,names)
   if names:assert names[0][1]+names[0][3]==424,args
   if flags&2:assert any(p[0]==232 and p[1]==(240 if compact else 384)for p in panels),args
   if flags&4:assert any(p[0]==232 and p[1]==(48 if compact else 320)for p in panels),args
   assert bool(casts)==bool(flags&8),(args,casts)
   for a in casts:
    for b in panels:assert a[0]+a[2]<=b[0] or b[0]+b[2]<=a[0] or a[1]+a[3]<=b[1] or b[1]+b[3]<=a[1],(args,a,b)
  if args[0]=='feedback' and int(args[1])==2:
   assert any(p[0]==232 and p[2]<300 for p in panels),args
  if args[0]=='cast' and len(args)>2:
   ticks=[line for line in r.stdout.splitlines() if line.startswith('F ') and line.split()[3:5]==['1','4'] and int(line.split()[5])==0xff181818]
   assert len(ticks)==int(float(args[2])*4),(args,len(ticks))
   assert any(line.startswith('F ') and int(line.split()[5])==0xff58aaff for line in r.stdout.splitlines()),args
  if args[0]=='cast':
   assert not any(line.startswith('Q ')for line in r.stdout.splitlines()),args
   assert len(casts)==(float(args[1])>0),(args,casts)
   for line in r.stdout.splitlines():
    if line.startswith('F '):assert int(line.split()[4])<=6,(args,line)
  if args[0]=='roll' and abs(float(args[1])/math.pi-round(float(args[1])/math.pi))<.00001:
   assert len(front)==len(rear)==len(shadows)==7,(args,front,rear)
   occlusion=max(p[1]+p[3] for p in front+shadows)
   for p in rear:assert 3*(p[1]+p[3]-occlusion)>=2*p[3],(args,p,occlusion)
  if args[0]=='assign':assert len(slots)==14,args
  # Native palette fills also consume one quad, as the recorder does.
  peak=max(peak,count)
 print(f'PASS {len(cases)} actual UI cases: all assignments/cart rows/job ends, inventory, services, all69 skill labels, feedback combinations and open windows; fixed feedback anchors, optional tooltips, text-free cast bars, storage/menu screens, two-thirds rear exposure and full-roll bounds; peak {peak} quads of1536')
print('PASS Test39 '+('UI-only' if '--ui-only' in sys.argv else 'host')+' validation complete; native compile and xemu/hardware remain separate checks')
