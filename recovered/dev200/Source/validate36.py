"""MIT. Current Test36 host suite; historical test files are retained separately.
Run: python validate35.py [--sanitize]. Native build and emulator tests are separate.
"""
from pathlib import Path
import subprocess, tempfile, sys, math, os
root=Path(__file__).resolve().parent
sanitize='--sanitize' in sys.argv
flags=['-O1','-g']+(['-fsanitize=address,undefined']if sanitize else [])
with tempfile.TemporaryDirectory(prefix='myro36-') as tmp:
 out=Path(tmp)
 tests=[('test_acolyte35',[]),('test_expansion36',[]),('test_mechanics36',[]),('test_batch36',[]),('test_services36',[]),('test_save35',[]),('test_inventory',[]),('test_shop',[]),('test_contact34',[]),('test_projection',[]),('test_sprite_projection35',[]),('test_atlas34',['skin_assets.c']),('test_hud_batch',[])]
 for name,extra in tests:
  exe=out/name
  subprocess.run(['gcc',*flags,str(root/(name+'.c')),*[str(root/e)for e in extra],'-lm','-lz','-o',str(exe)],check=True)
  args=[str(exe)]+([str(root.parent/'Actors/actors.bin')]if name=='test_sprite_projection35' else [])
  subprocess.run(args,check=True)
 subprocess.run([sys.executable,str(root/'verify_player_contact35.py'),str(root.parent/'Actors/actors.bin')],check=True)
 subprocess.run([sys.executable,str(root/'test_hud_backend.py')],check=True)
 exe=out/'ui'
 subprocess.run(['gcc',*flags,str(root/'test_ui36.c'),str(root/'ui_assets.c'),str(root/'skin_assets.c'),'-lm','-lz','-o',str(exe)],check=True)
 cases=[['assign',str(i)]for i in range(14)]+[['cart',str(i)]for i in range(36)]+[['skills',str(i)]for i in range(1,7)]+[['craft'],['appraise'],['styles'],['equip']]+[['roll',str(i*math.pi/64)]for i in range(65)]
 cases += [['inventory',str(i)]for i in range(18)]+[['cast',str(v)]for v in [.1,2.5,5]]+[['services',str(i),str(c)]for i in range(8)for c in range(2)]+[['servicecart',str(i)]for i in range(36)]+[['shop',str(i),str(selling)]for i in range(18)for selling in range(2)]
 peak=0
 for args in cases:
  r=subprocess.run([str(exe),*args],check=True,capture_output=True,text=True)
  count=0;selected=False;thumb=False
  for line in r.stdout.splitlines():
   a=line.split()
   if a[0]=='Q':
    x,y,w,h,u,v,uw,vh=map(float,a[1:]);assert x>=0 and y>=0 and x+w<=640.1 and y+h<=480.1,(args,line)
   elif a[0]=='F':
    x,y,w,h,c=map(int,a[1:]);assert x>=0 and y>=0 and x+w<=640 and y+h<=480,(args,line)
    if args[0]=='roll' and 210<=x<=430 and w>=10:assert y+h<=466,(args,line)
    if args[0]=='inventory' and (w,h,c)==(4,67,0xff8fd1ff):
     first=max(0,int(args[1])//4-2);assert x==581 and y==119+45*first//2,(args,line);thumb=True
    if args[0]=='assign':
     n=int(args[1]);xx=216+(n%6+1)*30 if n<12 else 186 if n==12 else 431;yy=392+n//6*33 if n<12 else 409;ww=28 if n<12 else 23
     if (x,y,w,h,c)==(xx,yy,ww,2,0xffffda45):selected=True
   count+=1
  if args[0]=='assign':assert selected,args
  if args[0]=='inventory':assert thumb,args
  # Native palette fills also consume one quad, as the recorder does.
  peak=max(peak,count)
 print(f'PASS {len(cases)} actual UI cases: all assignments/cart rows/job ends, crafting/appraisal/styles/equipment, full roll; screen/help bounds; peak {peak} quads of1536')
print('PASS Test36 host validation complete; native compile and xemu/hardware remain separate checks')
