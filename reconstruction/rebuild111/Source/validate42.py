"""MIT. Current Test42 host suite; historical test files are retained separately.
Run: python validate42.py [--sanitize] [--ui-only]. Native build and emulator tests are separate.
"""
from pathlib import Path
import subprocess, tempfile, sys, math, os
root=Path(__file__).resolve().parent
sanitize='--sanitize' in sys.argv
flags=['-O1','-g']+(['-fsanitize=address,undefined']if sanitize else [])
with tempfile.TemporaryDirectory(prefix='myro42-') as tmp:
 out=Path(tmp)
 tests=[('test_feedback42',[]),('test_spell_world42',[]),('test_target_frames41',['encounter_assets.c']),('test_behaviour42',[]),('test_acolyte38',[]),('test_expansion38',[]),('test_mechanics37',[]),('test_batch41',[]),('test_cast37',[]),('test_storage41',[]),('test_support_cast38',[]),('test_ui_controls42',[]),('test_art41',[]),('test_art_render41',[]),('test_session40',[]),('test_cart42',[]),('test_upload40',[]),('test_cast_head38',[]),('test_services36',[]),('test_save41',[]),('test_inventory',[]),('test_shop',[]),('test_contact34',[]),('test_projection',[]),('test_sprite_projection35',[]),('test_atlas34',['skin_assets.c']),('test_hud_batch',[])]
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
 subprocess.run(['gcc',*flags,str(root/'test_ui42.c'),str(root/'ui_assets.c'),str(root/'skin_assets.c'),'-lm','-lz','-o',str(exe)],check=True)
 cases=[['assign',str(i)]for i in range(14)]+[['cart',str(i)]for i in range(36)]+[['skills',str(i)]for i in range(1,7)]+[['craft'],['appraise'],['styles'],['equip']]+[['roll',str(i*math.pi/64)]for i in range(65)]
 cases += [['inventory',str(i)]for i in range(18)]+[['cast',str(v)]for v in [0,.1,2.5,5]]+[['services',str(i),str(c)]for i in range(9)for c in range(2)]+[['servicecart',str(i)]for i in range(36)]+[['shop',str(i),str(selling)]for i in range(18)for selling in range(2)]
 cases += [['feedback',str(i),'63']for i in range(128)]+[['feedback','63',str(i)]for i in range(69)]+[['windows',str(w),str(i)]for w in range(4)for i in range(6)]
 cases += [['storage',str(i)]for i in range(36)]+[['pause38',str(i),str(v)]for i in range(4)for v in range(2)]+[['windows',str(w),str(i),'1']for w in range(4)for i in range(6)]+[['feedback','63',str(128+i)]for i in range(18)]
 cases += [['preview39',str(i)]for i in range(21)]+[['cast','.0001',str(t)]for t in [.5,1,2,4,5]]
 cases += [['dock40',str(i)]for i in range(512)]+[['target40',str(i)]for i in [0,50,100]]+[['stylist40',str(i)]for i in range(5)]+[['label40',str(i)]for i in range(69)]
 cases += [['toggles41',str(row),str(mask)]for row in range(12)for mask in [0,1,127]]+[['popup41',str(mask),str(cat)]for mask in range(128)for cat in range(7)]+[['dev41',str(tab),str(row)]for tab in range(4)for row in range([8,9,6,4][tab])]
 cases += [['money41',str(z)]for z in [0,999,10000,999999,1000000000]]
 peak=0
 for args in cases:
  r=subprocess.run([str(exe),*args],check=True,capture_output=True,text=True)
  panels=[];captions=[];fills=[];quads=[]
  for line in r.stdout.splitlines():
   a=line.split()
   if a[0]=='Q':
    q=tuple(map(float,a[1:]));x,y,w,h,*uv=q;assert x>=0 and y>=0 and x+w<=640.1 and y+h<=480.1,(args,line);quads.append(q)
   elif a[0]=='F':
    f=tuple(map(int,a[1:]));x,y,w,h,c=f;assert x>=0 and y>=0 and x+w<=640 and y+h<=480,(args,line);fills.append(f)
    if c==0xffeaf0f5 and (w>=100 or x==72) and h>=20:panels.append((x,y,w,h))
    if c==0xffeaf0f5 and x==72:captions.append((x,y,w,h))
  if args[0] in ['feedback','windows','dock40']:
   for i,a in enumerate(panels):
    for b in panels[i+1:]:assert a[0]+a[2]<=b[0] or b[0]+b[2]<=a[0] or a[1]+a[3]<=b[1] or b[1]+b[3]<=a[1],(args,a,b)
  assert len(captions)<=1,(args,captions)
  for p in captions:assert p[1] in [380,400] and p[3]==24,(args,p)
  if args[0]=='dock40':
   f=int(args[1]);off=bool(f&16);msg=bool(f&4 and (not f&8 or not off));tip=not off and bool((f&1 and f&2 and not f&256) or (f&1 and f&32) or f&64 or f&128)
   assert bool(captions)==bool(msg or tip),(args,captions)
   if captions:assert captions[0][1]==(380 if f&256 else 400),args
  if args[0]=='windows' and len(args)>3 and args[3]=='1':assert not captions,args
  if args[0]=='label40':assert len(captions)==1,args
  if args[0]=='roll' and abs(float(args[1])/math.pi-round(float(args[1])/math.pi))<.00001:
   front=[f for f in fills if f[4]==0xffeaf0f5 and f[2:4]==(30,30)];rear=[f for f in fills if f[4]==0xffeaf0f5 and f[2:4]==(16,16)];shadow=[f for f in fills if f[4]==0x70000000 and f[2:4]==(30,30)];assert len(front)==len(rear)==len(shadow)==7,args
   bottom=max(f[1]+f[3] for f in front+shadow)
   assert all(3*(f[1]+f[3]-bottom)>=2*f[3]for f in rear),args
  if args[0]=='assign':
   n=int(args[1]);x=202+(n%6+1)*34 if n<12 else 170 if n==12 else 448;y=403+n//6*36 if n<12 else 424;w=32 if n<12 else 22
   assert (x,y,w,2,0xffffda45) in fills,args
  if args[0]=='inventory':assert any(f[0]==581 and f[2:4]==(4,67) for f in fills),args
  if args[0]=='cast':
   assert not quads,args
   black=[f for f in fills if f[2:4]==(48,6) and f[4]==0xff181818];assert len(black)==(float(args[1])>0),args
   if len(args)>2:
    ticks=[f for f in fills if f[2:4]==(1,4) and f[4]==0xff181818];assert len(ticks)==min(12,math.ceil(float(args[2])*2))-1,(args,ticks)
  if args[0]=='cast' and 0<float(args[1])<(float(args[2]) if len(args)>2 else 5):
   blues=[f for f in fills if f[4]==0xff58aaff];assert blues,args
   assert blues[0][0]==297,args
   if float(args[1])<=.0001:assert blues[0][2]==46,(args,blues)
  if args[0]=='target40':
   assert len(quads)==8,args
   for q in quads:assert abs(q[2]-4/3)<.01 or abs(q[3]-4/3)<.01,(args,q)
   assert sum(abs(q[1]+q[3]-249)<.02 for q in quads)==4,(args,quads)
  peak=max(peak,len(quads)+len(fills))
 print(f'PASS {len(cases)} sanitized actual UI cases: one bottom caption, tooltip-off/no-select-or-sitting leaks, paging/layout, all21 previews/69 labels, five stylist rows, all eight thin target corners, preserved hotbar/assignments and window bounds; peak{peak}/1536 quads')
print('PASS Test42 '+('UI-only' if '--ui-only' in sys.argv else 'host')+' validation complete; native and xemu/hardware checks separate')
